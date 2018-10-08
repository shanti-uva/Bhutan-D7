(function ($) {
  Drupal.behaviors.initializeSearchFlyout = {
    attach: function (context, settings) {
      var flyout_status = $.cookie('flyout_status');

      if ($.cookie('flyout_status') && $.cookie('flyout_status') == 'open') {
        $('#search-flyout').openMbExtruder();
      }
    }
  };

  Drupal.behaviors.updateSearchFlyout = {
    attach: function (context, settings) {
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
    }
  };
})(jQuery);
