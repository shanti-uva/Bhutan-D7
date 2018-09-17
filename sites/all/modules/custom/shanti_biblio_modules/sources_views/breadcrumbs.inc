<?php

/**
 * @file
 */

/**
 * Returns themed breadcrumbs.
 */

/**
 *
 */
function sources_views_custom_breadcrumbs() {
  $term_id = sources_views_get_selected_collection();
  if ($term_id === FALSE || $term_id == 'All') {
    $breadcrumbs = sources_views_get_contextual_breadcrumbs();
  }
  else {
    $breadcrumbs = sources_views_get_collection_breadcrumbs($term_id);
  }
  return theme('sources_views_breadcrumbs', $breadcrumbs);
}

/**
 * If not viewing sources as a collection, breadcrumbs are based of filters
 * Set on our sources view.
 */
function sources_views_get_contextual_breadcrumbs() {
  $field_zotero_tags = isset($_GET['field_zotero_tags']) ? $_GET['field_zotero_tags'] : FALSE;
  $breadcrumb = array('name' => '', 'tid' => 0);
  if (sources_views_is_search()) {
    $breadcrumb = array('name' => t('Search Results'), 'tid' => 0);
  }
  elseif ($field_zotero_tags) {
    $term = taxonomy_term_load($field_zotero_tags);
    $breadcrumb = array('name' => t("Tagged with ") . $term->name, 'tid' => 0);
  }
  elseif (sources_views_get_selected_collection() == 'All') {
    $breadcrumb = array('name' => t('All Sources'), 'tid' => 0);
  }
  elseif (current_path() == 'node/add/biblio') {
    $breadcrumb = array('name' => t('Create a Source'), 'tid' => 0);
  }
  return array((object) $breadcrumb);
}

/**
 *
 */
function sources_views_get_collection_breadcrumbs($term_id) {
  $parents = taxonomy_get_parents_all($term_id);
  $taxonomy_terms = array_reverse($parents);
  return $taxonomy_terms;
}

/**
 *
 */
function sources_views_theme_breadcrumbs($breadcrumbs) {
  $arrow_icon = '<span class="icon shanticon-arrow3-right"></span>';
  $html = "<ol class='breadcrumb'><li><a href='#' term_id='all'>Sources:</a></li>";
  unset($breadcrumbs['theme_hook_suggestions']);
  foreach ($breadcrumbs as $index => $breadcrumb) {
    if (!isset($breadcrumb->tid)) {
      continue;
    }
    $term_id = $breadcrumb->tid;
    $html .= "<li><a href='#' term_id='" . $term_id . "'>" . $breadcrumb->name . "</a>";
    if ($index != (count($breadcrumbs) - 1)) {
      $html .= $arrow_icon;
    }
    $html .= "</li>";
  }
  $html .= '</ol>';
  return $html;
}

/**
 *
 */
function sources_views_get_breadcrumb_dropdowns() {
  $term_id = isset($_GET['field_zotero_collections']) ? $_GET['field_zotero_collections'] : FALSE;
  $terms = sources_views_get_collection_breadcrumbs($term_id);
  $dropdowns = array();
  $dropdowns[] = sources_views_all_sources_dropdown();
  $breadcrumb_column_count = 1;
  foreach ($terms as $term) {
    $dropdowns[] = sources_views_get_breadcrumb_dropdown($term, $breadcrumb_column_count);
    $breadcrumb_column_count++;
  }
  return implode("\r\n", $dropdowns);
}

/**
 * Return HTML for the dropdown that appears when clicking a collection breadcrumb.
 */
function sources_views_get_breadcrumb_dropdown($taxonomy_term, $breadcrumb_column_count) {
  $vocabulary_id = sources_views_get_collection_vocabulary_id();
  $breadcrumb = array();
  $term_list = sources_views_build_taxonomy_tree($vocabulary_id, $taxonomy_term->tid);
  if ($term_list) {
    $breadcrumb['term_name_link'] = l(t($taxonomy_term->name), '', array('fragment' => '', 'attributes' => array('class' => 'breadcrumb-dropdown-cta')));
    $breadcrumb['term_id'] = $taxonomy_term->tid;
    $breadcrumb['breadcrumb_column_id'] = $breadcrumb_column_count;
    $breadcrumb['all_sources_top_link'] = sources_views_get_all_sources_top_link($taxonomy_term);
    $breadcrumb['all_sources_sub_top_link'] = sources_views_get_all_sources_sub_top_link($taxonomy_term);
    return theme('sources_views_breadcrumb_dropdown', array('value' => $breadcrumb));
  }
}

/**
 *
 */
function sources_views_all_sources_dropdown() {
  $library_content = array(
    'all_source_link' => l(t('View all sources'), 'sources-search', array('query' => array('field_zotero_collections' => 'All', 'view_mode' => 'collection'))),
  );
  return theme('sources_views_all_sources_dropdown', array('value' => $library_content));
}
