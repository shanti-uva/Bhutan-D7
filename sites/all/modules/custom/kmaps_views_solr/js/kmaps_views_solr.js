;(function($) {
  Drupal.behaviors.kmaps_views_solr = {
    attach: function(context, settings) {
      //Dom-id replacement for Better expose filters
      domid = $(".shanti-view-dom-id").attr("data-dom-id")
      $("div.view-dom-id-" + domid).removeClass("view-dom-id-" + domid)
      $(".shanti-view-dom-id").addClass("view-dom-id-" + domid)
    }
  }
})(jQuery)
