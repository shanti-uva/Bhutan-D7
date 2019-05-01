<?php

/**
 * @file
 * biblio_long_fields.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function biblio_long_fields_defaultconfig_features() {
  return array(
    'biblio_long_fields' => array(
      'field_default_fields' => 'field_default_fields',
    ),
  );
}

/**
 * Implements hook_defaultconfig_field_default_fields().
 */
function biblio_long_fields_defaultconfig_field_default_fields() {
  $fields = array();

  // Exported field: 'node-biblio-field_biblio_long_language'.
  $fields['node-biblio-field_biblio_long_language'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_biblio_long_language',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => 0,
      'module' => 'text',
      'settings' => array(),
      'translatable' => 0,
      'type' => 'text_long',
    ),
    'field_instance' => array(
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
    ),
  );

  // Exported field: 'node-biblio-field_biblio_long_title'.
  $fields['node-biblio-field_biblio_long_title'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_biblio_long_title',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => 0,
      'module' => 'text',
      'settings' => array(
        'entity_translation_sync' => FALSE,
      ),
      'translatable' => 0,
      'type' => 'text_long',
    ),
    'field_instance' => array(
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
    ),
  );

  // Exported field: 'node-biblio-field_kmaps_places'.
  $fields['node-biblio-field_kmaps_places'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => -1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_kmaps_places',
      'foreign keys' => array(),
      'indexes' => array(
        'id' => array(
          0 => 'id',
        ),
      ),
      'locked' => 0,
      'module' => 'shanti_kmaps_fields',
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'kmap_domain' => 'places',
      ),
      'translatable' => 0,
      'type' => 'shanti_kmaps_fields_default',
    ),
    'field_instance' => array(
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
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Long Title');
  t('Long Title Language');
  t('Places');

  return $fields;
}
