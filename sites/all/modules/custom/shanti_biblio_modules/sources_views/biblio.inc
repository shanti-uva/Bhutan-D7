<?php

/**
 * @file
 */

require_once 'facets.inc';

/**
 * Returns auto complete search values for content titles with info.
 */
function biblio_title_list_callback($string = '') {
  $string = ucfirst($string);
  $matches = array();
  if (!empty($string) && strlen($string) >= 3) {
    // Retrieve query result of each type of information.
    $titles = array_slice(biblio_list_query('custom-titles', $string), 0, 3);
    $authors = array_slice(biblio_list_query('authors', $string), 0, 3);
    $publishers = array_slice(biblio_list_query('publishers', $string), 0, 3);
    $places_published = array_slice(biblio_list_query('place_published', $string), 0, 3);
    $zotero_vocabulary = taxonomy_vocabulary_machine_name_load('zotero_tags');
    $vid = $zotero_vocabulary->vid;
    $tags = biblio_list_query('tags', $string, $vid);
    // Retrieve list of information for option list.
    $title_option_list = biblio_title_list_option($titles);
    $author_option_list = biblio_author_list_option($authors);
    $publisher_option_list = biblio_publisher_list_option($publishers);
    $place_published_option_list = biblio_place_published_list_option($places_published);
    $tag_option_list = biblio_tag_list_option($tags);
    // Merge and assign option list.
    $options = $title_option_list + $author_option_list + $publisher_option_list + $place_published_option_list + $tag_option_list;
    foreach ($options as $key => $value) {
      $matches[$key] = $value;
    }
  }
  drupal_json_output($matches);
}

/**
 * Gets a list of values from a filtered Solr facet.
 *
 * @param $field
 *   Field from search index to facet on
 * @param $string
 *   String to filter facet by. Uses f.<facetname>.facet.contains.
 * @param array $filters
 *   Option array of filters passed to _sources_views_solr_search. See that function
 *   signature for more info.
 *
 * @return array
 *   List of string values from the facet result
 **/
function _biblio_list_query_by_facet($field, $string = NULL, $filters = array()) {
  $facet_filter = ($field && $string) ? array($field, $string) : array();
  $response = _sources_views_solr_search(
    $filters,
    array($facet_filter)
  );
  $facet = $response['search_api_facets'][$field];
  return array_map(function ($item) {
    return trim($item['filter'], '"');
  }, $facet);
}

/**
 * Returns list callback query.
 *
 * @param $query_type
 *   The type of query to return.
 *
 * @param $string
 *   The filter string to use on query.
 *
 * @param $vid
 *   Vocabulary id of taxonomy tag.
 *
 * @return query result.
 */
