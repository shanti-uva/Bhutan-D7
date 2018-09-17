<?php
/**
 * @file
 * shanti_pager.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function shanti_pager_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
