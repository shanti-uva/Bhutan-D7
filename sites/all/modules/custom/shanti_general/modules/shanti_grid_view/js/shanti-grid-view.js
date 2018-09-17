(function ($) {
	Drupal.behaviors.shantiGridView = {
	    attach: function (context, settings) {
			if(context == document) {
				if ($("#ppg-grid").length > 0) {
					 Drupal.settings.shanti_grid_view.mypig = new Pig(Drupal.settings.shanti_grid_view.imgdata, {
                            containerId: 'ppg-grid',
                            entityType: Drupal.settings.shanti_grid_view.entity_type,
                            primaryImageBufferHeight: 10000,
                            secondaryImageBufferHeight: 10000,
                            urlForSize: function(filename, size, rotation) {
                                var url = Drupal.settings.shanti_grid_view.url_for_size;
                                if (typeof(size) == 'undefined') { size = '300'; }
                                if (typeof(rotation) != 'undefined') {
                                    url = url.replace('_/0/default', '_/' + rotation + '/default');
                                }
                                size = size.toString();
                                return url.replace('__FNAME__', filename).replace(/__SIZE__/g, size);
                            },
                            getImageSize: function(lastWindowWidth) {
                                if (lastWindowWidth <= 640)
                                  return 120;
                                else if (lastWindowWidth <= 1920)
                                  return 160;
                                return 180;
                            },
                            getMinAspectRatio: function(lastWindowWidth) {
                                if (lastWindowWidth <= 640)
                                  return 3;
                                else if (lastWindowWidth <= 1280)
                                  return 9;
                                else if (lastWindowWidth <= 1920)
                                  return 13;
                                return 18;
                            },
                        }).enable().activatePopdown(); 
                        
                      // Enable mouseover overlays on images in grid
                      $(document).on('mouseover', 'img.pig-loaded', function() {
                          $(this).next('.img-footer-overlay').fadeIn();
                      });
                      $(document).on('mouseleave', 'img.pig-loaded', function() {
                          $(this).next('.img-footer-overlay').fadeOut();
                      });   
				}
			} 
	    }
	};
	    
}) (jQuery);





