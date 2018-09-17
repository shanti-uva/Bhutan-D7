<?php
/**
 * @file
 * shanti_collections.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function shanti_collections_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_collection|node|subcollection|form';
  $field_group->group_name = 'group_collection';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'subcollection';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Collection',
    'weight' => '8',
    'children' => array(
      0 => 'group_group',
      1 => 'field_og_parent_collection_ref',
      2 => 'group_access',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-collection field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_collection|node|subcollection|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_content|node|subcollection|form';
  $field_group->group_name = 'group_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'subcollection';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '8',
    'children' => array(
      0 => 'body',
      1 => 'field_general_featured_image',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_content|node|subcollection|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Collection');
  t('Content');

  return $field_groups;
}
