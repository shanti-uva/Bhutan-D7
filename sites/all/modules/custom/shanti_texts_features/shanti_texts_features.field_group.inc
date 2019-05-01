<?php

/**
 * @file
 * shanti_texts_features.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function shanti_texts_features_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_book_admin|node|book|form';
  $field_group->group_name = 'group_book_admin';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'book';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Admin',
    'weight' => '6',
    'children' => array(
      0 => 'field_admin_status',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_book_admin|node|book|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_book_content|node|book|form';
  $field_group->group_name = 'group_book_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'book';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '1',
    'children' => array(
      0 => 'field_book_content',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_book_content|node|book|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_book_metadata|node|book|form';
  $field_group->group_name = 'group_book_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'book';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Catalog Data',
    'weight' => '4',
    'children' => array(
      0 => 'field_book_author',
      1 => 'field_book_date',
      2 => 'field_dc_date_orginial_year',
      3 => 'field_dc_date_publication_year',
      4 => 'field_dc_description',
      5 => 'field_dc_language_original',
      6 => 'field_dc_rights_creativecommons',
      7 => 'field_dc_rights_general',
      8 => 'field_general_featured_image',
      9 => 'field_book_editor',
      10 => 'field_book_translator',
      11 => 'field_dc_lang_code',
      12 => 'field_pdf_version',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_book_metadata|node|book|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_collection|node|book|form';
  $field_group->group_name = 'group_collection';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'book';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Collection',
    'weight' => '5',
    'children' => array(
      0 => 'field_og_collection_ref',
      1 => 'group_content_access',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_collection|node|book|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_kmap_terms|node|book|form';
  $field_group->group_name = 'group_kmap_terms';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'book';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Knowledge Maps',
    'weight' => '3',
    'children' => array(
      0 => 'field_kmap_places',
      1 => 'field_kmap_term',
      2 => 'field_language_kmap',
      3 => 'field_kmap_terms',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Knowledge Maps',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_kmap_terms|node|book|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_text_splitter|node|book|form';
  $field_group->group_name = 'group_text_splitter';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'book';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Shanti Texts Splitter',
    'weight' => '2',
    'children' => array(
      0 => 'field_split_headings',
      1 => 'field_split_text',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Shanti Texts Splitter',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'text-splitter-group',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_text_splitter|node|book|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Admin');
  t('Catalog Data');
  t('Collection');
  t('Content');
  t('Knowledge Maps');
  t('Shanti Texts Splitter');

  return $field_groups;
}
