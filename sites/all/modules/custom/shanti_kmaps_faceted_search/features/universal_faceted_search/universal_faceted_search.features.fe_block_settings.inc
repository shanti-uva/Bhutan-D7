<?php
/**
 * @file
 * universal_faceted_search.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function universal_faceted_search_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['search-form'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'form',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'sarvaka_mediabase' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_mediabase',
        'weight' => -28,
      ),
      'shanti_sarvaka_texts' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'shanti_sarvaka_texts',
        'weight' => -28,
      ),
      'sarvaka_images' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_images',
        'weight' => -28,
      ),
      'sarvaka_shiva' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_shiva',
        'weight' => -28,
      ),
      'sources_theme' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -28,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -10,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['shanti_kmaps_faceted_search-kmaps_1'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'kmaps_1',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'shanti_kmaps_faceted_search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'sarvaka_mediabase' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_mediabase',
        'weight' => -26,
      ),
      'shanti_sarvaka_texts' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'shanti_sarvaka_texts',
        'weight' => -26,
      ),
      'sarvaka_images' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_images',
        'weight' => -26,
      ),
      'sarvaka_shiva' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_shiva',
        'weight' => -26,
      ),
      'sources_theme' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -26,
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

  $export['shanti_kmaps_faceted_search-kmaps_2'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'kmaps_2',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'shanti_kmaps_faceted_search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'sarvaka_mediabase' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_mediabase',
        'weight' => -25,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
      'shanti_sarvaka_texts' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'shanti_sarvaka_texts',
        'weight' => -25,
      ),
      'sarvaka_images' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_images',
        'weight' => -25,
      ),
      'sarvaka_shiva' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_shiva',
        'weight' => -25,
      ),
      'sources_theme' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -25,
      ),
    ),
    'title' => 'Subjects',
    'visibility' => 0,
  );

  $export['shanti_kmaps_faceted_search-kmaps_facets'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'kmaps_facets',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'shanti_kmaps_faceted_search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'sarvaka_mediabase' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_mediabase',
        'weight' => -27,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
      'shanti_sarvaka_texts' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'shanti_sarvaka_texts',
        'weight' => -27,
      ),
      'sarvaka_images' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_images',
        'weight' => -27,
      ),
      'sarvaka_shiva' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sarvaka_shiva',
        'weight' => -27,
      ),
      'sources_theme' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -27,
      ),
    ),
    'title' => 'Facets',
    'visibility' => 0,
  );

  $export['shanti_kmaps_faceted_search-results'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'results',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'shanti_kmaps_faceted_search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'sarvaka_mediabase' => array(
        'region' => 'search_results',
        'status' => 1,
        'theme' => 'sarvaka_mediabase',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
      'shanti_sarvaka_texts' => array(
        'region' => 'search_results',
        'status' => 1,
        'theme' => 'shanti_sarvaka_texts',
        'weight' => 0,
      ),
      'sarvaka_images' => array(
        'region' => 'search_results',
        'status' => 1,
        'theme' => 'sarvaka_images',
        'weight' => 0,
      ),
      'sarvaka_shiva' => array(
        'region' => 'search_results',
        'status' => 1,
        'theme' => 'sarvaka_shiva',
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'search_results',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
