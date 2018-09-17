<?php
/**
 * @file
 * texts_security_settings_feature.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function texts_security_settings_feature_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-book-field_dc_lang_code'.
  $field_instances['node-book-field_dc_lang_code'] = array(
    'bundle' => 'book',
    'default_value' => array(
      0 => array(
        'value' => 'en',
      ),
    ),
    'deleted' => 0,
    'description' => 'The main language of the text in it\'s current form. For example, if translated, the language into which the text is translated. This information is used to render the text properly for reading.',
    'display' => array(
      'book_pubreader' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 24,
      ),
      'embed' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'full' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta' => array(
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
    'field_name' => 'field_dc_lang_code',
    'label' => 'Language',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 28,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Language');
  t('The main language of the text in it\'s current form. For example, if translated, the language into which the text is translated. This information is used to render the text properly for reading.');

  return $field_instances;
}
