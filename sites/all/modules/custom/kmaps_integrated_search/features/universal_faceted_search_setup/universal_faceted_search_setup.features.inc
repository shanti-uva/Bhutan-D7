<?php

/**
 * @file
 * universal_faceted_search_setup.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function universal_faceted_search_setup_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
