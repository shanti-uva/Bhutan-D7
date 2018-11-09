(function ($) {
    Drupal.behaviors.shantiImagesGeneral = {
        attach: function (context, settings) {
            if(context == document) {
                
                // Call image page init if it is an image page
                if ($('body').hasClass('node-type-shanti-image') && !$('body').hasClass('.page-node-edit')) { shanti_images_pages_init(settings); }
                // Activate Bootstrap Popovers
                if(typeof($('[data-toggle="popover"]').popover) == "function") {    
                    $('[data-toggle="popover"]').popover();
                }
                
                // Add target=_blank to not in-house links
                $('.shanti-long-text a, .shanti-image-description a').each(function() {
                    var href = $(this).attr('href');
                    if (href.charAt(0) != '#' && ~href.indexOf('http')) {
                        if (!~(href.indexOf('shanti.virginia'))) {
                            $(this).attr('target', '_blank');
                        }
                    }
                });
                
                // Trimmed Desc more links
                $('.shanti-long-text .trimmed .morelink').click(function(e) {
                    e.preventDefault();
                    var parent = $(this).parents('.trimmed').eq(0);
                    parent.find('.trimmed-text').hide();
                    parent.find('.full-text').slideDown(800).css('display', 'inline');
                    return false;
                });
                $('.shanti-long-text .trimmed .lesslink').click(function(e) {
                    e.preventDefault();
                    var parent = $(this).parents('.trimmed').eq(0);
                    parent.find('.full-text').slideUp();
                    parent.find('.trimmed-text').show();
                    return false;
                });


                // Perform JS for Image Node Pages
                if ($('body').is('.node-type-shanti-image, .page-gallery, .collection-page')) {
                    // Load Photoswipe components for image pages
                    $('body').append('<div id="pswpdiv" style="display: none;"></div>');
                    // adding animated horizontal preloader
                    $('.pswp__preloader').prepend('<span class="loading-horizontal"></span>');
                    var path = Drupal.settings.basePath + 'sites/all/themes/sarvaka_images/js/contrib/';
                    // Load the template
                    var templurl = path + 'photoswipe-template.html';
                    $('#pswpdiv').load(templurl, function() {
                        // Load pswp JS sequentially
                        var scripturl = path + 'photoswipe.js';
                        $.getScript(scripturl, function() {
                            var scripturl = path + 'photoswipe-ui-default.js';
                            $.getScript(scripturl, function() {
                                // Enable pswp link click
                                $(document).on('click', '.pswp-link', function() {
                                    $('#pswpdiv').show(); 
                                    openPhotoswipe(); 
                                });
                            });
                        });
                    });
                    
                    // Enable Key Events for images page
                    document.addEventListener('keydown', function(e) {
                        switch (e.key) {
                            // Previous Image
                            case "ArrowLeft":
                                if (typeof(document.sliderGoTo) == 'function') {
                                    document.sliderGoTo('prev');
                                }
                                break;
                                
                            // Next Image
                            case "ArrowRight":
                                if (typeof(document.sliderGoTo) == 'function') {
                                    document.sliderGoTo('next');
                                }
                               break;
                               
                           // Back
                           case "Escape":
                               window.location.pathname= $('.backarrow a').attr('href');
                               break;
                       }
                   });
                }

                
                // Add destination to create link when not logged in
                if ($("body").is(".not-logged-in")) {
                    var lnk = $('a[href="/saml_login"]:contains("Create")');
                    var href = lnk.attr('href');
                    href += '?destination=node/add/shanti-image';
                    lnk.attr('href', href);
                }

                // Deal with fssolo with no carousel. Add attribute to image-detail so title can be adjusted
                if ($('#fsslider').hasClass('fssolo')) {
                    $('aside.image-detail-wrapper').addClass('nocarousel');
                }

                /*
                setTimeout(function() {
                    var biurl = Drupal.settings.shanti_sarvaka.broken_image_icon_url;
                    $('#ppg-grid img').not(".pig-loaded").each(function () {
                        $(this).attr('data-orig', $(this).attr('src'))
                        $(this).attr('src', biurl);
                        if ($(this).hasClass('pig-thumbnail')) { $(this).hide(); }
                    });
                }, 10000);
                */
            }
        }
    };


    /**
     * Behaviors for Edit Pages
     */
    Drupal.behaviors.shantiImagesEdit = {
        attach: function (context, settings) {
            if(context == document) {
               // When adding file via ajax check for the thumbnail. if it's a .tif replace with generic tiff icon
               if (window.location.href.match('node/add') || window.location.href.match('/edit')) {
                    $('img').each(function() {
                        var url = $(this).attr('src').split('?')[0].split('.');
                        var ext = url.pop().toLowerCase();
                        if (['tif', 'tiff'].indexOf(ext) > -1) {
                            $(this).attr('src', '/sites/all/themes/sarvaka_mages/images/tiff.png');
                        } else if (ext == 'jp2') {
                            $(this).attr('src', '/sites/all/themes/sarvaka_mages/images/images/jp2.png');
                        } else if (['png', 'jpg', 'gif'].indexOf(ext) == -1) {
                            console.log("shanti_images.js: Extension not found: " + ext, $(this));
                        }
                    });
                }
            }
        }
    };
        
        
    /**
     * Drupal behaviors for creating the IIIF viewer (SeaDragon)
     */
    Drupal.behaviors.shantiImagesIIIF = {
        attach: function (context, settings) {
            if(context == document && $('body').is('.node-type-shanti-image')) {
                if (typeof(Drupal.settings.shanti_images) != "undefined") {
                    Drupal.settings.shanti_images.sdselectors = '#sddiv, #iiiftools, .sdwrapper';
                }
                // Close IIIF Viewer on pressing of Escape Button
                $(document).keyup(function(e) {
                     if (e.keyCode == 27 && $('.sdwrapper').is(":visible")) { // escape key maps to keycode `27`
                        $(Drupal.settings.shanti_images.sdselectors).fadeOut(400, function() {Drupal.settings.shanti_images.sdviewer.viewport.goHome(true);});
                    }
                });
                
                // Add Div for Seadragon
                $('section.image-display').append('<div class="sdwrapper" style="display: none;"><div id="iiiftools"></div><div id="sddiv" style="display: none;"></div></div>');
                // IIIF icon in top bar of image page
                // mark removed for testing Nov 2 using icon not image ---
            //    $('.image-actions .iiif-icon').mouseover(function() {
            //        $(this).attr('src', $(this).attr('src').replace('grey', 'white'));
            //    }).mouseout(function() {
            //        $(this).attr('src', $(this).attr('src').replace('white', 'grey'));
            //    });
                
                // Delay loading of SeaDragon JS. Then implement button to open IIIF viewer
                setTimeout(function() {
                    $.getScript('/sites/all/themes/sarvaka_images/js/contrib/openseadragon.min.js', function() {
                            $('.image-actions .iiif-icon').click(function() {
                                var sddiv = $('#sddiv');
                                var rotation = 0;
                                if (typeof(Drupal.settings.shanti_images) != "undefined") {
                                    rotation = parseInt(Drupal.settings.shanti_images.rotation);
                                    if (rotation > 180) { rotation = ((360 - rotation) % 360) * -1; }
                                }
                                var is_series = false;
                                if (typeof(Drupal.settings.shanti_images.sdviewer) == 'undefined') {
                                    Drupal.settings.shanti_images.sdviewer = OpenSeadragon({
                                        id:                              'sddiv',
                                        prefixUrl:                    "/sites/all/themes/sarvaka_images/images/openseadragon/",
                                        preserveViewport:       false,
                                        visibilityRatio:             1,
                                        minZoomLevel:            -1,
                                        maxZoomLevel:           25,
                                        defaultZoomLevel:       2,
                                        degrees:             rotation,
                                        showRotationControl:  true,
                                        showNavigator:            true,
                                        navigatorPosition:        "ABSOLUTE",
                                        navigatorTop:              45,
                                        navigatorLeft:              window.innerWidth - 200,
                                        navigatorHeight:          150,
                                        navigatorWidth:            200,
                                        sequenceMode:           is_series,
                                        zoomPerScroll:            1.08,
                                        zoomPerSecond:         2.0,
                                        toolbar:                      "iiiftools",
                                        homeFillsViewer:         true,
                                        tileSources:                 Drupal.settings.shanti_images.infourls
                                    });
                                }
                                $(Drupal.settings.shanti_images.sdselectors).fadeIn();
                                Drupal.settings.shanti_images.sdviewer.viewport.goHome(true);
                                if ($('#sdclose').length == 0 ) {
                                    $('#iiiftools').append('<div id="sdclose" title="Close" style="background: none transparent; float: right; padding-right: 100px; border: none; margin: 0px; padding: 0px; position: relative; touch-action: none; display: inline-block;"><img src="/sites/all/themes/sarvaka_images/images/openseadragon/close_rest.png" alt="Zoom in" style="background: none transparent; border: none; margin: 0px; padding: 0px; position: static;"><img src="/sites/all/themes/sarvaka_images/images/openseadragon/close_grouphover.png" alt="Zoom in" style="background: none transparent; border: none; margin: 0px; padding: 0px; position: absolute; top: 0px; left: 0px; opacity: 0;"><img src="/sites/all/themes/sarvaka_images/images/openseadragon/close_hover.png" alt="Zoom in" style="background: none transparent; border: none; margin: 0px; padding: 0px; position: absolute; top: 0px; left: 0px; visibility: hidden;"><img src="/sites/all/themes/sarvaka_images/images/openseadragon/close_pressed.png" alt="Zoom in" style="background: none transparent; border: none; margin: 0px; padding: 0px; position: absolute; top: 0px; left: 0px; visibility: hidden;"></div>');
                                }
                                
                                $('#sdclose').click(function() {
                                    $(Drupal.settings.shanti_images.sdselectors).fadeOut(400, function() {Drupal.settings.shanti_images.sdviewer.viewport.goHome(true);});
                                });
                            });
                    });
                }, 1000);
            }
        }
    };
    
    /**
     * Function called to initialize a shanti_image page
     */
    function shanti_images_pages_init(settings) {
        shanti_images_page_slider_init(settings);
        shanti_images_page_columns_init();
        shanti_images_page_download_init();
    }
    
    /**
     * Initiate the carousel slider for thumbnails from source gallery and a faux slider for the image itself to provide forward and back arrows
     */
    function shanti_images_page_slider_init(settings) {
        // Set Variables
        var moveNum = 3; // number of images to move in carousel on arrow click
        // picInd is the index of the current image in the gallery list of images
        var picInd = (typeof(settings.shanti_images) == 'undefined' || typeof(settings.shanti_images.flexindex) == 'undefined') ? 0 : parseInt(settings.shanti_images.flexindex);
        startInd = Math.floor(picInd / moveNum); // startInd is the index to start carousel (far left visible image)
        if (startInd > 0) { startInd -= 1; } // center the selected image in the carousel
        
        // Define document function sliderGoTo that can be accessed outside of this function for button clicks
        // Loads the page for the previous or next image in the carousel, called by the main images slider clicks
        document.sliderGoTo = function(dir) {
            var slide = $('#fscarousel .flex-active-slide');
            var href = false;
            if (dir === 'prev') {
                slide.prev().find('img').hide();
                href = slide.prev().find('a').attr('href');

            } else {
                slide.next().find('img').hide();
                href = slide.next().find('a').attr('href');
            }
            window.location.href = href;
        };
        if ($('#fsslider').length > 0) {
          // Initiate faux slider for image (this creates the forward/backward arrows)
          // the previous and next slides are empty, uses before callback to load new image
          var mainInd = ($('#fsslider ul.slides li').length > 1 && picInd != 0) ? 1 : 0;
          $('#fsslider').flexslider({
            animation: "fade",
            controlNav: false,
            slideshow: false,
            startAt: mainInd,
            maxItems: 1,
            move: 1,
            before: function(slider) {
              // before changing the slider image call the function to load the previous or next image depending on direction
              document.sliderGoTo(slider.direction);
            }
          });
        }

        // Lower image title until carousel is loaded
        $('header.image-title').css('top', '-70px');

        // Initialize the Mutation Observer to place on the main image div to observe when that image is loaded
        // When it's class goes from "progressive preview" to "progressive" then the main image is loaded and we can load the carousel
        var divobserver = new MutationObserver(function(mutations) {
            mutations.forEach(function(mutation) {
                // Look for the attribute class (initially this is "progressive preview")
                if (mutation.attributeName === "class") {
                    var attributeValue = $(mutation.target).prop(mutation.attributeName);
                    // When the class gets changed to just "progressive"...
                    if (attributeValue === "progressive") {
                        shanti_images_page_load_carousel(settings);  // See below
                    }
                }
            });
        });

        // Add the Observer to the Main Progressive Image Div
        $div = $('div.progressive');
        divobserver.observe($div[0], {
            attributes: true
        });

        /*
          // If current image in carousel is first or last, hide the corresponding arrow
          if ($('.flex-active-slide').prev('li').length == 0) {
              $('.flex-nav-prev').hide();
          }
          if ($('.flex-active-slide').next('li').length == 0) {
              $('.flex-nav-next').hide();
          }
         */

          $('.flexslider a:not(.flex-nav-prev > a)').click(function() {
            $('.preloading-horizontal,.image-preloading-text').css('display','block');
          });


          // wraps flexslideshow image w/anchor element, and displays icon for expand in center of image
          $('#fsslider .flex-active-slide img').parent().wrap('<a href="#" class="pswp-link" title="Fullscreen Image Viewer"></a>');
          $('#fsslider .flex-active-slide  .pswp-link').hover(function () {
              $(this).prepend('<span class="fa fa-arrows-alt"></span>');
              $('#fsslider .fa-arrows-alt').fadeIn(5000);
            },
            function () {
              $('#fsslider .fa-arrows-alt').remove();
            }
          );

   }

   function shanti_images_page_load_carousel(settings) {
       // Create a loading div and load the carousel into it. Using API to get slides
       settings.shanti_images.loading_slides = false;
       $('body').append('<div id="fscaroload" class="hidden" style="display:none;"></div>');
       $('#fscaroload').load('/api/carouseldata/' + settings.shanti_images.nid, function() {
           // Move the carousel div into place where the placeholder is
           var carousel = $('#fscarousel').detach();
           $('#fscarousel-placeholder').replaceWith(carousel);
           $('#fscaroload').remove(); // remove placeholder

           // Initialize carousel
           $('#fscarousel').flexslider({
               animation: "slide",
               controlNav: false,
               animationLoop: false,
               slideshow: false,
               itemWidth: 90,
               itemMargin: 5,
               move: 3
           });

           var slider = $('#fscarousel').data('flexslider');
           slider.flexAnimate(3, false, true, false);

           // Readjust header title with carousel loaded
           $('header.image-title').css('top', '-160px');

           // Set up ajax loading of further slides
           settings.shanti_images.carousel_coll = $('#fscarousel').data('collid');
           settings.shanti_images.carousel_start = $('#fscarousel').data('start');

           // Watch for hovering on first to show Prev arrow to initial ajax loading of more slides
           $('#fscarousel .slides').on('hover', 'li:first-child', function() {
               $('#fscarousel .flex-prev').removeClass('flex-disabled');
           });

           // Watch for hovering on first to show Prev arrow to initial ajax loading of more slides
           $('#fscarousel .slides').on('hover', 'li:last-child', function() {
               if (!$('#fscarousel .flex-next').hasClass('loaded')) {
                   $('#fscarousel .flex-next').removeClass('flex-disabled');
               }
           });

           // Load more slides if at the beginning
           $('#fscarousel').on('mouseup', '.flex-prev', function(e) {
               var slider = $('#fscarousel').data('flexslider');
               if (slider.currentSlide === 1 && !settings.shanti_images.loading_slides ) {
                   e.stopImmediatePropagation();
                   settings.shanti_images.loading_slides = true;
                   var num_to_load = 30;
                   var collid = settings.shanti_images.carousel_coll;
                   var start = settings.shanti_images.carousel_start - num_to_load;
                   settings.shanti_images.carousel_start = start;
                   $.ajax({
                       url: '/api/carouseldata/slides/' + collid + '/' + start + '/' + num_to_load,
                       success: function(data) {
                           var slider = $('#fscarousel').data('flexslider');
                           var slides = $(data);
                           var slen = slides.length;
                           // add slides in reverse order to front of carousel
                           for (var n=slen-1; n>-1; n--) {
                               var slide = slides.eq(n);
                               slider.addSlide(slide, 0);
                           }

                           slider.currentSlide = 0;
                           slider.flexAnimate(10, false, true, false);

                           setTimeout(function() {
                               settings.shanti_images.loading_slides = false;
                           }, 500);
                       }
                   });
               }
           });

           $('#fscarousel').on('mouseup', '.flex-next', function(e) {
               var slider = $('#fscarousel').data('flexslider');
               if (slider.currentSlide >= (slider.pagingCount - 2) && !settings.shanti_images.loading_slides ) {
                   e.stopImmediatePropagation();
                   settings.shanti_images.loading_slides = true;
                   var num_to_load = 30;
                   var slides_per_page = 3;
                   var collid = settings.shanti_images.carousel_coll;
                   var start = settings.shanti_images.carousel_start + slider.count;
                   settings.shanti_images.carousel_start = start;
                   $.ajax({
                       url: '/api/carouseldata/slides/' + collid + '/' + start + '/' + num_to_load,
                       success: function(data) {
                           if (data === 'END') {
                               $('#fscarousel .flex-next').addClass('flex-disabled loaded');
                               settings.shanti_images.loading_slides = false;
                               return;
                           }
                           var slider = $('#fscarousel').data('flexslider');
                           var slides = $(data);
                           var slen = slides.length;
                           var addind = slider.count - 1;
                           // add slides in reverse order to front of carousel
                           for (var n=0; n<slen; n++) {
                               var slide = slides.eq(n);
                               slider.addSlide(slide, addind + n);
                           }
                           var newslide = Math.floor(slider.count / slides_per_page) - Math.floor(num_to_load / slides_per_page) - 1;
                           slider.flexAnimate(newslide, false, true, false);

                           setTimeout(function() {
                               settings.shanti_images.loading_slides = false;
                           }, 500);
                       }
                   });
               }
           });
       });
   }
          
   /**
    * Initiate columns for image page details
    */
   function shanti_images_page_columns_init() {
      /**** Init Columnizer for more-details ******/
      // First move out kmaps popovers
      $('body').append('<div id="kmpostemp" style="height: 0px; display: none; visibility: none;"></div>');
      var kct = 0;
      $('.detail-columns .ppltemp').each(function() {
          kct +=1;
          var kmpoid =  'kmpo-' + kct;
          $(this).attr('data-kmpoid', kmpoid);
          $('#kmpostemp').append('<div id="' + kmpoid + '"></div>');
          var kmpo = $(this).next('.pptemp').detach();
          $('#' + kmpoid).append(kmpo);
      });
      if ( $('.detail-columns').length > 0 ) {
          $('.detail-columns').find('p, table, thead, tbody, tfoot, colgroup, caption, label, legend, script, style, textarea, button, object, embed, tr, th, td, li, h1, h2, h3, h4, h5, h6, form').addClass('dontsplit');
          $('.detail-columns').find('h1, h2, h3, h4, h5, h6').addClass('dontend');
          // Turn paragraphs in note field markup into sublists for display purpose in Image Notes, Technical Notes, etc.
          $('.detail-columns span.field-items span').each(function() {
              if ($(this).find('p').length > 0) {
                  var newmup = $('<ul class="note-list"></ul>');
                  $(this).find('p').each(function() {
                      newmup.append('<li>' + $(this).html() + '</li>');
                  } );
                  $(this).after(newmup);
                  $(this).remove();
              }
          });
          $('.detail-columns').columnize({ 
              // columns: 2,
              width:470,
              lastNeverTallest: true,
              buildOnce: false,
              doneFunc: function() {
                  $('.detail-columns > .column').each(function() {
                      $(this).html('<div class="column-inner">' + $(this).html() + '</div>');
                  });
                  $('.detail-columns .ppltemp').each(function() {
                         $(this).removeClass('ppltemp');
                         $(this).addClass('popover-link');
                         var poid = $(this).attr('data-kmpoid');
                         var po = $('#' + poid);
                         $(this).after(po.html());
                   });
                  $('.detail-columns .pptemp').each(function() {
                         $(this).removeClass('pptemp');
                         $(this).addClass('popover');
                   });
                   Drupal.attachBehaviors('.detail-columns');
                   $('#kmpostemp').remove();
              }
          });
      }
      $('.kmap-items').fadeIn();
   }
   
   /** 
    * Fallback for HTML 5 download attributes
    * See https://webdesign.tutsplus.com/tutorials/quick-tip-using-the-html5-download-attribute--cms-23880
    */
    function shanti_images_page_download_init() {
        if ( ! Modernizr.adownload ) {
            var $link = $('a');
            $link.each(function() {
                var $download = $(this).attr('download');
                if (typeof $download !== typeof undefined && $download !== false) {
                    var $el = $('<div>').addClass('download-instruction').text('Right-click and select "Download Linked File"');
                    $el.insertAfter($(this));
                }
            });
        }
    }
    
    /**
     * Opens photoswipe lightbox for an image. Genurls and imgratios are set in shanti_images_preprocess_node() function in shanti_images.module
     */
    function openPhotoswipe() {
        var pswidth = 2500;
        var pswpElement = document.querySelectorAll('.pswp')[0];
        var imgind = (typeof(Drupal.settings.shanti_grid_view) == 'undefined' || isNaN(Drupal.settings.shanti_grid_view.mypig.ppdIndex)) ? 0 : Drupal.settings.shanti_grid_view.mypig.ppdIndex;
        var imgurl = Drupal.settings.shanti_images.genurls[imgind].replace('__W__', pswidth).replace('__H__','');
        var ratio = Drupal.settings.shanti_images.imgratios[imgind] * 1;
        var items = [
            {
                src: imgurl,
                w: pswidth,
                h: Math.floor(pswidth / ratio),
            },
        ]; // end of items
        var options = {
            index: 0 // start at first slide
        };

        // Initializes and opens PhotoSwipe
        var gallery = new PhotoSwipe( pswpElement, PhotoSwipeUI_Default, items, options);
        gallery.listen('close', function() { $('#pswpdiv').hide(); });
        gallery.init();
    }
    
    /**
     * Cultural Landscapes Overrides
     */
    Drupal.behaviors.shantiImagesCLOverrides = {
        attach: function (context, settings) {
            if(context == document) {
                /*
                 * Cultural Landscape is a faux collection. The images are part of the sharedshelf module. 
                 * The cultural landscape project page is redirected to the shared shelf media item page. Only the teaser is used to display in the collections views
                 * There will not be further development in regard to the shared shelf media and no further will be added. 
                 * There are a fixed number of these items in the Cultural Landscape page. That number is 67.
                 * For the cultural landscapes collection tile change "0 items" to "67 items"
                 */
                if ($("body").is('.page-collections, .page-mycontent-collections')) {
                    var liel = $('a[href*=cultural-landscapes]').eq(0).parents('li').eq(0);
                    liel.find('.shanti-field-itemcount .shanti-field-content').eq(0).text('67 items');
                }
            }
        }
    };
    
}) (jQuery);





