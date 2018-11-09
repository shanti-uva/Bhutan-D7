(function ($) {
	Drupal.behaviors.shantiGridView = {
	    attach: function (context, settings) {
            if ($("#ppg-grid").length > 0) {
              // Reset pig is set in kmaps_views_solr.js to reset the pig grid after ajax load
              if (settings.shanti_grid_view.resetpig === true) {
                settings.shanti_grid_view.mypig = '';
                settings.shanti_grid_view.resetpig = false;
              }
              // When resetting pig grid, if new data array is shorter than last the leftover doesn't get written over
              // so need to trim the data array
              if (typeof(settings.shanti_grid_view.imgdatalen) != "undefined") {
                var datalen = settings.shanti_grid_view.imgdatalen;
                if (!isNaN(datalen) && datalen > 0) {
                  settings.shanti_grid_view.imgdata = settings.shanti_grid_view.imgdata.slice(0, datalen);
                }
              }

              if (typeof(Drupal.settings.shanti_grid_view.mypig) !== "object") {
                  Drupal.settings.shanti_grid_view.mypig = new Pig(Drupal.settings.shanti_grid_view.imgdata, {
                    containerId: 'ppg-grid',
                    entityType: Drupal.settings.shanti_grid_view.entity_type,
                    primaryImageBufferHeight: 10000,
                    secondaryImageBufferHeight: 10000,
                    urlForSize: function (filename, size, rotation) {
                      var url = Drupal.settings.shanti_grid_view.url_for_size;
                      // Adjust url if file is on prod iiif server by removing '-test';
                      if (filename.match(/shanti-image-(stage-)?\d+/)) {
                          url = url.replace('-test','');
                      }
                      if (typeof(size) == 'undefined') {
                        size = '300';
                      }
                      if (typeof(rotation) != 'undefined') {
                        url = url.replace('_/0/default', '_/' + rotation + '/default');
                      }
                      size = size.toString();

                      return url.replace('__FNAME__', filename).replace(/__SIZE__/g, size);
                    },
                    getImageSize: function (lastWindowWidth) {
                      if (lastWindowWidth <= 640)
                        return 170;
                      else if (lastWindowWidth <= 1920)
                        return 180;
                      return 180;
                    },
                    getMinAspectRatio: function (lastWindowWidth) {
                      if (lastWindowWidth <= 640)
                        return 3;
                      else if (lastWindowWidth <= 800)
                        return 4;
                      else if (lastWindowWidth <= 1280)
                        return 6;
                      else if (lastWindowWidth <= 1600)
                        return 8;
                      else if (lastWindowWidth <= 1920)
                        return 11;
                      return 12;
                    },
                  }).enable().activatePopdown();

                  // For data source views need to add the name fo the view to the info url.
                  if (typeof(Drupal.settings.shanti_grid_view.view_name) == "string"
                      && Drupal.settings.shanti_grid_view.view_name != "") {
                    Drupal.settings.shanti_grid_view.mypig.ppdSettings.infoURL += '/' + Drupal.settings.shanti_grid_view.view_name;
                  }

          } // end if my pig is not an object

              // Load Photoswipe
          if ($('#pswpdiv').length == 0) {
            $('body').append('<div id="pswpdiv" style="display: none;"></div>');
            var path = Drupal.settings.basePath + 'sites/all/modules/custom/shanti_general/modules/shanti_grid_view/';
            // Load the template
            var templurl = path + 'templates/photoswipe-template.html';
            $('#pswpdiv').load(templurl, function () {
              // Load pswp JS sequentially
              var scripturl = path + 'js/photoswipe.js';
              $.getScript(scripturl, function () {
                var scripturl = path + 'js/photoswipe-ui-default.js';
                $.getScript(scripturl, function () {
                  // Enable pswp link click
                  $(document).on('click', '.pswp-link', function () {
                    $('#pswpdiv').show();
                    gridViewOpenPhotoswipe();
                  });
                });
              });
            });
          } // end load photoswipe

          // Document only calls
          if (context == document) {
            // Scrolling listener to load further images in a pig gallery
            window.lastpigload = 0; // keep track of window y offset when last loaded to not run with each pixel change
            $(window).scroll(function() {
                var yoff = window.pageYOffset;
                var diff = yoff - window.lastpigload;
                // When scrolled difference is more than 50 pixels, go through and load images in view
                if (Math.abs(diff) > 50) {
                    var imgs = Drupal.settings.shanti_grid_view.mypig.images;
                    // Run show routine on each image in gallery
                    $(imgs).each(function() {
                        this.show();  // Images only show when in viewport.
                    });
                    window.lastpigload = yoff;  // remember this Y offset
                }
            });

            /* Load rest of thumbnails not in view */
              /*  This slows down the loading still because it doesn't happen outside the load somehow
            $(document).ready(setTimeout(function() {
                var ct = 0;
                $.each(Drupal.settings.shanti_grid_view.mypig.images,
                    function() {
                        if (this.element.childElementCount === 0) {
                            this.thumbnail = new Image();
                            this.thumbnail.src = this.pig.settings.urlForSize(this.filename, this.pig.settings.thumbnailSize, this.rotation);
                            this.thumbnail.className = this.classNames.thumbnail;
                            this.thumbnail.onload = function() {

                                // We have to make sure thumbnail still exists, we may have already been
                                // deallocated if the user scrolls too fast.
                                if (this.thumbnail) {
                                    this.thumbnail.className += ' ' + this.classNames.loaded;
                                }
                            }.bind(this);

                            this.getElement().appendChild(this.thumbnail);
                            this.show();
                        }
                    });
            }, 5000));
            */


            // Enable mouseover overlays on images in grid
            $(document).on('mouseover', 'img.pig-loaded', function () {
              $('.justopen').removeClass('justopen').fadeOut();
              $(this).next('.img-footer-overlay').addClass('justopen').fadeIn();
            });

            $(document).on('mouseleave', '#ppg-grid', function () {
              $('.img-footer-overlay').fadeOut();
            });

          } // End document only calls
        } // End if there is ppd-grid
      }
	};


  /**
   * Opens photoswipe lightbox for an image. Genurls and imgratios are set in shanti_images_preprocess_node() function in shanti_images.module
   */
  function gridViewOpenPhotoswipe() {
      var pswidth = 2500;
      var pswpElement = document.querySelectorAll('.pswp')[0];
      var imgind = (typeof(Drupal.settings.shanti_grid_view) == 'undefined' || isNaN(Drupal.settings.shanti_grid_view.mypig.ppdIndex)) ? 0 : Drupal.settings.shanti_grid_view.mypig.ppdIndex;
      var imgurl = Drupal.settings.shanti_grid_view.imgdata[imgind].lgimgurl;
      var ratio = Drupal.settings.shanti_grid_view.imgdata[imgind].aspectRatio;
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
	    
}) (jQuery);





