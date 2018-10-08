<?php
/**
 * @file
 * shanti_external_classification.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function shanti_external_classification_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function shanti_external_classification_node_info() {
  $items = array(
    'external_classification' => array(
      'name' => t('External Classification'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Label'),
      'help' => '',
    ),
    'external_classification_scheme' => array(
      'name' => t('External Classification Scheme'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
