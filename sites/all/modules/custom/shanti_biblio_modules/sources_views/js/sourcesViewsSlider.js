/**
 * @file
 * Javascript tweak for the date range slider
 */
(function ($) {
  /*
   * For other autocomplete fields (views filters) on the advanced search form
   */
  Drupal.behaviors.sourcesViewsSlider = {
    attach: function (context, settings) {
      var start_year_tab = '.ui-slider-range .start-year';
      var end_year_tab   = '.ui-slider-range .end-year';

      var start_year_handle  = '.ui-slider .ui-slider-handle:nth-of-type(1)';
      var end_year_handle    = '.ui-slider .ui-slider-handle:nth-of-type(2)';

      $(start_year_tab +', '+ start_year_handle).mousedown(function() {
        showStartYear();
      });

      $(end_year_tab +', '+ end_year_handle).mousedown(function() {
        showEndYear();
      });

      function showStartYear() {
        $(start_year_tab).css({'z-index': 1});
        $(end_year_tab).css({'z-index': -1});
      }

      function showEndYear() {
        $(end_year_tab).css({'z-index': 1});
        $(start_year_tab).css({'z-index': -1});
      }
    }
  };
})(jQuery);
