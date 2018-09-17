<?php
/**
 * @file
 * sources_collection_views_links.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function sources_collection_views_links_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Add Collection Block';
  $fe_block_boxes->format = 'php_code';
  $fe_block_boxes->machine_name = 'add_collection_button_block';
  $fe_block_boxes->body = '<div class="add-collection-div"><a class="btn btn-primary" href="/node/add/collection">Add Collection</a></div>';

  $export['add_collection_button_block'] = $fe_block_boxes;

  return $export;
}
