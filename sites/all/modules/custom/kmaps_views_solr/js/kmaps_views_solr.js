;(function($) {
  Drupal.behaviors.kmaps_views_solr = {
    attach: function(context, settings) {
      //Dom-id replacement for Better expose filters
      var domid = $(".shanti-view-dom-id").attr("data-dom-id");
      $("div.view-dom-id-" + domid).removeClass("view-dom-id-" + domid);
      $(".shanti-view-dom-id").addClass("view-dom-id-" + domid);
    }
  };

  Drupal.behaviors.kmaps_views_solr_images = {
    attach: function(context, settings) {
      if (context != document) {
        // for ajax calls in kmaps photos need to reset the pig gallery.
        if ($('body').hasClass('kmaps-photos') && typeof(context) == 'object' && context[0].localName == 'div') {
            if (typeof(settings.shanti_grid_view) != 'undefined') {
              settings.shanti_grid_view.resetpig = true;
            }
        }

      }

      if ($('.shanti-filters .pager a[href*="/ajax"]').length > 0) {
        window.location.reload();
      }
    }
  };


})(jQuery)
