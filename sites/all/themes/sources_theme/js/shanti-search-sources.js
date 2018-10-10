(function ($) {
  Drupal.behaviors.initializeSearchFlyout = {
    attach: function (context, settings) {
        /** Keeps opening flyout but does not remember status (May 29 2018) Disabling for now in 7.x-1.11
      var flyout_status = $.cookie('flyout_status');

      if ($.cookie('flyout_status') && $.cookie('flyout_status') == 'open') {
        $('#search-flyout').openMbExtruder();
      }
         **/
    }
  };

  Drupal.behaviors.updateSearchFlyout = {
    attach: function (context, settings) {
      /** Keeps opening flyout but does not remember status (May 29 2018) Disabling for now in 7.x-1.11
      var flyout_status = $.cookie('flyout_status');

      $('#search-flyout div.flap').click(function(e) {
        if ($('#search-flyout').attr('isopened')) {
          var flyout_status = 'open';
          $("#search-flyout").openMbExtruder();
        }
        else {
          var flyout_status = 'close';
        }
        $.cookie('flyout_status', flyout_status);
        e.preventDefault();
      });
       */
    }
  };


    /* copied and modified from Drupal.behaviors.searchPanelHeightAV in shanti-main-kmaps.js */
  Drupal.behaviors.searchPanelHeightSources = {
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
        var $inputsec = $('#search-flyout .input-section');
        var input_height = 110;

        // *** SEARCH *** adapt search panel height to viewport for scrolling treenav area
        Drupal.ShantiSarvaka.searchTabHeightSources = function (e) {
          var extruder_height;
          if ($extruder.css('display') == 'block') {
            extruder_height = $extruder.innerHeight();
            input_height = $inputsec.height(); // height of input-section may have changed
          }
          else {
            extruder_height = invisibleHeight($extruder);
          }
          var view_height = extruder_height - input_height - 80;
          $(".shanti-kmaps-facets-block").css('height', view_height + 'px');
        };

        $(window).bind('load orientationchange resize', Drupal.ShantiSarvaka.searchTabHeightSources);
      }
    }
  };


  Drupal.behaviors.toggleSourcesListItems = {
    attach: function (context, settings) {
      if (context == document) {

        $('.view-biblio-search-api .fa-plus').click(function() {

            if($(this).hasClass('on')) {
                $(this).toggleClass('on');
                $(this).closest('.views-row').find('.views-field:not(.views-field-title)').hide(100);
            } else {
              $(this).addClass('on');
              $(this).closest('.views-row').find('.views-field').show(100);
              return false;
            }
        });

        // clicking details buttons resets plus icons to original vertical position
        $('.detail-level-option li a').click(function() {
            $('.view-biblio-search-api .fa-plus').removeClass('on');
        });
        $('.detail-level-option li:nth-of-type(3) a').click(function() {
            $('.view-biblio-search-api .fa-plus').addClass('on');
        });

        if($('.detail-level-option li:nth-of-type(3) a').hasClass('active')){
            $('.view-biblio-search-api .fa-plus').addClass('on');
        }


        // For adding theme classes to Edit button on bibliographies 
        $('.page-sources-search-biblio .views-row .views-field:last-child').find('a').addClass('btn btn-primary');
        // Tag the mandala app
        $('body').addClass('sources');

      }
    }  
  };

    Drupal.behaviors.mySourcesPage = {
        attach: function (context, settings) {
          if (context == document) {
              $('.view-display-id-my_source_page .form-item-biblio-year-min input').attr('placeholder', 'From');
              $('.view-display-id-my_source_page .form-item-biblio-year-max input').attr('placeholder', 'To');
          }
      }
  };
})(jQuery);
