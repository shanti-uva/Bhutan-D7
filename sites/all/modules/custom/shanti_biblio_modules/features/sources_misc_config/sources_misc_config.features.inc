<?php
/**
 * @file
 * sources_misc_config.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sources_misc_config_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function sources_misc_config_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function sources_misc_config_image_default_styles() {
  $styles = array();

  // Exported image style: source_full_page_image.
  $styles['source_full_page_image'] = array(
    'label' => 'Source Full Page Image',
    'effects' => array(
      12 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 400,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
