<?php
/**
 * @file
 * shanti_images_features.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function shanti_images_features_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function shanti_images_features_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function shanti_images_features_image_default_styles() {
  $styles = array();

  // Exported image style: image_collection_thumbnail.
  $styles['image_collection_thumbnail'] = array(
    'label' => 'Image Collection Thumbnail',
    'effects' => array(
      4 => array(
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
