<?php

/**
 * @file
 * shanti_image_type.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function shanti_image_type_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_external_classification';
  $strongarm->value = 0;
  $export['comment_anonymous_external_classification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_image_agent';
  $strongarm->value = 0;
  $export['comment_anonymous_image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_image_descriptions';
  $strongarm->value = 0;
  $export['comment_anonymous_image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_shanti_image';
  $strongarm->value = 0;
  $export['comment_anonymous_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_external_classification';
  $strongarm->value = 0;
  $export['comment_default_mode_external_classification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_image_agent';
  $strongarm->value = 0;
  $export['comment_default_mode_image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_image_descriptions';
  $strongarm->value = 0;
  $export['comment_default_mode_image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_shanti_image';
  $strongarm->value = 0;
  $export['comment_default_mode_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_external_classification';
  $strongarm->value = '10';
  $export['comment_default_per_page_external_classification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_image_agent';
  $strongarm->value = '10';
  $export['comment_default_per_page_image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_image_descriptions';
  $strongarm->value = '10';
  $export['comment_default_per_page_image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_shanti_image';
  $strongarm->value = '50';
  $export['comment_default_per_page_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_external_classification';
  $strongarm->value = '1';
  $export['comment_external_classification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_external_classification';
  $strongarm->value = 0;
  $export['comment_form_location_external_classification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_image_agent';
  $strongarm->value = 0;
  $export['comment_form_location_image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_image_descriptions';
  $strongarm->value = 0;
  $export['comment_form_location_image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_shanti_image';
  $strongarm->value = 1;
  $export['comment_form_location_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_image_agent';
  $strongarm->value = '1';
  $export['comment_image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_image_descriptions';
  $strongarm->value = '1';
  $export['comment_image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_external_classification';
  $strongarm->value = '0';
  $export['comment_preview_external_classification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_image_agent';
  $strongarm->value = '0';
  $export['comment_preview_image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_image_descriptions';
  $strongarm->value = '0';
  $export['comment_preview_image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_shanti_image';
  $strongarm->value = '0';
  $export['comment_preview_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_shanti_image';
  $strongarm->value = '1';
  $export['comment_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_external_classification';
  $strongarm->value = 0;
  $export['comment_subject_field_external_classification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_image_agent';
  $strongarm->value = 0;
  $export['comment_subject_field_image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_image_descriptions';
  $strongarm->value = 0;
  $export['comment_subject_field_image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_shanti_image';
  $strongarm->value = 1;
  $export['comment_subject_field_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_image_agent';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_image_descriptions';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_shanti_image';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_image_agent';
  $strongarm->value = 1;
  $export['diff_show_preview_changes_node_image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_image_descriptions';
  $strongarm->value = 1;
  $export['diff_show_preview_changes_node_image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_shanti_image';
  $strongarm->value = 1;
  $export['diff_show_preview_changes_node_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_image_agent';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_image_descriptions';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_shanti_image';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__external_classification';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'node_teaser' => array(
        'custom_settings' => TRUE,
      ),
      'shanti_grid_details' => array(
        'custom_settings' => TRUE,
      ),
      'shanti_grid_desc' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'node_full' => array(
        'custom_settings' => FALSE,
      ),
      'node_rss' => array(
        'custom_settings' => FALSE,
      ),
      'node_search_index' => array(
        'custom_settings' => FALSE,
      ),
      'node_search_result' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'revision' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'node_diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_full' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_teaser' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_rss' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_search_index' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_search_result' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'grid_details' => array(
        'custom_settings' => TRUE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '1',
        ),
        'path' => array(
          'weight' => '5',
        ),
        'redirect' => array(
          'weight' => '4',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__external_classification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__image_agent';
  $strongarm->value = array(
    'view_modes' => array(
      'full' => array(
        'custom_settings' => TRUE,
      ),
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'node_teaser' => array(
        'custom_settings' => TRUE,
      ),
      'shanti_grid_details' => array(
        'custom_settings' => TRUE,
      ),
      'shanti_grid_desc' => array(
        'custom_settings' => TRUE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'node_full' => array(
        'custom_settings' => FALSE,
      ),
      'node_rss' => array(
        'custom_settings' => FALSE,
      ),
      'node_search_index' => array(
        'custom_settings' => FALSE,
      ),
      'node_search_result' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'revision' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '6',
        ),
        'redirect' => array(
          'weight' => '5',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__image_descriptions';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'node_teaser' => array(
        'custom_settings' => TRUE,
      ),
      'shanti_grid_details' => array(
        'custom_settings' => TRUE,
      ),
      'shanti_grid_desc' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => TRUE,
      ),
      'node_full' => array(
        'custom_settings' => FALSE,
      ),
      'node_rss' => array(
        'custom_settings' => FALSE,
      ),
      'node_search_index' => array(
        'custom_settings' => FALSE,
      ),
      'node_search_result' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_full' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_teaser' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_rss' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_search_index' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_search_result' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'revision' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'node_diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'grid_details' => array(
        'custom_settings' => TRUE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '5',
        ),
        'redirect' => array(
          'weight' => '5',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__shanti_image';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => TRUE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'revision' => array(
        'custom_settings' => FALSE,
      ),
      'node_teaser' => array(
        'custom_settings' => TRUE,
      ),
      'grid_details' => array(
        'custom_settings' => TRUE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'node_full' => array(
        'custom_settings' => FALSE,
      ),
      'node_rss' => array(
        'custom_settings' => FALSE,
      ),
      'node_search_index' => array(
        'custom_settings' => FALSE,
      ),
      'node_search_result' => array(
        'custom_settings' => FALSE,
      ),
      'node_diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_full' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_teaser' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_rss' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_search_index' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_search_result' => array(
        'custom_settings' => FALSE,
      ),
      'node_node_diff_standard' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '8',
        ),
        'path' => array(
          'weight' => '2',
        ),
        'redirect' => array(
          'weight' => '3',
        ),
        'metatags' => array(
          'weight' => '4',
        ),
      ),
      'display' => array(
        'node:image_agent:all:title' => array(
          'full' => array(
            'weight' => '40',
            'visible' => FALSE,
          ),
          'shanti_grid_desc' => array(
            'weight' => '4',
            'visible' => FALSE,
          ),
          'shanti_grid_details' => array(
            'weight' => '22',
            'visible' => FALSE,
          ),
          'grid_details' => array(
            'weight' => '18',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '30',
            'visible' => FALSE,
          ),
        ),
        'node:image_agent:all:log' => array(
          'full' => array(
            'weight' => '39',
            'visible' => FALSE,
          ),
          'shanti_grid_desc' => array(
            'weight' => '6',
            'visible' => FALSE,
          ),
          'shanti_grid_details' => array(
            'weight' => '26',
            'visible' => FALSE,
          ),
          'grid_details' => array(
            'weight' => '15',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '33',
            'visible' => FALSE,
          ),
        ),
        'node:image_agent:all:field_agent_dates' => array(
          'full' => array(
            'weight' => '42',
            'visible' => FALSE,
          ),
          'shanti_grid_desc' => array(
            'weight' => '9',
            'visible' => FALSE,
          ),
          'shanti_grid_details' => array(
            'weight' => '30',
            'visible' => FALSE,
          ),
          'grid_details' => array(
            'weight' => '38',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '39',
            'visible' => FALSE,
          ),
        ),
        'node:image_agent:all:field_agent_role' => array(
          'full' => array(
            'weight' => '41',
            'visible' => FALSE,
          ),
          'shanti_grid_desc' => array(
            'weight' => '7',
            'visible' => FALSE,
          ),
          'shanti_grid_details' => array(
            'weight' => '27',
            'visible' => FALSE,
          ),
          'grid_details' => array(
            'weight' => '36',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '37',
            'visible' => FALSE,
          ),
        ),
        'node:image_agent:all:field_agent_notes' => array(
          'full' => array(
            'weight' => '44',
            'visible' => FALSE,
          ),
          'shanti_grid_desc' => array(
            'weight' => '15',
            'visible' => FALSE,
          ),
          'shanti_grid_details' => array(
            'weight' => '33',
            'visible' => FALSE,
          ),
          'grid_details' => array(
            'weight' => '42',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '43',
            'visible' => FALSE,
          ),
        ),
        'node:image_agent:all:field_agent_place' => array(
          'full' => array(
            'weight' => '43',
            'visible' => FALSE,
          ),
          'shanti_grid_desc' => array(
            'weight' => '11',
            'visible' => FALSE,
          ),
          'shanti_grid_details' => array(
            'weight' => '32',
            'visible' => FALSE,
          ),
          'grid_details' => array(
            'weight' => '41',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '41',
            'visible' => FALSE,
          ),
        ),
        'node:image_descriptions:title' => array(
          'full' => array(
            'weight' => '8',
            'visible' => FALSE,
          ),
        ),
        'node:image_descriptions:log' => array(
          'full' => array(
            'weight' => '9',
            'visible' => FALSE,
          ),
        ),
        'node:image_descriptions:field_description' => array(
          'full' => array(
            'weight' => '11',
            'visible' => FALSE,
          ),
        ),
        'node:image_descriptions:field_language' => array(
          'full' => array(
            'weight' => '12',
            'visible' => FALSE,
          ),
        ),
        'node:image_descriptions:field_summary' => array(
          'full' => array(
            'weight' => '10',
            'visible' => FALSE,
          ),
        ),
        'node:image_descriptions:field_author' => array(
          'full' => array(
            'weight' => '13',
            'visible' => FALSE,
          ),
        ),
        'node:image_descriptions:all:title' => array(
          'shanti_grid_desc' => array(
            'weight' => '1',
            'visible' => FALSE,
          ),
          'full' => array(
            'weight' => '33',
            'visible' => FALSE,
          ),
          'shanti_grid_details' => array(
            'weight' => '23',
            'visible' => FALSE,
          ),
          'grid_details' => array(
            'weight' => '16',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '35',
            'visible' => FALSE,
          ),
        ),
        'node:image_descriptions:all:log' => array(
          'shanti_grid_desc' => array(
            'weight' => '3',
            'visible' => FALSE,
          ),
          'full' => array(
            'weight' => '34',
            'visible' => FALSE,
          ),
          'shanti_grid_details' => array(
            'weight' => '24',
            'visible' => FALSE,
          ),
          'grid_details' => array(
            'weight' => '17',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '31',
            'visible' => FALSE,
          ),
        ),
        'node:image_descriptions:all:field_description' => array(
          'shanti_grid_desc' => array(
            'weight' => '10',
            'visible' => FALSE,
          ),
          'full' => array(
            'weight' => '36',
            'visible' => FALSE,
          ),
          'shanti_grid_details' => array(
            'weight' => '29',
            'visible' => FALSE,
          ),
          'grid_details' => array(
            'weight' => '39',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '38',
            'visible' => FALSE,
          ),
        ),
        'node:image_descriptions:all:field_language' => array(
          'shanti_grid_desc' => array(
            'weight' => '12',
            'visible' => FALSE,
          ),
          'full' => array(
            'weight' => '37',
            'visible' => FALSE,
          ),
          'shanti_grid_details' => array(
            'weight' => '31',
            'visible' => FALSE,
          ),
          'grid_details' => array(
            'weight' => '40',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '40',
            'visible' => FALSE,
          ),
        ),
        'node:image_descriptions:all:field_summary' => array(
          'shanti_grid_desc' => array(
            'weight' => '8',
            'visible' => FALSE,
          ),
          'full' => array(
            'weight' => '35',
            'visible' => FALSE,
          ),
          'shanti_grid_details' => array(
            'weight' => '28',
            'visible' => FALSE,
          ),
          'grid_details' => array(
            'weight' => '37',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '36',
            'visible' => FALSE,
          ),
        ),
        'node:image_descriptions:all:field_author' => array(
          'shanti_grid_desc' => array(
            'weight' => '16',
            'visible' => FALSE,
          ),
          'full' => array(
            'weight' => '38',
            'visible' => FALSE,
          ),
          'shanti_grid_details' => array(
            'weight' => '34',
            'visible' => FALSE,
          ),
          'grid_details' => array(
            'weight' => '43',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '42',
            'visible' => FALSE,
          ),
        ),
        'node:image_agent:all:feeds_item_guid' => array(
          'grid_details' => array(
            'weight' => '5',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '34',
            'visible' => FALSE,
          ),
          'full' => array(
            'weight' => '28',
            'visible' => FALSE,
          ),
        ),
        'node:image_agent:all:feeds_item_url' => array(
          'grid_details' => array(
            'weight' => '6',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '32',
            'visible' => FALSE,
          ),
          'full' => array(
            'weight' => '29',
            'visible' => FALSE,
          ),
        ),
        'node:image_descriptions:all:feeds_item_guid' => array(
          'grid_details' => array(
            'weight' => '7',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '29',
            'visible' => FALSE,
          ),
          'full' => array(
            'weight' => '31',
            'visible' => FALSE,
          ),
        ),
        'node:image_descriptions:all:feeds_item_url' => array(
          'grid_details' => array(
            'weight' => '8',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '28',
            'visible' => FALSE,
          ),
          'full' => array(
            'weight' => '32',
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_node__shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_shanti_image';
  $strongarm->value = '0';
  $export['language_content_type_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_external_classification';
  $strongarm->value = array();
  $export['menu_options_external_classification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_image_agent';
  $strongarm->value = array();
  $export['menu_options_image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_image_descriptions';
  $strongarm->value = array();
  $export['menu_options_image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_shanti_image';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_external_classification';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_external_classification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_image_agent';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_image_descriptions';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_shanti_image';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_external_classification';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_external_classification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_image_agent';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_image_descriptions';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_shanti_image';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_external_classification';
  $strongarm->value = '1';
  $export['node_preview_external_classification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_image_agent';
  $strongarm->value = '0';
  $export['node_preview_image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_image_descriptions';
  $strongarm->value = '0';
  $export['node_preview_image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_shanti_image';
  $strongarm->value = '1';
  $export['node_preview_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_external_classification';
  $strongarm->value = 0;
  $export['node_submitted_external_classification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_image_agent';
  $strongarm->value = 0;
  $export['node_submitted_image_agent'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_image_descriptions';
  $strongarm->value = 0;
  $export['node_submitted_image_descriptions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_shanti_image';
  $strongarm->value = 0;
  $export['node_submitted_shanti_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_image_agent_pattern';
  $strongarm->value = 'agent/[node:title]';
  $export['pathauto_node_image_agent_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_image_descriptions_pattern';
  $strongarm->value = 'image/desc/[node:title]';
  $export['pathauto_node_image_descriptions_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_shanti_image_pattern';
  $strongarm->value = 'image/[node:title]';
  $export['pathauto_node_shanti_image_pattern'] = $strongarm;

  return $export;
}
