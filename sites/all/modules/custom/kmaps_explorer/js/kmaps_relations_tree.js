/*
 *  Project: UVa KMaps
 *  Description: Plugin to handle the fancyTree implementation with Solr
 *  Author: djrc2r
 */

// the semi-colon before function invocation is a safety net against concatenated
// scripts and/or other plugins which may not be closed properly.
;(function ( $, window, document, undefined ) {
  "use strict";

  var SOLR_ROW_LIMIT = 2000;
  var DEBUG = false;

  // undefined is used here as the undefined global variable in ECMAScript 3 is
  // mutable (ie. it can be changed by someone else). undefined isn't really being
  // passed in so we can ensure the value of it is truly undefined. In ES5, undefined
  // can no longer be modified.

  // window is passed through as local variable rather than global
  // as this (slightly) quickens the resolution process and can be more efficiently
  // minified (especially when both are regularly referenced in your plugin).

  // Create the defaults once
  var pluginName = 'kmapsRelationsTree',
    defaults = {
      termIndex: "http://localhost/solr/kmterms_dev",
      assetIndex: "http://localhost/solr/kmassets_dev",
      tree: "places",
      featuresPath: "/features/%%ID%%",
      checkbox: false,
      selectMode: 2,
      domain: "places",
      featureId: 1,
      perspective: "pol.admin.hier",
      descendants: false,
      directAncestors: true,
      descendantsFullDetail: true,
      sortBy: 'header_ssort+ASC',
      initialScrollToActive: false,
      displayPopup: false,
      mandalaURL: "https://mandala.shanti.virginia.edu/%%APP%%/%%ID%%/%%REL%%/nojs",
      solrUtils: {}, //requires solr-utils.js library
      language: 'eng',
      extraFields: [],
      nodeMarkerPredicates: [], //A predicate is: {field:, value:, operation: 'eq', mark: 'nonInteractive'}
    };

  // The actual plugin constructor
  function Plugin( element, options ) {
    this.element = element;

    // jQuery has an extend method which merges the contents of two or
    // more objects, storing the result in the first object. The first object
    // is generally empty as we don't want to alter the default options for
    // future instances of the plugin
    this.options = $.extend( {}, defaults, options) ;

    this._defaults = defaults;
    this._name = pluginName;

    this.init();
  }

  Plugin.prototype = {
    init: function () {
      const plugin = this;
      var options = {
        descendants: plugin.options.descendants,
        directAncestors: plugin.options.directAncestors,
        descendantsFullDetail: plugin.options.descendantsFullDetail,
        sortBy: plugin.options.sortBy,
        extraFields: plugin.options.extraFields,
        nodeMarkerPredicates: plugin.options.nodeMarkerPredicates,
        checkbox: plugin.options.checkbox || false,
        selectMode: plugin.options.selectMode || 2,
      };
      // Place initialization logic here
      // You already have access to the DOM element and the options via the instance,
      // e.g., this.element and this.options
      $(plugin.element).fancytree({
        extensions: ["filter", "glyph"],
        source: plugin.getAncestorTree(options),
        init: function(event,data) {
          if(plugin.options.initialScrollToActive){
            plugin.scrollToActiveNode();
          }
          plugin.sendEvent("INIT", event, data);
        },
        checkbox: plugin.options.checkbox, // plugin.settings.checkboxes,
        selectMode: plugin.options.selectMode,
        glyph: {
          map: {
            doc: "",
            docOpen: "",
            error: "glyphicon glyphicon-warning-sign",
            expanderClosed: "glyphicon glyphicon-plus-sign",
            expanderLazy: "glyphicon glyphicon-plus-sign",
            // expanderLazy: "glyphicon glyphicon-expand",
            expanderOpen: "glyphicon glyphicon-minus-sign",
            // expanderOpen: "glyphicon glyphicon-collapse-down",
            checkbox: "glyphicon glyphicon-unchecked",
            checkboxSelected: "glyphicon glyphicon-check",
            checkboxUnknown: "glyphicon glyphicon-share",
            folder: "",
            folderOpen: "",
            loading: "glyphicon glyphicon-refresh"
              //              loading: "icon-spinner icon-spin"
          }
        },
        activate: function(event, data){
          var node = data.node,
            orgEvent = data.originalEvent;
          if(typeof(node.data.marks) !== "undefined" && node.data.marks.includes('nonInteractiveNode')) {
            node.toggleExpanded();
          } else {
            if(node.data.href){
              window.location.href=node.data.href;
            }
          }
          plugin.sendEvent("ACTIVATE", event, data);
        },
        lazyLoad: function(event,data){
            data.result = plugin.getDescendantTree(data.node.key,data.node.getKeyPath(),plugin.options.sortBy);
        },
        createNode: function (event, data) {
          // data.node.span.childNodes[2].innerHTML = '<span id="ajax-id-' + data.node.key + '">' +
          //   data.node.title + ' ' +
          //   ( data.node.data.path || "") + '</span>';


          // Some "interesting" tomfoolery to insert our our drupal ajax special sauce...

          var node = $(data.node.span).find('.fancytree-title');
          node.attr('id', 'ajax-id-' + data.node.key);
          node.once('nav', function () {
            var base = $(this).attr('id');
            var argument = $(this).attr('argument');
            var url = location.origin + location.pathname.substring(0, location.pathname.indexOf(plugin.options.domain)) + plugin.options.domain + '/' + data.node.key + '/overview/nojs';
            Drupal.ajax[base] = new Drupal.ajax(base, this, {
              url: url,
              event: 'navigate',
              progress: {
                type: 'throbber'
              }
            });
          });

          var path = "";//plugin.makeStringPath(data);
          var elem = data.node.span;
          //var key = plugin.options.domain +"-" + data.node.key;
          var key = data.node.key;
          var title = data.node.title;
          var caption = data.node.data.caption;
          var theIdPath = data.node.data.path;
          //var displayPath = data.node.data.displayPath;
          var displayPath = data.node.getParentList(true,true).reduce(function(parentPath,ancestor) {
            var title_match = ancestor.title;
            var current_title = "";
            if(title_match != null){
              current_title = title_match[0];
            }
            var current_link = "<a href='"+ancestor.data.href+"'>"+
              current_title+"</a>";
            if(parentPath === ""){
              return current_link;
            }
            return parentPath + "/" + current_link;
          }, "");
          if(plugin.options.displayPopup){
            var pop_container = $('<span class="popover-kmaps" data-app="places" data-id="'+key+'"><span class="popover-kmaps-tip"></span><span class="icon shanticon-menu3"></span></span>');
            $(elem).append($(pop_container));
            $(pop_container).kmapsPopup({
              featuresPath: plugin.options.featuresPath,
              domain: plugin.options.domain,
              featureId:  "",
              mandalaURL: plugin.options.mandalaURL,
              solrUtils: plugin.options.solrUtils,
              language: plugin.options.language
            });
          }
          return data;
        },

        // User Event Handlers -- ys2n
        select: function (event, data) {
          plugin.sendEvent("SELECT", event, data);
        },
        focus: function (event, data) {
          data.node.scrollIntoView(true);
          plugin.sendEvent("FOCUS", event, data);
        },
        keydown: function (event, data) {
          plugin.sendEvent("KEYDOWN", event, data);
        }
      });

      function makeStringPath(data) {
        return $.makeArray(data.node.getParentList(false, true).map(function (x) {
          return x.title;
        })).join("/");
      }

    },
    scrollToActiveNode: async function() {
      var plugin = this;
      var tree = $(plugin.element).fancytree('getTree');
      var active = tree.getActiveNode();
      if (active){
        active.makeVisible().then(function() {
          var totalOffset =$(active.li).offset().top-$(active.li).closest('.fancytree-container').offset().top;
          $(active.li).closest('.fancytree-container').scrollTop(totalOffset);
        });
      }
    },
    getAncestorPath: function() {
      const plugin = this;
      return plugin.options.solrUtils.getAncestorPath();
    },
    getAncestorTree: function(options){
      const plugin = this;
      if(plugin.options.directAncestors) {
        return plugin.options.solrUtils.getAncestorTree(options);
      }
      return plugin.options.solrUtils.getFullAncestorTree(options);
    },
    getDescendantTree: function(featureId,keyPath){
      const plugin = this;
      if(!plugin.options.directAncestors) {
        var ancestorPath = keyPath.split("/"+plugin.options.domain+"-");
        ancestorPath.shift();
        return plugin.options.solrUtils.getDescendantsInPath(ancestorPath.join("/"),ancestorPath.length+1,plugin.options.sortBy,plugin.options.extraFields,plugin.options.nodeMarkerPredicates);
      }
      return plugin.options.solrUtils.getDescendantTree(featureId,plugin.options.descendantsFullDetail,plugin.options.sortBay,plugin.options.extraFields, plugin.options.nodeMarkerPredicates);
    },

    // utility functions -- ys2n
    sendEvent: function (handler, event, data) {
      function encapsulate(eventtype, event, n) {
        if (!n) {
          // console.error("Node data missing...");
          n = {
            title: "",
            key: "",
            data: {
              path: "",
              level: 0,
              parent: "/"
            }
          }
        }
        return {
          eventtype: eventtype, // "useractivate","codeactivate"
          title: n.title,
          key: n.key,
          path: "/" + n.data.path,
          level: n.data.level,
          parent: "/" + n.data.parent,
          event: event
        };
      }

      // console.error("HANDLER:  " + handler + " EVENT = " + event);

      if (handler === 'INIT') {
        $(this.element).trigger("init", encapsulate("init", event));
      }


      if (data.node == null) {
        return;
      }
      var kmapid = data.node.key;
      var path = "/" + data.node.data.path;
      var origEvent = (event.originalEvent) ? event.originalEvent.type : "none";
      var keyCode = "";
      if (event.keyCode) {
        keyCode = "(" + event.keyCode + ")";
      }
      if (event.type === "fancytreeactivate" && origEvent === "click") {
        // This was a user click
        //if (DEBUG) console.error("USER CLICKED: " + data.node.title);
        $(this.element).trigger("useractivate", encapsulate("useractivate", event, data.node));
      } else if (event.type === "fancytreekeydown" && origEvent === "keydown") {
        // This was a user arrow key (or return....)
        //if (DEBUG) console.error("USER KEYED: " + data.node.tree.getActiveNode() + " with " + event.keyCode);
        $(this.element).trigger("useractivate", encapsulate("useractivate", event, data.node.tree.getActiveNode()));
      } else if (event.type === "fancytreefocus" && origEvent === "none") {
        // if (DEBUG) console.error("FOCUS: " + data.node.title);
      } else if (event.type === "fancytreeactivate" && origEvent === "none") {
        // if (DEBUG) console.error("ACTIVATE: " + data.node.title);
        $(this.element).trigger("activate", encapsulate("codeactivate", event, data.node.tree.getActiveNode()));
      } else if (event.type === "fancytreeselect" && origEvent === "none") {
        // console.dir(data.node);
        if (data.node.selected) {
          $(this.element).trigger("select", data);
          console.log("SELECT: " + JSON.stringify(data.node.title));
          // console.dir(data);
        } else {
          $(this.element).trigger("deselect", data);
          console.log("DESELECT: " + JSON.stringify(data.node.title));
        }

      } else {
        log("UNHANDLED EVENT: " + event);
        console.dir(event);
      }
    },

  };

  // You don't need to change something below:
  // A really lightweight plugin wrapper around the constructor,
  // preventing against multiple instantiations and allowing any
  // public function (ie. a function whose name doesn't start
  // with an underscore) to be called via the jQuery plugin,
  // e.g. $(element).defaultPluginName('functionName', arg1, arg2)
  $.fn[pluginName] = function ( options ) {
    var args = arguments;

    // Is the first parameter an object (options), or was omitted,
    // instantiate a new instance of the plugin.
    if (options === undefined || typeof options === 'object') {
      return this.each(function () {

        // Only allow the plugin to be instantiated once,
        // so we check that the element has no plugin instantiation yet
        if (!$.data(this, 'plugin_' + pluginName)) {

          // if it has no instance, create a new one,
          // pass options to our plugin constructor,
          // and store the plugin instance
          // in the elements jQuery data object.
          $.data(this, 'plugin_' + pluginName, new Plugin( this, options ));
        }
      });

      // If the first parameter is a string and it doesn't start
      // with an underscore or "contains" the `init`-function,
      // treat this as a call to a public method.
    } else if (typeof options === 'string' && options[0] !== '_' && options !== 'init') {

      // Cache the method call
      // to make it possible
      // to return a value
      var returns;

      this.each(function () {
        var instance = $.data(this, 'plugin_' + pluginName);

        // Tests that there's already a plugin-instance
        // and checks that the requested public method exists
        if (instance instanceof Plugin && typeof instance[options] === 'function') {

          // Call the method of our plugin instance,
          // and pass it the supplied arguments.
          returns = instance[options].apply( instance, Array.prototype.slice.call( args, 1 ) );
        }

        // Allow instances to be destroyed via the 'destroy' method
        if (options === 'destroy') {
          $.data(this, 'plugin_' + pluginName, null);
        }
      });

      // If the earlier cached method
      // gives a value back return the value,
      // otherwise return this to preserve chainability.
      return returns !== undefined ? returns : this;
    }
  };
}(jQuery, window, document));

