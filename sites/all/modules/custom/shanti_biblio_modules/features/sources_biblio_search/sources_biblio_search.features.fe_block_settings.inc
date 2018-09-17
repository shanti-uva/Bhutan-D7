<?php
/**
 * @file
 * sources_biblio_search.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sources_biblio_search_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['sources_views-advanced_search_filter'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'advanced_search_filter',
    'module' => 'sources_views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'shanti_sarvaka' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'shanti_sarvaka',
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -18,
      ),
    ),
    'title' => '<none>',
    'visibility' => 0,
  );

  $export['sources_views-custom_sort_filter'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'custom_sort_filter',
    'module' => 'sources_views',
    'node_types' => array(),
    'pages' => '<front>
sources-search',
    'roles' => array(),
    'themes' => array(
      'shanti_sarvaka' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'shanti_sarvaka',
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -16,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['sources_views-custom_taxonomy_breadcrumb'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'custom_taxonomy_breadcrumb',
    'module' => 'sources_views',
    'node_types' => array(),
    'pages' => 'sources-search
sources-search/biblio',
    'roles' => array(),
    'themes' => array(
      'shanti_sarvaka' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'shanti_sarvaka',
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'banner',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  $export['sources_views-fancytree_taxonomy_block'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'fancytree_taxonomy_block',
    'module' => 'sources_views',
    'node_types' => array(),
    'pages' => 'home-old',
    'roles' => array(),
    'themes' => array(
      'shanti_sarvaka' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'shanti_sarvaka',
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -14,
      ),
    ),
    'title' => 'Browse',
    'visibility' => 1,
  );

  $export['sources_views-fancytree_taxonomy_flyout_block'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'fancytree_taxonomy_flyout_block',
    'module' => 'sources_views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'shanti_sarvaka' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'shanti_sarvaka',
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'sources_theme',
        'weight' => -12,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['system-main'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'main',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'shanti_sarvaka' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'shanti_sarvaka',
        'weight' => -13,
      ),
      'sources_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -15,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views--exp-biblio_search_api-page'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '-exp-biblio_search_api-page',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'csc-search
csc-search/biblio',
    'roles' => array(),
    'themes' => array(
      'shanti_sarvaka' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'shanti_sarvaka',
        'weight' => -14,
      ),
      'sources_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'sources_theme',
        'weight' => -15,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-zotero_tags-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'zotero_tags-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'csc-search*',
    'roles' => array(),
    'themes' => array(
      'shanti_sarvaka' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'shanti_sarvaka',
        'weight' => 3,
      ),
      'sources_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'sources_theme',
        'weight' => 8,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  return $export;
}
