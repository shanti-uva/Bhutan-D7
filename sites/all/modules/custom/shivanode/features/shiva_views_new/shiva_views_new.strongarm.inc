<?php
/**
 * @file
 * shiva_views_new.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function shiva_views_new_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pagerer.preset.pagerer_core';
  $strongarm->value = array(
    'left_pane' => array(
      'theme_name' => 'none',
    ),
    'center_pane' => array(
      'theme_name' => 'pagerer_mini',
      'theme_variables' => array(
        'pager_breaker' => '…',
        'pager_separator' => 'none',
        'range_separator' => '-',
        'display' => 'pages',
        'quantity' => '9',
        'label_display' => 'before_current',
        'current_display' => 'widget',
        'total_display' => 'after_current',
        'first_link' => 'always',
        'previous_link' => 'always',
        'next_link' => 'always',
        'last_link' => 'always',
        'widget_resize' => 1,
        'slider_action' => 'tickmark',
        'slider_action_timelapse' => '0',
        'slider_navigation_icons' => 'yes',
      ),
    ),
    'right_pane' => array(
      'theme_name' => 'none',
    ),
  );
  $export['pagerer.preset.pagerer_core'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_collection_pattern';
  $strongarm->value = 'collection/[node:title]';
  $export['pathauto_node_collection_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_shivanode_pattern';
  $strongarm->value = 'visual/[node:title]';
  $export['pathauto_node_shivanode_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_subcollection_pattern';
  $strongarm->value = 'collection/[node:title]';
  $export['pathauto_node_subcollection_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_facets_block_name_1';
  $strongarm->value = 'Kmaps Facet Block 1 Subjects';
  $export['shanti_kmaps_facets_block_name_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_facets_block_name_2';
  $strongarm->value = 'Kmaps Facet Block 2 Places';
  $export['shanti_kmaps_facets_block_name_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_facets_block_root_1';
  $strongarm->value = '8868 6793 6404 6664 7174 6844 6403 6653';
  $export['shanti_kmaps_facets_block_root_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_facets_block_root_2';
  $strongarm->value = '13735';
  $export['shanti_kmaps_facets_block_root_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_facets_block_type_1';
  $strongarm->value = 'subjects';
  $export['shanti_kmaps_facets_block_type_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_facets_block_type_2';
  $strongarm->value = 'places';
  $export['shanti_kmaps_facets_block_type_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_facets_hide_zeros';
  $strongarm->value = 1;
  $export['shanti_kmaps_facets_hide_zeros'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_facets_items_per_page';
  $strongarm->value = '60';
  $export['shanti_kmaps_facets_items_per_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_facets_resource_types';
  $strongarm->value = array(
    'visuals' => 'visuals',
    'audio-video' => 0,
    'photos' => 0,
    'sources' => 0,
    'texts' => 0,
  );
  $export['shanti_kmaps_facets_resource_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_facets_show_counts';
  $strongarm->value = 1;
  $export['shanti_kmaps_facets_show_counts'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_facets_use_bs_tabs';
  $strongarm->value = 1;
  $export['shanti_kmaps_facets_use_bs_tabs'] = $strongarm;

  return $export;
}
