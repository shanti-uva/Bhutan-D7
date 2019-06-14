(function ($) {


/*
 * MbExtruder Init
 */
/* Extruder GIT Doc - https://github.com/pupunzi/jquery.mb.extruder/wiki */
Drupal.behaviors.sarvakaMbextruder = {
  attach: function (context, settings) {
  	if(context == document) {
	    var mywidth = Drupal.settings.shanti_sarvaka.flyoutWidth;
	    $(".input-section, .view-section, .view-section .nav-tabs>li>a").css("display","block"); // show hidden containers after loading to prevent content flash
			// Remove extruder div content so as to preserve AJAX events
			var mbContent = $("#search-flyout .region-search-flyout").detach();
	    // Initialize Search Flyout
	    $("#search-flyout").buildMbExtruder({
	      positionFixed: false,
	      position: "right",
	      closeOnExternalClick:false,
	      closeOnClick:false,
	      width: mywidth, // width is set in two places, here and the css
	      top: 0,
		    onExtOpen: function() {
	        $("#faceted-search-results").trigger("extopen");
        },
        onExtClose: function() {
          $("#faceted-search-results").trigger("extclose");
        },
        onExtContentLoad: function () {
        }
        });
	    // Add back in extruder content
	    $('#search-flyout .text').append(mbContent);
      // $('div.extruder-content').before("<div id='faceted-search-results' class='panel'><div class='content'>RESULTSARAMA</div></div>");
	//    $('#search-flyout .text').css('overflow','hidden');
	    // Make it resizeable
	    try {
		    if($('#search-flyout .text').length > 0) {
			    // top-right close button, visible for small mobile screens only - currently set to display on all but kmaps which has it's own script for rendering of the button
				$('body:not(.kmaps) #search-flyout .text').append( '<span id="btn-collapse-flyout" class="icon shanticon-arrow-end-right btn-collapse-flyout" type="button" aria-label="Close Search Flyout"></span>' );
				// Search Results and Flyout Width Integration --------------------
				$('#btn-collapse-flyout').click(function() {
					$('#search-flyout').closeMbExtruder();
					// this is only for kmaps search currently
					$('#faceted-search-results').toggleClass('search-flyout-open search-flyout-collapsed');
	      		});

			    $('#search-flyout .text').resizable({
			      handles: 'w,nw',
			      resize: function (event, ui) {
			      	$('#search-flyout .extruder-content').css('width','');
			        //$('span.fancytree-title').trunk8({ tooltip:false });
			      }
			    });
			}
		    // Bind event listener
		    $('.extruder-content').resize(function() {
            Drupal.attachBehaviors('#faceted-search-results');
            Drupal.ShantiSarvaka.checkWidth();
          }
        );
		    // Add identifier
		    // $(".extruder-content").attr("aria-label","Search Panel");
		    } catch (e) {
		   	  console.warn('Resizeable not a function error caught! shanti-search.js line 31');
		}

	    if (!$("#search-flyout").hasClass("isOpened")) {
			$(".flap").click( function() {
				$("#search-flyout .text").css("width","100%");
				// Search Results and Flyout Width Integration --------------------
				$("#faceted-search-results").toggleClass('search-flyout-collapsed search-flyout-open');
			});
			$(".flap").prepend("<span><span class='icon shanticon-search'></span></span>");
			$(".flap").addClass("on-flap");
			// Add identifiers
			$(".flap").attr("role", "button");
			$(".flap").attr("aria-label", "Open Search Panel");
	    } else {

			// Search Results and Flyout Width Integration --------------------
			$("#faceted-search-results").toggleClass('search-flyout-open search-flyout-collapsed');
	    }

	    // Search Results and Flyout Width Integration --------------------
		$('#btn-show-search-results').click( function() {
			if ($('#search-flyout').hasClass('isOpened')) {
			  $('#faceted-search-results').addClass('search-flyout-open');
			} else {
			  $('#faceted-search-results').addClass('search-flyout-collapsed');
			}
		});

//		$("#search-flyout .flap").click( function () {
//			if ($("#search-flyout").hasClass("isOpened")) {
//					$(".btn-show-search-results").hide();
//				} else {
//	                $(".btn-show-search-results").show();
//            }
//		});

	    $("#search-flyout .flap").hover(
	      function () {
	        $(this).addClass('on-hover');
	      },
	      function () {
	        $(this).removeClass('on-hover');
	    });

	    $('#search-flyout').show();
	    // --- set class on dropdown menu for icon
	    $('.shanti-field-title a').hover( function() {
	      $(this).addClass('on-hover');
	    },
	    function () {
	      $(this).removeClass('on-hover');
	    });
	    // Inizialize bootstrap elements inside flyout region
	    $('#search-flyout .selectpicker').selectpicker({
	      dropupAuto: false,
	    }); // initiates jq-bootstrap-select

        // listen for 'extopen', the event that signals that the search flyout is being opened.
        $('#search-flyout').on('extopen', function() {
            setTimeout(function () {
                $('#search-flyout .treeview').trigger('shown.bs.tab');
            }, 30);
        });
        /* color change for ui-resize handle */
        $('#search-flyout .ui-resizable-nw').hover(function () {
        	$('.extruder .ui-resizable-w').css('opacity','1');
        },
          function () {
            $('#search-flyout .ui-resizable-w').css('opacity','0.8');
          }
        );
    }
  }
};

/**
 * Open Extruder by default
 */
Drupal.behaviors.shanti_sarvaka_flyoutinit = {
    attach: function (context, settings) {
        if (context == document && Drupal.settings.shanti_sarvaka.flyoutautoopen) {
            if ($(window).width() >= 992) {
                var flyout_status = $.cookie('flyout_status');
                if (!$.cookie('flyout_status') || $.cookie('flyout_status') == 'open') {
                    var tabnum = -1;
                    if ($('body').hasClass('page-places')) {
                        tabnum = 1;
                    } else if ($('body').hasClass('page-subjects')) {
                        tabnum = 2;
                    } else if ($('body').hasClass('page-terms')) {
                        tabnum = 3;
                    }
                    setTimeout( function() {
                        if (tabnum > -1) {
                            $('.shanti-kmaps-faceted-search-kmaps-' + tabnum + ' a').click();
                        }
                        // $('#search-flyout').openMbExtruder();
                        $('#search-flyout.extruder:not(.isOpened) .flap').click();
                    }, 800);
                }
            }
        }
    }
};

Drupal.behaviors.shanti_sarvaka_flyoutupdate = {
    attach: function (context, settings) {
        if (context == document && Drupal.settings.shanti_sarvaka.flyoutautoopen) {
            var flyout_status = $.cookie('flyout_status');
            $('#search-flyout .flap').click(function(e) {
                if ($('#search-flyout').attr('isOpened')) {
                    var flyout_status = 'open';
                    // $('#search-flyout').openMbExtruder();
                  $('#search-flyout.extruder:not(.isOpened) .flap').click();
                    $('#faceted-search-results').addClass('search-flyout-open');
                }
                else {
                    var flyout_status = 'close';
                }
                $.cookie('flyout_status', flyout_status, {path:'/'});
                e.preventDefault();
            });
        }
    }
};

/**
* Search Init
*/
Drupal.behaviors.sarvakaSearchInit = {
	attach: function (context, settings) {
		if(context == document) {

	        Drupal.ShantiSarvaka.searchTabHeight();
	        $(window).bind('load orientationchange resize', Drupal.ShantiSarvaka.searchTabHeight );
	    }
	}
};


  // handles ordinary search flyout inputs (not typeahead inputs)
Drupal.behaviors.shantiSarvakaSearchFlyoutCancel = {
    attach: function (context, settings) {
      if (context == window.document) {
        $('.search-group .input-group').once().each(function () { // ----- testing broader target on oct. 20, 2016
            // $('.extruder').once().each(function() {
          var $xbtn = $("button.searchreset", this);
          var $srch = $(".form-control", this);  // the main search input
          $srch.data("holder", $srch.attr("placeholder"));

            // --- focusin - focusout
          $srch.focusin(function () {
            $srch.attr("placeholder", "");
            $xbtn.show("fast");
          });
          $srch.focusout(function () {
            $srch.attr("placeholder", $srch.data("holder"));
            $xbtn.hide();

            var str = $srch.data("holder"); //"Enter Search...";
            var txt = $srch.val();

              if (str.indexOf(txt) > -1) {
              $xbtn.hide();
              return true;
              } else {
              $xbtn.show(100);
              return false;
             }
          });
        });
      }
    }
};


Drupal.behaviors.searchPanelHeightKMaps = {
	attach: function (context, settings) {

	  const DEBUG = false;
	  if (context === document) {
	    var $extruder = $('#search-flyout .extruder-content');
	    var $kmfacets = $('#kmfacet-list');
      var invisibleHeight = function ($el) {
        $el.css({
          'display': 'block',
          'visibility': 'hidden'
        });
        var height = $el.innerHeight();
        $el.css({
          'display': 'none',
          'visibility': 'visible'
        });
        return height;
      };

	    if ($kmfacets.length === 0) { // subjects or places
	      /* http://remy.bach.me.uk/blog/2011/04/getting-the-height-of-a-hidden-element-using-jquery/ */

	      var $inputsec = $('#kmaps-search .input-section');
	      var input_height = $('.search-filters', $inputsec).length === 1 ? 225 : 68; // places but not subjects has search filters

	      // *** SEARCH *** adapt search panel height to viewport for scrolling treenav area
	      Drupal.ShantiSarvaka.searchTabHeightKMaps = function (e) {

          var extruder_height;
	        if ($extruder.css('display') === 'block') {
	          extruder_height = $extruder.innerHeight();
	          input_height = $inputsec.height(); // height of input-section may have changed
	        }
	        else {
	          extruder_height = invisibleHeight($extruder);
	        }
	        var viewheightKMaps = extruder_height - input_height - 75;
	        $extruder.find('.view-wrap').css('height', viewheightKMaps + 'px');
	      };

	      //Drupal.ShantiSarvaka.searchTabHeightKMaps();
	      $(window).bind('load orientationchange resize searchUpdate extopen', Drupal.ShantiSarvaka.searchTabHeightKMaps);

	      // prevent overscrolling into body
	      $extruder.find('.view-wrap').scrollLock();
	    }
	    else { // mandala home page
	      Drupal.ShantiSarvaka.searchTabHeightKMaps = function (e) {

	        var view_height = 100;
          if ($extruder.css('display') === 'block') {
            view_height = $extruder.innerHeight() - 90; // tab_height = 60
          }  else {
            view_height = invisibleHeight($extruder) - 90;
          }



          var $input_height = $('.input-section').height();
          var $filterbox_height = $('.kmap-filter-box').height();
          var $navtab_height = $('.nav-tabs').height();
          var $viewsection_height = $('.view-section').height();

          var $other_height = $filterbox_height + $navtab_height;

          // console.log("view_height = " + view_height);
          $('.km-facet-div > div').css('height', (view_height - $other_height) + 'px');


          // Need to add space to the height of $('#kmtree-kmaps_1 > ul > li > ul').height();

          // The question is WHY?

          // Search Results Panel and List Heights
          // hiding this to try using results script in Sarvaka
          $('#faceted-search-results').css('height', (view_height + 105) +'px'); // Results Panel Height: This will adjust the distance from the bottom of the results panel to the bottom of the browser - This should match the distance of the search flyout to bottom.
          $('.search-results-list-wrapper, .search-results-node-preview').css('height', (view_height - 80) +'px'); // Results Scrollable List Height: This will adjust eh scrollable results list height - This should be about (1/8 in) above bottom of results list wrapper.

          if (DEBUG) {
            console.log("searchTabHeightKMaps()");

            console.groupCollapsed("searchTabHeightKMaps");

            console.log("input-section height: " + $input_height);
            console.log("kmap-filter-box height: " + $filterbox_height);
            console.log("nav-tab height: " + $navtab_height);
            console.log("view-section height: " + $viewsection_height);
            console.log("tab-content height: " + $('.tab-content').height());
            console.log("tab-pane height: " + $('.tab-pane').height());
            console.log("km-facet-div > div: " + $('.km-facet-div > div').height());
            console.groupEnd();
          }

	      };
	      $(window).bind('load orientationchange resize searchUpdate', Drupal.ShantiSarvaka.searchTabHeightKMaps);
	      $('#search-flyout').on('extopen', Drupal.ShantiSarvaka.searchTabHeightKMaps);

	      // prevent overscrolling into body
	      $('.km-facet-div > div').scrollLock();
	    }

	  }
	}
};


/* Testing for improved positioning of popover son search tree ----------------
  Drupal.behaviors.sarvakaSearchPopoverPosition = {
    attach: function (context, settings) {
    	if(context == document) {
			$('[data-toggle=popover]').on('shown.bs.popover', function () {
			  $('.search-popover.left').css('left',parseInt($('.popover').css('left')) - 15 + 'px')
			})
	    }
    }
  };
*/


})(jQuery);
