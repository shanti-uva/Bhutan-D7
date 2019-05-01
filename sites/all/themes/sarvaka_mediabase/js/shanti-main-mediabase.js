(function ($) { // jQuery wrapper function

  // *** Common Functions for Shanti Mediabase ***
  Drupal.ShantiMediabase = {};

  /*
   * 2017-03-03: Modified to factor in height of facets and use 'extopen' event.
   * 2017-01-25: Removed because it made the facet tree scroll to bottom every time item was expanded
   * See also Drupal.behaviors.searchPanelHeightKMaps in shanti-main-kmaps.js
   */
  Drupal.behaviors.searchPanelHeightAV = {
    attach: function (context, settings) {
      if (context == document) {
        var $extruder = $('#search-flyout .extruder-content');
        var $kmfacets = $('#kmfacet-list');

        Drupal.ShantiMediabase.searchTabHeight = function (e) {
          if ($extruder.css('display') == 'block') {
            var kmfacets_height = $kmfacets.find('.facet-item').length == 0 ? 0 : $kmfacets.innerHeight();
            var view_height = $extruder.innerHeight() - kmfacets_height - 167;
            $('.km-facet-div > div').css('height', view_height + 'px'); // input_height = 100, tab_height = 60, facets_margins = 12
          }
        };
        $(window).bind('load orientationchange resize', Drupal.ShantiMediabase.searchTabHeight);
        $('#search-flyout').on('extopen', Drupal.ShantiMediabase.searchTabHeight);
        $('#search-block-form .input-group').on('change', 'input[name=kmap_filters]', Drupal.ShantiMediabase.searchTabHeight);

        // prevent overscrolling into body
        $('.km-facet-div > div').scrollLock();
      }
    }
  };

	// Move the dom-id class so that the view block reloads all content and so does not duplicate filters, pager, etc.
	Drupal.behaviors.shanti_sarvaka_mb_bef_mainpage = {
		attach: function (context, settings) {
			domid = $('.shanti-view-dom-id').attr('data-dom-id');
			$("div.view-dom-id-" + domid).removeClass("view-dom-id-" + domid);
			$('.shanti-view-dom-id').addClass("view-dom-id-" + domid);
		}
	};


	// Various Markup changes for styling MB in sarvaka theme
	Drupal.behaviors.shantiSarvakaMbMarkupTweaks = {
		attach: function (context, settings) {
			if(context == window.document) {
				$('#edit-group-audience .form-item-group-audience-und', context).once('aveditcollaud').wrapInner('<div class="collection-details-audience"></div>');
				$('.collection-details-audience').once('aveditcollaud2').before($('.collection-details-audience > label').detach());
				$('#edit-group-audience .form-item-group-audience-und > label, #edit-field-subcollection > label').once('aveditsubcoll').prepend('<span class="icon shanticon-stack"></span> ');
                                $('#edit-field-transcript .form-item-field-transcript-und-0 > label').once('avedittrans').prepend('<span class="icon shanticon-comments-o"></span> ');
				$('#edit-field-characteristic > label').once('aveditsubjects').prepend('<span class="icon shanticon-subjects"></span> ');
				$('#edit-field-pbcore-coverage-spatial > label').once('aveditspatial').prepend('<span class="icon shanticon-places"></span> ');
				// Show more language descriptions
				if( $('.avpbcoredesc .field-item .content > .hidden').length > 1) {
					$('.showdesclang').removeClass('hidden');
				}
				// Show All Languages link: Shows everything and removes any toggles. Can't hide after this.
				$('.showdesclang a').click(function(e) {
					e.preventDefault();
					$('#pb-core-desc-readmore').show(); // Show the Read More link
					$('.showdesclang').addClass('hidden'); // Hide the Show All Languages link
					// if more than one altlang field show everything and change to show less (This doesn't work?)
					if ($('.avpbcoredesc .altlang').length > 1) {
						$('.avpbcoredesc .hidden').removeClass('hidden');
						$('#pb-core-desc-readmore a').eq(0).text('Show Less');
					}
					// Default just show altlang (Show everything and remove toggle)
					$('.avpbcoredesc .altlang').removeClass('hidden altlang'); // Show all alternate languages
                    $('.pb-desc-label').removeClass('hidden'); // Show labels for alternate languages
					$('.avpbcoredesc .field-name-field-description .field-item > *').show(); // Show all paragraph elements in field description itesms
					$('.avpbcoredesc #pb-core-desc-readmore').hide(); // Hide the Readmore link
				});
			}
	  }
	};


	Drupal.behaviors.shantiSarvakaAccountTabs = {
			attach: function (context, settings) {
				if(context == window.document) {

						if ($('.tabs.primary > .active:contains("My Media")').length ) {
							  $('body').addClass('page-my-media');
						}
						if ($('.tabs.primary > .active:contains("My Collections")').length ) {
							  $('body').addClass('page-my-collections');
						}
						if ($('.tabs.primary > .active:contains("My Workflow")').length ) {
							  $('body').addClass('page-my-workflow');
						}
						if ($('.tabs.primary > .active:contains("My Memberships")').length ) {
							  $('body').addClass('page-my-memberships');
						}
				}
		 }
	};

	// Moved from Shanti Sarvaka shanti-main.js

	Drupal.behaviors.shantiSarvakaMbTrimDesc = {
	  attach: function (context, settings) {
	  	if (context == document) {
	  	    // Scoped Function to Show or Hide Description elements. Called below
	  	    function MbShowHideDesc(descElItems, show) {
	  	        if (typeof(show) == "undefined") { show = false; }
	  	        // Hide Extra Text
	  	        if (!show) {
	  	            var c = 0;
	  	            var txtlen = 0;
	  	            var pn = 0;
	  	            descElItems.eq(0).find("p").each(function() {
	  	                if ($(this).text().length > 0 ) { pn += 1; }
	  	                txtlen += $(this).text().length;
	  	                if (txtlen > 750 && pn > 1) {
	  	                    $(this).addClass('toggle');
	  	                }
	  	            });
	  	            descElItems.each(function() {
	  	                c++;
	  	                $(this).find('.toggle').hide();
	  	                if (c > 1) { $(this).hide(300); }
	  	            });
	  	        } else {
	  	            // Show Extra Text
	  	            descElItems.each(function() {
	  	                $(this).find('.hidden').removeClass('hidden').addClass('toggle');
	  	                $(this).find('.toggle').show(300);
	  	                $(this).show(300);
	  	            });
	  	        }
	  	    }
		  	// Pb core description trimming for a/v nodes
		  	var items = $('.field-name-field-pbcore-description > .field-items > .field-item');
		    if(items.length > 1) {
		        MbShowHideDesc(items); // hide extra items at start
			   items.last().after('<p id="pb-core-desc-readmore" class="show-more"><a href="#">' + Drupal.t('Show More') + '</a></p>');
                if(!$(".avdesc").hasClass("show-more-height")) { $(".avdesc").addClass("show-more-height"); }
                $(".show-more > a").click(function (e) {
                    var showitems = ($(this).text() == Drupal.t('Show More')) ? true : false;
                    if (showitems) {
                        MbShowHideDesc(items, true);
                        $(this).text(Drupal.t('Show Less'));
                    } else {
                        MbShowHideDesc(items, false);
                        $(this).text(Drupal.t('Show More'));
                    }
                     e.preventDefault();
                });
			}

				// Description Trimming for collections
				if ($('.node-type-collection .field-type-text-with-summary, .node-type-subcollection .field-type-text-with-summary').length > 0) {
				    var maxlen = 800;  // Max length for collection descriptions
				    var descel = $('.node-type-collection .field-type-text-with-summary, .node-type-subcollection .field-type-text-with-summary').eq(0);
				    if (descel.text().length > maxlen) {
				        var totalchar = 0;
				        var eltotal = 0;
				        var ishidden = false;
				        $('.node-type-collection .field-type-text-with-summary .field-item, .node-type-subcollection .field-type-text-with-summary .field-item').each(function() {
				            $(this).children().each(function() {
				                totalchar += $(this).text().length;
				                eltotal++;
				                if (totalchar > maxlen && eltotal > 1) {
				                    $(this).addClass('overmax');
				                    $(this).hide();
				                    ishidden = true;
				                }
				            });
				        });
				        if (ishidden) {
				            $('.node-type-collection .field-type-text-with-summary, .node-type-subcollection .field-type-text-with-summary')
				                .append('<div class="coldesc-showmore show-more"><a class="link show" href="#">Show more</a></div>');
				            $('.coldesc-showmore a.link').click(function(e) {
				                if ($(this).hasClass('show')) {
				                    $('.overmax').show();
				                    $(this).text('Show less');
				                    $(this).removeClass('show');
				                } else {
				                    $('.overmax').hide();
                                    $(this).text('Show more');
                                    $(this).addClass('show');
				                }
                                e.preventDefault();
				            });
				        }
				    }
				}
			}
		} // end context = document
	};

	// --- unhiding shanti-filters: inline styles keeps the default dropdown from flashing onLoad before the bootstrap-select script/css loads
	Drupal.behaviors.shantiFiltersOnLoadFlickerControl = {
	  	attach: function (context, settings) {
	  		$(".front .control-box-cell-filters").show( "fast" );
	  		if ($.trim($(".control-box-cell-header").html()) == '') {
	  			$(".control-box-cell-header").html('<span class="label">Recent Additions</span> (No matches)');
	  		}
	    }
	};

	Drupal.behaviors.shantiOpenAVLoginPanel = {
	  	attach: function (context, settings) {
	  		$("#accordionedit-drupal-login .panel-collapse").collapse('show');
	    }
	};

	Drupal.behaviors.shantiAVVideoFix = {
		attach: function(context, settings) {
			if (context == document) {
				$('.kWidgetIframeContainer.kaltura-embed-processed').once('videosizeadjustment', function() {
				$('.kWidgetIframeContainer.kaltura-embed-processed').prev('div').remove();
					$('.kWidgetIframeContainer.kaltura-embed-processed iframe').on('load', function() {
						var ratio = Drupal.settings.mediabase.vratio,
							  pwidth = $('.kWidgetIframeContainer.kaltura-embed-processed').parent().width(),
							  height = ((ratio == '4:3') ? pwidth / 1.3333 : pwidth / 1.7778) + ((ratio == '4:3') ? 32 : 42), // add 32/42 px to height for control bar
							  divclass = (ratio == '4:3') ? 'ratio-4-3' : 'ratio-16-9';
						$('.kWidgetIframeContainer.kaltura-embed-processed').addClass(divclass).css({
								'position':'',
								'top':'',
								'left': '',
								'right':'',
								'bottom':'',
								'width':'100%',
								'height': height + 'px'
						});
					});
				});
			}
		}
	};

	/**
	 * Make sure gallery thumbnails from kaltura use the proper size. Hack because php code to save thumb url is not working properly
	 * ndg, 2015-12-07
	 */
	Drupal.behaviors.shantiAVThumbnailFix = {
		attach: function(context, settings) {
			if (context == document) {
				$('li.shanti-thumbnail.video img').each(function() {
					var src = $(this).attr('src');
					if (src.indexOf('kaltura.com') > -1 && src.indexOf('/version') > -1) {
						var pts = src.split('version'); $(this).attr('src', pts[0] + '/width/240/height/220/type/1');
					}
				});
			}
		}
	};

	/**
	 * Footer delay css and loading flash from media rating element
	 */
	Drupal.behaviors.miscFunctions = {
	  attach: function (context, settings) {
	    if(context == window.document) {

			/* avoid flash on load for the Star Ratings below Audio or Video players */
			$('.avrating').css('display','block');
            
			/* open by default the required fields section */
			//$('.mb-av-form .group-required-video-info').find('.panel-collapse').addClass('in');
			//$('.mb-av-form .group-required-video-info .panel-heading').find('a').removeClass('collapsed');

	    }
	    
        $('.modal-header .close').on('click', function() {
            // If modal upload is cancelled, need to reload page to reactivate the loading button
            // Do this by submitting the form to save any existing data but without av item will return to form with messages
            $('#edit-actions #edit-submit').click();
        });
	  }
	};
	
/*
	Drupal.behaviors.equalHeightTranscriptAV = {
    attach: function (context, settings) {
      if (context == document) {

        var mainvideo = $('.av-main-video-section').height();
        var maintranscript = $('.av-main-transcript-section').height();

		Drupal.ShantiMediabase.equalHeightTranscriptAV = function (e) {
			if($(mainvideo > maintranscript)) {
			    $('.av-main-video-section').css('height', mainvideo );
			    $('.av-main-transcript-section .transcript-container').css('height', mainvideo );
			}
		};

        $(window).bind('load orientationchange resize', Drupal.ShantiMediabase.equalHeightTranscriptAV);
      }
    }
  };
*/

} (jQuery)); // End of JQuery Wrapper
