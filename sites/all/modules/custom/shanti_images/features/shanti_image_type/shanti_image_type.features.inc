<?php

/**
 * @file
 * shanti_image_type.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function shanti_image_type_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function shanti_image_type_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function shanti_image_type_image_default_styles() {
  $styles = array();

  // Exported image style: shanti_image_full.
  $styles['shanti_image_full'] = array(
    'label' => 'Shanti Image Full',
    'effects' => array(
      4 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 900,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function shanti_image_type_node_info() {
  $items = array(
    'image_agent' => array(
      'name' => t('Agent'),
      'base' => 'node_content',
      'description' => t('Agents involved in the creation of an image.'),
      'has_title' => '1',
      'title_label' => t('Agent Name'),
      'help' => '',
    ),
    'image_descriptions' => array(
      'name' => t('Image Descriptions'),
      'base' => 'node_content',
      'description' => t('Descriptions about images with language selection, includes caption, summary, and full-length descriptions'),
      'has_title' => '1',
      'title_label' => t('Caption'),
      'help' => '',
    ),
    'shanti_image' => array(
      'name' => t('Shanti Image'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Main Caption'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
