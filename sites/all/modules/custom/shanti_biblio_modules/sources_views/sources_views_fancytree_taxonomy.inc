<?php

/**
 * @file
 * Format taxonomy list into json data format required to integrate with fancytree javascript.
 */

/**
 *
 */
function sources_views_build_json_taxonomy_list() {
  $vocabulary_id = sources_views_get_collection_vocabulary_id();
  $taxonomy_list_output = sources_views_get_taxonomy(sources_views_build_taxonomy_tree($vocabulary_id));
  drupal_json_output($taxonomy_list_output);
}

/**
 *
 */
function sources_views_build_json_taxonomy_filtered_list($term_id = NULL) {
  $vocabulary_id = sources_views_get_collection_vocabulary_id();
  $taxonomy_list_output = sources_views_get_breadcrumb_taxonomy(sources_views_build_taxonomy_tree($vocabulary_id, $term_id));
  drupal_json_output($taxonomy_list_output);
}

/**
 *
 */
function sources_views_fancytree_taxonomy_list() {
  $all_sources_link = l(t('Sources'), 'sources-search', array(
    'attributes' => array('class' => array('collection-library')),
    'query' => array('field_zotero_collections' => 'All', 'view_mode' => 'collection'),
  ));
  return theme('sources_fancytree_taxonomy', array('all_sources_link' => $all_sources_link));
}

/**
 *
 */
function sources_views_search_flyout_fancytree_taxonomy_list() {
  return theme('sources_fancytree_taxonomy', array('all_sources_link' => NULL));
}

/**
 *
 */
function sources_views_get_taxonomy($hierarchy) {
  $taxonomy_terms = array();
  foreach ($hierarchy as $term) {
    if (!empty($term->children)) {
      $taxonomy_terms[] = array('key' => 'collection-item-' . $term->tid, 'title' => $term->name, 'children' => sources_views_get_taxonomy($term->children));
    }
    else {
      $taxonomy_terms[] = array('key' => 'collection-item-' . $term->tid, 'title' => $term->name);
    }
  }
  return $taxonomy_terms;
}

/**
 *
 */
function sources_views_get_breadcrumb_taxonomy($hierarchy) {
  $taxonomy_terms = array();
  foreach ($hierarchy as $term) {
    if (!empty($term->children)) {
      $taxonomy_terms[] = array('key' => 'breadcrumb-collection-item-' . $term->tid, 'title' => $term->name, 'children' => sources_views_get_breadcrumb_taxonomy($term->children));
    }
    else {
      $taxonomy_terms[] = array('key' => 'breadcrumb-collection-item-' . $term->tid, 'title' => $term->name);
    }
  }
  return $taxonomy_terms;
}
