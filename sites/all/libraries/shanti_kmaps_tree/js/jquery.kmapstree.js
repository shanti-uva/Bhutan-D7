// the semi-colon before function invocation is a safety net against concatenated
// scripts and/or other plugins which may not be closed properly.
;(function ($, window, document, undefined) {

    "use strict";

    // undefined is used here as the undefined global variable in ECMAScript 3 is
    // mutable (ie. it can be changed by someone else). undefined isn't really being
    // passed in so we can ensure the value of it is truly undefined. In ES5, undefined
    // can no longer be modified.

    // window and document are passed through as local variable rather than global
    // as this (slightly) quickens the resolution process and can be more efficiently
    // minified (especially when both are regularly referenced in your plugin).

    var SOLR_ROW_LIMIT = 2000;
    var DEBUG = false;
    var store = sessionStorage; // TODO:  provide fallback mechanisms

    // Create the defaults once
    var pluginName = "kmapsTree",
        defaults = {
            termindex_root: "",
            kmindex_root: "",
            type: "subjects",
            root_kmapid: 0,
            root_kmap_path: "/", // "/13735/13740/13734"
            config: function () {
            },
            expand_path: null,
            checkboxes: false,
            selectMode: 2
            // baseUrl: "http://subjects.kmaps.virginia.edu/"
        };

    // copied from jquery.fancytree.js to support moved loadKeyPath function
    function _makeResolveFunc(deferred, context) {
        return function () {
            deferred.resolveWith(context);
        };
    }

    // The actual plugin constructor
    function KmapsTreePlugin(element, options) {
        this.element = element;
        // jQuery has an extend method which merges the contents of two or
        // more objects, storing the result in the first object. The first object
        // is generally empty as we don't want to alter the default options for
        // future instances of the plugin
        this.settings = $.extend({}, defaults, options);
        this._defaults = defaults;
        this._name = pluginName;
        this.init();
    }

    function log(msg) {
        if (DEBUG) {
            console.log(msg);
            $('#debug').append(msg + "<br/>");
        }
    }

    function hashCode(str) {
        var result = '';
        var hash = 0, i, chr;
        for (i = 0; i < str.length; i++) {
            chr = str.charCodeAt(i);
            hash = ((hash << 5) - hash) + chr;
            hash |= 0; // Convert to 32bit integer
        }
        result = ("0000000" + (hash >>> 0).toString(16)).substr(-8);
        return result;
    }

    var cleanPath = function (path, parentOnly, rootSlash) {
        log("cleanPath() args: " + JSON.stringify(arguments, undefined, 2));
        log("cleanPath() in: " + path);
        // Eliminate initial/terminal slash
        path = path.replace(/^\/+/, '');
        path = path.replace(/\/$/, '');
        var p = path.split('/');
        if (parentOnly) {
            p.splice(-1, 1);
        }
        path = rootSlash ? "/" : "";
        path += p.join('/');
        var msg = "cleanPath() out: " + path;
        log(msg);
        return path;
    };

    ////  Cleanup and re-root the paths
    var fixPath = function (path, i) {
        path = cleanPath(path);

        var rootpath = cleanPath(plugin.settings.root_kmap_path, true, false);
        log("fixPath(): rootpath = " + rootpath);
        log("fixPath(): path = " + path);

        // truncate the beginning of the path according to kmap_root_path
        path = path.replace(rootpath, "");
        log("fixPath(): fixed path = " + path);

        // truncate the beginning of the path according to kmap_root_path
        var clean = cleanPath(path, false, true);
        log("fixPath(): fixed clean = " + clean);

        return clean;
    };

    $.extend(KmapsTreePlugin.prototype, {
        debug: false,
        init: function () {
            // Place initialization logic here
            // You already have access to the DOM element and
            // the options via the instance, e.g. this.element
            // and this.settings
            // you can add more functions like the one below and
            // call them like so: this.yourOtherFunction(this.element, this.settings).
            var plugin = this;
            this.element = $(plugin.element);

            // create unique ID if it doesn't have one already
            $(this).uniqueId();

            //
            // Fancytree plugin
            //
            $(plugin.element).fancytree({
                extensions: ["filter", "glyph"],
                generateIds: false,
                quicksearch: false,
                checkbox: plugin.settings.checkboxes,
                selectMode: plugin.settings.selectMode,
                minExpandLevel: 1, // TODO: reconcile this with lazy loading.  Only "1" is supported currently.
                theme: 'bootstrap',
                debugLevel: 0,
                autoScroll: false,
                filter: {
                    highlight: true,
                    counter: false,
                    mode: "hide",
                    leavesOnly: false
                },
                cookieId: this.id,
                idPrefix: this.id,
                source: {
                    url: plugin.buildQuery(
                        plugin.settings.termindex_root,
                        plugin.settings.type,
                        plugin.settings.root_kmap_path,
                        1,
                        plugin.settings.root_kmap_path.split('/').length
                    ),
                    dataType: 'jsonp',
                    jsonp: 'json.wrf'
                },

                // User Event Handlers
                select: function (event, data) {
                    plugin.sendEvent("SELECT", event, data);
                },
                focus: function (event, data) {
                    data.node.scrollIntoView(true);
                    plugin.sendEvent("FOCUS", event, data);
                },
                keydown: function (event, data) {
                    plugin.sendEvent("KEYDOWN", event, data);
                },
                activate: function (event, data) {
                    plugin.sendEvent("ACTIVATE", event, data);
                },

                // Fancytree Building Event Handlers
                createNode: function (event, data) {
                    // data.node.span.childNodes[2].innerHTML = '<span id="ajax-id-' + data.node.key + '">' + data.node.title + ' ..... ' + data.node.data.path + '</span>';

                    var path = plugin.makeStringPath(data);
                    var elem = data.node.span;
                    var key = data.node.key;
                    var type = plugin.settings.type;
                    var title = data.node.title;
                    var caption = data.node.data.caption;
                    var theIdPath = data.node.data.path;
                    var displayPath = data.node.data.displayPath;

                    decorateElementWithPopover(elem, key, title, displayPath, caption);

                    return data;
                },
                renderNode: function (event, data) {
                    if (!data.node.isStatusNode()) {
                        var keystr = (plugin.settings.showIDs) ? ' [' + data.node.key + ']' : '';
                        // data.node.span.childNodes[2].innerHTML =
                        //     '<span id="ajax-id-' + data.node.key + '">'
                        //     + data.node.title
                        //     + keystr
                        //     + ' <span class="count"></span></span>';

                      var elem = data.node.span
                      $(elem).find('.fancytree-title').attr("id", "ajax-id-" + data.node.key);

                      // add a count span, if there isn't one already.
                      if ($(elem).find('.count').length === 0) {
                        $(elem).append("<span class=\"count\"></span>");
                      }
                      // console.error("renderNode(): ELEMENT: " + JSON.stringify($(elem).html()))

                      var path = plugin.makeStringPath(data);

                        decorateElementWithPopover(data.node.span, data.node.key, data.node.title, data.node.path, data.node.data.caption);
                        $(data.node.span).find('#ajax-id-' + data.node.key).once('nav', function () {
                            var base = $(this).attr('id');
                            var argument = $(this).attr('argument');
                            var url = location.origin + location.pathname.substring(0, location.pathname.indexOf(plugin.settings.type)) + plugin.settings.type + '/' + data.node.key + '/overview/nojs';
                            Drupal.ajax[base] = new Drupal.ajax(base, this, {
                                url: url,
                                event: 'navigate',
                                progress: {
                                    type: 'throbber'
                                }
                            });
                        });
                    }
                    return data;
                },

                postProcess: function (event, data) {
                    log("postProcess!");
                    data.result = [];

                    var docs = data.response.response.docs;
                    var facet_counts = data.response.facet_counts.facet_fields.ancestor_id_path;
                    var rootbin = {};
                    var countbin = {};

                    docs.sort(function (a, b) {
                        var aName = a.ancestor_id_path.toLowerCase();
                        var bName = b.ancestor_id_path.toLowerCase();
                        return ((aName < bName) ? -1 : ((aName > bName) ? 1 : 0));
                    });

                    for (var i = 0; i < facet_counts.length; i += 2) {
                        var path = facet_counts[i];
                        var count = facet_counts[i + 1];
                        countbin[path] = (count - 1);
                    }

                    for (var i = 0; i < docs.length; i++) {
                        var doc = docs[i];
                        var ancestorIdPath = docs[i].ancestor_id_path;
                        var ancestors = docs[i].ancestors;
                        var parentIdPath = ancestorIdPath.split('/');
                        var localId = ancestorIdPath;

                        if (parentIdPath && parentIdPath.length != 0) {
                            localId = parentIdPath.pop();
                        } else {
                            parentIdPath = [];
                            localId = "";
                        }

                        var caption = (docs[i]['caption_eng'] && $.isArray(docs[i]['caption_eng'])) ? docs[i]['caption_eng'][0] : null;
                        var displayPath = (ancestors) ? ancestors.join("/") : "";
                        var parentPath = (parentIdPath) ? parentIdPath.join("/") : "";
                        var n =
                            {
                                key: localId,
                                title: doc.header,
                                parent: parentPath,
                                path: ancestorIdPath,
                                displayPath: displayPath,
                                caption: caption,
                                level: doc.level_i,
                                lazy: (countbin[ancestorIdPath]) ? true : false,
                            };

                        rootbin[ancestorIdPath] = n;  // save for later
                    }


                    //if (DEBUG) console.log("ROOT BIN");
                    //if (DEBUG) console.log(JSON.stringify(rootbin));
                    var props = Object.getOwnPropertyNames(rootbin);
                    for (var i = 0; i < props.length; i++) {
                        var node = rootbin[props[i]];
                        if (DEBUG) console.log("node: " + node.path + "  parent:" + node.parent);

                        if (rootbin[node.parent]) {
                            var p = rootbin[node.parent];
                            if (!p.children) {
                                p.children = []
                            }
                            p.children.push(node);
                            p.lazy = false;
                            delete rootbin[props[i]];
                        }
                    }
                    var x = Object.getOwnPropertyNames(rootbin);
                    for (var i = 0; i < x.length; i++) {
                        data.result.push(rootbin[x[i]]);
                    }
                    if (DEBUG) console.dir({log: "result", "data": data.result});
                    //data.result.sortChildren();
                },

                lazyLoad: function (event, data) {

                    if (DEBUG) console.error("EVENT: lazyload");
                    var id = data.node.key;
                    var lvla = 1 + data.node.data.level;
                    var lvlb = 1 + data.node.data.level;
                    var path = data.node.data.path;
                    var termIndexRoot = plugin.settings.termindex_root;
                    var type = plugin.settings.type;
                    data.result = {
                        url: plugin.buildQuery(termIndexRoot, type, path, lvla, lvlb),
                        dataType: 'jsonp',
                        jsonp: 'json.wrf'
                    };
                },

                init: function (event, data) {
                    var path = "";
                    var safe_path = "";
                    var focus_id = "";
                    // var DEBUG = true;

                    log("initing!");
                    if (Drupal
                        && Drupal.settings
                        && Drupal.settings.kmaps_explorer
                        && Drupal.settings.kmaps_explorer.kmaps_path
                    ) {
                        path = Drupal.settings.kmaps_explorer.kmaps_path
                        focus_id = Drupal.settings.kmaps_explorer.kmaps_id
                    }
                    if (DEBUG) console.error("path = " + path + " focus_id = " + focus_id);

                    if (path) {
                      setTimeout( function() {
                        focus_id = focus_id || path.split("/").pop();
                        if (DEBUG) console.log("Auto Loading " + path);
                        var tree = $(event.target).fancytree('getTree');
                        tree.loadKeyPath(path, function (key, status) {
                          if (status === "error") {
                            if (DEBUG) console.log("error with key = " + key)
                            // Cut down the path...
                            safe_path = (path + "/").split('/' + key + '/')[0];  // "left of the match"
                            if (DEBUG) console.log("safe_path = " + safe_path);
                          }
                        }).done(
                          function () {
                            if (safe_path) {
                              focus_id = safe_path.split('/').pop();
                              if (DEBUG) console.warn("safe focus_id = " + focus_id);
                            }
                            if (DEBUG) console.log("using focus_id = " + focus_id);

                            var autoEx = tree.activateKey(String(focus_id));
                            if (autoEx) {
                              autoEx.setExpanded(true);
                            } else {
                              console.warn("Could not auto-expand " + focus_id);
                            }
                          }
                        );
                      }, 2000);
                    } else {
                        if (plugin.settings.expand_path) {
                            /* if (DEBUG) */
                            console.log("Auto-expandeing expand_path = " + plugin.settings.expand_path);
                            $(event.target).fancytree('getTree').loadKeyPath(plugin.settings.expand_path, function (x) {
                                if (typeof(x.setExpanded) === "function") {
                                    x.setExpanded(true);
                                }
                            });
                        }
                    }

                },
                glyph: {
                    map: {
                        doc: "",
                        docOpen: "",
                        error: "glyphicon glyphicon-warning-sign",
                        expanderClosed: "glyphicon glyphicon-plus-sign",
                        expanderLazy: "glyphicon glyphicon-plus-sign",
                        // expanderLazy: "glyphicon glyphicon-expand",
                        expanderOpen: "glyphicon glyphicon-minus-sign",
                        noExpander: "glyphicon glyphicon-record",
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

                create: function (evt, ctx) {
                  if (DEBUG) console.error("EVENT: create");
                },

                loadChildren: function (evt, ctx) {
                  if (DEBUG) {
                    console.error("EVENT: loadChildren");
                  }
                  ctx.node.sortChildren(null, true);

                  if (plugin.settings.selectMode === 3) {
                    // Fix the selection state of children of checked items
                    ctx.node.fixSelection3AfterClick();
                    // see http://wwwendt.de/tech/fancytree/doc/jsdoc/FancytreeNode.html#fixSelection3AfterClick
                    // and https://github.com/mar10/fancytree/issues/247

                    var sel_state = ctx.node.checkbox;
                    // console.log("sel_state = " + sel_state);
                    // console.dir(ctx.node);

                    ctx.node.visit(function (vn) {
                      // console.log("vn = " + vn + " state = " + sel_state);
                      vn.unselectable = sel_state;
                      return true;
                    }, false);
                  }
                }
            }).on('fancytreeinit', function (x, y) {
              if (DEBUG) console.error("EVENT: fancytreeinit");
            }).on('loadChildren loadError lazyLoad restore init', function (evt, ctx){
                console.dir(evt);
                console.dir(ctx);
            });


            function decorateElementWithPopover(elem, key, title, path, caption) {

                function update_counts(countsUrl, element, config) {

                    if (!element) {
                        console.error("no element:  nothing doing!  How did we get here???");
                        return;
                    }

                    var conf = {
                        countsMap: {
                            "places": "unmapped_places",
                            "subjects": "unmapped_subjects"
                        },
                        callback: function () {
                        }
                    };

                    $.extend(conf.countsMap, config);

                    if (DEBUG) {
                        console.log("update_counts: countsUrl=" + countsUrl);
                        console.log("update_counts: countsMap=" + JSON.stringify(conf.countsMap));
                    }
                    var processResult = function (data) {
                        var updates = {};
                        var groups;

                        if (data.grouped.asset_type) {
                            groups = data.grouped.asset_type.groups;
                        } else if (data.grouped.block_child_type) {
                            groups = data.grouped.block_child_type.groups;
                        } else if (data.grouped.tree) {
                            groups = data.grouped.tree.groups;
                        } else {
                            console.error("Unrecognized group! " + JSON.stringify(data.grouped));
                        }

                        // extract the group counts -- index by groupValue
                        $.each(groups, function (x, y) {
                            var category = y.groupValue;
                            var count = y.doclist.numFound;

                            // rename the category if needed
                            var mapped_category = category;
                            if (conf.countsMap[category]) {
                                mapped_category = conf.countsMap[category];
                            }
                            updates[mapped_category] = count;
                        });


                        if (element && updates) {
                            update_countsElem(element, updates);
                        } else {
                            console.error("Something was null!");
                            console.error("element = " + element);
                            console.error("updates = " + JSON.stringify(updates));
                        }

                        // callback if synchronization is needed.
                        if (conf.callback) {
                            conf.callback(element);
                        }
                    };



                    //  CACHING
                    //
                    //  TODO:
                    //  Use cache to update but also trigger update
                    //  But only allow ONE update per query at a time
                    // Use cached semaphor?
                    // Use in-memory semaphor?
                    // Use dom-attached semaphor  ala jQuery
                    // Use timestamp?










                    var hashcode = hashCode(countsUrl);
                    var raw = store.getItem(hashcode);
                    var cached = {};
                    if (raw) {
                        try {
                            cached = JSON.parse(raw);
                        } catch (e) {
                            console.error("Problem parsing cached response.  Ignoring. ")
                            console.error(e);
                        }
                    }
                    // console.log("Got from session store: " + JSON.stringify(cached, undefined, 2) + "\n raw: " + raw);

                    if (cached && cached.responseHeader) {
                        if (DEBUG) {  console.log("returning cached result for hashcode " + hashcode); }
                        processResult(cached);
                    } else {
                       if (DEBUG) { console.log(countsUrl); }
                        $.ajax({
                            type: "GET",
                            cache: true,
                            url: countsUrl,
                            dataType: "jsonp",
                            jsonp: 'json.wrf',
                            // jsonpCallback: 'Callback_' + hashcode,
                            timeout: 30000,
                            error: function (e) {
                                console.error(e);
                                // countsElem.html("<i class='glyphicon glyphicon-warning-sign' title='" + e.statusText);
                            },
                            beforeSend: function () {
                            },

                            success: function (result) {
                                processResult(result);
                                store.setItem(hashcode, JSON.stringify(result));
                            }
                        });
                    }
                }

                function update_countsElem(elem, counts) {
                    if (DEBUG) {
                        console.log("elem = " + elem.selector);
                        console.dir(elem);
                        console.error(JSON.stringify(counts,undefined,2));
                    }
                    var av = elem.find('i.shanticon-audio-video ~ span.badge');
                    if (typeof(counts["audio-video"]) != "undefined") {
                        (counts["audio-video"]) ? av.html(counts["audio-video"]).parent().show() : av.parent().hide();
                    }
                    if (Number(av.text()) > 0) {
                        av.parent().show();
                    }

                    var photos = elem.find('i.shanticon-photos ~ span.badge');
                    if (typeof(counts.picture) != "undefined") {
                        photos.html(counts.picture);
                    }
                    (Number(photos.text()) > 0) ? photos.parent().show() : photos.parent().hide();

                    var places = elem.find('i.shanticon-places ~ span.badge');
                    if (typeof(counts.related_places) != "undefined") {
                        places.html(counts.related_places);
                    }
                    if (Number(places.text()) > 0) {
                        places.parent().show();
                    }

                    var texts = elem.find('i.shanticon-texts ~ span.badge');
                    if (typeof(counts.texts) != "undefined") {
                        texts.html(counts["texts"]);
                    }
                    if (Number(texts.text()) > 0) {
                        texts.parent().show();
                    }

                    var subjects = elem.find('i.shanticon-subjects ~ span.badge');

                    if (!counts.feature_types) {
                        counts.feature_types = 0
                    }
                    ;
                    if (!counts.related_subjects) {
                        counts.related_subjects = 0
                    }
                    ;

                    var s_counts = Number(counts.related_subjects) + Number(counts.feature_types);
                    if (DEBUG) {
                        console.error("related_subjects  = " + Number(counts.related_subjects));
                        console.error("feature_types  = " + Number(counts.feature_types));
                        console.error("Calculated subject count: " + s_counts);
                    }
                    if (s_counts) {
                        subjects.html(s_counts);
                    }
                    if (Number(subjects.text()) > 0) {
                        subjects.parent().show();
                    }

                    var visuals = elem.find('i.shanticon-visuals ~ span.badge');
                    if (typeof(counts.visuals) != "undefined") {
                        visuals.html(counts.visuals);
                    }
                    if (Number(visuals.text()) > 0) {
                        visuals.parent().show();
                    }

                    var sources = elem.find('i.shanticon-sources ~ span.badge');
                    if (typeof(counts.sources) != "undefined") {
                        sources.html(counts.sources);
                    }
                    if (Number(sources.text()) > 0) {
                        sources.parent().show();
                    }

                    elem.find('.assoc-resources-loading').hide();

                }

                if (jQuery(elem).popover) {
                    jQuery(elem).attr('rel', 'popover');

                    jQuery(elem).popover({
                            html: true,
                            content: function () {
                                caption = ((caption) ? caption : "");
                                var popover = "<div class='kmap-path'>/" + path + "</div>" + "<div class='kmap-caption'>" + caption + "</div>" +
                                    "<div class='info-wrap' id='infowrap" + key + "'><div class='counts-display'>...</div></div>";
                                return popover;
                            },
                            title: function () {
                                return title + "<span class='kmapid-display'>" + key + "</span>";
                            },
                            trigger: 'hover',
                            placement: 'left',
                            delay: {hide: 5},
                            container: 'body'
                        }
                    );

                    jQuery(elem).on('shown.bs.popover', function (x) {
                        $("body > .popover").removeClass("related-resources-popover"); // target css styles on search tree popups
                        $("body > .popover").addClass("search-popover"); // target css styles on search tree popups

                        var countsElem = $("#infowrap" + key + " .counts-display");
                        countsElem.html("<span class='assoc-resources-loading'>loading...</span>\n");
                        countsElem.append("<span style='display: none' class='associated'><i class='icon shanticon-sources'></i><span class='badge' >?</span></span>");
                        countsElem.append("<span style='display: none' class='associated'><i class='icon shanticon-audio-video'></i><span class='badge' >?</span></span>");
                        countsElem.append("<span style='display: none' class='associated'><i class='icon shanticon-photos'></i><span class='badge' >?</span></span>");
                        countsElem.append("<span style='display: none' class='associated'><i class='icon shanticon-texts'></i><span class='badge' >?</span></span>");
                        countsElem.append("<span style='display: none' class='associated'><i class='icon shanticon-visuals'></i><span class='badge' >?</span></span>");
                        countsElem.append("<span style='display: none' class='associated'><i class='icon shanticon-places'></i><span class='badge' >?</span></span>");
                        countsElem.append("<span style='display: none' class='associated'><i class='icon shanticon-subjects'></i><span class='badge' >?</span></span>");

                        // highlight matching text (if/where they occur).
                        var txt = $('#searchform').val();
                        // $('.popover-caption').highlight(txt, {element: 'mark'});

                        var fq = Drupal.settings.shanti_kmaps_admin['shanti_kmaps_admin_solr_filter_query'];
                        var project_filter = (fq) ? ("&" + fq) : "";
                        var kmidxBase = Drupal.settings.shanti_kmaps_admin['shanti_kmaps_admin_server_solr'];
                        if (!kmidxBase) {
                            console.error("kmindex_root not set!");
                        }
                        var termidxBase = Drupal.settings.shanti_kmaps_admin['shanti_kmaps_admin_server_solr_terms'];
                        if (!termidxBase) {
                            console.error("termindex_root not set!");
                        }
                        // Update counts from asset index
                        var domain = (Drupal.settings.kmaps_explorer) ? Drupal.settings.kmaps_explorer.app : "places";


                        // NOTE: these count updates are done IN PARALLEL, so do not rely on them overwriting or updating in order
                        //  i.e. make sure they update non-overlapping setups of values
                        var uid = domain + '-' + key;

                        if(DEBUG) {
                            console.log("BLUPBLUPBLUP!");
                            console.error("### termindex name = " + $('<a>', {href: termidxBase})[0].pathname.split('/').reverse()[0]);
                        }

                        var termindex = $('<a>',{ href:termidxBase })[0].pathname.split('/').reverse()[0];
                        var cumulativeQuery = "{!join%20to=\"kmapid\"%20from=\"uid\"%20fromIndex=\"" + termindex + "\"}ancestor_uids_generic:" + uid;
                        var flatQuery = "kmapid:" + uid;

                        var assetCountsUrl =
                            kmidxBase + '/select?q=' + flatQuery + project_filter + '&start=0&facets=on&group=true&group.field=asset_type&group.facet=true&group.ngroups=true&group.limit=0&wt=json&json.wrf=?';
                        update_counts(assetCountsUrl, countsElem);

                        var dom_map, alt_map = {};

                        // Update related place and subjects counts from term index
                        if (domain === 'subjects') {
                            alt_map = {
                                "subjects": "related_subjects",
                                "places": "unmapped_places",
                                "related_places": "unmapped_places"
                            };
                            dom_map = {
                                "places": "related_places",
                                "subjects": "unmapped_subjects",
                                "related_subjects": "unmapped_subjects",
                                "feature_types": "unmapped_feature_types"
                            };
                        } else {
                            alt_map = {
                                "places": "related_places",
                                "subjects": "unmapped_subjects",
                                "related_subjects": "unmapped_subjects",
                                "feature_types": "unmapped_feature_types"
                            };
                            dom_map = {
                                "subjects": "related_subjects",
                                "places": "unmapped_places",
                                "related_places": "unmapped_places"
                            };
                        }

                        var flatRelatedCountsUrl =
                            termidxBase + '/select?q={!child of=block_type:parent}id:' + domain + '-' + key + project_filter + '&fq=-related_kmaps_node_type:child&wt=json&indent=true&group=true&group.field=block_child_type&group.limit=0&wt=json&json.wrf=?';
                        update_counts(flatRelatedCountsUrl, countsElem, dom_map);

                        // Update related place and subjects counts from term index
                        var cumulativeRelatedCountsUrl =
                            termidxBase + '/select?q={!child of=block_type:parent}ancestor_uids_generic:' + domain + '-' + key + project_filter + '&fq=-related_kmaps_node_type:child&wt=json&indent=true&group=true&group.field=block_child_type&group.limit=0&wt=json&json.wrf=?';
                        update_counts(cumulativeRelatedCountsUrl, countsElem, alt_map);


                        if (domain == "subjects") {
                            // this should NOT be cumulative
                            var subjectsRelatedPlacesCountQuery = termidxBase + "/select?indent=on&q={!parent%20which=block_type:parent}related_subjects_id_s:" + domain + '-' + key + "%20OR%20feature_type_id_i:" + key + "&fq=-related_kmaps_node_type:child&wt=json&json.wrf=?&group=true&group.field=tree&group.limit=0";
                            if (DEBUG) {
                                console.log(">>>>>>> subjectsRelatedPlacesCountQuery = " + subjectsRelatedPlacesCountQuery);
                            }
                            update_counts(subjectsRelatedPlacesCountQuery, countsElem, dom_map);
                        }

                    });
                }

                return elem;
            };

            function decorateElemWithDrupalAjax(theElem, theKey, theType) {
                //if (DEBUG) console.log("decorateElementWithDrupalAjax: "  + $(theElem).html());
                //$(theElem).once('nav', function () {
                //    //if (DEBUG) console.log("applying click handling to " + $(this).html());
                //    var base = $(this).attr('id') || "ajax-wax-" + theKey;
                //    var argument = $(this).attr('argument');
                //    var url = location.origin + location.pathname.substring(0, location.pathname.indexOf(theType)) + theType + '/' + theKey + '/overview/nojs';
                //
                //    var element_settings = {
                //        url: url,
                //        event: 'navigate',
                //        progress: {
                //            type: 'throbber'
                //        }
                //    };
                //
                //    // if (DEBUG) console.log("Adding to ajax to " + base);
                //
                //    Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);
                //    //this.click(function () {
                //    //    if (DEBUG) console.log("pushing state for " + url);
                //    //    window.history.pushState({tag: true}, null, url);
                //    //});
                //});
            }


        },
        yourOtherFunction: function (elem, settings) {
            // some logic
        },
        makeStringPath: function (data) {
            return $.makeArray(data.node.getParentList(false, true).map(function (x) {
                return x.title;
            })).join("/");
        },
        buildQuery: function (termIndexRoot, type, path, lvla, lvlb) {

            path = path.replace(/^\//, "").replace(/\s\//, " ");  // remove root slashes
            if (path === "") {
                path = "*";
            }

            var fieldList = [
                "header",
                "id",
                "ancestor*",
                "caption_eng",
                "level_i"
            ].join(",");

            var result =
                termIndexRoot + "/select?" +
                "df=ancestor_id_path" +
                "&q=" + path +
                "&wt=json" +
                "&indent=true" +
                "&limit=" + SOLR_ROW_LIMIT +
                "&facet=true" +
                "&fl=" + fieldList +
                "&indent=true" +

                "&fq=tree:" + type +
                "&fq=level_i:[" + lvla + "+TO+" + (lvlb + 1) + "]" +
                "&fq={!tag=hoot}level_i:[" + lvla + "+TO+" + lvlb + "]" +

                "&facet.mincount=2" +
                "&facet.limit=-1" +
                "&sort=level_i+ASC" +
                "&facet.sort=ancestor_id_path" +
                "&facet.field={!ex=hoot}ancestor_id_path" +

                "&wt=json" +
                "&json.wrf=?" +

                "&rows=" + SOLR_ROW_LIMIT;

            if (DEBUG) {
                console.log("buildQuery():SOLR QUERY=" + result)
            }

            return result;
        },
        showPaths: function (paths, callback) {

            //console.log("ARGY!");
            //console.dir(arguments);
            var plugin = this;

            var cleanPath = function (path, parentOnly, rootSlash) {
                log("cleanPath() args: " + JSON.stringify(arguments, undefined, 2));
                log("cleanPath() in: " + path);
                // Eliminate initial/terminal slash
                path = path.replace(/^\/+/, '');
                path = path.replace(/\/$/, '');
                var p = path.split('/');
                if (parentOnly) {
                    p.splice(-1, 1)
                }
                path = rootSlash ? "/" : "";
                path += p.join('/');
                var msg = "cleanPath() out: " + path;
                log(msg);
                return path;
            };

            ////  Cleanup and re-root the paths
            var fixPath = function (path, i) {
                path = cleanPath(path);

                var rootpath = cleanPath(plugin.settings.root_kmap_path, true, false);
                log("fixPath(): rootpath = " + rootpath);
                log("fixPath(): path = " + path);

                // truncate the beginning of the path according to kmap_root_path
                path = path.replace(rootpath, "");
                log("fixPath(): fixed path = " + path);

                // truncate the beginning of the path according to kmap_root_path
                var clean = cleanPath(path, false, true);
                log("fixPath(): fixed clean = " + clean);

                return clean;
            };


            // ensure it is an array
            if (!$.isArray(paths)) {
                // wrap a single bare path into a single-value array.
                paths = [paths];
            }

            if (DEBUG) log("paths " + paths);

            // cleanup the paths
            paths = $.map(paths, fixPath);
            paths = $.grep(paths, function (x) {
                return (x !== "/")
            })

            if (DEBUG) {
                console.dir(paths);
            }

            var pathlist = [];
            for (var i = 0; i < paths.length; i++) {
                if (DEBUG) log("======> processing path:" + paths[i]);
                if (paths[i].length > 0 && this.element.fancytree('getTree').getNodeByKey(paths[i].substring(paths[i].lastIndexOf('/') + 1)) == null) {
                    pathlist.push(paths[i]);
                }
            }
            // if (DEBUG)
            //     log("loadKeyPath " + pathlist);

            if (paths !== null) {
                if (pathlist.length == 0) { // all paths to show have already been loaded
                    var ret = this.element.fancytree('getTree').filterNodes(function (x) {
                            if (DEBUG) log("     filt:" + x.getKeyPath());
                            return $.inArray(x.getKeyPath(), paths) !== -1;
                            // unfortunately filterNodes does not implement a cal
                            // Terminal callback");
                            if (DEBUG) console.dir(node);
                            if (DEBUG) console.dir(state);

                            if (node === null) {
                                console.error("HEY NODE IS NULL");
                                console.error("paths = " + JSON.stringify(pathlist));
                            }

                            if (state === "ok") {
                                log("state = OK");
                                if (node != null) {
                                    if (DEBUG) log("ok " + node);
                                    var ret = node.tree.filterNodes(function (x) {
                                        if (DEBUG) log("     filt:" + x.getKeyPath());
                                        return $.inArray(x.getKeyPath(), paths) !== -1;
                                        // unfortunately filterNodes does not implement a callback for when it is done AFAICT
                                    }, {autoExpand: true});
                                    if (DEBUG) log("filterNodes returned: " + ret);
                                }
                            } else if (state == "loading") {
                                if (DEBUG) log("loading " + node);
                            } else if (state == "loaded") {
                                if (DEBUG) log("loaded" + node);
                            } else if (state == "error") {
                                console.log("ERROR: state was " + state + " for " + node);
                            }

                        }
                    ).always(
                        // The logic here is not DRY, so will need to refactor.
                        function () {
                            if (callback) {
                                if (DEBUG) {
                                    log("Calling back! ");
                                    console.dir(arguments);
                                }
                                callback();
                            }
                        }
                    );
                }
            } else {
                if (callback) callback();
            }
        },
        loadKeyPath: function (tree, keyPathList, callback, _rootNode) {
            var deferredList, dfd, i, path, key, loadMap, node, root, segList,
                sep = tree.options.keyPathSeparator,
                self = tree;

            if (!$.isArray(keyPathList)) {
                keyPathList = [keyPathList];
            }
            // Pass 1: handle all path segments for nodes that are already loaded
            // Collect distinct top-most lazy nodes in a map
            loadMap = {};

            for (i = 0; i < keyPathList.length; i++) {
                root = _rootNode || self.rootNode;
                path = keyPathList[i];
                // strip leading slash
                if (path.charAt(0) === sep) {
                    path = path.substr(1);
                }
                // traverse and strip keys, until we hit a lazy, unloaded node
                segList = path.split(sep);
                while (segList.length) {
                    key = segList.shift();
//                node = _findDirectChild(root, key);
                    node = root._findDirectChild(key);
                    if (!node) {
                        self.info("loadKeyPath: key not found: " + key + " (parent: " + root + ", path: " + path + ")");
                        callback.call(self, key, "error");
                        break;
                    } else if (segList.length === 0) {
                        callback.call(self, node, "ok");
                        break;
                    } else if (!node.lazy || (node.hasChildren() !== undefined )) {
                        callback.call(self, node, "loaded");
                        root = node;
                    } else {
                        callback.call(self, node, "loaded");
//                    segList.unshift(key);
                        if (loadMap[key]) {
                            loadMap[key].push(segList.join(sep));
                        } else {
                            loadMap[key] = [segList.join(sep)];
                        }
                        break;
                    }
                }
            }
//        alert("loadKeyPath: loadMap=" + JSON.stringify(loadMap));
            // Now load all lazy nodes and continue itearation for remaining paths
            deferredList = [];
            // Avoid jshint warning 'Don't make functions within a loop.':
            function __lazyload(key, node, dfd) {
                callback.call(self, node, "loading");
                node.load().done(function () {
                    self.loadKeyPath.call(self, loadMap[key], callback, node).always(_makeResolveFunc(dfd, self));
                }).fail(function (errMsg) {
                    self.warn("loadKeyPath: error loading: " + key + " (parent: " + root + ")");
                    callback.call(self, node, "error");
                    dfd.reject();
                });
            }

            for (key in loadMap) {
                node = root._findDirectChild(key);
                if (node == null) {
                    node = self.getNodeByKey(key);
                }
//            alert("loadKeyPath: lazy node(" + key + ") = " + node);
                dfd = new $.Deferred();
                deferredList.push(dfd);
                __lazyload(key, node, dfd);
            }
            // Return a promise that is resovled, when ALL paths were loaded
            return $.when.apply($, deferredList).promise();
        },
        getNodeByKey: function (key, root) {
            return this.element.fancytree("getTree").getNodeByKey(key, root);
        },
        hideAll: function (cb) {
            var ftree = this.element.fancytree("getTree");
            ftree.filter(function (x) {
                return false;
            });
            cb(ftree);
        },
        reset: function (cb) {
            this.element.fancytree("getTree").clearFilter();
            if (cb) {
                cb();
            }
        },
        // Utility Functions
        sendEvent: function (handler, event, data) {
            function encapsulate(eventtype, event, n) {
                if (!n) {
                    console.error("Node data missing...");
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

            // log("HANDLER:  " + handler);
            if (data.node == null) {
                return;
            }
            var kmapid = this.settings.type + "-" + data.node.key;
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
                console.log("DESELECT: " + JSON.stringify(data.node.title))
              }

            } else {
                log("UNHANDLED EVENT: " + event);
                console.dir(event);
            }
        }

    });


    // See https://github.com/jquery-boilerplate/jquery-boilerplate/wiki/Extending-jQuery-Boilerplate
    $.fn[pluginName] = function (options) {
        var args = arguments;

        if (options === undefined || typeof options === 'object') {
            return this.each(function () {
                if (!$.data(this, 'plugin_' + pluginName)) {
                    $.data(this, 'plugin_' + pluginName, new KmapsTreePlugin(this, options));
                }
            });
        } else if (typeof options === 'string' && options[0] !== '_' && options !== 'init') {
            var returns;

            this.each(function () {
                var instance = $.data(this, 'plugin_' + pluginName);
                if (instance instanceof KmapsTreePlugin && typeof instance[options] === 'function') {
                    returns = instance[options].apply(instance, Array.prototype.slice.call(args, 1));
                }
                if (options === 'destroy') {
                    $.data(this, 'plugin_' + pluginName, null);
                }
            });
            return returns !== undefined ? returns : this;
        }
    };


})(jQuery, window, document);
