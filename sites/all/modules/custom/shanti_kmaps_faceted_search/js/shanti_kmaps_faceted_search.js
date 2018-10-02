(function ($) {

  'use strict';
  var DEBUG = false; // To turn on console log DEBUGging
  var ASSET_VIEWER_PATH = "/places/0/";
  var ASSET_TYPE_LIST = ["all", "places", "subjects", "audio-video", "images", "sources", "texts", "visuals"];
  var storage = window.localStorage; // probably should polyfill

    // Drupal Behavior Functions
    /**
     * Script for loading the trees upon page load.
     *      Each tree is in div.kmapfacetedtree
     *      Calls $.kmapsTree() function (from shanti_kmaps_tree library) for each such div with special settings.
     *      Uses special functions below:
     *              - getKmapFacetCounts() : whenever a treenode is expanded, adds counts to new treenodes (Really readds to all treenodes)
     *              - loadMyFacetHitCounts() : when a treenode is collapsed, because it is displayed without the count by the innate collapse function
     *              - loadKmapFacetHits(): when a treenode is activated (clicked on), load teasers for all such tagged Drupal nodes
     *              - updateKmapFacetCounts: an jQuery extended function called by Drupal Ajax array
     */
    Drupal.behaviors.shanti_kmaps_faceted_search_tree_loading = {
      attach: function (context, settings) {
        var admin = settings.shanti_kmaps_admin;
        var kmfset = settings.shanti_kmaps_faceted_search;

        // console.log("shanti_kmaps_faceted_search_tree_loading...");
        // console.dir(kmfset);
        // console.dir(context);

        if (context === document) {
          // Process each tree
          $('.kmapfacetedtree').each(function () {
            // Create the Settings values
            var id = $(this).attr("id");
            var $tree = $('#' + id);
            var domain = $.trim($tree.data('kmtype'));
            if (DEBUG) {
              console.log('loading: ' + id, domain, $tree);
            }
            var rootid = $.trim($tree.data('kmroot'));
            var root_kmap_path = (domain === 'subjects') ? admin.shanti_kmaps_admin_root_subjects_path : admin.shanti_kmaps_admin_root_places_path;
            var base_url = (domain === 'subjects') ? admin.shanti_kmaps_admin_server_subjects : admin.shanti_kmaps_admin_server_places;

            var cboxes = true;
            // if (Drupal.settings.kmaps_explorer && Drupal.settings.kmaps_explorer.app ){
            //   cboxes = true;
            // }

            var tree_settings = {
              termindex_root: admin.shanti_kmaps_admin_server_solr_terms, // calls proxyIt() function below
              kmindex_root: admin.shanti_kmaps_admin_server_solr,
              type: domain,
              baseUrl: base_url,
              generateIds: false,
              checkboxes: cboxes,
              selectMode: 3
            };
            if (rootid && (rootid !== "" || rootid !== "all")) {
              tree_settings.root_kmap_path = rootid;
            }

            // Initialize the tree



            var collapseUpdate = loadMyFacetHitCount;
            var selectFacet = loadKmapFacetHits;
            var navigate = navigateToKmap;

            // alert(" DOMAIN: " + domain);

            if (domain === "facets") {
              var markup = "<h2>Facets unconfigured.</h2>";
              $tree.html(markup);
            } else if (domain === "results") {
              var results = "<h2>Results area.</h2>";
              $tree.html(results);
            } else {
              var $clickFunction = function() {
                console.warn ("Nothing is specified for clickFunction!");
              };
              var $clickAction = $tree.data('kmclick');
              var $deselectFacet = function(evt,data) {
                var $kid = data.node.tree.data.kmtype + "-" + data.node.key;
                // doRemoveFacet("#facet-item-delete-" + $kid, $kid);
                doRemoveFacet($kid);
              };

              if ($clickAction === 'navigate') {
                $clickFunction = navigate;
              } else if ($clickAction === 'add_facet') {
                $clickFunction = selectFacet;
              } else {
                console.log ("NOT SURE WHAT TO DO! kmclick is unrecognized: " + $clickAction);
              }

              var tree = $tree.kmapsTree(tree_settings)
                .on('fancytreeexpand', getKmapFacetCounts)
                .on('fancytreecollapse', collapseUpdate)
                .on('fancytreeactivate', $clickFunction)
                .on('select', selectFacet)
                .on('deselect', $deselectFacet);
              // .css("height", "auto");

              // Expand first level of the tree
              setTimeout(function () {
                var roots = $(tree).fancytree('getTree').getRootNode().getChildren();
                if (roots && roots.length === 1) {
                  console.log("auto expanding single root node");
                  roots[0].setExpanded(true);
                }
              }, 1000);
            }
          });

          // Set "live" action for kmaps facet item delete clicks (enabling the delete icon on all facet tags in future)
          $(document).on('click', '.kmfaceted-item-delete', function (evt,target) {
            // var cid = '#' + $(this).attr('id');
            // var cid = $(this).data('kmid');
            // doRemoveFacet(cid, $(this).parent().data('kmid'));
            doRemoveFacet($(this).parent().data('kmid'));
            evt.stopPropagation();
          });


          // THIS MIGHT BE UNUSED
          // Load Facets from URL
          if (kmfset && kmfset.loadFacetsFromURL) {
            var tags = $.parseJSON(kmfset.loadFacetsFromURL);
            for (n in tags) {
              console.log("kmfset: " + n);
              var tag = tags[n];
              AddFacetTagToList(tag.title, tag.kmid);
            }
          }
          // Repopulate Search box if loaded from URL
          repopulateSearchBoxFromSettings();

          $('.kmap-filter-box').append('<button type="reset" class="btn kmfaceted-list-clear"><span class="icon"></span></button>');
          $('.kmfaceted-list-clear').click(function () {
            closeSearchResults();
            Drupal.settings.kmapsSolr.clearFacets().then(
              function () {
                $('.active-kmfaceted-list').hide();
                $('.active-kmfaceted-list .facet-item').remove();

                // Clear all trees
                $('.kmapfacetedtree').each( function(i, x) {
                  var n = $(x).fancytree("getTree").getSelectedNodes();
                  $(n).each(function(i, y) {
                    // console.log("deselecting: " + y);
                    y.setSelected(false);
                  });

                });
              });
          });

          //Functionality for history popstate
          $(window).on('popstate', function (e) {
            if (!e.originalEvent.state || !e.originalEvent.state.tag) return;
            window.location.href = location.href;
          });
        }
      }
    };

    /**
     * Add Pager events for facet results pages
     */
    Drupal.behaviors.shanti_kmaps_faceted_search_pager_events = {
        attach: function (context, settings) {
            // TODO: Generalize! (This only works for pagerer)
            $('.kmaps-facets-results table.pagerer ul.pager input.pagerer-page').unbind('keydown').on('keydown', function (e) {
                if (e.keyCode === 13) {
                    e.preventDefault();
                    e.stopImmediatePropagation();
                    var jstr = $(this).attr('name');
                    var json = $.parseJSON(jstr);
                    var pgnum = $(this).val() - 1;
                    var path = Drupal.settings.basePath + json.path.replace('/nojs', '/ajax').replace('pagererpage', pgnum);
                    $(this).after('<div class="ajax-progress ajax-progress-throbber" style="display:inline-block;"><div class="throbber">&nbsp;</div></div>');
                    $(this).after('<div class="link" style="display: none;"><a id="mykmflink" href="' + path + '" class="use-ajax">go</a></div>');
                    Drupal.attachBehaviors('a#mykmflink');
                    $('a#mykmflink').click(function () {
                        setTimout(function () {
                            $('a#mykmflink').remove();
                        }, 1000);
                    });
                }
            });
        }
    };

    /**
     * Attach Events that happen to the tree and search box
     */
    Drupal.behaviors.shanti_kmaps_faceted_search_tree_events = {
        attach: function (context, settings) {
            if (context === document) {
                // When BS Tab is activated
                $('.km-facet-tab').on('show.bs.tab', function (e) {
                    var div = $(this).children('a').eq(0).attr('href') + " .kmapfacetedtree"; // find the tree div


                    //  TODO: ys2n: CRAPPY HACK!  PROBABLY WILL CAUSE PROBLEMS
                    if ($(div).data('kmtype') !== "facets") {
                        var tree = $(div).fancytree('getTree');   // get the fancytree
                        Drupal.settings.shanti_kmaps_faceted_search.activeTree = tree;
                    } else {
                        Drupal.settings.kmaps_explorer = {'app': $(div).data('kmtype')};
                    }
                });
                if (typeof(Drupal.settings.shanti_kmaps_faceted_search.activeTree) === "undefined" && $('.km-facet-div.active .kmapfacetedtree').fancytree == "function") {
                    Drupal.settings.shanti_kmaps_faceted_search.activeTree = $('.km-facet-div.active .kmapfacetedtree').fancytree('getTree');
                }
            }
        }
    };

  /**
   *
   * @type {{attach: Drupal.behaviors.shanti_kmaps_faceted_search_solr.attach}}
   */
  Drupal.behaviors.shanti_kmaps_faceted_search_solr = {
    attach: function (context, settings) {
      $("#search-flyout").once('shanti_kmaps_faceted_search_solr_attach',  function() {

        var select_searchForm = '#search-block-form'; // selector for the search form
        var select_searchInput = '#edit-search-block-form--2'; // selector for the search input
        var DEBUG = false;
            // ndg: the code below only works on individual subject or place pages
            // if ($("body").is('.page-subjects-*, .page-places-*')) {
            if (DEBUG) console.log("ATTACHING shanti_kmaps_faceted_search_solr BEHAVIORS");

            // TODO: ys2n: should handle missing templates
            // compile handlebars templates

        var search_main_template = undefined;
        var search_results_popover_template = undefined;

        // The templates in shanti_kmaps_solr/templates will be added to the DOM according to the filename

        if ($("#search-results-main").html()) {
          search_main_template = Handlebars.compile($("#search-results-main").html());
          search_results_popover_template = Handlebars.compile($("#search-results-details-popover").html());
          Handlebars.registerPartial('item-template', $('#search-results-item').html());
          Handlebars.registerPartial('search-results-details-media', $('#search-results-details-media').html());
          Handlebars.registerPartial('search-results-details-kmaps', $('#search-results-details-kmaps').html());
          Handlebars.registerPartial('search-results-gallery-audio-video', $('#search-results-gallery-audio-video').html());
          Handlebars.registerPartial('search-results-gallery-default', $('#search-results-gallery-default').html());
          Handlebars.registerPartial('search-results-gallery-visuals', $('#search-results-gallery-visuals').html());
          Handlebars.registerPartial('search-results-gallery-images', $('#search-results-gallery-images').html());
        } else {
          console.error("Handlebars templates are missing!");
        }

        // map the asset type to a template name
        Handlebars.registerHelper('choosetemplate', function(asset_type) {
          var DEFAULT_TEMPLATE = "search-results-details-media";
          var KMAPS_TEMPLATE = "search-results-details-kmaps";
          if (DEBUG) console.log("chooseTemplate: asset_type = " + asset_type);
          if (asset_type === "subjects" || asset_type === "places" || asset_type === "terms") {
            return KMAPS_TEMPLATE;
          } else {
            return DEFAULT_TEMPLATE;
          }
        });

        Handlebars.registerHelper('choosegallery', function(view_type) {
          var DEFAULT_TEMPLATE = "search-results-gallery-default";
          if (true) console.log("chooseGallery: view_type = " + view_type);

          // see if a template with this name exists
          var mapped_template = $('#search-results-gallery-' + view_type);

          var template = DEFAULT_TEMPLATE;
          if(mapped_template[0]) {
            template = "search-results-gallery-" + view_type;
          }
          console.log("Returning template " + template);
          return template;
        });

            Handlebars.registerHelper('json', function (obj) {
              return JSON.stringify(obj, undefined, 3);
            });

            Handlebars.registerHelper('flatlist', function (obj) {
              if ($.isArray(obj)) {
                return obj.join(", ");
              } else {
                return obj;
              }
            });

            Handlebars.registerHelper('safe', function(x) {
              return new Handlebars.SafeString(x);
            })

            $('#btn-collapse-flyout').css('display','none');

            // TODO: ys2n: read solr specifications and set them here!!!
            //  Right now it will just use internal defaults (using predev).

            // postpone this until loaded?

            $(function () {

              var $solrBase = '';
              var $solrPath = '';
              var $assetIndex = '';
              var $termIndex = '';

              // extract the parts from Shanti Kmaps Admin setttings

              $('#faceted-search-results').once('open-handler', function () {

                // TODO: ys2n: candidate for removal.  not sure this is necessary
                $('#facetpicker a').on('click', function () {
                  console.log("opening flyout on click or submit in #facetpicker anchor");
                  Drupal.attachBehaviors('#faceted-search-results');
                  // openSearchResults();
                  // showResultsTab();
                });

                $('.fancytree-title').on('click', function() {
                  console.log("closing flyout on click fancytree-title");
                  closeSearchResults();
                });

                // Results-details openers
                // TODO: ys2n: review this...  not necessary?
                $('#faceted-search-results').on('click', '.results-details-open', function (evt) {
                  $(this).toggleClass('open-task');
                  // $('#mandala-veil-bg').css('z-index','290');
                  var app = $(this).data('app');
                  var kid = $(this).data('id');
                  $('.place-open-' + kid).toggle('fast');
                  console.log("open: " + app + "-" + kid);
                  populateAssetCounts($('.place-open-' + kid + " .results-kmaps-resource-list"), kid, app);
                });


                // wire up the search result closers
                $('#faceted-search-results').on('click', '#btn-collapse-search-results', function() {
                  closeSearchResults();
                  showResultsTab();
                  $('#mandala-veil-bg').css({'z-index' : '-1','opacity' : '0'});
                });

                // wire up extruder event listeners
                $('#faceted-search-results').on('extopen extclose', function(evt) {
                  // console.log("extruder event: " + evt.type);
                  Drupal.attachBehaviors('#faceted-search-results');
                });


                // attach listener to the mbExtruder "flap" or search flyout tab and then
                // apply logic to decide whether to open the #faceted-search-results flyout
                $('.on-flap').click( function() {
                  if ($('#search-flyout').hasClass('isOpened')) {
                    // console.log("opening...");
                    if ($('#faceted-search-results').hasClass('filters-applied')) {
                      // console.log("opening flyout on click .on-flap when filters-applied");
                      // openSearchResults();
                      showResultsTab();
                    }
                  } else {
                    // console.log("closing...");
                    // console.log("closing flyout on click .on-flap");
                    closeSearchResults();
                  }
                  return true;
                });

                // setup results tab
                var $results_tab = $('<span id="btn-show-search-results" class="btn-show-search-results" style="display:none;" type="button" aria-label="Open Search Results"><span><span class="icon shanticon-preview"></span><span id="results-count-badge" class="badge results-count-badge"></span></span></span>');

                $('.ext_wrapper').append($results_tab);
                $('#btn-show-search-results').click( function() {
                  console.log("opening search results on click #btn-show-search-results");
                  openSearchResults();
                  $('#mandala-veil-bg').css({'z-index' : '290','opacity' : '85'});
                  // Added by ndg8f 2017-07-06 to rebuild gallery when opening after going to a result
                  if ($('#faceted-search-results').hasClass('filters-applied') && !$('#search-results-gallery').hasClass('rejustified')) {
                    setTimeout(function() {
                      $('#search-results-gallery').justifiedGallery('destroy').justifiedGallery({
                        rowHeight: 110,
                        lastRow: 'nojustify',
                        margins: 3,
                      }).addClass('rejustified');
                    }, 100);
                  }
                });
              });

              var a = $('<a>', { href: Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_server_solr_terms });
              $solrBase = a.prop('hostname');
              var $fullPath = a.prop('pathname').split('/');
              $termIndex = $fullPath.pop();
              $solrPath = $fullPath.join("/") + "/";


              // Do it again for assets.   ASSUME THAT THE SERVER IS THE SAME!

              var b = $('<a>', { href: Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_server_solr });
              // $solrBase = b.prop('hostname');
              var $fullPath2 = b.prop('pathname').split('/');
              $assetIndex = $fullPath2.pop();
              // $solrPath = $fullPath.join("/") + "/";

              console.log(JSON.stringify({ 'solrBase': $solrBase,
                'solrPath': $solrPath,
                'assetIndex': $assetIndex,
                'termIndex': $termIndex
              }, undefined, 2));

                if ($.kmapsSolr) {

                  // analyze query string for encoded filterState
                  if (DEBUG) {
                    console.log("WINDOW LOCATION");
                    console.dir(window.location);
                  }

                  var defaultFilterState = null;
                  try {
                    if ($.cookie('defaultFilterState')) {
                      console.log("restoring defaultFilterState... " + JSON.stringify($.cookie('defaultFilterState')));
                      defaultFilterState = JSON.parse($.cookie('defaultFilterState'));
                    }
                  } catch (err) {
                    console.log("Error deserializing defaultFilterState: " + err);
                  }

                  var f = $(document).getUrlParam("f");
                  if (f) {
                    var json = LZString.decompressFromEncodedURIComponent(f);
                    defaultFilterState = JSON.parse(json);
                  }
                  if (DEBUG) { console.error("INITIAL FILTERS = " + JSON.stringify(defaultFilterState)); }
                  var path = document.location.pathname; // path without hash or queryString
                  var hash = document.location.hash;
                  if (hash) {
                    path += hash;
                  }
                  history.pushState({}, null, path);  // TODO: ys2n: are these appropriate arguments?
                  var kmapFilters = [];
                  var assetFilters = [];
                  var root_id_list = [];
                  if (Drupal.settings.shanti_kmaps_admin) {
                    if (Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_solr_filter_query_kmaps_enabled &&
                      Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_solr_filter_query_kmaps) {
                      kmapFilters.push(Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_solr_filter_query_kmaps);
                    }

                    if (Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_root_places_filter_enabled) {
                      console.log("places root: " + Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_root_places_id);
                      var plist = Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_root_places_id.split('\s+');
                      var p = $.map(plist, function (value) {

                        if (!value) {
                          value="*";
                        }

                        return "places-"+ value;
                      })
                      if (p.length !== 0) {
                        for (var i = 0; i < p.length; i++) {
                          root_id_list.push(p[i]);
                        }
                      } else {
                        root_id_list.push("places-*");
                      }
                    }

                    if (Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_root_subjects_filter_enabled) {

                      console.log("subjects root: " + Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_root_subjects_id);
                      var slist = Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_root_subjects_id.split('\s+');
                      console.log ("slist: "  + JSON.stringify(slist));

                      var s = $.map(slist, function (value) {
                        if (!value) {
                          value="*";
                        }
                        return "subjects-"+ value;
                      });

                      if (s.length !== 0) {
                        for (var j = 0; j < s.length; j++) {
                          root_id_list.push(s[j]);
                        }
                      } else {
                        root_id_list.push("subjects-*");
                      }
                    }

                    if (root_id_list.length) {
                      console.log("root_id_list = " + JSON.stringify(root_id_list));
                      kmapFilters.push(
                        "ancestor_uids_generic: (" + root_id_list.join(' ') + ")"
                      );

                      assetFilters.push(
                        "kmapid: (" + root_id_list.join(' ') + ")"
                      );
                    }


                    if (Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_solr_filter_query_assets_enabled &&
                      Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_solr_filter_query_assets) {
                      assetFilters.push(Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_solr_filter_query_assets);
                    }



                  }
                  // if (Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_solr_filter_query_kmaps_enabled ||
                  //   Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_solr_filter_query_assets_enabled) {
                    console.log("Solr Filtering Enabled: ");
                    console.dir({
                        admin_settings: Drupal.settings.shanti_kmaps_admin,
                        kmapFilters: kmapFilters,
                        assetFilters: assetFilters
                      },
                      undefined,
                      2);
                  // }

                  settings.kmapsSolr = $.kmapsSolr(
                    {
                      'pageSize': 100,
                      'solrBase': $solrBase,
                      'solrPath': $solrPath,
                      'assetIndex': $assetIndex,
                      'termIndex': $termIndex,
                      'kmapFilterQuery': kmapFilters,
                      'assetFilterQuery': assetFilters,
                      // update handler is called whenever a search is completed
                      updateHandler: function (blob) {
                        function resetExpand($this, expand) {
                          var $block = $this.closest('.shanti-kmaps-solr-facet-block');

                          // toggle the icon
                          var $toggle = $block.find('.facet-title-toggle.glyphicon');
                          if (expand) {
                            $block.addClass('facets-showing-all');
                            $toggle
                              .removeClass('glyphicon-plus-sign')
                              .addClass('glyphicon-minus-sign');
                          } else {
                            $block.removeClass('facets-showing-all');
                            $toggle
                              .removeClass('glyphicon-minus-sign')
                              .addClass('glyphicon-plus-sign');
                          }

                          // clear quicksearch
                          $block.removeClass('quickfiltered');
                          $block.find('.facet-quicksearch').val("");
                          $block.find('.facet-quicksearch-shown-count')
                            .text($block.find('.shanti-kmaps-solr-facet-title').data("bucketCount"));
                          $block.find('.facet-quicksearch-count').fadeOut();

                          var $slice = $block
                            .find('.shanti-kmaps-solr-facet-list')
                            .show()
                            .slice(numShown)
                            .unhighlight();

                          if (expand) {
                            $slice.slideDown('fast');
                          } else {
                            $slice.slideUp('fast');
                          }
                          return $slice;
                        }

                        function expandFacets($this) {
                          resetExpand($this, true);
                        }

                        function contractFacets($this) {
                          resetExpand($this, false);
                        }

                        // console.log("RESULTS: " + JSON.stringify(blob.results, undefined, 2));
                        // TODO: ys2n: These should be confgurable (or derivable).
                        var $flist = $("#facetpicker");
                        var numShown = 5; // TODO: ys2n: configure numShown...
                        var template = Handlebars.compile($('#shantiKmapsSolrFacetList').html());

                        // use the filters to mark the chosen facets
                        if (DEBUG) console.dir( {
                          'filters': blob.filters,
                          'facets' : blob.facets
                        });

                        $flist.html(template({
                          facets: blob.facets,
                          numShown: numShown
                        }));

                        // hide facet list items beyond numShown
                        $('.shanti-kmaps-solr-facet-block').each(function (_, item) {
                          $(item).find('.shanti-kmaps-solr-facet-list')
                            .show()
                            .slice(numShown)
                            .hide();
                        });

                        // attach quicksearch handlers
                        $('.shanti-kmaps-solr-facet-block').on('keyup change','.facet-quicksearch',function(e) {
                          var $fcts = $(this).parent().siblings('.shanti-kmaps-solr-facet-list');
                          var $search = $(this).val().toLowerCase();
                          var $block = $(this).closest('.shanti-kmaps-solr-facet-block');
                          if($search === ""){
                            contractFacets($(this));
                            $fcts.unhighlight();
                            $block.removeClass('quickfiltered');
                            $fcts.parent().find('.facet-quicksearch-shown-count').text($fcts.parent().find('.shanti-kmaps-solr-facet-title').data("bucketCount"));
                            // console.log($fcts.parent().find('.shanti-kmaps-solr-facet-title').data("bucketCount"));
                            $block.find('.facet-quicksearch-count').fadeOut();
                          } else {
                            $block.addClass('quickfiltered');
                            $fcts.each(function() {
                              var text = $(this).text().toLowerCase().replace(/\(\d+\)/,"");
                              if (text.indexOf($search) >= 0) {
                                $(this).unhighlight();
                                $(this).show().highlight($search);
                              } else {
                                $(this).hide();
                                $(this).unhighlight();
                              }
                            });
                            $fcts.parent().find('.facet-quicksearch-shown-count').text(($($fcts).parent().find('dd.shanti-kmaps-solr-facet-list:visible').length));
                            $block.find('.facet-quicksearch-count').fadeIn();
                          }
                        });

                        $('.facet-quicksearch-reset').on('click', function() {
                          $(this).parent().find('input').val("");
                          contractFacets($(this));
                        });

                        // attach listeners to slide-expand-show truncated list on click
                        $('.shanti-kmaps-solr-facet-title').each(function (_, item) {
                          var veil_threshold = numShown;
                          var $block = $($(item).closest('.shanti-kmaps-solr-facet-block'));
                          if (
                            $block
                              .find('.shanti-kmaps-solr-facet-list')
                              .size() < veil_threshold) {
                            $block.addClass("facets-short-list");
                          } else {
                            $block.removeClass("facets-short-list");
                          }

                          $(item).on('click', function () {
                            var $this = $(this);
                            var $glyph = $this.find('.facet-title-toggle.glyphicon');

                            if ($glyph.hasClass('glyphicon-plus-sign')) {
                              expandFacets($this);
                            } else {
                              contractFacets($this);
                            }
                          });


                        });

                        // attach listeners to add the facets to the facet list when selected.
                        $('.shanti-kmaps-solr-facet-item').each(function (_, item) {
                          $(item).on('click', function () {
                            var $this = $(this);
                            var facetType = $this.attr('data-facet-type');
                            var facetLabel = $this.attr('data-facet-label');
                            var facetId = $this.attr('data-facet-id');
                            addFacetTagToList(facetType + ': ' + facetLabel, facetId);
                            settings.kmapsSolr.selectFacet(facetId);
                          });
                        });

                        // search string handling
                        var searchString;
                        if (Drupal.settings.kmapsSolr &&
                          Drupal.settings.kmapsSolr.getState().filters &&
                          Drupal.settings.kmapsSolr.getState().filters.searchString) {
                          searchString = Drupal.settings.kmapsSolr.getState().filters.searchString.replace('name_autocomplete:', '');
                        }

                        var total_count = 0;
                        for (var n in blob.asset_counts) {
                          if (blob.asset_counts.hasOwnProperty(n) && n !== "all") {
                            total_count += blob.asset_counts[n];
                          }
                        }
                        if (blob.asset_counts) {
                          blob.asset_counts['all'] = total_count;
                        }
                        if (DEBUG) console.log("ASSET COUNTS");
                        if (DEBUG) console.dir(blob.asset_counts);

                        var decorated_counts = {};
                        if (blob.asset_counts) {
                          for(var f in ASSET_TYPE_LIST) {
                            var field = ASSET_TYPE_LIST[f];
                            var value = blob.asset_counts[field];

                            if (DEBUG) console.log("field = " + field + " count = " + value);

                            var assetTypes = [];

                            if(DEBUG) console.error("assetType List: " + JSON.stringify(Drupal.settings.kmapsSolr.getState().assetTypeList, undefined, 2));

                            if (Drupal.settings.kmapsSolr.getState().assetTypeList) {
                              assetTypes = Drupal.settings.kmapsSolr.getState().assetTypeList;
                              if (assetTypes.length === 0 || assetTypes[0] === 'all') {
                                assetTypes = ['all'];
                              }
                            }
                            var selected = ($.inArray(field, assetTypes) > -1) ? "selected" : "";
                            var label = (field === "audio-video")?"A/V":field;
                            // TODO: ys2n: refactor to abstract this logic
                            var hide = (value === 0 && selected !== "selected");
                            var icon = (field === 'all')?"shanticon-logo-shanti":"shanticon-" + field;

                            // ROUNDING:  if the count is over a threshhold, round the number to the nearest 1K
                            var rounding_threshhold = 1000;
                            var count = value;
                            if (count > rounding_threshhold) {
                              count = Math.round(count/1000) + "K";
                            }

                            var obj = {field: field, count: count, icon: icon, label: label, selected: selected, hide: hide};
                            decorated_counts[field] = obj;
                          };
                        }

                        if (DEBUG) {
                          console.log("DECORATED COUNTS:");
                          console.log(JSON.stringify(decorated_counts, undefined,2));
                        }


                        //

                        var filterJson = JSON.stringify(blob.filters);
                        var encodedFilters = LZString.compressToEncodedURIComponent(filterJson);

                        if (DEBUG) {
                          console.log("filterJson = " + filterJson);
                          console.log("encodedFilters = " + encodedFilters);
                        }

                        // groom asset_results
                        if (blob.asset_results && blob.asset_results.docs) {
                          $.each(blob.asset_results.docs, function() {
                            // DISPLAY LABEL LOGIC
                            var display_label = "Bloomers!";
                            if (this.header) {
                              display_label = this.header;
                            } else if (this.caption) {
                              display_label = this.caption
                            } else if(this.title[0]) {
                              display_label = this.title[0];
                            } else if (this.names_txt[0]) {
                              display_label = this.names_txt[0];
                            } else if (this.names_txt[1]) {
                              display_label = this.names_txt[1];
                            }

                            // if its a subject or a place, append the kmapid
                            if (this.asset_type === "subjects" || this.asset_type === "places") {
                              display_label = display_label + " (" + this.uid + ")";
                            }

                            this.display_label = $("<i>" + display_label + "</i>").text();

                            //
                            // Asset View URL's
                            //

                            if (Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_search_navigation_mode === "app") {
                              if (this.asset_type === "subjects" || this.asset_type === "places") {
                                // this.url_asset_nav = "/" + this.asset_type + "/" + this.id + "/overview/nojs?f=" + encodedFilters + "#search";
                                this.url_asset_nav = new Handlebars.SafeString(this.url_html + "?f=" + encodedFilters + "#search");
                              } else if (this.asset_type === "texts") {
                                // this.url_asset_nav = ASSET_VIEWER_PATH + "text_node/" + this.id + "/nojs?f=" + encodedFilters + "#search";
                                this.url_asset_nav = new Handlebars.SafeString(this.url_html + "?f=" + encodedFilters + "#search");
                              } else if (this.asset_type === "visuals") {
                                // this.url_asset_nav = ASSET_VIEWER_PATH + "visuals/node/" + this.id + "/nojs?f=" + encodedFilters + "#search";
                                this.url_asset_nav = new Handlebars.SafeString(this.url_html + "?f=" + encodedFilters + "#search");
                              } else if (this.asset_type === "sources") {
                                // this.url_asset_nav = ASSET_VIEWER_PATH + "sources/node/" + this.id + "/nojs?f=" + encodedFilters + "#search";
                                this.url_asset_nav = new Handlebars.SafeString(this.url_html + "?f=" + encodedFilters + "#search");
                              } else if (this.asset_type === "images") {
                                // this.url_asset_nav = ASSET_VIEWER_PATH + "photos_node/" + this.id + "/nojs?f=" + encodedFilters + "#search";
                                this.url_asset_nav = new Handlebars.SafeString(this.url_html + "?f=" + encodedFilters + "#search");
                              } else if (this.asset_type === "picture") {
                                // this.url_asset_nav = ASSET_VIEWER_PATH + "photos_node/" + this.id + "/nojs?f=" + encodedFilters + "#search";
                                this.url_asset_nav = new Handlebars.SafeString(this.url_html + "?f=" + encodedFilters + "#search");
                              } else if (this.asset_type === "audio-video") {
                                var url = this.url_html;
                                this.url_asset_nav = new Handlebars.SafeString(url + "?f=" + encodedFilters + "#search");
                              } else {
                                console.error("ERROR unknown asset type! " + this.asset_type + " for " + this.uid);
                                console.dir(this);
                                this.asset_type = 'unknown';
                                this.tree = 'unknown';
                              }
                            } else /* if (Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_search_navigation_mode === "local") */ {

                              if (this.asset_type === "subjects" || this.asset_type === "places") {
                                this.url_asset_nav =  "/" + this.asset_type + "/" + this.id + "/overview/nojs#search";
                              } else if (this.asset_type === "texts") {
                                this.url_asset_nav = ASSET_VIEWER_PATH + "text-node/" + this.id + "/nojs#search";
                              } else if (this.asset_type === "visuals") {
                                this.url_asset_nav = ASSET_VIEWER_PATH + "visuals-node/" + this.id + "/nojs#search";
                              } else if (this.asset_type === "sources") {
                                this.url_asset_nav = ASSET_VIEWER_PATH + "sources-node/" + this.id + "/nojs#search";
                              } else if (this.asset_type === "images") {
                                this.url_asset_nav = ASSET_VIEWER_PATH + "photos-node/" + this.id + "/nojs#search";
                              } else if (this.asset_type === "picture") {
                                this.url_asset_nav = ASSET_VIEWER_PATH + "photos-node/" + this.id + "/nojs?mms#search"
                              } else if (this.asset_type === "audio-video") {
                                var path = this.url_html.split('/');
                                var last = path.pop();
                                var type = path.pop();
                                this.url_asset_nav = "/places/0/" + "audio-video-node/" + this.id + "/nojs#search";
                              } else {
                                console.error("ERROR unknown asset type! " + this.asset_type);
                              }

                            }
                          });
                        }

                        var hbcontext = {
                          encodedFilters: encodedFilters,
                          searchString: searchString,
                          data: blob.asset_results,
                          asset_counts: decorated_counts,
                          rangeStart: Drupal.settings.kmapsSolr.getRangeStart(),
                          rangeEnd: Drupal.settings.kmapsSolr.getRangeEnd()
                        };
                        // Add pager to the context
                        if (blob.asset_results && blob.asset_results.numFound) {
                          // TODO: ys2n refactor to glean the kmapSolr instance via more flexible means
                          hbcontext.pager = getPagerMarkup(Drupal.settings.kmapsSolr);
                        }

                        // Decorate menu with counts and hints
                        if (blob.asset_results && blob.asset_results.numFound) {
                          // update the search badge count

                          // ROUNDING:  if the count is over a threshhold, round the number to the nearest 1K
                          var rounding_threshhold = 1000;
                          var count = blob.asset_results.numFound;

                          if (blob.asset_results.numFound > rounding_threshhold) {
                            count = Math.round(count/1000) + "K";
                          }

                          $('#results-count-badge').html( count );
                          // $('.search .search-hint').html("search hint");


                          // cache results data for use later
                          $.each(blob.results.docs,
                            function( n, doc ) {
                              cacheDoc(doc);
                            }
                          );
                        } else {
                          $('#results-count-badge').html("");
                          $('.search .search-hint').html("");
                        }

                        // render template:  see search_main_template retrieval above
                        if (search_main_template) {

                          if(DEBUG) console.log("HBCONTEXT asset_counts: " + JSON.stringify(hbcontext.asset_counts, undefined, 2));

                          // New context and cookie based gallery-mode logic....
                          // view-mode

                          // viewMode defaults
                          var viewMode = {
                            'places': 'list',
                            'subjects': 'list',
                            'audio-video': 'gallery',
                            'images': 'gallery',
                            'visuals': 'gallery',
                            'all': 'list',
                            'texts': 'list',
                            'sources': 'list'
                          };

                          var vmc = $.cookie('search-results-view-mode');
                          if (vmc) {

                            console.log("vmc = " + JSON.stringify(vmc));
                            try {
                              viewMode = JSON.parse(vmc);
                            } catch (e) {
                              console.error("bailing on parsing " + vmc)
                              $.cookie('search-results-view-mode', JSON.stringify(viewMode));
                            }
                          } else {
                            console.error ("saving " + JSON.stringify(viewMode));
                            $.cookie('search-results-view-mode', JSON.stringify(viewMode));
                          }

                          console.dir(viewMode);

                          // We use the first item in the array
                          // The implicit assumption here is that this is a radio-button selector
                          // and there will always only be one assetType selected at a time.
                          var current = (assetTypes)?assetTypes[0]:"all";
                          hbcontext.view_mode = current;

                          if ( viewMode[current] === "gallery" ) {
                            hbcontext.list_mode_selected = ""
                            hbcontext.gallery_mode_selected = "selected";
                          } else {
                            hbcontext.list_mode_selected = "selected";
                            hbcontext.gallery_mode_selected = "";
                          }

                          console.error("CURRENT: " + current);

                          if (current === "subjects" || current === "places" || current === "texts" || current === "sources") {
                            hbcontext.no_gallery = "no_gallery";
                          }

                          if (current === "audio-video") {
                            hbcontext.av_gallery = 1;
                            hbcontext.default_gallery = 0;
                          } else {
                            hbcontext.av_gallery = 0;
                            hbcontext.default_gallery = 1;
                          }

                          var markup = search_main_template(hbcontext);

                          // console.log("HBCONTEXT");
                          // console.dir(hbcontext);


                          // TODO: ys2n: this should be configurable
                          $('#faceted-search-results').html(markup);

                          // Resize Results Panel
                          //$('#faceted-search-results').resizable({
                          //    handles: 'w'
                          //});


                          // attach gallery behaviors (e.g. wookmark)
                          Drupal.attachBehaviors('.shanti-gallery');

                          $(window).bind('load orientationchange resize searchUpdate extopen', function() {
                            // console.error("bark!");
                            Drupal.attachBehaviors('#faceted-search-results');
                          });

                          $('.ui-resizable').bind('load orientationchange resize searchUpdate extopen', function() {
                            console.error("bark!");
                            Drupal.attachBehaviors('#faceted-search-results');
                          });

                          // apply the justified gallery script
                          $('#search-results-gallery').justifiedGallery({
                            rowHeight : 110,
                            lastRow : 'nojustify',
                            margins : 3,
                          });

                          //  apply customized popovers
                          $('#faceted-search-results [data-toggle="popover"]').popover({
                            content: function() {
                              var idx = $(this).closest('.search-results-gallery-node').data('lookup-index');
                              var ctx = hbcontext.data.docs[idx];
                              // console.dir(ctx);
                              // console.dir(hbcontext);
                              return search_results_popover_template(ctx);
                            },
                            trigger: 'hover',
                            html: true
                          }).mouseleave(function() {
                            $(this).popover('hide');
                          })

                          $('.kmaps-inpage-results-pager .pager-next').click(function () {
                            Drupal.settings.kmapsSolr.pageNext();
                          });
                          $('.kmaps-inpage-results-pager .pager-previous').click(function () {
                            Drupal.settings.kmapsSolr.pagePrev();
                          });
                          $('.kmaps-inpage-results-pager .pager-last').click(function () {
                            Drupal.settings.kmapsSolr.pageLast();
                          });
                          $('.kmaps-inpage-results-pager .pager-first').click(function () {
                            Drupal.settings.kmapsSolr.pageFirst();
                          });
                          $('.kmaps-inpage-results-pager .pager-input').on('change', function () {
                            var pg = parseInt($(this).val()); // force to be a number...
                            if (isNaN(pg)) {
                              pg = Drupal.settings.kmapsSolr.page();
                            }
                            $(this).val(pg);
                            Drupal.settings.kmapsSolr.page(pg);
                          });


                          // if the results are unfiltered, lets hide the results-tab
                          if($.isEmptyObject(blob.filters)){
                            $('#btn-show-search-results').hide('fast');
                          }

                          // This is a debug block that can be used to develop the UI.   Of course,
                          // this shouldn't be displayed to users in the end.
                          if (false) {
                            // useful debugging
                            $('.search-results-facets').append("<pre>" + JSON.stringify({
                              filters: blob.filters,
                              results: blob.results.numFound + " documents"
                            }, undefined, 3) + "</pre>");
                          }

                          // set or unset "filters-applied" class
                          // console.log("FILTERS: " + JSON.stringify(blob.filters));
                          if (($.type(blob.filters) === "undefined") || $.isEmptyObject(blob.filters)) {
                            // console.log("filters-applied OFF")
                            $('#faceted-search-results').removeClass("filters-applied");
                            $('.input-section .clearall').slideUp();
                          } else {
                            // console.log("filters-applied ON");
                            $('#faceted-search-results').addClass("filters-applied");
                            $('.input-section .clearall').slideDown();
                          }

                          $('#faceted-search-results').addClass('initialized');

                          $('.search-results-list-wrapper').scrollLock();

                          // update the facet count badges
                          $('.shanti-kmaps-solr-facet-title').each(function (i, x) {
                            var cnt = $(x).data("bucket-count");

                            // TODO: ys2n: THIS SHOULD BE CONFIGURABLE LIMIT (passed from jquery.solr.js?)
                            if (Number(cnt) > (300 - 1)) {
                              cnt = cnt + '+';
                            }

                            // make sure the badge is there
                            if ($(x).find('.badge').length < 1) {
                              $(x).append("<span class='badge'></span>");
                            }
                            $(x).find('.badge').text(cnt);
                          });

                          // asset filter handling
                          $('.results-list-asset-type-filter').on('click',function() {
                            console.error("PROCESS ASSET TYPE");
                            $(this).toggleClass('selected');

                            var singleMode = true;
                            if (singleMode) {
                              $(this).siblings('.results-list-asset-type-filter').removeClass('selected');
                            }

                            console.log("result asset type filter clicked: " + $(this).data('asset-type') + " selected=" + $(this).hasClass('selected'));

                            var selected_nodes = $('.results-list-asset-type-filter.selected');
                            var selected_asset_types = $.map(selected_nodes, function(x){
                              var type = $(x).data('asset-type');
                              return type;
                              }
                            );
                            console.log("SELECTED_ASSET_TYPES: " + selected_asset_types);
                            settings.kmapsSolr.showAssetTypes(selected_asset_types);

                          });

                          // view mode click handler
                          $('.results-list-asset-view-mode').on('click', function() {

                            var vm = JSON.parse($.cookie('search-results-view-mode'));
                            console.error("VIEW MODE SELECTED: " + $(this).data("view-mode"));

                            $(this).addClass('selected');
                            $(this).siblings('.results-list-asset-view-mode').removeClass('selected');

                            var selected_nodes = $('.results-list-asset-type-filter.selected');
                            var selected_asset_types = $.map(selected_nodes, function(x){
                                var type = $(x).data('asset-type');
                                return type;
                              }
                            );
                            console.log("SELECTED_ASSET_TYPES: " + selected_asset_types);

                            var viewMode = $(this).data("view-mode");
                            if (viewMode === "list") {
                              $('#faceted-search-results').removeClass("gallery-mode");
                              $('.search-results-node-preview').removeClass('show-gallery');
                              // update the cookie
                              vm[selected_asset_types[0]] = "list";

                            } else {
                              $('.search-results-node-preview').addClass('show-gallery');
                              $('#faceted-search-results').addClass("gallery-mode");
                              // update the cookie
                              vm[selected_asset_types[0]] = "gallery";
                            }

                            // save the updated view modes;
                            $.cookie('search-results-view-mode',JSON.stringify(vm));

                          });

                          $('#faceted-search-results').trigger("searchUpdate");

                          if (!$.isEmptyObject(blob.filters)) {
                            if ($('#faceted-search-results').hasClass('initialized')) {
                              // console.log("should we auto-open search results? " + window.location);
                              if (window.location && window.location.pathname.startsWith(ASSET_VIEWER_PATH) || window.location.hash === "#search") {
                                showResultsTab();
                              } else {
                                showResultsTab();
                              }
                            } else {
                              showResultsTab();
                            }
                          }


                          $('#faceted-search-results').trigger("searchUpdate");
                          // console.log("searchUpdate triggered");

                          //  kludge logic for seeing if the search has been updated:

                          var stateChange = false;
                          var newState = JSON.stringify(Drupal.settings.kmapsSolr.getState());
                          if(Drupal.settings.kmapsSolr.lastState) {
                            stateChange = (Drupal.settings.kmapsSolr.lastState !== newState);
                          }
                          Drupal.settings.kmapsSolr.lastState = newState;

                          if (!$.isEmptyObject(blob.filters)) {
                            if ($('#faceted-search-results').hasClass('initialized')) {
                              // console.log("should we auto-open search results? " + window.location);
                              if (window.location && window.location.pathname.startsWith(ASSET_VIEWER_PATH) || window.location.hash === "#search") {
                                // console.log("showResults 1");
                                showResultsTab();
                              } else {
                                if (stateChange) {
                                  // console.log("showResults: changed search");
                                  openSearchResults();
                                } else {
                                  // console.log("showResults: same search");
                                  showResultsTab();
                                }
                              }
                            } else {
                              // console.log("showResults 3");
                              showResultsTab();
                            }
                          }

                        } // end if (search_main_template)

                      }, // end updateHandler


                      beforeSearch: function(x) {
                        // console.error("Before Search!");
                        // console.dir(x);
                        $('#faceted-search-results').trigger("searchUpdating");
                        $('#faceted-search-results').addClass("search-active");
                        $('.search-results-list-wrapper').addClass("search-results-loading");
                        $('.search-results-node-preview').addClass("search-results-loading");
                        $('.view-section .tab-content').addClass("active-loading");
                        // console.log("beforeSearch: overlayMask show")
                        $('.extruder-content').overlayMask('show');
                      },

                      afterSearch: function(x) {
                        // console.error("After Search!");
                        // console.dir(x);

                        try {
                          var serializedFilterState = JSON.stringify(x.filters);
                          console.log("Saving defaultFilterState: " + serializedFilterState);
                          $.cookie("defaultFilterState", serializedFilterState, { expires: 1 , path: "/" })
                        } catch (err) {
                          console.error("Failed to serialize and save filter state: " + err);
                        }

                        $('#faceted-search-results').trigger("searchUpdate");
                        $('#faceted-search-results').removeClass("search-active")
                        $('.search-results-list-wrapper').removeClass("search-results-loading");
                        $('.search-results-node-preview').removeClass("search-results-loading");
                        $('.view-section .tab-content.active-loading').removeClass("active-loading");
                        // console.log("afterSearch: overlayMask hide")
                        $('.extruder-content').overlayMask('hide');

                      },

                      afterInit: function (xxx) {
                        $(function () {
                          // console.error("dEBUG: " + JSON.stringify(xxx.getState().filters, undefined, 3));
                          var $filters = xxx.getState().filters;
                          // console.dir($filters);

                          var tagList = [], pathLists = {};

                          $.each($filters, function (x, v) {
                            if (x === "kmaps") {
                              $.each(v, function (xid, i) {
                                var data = JSON.parse(storage.getItem(xid));
                                var $id, $label, $path;
                                if (data) {
                                  $label = data.header;
                                  $id = data.uid;
                                  $path = data.path;
                                } else {
                                  $label = xid;
                                  $id = xid;
                                }
                                tagList.push({ 'label': $label, 'id': $id });

                                var kpts = $id.split('-'),
                                  kmtype = kpts[0],
                                  id = kpts[1];

                                if ($.type(pathLists[kmtype]) !== 'array') {
                                  pathLists[kmtype] = [];
                                }
                                pathLists[kmtype].push($path);
                              });
                            } else {
                              var ent = xxx.getState().facetHash[x];
                              // console.log("*****: " + JSON.stringify(ent));
                              if (ent) {
                                tagList.push({
                                  'label': ent.type + ":" + ent.label,
                                  'id':ent.id
                                });
                                // addFacetTagToList(ent.type + ": " + ent.label, ent.id);
                              } else {
                                console.error("Hmmm:  unknown facet: " + x);
                              }
                            }

                            // process the lists
                            $.each(tagList, function(i,tag) {
                              addFacetTagToList(tag.label, tag.id);
                            });

                            for (var kmtype in pathLists) {
                              var pathList = pathLists[kmtype];
                              var $tree = $('.kmapfacetedtree[data-kmtype="' + kmtype + '"]').fancytree('getTree');
                              $tree.loadKeyPath(pathList) .done( function() {
                                $.each(pathList, function (i,path) {
                                  var id = path.split('/').pop();
                                  console.log("selecting " + id);
                                  var $node = $tree.getNodeByKey(id);
                                  console.log("found node " + $node);
                                  if ($node) {
                                    $node.setSelected(true);
                                  } else {
                                    console.error("We looked for a node " + id + " which didn't exist in tree " + $tree );
                                  }
                                });
                              }).fail(function() {
                                console.error("Fail callback called with arguments " + JSON.stringify(arguments));
                                alert('fail: ' + JSON.stringify(arguments));
                              });
                            }
                          });

                          if (xxx.getState().filters.searchString) {
                            // TODO: ys2n: kinda icky way to do this....
                            $(select_searchInput).val(xxx.getState().filters.searchString.replace('name_autocomplete:*', '').replace('*', ''));
                          }
                        });
                      }


                    },
                    { 'defaultFilterState': defaultFilterState }
                  );

                  // Search reset controls
                  // Add listener to search box clear (reloads page without search string)
                  $('#search-flyout .search-group .searchreset').click(function () {
                    Drupal.settings.kmapsSolr.search( { searchString:"" } );
                  });
                  $('.input-section').append("<div class='facet-search-controls'>" +
                    "<a href='#' class='clearall'>Clear All</a>" +
                    "</div>");
                  $('.input-section').on('click','.clearall',
                    function() {
                      Drupal.settings.kmapsSolr.clearAll().then(
                        function () {

                          // console.log("clearAll()");
                          closeSearchResults();

                          $('.active-kmfaceted-list').hide();
                          $('.active-kmfaceted-list .facet-item').remove();

                          // Clear all trees
                          $('.kmapfacetedtree').each( function(i, x) {
                            var n = $(x).fancytree("getTree").getSelectedNodes();
                            $(n).each(function(i, y) {
                              // console.log("deselecting: " + y);
                              y.setSelected(false);
                            });
                          });

                          // Clear the search input
                          $(select_searchInput).val("");
                        });
                    }
                  );

                } else {
                  console.error("HEY THERE'S no $.kmapsSolr!");
                  // set an error message in the search?
                }
              });

            // hijack the search form
            // TODO: ys2n: need to make this configurable.
            $(select_searchForm).submit(function () {
              var $ss = $(select_searchInput).val();
              var $params = {searchString: ""};
              if ($ss !== null && $ss !== "") {
                // need to support other types of wildcarding: e.g. begins with, exact match, etc.
                $ss = "*" + $ss.toLowerCase() + "*";
                $params = {searchString: $ss};
              }
              console.log("DOING SEARCH: " + JSON.stringify($params));
              // do an initial search to populate facets
              settings.kmapsSolr.search($params);
              return false;
            });

          });  // once


    }
  };


    // Helper Functions

    /**
     * updateKmapFacetCounts:
     *          a function extended in jQuery for the AJAX command array in shanti_kmaps_faceted_search.module function shanti_kmaps_faceted_search_gallery()
     *          It is called to add counts to the tree based on current treenode selection after drupal node teasers are loaded
     *          Also called after a page reload, when url has facets tags in them.
     *
     * @param {String} data
     *      A JSON representation of count data in an associative array with kmapid => count pairs, where kmapid is domain-number.
     *      When added to Drupal.settings.shanti_kmaps_faceted_search.search_filter_data this is the default count data displayed on the tree
     *      If not set, then the getKmapFacetCounts will get data from SOLR index based on selected kmapids.
     */
    // Called in Ajax Command Array in shanti_kmaps_faceted_search.module (~ l.682)
    $.fn.updateKmapFacetCounts = function (data) {
        if (data) {
            Drupal.settings.shanti_kmaps_faceted_search.search_filter_data = data;
        }
        // Set filters on tree then call getKmapFacetCounts()
        $('.kmapfacetedtree').each(function () {
            var atree = $(this).fancytree('getTree');
            getKmapFacetCounts(null, atree);
        });
        // Deal with Breadcrumbs
        $('nav.breadwrap ol.breadcrumb li').eq(0).nextAll('li').remove();
        var bclist = $.map($('.facet-item'), function (item) {
            return $(item).text();
        }).join(", ").replace(' ,', ',');
        if ($('.facet-item').length == 0) {
            bclist = "<em>No tags currently chosen</em>";
        }
        if ($('nav.breadwrap ol.breadcrumb li').eq(0).children("a").text() == "Audio-Video") {
            $('nav.breadwrap ol.breadcrumb li').eq(0).children("a").text("Audio-Video:");
        }
        $('nav.breadwrap ol.breadcrumb').append(
            '<li class="kmfbreadcrumb"><a name="page-type">' + Drupal.t('Subject or Place Tags') + '</a> <span class="icon shanticon-arrow3-right"></span></li>',
            '<li class="kmfbreadcrumb"><a name="current-page">' + bclist + '</a></li>'
        );
        $("body").removeClass("front").addClass("not-front");
        repopulateSearchBoxFromSettings();

    };

    /**
     * Called when a facet results are loaded after a search has been made and then a facet clicked on
     */
    var repopulateSearchBoxFromSettings = function () {
        // Repopulate search box after ajax load
        if (Drupal.settings.shanti_kmaps_faceted_search && Drupal.settings.shanti_kmaps_faceted_search.core_search && Drupal.settings.shanti_kmaps_faceted_search.core_search_query) {
            var json = $.parseJSON(Drupal.settings.shanti_kmaps_faceted_search.core_search_query);
            if (typeof(json["q"]) != "undefined") {
                $('#edit-search-block-form--2').val(json["q"]);
            }
        }
    };

    /**
     * An extension of the fancytree-expand event and also called on facet loads by updateKmapFacetCounts()
     * Queries the kmasset index for all assets of selected type that are tagged with the currently selecte facet(s)
     * And with the results updates the counts for each visisble node on the tree
     * Also hides nodes with no counts if that setting is chosen in the shanti_kmaps_faceted_search config page.
     * Counts are added to each node as an attribute of the node object (node.hitcount)
     * TODO: Several things to do:
     *                  - Only load counts on page load (for all) and when a node is activated (and counts change).
     *                  - Have server make call on page loads. (Can use setting .search_filter_data which automatically calls filterTreeByArray)
     *                  - Only update new nodes when exanded. Don't visit the whole tree. (Can use node.node.visit() possibly)
     *
     * @param {Object} e
     *      The current event object
     *
     * @param {Object} node
     *      The tree node that is being expanded
     */
    var getKmapFacetCounts = function (e, node) {
        if (typeof(node) === "undefined") {
            if ($('.kmapfacetedtree').length > 0) {
                node = $('.kmapfacetedtree').eq(0).fancytree('getTree');
            } else {
                return;
            }
        }
        if (typeof(node) === "string") {
            node = $('#' + node).fancytree('getTree');
        }
        // Solr/Kmaps Settings
        var solrurl = Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_server_solr,
            skfsettings = Drupal.settings.shanti_kmaps_faceted_search,
            domain = (typeof(node.data) != "undefined") ? node.data.kmtype : $(this).data('kmtype'),
            query = '';

        // Tree info
        var mytree = (typeof(node.tree) == "undefined") ? node : node.tree;
        var iswholetree = (node == mytree);
        if (typeof(mytree.data.kmroot) == "undefined") {
            mytree.data.kmroot = ' ';
        }
        var root = mytree.data.kmroot.toString().split(' '),
            childkeys = $.map(root, function (val, i) {
                val = val.replace(/\//g, '');
                if (val && val.length > 0) {
                    return domain + "-" + val;
                }
            }),
            boolop = " OR "; // boolean operator: OR by default (for children of a node) but set to AND for facets

        // Check if current search is active
        if (skfsettings.core_search) {
            var fdata = $.parseJSON(skfsettings.search_filter_data);
            filterTreeByArray(mytree, fdata);
            mytree.visit(function (child) {
                if (child.isVisible() && !child.isExpanded() && child.hitcount > 0) {
                    adjustListIconChildren(child, fdata);
                }
            });
            return;
        }

        // Childkeys set to facet ids if facets are chosen
        if ($('.active-kmfaceted-list .facet-item').length > 0) {
            childkeys = $.map($('.active-kmfaceted-list .facet-item'), function (item, i) {
                return $(item).data('kmid');
            });
            boolop = " AND ";
            // Otherwise just use ids from children of present node
        } else {
            for (var n in node.children) {
                if (node.children[n].key) {
                    childkeys.push(domain + "-" + node.children[n].key);
                }
            }
        }

        var restypes = skfsettings.resource_types.split(',').join(' OR ');

        if (restypes && restypes.length > 0) {
          query = 'asset_type:(' + restypes + ')';
          if (typeof(childkeys.length) !== "undefined" && childkeys.length > 0) {
            query = query + ' AND kmapid:(' + childkeys.join(boolop) + ')';
          }

          Drupal.settings.shanti_kmaps_faceted_search.hideZeros = false;
          $.ajax({
            url: solrurl + '/select',
            data: {
              'q': query,
              'rows': 0,
              'wt': 'json',
              'facet': true,
              'facet.field': 'kmapid',
              'facet.prefix': domain + '-',
              'facet.mincount': 1,
              'facet.limit': -1,
              'facet.sort': 'count',
            },
            dataType: 'jsonp',
            jsonp: 'json.wrf',
            success: function (data, status, jqXHR) {
              var kmfaceted = data.facet_counts.facet_fields.kmapid,
                kmcounts = {};
              for (var n = 0; n < kmfaceted.length; n += 2) {
                if (isNaN(kmfaceted[n]) && kmfaceted[n].indexOf('-') > -1) {
                  var kid = kmfaceted[n].split('-')[1],
                    fcount = kmfaceted[(n + 1)];
                  kmcounts[kid] = fcount;
                }
              }

              // Filter tree and add hitcount field to nodes. Hide nodes with no resources if that setting is on.
              var some_visible = false;
              mytree.filterNodes(function (node) {
                var nkey = node.key;
                if (typeof(kmcounts[nkey]) == "undefined") {
                  node.hitcount = 0;
                  if (!checkAncestorVisibility(node)) {
                    return false;
                  }
                  return !(Drupal.settings.shanti_kmaps_faceted_search.hideZeros); // hide no counts if admin setting is on (i.e. return false for settings value = true)
                } else {
                  some_visible = true;
                  node.hitcount = kmcounts[nkey];
                  if (node.parent == null || typeof(node.parent.expanded) == "undefined") {
                    return true;
                  }
                  return checkAncestorVisibility(node);
                }
              });

              // Add message to tree's tab if no kmap facet hits
              // if (!some_visible) {
              //     if (mytree.$div.parent().find('div.kmf-no-results').length == 0) {
              //         mytree.$div.before('<div class="kmf-no-results">No facet hits for this tree.</div>');
              //     }
              // } else {
              //     mytree.$div.parent().find('div.kmf-no-results').remove();
              // }
              // Add the hit count to the span.count if greater than 0. Otherwise, remove any previous counts.
              mytree.visit(function (child) {
                  var cspan = $(child.span).find('.count');
                  if (typeof(child.hitcount) != "undefined" && child.hitcount > 0) {
                      cspan.text('(' + child.hitcount + ')');
                      if (child.children) {
                          // Iterate through the now visible children and see test if they have children
                          // If not change icon from plus to terminal
                          for (var n in child.children) {
                              var child2 = child.children[n];
                              if (child2.hitcount > 0) {
                                  if (child2.isVisible()) {
                                      adjustListIconChildren(child2, kmcounts); // see below, changes icon to terminal if no children with hits
                                  }
                              }
                          }
                      }
                  } else {
                      cspan.text('');
                  }
              });

              // setTimeout(function() { mytree.$container.scrollTop(0);}, 350);
            }
          });
        }
    };


    function cacheDoc(doc) {
//       console.log("FARKLE!");
//       console.dir(doc);
      var path;
      if (doc.path) {
        path = doc.path;
      } else if (doc.ancestor_id_path) {
        path = doc.ancestor_id_path;
      } else if (doc.ancestor_id_gen_path) {
        path = doc.ancestor_id_gen_path;
      }

      if (path) {
        var cache = {
          "uid": doc.uid,
          "header": doc.header,
          "path": path,
        };
        var jsondata = JSON.stringify(cache);
        // console.log("caching: " + jsondata);
        storage.setItem(doc.uid, jsondata);
      } else {
        console.error ("Could not determine path from: " + JSON.stringify(doc.uid,undefined,1));
      }

    }

    function adjustListIconChildren(node, kmcounts) {
        var kmtype = node.tree.data.kmtype;
        var solrurl = Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_server_solr_terms;
        var level = node.data.path.split('/').length + 1;
        // Call Term data for all children
        $.ajax({
            url: solrurl + "/select",
            data: {
                q: "tree:" + kmtype + " AND ancestor_ids_generic:" + node.key + " AND level_i:" + level,
                fl: "id",
                rows: 200,
                wt: "json",
            },
            success: function (data) {
                var found = false;
                for (var n in data.response.docs) {
                    var ckid = data.response.docs[n].id;
                    var ckidnum = ckid.split("-")[1];
                    if (kmcounts[ckid] || kmcounts[ckidnum]) {
                        found = true;
                    }
                }
                if (!found) {
                    //if (DEBUG) console.log(node.title + ' does not have children with hits');
                    node.span.className = 'fancytree-node fancytree-exp-n fancytree-ico-c fancytree-match';
                }
            },
            dataType: 'jsonp',
            jsonp: 'json.wrf',
        });
    }

    /**
     * Will filter the given tree by a javascript object array where properies are the kmap ids and their values are the counts, e.g., fdata['subjects-123'] = 9
     * Called from getKmapFacetCounts if Drupal.settings.shanti_kmap_facets.search_filter_data contains an assoc. array of kmap ids with counts
     *
     * @param {Object} mytree
     *      The tree being filtered
     *
     * @param {Object} fdata
     *      An associative array of counts in the form of kmapid => count, where kmapid is in the format of domain-###
     */
    function filterTreeByArray(mytree, fdata) {
        // Filter tree and add hitcount field to nodes. Remove nodes with no resources if that setting is on.
        if (!fdata || fdata == null) {
            console.warn("No data in shanti_kmaps_faceted_search.js filterTreeByArray()");
            return;
        }
        mytree.filterNodes(function (node) {
            //if (DEBUG) console.log('node', node);
            var nkey = node.tree.data.kmtype + "-" + node.key;
            if (typeof(fdata[nkey]) == "undefined") {
                node.hitcount = 0;
                if (node.parent == null || typeof(node.parent.expanded) == "undefined") {
                    return true;
                }
                if (!checkAncestorVisibility(node)) {
                    return false;
                }
                return !(Drupal.settings.shanti_kmaps_faceted_search.hideZeros); // hide no counts if admin setting is on (i.e. return false for settings value = true)
            } else {
                node.hitcount = fdata[nkey];
                if (node.parent == null || typeof(node.parent.expanded) == "undefined") {
                    return true;
                }
                return checkAncestorVisibility(node);
            }
        });

        // Add the hit count to the span.count if greater than 0. Otherwise, remove any previous counts.
        mytree.visit(function (child) {
            var cspan = $(child.span).find('.count');
            if (typeof(child.hitcount) != "undefined" && child.hitcount > 0) {
                cspan.text('(' + child.hitcount + ')');
            } else {
                cspan.text('');
            }
        });
    }

    /**
     * Traverses up a treenode's ancestor chain to and returns true only if all ancestors are visible
     */
    function checkAncestorVisibility(node) {
        if (node.parent == null) {
            return true;
        }
        var parent = node.parent;
        var visible = true;
        do {
            visible = visible * parent.expanded;
        } while (parent = parent.parent);
        return visible;
    }


    // encapsulate resultsTab show action
    function showResultsTab() {
      // console.error("showing results tab");
      if ($('#faceted-search-results').hasClass('filters-applied') && $('#faceted-search-results').hasClass( 'off' ) ){
        $('#btn-show-search-results').show('fast');
        Drupal.attachBehaviors('#faceted-search-results');
      } else {
        console.log("filters-applied not found! NOT SHOWING RESULTS TAB");
      }
    }

    // encapsulate searchResults open
    function openSearchResults() {
      console.error("opening Search Results");
      $('#faceted-search-results')
        .css('display', 'block')
        .attr('aria-expanded', 'true')
        .openFlyout();
      $('#mandala-veil-bg').css({'z-index' : '290','opacity' : '85'});
      $('#btn-show-search-results').hide('fast');
      $('#btn-collapse-flyout').fadeIn('fast');
      console.log("openSeachResults");
      Drupal.attachBehaviors('#faceted-search-results');
    }

    // encapsulate searchResults close
    function closeSearchResults() {
      console.error("closing Search Results");
      $('#faceted-search-results')
        .attr('aria-expanded', 'false')
        .closeFlyout();
      $('#mandala-veil-bg').css({'z-index' : '-1','opacity' : '0'});
      $('#btn-collapse-flyout').fadeOut('fast');
      showResultsTab();
      console.log("closeSeachResults");
      Drupal.attachBehaviors('#faceted-search-results');
    }
  /**
   *
   *
   * @param evt
   * @param node
   */
  var navigateToKmap = function (evt, item) {

    var ftree = item.tree,
      trid = ftree.$div.attr('id'),
      title = item.node.title,
      data = item.node.data,
      domain = ftree.data.kmtype,
      kmid = data.path.split('/').pop(),
      fullkid = domain + "-" + kmid,
      curr_app = (Drupal.settings.kmaps_explorer) ? Drupal.settings.kmaps_explorer.app : "home"

    if ($.type(evt.originalEvent) === "undefined") {
      // console.error("NO NAVIGATE: " + domain + " " + kmid + " " + fullkid);
      // console.dir(evt.originalEvent);
    } else {
      // TODO: ys2n: FIX THIS KLUDGE!
      // console.error("CHECK NAVIGATION");
      // console.dir( { 'curr_app' : curr_app, 'data' : data , 'domain' : domain  })
      if (curr_app === domain) {
        console.log("NAVIGATE: " + domain + " " + kmid + " " + fullkid);
        Drupal.ajax["ajax-id-" + kmid].createNavigateAction(kmid, domain);
        // booby trap
        // TODO: ys2n: gotta be a better way to do this!
        closeSearchResults();
      } else {
        console.log("NAVIGATE BY REDIRECT! " + domain + " " + kmid + " " + fullkid);

        var kmloc = "https://mandala-dev.shanti.virginia.edu/" + domain + "/__KMAPID__/overview/nojs";

        if (Drupal.settings && Drupal.settings.shanti_kmaps_admin) {
          if (domain === "subjects") {
            kmloc = Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_server_subjects_explorer;
          } else if (domain === "places") {
            kmloc = Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_server_places_explorer;
          }
        }
        kmloc = kmloc.replace('__KMAPID__', kmid)

        console.log("NAVIGATE BY REDIRECT! " + kmloc);

        window.location = kmloc;

        // window.location = "https://mandala-dev.shanti.virginia.edu/" + domain + "/" + kmid + "/overview/nojs";
      }
    }
  }

    /**
     * An extension of the fancytreecollapse event. Called when a treenode is collapsed
     * In such cases, fancy tree redisplays the node and its facet count is lost. So this function redisplays that facet count.
     */
    var loadMyFacetHitCount = function (e, node) {
        if (typeof(node.node) === "undefined") {
            return;
        }
        var nd = node.node;
        var cspan = $(nd.span).find(".count");
        if (typeof(nd.hitcount) !== "undefined" && nd.hitcount > 0) {
            cspan.text('(' + nd.hitcount + ')');
        } else {
            cspan.text('');
        }
    };

    /**
     * Load AV thumbnails for resources with a certain facet in the main content div of the page via AJAX and adds facet tag to list of chosen facets
     * In order to initiate an AJAX call, we call createFacetAction() with the full kmap id.
     * A loading div replaces the current page content
     *
     * @param {Object} e
     *      The event that triggered this function, a fancytreeactivate event
     *
     * @param {Object} item
     *      The treenode that was clicked. (Item is less confusing than "node", because the item has a node attribute.)
     */
    var loadKmapFacetHits = function (e, item) {

        if (DEBUG) console.log({"event": e, "item": item});
        var ftree = item.tree,
            trid = ftree.$div.attr('id'),
            title = item.node.title,
            data = item.node.data,
            domain = ftree.data.kmtype,
            kmid = data.path.split('/').pop(),
            fullkid = domain + "-" + kmid;

      // cache the data here

        var cache = {
          "header": title,
          "uid" : fullkid,
          "path" : data.path
        };

        cacheDoc(cache);

      if (false && Drupal.settings.shanti_kmaps_faceted_search.kmaps_link) {
            window.location.pathname = '/' + domain + '/' + kmid + '/overview/nojs';
            if (e) {
                e.preventDefault();
            }
            return;
        }

        $('.ajaxtmplink').remove(); // Remove temp link added when deleting facet

        // Check if already clicked and loaded and return if so
        if ($('.active-kmfaceted-list #facet-item-' + fullkid).length > 0) {
            return;
        }

        Drupal.settings.kmapsSolr.selectKmapId(fullkid);
        // console.log("selectedKmapId " + fullkid);

        // Add facet item tag
        addFacetTagToList(title, fullkid, data.path);

        // Set active tree, remove any messages, and add a progress spinner
        Drupal.settings.shanti_kmaps_faceted_search.activeTree = trid;
        $('div.messages').remove();

        if (false) {
            $('article.tab-pane.main-col').html('<div class="region region-content"><div id="block-system-main" class="block block-system"><div class="ajax-progress ajax-progress-throbber" style="display:inline-block;"><div class="throbber">&nbsp;</div></div> Loading ...</div></div>');
        }

        // Create the facet filtering action

        // TODO!: ys2n: vestige from audio-video...?
        if (false) {
            Drupal.ajax["ajax-id-" + kmid].createFacetAction(fullkid);
        }
        // Hide Popover from Tree if any are shown
        $('.popover.search-popover').popover("hide");

        // Prevent click event from propogating
        e.stopImmediatePropagation();
        return false;
    };

  var populateAssetCounts = function (countsElem, key, domain) {

    // console.error("populateAssetCounts");

    var update_counts = function (elem, counts) {
      // console.log("update counts: " + elem + " " + JSON.stringify(counts));
      // console.groupCollapsed(elem.text());
      // console.groupEnd();

      var av = elem.find('span.shanticon-audio-video ~ span.badge');
      if (typeof(counts["audio-video"]) != "undefined") {
        av.html(counts["audio-video"]);
      }
      (Number(av.text()) > 0) ? av.closest('li').show() : av.closest('li').hide();

      var photos = elem.find('span.shanticon-photos ~ span.badge');
      if (typeof(counts.picture) != "undefined") {
        photos.html(counts.picture);
      }
      (Number(photos.text()) > 0) ? photos.closest('li').show() : photos.closest('li').hide();

      var places = elem.find('span.shanticon-places ~ span.badge');
      if (typeof(counts.related_places) != "undefined") {
        places.html(counts.related_places);
      }
      (Number(places.text()) > 0) ? places.closest('li').show() : places.closest('li').hide();

      var texts = elem.find('span.shanticon-texts ~ span.badge');
      if (typeof(counts.texts) != "undefined") {
        texts.html(counts["texts"]);
      }
      (Number(texts.text()) > 0) ? texts.closest('li').show() : texts.closest('li').hide();

      var subjects = elem.find('span.shanticon-subjects ~ span.badge');

      if (!counts.feature_types) {
        counts.feature_types = 0
      }
      ;
      if (!counts.related_subjects) {
        counts.related_subjects = 0
      }
      ;

      var s_counts = Number(counts.related_subjects) + Number(counts.feature_types);
      if (s_counts) {
        subjects.html(s_counts);
      }
      (Number(subjects.text()) > 0) ? subjects.closest('li').show() : subjects.closest('li').hide();


      var visuals = elem.find('span.shanticon-visuals ~ span.badge');
      if (typeof(counts.visuals) != "undefined") {
        visuals.html(counts.visuals);
      }
      (Number(visuals.text()) > 0) ? visuals.closest('li').show() : visuals.closest('li').hide();


      var sources = elem.find('span.shanticon-sources ~ span.badge');
      if (typeof(counts.sources) != "undefined") {
        sources.html(counts.sources);
      }
      (Number(sources.text()) > 0) ? sources.closest('li').show() : sources.closest('li').hide();

      elem.find('.assoc-resources-loading').hide();
    };

    var fq = Drupal.settings.shanti_kmaps_admin['shanti_kmaps_admin_solr_filter_query'];
    var kmidxBase = Drupal.settings.shanti_kmaps_admin['shanti_kmaps_admin_server_solr'];
    var termidxBase = Drupal.settings.shanti_kmaps_admin['shanti_kmaps_admin_server_solr_terms'];
    if (!domain) {
      domain = (Drupal.settings.kmaps_explorer) ? Drupal.settings.kmaps_explorer.app : "places";
    }
    // console.log("counts elem = " + countsElem + " key = " + key + " domain = " + domain);

    var project_filter = (fq) ? ("&" + fq) : "";
    if (!kmidxBase) {
      console.error("kmindex_root not set!");
    }
    if (!termidxBase) {
      console.error("termindex_root not set!");
    }
    // Update counts from asset index
    var assetCountsUrl =
      kmidxBase + '/select?q=kmapid:' + domain + '-' + key + project_filter + '&start=0&facets=on&group=true&group.field=asset_type&group.facet=true&group.ngroups=true&group.limit=0&wt=json&json.wrf=?';
    $.ajax({
      type: "GET",
      url: assetCountsUrl,
      dataType: "jsonp",
      timeout: 90000,
      error: function (e) {
        console.error(e);
        // countsElem.html("<i class='glyphicon glyphicon-warning-sign' title='" + e.statusText);
      },
      beforeSend: function () {
      },

      success: function (data) {
        var updates = {};

        // extract the group counts -- index by groupValue
        $.each(data.grouped.asset_type.groups, function (x, y) {
          var asset_type = y.groupValue;
          var asset_count = y.doclist.numFound;
          updates[asset_type] = asset_count;
        });

        update_counts(countsElem, updates);
      }
    });

    // Update related place and subjects counts from term index






    // {!child of=block_type:parent}id:places-22675&wt=json&indent=true&group=true&group.field=block_child_type&group.limit=0
    var relatedCountsUrl =
      termidxBase + '/select?q={!child of=block_type:parent}id:' + domain + '-' + key + project_filter + '&wt=json&indent=true&group=true&group.field=block_child_type&group.limit=0&wt=json&json.wrf=?';
    $.ajax({
      type: "GET",
      url: relatedCountsUrl,
      dataType: "jsonp",
      timeout: 90000,
      error: function (e) {
        console.error(e);
        // countsElem.html("<i class='glyphicon glyphicon-warning-sign' title='" + e.statusText);
      },
      beforeSend: function () {
      },

      success: function (data) {
        var updates = {};

        // extract the group counts -- index by groupValue
        $.each(data.grouped.block_child_type.groups, function (x, y) {
          var block_child_type = y.groupValue;
          var rel_count = y.doclist.numFound;
          updates[block_child_type] = rel_count;
        });

        update_counts(countsElem, updates);
      }
    });

    // Another (parallel) query

    var subjectsRelatedPlacesCountQuery = termidxBase + "/select?indent=on&q={!parent%20which=block_type:parent}related_subject_uid_s:" + domain + '-' + key + "%20OR%20feature_type_id_i:" + key + "&wt=json&json.wrf=?&group=true&group.field=tree&group.limit=0";

    $.ajax({
      type: "GET",
      url: subjectsRelatedPlacesCountQuery,
      dataType: "jsonp",
      timeout: 90000,
      error: function (e) {
        console.error(e);
        // countsElem.html("<i class='glyphicon glyphicon-warning-sign' title='" + e.statusText);
      },
      beforeSend: function () {
      },

      success: function (data) {
        var updates = {};
        // extract the group counts -- index by groupValue
        $.each(data.grouped.tree.groups, function (x, y) {
          var tree = y.groupValue;
          var rel_count = y.doclist.numFound;
          console.error(tree + " = " + rel_count);
          updates["related_" + tree] = rel_count;
        });

        update_counts(countsElem, updates)
      }
    });
  };

    /**
     * Adds a facet tag to the list of active (chosen) facets. Also adds hidden input named "kmap_filters" with kmap ids chosen to the search form if it exists.
     *
     * @param {String} title
     *      the text to display in the tag,
     *
     * @param {String} fullkid
     *      full kmaps id, e.g. subjects-123
     *
     */
    var addFacetTagToList = function () {

      var actionQueue = function (){
        // this always returns a resolved promise
        var resolved = function () {
          return $.Deferred().resolve();
        };
        // this always returns a rejected promise
        var rejected = function () {
          return $.Deferred().reject();
        };
        var promise = resolved();

        return {
          push: function push(fn) {
            promise = promise
              .then(fn)
              .then(resolved, fn)
              .then(resolved, fn)
              .then(resolved, fn)
              .then(resolved, fn)
              .then(resolved, rejected);
            return this;
          }
        };
      }();

      // var selectNode = function () {
      //   return function (ftree, id) {
      //     var def = $.Deferred();
      //     console.log("getNodeByKey: " + id);
      //     var activeNode = ftree.getNodeByKey(id);
      //     if (activeNode) {
      //       console.log("activeNode: " + activeNode);
      //       activeNode.setSelected(true);
      //       return activeNode.setActive();
      //     } else {
      //       return def.reject();
      //     }
      //   };
      // }();

      var doneCallback = function () {
      }; // null function

      var instance = function(title, fullkid, path, callback) {

          if ($.type(callback) === "function") {
            doneCallback = callback;
          }
          if (DEBUG) {
            console.log("AddFacetTagToList: title = " + title + " fullkid = " + fullkid + " path: " + path);
          }

          var jsondata = storage.getItem(fullkid);
          // console.log("ADDFacetTagToList: found in cache: " + jsondata);

          var cache;
          try {
            cache = JSON.parse(jsondata);
            // console.log("AddFacetTag: cache returned: " + JSON.stringify(cache, undefined, 2));
          } catch (e) {
            console.error("couldn't parse cached json data: " + jsondata);
          }

          if ($.type(path) === "undefined") {
            if (cache) {
              path = cache.path;
            }
          }
          if ($.type(path) === "undefined") {
            path = "";
          }

          if ($.type(title) === "undefined" || title.length === 0 || title === fullkid) {
            if (cache) {
              title = cache.header;
            }
          }
          if ($.type(title) === "undefined" || title.length === 0) {
            title = fullkid;
          }

        if (path.length > 0) {
          // This has a path and is therefore tree-based and therefore we should display a "+"
          title = "+" + title
        }

        if ($('.active-kmfaceted-list').find($('#facet-item-' + fullkid)).length === 0) {
            var taghtml = '<div class="facet-item label label-default selected-kmap" id="facet-item-' + fullkid + '" data-kmid="' + fullkid +
              '" title="' + fullkid + '"><span  id="facet-item-delete-' + fullkid + '" class="icon shanticon-close2 kmfaceted-item-delete ' + fullkid + ' shanti-kmaps-processed"></span>' +
              '<span class="kmap-label">' + title + '</span></div>';
            $('.active-kmfaceted-list').slideDown().append(taghtml);
            // Add chosen Kmaps to search form inputs if it exists to be used by site to filter searches by chosen kmaps. Must be implemented on a site by site basis in search form submit function
            if ($('#search-block-form .input-group').length > 0) {
              if ($('#search-block-form .input-group #kmap_filters_input').length == 0) {
                $('#search-block-form .input-group').append('<input type="hidden" name="kmap_filters"  id="kmap_filters_input" value="">');
              }
              var val = $('#search-block-form .input-group #kmap_filters_input').attr('value');
              if (val.length > 0) {
                val += "_";
              }
              $('#search-block-form .input-group #kmap_filters_input').attr('value', val + fullkid).trigger('change');
            }

            // var kpts = fullkid.split('-'),
            //   kmtype = kpts[0],
            //   id = kpts[1];
            //
            // // select nodes in the trees
            //
            // // if (path) {
            //   var $tree = $('.kmapfacetedtree[data-kmtype="' + kmtype + '"]').fancytree('getTree');
            //
            //   if (!path.startsWith("/")) {
            //     path = "/" + path;
            //   }
            //
            //   console.error("LOADKEYPATH : " + path + " id: " + id);
            //   actionQueue.push($tree.loadKeyPath(path));
            //   actionQueue.push(selectNode($tree, id));
            // } else {
            //   console.error("AddFacetTagToList: ERROR: PATH: " + path);
            // }

          } else {
            console.log(fullkid + " already exists in the list");
          }
      }
      return instance;
    }();

    /**
     * This function is called when the X delete button next to a facet is clicked. It creates a temporary hidden div,
     * Calculates what the URL would be without that facet, then attaches an Drupal AJAX click call to div with the new url.
     * Finally, it waits .3 secs and clicks on the hidden div and at the same time removes the facet tile in the list
     *
     * @param {Object} cid
     *      This is the Cancel button ID or the element ID on the circle X icon in the facet tag in the list
     * @param {Object} kmid
     *      This is the kmap id of the item being deleted, e.g. subjects-20, places-643.
     */

        // TODO: ys2n:  refactor to encapsulate the "AJAX-url-creating" action and substitute our own
    var doRemoveFacet = function (kmid) {

            var cid = "#facet-item-delete-" + kmid;
            console.log("doRemoveFacet:  cid=" + cid + " kmid=" + kmid);
            // Remove kmap from hidden input #kmap_filters_input value, set above in AddFacetTagToList()
            if ($('#search-block-form .input-group  #kmap_filters_input').length != 0) {
                var val = $('#search-block-form .input-group #kmap_filters_input').attr('value').replace(kmid, '').replace('__', '_').replace(/^_([^_]+)/, "$1").replace(/([^_]+)_$/, "$1");
                $('#search-block-form .input-group  #kmap_filters_input').attr('value', val);
            }
            // Deactivate removed facet in it tree so it can be clicked again
            var keypts = kmid.match(/(subjects|places)-(\d+)/);

            if (keypts && keypts.length) {
              var nodeid = (keypts.length == 3) ? keypts[2] : false;
              var kmtype = keypts[1];

              console.log("Drupal.settings.shanti_kmaps_faceted_search.activeTree: " + Drupal.settings.shanti_kmaps_faceted_search.activeTree);

              var activeNode = $('.kmapfacetedtree[data-kmtype="' + kmtype + '"]').fancytree('getTree').getNodeByKey(nodeid);
              if (activeNode) {
                  activeNode.setActive(false);
                  activeNode.setSelected(false);
              }

            }

            if (DEBUG) {
                console.log("Removing facet item: " + kmid);
            }
            // Map all currently chosen facet kmap ids into an array.
            var allkids = $.map($('.facet-item .kmfaceted-item-delete'), function (item) {
                return $(item).parent().data("kmid");
            });
            allkids = allkids.join("_"); // join them with an underscore

            // Get search string if it exists
            var m,sstr = '';
            if (m = window.location.pathname.match(/(\/search\/[^\/]+)\/nojs/)) {
                sstr = m[1];
            }
            // // Calculate the new URL, removing the kmap id for the facet being deleted
            // var newurl = Drupal.settings.basePath + 'kmaps/facets/' + allkids + sstr + '/ajax';
            // newurl = newurl.replace(kmid,'').replace('/_','/').replace('_/','/').replace('__','_');
            // newurl = newurl.replace('facets//', 'facets/all/');

            // Remove old temporary delete links and create a new one to assign a Drupal.ajax call to
            $('.ajaxtmplink').remove();
            var dellnkid = kmid + "-delete-link";
            $('.active-kmfaceted-list').append('<div id="' + dellnkid + '" class="ajaxtmplink" style="display:none;">Delete ' + kmid + '</div>');

            // // Assign a Drupal.ajax call to the temp div.
            // var settings = {
            //             url:  newurl,
            //             event: 'click',
            //             keypress: false,
            //             prevent: false,
            //             progress: {
            //               type: 'text',
            //               message: ' ... '
            //             },
            //         };
            // Drupal.ajax[dellnkid] = new Drupal.ajax(null, $("#" + dellnkid), settings);

            // Show loading message
            if (false) $('article.tab-pane.main-col').html('<div class="region region-content"><div id="block-system-main" class="block block-system"><div class="ajax-progress ajax-progress-throbber" style="display:inline-block;"><div class="throbber">&nbsp;</div></div> Loading ...</div></div>');

            // Click the temp div to initiate Ajax call and remove the facet tile from the list.
            setTimeout(function () {
                $("#" + dellnkid).click();
                $(cid).parent().remove();
                // If the list is empty, hide the div
                if ($('.active-kmfaceted-list .facet-item').length == 0) {
                    $('.active-kmfaceted-list').slideUp();

                }
                // can't do this until facet is actually removed from UI
                if ($('#search-block-form .input-group  #kmap_filters_input').length != 0) {
                    $('#search-block-form .input-group  #kmap_filters_input').trigger('change');
                }
            }, 300);

            //  Hmmm. Groaty way to access this object, doncha think?
            Drupal.settings.kmapsSolr.removeFacet(kmid);
            Drupal.settings.kmapsSolr.removeKmapId(kmid);
        };

    if (typeof(Drupal.ajax) != 'undefined') {
        // Ajax Related Functions

        /**
         * Custom method to execute this ajax action... (taken from kmaps explorer)
         *
         * I think this is a way to avoid calling an action twice.
         */
        Drupal.ajax.prototype.executeFacetAction = function () {
            var ajax = this;

            if (ajax.ajaxing) {
                return false;
            }

            try {
                // console.log("Executing ajax action: " + JSON.stringify(ajax.options))
                // console.log(JSON.stringify(Drupal.settings, undefined, 2))
                $.ajax(ajax.options);

                // KLUDGE!!
              // var redirect = ajax.options.url.replace('ajax','nojs');
              // console.log("punting to redirect: " + redirect);
              // //
              //
              // alert("Redirecting to: " + redirect);
              //   window.location = redirect;

            } catch (err) {
                console.error("Could not process process: " + JSON.stringify(ajax.options) + " error: " + err);
                console.dir(ajax.options);

              var redirect = ajax.options.url.replace('ajax','nojs');
              console.log("punting to redirect: " + redirect);
              alert("Redirecting to: " + redirect);
              window.location = redirect;
                return false;
            }

            return false;
        };

        /**
         * Create the custom actions and execute it (taken from Gerard's code in explorer but slightly modified)
         *
         * @param {Object} kid
         *      The Kmap ID for which to create an action
         */


        // TODO: ys2n: candidate for elimination (old audio-video facet code)
        Drupal.ajax.prototype.createFacetAction = function (kid) {
            var DEBUG = false;

            if (DEBUG) console.log(" CREATE FACET ACTION: " + kid);

            var kpts = kid.split('-'),
                app = kpts[0],
                id = kpts[1],
                baseUrl = Drupal.settings.basePath,
                skf = Drupal.settings.shanti_kmaps_faceted_search;

            // append terminal slash if there isn't one.
            if (!/\/$/.test(baseUrl)) {
                baseUrl += "/";
            }

            var pthpts = window.location.pathname.split('/');
            if (DEBUG) {
                console.log("Window path in Create Facet Action: " + window.location.pathname);
            }

            if (pthpts.length > 3 && pthpts[3].match(/places|subjects/)) {
                var oldkids = pthpts[3];
                kid = oldkids + "_" + kid;
            }

            if (DEBUG) {
                console.log("kid string in Create Facet Action: " + kid);
            }
            var qparams = $.parseJSON(skf.core_search_query);
            var srchp = (skf.core_search) ? '/search/' + qparams['q'] : '';

            var settings = {
                url: baseUrl + "kmaps/facets/" + kid + srchp + '/ajax',
                event: 'click',
                keypress: false,
                prevent: false
            };

            Drupal.ajax['ajax-' + app + '-' + id] = new Drupal.ajax(null, $('<br/>'), settings);

            Drupal.ajax['ajax-' + app + '-' + id].executeFacetAction();
        };

      Drupal.ajax.prototype.createNavigateAction = function ($id, $app) {
        // console.log("createNavigateAction called with app = " + $app + " and id = " + $id);
        var baseUrl = Drupal.settings.basePath;

        // append terminal slash if there isn't one.
        if (!/\/$/.test(baseUrl)) {
          baseUrl += "/";
        }

        // probably should prevent regenerating an ajax action that already exists... Maybe using . once()?
        var settings = {
          url: baseUrl + $app + '/' + $id + '/overview/ajax',
          event: 'click',
          keypress: false,
          prevent: false
        }

        if (!Drupal.ajax['navigate-' + $app + '-' + $id]) {
          //console.error("Adding ajax to navigate-" + $app + '-' + $id);
          Drupal.ajax['navigate-' + $app + '-' + $id] = new Drupal.ajax(null, $('<br/>'), settings);
        }
        //console.error("Executing action navigate-" + $app + '-' + $id);
        Drupal.ajax['navigate-' + $app + '-' + $id].executeFacetAction();
      };
    }

    var getPagerMarkup = function (kmapsSolr) {

        var current = kmapsSolr.page();
        var pagecount = kmapsSolr.pageCount();

        var pager = '<ul class="typeahead-pager pager">';
        if (current > 1) { // link to first and previous pages
            pager += '<li class="pager-first active first"><a data-goto-page="1" title="Go to first page"><span class="icon"></span></a></li>';
            pager += '<li class="pager-previous active"><a data-goto-page="' + (current - 1) + '" title="Go to previous page"><span class="icon"></span></a></li>';
        }
        else {
            pager += '<li class="pager-first first"><span class="icon"></span></li>';
            pager += '<li class="pager-previous"><span class="icon"></span></li>';
        }
        pager += '<li class="pager-item">Page</li>';
        pager += '<li class="pager-item widget active"><input class="pager-input" type="text" value="' + current + '" data-last="' + pagecount + '" title="Enter page, then press Return."></li>';
        pager += '<li class="pager-item">of ' + pagecount + '</li>';
        if (current < pagecount) { // link to next and last pages
            pager += '<li class="pager-next active"><a data-goto-page="' + (current + 1) + '" title="Go to next page"><span class="icon"></span></a></li>';
            pager += '<li class="pager-last active last"><a data-goto-page="' + pagecount + '" title="Go to last page"><span class="icon"></span></a></li>';
        }
        else {
            pager += '<li class="pager-next"><span class="icon"></span></li>';
            pager += '<li class="pager-last last"><span class="icon"></span></li>';
        }
        pager += '</ul>';
        return pager;
    };


})(jQuery);