function biblio_list_query($query_type, $string, $vid = '') {
  switch ($query_type) {
    case 'custom-titles':
      $response = _sources_views_solr_search(
        array(
          array('title', $string, '=', TRUE),
        ),
        NULL,
        array('title', 'nid', 'biblio_year', 'title_orig')
      );
      $query = array_map(function ($result) {
        $fields = $result['fields'];
        // Regular title has been passed through the ignore case filter...
        $fields['title'] = $fields['title_orig'];
        return $fields;
      }, $response['results']);
      break;

    case 'title':
      $query = _biblio_list_query_by_facet('title_orig', $string);
      break;

    case 'authors':
      $query = _biblio_list_query_by_facet('biblio_authors', $string);
      break;

    case 'publishers':
      $query = _biblio_list_query_by_facet('biblio_publisher', $string);
      break;

    case 'place_published':
      $query = _biblio_list_query_by_facet('biblio_place_published', $string);
      break;

    case 'tags':
      $query = db_query_range('SELECT name, tid FROM {taxonomy_term_data} WHERE name
        LIKE :name and vid = :vid_val ORDER BY name ASC', 0, 3, array(':name' => db_like($string) . '%', ':vid_val' => $vid));
      break;
  }
  return $query;
}

/**
 * Returns array list of biblio content titles.
 */
function biblio_title_list_option($list) {
  $option_list = array();
  if (!empty($list)) {
    $biblio_full_page = sources_views_get_views_results('biblio_search_api', 'biblio_full');
    foreach ($list as $title_key => $node) {
      $title_authors = biblio_title_authors($node['nid']);
      $current_page = biblio_current_page($biblio_full_page, $node['nid']);
      $publication_year = ($node['biblio_year'] != 0) ? '(' . $node['biblio_year'] . ')' : '';
      $option_header_text = ($title_key == 0) ? t('Titles') : '';
      $base_class_name = 'titles';
      $option_list['node=' . $node['nid'] . '=' . $current_page] = biblio_title_list_option_output($option_header_text, $base_class_name, $title_key, $node['title'], $publication_year, $title_authors);
    }
  }
  return $option_list;
}

/**
 *
 */
function _biblio_list_option($list, $type, $label, $class_name) {
  $option_list = array();
  if (!empty($list)) {
    foreach ($list as $key => $value) {
      $option_header_text = ($key == 0) ? t($label) : '';
      $option_list["$type=$value"] = biblio_title_list_option_output($option_header_text, $class_name, $key, $value);
    }
  }
  return $option_list;
}

/**
 * Returns array list of biblio content authors.
 */
function biblio_author_list_option($list) {
  return _biblio_list_option($list, 'author', 'Authors', 'authors');
}

/**
 * Returns array list of biblio content publishers.
 */
function biblio_publisher_list_option($list) {
  return _biblio_list_option($list, 'publisher', 'Publishers', 'publishers');
}

/**
 * Returns array list of biblio content publish places.
 */
function biblio_place_published_list_option($list) {
  return _biblio_list_option($list, 'publishplace', 'Place of Publication', 'place-published');
}

/**
 * Returns array list of biblio content tags.
 */
function biblio_tag_list_option($list) {
  $option_list = array();
  if ($list->rowCount() != 0) {
    foreach ($list as $tag_key => $tag) {
      $option_header_text = ($tag_key == 0) ? t('Tags') : '';
      $base_class_name = 'tags';
      $option_list['tag=' . $tag->tid] = biblio_title_list_option_output($option_header_text, $base_class_name, $tag_key, $tag->name);
    }
  }
  return $option_list;
}

/**
 * Returns html format of custom option output.
 *
 * @param $option_header_text
 *   Option header text of individual option type.
 *
 * @param $base_class_name
 *   Base class name of individual option type.
 *
 * @param $key
 *   Array key value.
 *
 * @param $value
 *   Option value.
 *
 * @param $year
 *   Publication year value.
 *
 * @param $author
 *   Author names.
 *
 * @return custom display output for option list.
 */
function biblio_title_list_option_output($option_header_text, $base_class_name, $key, $value, $year = '', $author = '') {
  $option_values = array(
    'header_label' => $option_header_text,
    'base_class_name' => $base_class_name,
    'key' => $key,
    'value' => $value,
  );
  if (!empty($year)) {
    $option_values = $option_values + array('year' => $year);
  }
  if (!empty($author)) {
    $option_values = $option_values + array('author' => $author);
  }
  return theme('sources_custom_option_list', array('option' => $option_values));
}

/**
 * Returns author list based on node id.
 *
 * @param $nid
 *   Node id to be used on querying author list.
 *
 * @return list of author names.
 */
function biblio_title_authors($nid) {
  $title_authors = _biblio_list_query_by_facet('biblio_authors', NULL, array(
    array('nid', $nid, '='),
  ));
  $authors = '';
  foreach ($title_authors as $author_data_key => $author_data) {
    $authors .= ($author_data_key != 0) ? ', ' . $author_data : $author_data;
  }
  return $authors;
}

/**
 * Returns current page of sources result.
 *
 * @param $list
 *   List of biblio content.
 *
 * @param $nid
 *   Node id of individual sources content.
 *
 * @return Current page value.
 */
function biblio_current_page($list, $nid) {
  foreach ($list as $biblio_full_result_key => $value) {
    if ($value->entity == $nid) {
      $current_page = $biblio_full_result_key;
      return $current_page;
    }
  }
}

/**
 * Helper to get auto-complete callback values.
 *
 * @param string $type
 *   Callback type, i.e. title, publishers, etc.
 * @param string $search
 *   The autocomplete search string.
 */
function _biblio_autocomplete_callback($type, $search) {
  $string = ucfirst($search);
  $matches = array();
  if (!empty($search) && strlen($search) >= 3) {
    $suggestions = biblio_list_query($type, $string);
    foreach ($suggestions as $suggestion) {
      $type_class = str_replace('_', '-', $type) . '-group';
      $matches[$suggestion] = "<span class=\"$type_class\">$suggestion</span>";
    }
  }
  drupal_json_output($matches);
}

/**
 * Returns auto complete search values for plain titles.
 */
function biblio_plain_title_list_callback($string = '') {
  return _biblio_autocomplete_callback('title', $string);
}

/**
 * Returns auto complete search values for content authors.
 */
function biblio_author_list_callback($string = '') {
  return _biblio_autocomplete_callback('authors', $string);
}

/**
 * Returns auto complete search values for content publishers.
 */
function biblio_publisher_list_callback($string = '') {
  return _biblio_autocomplete_callback('publishers', $string);
}

/**
 * Returns auto complete search values for content published places.
 */
function biblio_place_published_list_callback($string = '') {
  return _biblio_autocomplete_callback('place_published', $string);
}

/**
 * Returns auto complete search values for content abstracts.
 */
function biblio_tags_list_callback($string = '') {
  $string = ucfirst($string);
  $matches = array();
  if (!empty($string) && strlen($string) >= 3) {
    $zotero_vocabulary = taxonomy_vocabulary_machine_name_load('zotero_tags');
    $vid = $zotero_vocabulary->vid;
    $tags = biblio_list_query('tags', $string, $vid);
    if ($tags->rowCount() != 0) {
      foreach ($tags as $tag_key => $tag) {
        // $matches['tag=' . $tag->tid] = '<span class="tags-group">' . $tag->name . '</span>';.
        $matches[$tag->name] = '<span class="tags-group">' . $tag->name . '</span>';
      }
    }
  }
  drupal_json_output($matches);
}
