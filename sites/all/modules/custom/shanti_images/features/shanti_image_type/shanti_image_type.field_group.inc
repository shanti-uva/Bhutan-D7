<?php

/**
 * @file
 * shanti_image_type.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function shanti_image_type_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_additional_technical_info|node|shanti_image|form';
  $field_group->group_name = 'group_additional_technical_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_technical';
  $field_group->data = array(
    'label' => 'Additional Info',
    'weight' => '19',
    'children' => array(
      0 => 'field_altitude',
      1 => 'field_aperture',
      2 => 'field_exposure_bias',
      3 => 'field_flash_settings',
      4 => 'field_focal_length',
      5 => 'field_iso_speed_rating',
      6 => 'field_latitude',
      7 => 'field_lens',
      8 => 'field_light_source',
      9 => 'field_longitude',
      10 => 'field_metering_mode',
      11 => 'field_noise_reduction',
      12 => 'field_sensing_method',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-additional-technical-info field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_additional_technical_info|node|shanti_image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_class|node|shanti_image|form';
  $field_group->group_name = 'group_class';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_image_form_pgs';
  $field_group->data = array(
    'label' => 'Classification',
    'weight' => '5',
    'children' => array(
      0 => 'field_classification_notes',
      1 => 'field_external_classification',
      2 => 'field_places',
      3 => 'field_subjects',
      4 => 'field_other_ids',
      5 => 'field_kmap_collections',
      6 => 'field_kmap_terms',
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
  $field_groups['group_class|node|shanti_image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_copyright|node|shanti_image|form';
  $field_group->group_name = 'group_copyright';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_image_form_pgs';
  $field_group->data = array(
    'label' => 'Copyright Information',
    'weight' => '7',
    'children' => array(
      0 => 'field_copyright_date',
      1 => 'field_copyright_holder',
      2 => 'field_copyright_statement',
      3 => 'field_rights_notes',
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
  $field_groups['group_copyright|node|shanti_image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_decriptive_page|node|shanti_image|form';
  $field_group->group_name = 'group_decriptive_page';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_image_form_pgs';
  $field_group->data = array(
    'label' => 'Description & Classification',
    'weight' => '2',
    'children' => array(
      0 => 'group_class',
      1 => 'group_descriptive',
      2 => 'group_origin',
      3 => 'group_tech',
    ),
    'format_type' => 'multipage',
    'format_settings' => array(
      'formatter' => 'no-start',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-decriptive-page',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_decriptive_page|node|shanti_image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_description|node|shanti_image|form';
  $field_group->group_name = 'group_description';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Descriptive',
    'weight' => '1',
    'children' => array(
      0 => 'body',
      1 => 'field_image_type',
      2 => 'field_image_quality',
      3 => 'field_image_summary',
      4 => 'field_image_caption',
      5 => 'field_image_note',
      6 => 'field_image_color',
      7 => 'field_image_size',
      8 => 'field_image_materials',
      9 => 'field_image_time_period',
      10 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-description field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_description|node|shanti_image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_descriptive|node|shanti_image|form';
  $field_group->group_name = 'group_descriptive';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_decriptive_page';
  $field_group->data = array(
    'label' => 'Descriptive',
    'weight' => '3',
    'children' => array(
      0 => 'body',
      1 => 'field_caption',
      2 => 'field_descriptions',
      3 => 'field_image_color',
      4 => 'field_image_materials',
      5 => 'field_image_notes',
      6 => 'field_image_quality',
      7 => 'field_image_type',
      8 => 'field_language',
      9 => 'field_physical_size',
      10 => 'field_summary',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_descriptive|node|shanti_image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|node|shanti_image|full';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '2',
    'children' => array(
      0 => 'field_classification_notes',
      1 => 'field_image_date',
      2 => 'field_image_series',
      3 => 'field_image_type',
      4 => 'field_og_collection_ref',
      5 => 'field_places',
      6 => 'field_subjects',
      7 => 'group_content_access',
      8 => 'field_external_classification',
      9 => 'field_image_descriptions',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Details',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-details field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_details|node|shanti_image|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_image_form_pgs|node|shanti_image|form';
  $field_group->group_name = 'group_image_form_pgs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Image Form Pages',
    'weight' => '0',
    'children' => array(
      0 => 'group_class',
      1 => 'group_copyright',
      2 => 'group_image_info',
      3 => 'group_images',
      4 => 'group_sponsorship',
      5 => 'group_technical',
    ),
    'format_type' => 'tabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => '',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_image_form_pgs|node|shanti_image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_image_info|node|shanti_image|form';
  $field_group->group_name = 'group_image_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_image_form_pgs';
  $field_group->data = array(
    'label' => 'Required Image Info',
    'weight' => '3',
    'children' => array(
      0 => 'field_image',
      1 => 'field_image_agents',
      2 => 'field_image_type',
      3 => 'field_license_url',
      4 => 'field_og_collection_ref',
      5 => 'group_content_access',
      6 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-image-info field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_image_info|node|shanti_image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_images|node|shanti_image|form';
  $field_group->group_name = 'group_images';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_image_form_pgs';
  $field_group->data = array(
    'label' => 'Description & Notes',
    'weight' => '4',
    'children' => array(
      0 => 'field_admin_notes',
      1 => 'field_image_descriptions',
      2 => 'field_image_notes',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Description & Notes',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_images|node|shanti_image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_origination|node|shanti_image|form';
  $field_group->group_name = 'group_origination';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Origination',
    'weight' => '3',
    'children' => array(
      0 => 'field_agents',
      1 => 'field_origin_note',
      2 => 'field_owners',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-origination field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_origination|node|shanti_image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_origin|node|shanti_image|form';
  $field_group->group_name = 'group_origin';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_image_form_pgs';
  $field_group->data = array(
    'label' => 'Origin',
    'weight' => '2',
    'children' => array(
      0 => 'field_origin_notes',
      1 => 'field_image_agents',
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
  $field_groups['group_origin|node|shanti_image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_origin|node|shanti_image|full';
  $field_group->group_name = 'group_origin';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Origin',
    'weight' => '10',
    'children' => array(
      0 => 'field_copyright_date',
      1 => 'field_copyright_holder',
      2 => 'field_copyright_statement',
      3 => 'field_license_url',
      4 => 'field_origin_notes',
      5 => 'field_rights_notes',
      6 => 'field_image_agents',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Origin',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-origin field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_origin|node|shanti_image|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_people|node|shanti_image|full';
  $field_group->group_name = 'group_people';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'People',
    'weight' => '3',
    'children' => array(
      0 => 'field_origin_notes',
      1 => 'field_image_agents',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'People',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-people field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_people|node|shanti_image|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_rights2|node|shanti_image|form';
  $field_group->group_name = 'group_rights2';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_image_form_pgs';
  $field_group->data = array(
    'label' => 'Rights',
    'weight' => '8',
    'children' => array(
      0 => 'field_license_url',
      1 => 'field_rights_notes',
      2 => 'group_copyright',
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
  $field_groups['group_rights2|node|shanti_image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_rights|node|shanti_image|full';
  $field_group->group_name = 'group_rights';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Rights & Licensing',
    'weight' => '4',
    'children' => array(
      0 => 'field_copyright_date',
      1 => 'field_copyright_holder',
      2 => 'field_copyright_statement',
      3 => 'field_license_url',
      4 => 'field_rights_notes',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Rights & Licensing',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-rights field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_rights|node|shanti_image|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sponsorship|node|shanti_image|form';
  $field_group->group_name = 'group_sponsorship';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_image_form_pgs';
  $field_group->data = array(
    'label' => 'Sponsorship and Notes',
    'weight' => '8',
    'children' => array(
      0 => 'field_general_note',
      1 => 'field_organization_name',
      2 => 'field_private_note',
      3 => 'field_project_name',
      4 => 'field_sponsor_name',
      5 => 'field_spot_feature',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-sponsorship field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_sponsorship|node|shanti_image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_technical|node|shanti_image|form';
  $field_group->group_name = 'group_technical';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_image_form_pgs';
  $field_group->data = array(
    'label' => 'Technical Details',
    'weight' => '6',
    'children' => array(
      0 => 'field_image_capture_device',
      1 => 'field_image_color',
      2 => 'field_image_digital',
      3 => 'field_image_enhancement',
      4 => 'field_image_materials',
      5 => 'field_image_quality',
      6 => 'field_image_rotation',
      7 => 'field_physical_size',
      8 => 'field_technical_notes',
      9 => 'field_original_filename',
      10 => 'group_additional_technical_info',
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
  $field_groups['group_technical|node|shanti_image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_technical|node|shanti_image|full';
  $field_group->group_name = 'group_technical';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Technical',
    'weight' => '11',
    'children' => array(
      0 => 'field_image_capture_device',
      1 => 'field_image_color',
      2 => 'field_image_digital',
      3 => 'field_image_enhancement',
      4 => 'field_image_materials',
      5 => 'field_image_quality',
      6 => 'field_image_rotation',
      7 => 'field_physical_size',
      8 => 'field_technical_notes',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Technical',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-technical field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_technical|node|shanti_image|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_tech|node|shanti_image|form';
  $field_group->group_name = 'group_tech';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_decriptive_page';
  $field_group->data = array(
    'label' => 'Technical',
    'weight' => '4',
    'children' => array(
      0 => 'field_admin_notes',
      1 => 'field_image_capture_device',
      2 => 'field_image_digital',
      3 => 'field_image_enhancement',
      4 => 'field_image_rotation',
      5 => 'field_technical_notes',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_tech|node|shanti_image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_workflow|node|shanti_image|full';
  $field_group->group_name = 'group_workflow';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'shanti_image';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Workflow',
    'weight' => '12',
    'children' => array(
      0 => 'field_admin_notes',
      1 => 'field_image_notes',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-workflow field-group-fieldset',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_workflow|node|shanti_image|full'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Additional Info');
  t('Classification');
  t('Copyright Information');
  t('Description & Classification');
  t('Description & Notes');
  t('Descriptive');
  t('Details');
  t('Image Form Pages');
  t('Origin');
  t('Origination');
  t('People');
  t('Required Image Info');
  t('Rights');
  t('Rights & Licensing');
  t('Sponsorship and Notes');
  t('Technical');
  t('Technical Details');
  t('Workflow');

  return $field_groups;
}
