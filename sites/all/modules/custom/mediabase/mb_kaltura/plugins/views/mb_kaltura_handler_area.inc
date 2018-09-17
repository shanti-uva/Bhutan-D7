<?php

/**
 * A handler to provide an area that is constructed by the administrator using PHP.
 *
 * @ingroup views_area_handlers
 */
class mb_kaltura_handler_area extends views_handler_area {
  /**
   * Implements views_handler_area#render().
   */
  function render($empty = FALSE) {
    // return total minutes on results
    $total = mb_kaltura_get_total_minutes($this->view->result);
    return "<p>Total Video Time: $total  (Note: In multipage results, totals represent only the page being shown.)</p>"; 
   }
}
