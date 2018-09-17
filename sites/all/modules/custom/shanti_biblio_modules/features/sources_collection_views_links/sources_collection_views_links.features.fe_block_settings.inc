<?php
/**
 * @file
 * sources_collection_views_links.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sources_collection_views_links_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['block-add_collection_button_block'] = array(
    'cache' => -1,
    'custom' => 0,
    'machine_name' => 'add_collection_button_block',
    'module' => 'block',
    'node_types' => array(),
    'pages' => 'collections',
    'roles' => array(),
    'themes' => array(
      'shanti_sarvaka' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'shanti_sarvaka',
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -20,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  return $export;
}
