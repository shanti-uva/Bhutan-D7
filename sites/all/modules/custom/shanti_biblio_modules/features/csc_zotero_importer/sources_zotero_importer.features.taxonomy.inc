<?php
/**
 * @file
 * sources_zotero_importer.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function sources_zotero_importer_taxonomy_default_vocabularies() {
  return array(
    'collections' => array(
      'name' => 'Collections',
      'machine_name' => 'collections',
      'description' => 'Zotero Collections',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'zotero_tags' => array(
      'name' => 'Zotero Tags',
      'machine_name' => 'zotero_tags',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
