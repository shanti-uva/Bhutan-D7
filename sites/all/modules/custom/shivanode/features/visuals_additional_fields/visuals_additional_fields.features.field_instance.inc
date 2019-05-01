<?php

/**
 * @file
 * visuals_additional_fields.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function visuals_additional_fields_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-shivanode-field_language_kmap'.
  $field_instances['node-shivanode-field_language_kmap'] = array(
    'bundle' => 'shivanode',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The main language of the visualization, if applicable.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'shanti_kmaps_fields',
        'settings' => array(),
        'type' => 'kmap_popover_formatter',
        'weight' => 10,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_language_kmap',
    'label' => 'Language (Kmap)',
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
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'node-shivanode-field_og_collection_ref'.
  $field_instances['node-shivanode-field_og_collection_ref'] = array(
    'bundle' => 'shivanode',
    'default_value' => NULL,
    'default_value_function' => 'entityreference_prepopulate_field_default_value',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 5,
      ),
      'full' => array(
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
    'field_name' => 'field_og_collection_ref',
    'label' => 'Collection',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'og_widget' => array(
          'access_override' => 0,
          'admin' => array(
            'widget_type' => 'entityreference_autocomplete',
          ),
          'default' => array(
            'widget_type' => 'options_select',
          ),
          'status' => TRUE,
        ),
        'prepopulate' => array(
          'action' => 'none',
          'action_on_edit' => 0,
          'fallback' => 'none',
          'providers' => array(
            'og_context' => 0,
            'url' => 1,
          ),
          'skip_perm' => 0,
          'status' => 1,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'og',
      'settings' => array(),
      'type' => 'og_complex',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-shivanode-field_places_kmap'.
  $field_instances['node-shivanode-field_places_kmap'] = array(
    'bundle' => 'shivanode',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
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
    'field_name' => 'field_places_kmap',
    'label' => 'Places',
    'required' => 0,
    'settings' => array(
      'kmap_term_limit' => 100,
      'search_filters' => array(
        'associated_subject' => 'associated_subject',
        'feature_type' => 'feature_type',
      ),
      'search_root_kmap_path' => '',
      'search_root_kmapid' => '',
      'search_view' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'shanti_kmaps_fields',
      'settings' => array(),
      'type' => 'kmap_typeahead_picker',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-shivanode-field_subjects_kmap'.
  $field_instances['node-shivanode-field_subjects_kmap'] = array(
    'bundle' => 'shivanode',
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
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_subjects_kmap',
    'label' => 'Subjects',
    'required' => 0,
    'settings' => array(
      'kmap_term_limit' => 100,
      'search_filters' => array(),
      'search_root_kmap_path' => NULL,
      'search_root_kmapid' => NULL,
      'search_view' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'shanti_kmaps_fields',
      'settings' => array(),
      'type' => 'kmap_typeahead_picker',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-shivanode-field_terms_kmap'.
  $field_instances['node-shivanode-field_terms_kmap'] = array(
    'bundle' => 'shivanode',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'shanti_kmaps_fields',
        'settings' => array(),
        'type' => 'kmap_popover_formatter',
        'weight' => 11,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_terms_kmap',
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
      'weight' => 12,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Collection');
  t('Language (Kmap)');
  t('Places');
  t('Subjects');
  t('Terms');
  t('The main language of the visualization, if applicable.');

  return $field_instances;
}
