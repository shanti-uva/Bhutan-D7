<?php

/**
 * @file
 * Helper methods to interact with Search API facets.
 */

/**
 *
 */
function _sources_views_current_query() {
  $searches = search_api_current_search();
  // A slight hack... technically there can be more than one active search. In this case just
  // use the 0th search.
  if (!empty($searches)) {
    $seaches = array_values($searches);
    $search = $seaches[0];
    list($current_query, $_) = $search;
    return $current_query;
  }
  return NULL;
}

/**
 *
 */
function _sources_views_current_search_index(SearchApiQuery $current_query = NULL) {
  return $current_query ? $current_query->getIndex() : search_api_index_load('database_node_index');
}

/**
 * A helper to grab facets associated with the current SearchAPI search.
 *
 * @return array
 *   Hash mapping facet names (machine name of indexed property) to an array of facet arrays. These
 *   facets have the form:
 *   - filter: the facet value
 *   - count: the facet count
 */
function _sources_views_get_current_search_facets() {
  // The strategy here is to clone the current query configuration but to strip any active
  // filters other than the non-exposed Content-Type filter defined in the view. This filter
  // limits the Nodes to type 'biblio' only. If we didn't do this, the facets returned from
  // $current_query would be facets of the current search, e.g. for filters like biblio_year
  // the resulting facet would only descibe the filtered subset of the search results.
  // Additionlly, when visiting /sources-search directly we can't be aware of the active
  // query when rendering the advanced search block. So fall back to creating a new query
  // with the best information we have available.
  $current_query = _sources_views_current_query();
  $options = $current_query ? $current_query->getOptions() : array();
  $index = _sources_views_current_search_index($current_query);
  $query = new SearchApiQuery($index, $options);
  _sources_views_set_default_query_filters($query);
  $results = $query->execute();

  return $results['search_api_facets'];
}

/**
 *
 */
function _sources_views_set_default_query_filters(&$query) {
  $query->condition('type', 'biblio', '=');
}

/**
 *
 */
function &sources_views_search_modifications($key = NULL) {
  static $drupal_static_fast;
  if (!isset($drupal_static_fast)) {
    $drupal_static_fast = &drupal_static('sources_views_solr_search_modifications');
  }
  if ($key) {
    return $drupal_static_fast[$key];
  }
  return $drupal_static_fast;
}

/**
 * Helper to take a facet filter value and get a typed value.
 *
 * @param array $facet
 * @param callable $clean
 *   Function to get a typed value from the facet filter. Defaults to intval (string -> integer)
 */
function _sources_views_get_clean_facet_filter(array $facet, callable $clean = NULL) {
  $clean = $clean ?: 'intval';
  return $clean(str_replace('"', '', $facet['filter']));
}

/**
 * Helper to use Search Api to search Solr that also includes some custom magic. See
 * the signature of sources_views_search_api_solr_query_alter for more information
 * about what and why this function does what it does.
 *
 * @param array $filters
 *   List of query filters to be applied to the search. These filters take the form of
 *   tuples of field_name, value, operator, and wildcard (optional) elements. See
 *   SearchApiQuery#condition for more insight into this implementation.
 * @param array $facet_contains
 *   List of facet contains to be applied to the search. These items take the form of
 *   tuples of facet_field_name, value elements.
 * @param array $field_list
 *   Array field names to be returned with the Solr results.
 *
 * @return array
 *   See SearchApiQuery#execute for more info. Contains 'results' array and 'search_api_facets'
 **/
function _sources_views_solr_search($filters = array(), $facet_contains = array(), $field_list = array()) {
  $search_modifications = &sources_views_search_modifications();

  if (!isset($search_modifications['field_names'])) {
    $index = _sources_views_current_search_index();
    // Load the mapping of original field names to their version in the index.
    $server = $index->server();
    $search_modifications['field_names'] = $server->getFieldNames($index);
  }
  $field_names = $search_modifications['field_names'];

  $field_list = array_map(function ($f) use ($field_names) {
    return $field_names[$f];
  }, $field_list);
  // See: sources_views_search_api_solr_query_alter.
  $search_modifications['field_list'] = $field_list;

  $search_modifications['facet_contains'] = array_map(function ($c) use ($field_names) {
    $c[0] = $field_names[$c[0]];
    return $c;
  }, $facet_contains);

  $query = new SearchApiQuery($index);
  _sources_views_set_default_query_filters($query);
  $wildcard_searches = array();
  foreach ($filters as $filter) {
    list($field, $value, $op, $wildcard) = $filter;
    if ($wildcard) {
      // Wildcard params have to be explicity appended to the query string to avoid
      // being distorted internally by search_api_solr. There should be a better way...
      $field = $field_names[$field];
      array_push($wildcard_searches, array($field, $value, $op));
    }
    else {
      $query->condition($field, $value, $op);
    }
  }
  if ($wildcard_searches) {
    // See: sources_views_search_api_solr_query_alter.
    $search_modifications['wildcard_searches'] = $wildcard_searches;
  }
  return $query->execute();
}

