<?php
/**
 * @file
 * universal_faceted_search.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function universal_faceted_search_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_admin_search_navigation_mode';
  $strongarm->value = 'app';
  $export['shanti_kmaps_admin_search_navigation_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_faceted_search_block_click_action_ kmaps_1';
  $strongarm->value = 'navigate';
  $export['shanti_kmaps_faceted_search_block_click_action_ kmaps_1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_faceted_search_block_click_action_ kmaps_2';
  $strongarm->value = 'navigate';
  $export['shanti_kmaps_faceted_search_block_click_action_ kmaps_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'shanti_kmaps_faceted_search_block_click_action_ kmaps_facets';
  $strongarm->value = '';
  $export['shanti_kmaps_faceted_search_block_click_action_ kmaps_facets'] = $strongarm;

  return $export;
}
