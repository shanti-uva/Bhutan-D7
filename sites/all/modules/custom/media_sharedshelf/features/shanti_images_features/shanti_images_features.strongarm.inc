<?php
/**
 * @file
 * shanti_images_features.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function shanti_images_features_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_collection_pattern';
  $strongarm->value = 'collection/[node:title]';
  $export['pathauto_node_collection_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_subcollection_pattern';
  $strongarm->value = 'collection/[node:title]';
  $export['pathauto_node_subcollection_pattern'] = $strongarm;

  return $export;
}
