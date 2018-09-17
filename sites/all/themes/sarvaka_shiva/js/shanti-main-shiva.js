( function($) {

        /**
         *  Front page tabs
         */
        Drupal.behaviors.shivaCustomGalleries = {
            attach : function(context, settings) {
                if (context == document) {
                    /**
                     * Call wookmark script for custom shiva galleries:
                     * 		.shanti-gallery2 => My Visualizations tab on home page
                     *
                     */
                    /*
                    $('.shanti-gallery2', context).imagesLoaded(function() {
                        // Prepare layout options.
                        var options = {
                            align : 'left',
                            itemWidth : 185, // Optional min width of a grid item
                            autoResize : true, // This will auto-update the layout when the browser window is resized.
                            container : $('.shanti-gallery2'), // Optional, used for some extra CSS styling
                            offset : 12, // Optional, the distance between grid items
                            outerOffset : 0, // Optional the distance from grid to parent
                            flexibleWidth : '35%', // Optional, the maximum width of a grid item
                            ignoreInactiveItems : false,
                        };
                        // Get a reference to your grid items.
                        var handler = $('.shanti-gallery2'); // for wookmark 2.1.2 removed the ' > li ' as initialiazation now requires just the parent.

                        var $window = $(window);
                        $window.resize(function() {
                            console.log('in resize in shiva');
                            var windowWidth = $window.width(), newOptions = {
                                flexibleWidth : '30%'
                            };

                            // Breakpoint
                            if (windowWidth < 1024) {
                                newOptions.flexibleWidth = '100%';
                            }

                            handler.wookmark(newOptions);
                        });

                        // Call the layout function.
                        handler.wookmark(options);
                    });
                    /** End of Wookmark Code **/

                   // Kmap Tags on Vis Page
                   // Show kmap subject or places
                   $(".node-shivanode .vis-kmaps .vis-kmaps-show-link").click(function() {
                       var parentclass = $(this).parent().attr('class');
                       $(".kmap-content:visible").not("." + parentclass).hide();
                       $(".kmap-content." + parentclass).toggle();
                   });
                   // Enable close icon for kmap popover (there)
                   $("a.vis-kmaps-close").click(function() {
                       $(this).parent().hide();
                   });
                   // When click on page outside of kmap popover, close any kmap popover that is open
                   $(".site-banner, .titlearea.banner, .node-shivanode .visualization, .footer").click(function() {
                       $(".kmap-content:visible").hide();
                   });
                   
                   // Remove resize events for create and explore pages
                   if (window.location.pathname.match(/(create|explore)/)) {
                       // Need to use Timeout because it must be set after this sometime.
                       setTimeout(function() {
                           $(window).data("events").resize = null; // Nullify any resize events.
                       }, 1000);
                   }
                   
                   // Call window resize for home page my vis tab to get gallery to kick in
                   $('a#myvis-tab').on('shown.bs.tab', function (e) {$(window).resize();});
                }
            }
        };

        Drupal.behaviors.thumbInsertingCreateIcon = {
            attach : function(context, settings) {
                if (context == document) {
                    $('.sn-create-link a').prepend('<span class="fa fa-pencil"></span>');
                }
            }
        };

        Drupal.behaviors.descriptionTrimming = {
            attach : function(context, settings) {
                if (context == document) {
                    if ($('body').hasClass('node-type-collection') || $('body').hasClass('node-type-subcollection')) {
                        var ps = [];
                        $('.field-name-body .field-item p').each(function() {if ($(this).text().length > 0) { ps.push($(this)); }});
                        var tlen = 0;
                        var ishidden = false;
                        $.each(ps, function(ind, p) {
                            if (tlen > 300) {
                                p.addClass('desctrimmed');
                                p.hide();
                                ishidden = true;
                            }
                            tlen += p.text().length;
                        });
                        if (ishidden) {
                            ps.pop().after('<div class="desc-read-more"><a href="#" class="read-more-link">' + Drupal.t('Show More') + '</a></div>');
                            $('.field-name-body .field-item .desc-read-more a.read-more-link').click(function(e) {
                                e.preventDefault();
                                var txt = $(this).text();
                                if (txt.indexOf('More') > -1) {
                                    $('.field-name-body .field-item p.desctrimmed').show();
                                    $(this).text( Drupal.t('Show Less'))  ;
                                } else {
                                    $('.field-name-body .field-item p.desctrimmed').hide();
                                    $(this).text( Drupal.t('Show More'));
                                }
                            });
                        }
                    }
                }
            }
        };

    }(jQuery)); 