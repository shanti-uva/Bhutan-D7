<?php

/**
 * @file
 * Class kaltura_views_handler_field_url.
 */

/**
 * Download-link field handler class.
 */
class kaltura_views_handler_field_url extends views_handler_field {

  function option_definition() {
    $options = parent::option_definition();

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  function render($values) {
    $html = l(t("Download"), $values->node_kaltura_kaltura_download_url,
              array('attributes' => array('target' => '_blank')));
    return $html;
  }
}
