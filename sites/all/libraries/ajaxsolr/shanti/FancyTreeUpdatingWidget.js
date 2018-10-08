(function (callback) {
  if (typeof define === 'function' && define.amd) {
    define(['core/AbstractWidget'], callback);
  }
  else {
    callback();
  }
}(function () {

    var maskSearchResults = function ( isMasked ) {
//        console.log("FancyTreeUpdateingWidget: maskSearchResults: " + isMasked);
        var showhide = (isMasked)?'show':'hide';
        jQuery('.view-section>.tab-content').overlayMask(showhide);
    }

    var maskTree = function(isMasked) {
//        console.log("FancyTreeUpdateingWidget: maskTree: " + isMasked);
        var showhide = (isMasked)?'show':'hide';
        jQuery('#tree').overlayMask(showhide);
    }

    var notify = {
        warn: function (warnid, warnhtml) {
            var wonk = function () {
                if (jQuery('div#' + warnid).length) {
                    jQuery('div#' + warnid).fadeIn();
                } else {
                    jQuery('<div id="' + warnid + '" class="alert alert-danger fade in"><button type="button" class="close" data-dismiss="alert" aria-hidden="true">×</button>' + warnhtml + '</div>').fadeIn().appendTo('#notification-wrapper');
                }
            }

            if (jQuery('#notification-wrapper div#' + warnid).length) {
                jQuery('#notification-wrapper div#' + warnid).fadeOut('slow', wonk);
            } else {
                wonk();
            }
        },

        clear: function (warnid) {

            if (warnid) {
                jQuery('#notification-wrapper div#' + warnid).fadeOut('slow').remove()
            } else {
                jQuery('#notification-wrapper div').fadeOut('slow').remove()
            }
        }
    };

    function searchChanged(self) {

        if (!self.tmpstore) {
            self.tmpstore = new AjaxSolr.ParameterStore();
        }

        var tmpparams = self.tmpstore.string().replace(/&start=\d+/, '');
        var mgrparams = self.manager.store.string().replace(/&start=\d+/, '');

//        console.log("TMPSTORE: " + tmpparams);
//        console.log("MANSTORE: " + mgrparams);

        var changed = tmpparams != mgrparams;
//        console.log("Search Changed: " + changed);

        return changed;
    }

    (function ($) {

/**
 *
 * @expects to work someday
 * @class FancyTreeUpdatingWidget
 * @augments AjaxSolr.AbstractWidget
 * @todo
 */
AjaxSolr.FancyTreeUpdatingWidget = AjaxSolr.AbstractWidget.extend(
  /** @lends AjaxSolr.FancyTreeUpdatingWidget.prototype */
  {
  /**
   * @param {Object} [attributes]
   */
  constructor: function (attributes) {
    AjaxSolr.FancyTreeUpdatingWidget.__super__.constructor.apply(this, arguments);
//    AjaxSolr.extend(this, {
//    }, attributes);
  },

  init: function () {
      this.servlet = this.servlet || this.manager.servlet;
//      console.log("PILL: " + self.servlet);

  },

  beforeRequest: function () {
//      console.log("FancyTreeUpdatingWidget: beforeRequest()");
      if (searchChanged(this)) {
          maskSearchResults(true);
      }
  },

  afterRequest: function () {
//      console.log("FancyTreeUpdatingWidget: afterRequest()");

      // rerun the query with the correct specs
      var self = this;
      // maskSearchResults(false);
      this.servlet = this.servlet || this.manager.servlet;

//      console.log("GHERKIN: "  + self.manager.store.string());
//      console.log("DILL: " + self.servlet);

      //  We need to make sure we don't update the tree unnecessarily.
      // If this was simply a paging change then DON'T UPDATE
      // If this is a query change then UPDATE!

      // wsee https://github.com/evolvingweb/ajax-solr/wiki/Tutorial%3A-Send-a-Solr-request-without-updating-widgets
      // this is to prevent all the registered widgets from updating (And causing additional requests)
      if (searchChanged(self)) {
          self.tmpstore.remove("q");
          self.tmpstore.parseString(self.manager.store.string());
//          console.log("q=" + self.manager.store.get("q"));
//          console.dir(self.manager.store.get("q"));

          // don't do a query if there is no query!
          if (self.manager.store.get("q").value !== null) {
                self.manager.executeRequest(self.servlet, 'json.nl=map&fl=id&rows=300000&' + self.manager.store.string(), function (data) {
//                  console.log("QUERYING: " + 'json.nl=map&fl=id&rows=300000&' + self.manager.store.string());
//                  console.dir(data);

                  var resultHash = {};
                  $(data.response.docs).each( function(z,x) {
    //              console.log("hashing:  " + x.id + "   " + x.id.split('-')[1]);
                      resultHash[x.id.split('-')[1]] = true;
                  })

                  if (data.response.numFound === 0) {
                      notify.warn("warnnoresults", "There are no matches.  <br>Try to modify your search.");
                  } else {
                      notify.clear();
                  }

                  // clear the highlighting
                  $('span.fancytree-title').has("mark").each(
                      function() {
//                        console.log("found: " + this);
                        $(this).text($(this).text());
                      }
                  );

                  maskTree(true);
                  var tree = $('#tree').fancytree('getTree');

                tree.clearFilter();
                tree.options.filter.hide = true;
                  tree.options.filter.leavesOnly = false;
                    tree.options.filter.scrollIntoView = false;
                  tree.filterNodes(function (node) {
                      // console.log(node.key);
                      //if (typeof resultHash[node.key] !== 'undefined') {
                      //    console.log(node.key + ":" + resultHash[node.key]);
                      //}
                      return (typeof resultHash[node.key] !== 'undefined');
                  },false);
                  console.log("done traversing");
                  maskTree(false);
                  // we are masking everything and unmasking here (for the time being).
                  maskSearchResults(false)

                  var txt = $('#searchform').val();
                  $('span.fancytree-title').highlight(txt, { element: 'mark' });


              },false);
          } else {
              // Let's not do the search, since there is no query.
              maskSearchResults(false)
          }
      } else {
          console.log("FancyTreeUpdatingWidget: no param change: doing nothing.")
          maskTree(false);
          // we are masking everything and unmasking here (for the time being).
          maskSearchResults(false);
      }

  }
});

})(jQuery);

}));
