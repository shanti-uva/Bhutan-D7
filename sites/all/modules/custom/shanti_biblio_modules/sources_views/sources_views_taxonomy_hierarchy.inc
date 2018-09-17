<?php

/**
 * @file
 * Generate taxonomy term list arranged in hierarchy.
 */

/**
 * Generates & returns a nested array of taxonomy terms for the specified vocabulary id.
 */
function sources_views_build_taxonomy_tree($vid, $parent = NULL) {
  static $results;
  // If no parent term is NULL we set it to 0 by default.
  if (!$parent) {
    $parent = 0;
  }
  $args = func_get_args();
  $hash = md5(implode('-', $args));
  if (!isset($results[$hash])) {
    $terms = array();
    $data = taxonomy_get_tree($vid, $parent);
    foreach ($data as $term) {
      $terms[$term->tid] = $term;
    }
    $terms = sources_views_nest_taxonomy_terms($terms, $parent);
    $results[$hash] = $terms;
  }
  return $results[$hash];
}

/**
 * Looks for each term's parent term in the given tree and assigns the child to the parent.
 */
function sources_views_nest_taxonomy_terms($terms, $parent) {
  foreach ($terms as $term) {
    $parent_tid = isset($term->parents[0]) ? $term->parents[0] : 0;
    if ($parent_tid) {
      if (isset($terms[$parent_tid])) {
        $terms[$parent_tid]->children[$term->tid] = $term;
        unset($terms[$term->tid]);
      }
      elseif ($parent_tid != $parent) {
        sources_views_nest_taxonomy_terms_child($terms, $parent_tid, $term);
        unset($terms[$term->tid]);
      }
    }
  }
  return $terms;
}

/**
 * Recursive function which nests the child element within the appropriate parent element in the given terms tree.
 */
function sources_views_nest_taxonomy_terms_child(&$terms, $parent_tid, $child) {
  foreach ($terms as &$term) {
    if ($term->tid == $parent_tid) {
      $term->children[$child->tid] = $child;
      break;
    }
    elseif (!empty($term->children)) {
      sources_views_nest_taxonomy_terms_child($term->children, $parent_tid, $child);
    }
  }
}
