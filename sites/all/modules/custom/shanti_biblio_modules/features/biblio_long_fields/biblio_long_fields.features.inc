<?php
/**
 * @file
 * biblio_long_fields.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function biblio_long_fields_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
