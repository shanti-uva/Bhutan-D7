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
        'weight' => 4,
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
        'weight' => 14,
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
    'label' => 'Content Language',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
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
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 13,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 13,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_biblio_long_language',
    'label' => 'Long Title Language',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => '',
      ),
      'type' => 'options_select',
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
        'weight' => 14,
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
        'weight' => 0,
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
    'label' => 'Long Title',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
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
        'label' => 'inline',
        'module' => 'shanti_kmaps_fields',
        'settings' => array(),
        'type' => 'kmap_popover_formatter',
        'weight' => 5,
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
      'entity_translation_sync' => FALSE,
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
      'weight' => 70,
    ),
  );

  // Exported field_instance: 'node-biblio-field_kmaps_subjects'.
  $field_instances['node-biblio-field_kmaps_subjects'] = array(
    'bundle' => 'biblio',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'shanti_kmaps_fields',
        'settings' => array(),
        'type' => 'kmap_popover_formatter',
        'weight' => 8,
      ),
      'embed' => array(
        'label' => 'above',
        'module' => 'shanti_kmaps_fields',
        'settings' => array(),
        'type' => 'kmap_simple_formatter',
        'weight' => 3,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'full' => array(
        'label' => 'inline',
        'module' => 'shanti_kmaps_fields',
        'settings' => array(),
        'type' => 'kmap_popover_formatter',
        'weight' => 6,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_kmaps_subjects',
    'label' => 'Subjects',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
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

  // Exported field_instance: 'node-biblio-field_kmaps_terms'.
  $field_instances['node-biblio-field_kmaps_terms'] = array(
    'bundle' => 'biblio',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'shanti_kmaps_fields',
        'settings' => array(
          'target' => '_blank',
        ),
        'type' => 'kmap_default_formatter',
        'weight' => 17,
      ),
      'full' => array(
        'label' => 'inline',
        'module' => 'shanti_kmaps_fields',
        'settings' => array(),
        'type' => 'kmap_popover_formatter',
        'weight' => 7,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_kmaps_terms',
    'label' => 'Terms',
    'required' => 0,
    'settings' => array(
      'kmap_term_limit' => 100,
      'search_filters' => array(),
      'search_root_kmap_path' => '',
      'search_root_kmapid' => '',
      'search_view' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'shanti_kmaps_fields',
      'settings' => array(),
      'type' => 'kmap_typeahead_term_picker',
      'weight' => 71,
    ),
  );

  // Exported field_instance: 'node-biblio-field_language_kmaps'.
  $field_instances['node-biblio-field_language_kmaps'] = array(
    'bundle' => 'biblio',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'This is the main content language field for this source. Chosen from Knowledge Maps.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'shanti_kmaps_fields',
        'settings' => array(),
        'type' => 'kmap_popover_formatter',
        'weight' => 9,
      ),
      'full' => array(
        'label' => 'inline',
        'module' => 'shanti_kmaps_fields',
        'settings' => array(),
        'type' => 'kmap_popover_formatter',
        'weight' => 8,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_language_kmaps',
    'label' => 'Language (Kmaps)',
    'required' => 0,
    'settings' => array(
      'kmap_term_limit' => 100,
      'search_filters' => array(),
      'search_root_kmap_path' => 301,
      'search_root_kmapid' => 301,
      'search_view' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'shanti_kmaps_fields',
      'settings' => array(),
      'type' => 'kmap_typeahead_picker',
      'weight' => 68,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Content Language');
  t('Language (Kmaps)');
  t('Long Title');
  t('Long Title Language');
  t('Places');
  t('Subjects');
  t('Terms');
  t('This is the main content language field for this source. Chosen from Knowledge Maps.');

  return $field_instances;
}
