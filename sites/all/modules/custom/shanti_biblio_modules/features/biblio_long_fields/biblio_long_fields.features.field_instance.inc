<?php
/**
 * @file
 * biblio_long_fields.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function biblio_long_fields_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-biblio-field_biblio_language'.
  $field_instances['node-biblio-field_biblio_language'] = array(
    'bundle' => 'biblio',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 5,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 12,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_biblio_language',
    'label' => 'Biblio Language',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => '',
      ),
      'type' => 'options_select',
      'weight' => 67,
    ),
  );

  // Exported field_instance: 'node-biblio-field_biblio_long_language'.
  $field_instances['node-biblio-field_biblio_long_language'] = array(
    'bundle' => 'biblio',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 10,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_biblio_long_language',
    'label' => 'Biblio Long Language',
    'required' => 0,
    'settings' => array(
      'linkit' => array(
        'button_text' => 'Search',
        'enable' => 0,
        'profile' => '',
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 66,
    ),
  );

  // Exported field_instance: 'node-biblio-field_biblio_long_title'.
  $field_instances['node-biblio-field_biblio_long_title'] = array(
    'bundle' => 'biblio',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 9,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'full' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_plain',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 11,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_biblio_long_title',
    'label' => 'Biblio Long Title',
    'required' => 0,
    'settings' => array(
      'linkit' => array(
        'button_text' => 'Search',
        'enable' => 0,
        'profile' => '',
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 65,
    ),
  );

  // Exported field_instance: 'node-biblio-field_kmaps_places'.
  $field_instances['node-biblio-field_kmaps_places'] = array(
    'bundle' => 'biblio',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'shanti_kmaps_fields',
        'settings' => array(),
        'type' => 'kmap_popover_formatter',
        'weight' => 7,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'shanti_kmaps_fields',
        'settings' => array(),
        'type' => 'kmap_popover_formatter',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_kmaps_places',
    'label' => 'Places',
    'required' => 0,
    'settings' => array(
      'kmap_term_limit' => 100,
      'search_filters' => array(),
      'search_root_kmap_path' => NULL,
      'search_root_kmapid' => '',
      'search_view' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'shanti_kmaps_fields',
      'settings' => array(),
      'type' => 'kmap_typeahead_picker',
      'weight' => 69,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Biblio Language');
  t('Biblio Long Language');
  t('Biblio Long Title');
  t('Places');

  return $field_instances;
}
