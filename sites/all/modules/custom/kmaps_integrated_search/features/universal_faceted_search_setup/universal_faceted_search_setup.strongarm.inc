<?php

/**
 * @file
 * universal_faceted_search_setup.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function universal_faceted_search_setup_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_auto_show';
  $strongarm->value = 0;
  $export['kmaps_integrated_search_auto_show'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_click_action_ kmaps_1';
  $strongarm->value = 'navigate';
  $export['kmaps_integrated_search_block_click_action_ kmaps_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_click_action_ kmaps_2';
  $strongarm->value = 'navigate';
  $export['kmaps_integrated_search_block_click_action_ kmaps_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_click_action_ kmaps_3';
  $strongarm->value = 'navigate';
  $export['kmaps_integrated_search_block_click_action_ kmaps_3'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_click_action_ kmaps_facets';
  $strongarm->value = '';
  $export['kmaps_integrated_search_block_click_action_ kmaps_facets'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_count';
  $strongarm->value = '3';
  $export['kmaps_integrated_search_block_count'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_name_kmaps_1';
  $strongarm->value = 'Kmaps Integrated Search Block Places';
  $export['kmaps_integrated_search_block_name_kmaps_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_name_kmaps_2';
  $strongarm->value = 'Kmaps Integrated Search Block Subjects';
  $export['kmaps_integrated_search_block_name_kmaps_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_name_kmaps_3';
  $strongarm->value = 'Kmaps Integrated Search Block Terms';
  $export['kmaps_integrated_search_block_name_kmaps_3'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_name_kmaps_facets';
  $strongarm->value = 'Kmaps Integrated Search Block kmaps_facets';
  $export['kmaps_integrated_search_block_name_kmaps_facets'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_root_kmaps_1';
  $strongarm->value = '';
  $export['kmaps_integrated_search_block_root_kmaps_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_root_kmaps_2';
  $strongarm->value = '192 4833 8868 2693 5806 5807 5805 6404 6403 6793 20 6844 2823 5810 5813 5809 5808 5812 6670 302 301 2688 7174 6664 6669 274';
  $export['kmaps_integrated_search_block_root_kmaps_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_root_kmaps_3';
  $strongarm->value = '';
  $export['kmaps_integrated_search_block_root_kmaps_3'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_root_kmaps_facets';
  $strongarm->value = '';
  $export['kmaps_integrated_search_block_root_kmaps_facets'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_type_kmaps_1';
  $strongarm->value = 'places';
  $export['kmaps_integrated_search_block_type_kmaps_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_type_kmaps_2';
  $strongarm->value = 'subjects';
  $export['kmaps_integrated_search_block_type_kmaps_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_type_kmaps_3';
  $strongarm->value = 'terms';
  $export['kmaps_integrated_search_block_type_kmaps_3'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_block_type_kmaps_facets';
  $strongarm->value = 'facets';
  $export['kmaps_integrated_search_block_type_kmaps_facets'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_hide_zeros';
  $strongarm->value = 1;
  $export['kmaps_integrated_search_hide_zeros'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_items_per_page';
  $strongarm->value = '60';
  $export['kmaps_integrated_search_items_per_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_kmaps_link';
  $strongarm->value = 0;
  $export['kmaps_integrated_search_kmaps_link'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_resource_types';
  $strongarm->value = array(
    'audio-video' => 0,
    'picture' => 0,
    'sources' => 0,
    'texts' => 0,
    'visuals' => 0,
  );
  $export['kmaps_integrated_search_resource_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'kmaps_integrated_search_show_counts';
  $strongarm->value = 1;
  $export['kmaps_integrated_search_show_counts'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_admin_search_navigation_mode';
  $strongarm->value = 'app';
  $export['shanti_kmaps_admin_search_navigation_mode'] = $strongarm;

  return $export;
}
