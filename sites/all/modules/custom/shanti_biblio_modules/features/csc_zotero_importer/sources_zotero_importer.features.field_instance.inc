<?php
/**
 * @file
 * sources_zotero_importer.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function sources_zotero_importer_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-biblio-field_zotero_attachment'
  $field_instances['node-biblio-field_zotero_attachment'] = array(
    'bundle' => 'biblio',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 5,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_zotero_attachment',
    'label' => 'Zotero Attachments',
    'required' => 0,
    'settings' => array(
      'attributes' => array(
        'class' => '',
        'configurable_title' => 0,
        'rel' => '',
        'target' => 'default',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'linkit' => array(
        'enable' => 0,
        'insert_plugin' => '',
      ),
      'rel_remove' => 'default',
      'title' => 'optional',
      'title_maxlength' => 255,
      'title_value' => '',
      'url' => 0,
      'user_register_form' => FALSE,
      'validate_url' => 0,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(),
      'type' => 'link_field',
      'weight' => 35,
    ),
  );

  // Exported field_instance: 'node-biblio-field_zotero_collections'
  $field_instances['node-biblio-field_zotero_collections'] = array(
    'bundle' => 'biblio',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 2,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_zotero_collections',
    'label' => 'Zotero Collections',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 32,
    ),
  );

  // Exported field_instance: 'node-biblio-field_zotero_files'
  $field_instances['node-biblio-field_zotero_files'] = array(
    'bundle' => 'biblio',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 6,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_zotero_files',
    'label' => 'Zotero Files',
    'required' => 0,
    'settings' => array(
      'attributes' => array(
        'class' => '',
        'configurable_title' => 0,
        'rel' => '',
        'target' => 'default',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'linkit' => array(
        'enable' => 0,
        'insert_plugin' => '',
      ),
      'rel_remove' => 'default',
      'title' => 'optional',
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
      'user_register_form' => FALSE,
      'validate_url' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(),
      'type' => 'link_field',
      'weight' => 36,
    ),
  );

  // Exported field_instance: 'node-biblio-field_zotero_tags'
  $field_instances['node-biblio-field_zotero_tags'] = array(
    'bundle' => 'biblio',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 1,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_zotero_tags',
    'label' => 'Zotero Tags',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 31,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Zotero Attachments');
  t('Zotero Collections');
  t('Zotero Files');
  t('Zotero Tags');

  return $field_instances;
}
