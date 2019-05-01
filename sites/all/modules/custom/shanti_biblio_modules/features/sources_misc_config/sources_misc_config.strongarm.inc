<?php

/**
 * @file
 * sources_misc_config.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sources_misc_config_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'biblio_node_layout';
  $strongarm->value = 'orig';
  $export['biblio_node_layout'] = $strongarm;

  return $export;
}
