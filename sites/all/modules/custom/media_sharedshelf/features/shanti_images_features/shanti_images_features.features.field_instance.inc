<?php
/**
 * @file
 * shanti_images_features.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function shanti_images_features_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'file-image-field_og_collection_ref'.
  $field_instances['file-image-field_og_collection_ref'] = array(
    'bundle' => 'image',
    'default_value' => NULL,
    'default_value_function' => '',
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
        'weight' => 13,
      ),
      'grid_details' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 9,
      ),
      'preview' => array(
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
    'entity_type' => 'file',
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
          'status' => 0,
        ),
      ),
      'user_register_form' => FALSE,
      'wysiwyg_override' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'og',
      'settings' => array(),
      'type' => 'og_complex',
      'weight' => 12,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Collection');

  return $field_instances;
}
