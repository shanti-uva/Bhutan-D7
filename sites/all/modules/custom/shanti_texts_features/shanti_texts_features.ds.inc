<?php
/**
 * @file
 * shanti_texts_features.ds.inc
 */

/**
 * Implements hook_ds_view_modes_info().
 */
function shanti_texts_features_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'embed';
  $ds_view_mode->label = 'Embed';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['embed'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'meta';
  $ds_view_mode->label = 'Meta';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['meta'] = $ds_view_mode;

  return $export;
}
