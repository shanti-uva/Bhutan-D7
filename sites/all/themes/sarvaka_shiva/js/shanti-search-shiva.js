( function($) {

        /**
         *  Shiva Sarvaka Search JS behaviors
         * 
         *  Full text search box
         */
        Drupal.behaviors.fulltextSearch = {
            attach : function(context, settings) {
                if (context == document) {
                    $('#fulltextsearch-reset').click(function() { $('#edit-reset').click(); });
                }
            }
        };


        // For Views - Search flyout inputs (not typeahead inputs)
        Drupal.behaviors.shantiSarvakaSearchFlyoutViewsCancel = {
          attach: function (context, settings) {
            if(context == window.document) {
              $('.region-search-flyout .views-exposed-widgets').once().each(function() { // ----- testing broader target on oct. 20, 2016
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




        /* copied and modified from Drupal.behaviors.searchPanelHeightAV in shanti-main-kmaps.js */
        Drupal.behaviors.searchPanelHeightVisuals = {
        attach: function (context, settings) {
          if (context == document) {
            /* http://remy.bach.me.uk/blog/2011/04/getting-the-height-of-a-hidden-element-using-jquery/ */
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

            var $extruder = $('#search-flyout .extruder-content');
            var $inputsec = $('.region-search-flyout > div.block');
            var input_height = 75; /* height of top container for search input section */

            // *** SEARCH *** adapt search panel height to viewport for scrolling treenav area
            Drupal.ShantiSarvaka.searchTabHeightVisuals = function (e) {
              var extruder_height;
              if ($extruder.css('display') == 'block') {
                extruder_height = $extruder.innerHeight();
                input_height = $inputsec.height(); // height of input-section may have changed
              }
              else {
                extruder_height = invisibleHeight($extruder);
              }
              var view_height = extruder_height - input_height - 60; /* height of tabs plus */
              $(".shanti-kmaps-facets-block").css('height', view_height + 'px');
            };

            $(window).bind('load orientationchange resize', Drupal.ShantiSarvaka.searchTabHeightVisuals );
          }
        }
        };


        
}(jQuery)); 










