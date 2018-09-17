/**
 * Created by edwardjgarrett on 6/12/16.
 */

(function ($) {

  $.fn.overlayMask = function (action) {
    var mask = this.find('.overlay-mask');
    // Create the required mask
    if (!mask.length) {
      mask = $('<div class="overlay-mask"><div class="loading-container"><div class="loading"></div><div id="loading-text">Searching&#133;</div></div></div>');
      mask.css({
        position: 'absolute',
        width: '100%',
        height: '100%',
        top: '0px',
        left: '0px',
        zIndex: 100,
        opacity: 9,
        backgrogroundColor: 'white'
      }).appendTo(this).fadeTo(0, 0.5).find('div').position({
        my: 'center center',
        at: 'center center',
        of: '.overlay-mask'
      });
    }

    // Act based on params
    if (!action || action === 'show') {
      mask.show();
    } else if (action === 'hide') {
      mask.hide();
    }
    return this;
  };

  Drupal.behaviors.explorer_block = {
    attach: function (context, settings) {
      var admin = settings.shanti_kmaps_admin;
      //console.dir(settings);
      //console.log(JSON.stringify(settings, undefined, 2));
      var domain = (settings.kmaps_explorer) ? settings.kmaps_explorer.app : 'places';
      var root_kmap_path = domain == 'subjects' ? admin.shanti_kmaps_admin_root_subjects_path : admin.shanti_kmaps_admin_root_places_path;
      var base_url = domain == 'subjects' ? admin.shanti_kmaps_admin_server_subjects : admin.shanti_kmaps_admin_server_places;
      var root_kmapid = domain == 'subjects' ? admin.shanti_kmaps_admin_root_subjects_id : admin.shanti_kmaps_admin_root_places_id;

      var update_countsElem = function (elem, counts) {
        // console.log("elem = ");
        // console.dir(elem);
        // console.error(JSON.stringify(counts,undefined,2));

        var av = elem.find('.shanticon-audio-video ~ span.badge');
        if (typeof(counts["audio-video"]) != "undefined") {
          (counts["audio-video"]) ? av.html(counts["audio-video"]).parent().show() : av.parent().hide();
        }
        if (Number(av.text()) > 0) {
          av.parent().show();
        }

        var photos = elem.find('.shanticon-photos ~ span.badge');
        if (typeof(counts.picture) != "undefined") {
          photos.html(counts.picture);
        }
        (Number(photos.text()) > 0) ? photos.parent().show() : photos.parent().hide();

        var places = elem.find('.shanticon-places ~ span.badge');
        if (typeof(counts.related_places) != "undefined") {
          places.html(counts.related_places);
        }
        if (Number(places.text()) > 0) {
          places.parent().show();
        }

        var texts = elem.find('.shanticon-texts ~ span.badge');
        if (typeof(counts.texts) != "undefined") {
          texts.html(counts["texts"]);
        }
        if (Number(texts.text()) > 0) {
          texts.parent().show();
        }

        var subjects = elem.find('.shanticon-subjects ~ span.badge');

        if (!counts.feature_types) { counts.feature_types = 0 };
        if (!counts.related_subjects) { counts.related_subjects = 0 };

        var s_counts = Number(counts.related_subjects)  + Number(counts.feature_types);
        if (s_counts) {
          subjects.html(s_counts);
        }
        if (Number(subjects.text()) > 0) {
          subjects.parent().show();
        }

        var visuals = elem.find('.shanticon-visuals ~ span.badge');
        if (typeof(counts.visuals) != "undefined") {
          visuals.html(counts.visuals);
        }
        if (Number(visuals.text()) > 0) {
          visuals.parent().show();
        }

        var sources = elem.find('.shanticon-sources ~ span.badge');
        if (typeof(counts.sources) != "undefined") {
          sources.html(counts.sources);
        }
        if (Number(sources.text()) > 0) {
          sources.parent().show();
        }

        elem.find('.assoc-resources-loading').hide();
      };

      var decorateElementWithPopover = function (elem, key, title, path, caption) {
          function update_counts(countsUrl, element, config) {

              var conf = {
                  countsMap: {
                      "places": "unmapped_places",
                      "subjects": "unmapped_subjects"
                  },
                  callback: function() {}
              };

              $.extend(conf, config);

              console.log("update_counts: countsUrl=" + countsUrl);
              console.log("update_counts: countsMap=" + JSON.stringify(conf.countsMap));

              $.ajax({
                  type: "GET",
                  url: countsUrl,
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
                          var category = y.groupValue;
                          var count = y.doclist.numFound;

                          // rename the category if needed
                          var mapped_category = category;
                          if (conf.countsMap[category]) {
                              mapped_category = conf.countsMap[category];
                          }
                          updates[mapped_category] = count;
                      });

                      update_countsElem(element, updates);

                      // callback if synchronization is needed.
                      if (conf.callback) {
                          conf.callback(element);
                      }
                  }
              });
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
            // $("body > .popover").removeClass("related-resources-popover"); // target css styles on search tree popups
            // $("body > .popover").addClass("search-popover"); // target css styles on search tree popups

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
            var termindex =  "kmterms_predev";  // TODO this needs to be derived from termidxBase...
            var cumulativeQuery = "{!join%20to=\"kmapid\"%20from=\"uid\"%20fromIndex=\"" + termindex + "\"}ancestor_uids_generic:" + uid;
            var flatQuery = "kmapid:" + uid;

            var assetCountsUrl =
              kmidxBase + '/select?q='  + cumulativeQuery + project_filter + '&start=0&facets=on&group=true&group.field=asset_type&group.facet=true&group.ngroups=true&group.limit=0&wt=json&json.wrf=?';
            update_counts(assetCountsUrl, countsElem);

            // Update related place and subjects counts from term index
            if (domain === 'subjects') {
              dom_map = {subjects:"related_subjects",places:"places"};
              alt_map = {places:"related_places", subject:"subjects"};
            } else {
              dom_map = {places:"related_places", subject:"subjects"};
              alt_map = {subjects:"related_subjects",places:"places"};
            }

            var flatRelatedCountsUrl =
              termidxBase + '/select?q={!child of=block_type:parent}id:' + domain + '-' + key + project_filter + '&wt=json&indent=true&group=true&group.field=block_child_type&group.limit=0&wt=json&json.wrf=?';
            update_counts(flatRelatedCountsUrl, countsElem, dom_map);

            // Update related place and subjects counts from term index
            var cumulativeRelatedCountsUrl =
              termidxBase + '/select?q={!child of=block_type:parent}ancestor_uids_generic:' + domain + '-' + key + project_filter + '&wt=json&indent=true&group=true&group.field=block_child_type&group.limit=0&wt=json&json.wrf=?';
            update_counts(cumulativeRelatedCountsUrl, countsElem, alt_map );

            // this should NOT be cumulative
            var subjectsRelatedPlacesCountQuery = termidxBase + "/select?indent=on&q={!parent%20which=block_type:parent}related_subject_uid_s:" + domain + '-' + key + "%20OR%20feature_type_id_i:" + key + "&wt=json&json.wrf=?&group=true&group.field=tree&group.limit=0";
            update_counts(subjectsRelatedPlacesCountQuery);

          });
        }

        return elem;
      };

      $('#kmaps-search', context).once('kmaps-explorer').each(function () {

        var $typeahead = $('#kmaps-explorer-search-term', this);
        var search = $typeahead.hasClass('kmap-no-search') ? false : true;
        var search_key = '';
        var $tree = $('#tree');

        ////   RECONFIGURE HERE!

        $tree.kmapsTree({
          termindex_root: admin.shanti_kmaps_admin_server_solr_terms,
          kmindex_root: admin.shanti_kmaps_admin_server_solr,
          type: domain,
          root_kmap_path: root_kmap_path,
          baseUrl: base_url,
          expand_path: "/13735"

        }).on('useractivate', function (ev, data) {
          var domain = (Drupal.settings.kmaps_explorer) ? Drupal.settings.kmaps_explorer.app : "places";
          // console.dir(ev);
          // console.dir(data);
         //  console.log(root_kmapid);
          Drupal.ajax["ajax-id-" + data.key].createAction(data.key, domain);
          ev.stopImmediatePropagation();
          return false;
        });

        if (search) {
          var $listview = $('.listview > .view-wrap');
          $typeahead.kmapsTypeahead({
            menu: $listview,
            term_index: admin.shanti_kmaps_admin_server_solr_terms,
            domain: domain,
            root_kmapid: root_kmapid,
            ancestors: 'off', //don't display ancestry in search results
            fields: 'ancestors', //get ancestors field for use in popover
            max_terms: 30,
            min_chars: 0,
            pager: 'on',
            empty_query: '*:*',
            empty_limit: 30,
            empty_sort: 'header_ssort ASC', // sortable header field
            sort: 'header_ssort ASC', // sort even when there's a search term
            filters: admin.shanti_kmaps_admin_solr_filter_query ? admin.shanti_kmaps_admin_solr_filter_query : ''
          }).kmapsTypeahead('onSuggest',
            function () {
              $('a[href=".listview"]').tab('show');
              $('.kmaps-tt-suggestion', $listview).each(function() {
                var $sugg = $(this);
                decorateElementWithPopover(this, $sugg.attr('data-id'), $sugg.find('.kmaps-place-name, .kmaps-term').html(), $sugg.attr('data-path'), '');
              });
            }
          ).kmapsTypeahead('onFilterChange',
            function (filters) {
              Drupal.ShantiSarvaka.searchTabHeightKMaps();
            }
          ).bind('typeahead:asyncrequest',
            function () {
              search_key = $typeahead.typeahead('val'); //get search term
            }
          ).bind('typeahead:select',
            function (ev, sel) {
              var id = sel.doc.id.substring(sel.doc.id.indexOf('-') + 1);
              // console.log(JSON.stringify(sel, undefined, 2));
              var elid = $('span[id*="ajax-id-"]').eq(0).attr('id'); // get first valid ajax id to attach action to.
              $typeahead.typeahead('val', search_key); // revert back to search key
              Drupal.ajax[elid].createAction(id, domain);
            }
          ).on('input',
            function () {
              if (this.value == '') {
                search_key = '';
                $tree.kmapsTree('reset', function () {
                  $tree.fancytree('getTree').getNodeByKey(root_kmapid).scrollIntoView(true);
                });
              }
            }
          );
        }
        $('.advanced-link').click(function () {
          $(this).toggleClass("show-advanced", 'fast');
          $(".advanced-view").slideToggle('fast', function () {
            Drupal.ShantiSarvaka.searchTabHeightKMaps();
          });
          $(".advanced-view").toggleClass("show-options");
          $(".view-wrap").toggleClass("short-wrap"); // ----- toggle class for managing view-section height
        });

        $("#searchbutton").on('click', function () {
          // console.log("triggering doSearch!");
          $("#kmaps-explorer-search-term").trigger('doSearch');
        });

        $('#kmaps-explorer-search-term').attr('autocomplete', 'off'); // turn off browser autocomplete

        $('.listview').on('shown.bs.tab', function () {

          if ($('div.listview div div.table-responsive table.table-results tr td').length == 0) {
            notify.warn("warnnoresults", "Enter a search above.");
          }

          var header = (location.pathname.indexOf('subjects') !== -1) ? "<th>Name</th><th>Root Category</th>" : "<th>Name</th><th>Feature Type</th>";
          $('div.listview div div.table-responsive table.table-results tr:has(th):not(:has(td))').html(header);
          $("table.table-results tbody td span").trunk8({tooltip: false});

          if ($('.row_selected')[0]) {
            if ($('.listview')) {
              var me = $('div.listview').find('.row_selected');
              var myWrapper = me.closest('.view-wrap');
              var scrollt = me.offset().top;

              myWrapper.animate({
                scrollTop: scrollt
              }, 2000);
            }
          }
        });

        // Run when switching to tree view
        $('.treeview').on('shown.bs.tab', function () {
          var activeNode = $('#tree').fancytree("getTree").getActiveNode();
          if (activeNode) {
              scrollToActiveNode();
          }
        });


        function scrollToActiveNode() {
            var tree = $('#tree').fancytree('getTree');
            var active = tree.getActiveNode();
            active.makeVisible().done(
                function() {
                    var totalOffset = active.li.offsetTop ;
                    $(tree.getActiveNode().li)
                        .parentsUntil('#tree','li')
                        .each(
                            function() { totalOffset += this.offsetTop }
                        );
                    $(active.li).closest('.view-wrap').scrollTop(totalOffset);
                }
            );
        }


        function maskSearchResults(isMasked) {
          var showhide = (isMasked) ? 'show' : 'hide';
          $('.view-section>.tab-content').overlayMask(showhide);
        }

        function maskTree(isMasked) {
          var showhide = (isMasked) ? 'show' : 'hide';
          $('#tree').overlayMask(showhide);
        }

        var searchUtil = {
          clearSearch: function () {
            // console.log("BANG: searchUtil.clearSearch()");
            if ($('#tree').fancytree('getActiveNode')) {
              $('#tree').fancytree('getActiveNode').setActive(false);
            }
            $('#tree').fancytree('getTree').clearFilter();
            $('#tree').fancytree("getRootNode").visit(function (node) {
              node.setExpanded(false);
            });
            //        $('div.listview div div.table-responsive table.table-results').dataTable().fnDestroy();


            $('div.listview div div.table-responsive table.table-results tr').not(':first').remove();
            //        $('div.listview div div.table-responsive table.table-results').dataTable();

            // "unwrap" the <mark>ed text
            $('span.fancytree-title').each(
              function () {
                $(this).text($(this).text());
              }
            );

          }
        };

        var notify = {
          warn: function (warnid, warnhtml) {
            var wonk = function () {
              if ($('div#' + warnid).length) {
                $('div#' + warnid).fadeIn();
              } else {
                jQuery('<div id="' + warnid + '" class="alert alert-danger fade in"><button type="button" class="close" data-dismiss="alert" aria-hidden="true">×</button>' + warnhtml + '</div>').fadeIn().appendTo('#notification-wrapper');
              }
            };

            if ($('#notification-wrapper div#' + warnid).length) {
              $('#notification-wrapper div#' + warnid).fadeOut('slow', wonk);
            } else {
              wonk();
            }
          },

          clear: function (warnid) {

            if (warnid) {
              $('#notification-wrapper div#' + warnid).fadeOut('slow').remove()
            } else {
              $('#notification-wrapper div').fadeOut('slow').remove()
            }
          }
        };
        // SOLR AJAX
        //

        // --- close and clear all
        //  searchUtil.clearSearch();
        //  $('#tree').fancytree("getTree").clearFilter();

        // If there is a error node in fancytree.  Then you can click it to retry.
        $('#tree').on('click', '.fancytree-statusnode-error', function () {
          $('#tree').fancytree();
        });

        // iCheck fixup -- added by gketuma
        $('nav li.form-group input[name=option2]').on('ifChecked', function (e) {
          var newSource = settings.baseUrl + "/features/fancy_nested.json?view_code=" + $('nav li.form-group input[name=option2]:checked').val();
          $("#tree").fancytree("option", "source.url", newSource);
        });

        // kludge, to prevent regular form submission.
        $('#kmaps-search form').on('submit', function (event, target) {
          event.preventDefault();
          return false;
        });
      }); // end of once
    }

    //end of attach
  };


  // Custom method to execute this ajax action...
  Drupal.ajax.prototype.executeAction = function () {
    var ajax = this;


    // return false;

    // hey buzz off, we're already busy!
    if (ajax.ajaxing) {
      //console.log("WE ARE ALREADY EXECUTING")
      return false;
    }

    try {
      //console.log("WE ARE AJAXING")
      $.ajax(ajax.options);
    }
    catch (err) {
      console.error("Could not process process: " + ajax.options.url);
      console.dir(ajax.options);
      return false;
    }

    return false;
  };

  // Create the custom actions and execute it

  Drupal.ajax.prototype.createAction = function ($id, $app) {
    var admin = Drupal.settings.shanti_kmaps_admin;
    var domain = (Drupal.settings.kmaps_explorer) ? Drupal.settings.kmaps_explorer.app : "places";
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

    console.dir(settings);

    if (!Drupal.ajax['navigate-' + $app + '-' + $id]) {
      //console.error("Adding ajax to navigate-" + $app + '-' + $id);
      Drupal.ajax['navigate-' + $app + '-' + $id] = new Drupal.ajax(null, $('<br/>'), settings);
    }
    //console.error("Executing action navigate-" + $app + '-' + $id);
    Drupal.ajax['navigate-' + $app + '-' + $id].executeAction();
  };


})(jQuery);