/**
 * Implements HOOK_search_api_solr_query_alter.
 *
 * This particular implementation is necesssary in order to bypass some of the internal
 * argument re-writing adopted by search_api_solr. In particular when using this module
 * it is near impossible to utilize Solr's wildcard searches. Additionally support for
 * custom facets (along with additonal options such as facet.contains and facet.sort) and
 * custom field (Solr's fl param) return values is severly lacking. As a result, we have to
 * utilize this hook to directly modify the call_args being sent to Solr. See the
 * implementation of SearchApiSolrService#search for more insight on this.
 *
 * This hook accomplishes a couple tasks:
 *   - Apply facet filters (i.e. f.<field>.facet.contains). This is used when we want to
 *   get a facet of the search index but also apply a search term.
 *   - Apply wildcard searches. Internally search_api and search_api_solr do some significant
 *   data-manipulation including rawurlencoding search terms. Since this automatically breaks
 *   any wild card searches we have to bypass the search_api(_solr) internals and apply the
 *   search directly.
 *   - Add additional fields to the Solr fl param. By default the returned fields are very
 *   limited and in some cases would necessitate followup MySQL queries just to fetch fields
 *   that are already in the search index. Adding needed fields to the Solr return payload
 *   allows us to bypass this.
 *   - Makes it possible to remove boost params from the query. Search API Solr automatically
 *   adds a boost of 1.0 to fulltext fields. In some cases including these boosts in the search
 *   results causes the search to return no results. See comments in sources_views_views_pre_render
 *   for more info.
 **/
function sources_views_search_api_solr_query_alter($call_args, $query) {
  $search_modifications = &sources_views_search_modifications();

  if (!isset($search_modifications['field_names'])) {
    $index = _sources_views_current_search_index();
    $server = $index->server();
    $search_modifications['field_names'] = $server->getFieldNames($index);
  }
  $field_names = $search_modifications['field_names'];

  if (array_key_exists('facet_contains', $search_modifications)) {
    $facet_filters = $search_modifications['facet_contains'];
    foreach ($facet_filters as $filter) {
      list($field, $contains) = $filter;
      $call_args['params']["f.$field.facet.contains"] = $contains;
      // TODO(samchrisinger): parameterize this-- using index sort returns facet values
      // in alphabetical order.
      $call_args['params']["f.$field.facet.sort"] = 'index';
      $call_args['params']["f.$field.facet.contains.ignoreCase"] = 'true';
    }
  }

  $title_contains_wildcard = FALSE;
  if (array_key_exists('wildcard_searches', $search_modifications)) {
    $wildcard_searches = $search_modifications['wildcard_searches'];
    foreach ($wildcard_searches as $search) {
      list($field, $value, $op) = $search;
      $title_contains_wildcard = $title_contains_wildcard || ($field == $field_names['title']);
      // TODO(samchrisinger): presumes wildcard searches all use '=' operator.
      $value = strtolower($value);
      // Whitespaces and special chars must be escaped before going to Solr.
      $value = SearchApiSolrConnection::escape($value);
      $value = str_replace(' ', '\ ', $value);
      array_push($call_args['params']['fq'], "$field:*$value*");
    }
  }

  if (!$title_contains_wildcard) {
    // Special case title.
    $title_field_name = $field_names['title'];
    array_walk($call_args['params']['fq'], function ($field, $index) use ($title_field_name, $call_args) {
      list($key, $value) = preg_split('/:/', $field, 2);
      if (strpos($key, $title_field_name) !== FALSE) {
        $value = trim($value, '"');
        $value = trim($value, ' ');
        $value = SearchApiSolrConnection::escape($value);
        $value = str_replace(' ', '\ ', $value);
        $call_args['params']['fq'][$index] = "$key:*$value*";
      }
    });
  }

  // Special case publisher, author, place of publication.
  $special_case_field_names = array('biblio_publisher', 'biblio_author', 'biblio_publish_place', 'biblio_abstract');
  array_walk($call_args['params']['fq'], function ($field, $index) use ($special_case_field_names, $call_args) {
    list($key, $value) = preg_split('/:/', $field, 2);
    if (current(array_filter($special_case_field_names, function ($field_name) use ($key) {
      return strpos($key, "search_text_$field_name") !== FALSE;
    }))) {
      $value = trim($value, '"');
      $value = trim($value, ' ');
      $value = rtrim($value, ')');
      $value = ltrim($value, '(');
      $value = SearchApiSolrConnection::escape($value);
      $value = str_replace(' ', '\ ', $value);
      $call_args['params']['fq'][$index] = "$key:(\"$value\")";
    }
  });

  // Always fetch all year facets.
  if (isset($call_args['params']['f.' . $field_names['biblio_year'] . '.facet.limit'])) {
    $call_args['params']['f.' . $field_names['biblio_year'] . '.facet.limit'] = -1;
  }

  if (array_key_exists('field_list', $search_modifications)) {
    $field_list = $search_modifications['field_list'];
    if ($field_list) {
      $call_args['params']['fl'] = $call_args['params']['fl'] . ',' . implode(',', $field_list);
    }
  }

  if (array_key_exists('skip_boosts', $search_modifications)) {
    $skip_boosts = $search_modifications['skip_boosts'];
    if ($skip_boosts) {
      unset($call_args['params']['qf']);
    };
  }

  $search_modifications = array();
}
