<?php
/**
 * @file
 * shiva_views_new.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function shiva_views_new_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function shiva_views_new_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function shiva_views_new_image_default_styles() {
  $styles = array();

  // Exported image style: shiva_collection_teaser.
  $styles['shiva_collection_teaser'] = array(
    'label' => 'Shiva Collection Teaser',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 200,
          'height' => 150,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
