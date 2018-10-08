<?php
/**
 * @file
 * sponsors_feature.features.inc
 */

/**
 * Implements hook_views_api().
 */
function sponsors_feature_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function sponsors_feature_image_default_styles() {
  $styles = array();

  // Exported image style: sponsor_logo.
  $styles['sponsor_logo'] = array(
    'label' => 'Sponsor Logo',
    'effects' => array(),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function sponsors_feature_node_info() {
  $items = array(
    'sponsor' => array(
      'name' => t('Sponsor'),
      'base' => 'node_content',
      'description' => t('An organization that has sponsored the Bhutan Cultural Library'),
      'has_title' => '1',
      'title_label' => t('Sponsor'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
