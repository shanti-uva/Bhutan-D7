;(function ($) {
    Drupal.behaviors.kmapsExplorerCustom = {
        attach: function (context, settings) {
            var selectedResource = settings.kmaps_explorer.resource
            var resources = settings.shanti_kmaps_admin.shanti_kmaps_admin_asset_types.concat(
                "overview"
            );
            var resourceNameToCSSClass = function (a) {
                return "kmaps-" + a.replace(/\_/g, "-")
            };
            $("body").removeClass(resources.map(resourceNameToCSSClass).join(" "));
            if (selectedResource) {
                $("body").addClass(resourceNameToCSSClass(selectedResource))
            }

            var $related = $("#sidebar-first > ul.nav-pills > li a")
            $related.click(function () {
                $("#sidebar-first > ul.nav-pills > li").removeClass("active");
                $(this)
                    .parent()
                    .addClass("active")
            });

            //Include index item to breadcrumbs for normal page loads
            if (Drupal.settings.kmaps_explorer) {
                $("ol.breadcrumb li:first-child a").html(
                    Drupal.settings.kmaps_explorer.app + ": "
                )
            } else {
                $("ol.breadcrumb li:first-child a").html("")
            }

            //Functionality for history popstate
            $(window).on("popstate", function (e) {
                if (!e.originalEvent || !e.originalEvent.state || !e.originalEvent.state.tag) return;
                window.location.href = location.href
            });

            //Functionality for popovers
            $(".popover-kmaps", context)
                .not(".kmaps-list-columns.subjects-in-subjects .popover-kmaps")
                .not(".kmaps-list-columns.places-in-places .popover-kmaps")
                .not(".kmaps-list-columns.places-in-subjects .popover-kmaps")
                .each(function () {
                    var $that = $(this);
                    var app = $that.data("app");
                    var kid = $that.data("id");
                    $that.popover({
                        html: true,
                        title: '<span id="pop-title-' + kid + '">Loading ...</span>',
                        trigger: "hover",
                        content:
                        '<span id="pop-content-' +
                        kid +
                        '">Please wait while captions and related assets load. Loading ...</span>'
                    });
                    $that.on("show.bs.popover", function () {
                        $("#pop-title-" + kid, context).html("");
                        $("#pop-content-" + kid, context).html("");
                        $("div.popover").hide();
                        $.get("/mandala/popover/populate/" + app + "/" + kid, function (
                            data
                        ) {
                            //data = $.parseJSON(data);
                            if (data.node) {
                                if (data.node && data.node.header) {
                                    $("#pop-title-" + kid, context).html(data.node.header)
                                }
                                $("#pop-content-" + kid, context).html(
                                    populateSolrPopover(data)
                                )
                            }
                        })
                    })
                });

            //Functionality for visuals individual assets
            $(".node-shivanode .vis-kmaps .vis-kmaps-show-link").mouseenter(function () {
                var parentclass = $(this).parent().attr('class');
                $(".kmap-content:visible").not("." + parentclass).hide();
                $(".kmap-content." + parentclass).toggle();
            });
            // Enable close icon for kmap popover (everywhere)
            $("a.vis-kmaps-close").click(function () {
                $(this).parent().hide();
            });
            // When click on page outside of kmap popover, close any kmap popover that is open
            $(".site-banner, .titlearea.banner, .node-shivanode .visualization, .footer").click(function () {
                $(".kmap-content:visible").hide();
            });

            // Functionality for columnizer
            $(".kmaps-list-columns.places-in-subjects", context).columnize({
                width: 330,
                lastNeverTallest: true,
                buildOnce: true,
                doneFunc: function () {
                    $(".popover-kmaps", context).each(function () {
                        var $that = $(this);
                        var app = $that.data("app");
                        var kid = $that.data("id");
                        $that.popover({
                            html: true,
                            title: '<span id="pop-title-' + kid + '">Loading ...</span>',
                            trigger: "hover",
                            content:
                            '<span id="pop-content-' +
                            kid +
                            '">Please wait while captions and related assets load. Loading ...</span>'
                        });
                        $that.on("show.bs.popover", function () {
                            $("#pop-title-" + kid, context).html("");
                            $("#pop-content-" + kid, context).html("");
                            $("div.popover").hide();
                            $.get("/mandala/popover/populate/" + app + "/" + kid, function (
                                data
                            ) {
                                //data = $.parseJSON(data);
                                if (data.node) {
                                    if (data.node && data.node.header) {
                                        $("#pop-title-" + kid, context).html(data.node.header)
                                    }
                                    $("#pop-content-" + kid, context).html(
                                        populateSolrPopover(data)
                                    )
                                }
                            })
                        })
                    })
                }
            });

            //Functionality for images to add location and id
            $(".related-photos > .modal", context).each(function () {
                var $that = $(this);
                var id = $that.attr("id");
                var pid = $that.data("place");
                $that.on("show.bs.modal", function (e) {
                    var url =
                        Drupal.settings.shanti_kmaps_admin
                            .shanti_kmaps_admin_server_places +
                        "/features/" +
                        pid +
                        ".json";
                    $.get(url, function (data) {
                        $(
                            "#" + id + " .modal-body .image-modal-location .places-loc",
                            context
                        ).html(data.feature.header)
                    })
                })
            });

            function populateSolrPopover(data) {
                //Create markup for related places in images.
                var template = $("#popover-general").html();
                var templateScript = Handlebars.compile(template);
                var html = templateScript(data);
                return html;
            }

            $(".transcripts-ui-search-form", context).once(
                "transcript-search-wrapper",
                function () {
                    var $form = $(this);
                    var trid = $form.attr("data-transcripts-id");
                    var base = "transcript-search-button-" + trid;

                    var element_settings = {
                        url:
                        "http://" +
                        window.location.hostname +
                        settings.basePath +
                        settings.pathPrefix +
                        "system/ajax",
                        event: "click",
                        progress: {
                            type: "throbber"
                        },
                        callback: "transcripts_ui_ajax_hits"
                    };

                    Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);
                    $(this).click()
                }
            );

            //Function to make kmaps relationship tree
            $(".relation_tree_container").kmapsRelationsTree({
                domain: Drupal.settings.kmaps_explorer.domain, //[places, subjects, sources, etc.]
                featureId: Drupal.settings.kmaps_explorer.featureId, //Feature fid of the active node
                //featuresPath: "HTTPS://PATH/TO/NODE/%%ID%%", //This base URL is a pattern with the %%ID%% to be replaced with each node's ID
                featuresPath: Drupal.settings.kmaps_explorer.featuresPath,
                perspective: Drupal.settings.kmaps_explorer.perspective,
                tree: Drupal.settings.kmaps_explorer.tree, //[places,subjects,sources, etc.]
                termIndex: Drupal.settings.kmaps_explorer.termIndex,
                seedTree: {
                    descendants: true, //Show descendants
                    directAncestors: false //Show only direct A
                },
                displayPopup: true,
                mandalaURL:
                    "https://mandala.shanti.virginia.edu/%%APP%%/%%ID%%/%%REL%%/nojs"
            });

            //Function for Summary tab in Places
            var relatedSolrUtils = kmapsSolrUtils.init({
                termIndex: Drupal.settings.kmaps_explorer.termIndex,
                assetIndex: Drupal.settings.kmaps_explorer.assetIndex,
                featureId: Drupal.settings.kmaps_explorer.domain + '-' + Drupal.settings.kmaps_explorer.featureId, //Your featureId will have the format APP-ID(eg. subjects-20, places-637)
                domain: Drupal.settings.kmaps_explorer.domain, //Use the apps name [places|subjects|terms]
                perspective: Drupal.settings.kmaps_explorer.perspective,
                tree: Drupal.settings.kmaps_explorer.domain
            });

            var summaryLoaded = false;
            var collapsibleApplied = false;
            var popupsSet = false;
            var columnizedApplied = false;

            var feature_label = Drupal.settings.kmaps_explorer.title; //Change this to the feature display label
            var feature_path = Drupal.settings.kmaps_explorer.featuresPath; //Change this to your feature path you can use Drupal's mode too, just using %%ID%% to match the pattern

            $('#summary-tab-link[data-toggle="tab"]').on('shown.bs.tab', function (e) {
                //Code for Summary
                if (!summaryLoaded) {
                    $("#relation_details .tab-content-loading").show();
                    relatedSolrUtils.getPlacesSummaryElements().then(function (result) {
                        relatedSolrUtils.addPlacesSummaryItems(feature_label, feature_path, 'parent', result);
                        relatedSolrUtils.addPlacesSummaryItems(feature_label, feature_path, 'child', result);
                        if (!collapsibleApplied) {
                            $('ul.collapsibleList').kmapsCollapsibleList();
                            collapsibleApplied = true;
                        }
                        if (!columnizedApplied) {
                            // Functionality for columnizer
                            $('.kmaps-list-columns:not(.subjects-in-places):not(.already_columnized)').addClass('already_columnized').columnize({
                                width: 330,
                                lastNeverTallest: true,
                                buildOnce: true,
                            });
                            //reapply kmapsCollapsibleList if the element has lost the kmapscollapsibleList plugin
                            //columnizer seems to cause a bug when the clone doesn't keep the events previously assigned
                            $('ul.collapsibleList').each(function () {
                                if (!($(this).data('plugin_kmapsCollapsibleList'))) $(this).kmapsCollapsibleList();
                            });
                            columnizedApplied = true;
                        }
                        if (!popupsSet) {
                            jQuery('#relation_details .popover-kmaps').kmapsPopup({
                                termIndex: Drupal.settings.kmaps_explorer.termIndex,
                                assetIndex: Drupal.settings.kmaps_explorer.assetIndex,
                                featureId: "", //Leave Empty the JavaScript code will obtain it from the data-id of the DOM element
                                domain: Drupal.settings.kmaps_explorer.domain, //Use the apps name [places|subjects|terms]
                                perspective: Drupal.settings.kmaps_explorer.perspective,
                                feature_path: Drupal.settings.kmaps_explorer.featuresPath, //Change this to your feature path you can use Drupal's mode too, just using %%ID%% to match the pattern
                                solrUtils: relatedSolrUtils
                            });
                            popupsSet = true;
                        }
                        $("#relation_details .tab-content-loading").hide();
                        $("#relation_details .collapsible_btns_container").show();
                        summaryLoaded = true;
                    });
                }
            }); // END - Summary Tab on show action

            $('#summary-tab-link-subjects[data-toggle="tab"]').on('shown.bs.tab', function (e) {
                //Code for Summary
                if (!summaryLoaded) {
                    $("#relation_details .tab-content-loading").show();
                    relatedSolrUtils.getSubjectsSummaryElements().then(function (result) {
                        relatedSolrUtils.addSubjectsSummaryItems(feature_label, feature_path, 'parent', result);
                        relatedSolrUtils.addSubjectsSummaryItems(feature_label, feature_path, 'child', result);
                        if (!collapsibleApplied) {
                            $('ul.collapsibleList').kmapsCollapsibleList();
                            collapsibleApplied = true;
                        }
                        if (!columnizedApplied) {
                            // Functionality for columnizer
                            $('.kmaps-list-columns:not(.places-in-subjects):not(.already_columnized)').addClass('already_columnized').columnize({
                                width: 330,
                                lastNeverTallest: true,
                                buildOnce: true
                            });
                            //reapply kmapsCollapsibleList if the element has lost the kmapscollapsibleList plugin
                            //columnizer seems to cause a bug when the clone doesn't keep the events previously assigned
                            $('ul.collapsibleList').each(function () {
                                if (!($(this).data('plugin_kmapsCollapsibleList'))) $(this).kmapsCollapsibleList();
                            });
                            columnizedApplied = true;
                        }
                        if (!popupsSet) {
                            jQuery('#relation_details .popover-kmaps').kmapsPopup({
                                termIndex: Drupal.settings.kmaps_explorer.termIndex,
                                assetIndex: Drupal.settings.kmaps_explorer.assetIndex,
                                featureId: "", //Leave Empty the JavaScript code will obtain it from the data-id of the DOM element
                                domain: Drupal.settings.kmaps_explorer.domain, //Use the apps name [places|subjects|terms]
                                perspective: Drupal.settings.kmaps_explorer.perspective,
                                feature_path: Drupal.settings.kmaps_explorer.featuresPath, //Change this to your feature path you can use Drupal's mode too, just using %%ID%% to match the pattern
                                solrUtils: relatedSolrUtils
                            });
                            popupsSet = true;
                        }
                        $("#relation_details .tab-content-loading").hide();
                        $("#relation_details .collapsible_btns_container").show();
                        summaryLoaded = true;
                    });
                }
            }); // END - Summary Tab on show action

            //Collapse/Expand Button functionality
            $(".collapsible_expand_all").on("click", function (e) {
                $(".collapsible_collapse_all").removeClass("collapsible_all_btn_selected");
                if (!$(".collapsible_expand_all").hasClass("collapsible_all_btn_selected")) {
                    $(".collapsible_expand_all").addClass("collapsible_all_btn_selected");
                }
                $('ul.collapsibleList').each(function () {
                    $(this).kmapsCollapsibleList('expandAll', this);
                });
            });
            $(".collapsible_collapse_all").on("click", function (e) {
                $(".collapsible_expand_all").removeClass("collapsible_all_btn_selected");
                if (!$(".collapsible_collapse_all").hasClass("collapsible_all_btn_selected")) {
                    $(".collapsible_collapse_all").addClass("collapsible_all_btn_selected");
                }
                $('ul.collapsibleList').each(function () {
                    $(this).kmapsCollapsibleList('collapseAll', this);
                });
            });

            //Extend handlebars to support comparison Functionality
            Handlebars.registerHelper("ifCond", function (v1, operator, v2, options) {
                switch (operator) {
                    case "==":
                        return v1 == v2 ? options.fn(this) : options.inverse(this)
                    case "!=":
                        return v1 != v2 ? options.fn(this) : options.inverse(this)
                    case "===":
                        return v1 === v2 ? options.fn(this) : options.inverse(this)
                    case "!==":
                        return v1 !== v2 ? options.fn(this) : options.inverse(this)
                    case "<":
                        return v1 < v2 ? options.fn(this) : options.inverse(this)
                    case "<=":
                        return v1 <= v2 ? options.fn(this) : options.inverse(this)
                    case ">":
                        return v1 > v2 ? options.fn(this) : options.inverse(this)
                    case ">=":
                        return v1 >= v2 ? options.fn(this) : options.inverse(this)
                    case "&&":
                        return v1 && v2 ? options.fn(this) : options.inverse(this)
                    case "||":
                        return v1 || v2 ? options.fn(this) : options.inverse(this)
                    default:
                        return options.inverse(this)
                }
            });

            //Extend handlebars to support increment function
            Handlebars.registerHelper("inc", function (value, options) {
                return parseInt(value) + 1
            });

            //Capitalize first letter
            Handlebars.registerHelper("capitalizeFirstLetter", function (str) {
                return str.charAt(0).toUpperCase() + str.slice(1)
            });

            //Extract id from solr id
            Handlebars.registerHelper("extractId", function (str) {
                if ($.type(str) === "string" && str.includes("-")) {
                    return str.split("-").pop();
                } else {
                    return "UNKNOWN";
                }
            })
        }
    }
})(jQuery);
