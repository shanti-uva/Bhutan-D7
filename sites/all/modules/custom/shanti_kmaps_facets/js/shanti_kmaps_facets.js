(function ($) {

    var debug = false; // To turn on console log debugging

    // Drupal Behavior Functions
    /**
     * Script for loading the trees upon page load.
     *      Each tree is in div.kmapfacettree
     *      Calls $.kmapsTree() function (from shanti_kmaps_tree library) for each such div with special settings.
     *      Uses special functions below:
     *              - getKmapFacetCounts() : whenever a treenode is expanded, adds counts to new treenodes (Really readds to all treenodes)
     *              - loadMyFacetHitCounts() : when a treenode is collapsed, because it is displayed without the count by the innate collapse function
     *              - loadKmapFacetHits(): when a treenode is activated (clicked on), load teasers for all such tagged Drupal nodes
     *              - updateKmapFacetCounts: an jQuery extended function called by Drupal Ajax array
     */
    Drupal.behaviors.shanti_kmaps_facets_tree_loading = {
        attach: function (context, settings) {
            var admin = settings.shanti_kmaps_admin;
            var kmfset = settings.shanti_kmaps_facets;
            if (context == document && !$('body').hasClass('page-admin')) {
                // Process each tree
                $('.kmapfacettree').each(function() {
                    // Create the Settings values
                    var id = $(this).attr("id");
                    $tree = $('#' + id);
                    var domain = $.trim($tree.data('kmtype'));
                    if (debug) { console.log('loading: ' + id, domain, $tree); }
                    var rootid = $.trim($tree.data('kmroot'));
                    var root_kmap_path = (domain == 'subjects') ? admin.shanti_kmaps_admin_root_subjects_path : admin.shanti_kmaps_admin_root_places_path;
                    var base_url = (domain == 'subjects') ? admin.shanti_kmaps_admin_server_subjects : admin.shanti_kmaps_admin_server_places;
                    var tree_settings = {
                        termindex_root: admin.shanti_kmaps_admin_server_solr_terms, // calls proxyIt() function below
                        kmindex_root: admin.shanti_kmaps_admin_server_solr,
                        type: domain,
                        baseUrl: base_url,
                        generateIds: false,
                    };
                    if (rootid && (rootid != "" || rootid != "all")) { tree_settings.root_kmap_path = rootid; }
                    // Initialize the tree
                    var tree = $tree.kmapsTree(tree_settings).on('fancytreeexpand', getKmapFacetCounts)
                        // Add Handlers to show counts and ...
                       .on('fancytreecollapse', loadMyFacetHitCount) 
                        // Load Video Thumnbails in Content Page via Ajax
                        .on('fancytreeactivate', loadKmapFacetHits)
                        .css("height", "auto");

                        // Expand first level of the tree
                        setTimeout(function() {
                            var child1 =$(tree).fancytree('getTree').getRootNode().getFirstChild();
                            if (child1) {
                                child1.setExpanded(true);
                            }
                        }, 1000);
                });

                // Set "live" action for kmaps facet item delete clicks (enabling the delete icon on all facet tags in future)
                $(document).on('click', '.kmfacet-item-delete', function(e) {
                    var cid = '#' + $(this).attr('id');
                    doRemoveFacet(cid, $(this).parent().data('kmid'));
                });

                // Load Facets from URL
                if (kmfset.loadFacetsFromURL) {
                    tags = $.parseJSON(kmfset.loadFacetsFromURL);
                    for (n in tags) {
                        var tag = tags[n];
                        AddFacetTagToList(tag.title, tag.kmid);
                    }
                }
                // Repopulate Search box if loaded from URL
                repopulateSearchBoxFromSettings();

                //Functionality for history popstate
                $(window).on('popstate', function(e) {
                    if (!e.originalEvent.state || !e.originalEvent.state.tag) return;
                    window.location.href = location.href;
                });
            }
        }
    };

    /**
     * Add Pager events for facet results pages
     */
    Drupal.behaviors.shanti_kmaps_facets_pager_events = {
        attach: function (context, settings) {
            // TODO: Generalize! (This only works for pagerer)
            $('.kmaps-facets-results table.pagerer ul.pager input.pagerer-page').unbind('keydown').on('keydown', function(e) {
                if (e.keyCode == 13) {
                    e.preventDefault();
                    e.stopImmediatePropagation();
                    var jstr = $(this).attr('name');
                    var json = $.parseJSON(jstr);
                    var pgnum = $(this).val() - 1;
                    var path = Drupal.settings.basePath + json.path.replace('/nojs', '/ajax').replace('pagererpage', pgnum);
                    $(this).after('<div class="ajax-progress ajax-progress-throbber" style="display:inline-block;"><div class="throbber">&nbsp;</div></div>');
                    $(this).after('<div class="link" style="display: none;"><a id="mykmflink" href="' + path + '" class="use-ajax">go</a></div>');
                    Drupal.attachBehaviors('a#mykmflink');
                    $('a#mykmflink').click(function() {
                        setTimout(function() {$('a#mykmflink').remove();}, 1000);
                    });
                }
            });
        }
    };

    /**
     * Attach Events that happen to the tree and search box
     */
     Drupal.behaviors.shanti_kmaps_facets_tree_events = {
        attach: function (context, settings) {
            if (context == document && !$('body').hasClass('page-admin')) {
                // When BS Tab is activated
                $('.km-facet-tab').on('show.bs.tab', function (e) {
                    var div = $(this).children('a').eq(0).attr('href') + " .kmapfacettree"; // find the tree div
                    var tree = $(div).fancytree('getTree');   // get the fancytree
                    Drupal.settings.shanti_kmaps_facets.activeTree = tree;
                    Drupal.settings.kmaps_explorer = { 'app': tree.data.kmtype };
                });
                if (typeof(Drupal.settings.shanti_kmaps_facets.activeTree) == "undefined" && $('.km-facet-div.active .kmapfacettree').fancytree == "function") {
                    Drupal.settings.shanti_kmaps_facets.activeTree = $('.km-facet-div.active .kmapfacettree').fancytree('getTree');
                }

                // Add listener to search box clear (reloads page without search string)
                $('.extruder .search-group button.btn.searchreset').click(function() {
                    var myloc = window.location.href;
                    if (m = myloc.match(/\/search\/[^\/]+\/nojs/)) {
                        // TODO: Replace this page reload with a true AJAX call for when search is cancelled.
                        window.location.href = myloc.replace(m[0], '/nojs');
                    } else if (myloc.match(/\/search\//)) {
                        window.location.href=myloc.split("/search/")[0]; // When it's a regular search being cancelled, just go to home page
                    } else {
                        window.location.reload(); // to reset facet trees
                    }
                });
            }
        }
    };

    // Helper Functions

    /**
     * updateKmapFacetCounts:
     *          a function extended in jQuery for the AJAX command array in shanti_kmaps_facets.module function shanti_kmaps_facets_gallery()
     *          It is called to add counts to the tree based on current treenode selection after drupal node teasers are loaded
     *          Also called after a page reload, when url has facets tags in them.
     *
     * @param {String} data
     *      A JSON representation of count data in an associative array with kmapid => count pairs, where kmapid is domain-number.
     *      When added to Drupal.settings.shanti_kmaps_facets.search_filter_data this is the default count data displayed on the tree
     *      If not set, then the getKmapFacetCounts will get data from SOLR index based on selected kmapids.
     */
    // Called in Ajax Command Array in shanti_kmaps_facets.module (~ l.682)
    $.fn.updateKmapFacetCounts = function(data) {
        if (data) { Drupal.settings.shanti_kmaps_facets.search_filter_data = data; }
        // Set filters on tree then call getKmapFacetCounts()
        $('.kmapfacettree').each(function() {
            var atree = $(this).fancytree('getTree');
            getKmapFacetCounts(null, atree);
        });
        // Deal with Breadcrumbs
        $('nav.breadwrap ol.breadcrumb li').eq(0).nextAll('li').remove();
        var bclist = $.map($('.facet-item'), function(item) {return $(item).text(); }).join(", ").replace(' ,', ',');
        if ($('.facet-item').length == 0) { bclist = "<em>No tags currently chosen</em>";}
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
    var repopulateSearchBoxFromSettings = function() {
         // Repopulate search box after ajax load
        if (Drupal.settings.shanti_kmaps_facets.core_search && Drupal.settings.shanti_kmaps_facets.core_search_query) {
            var json = $.parseJSON(Drupal.settings.shanti_kmaps_facets.core_search_query);
            if (typeof(json["q"]) != "undefined") {
                $('#edit-search-block-form--2').val(json["q"]);
            }
        }
    };

    /**
     * An extension of the fancytree-expand event and also called on facet loads by updateKmapFacetCounts()
     * Queries the kmasset index for all assets of selected type that are tagged with the currently selecte facet(s)
     * And with the results updates the counts for each visisble node on the tree
     * Also hides nodes with no counts if that setting is chosen in the shanti_kmaps_facets config page.
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
    var getKmapFacetCounts = function(e, node) {
       if (typeof(node) == "undefined") {
           if ($('.kmapfacettree').length > 0) {
               node = $('.kmapfacettree').eq(0).fancytree('getTree');
           } else {
               return;
           }
       }
       if (typeof(node) == "string") {
           node = $('#' + node).fancytree('getTree');
       }
       // Solr/Kmaps Settings
        var solrurl = Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_server_solr,
                skfsettings = Drupal.settings.shanti_kmaps_facets,
                domain = (typeof(node.data) != "undefined") ? node.data.kmtype : $(this).data('kmtype'),
                query = '';

       // Tree info
       var mytree = (typeof(node.tree) == "undefined") ? node : node.tree;
       var iswholetree = (node == mytree);
       if (typeof(mytree.data.kmroot) == "undefined") {mytree.data.kmroot = ' '; }
       var root = mytree.data.kmroot.toString().split(' '),
            childkeys = $.map(root, function(val, i) { 
                                    val = val.replace(/\//g,'');
                                    if (val && val.length > 0) {return domain + "-" + val;}
                                }),
            boolop = " OR "; // boolean operator: OR by default (for children of a node) but set to AND for facets

       // Check if current search is active
       if (skfsettings.core_search) {
           var fdata = $.parseJSON(skfsettings.search_filter_data);
           filterTreeByArray(mytree, fdata);
           mytree.visit(function(child) {
               if (child.isVisible() && !child.isExpanded() && child.hitcount > 0) {
                   adjustListIconChildren(child, fdata);
               }
           });
           return;
       }

       // Childkeys set to facet ids if facets are chosen
       if ($('.active-kmfacets-list .facet-item').length > 0) {
            childkeys = $.map($('.active-kmfacets-list .facet-item'), function(item, i) {return $(item).data('kmid');});
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
        query = 'asset_type:(' + restypes + ')';
       if (typeof(childkeys.length) != "undefined" && childkeys.length > 0) {
             query = query + ' AND kmapid:(' + childkeys.join(boolop) + ')';
        }
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
            success: function(data, status, jqXHR) {
                var kmfacets = data.facet_counts.facet_fields.kmapid,
                        kmcounts = {};
                for (var n=0; n < kmfacets.length; n+=2) {
                    if (isNaN(kmfacets[n]) && kmfacets[n].indexOf('-') > -1) {
                        var  kid = kmfacets[n].split('-')[1],
                               fcount = kmfacets[(n + 1)];
                        kmcounts[kid] = fcount;
                    }
                }

                // Filter tree and add hitcount field to nodes. Hide nodes with no resources if that setting is on.
                var some_visible = false;
                mytree.filterNodes(function(node){
                   var nkey = node.key;
                   if (typeof(kmcounts[nkey]) == "undefined") {
                       node.hitcount = 0;
                       if (!checkAncestorVisibility(node)) {return false; }
                       return !(Drupal.settings.shanti_kmaps_facets.hideZeros); // hide no counts if admin setting is on (i.e. return false for settings value = true)
                   } else {
                       some_visible = true;
                       node.hitcount = kmcounts[nkey];
                       if (node.parent == null || typeof(node.parent.expanded) == "undefined") {return true;}
                       return checkAncestorVisibility(node);
                   }
                });

                // Add message to tree's tab if no kmap facet hits
                if (!some_visible) {
                    if (mytree.$div.parent().find('div.kmf-no-results').length == 0) {
                        mytree.$div.before('<div class="kmf-no-results">No facet hits for this tree.</div>');
                    }
                } else {
                    mytree.$div.parent().find('div.kmf-no-results').remove();
                }
                // Add the hit count to the span.count if greater than 0. Otherwise, remove any previous counts.
                mytree.visit(function(child) {
                   var cspan = $(child.span).find('.count');
                   if  (typeof(child.hitcount) != "undefined" && child.hitcount > 0) {
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
    };

    function adjustListIconChildren(node, kmcounts) {
        var kmtype = node.tree.data.kmtype;
        var solrurl = Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_server_solr_terms;
        var level = node.data.path.split('/').length + 1;
        // Call Term data for all children
        $.ajax({
            url: solrurl + "/select",
            data: {
               q:  "tree:" + kmtype + " AND ancestor_ids_generic:" + node.key + " AND level_i:" + level,
               fl: "id",
               rows: 200,
               wt: "json",
            },
            success: function(data) {
                var found = false;
                for (var n in data.response.docs) {
                    var ckid = data.response.docs[n].id;
                    var ckidnum = ckid.split("-")[1];
                    if (kmcounts[ckid] || kmcounts[ckidnum]) { found = true; }
                }
                if (!found) {
                    //console.log(node.title + ' does not have children with hits');
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
            console.warn("No data in shanti_kmaps_facets.js filterTreeByArray()");
            return;
        }
        mytree.filterNodes(function(node){
            //console.log('node', node);
           var nkey = node.tree.data.kmtype + "-" + node.key;
           if (typeof(fdata[nkey]) == "undefined") {
               node.hitcount = 0;
               if (node.parent == null || typeof(node.parent.expanded) == "undefined") {return true;}
               if (!checkAncestorVisibility(node)) {return false; }
               return !(Drupal.settings.shanti_kmaps_facets.hideZeros); // hide no counts if admin setting is on (i.e. return false for settings value = true)
           } else {
               node.hitcount = fdata[nkey];
               if (node.parent == null || typeof(node.parent.expanded) == "undefined") {return true;}
               return checkAncestorVisibility(node);
           }
        });

        // Add the hit count to the span.count if greater than 0. Otherwise, remove any previous counts.
        mytree.visit(function(child) {
           var cspan = $(child.span).find('.count');
           if  (typeof(child.hitcount) != "undefined" && child.hitcount > 0) {
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
        if (node.parent == null) {return true;}
        var parent = node.parent;
        var visible = true;
        do {
            visible = visible * parent.expanded;
        } while (parent = parent.parent);
        return visible;
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
      fullkid = domain + "-" + kmid;



      console.log("NAVIGATE: " + domain + " " + kmid + " " + fullkid);

    Drupal.ajax["ajax-id-" + kmid].createNavigateAction(kmid,domain);

  };





    /**
     * An extension of the fancytreecollapse event. Called when a treenode is collapsed
     * In such cases, fancy tree redisplays the node and its facet count is lost. So this function redisplays that facet count.
     */
    var loadMyFacetHitCount = function (e, node) {
        if (typeof(node.node) == "undefined") {return;}
        var nd = node.node;
        var cspan = $(nd.span).find(".count");
        if (typeof(nd.hitcount) != "undefined" && nd.hitcount > 0) {
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
    var loadKmapFacetHits = function(e, item) {
        //console.log({"event":e, "item":item});
        var ftree = item.tree,
              trid = ftree.$div.attr('id'),
              title = item.node.title,
              data = item.node.data,
              domain = ftree.data.kmtype,
              kmid = data.path.split('/').pop(),
              fullkid = domain + "-" + kmid;

        if (Drupal.settings.shanti_kmaps_facets.kmaps_link) {
            window.location.pathname = '/' + domain + '/' + kmid + '/overview/nojs';
            if (e) { e.preventDefault();}
            return;
        }

        $('.ajaxtmplink').remove(); // Remove temp link added when deleting facet

        // Check if already clicked and loaded and return if so
        if ($('.active-kmfacets-list #facet-item-' + fullkid).length > 0) { return; }

        // Add facet item tag
        AddFacetTagToList(title, fullkid);

        // Set active tree, remove any messages, and add a progress spinner
        Drupal.settings.shanti_kmaps_facets.activeTree = trid;
        $('div.messages').remove();
        $('article.tab-pane.main-col').html('<div class="region region-content"><div id="block-system-main" class="block block-system"><div class="ajax-progress ajax-progress-throbber" style="display:inline-block;"><div class="throbber">&nbsp;</div></div> Loading ...</div></div>');

        // Create the facet filtering action
        Drupal.ajax["ajax-id-" +kmid].createFacetAction(fullkid);

        // Hide Popover from Tree if any are shown
        $('.popover.search-popover').popover("hide");

        // Prevent click event from propogating
        e.stopImmediatePropagation();
        return false;
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
    function AddFacetTagToList(title, fullkid) {
        if (debug) {console.log("Adding facet item: " + fullkid);}
        var taghtml = '<div class="facet-item label label-default selected-kmap" id="facet-item-' + fullkid + '" data-kmid="' + fullkid +
                        '" title="' + fullkid + '"><span  id="facet-item-delete-' + fullkid +'" class="icon shanticon-close2 kmfacet-item-delete ' + fullkid + ' shanti-kmaps-processed"></span>' +
                        '<span class="kmap-label">' + title + '</span></div>';
       $('.active-kmfacets-list').show().append(taghtml);
       // Add chosen Kmaps to search form inputs if it exists to be used by site to filter searches by chosen kmaps. Must be implemented on a site by site basis in search form submit function
       if ($('#search-block-form .input-group').length > 0) {
           if ($('#search-block-form .input-group #kmap_filters_input').length == 0) {
                $('#search-block-form .input-group').append('<input type="hidden" name="kmap_filters"  id="kmap_filters_input" value="">');
            }
            var val = $('#search-block-form .input-group #kmap_filters_input').attr('value');
            if (val.length > 0) { val += "_";}
            $('#search-block-form .input-group #kmap_filters_input').attr('value', val + fullkid).trigger('change');
        }
    }


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
    var doRemoveFacet = function(cid, kmid) {
        // Remove kmap from hidden input #kmap_filters_input value, set above in AddFacetTagToList()
         if ($('#search-block-form .input-group  #kmap_filters_input').length != 0) {
              var val = $('#search-block-form .input-group #kmap_filters_input').attr('value').replace(kmid, '').replace('__','_').replace(/^_([^_]+)/,"$1").replace(/([^_]+)_$/,"$1");
              $('#search-block-form .input-group  #kmap_filters_input').attr('value', val);
          }
        // Deactivate removed facet in it tree so it can be clicked again
        var keypts = kmid.match(/(subjects|places)-(\d+)/);
        var nodeid = (keypts.length == 3) ? keypts[2] : false;
        if (nodeid && typeof(Drupal.settings.shanti_kmaps_facets.activeTree) == "string") {
            var treeid = Drupal.settings.shanti_kmaps_facets.activeTree;
            var activeNode = $('#' + treeid).fancytree('getTree').getNodeByKey(nodeid);
            if (activeNode) { activeNode.setActive(false); }
        }
        if (debug) {console.log("Removing facet item: " + kmid);}
        // Map all currently chosen facet kmap ids into an array.
        var allkids = $.map( $('.facet-item .kmfacet-item-delete'), function(item) { return $(item).parent().data("kmid");});
        allkids = allkids.join("_"); // join them with an underscore

        // Get search string if it exists
        var sstr = '';
        if (m = window.location.pathname.match(/(\/search\/[^\/]+)\/nojs/)) {
            sstr = m[1];
        }
        // Calculate the new URL, removing the kmap id for the facet being deleted
        var newurl = Drupal.settings.basePath + 'kmaps/facets/' + allkids + sstr + '/ajax';
        newurl = newurl.replace(kmid,'').replace('/_','/').replace('_/','/').replace('__','_');
        newurl = newurl.replace('facets//', 'facets/all/');

        // Remove old temporary delete links and create a new one to assign a Drupal.ajax call to
        $('.ajaxtmplink').remove();
        var dellnkid = kmid + "-delete-link";
        $('.active-kmfacets-list').append('<div id="' + dellnkid + '" class="ajaxtmplink" style="display:none;">Delete ' + kmid + '</div>');

        // Assign a Drupal.ajax call to the temp div.
        var settings = {
                    url:  newurl,
                    event: 'click',
                    keypress: false,
                    prevent: false,
                    progress: {
                      type: 'text',
                      message: ' ... '
                    },
                };
        Drupal.ajax[dellnkid] = new Drupal.ajax(null, $("#" + dellnkid), settings);

        // Show loading message
        $('article.tab-pane.main-col').html('<div class="region region-content"><div id="block-system-main" class="block block-system"><div class="ajax-progress ajax-progress-throbber" style="display:inline-block;"><div class="throbber">&nbsp;</div></div> Loading ...</div></div>');

        // Click the temp div to initiate Ajax call and remove the facet tile from the list.
        setTimeout(function() {
                $("#" + dellnkid).click();
                $(cid).parent().remove();
                // If the list is empty, hide the div
                if ($('.active-kmfacets-list .facet-item').length == 0) {
                    $('.active-kmfacets-list').hide();

                }
                // can't do this until facet is actually removed from UI
                if ($('#search-block-form .input-group  #kmap_filters_input').length != 0) {
                  $('#search-block-form .input-group  #kmap_filters_input').trigger('change');
                }
        }, 300);

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
              var redirect = ajax.options.url.replace('ajax','nojs');
              console.log("punting to redirect: " + redirect);
                window.location = redirect;

            } catch (err) {
                console.error("Could not process process: " + ajax.options.url);
                console.dir(ajax.options);

              var redirect = ajax.options.url.replace('ajax','nojs');
              console.log("punting to redirect: " + redirect);
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
        Drupal.ajax.prototype.createFacetAction = function (kid) {
            var   kpts = kid.split('-'),
                    app = kpts[0],
                    id = kpts[1],
                    baseUrl = Drupal.settings.basePath,
                    skf = Drupal.settings.shanti_kmaps_facets;

            // append terminal slash if there isn't one.
            if (!/\/$/.test(baseUrl)) {
                baseUrl += "/";
            }
            var pthpts = window.location.pathname.split('/');
            if (debug) { console.log("Window path in Create Facet Action: " + window.location.pathname); }

            if (pthpts.length > 3 && pthpts[3].match(/places|subjects/)) {
                var oldkids = pthpts[3];
                kid = oldkids + "_" + kid;
            }

            if (debug) { console.log("kid string in Create Facet Action: " + kid); }
            var qparams = $.parseJSON(skf.core_search_query);
            var srchp = (skf.core_search) ? '/search/' + qparams['q'] : '';

            var settings = {
                url: baseUrl + "kmaps/facets/" + kid + srchp + '/ajax' ,
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

}) (jQuery);
