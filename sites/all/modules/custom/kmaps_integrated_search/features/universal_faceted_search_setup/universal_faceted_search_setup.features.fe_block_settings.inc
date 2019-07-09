<?php

/**
 * @file
 * universal_faceted_search_setup.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function universal_faceted_search_setup_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['kmaps_integrated_search-kmaps_1'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'kmaps_1',
    'module' => 'kmaps_integrated_search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'sarvaka_kmaps' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_kmaps',
        'weight' => 0,
      ),
      'sarvaka_images' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_images',
        'weight' => 0,
      ),
      'sarvaka_mediabase' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_mediabase',
        'weight' => 0,
      ),
      'sarvaka_shiva' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_shiva',
        'weight' => 0,
      ),
      'shanti_sarvaka_texts' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'shanti_sarvaka_texts',
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Places',
    'visibility' => 0,
  );

  $export['kmaps_integrated_search-kmaps_2'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'kmaps_2',
    'module' => 'kmaps_integrated_search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'sarvaka_kmaps' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_kmaps',
        'weight' => 0,
      ),
      'sarvaka_images' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_images',
        'weight' => 0,
      ),
      'sarvaka_mediabase' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_mediabase',
        'weight' => 0,
      ),
      'sarvaka_shiva' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_shiva',
        'weight' => 0,
      ),
      'shanti_sarvaka_texts' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'shanti_sarvaka_texts',
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Subjects',
    'visibility' => 0,
  );

  $export['kmaps_integrated_search-kmaps_3'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'kmaps_3',
    'module' => 'kmaps_integrated_search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'sarvaka_kmaps' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_kmaps',
        'weight' => 0,
      ),
      'sarvaka_images' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_images',
        'weight' => 0,
      ),
      'sarvaka_mediabase' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_mediabase',
        'weight' => 0,
      ),
      'sarvaka_shiva' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_shiva',
        'weight' => 0,
      ),
      'shanti_sarvaka_texts' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'shanti_sarvaka_texts',
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Terms',
    'visibility' => 0,
  );

  $export['kmaps_integrated_search-kmaps_facets'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'kmaps_facets',
    'module' => 'kmaps_integrated_search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'sarvaka_kmaps' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_kmaps',
        'weight' => -7,
      ),
      'sarvaka_images' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_images',
        'weight' => -7,
      ),
      'sarvaka_mediabase' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_mediabase',
        'weight' => -7,
      ),
      'sarvaka_shiva' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_shiva',
        'weight' => -7,
      ),
      'shanti_sarvaka_texts' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'shanti_sarvaka_texts',
        'weight' => -7,
      ),
      'sources_theme' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -7,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -7,
      ),
    ),
    'title' => 'Facets',
    'visibility' => 0,
  );

  $export['kmaps_integrated_search-results'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'results',
    'module' => 'kmaps_integrated_search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'sarvaka_kmaps' => array(
        'region' => 'search_results',
        'status' => 1,
        'theme' => 'sarvaka_kmaps',
        'weight' => 0,
      ),
      'sarvaka_images' => array(
        'region' => 'search_results',
        'status' => 1,
        'theme' => 'sarvaka_images',
        'weight' => 0,
      ),
      'sarvaka_mediabase' => array(
        'region' => 'search_results',
        'status' => 1,
        'theme' => 'sarvaka_mediabase',
        'weight' => 0,
      ),
      'sarvaka_shiva' => array(
        'region' => 'search_results',
        'status' => 1,
        'theme' => 'sarvaka_shiva',
        'weight' => 0,
      ),
      'shanti_sarvaka_texts' => array(
        'region' => 'search_results',
        'status' => 1,
        'theme' => 'shanti_sarvaka_texts',
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['search-form'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'form',
    'module' => 'search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'administrator' => 3,
      'anonymous user' => 1,
      'authenticated user' => 2,
    ),
    'themes' => array(
      'sarvaka_kmaps' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_kmaps',
        'weight' => -18,
      ),
      'sarvaka_images' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_images',
        'weight' => -18,
      ),
      'sarvaka_mediabase' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_mediabase',
        'weight' => -18,
      ),
      'sarvaka_shiva' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_shiva',
        'weight' => -18,
      ),
      'shanti_sarvaka_texts' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'shanti_sarvaka_texts',
        'weight' => -18,
      ),
      'sources_theme' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -18,
      ),
      'seven' => array(
        'region' => 'dashboard_sidebar',
        'status' => 1,
        'theme' => 'seven',
        'weight' => -10,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
