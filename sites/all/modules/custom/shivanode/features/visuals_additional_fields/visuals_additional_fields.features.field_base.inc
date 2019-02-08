<?php

/**
 * @file
 * visuals_additional_fields.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function visuals_additional_fields_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_language_kmap'.
  $field_bases['field_language_kmap'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_language_kmap',
    'indexes' => array(
      'id' => array(
        0 => 'id',
      ),
    ),
    'locked' => 0,
    'module' => 'shanti_kmaps_fields',
    'settings' => array(
      'kmap_domain' => 'subjects',
    ),
    'translatable' => 0,
    'type' => 'shanti_kmaps_fields_default',
  );

  return $field_bases;
}
