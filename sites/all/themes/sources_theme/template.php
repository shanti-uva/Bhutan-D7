<?php

/**
 * @file
 * template.php
 */

 /**
  *   This is the template.php file for a child sub-theme of the Shanti Sarvaka theme.
  *   Use it to implement custom functions or override existing functions in the theme.
  */

/**
 * Implements HOOK_breadcrumb
 * Customizes output of breadcrumbs
 */
function sources_theme_breadcrumb(&$bcs) {
  $obj = menu_get_object();
  if (!empty($obj)) {
    // Biblio pages
    if ($obj->type == 'biblio') { // add collection & subcollection breadcrumbs to biblio pages
      /*dpm($obj, 'node');
        dpm($bcs);*/
      if (!empty($obj->field_og_collection_ref)) {
        $gid = $obj->field_og_collection_ref['und'][0]['target_id'];
        $gnode = node_load($gid);
        if ($gnode->type == "subcollection") {
          $bc = l($gnode->title, 'node/' . $gid);
          array_splice($bcs['breadcrumb'], 1, 0, array($bc));
          $gid = $gnode->field_og_parent_collection_ref['und'][0]['target_id'];
          $gnode = node_load($gid);
        }
        $bc = l($gnode->title, 'node/' . $gid);
        array_splice($bcs['breadcrumb'], 1, 0, array($bc));
        $bcout = shanti_sarvaka_breadcrumb($bcs);
        return $bcout;
      }
      // Subcollections
    } elseif($obj->type == 'subcollection') {  // Add collection breadcrumb to subcollection page
      $gid = $obj->field_og_parent_collection_ref['und'][0]['target_id'];
      $gnode = node_load($gid);
      $bc = l($gnode->title, 'node/' . $gid);
      array_splice($bcs['breadcrumb'], 1, 0, array($bc));
    }
    if (strpos($obj->type, 'collection') > -1) {
        $colllink = '<a href="/collections/all">' . t("Collections") . '</a>';
        array_splice($bcs['breadcrumb'], 1, 0, array($colllink));
    }
  }
  $bchtml = sources_views_custom_breadcrumbs();
  if ($bchtml == "<ol class='breadcrumb'><li><a href='#' term_id='all'>Sources:</a></li><li><a href='#' term_id='0'></a><span class=\"icon shanticon-arrow3-right\"></span></li></ol>") {
    $bchtml = shanti_sarvaka_breadcrumb($bcs);
  }
  return $bchtml;
}

/**
 * Implements HOOK_preprocess_html().
 */
function sources_theme_preprocess_html(&$variables) {
    $cp = current_path();
  if (strstr($cp, 'sources-search?')) { drupal_goto('home'); }
  drupal_add_js('sites/all/libraries/cookie.js/jquery.cookie.js', 'file');
  if (!sources_theme_is_front_page()) {
    sources_theme_remove_front_page_class($variables);
  }
  if(drupal_is_front_page()) {
      $variables['classes_array'][] = 'page-sources-search';
  }
}

function sources_theme_is_front_page() {
  return (drupal_is_front_page() && !$_SERVER['QUERY_STRING']);
}

function sources_theme_remove_front_page_class(&$variables) {
  if (($key = array_search('front', $variables['classes_array'])) !== FALSE) {
    unset($variables['classes_array'][$key]);
  }
}

function sources_theme_preprocess_node(&$vars) {
    //dpm($vars, 'in pp node');
    $type = $vars['type'];
    $mode = $vars['view_mode'];
    // For collections or subcollections
    if (strstr($type,'collection')) {
        // If biblio permission "import from file" is given and the biblio_import_mods module is on
        if (user_access('import from file') && module_exists('biblio_import_mods')) {
            $nid = $vars['nid'];
            $mycolls = biblio_import_mods_collections_list_options();
            $mycolls = array_keys($mycolls);
            // Only allow users to import into their own collections unless they have 'administer biblio bulkimport' privileges
            // See biblio_import_mods_permission()
            if (in_array($nid, $mycolls) || user_access('administer biblio bulkimport')) {
                $vars['import_url'] = '/biblio/import?collection=' . $nid;
            }
        }
    // Updates to Biblio Node Display
    } else if ($type == 'biblio' && $mode == 'full') {
        $url = $vars['biblio_url'];
        if (!empty($url) && isset($vars['content']['body']['#markup'])) {
            $vars['content']['body']['#markup'] .= '<div class="source-field source-field-url">
                <span class="field-label label-url">URL: </span>
                <span class="field-content"><a href="' . $url . '" target="_blank">' . $url . '</a></span>  </div>';
        }
    }
}

/**
 * Overriding theme_biblio_long($variables) in biblio_theme.inc (line 75)
 */
function sources_theme_biblio_long($variables) {
    //dpm($variables, 'Variables in source theme bibl long');
  $output = '';
  $node = $variables['node'];
  // Title Info
  if (!empty($node->field_biblio_long_title)) {
    $title = $node->field_biblio_long_title['und'][0]['safe_value'];
  } else {
    $title = $node->title;
  }
  $output .= '<!-- Title info -->
                        <div class="source-field-title"><span class="field-content"> ' . $title . '</span></div>';
  if (!empty($node->biblio_secondary_title)) {
    $output .= '<div class="source-field source-field-title-2"><span class="field-content"> ' . $node->biblio_secondary_title . '</span></div>';
  }
  if (!empty($node->biblio_tertiary_title)) {
    $output .= '<div class="source-field source-field-title-3"><span class="field-content"> ' . $node->biblio_tertiary_title . '</span></div>';
  }
  // Authors
  $auths = array();
  foreach ((array)$node->biblio_contributors as $auth) {
    $type = sources_misc_get_author_types($auth['auth_type']);
    $auths[] = theme('biblio_author_link', array('author' => $auth)) . " ({$type})";
  }
  if (!empty($auths)) {
    $output .= '<!-- Authors -->
            <div class="source-field source-field-authors"><span class="field-content"><ul><li>';
    $output .= implode(", ", $auths) . '</li></ul></span></div><!-- end of authors -->';
  }

  // Featured Image
  if (!empty($node->field_featured_image)) {
      $img_ra = field_view_field('node', $node, 'field_featured_image', 'full');
      $output .= '<div class="source-field source-field-featured-image">
                        <span class="field-content">' . render($img_ra) . "</span>  </div>\n";
  }

  // Publication Type
  $output .= '<div class="source-field source-field-biblio-type">
                        <span class="field-label label-biblio-type-1">' . t('Format') . ': </span>
                        <span class="field-content">' . $node->biblio_type_name . "</span>  </div>\n";

  // Publication Year
  $output .= '<div class="source-field source-field-biblio-year">
                        <span class="field-label label-biblio-year-1">' . t('Publication Year') . ': </span>
                        <span class="field-content">' . (($node->biblio_year != '0') ? $node->biblio_year : 'n/a') . "</span>  </div>\n";


  // Publication Info
  if (!empty($node->biblio_publisher)) {
    $output .= '<div class="source-field source-field-publisher">
                                <span class="field-label label-publisher">' . t('Publisher') . ': </span>
                                <span class="field-content">' . $node->biblio_publisher . "</span>  </div>\n";
  }
  if (!empty($node->biblio_place_published)) {
    $output .= '<div class="source-field source-field-pubplace">
                                <span class="field-label label-pubplace">' . t('Place of Publication') . ': </span>
                                <span class="field-content">' . $node->biblio_place_published . "</span>  </div>\n";
  }

  // Pages
  if (!empty($node->biblio_pages)) {
    $output .= '<div class="source-field source-field-pages">
                                <span class="field-label label-pages">' . t('Pages') . ': </span>
                                <span class="field-content">' . $node->biblio_pages . "</span>  </div>\n";
  }

  // ID
  $output .= '<div class="source-field source-field-id">
                            <span class="field-label label-id">' . t('Source ID') . ': </span>
                            <span class="field-content">shanti-sources-' . $node->biblio_citekey . "</span>  </div>\n";

  // Collection
  if (!empty($node->field_og_collection_ref['und'])) {
    $coll = $node->field_og_collection_ref['und'][0]['entity'];
    $output .= '<div class="source-field source-field-collection">
                                <span class="field-label label-collection">' . t('Collection') . ': </span>
                                <span class="field-content">' . l($coll->title, '/node/' . $coll->nid) . "</span>  </div>\n";
  }

  // Visibility
  if (!empty($node->field_group_content_access['und'][0])) {
    $output .= '<div class="source-field source-field-visibility">
                                <span class="field-label label-visibility">' . t('Visibility') . ': </span>
                                <span class="field-content">' . $node->field_group_content_access['und'][0]['#markup'] . "</span>  </div>\n";
  }

  // Zotero Collections
  $zcolls = array();
  if (!empty($node->field_zotero_collections['und'])) {
    foreach ($node->field_zotero_collections['und'] as $n => $term) {
      $term = taxonomy_term_load($term['tid']);
      if ($term) {
        $zcolls[] = l($term->name, "/sources-search?field_zotero_collections={$term->tid}&view_mode=collection");
      }
    }
  }
  if (!empty($zcolls)) {
    $output .= '<div class="source-field source-field-zotero">
                                <span class="field-label label-zotero">' . t('Zotero Collections') . ': </span>
                                <span class="field-content">' . implode($zcolls, ', ') . "</span>  </div>\n";
  }

  // Extract
  if (!empty($node->biblio_abst_e)) {
    $output .= '<div class="source-field source-field-abstract-e">
                                <span class="field-label label-abstract-e">' . t('Abstract') . ': </span>
                                <span class="field-content">' . $node->biblio_abst_e  . "</span>  </div>\n";
  }

  return $output;
}

/**
 * Implements THEME_preprocess_views_view_fields().
 */
function sources_theme_preprocess_views_view_fields(&$vars) {
  if ($vars['view']->name == 'biblio_search_api') {
    $publication_year = (!empty($vars['row']->_entity_properties['biblio_year'])) ? $vars['row']->_entity_properties['biblio_year'] : '';
    $updated_query_string_parameters = sources_theme_get_updated_query_string_parameters($vars);
    $publication_format = sources_theme_get_publication_type($vars);
    $source_title_info = sources_theme_get_source_title_info($publication_year, $publication_format);
    $custom_title_link_wrapper_prefix = '<div class="source-icon-' . $publication_format . ' title-link-container"><span class="icon shanticon-sources"></span><span class="icon shanticon-plus"></span>';
    $custom_title_link_wrapper_suffix = '</div>';
    //Display custom views field output based on current views display.
    $link = '';
    if (isset($updated_query_string_parameters['current_nid'])) {
      $node = node_load($updated_query_string_parameters['current_nid']);
      if ($node) {
        list($id, , $bundle) = entity_extract_ids('node', $node);
        $path = drupal_get_path_alias('node/' . $node->nid);
        $link = l($vars['row']->_entity_properties['title'] . $source_title_info, $path, array('html' => TRUE));
      }
    }
    switch ($vars['view']->current_display) {
      case 'page':
        $link = l($vars['row']->_entity_properties['title'] . $source_title_info, 'sources-search/biblio', array('query' => $updated_query_string_parameters, 'html' => TRUE));
        if (!isset($vars['fields']['title'])) {
          $vars['fields']['title'] = new stdClass();
        }
        $vars['fields']['title']->content = $custom_title_link_wrapper_prefix . $link . $custom_title_link_wrapper_suffix;
        break;
      case 'allpage':
        $link = l($vars['row']->_entity_properties['title'] . $source_title_info, 'sources-search/biblio/' . $updated_query_string_parameters['current_nid'], array('html' => TRUE));
        $vars['fields']['title'] = (object) array(
          "label_html" => '',
          "wrapper_prefix" => $custom_title_link_wrapper_prefix,
          "content" => $link,
          "wrapper_suffix" => $custom_title_link_wrapper_suffix,
        );
        break;
      case 'biblio_full':
        $vars['fields']['biblio_publication_type_1']->content = '<span>' . $publication_format . '</span>';
        break;
    }
  }
    // Unescape Markup in Notes
    if (!empty($vars['fields']['biblio_notes'])) {
        $cnt = $vars['fields']['biblio_notes']->content;
        $cnt = str_replace('&lt;', '<', str_replace('&gt;', '>', $cnt));
        $vars['row']->_entity_properties['biblio_notes'] = $cnt;
        $vars['fields']['biblio_notes']->content = $cnt;
    }
}

/**
 * Returns query string parameters with updated node id and page number.
 *
 */
function sources_theme_get_updated_query_string_parameters($vars) {
  $current_page = (!empty($_GET['page'])) ? intval($_GET['page']) : 0;
  $new_page = $vars['view']->row_index + (25 * $current_page);
  $current_query_strings = $_SERVER['QUERY_STRING'];
  parse_str($current_query_strings, $parsed_current_query_strings);
  $parameters = array_replace($parsed_current_query_strings, array('page' => $new_page));
  $current_node = $vars['row']->entity;
  if (is_string($current_node) || is_numeric($current_node)) {
    $parameters['current_nid'] = $current_node;
  }
  else {
    $parameters['current_nid'] = $current_node->nid;
  }
  if ($vars['view']->current_display == "allpage") {
      unset($parameters['page']);  // Page parameter is for search results
      $paranew = array(
        'field_zotero_collections' => 'All',
        'current_nid' => $parameters['current_nid'],
      );
      $parameters = $paranew;
  }
  return $parameters;
}

function sources_theme_get_publication_type($vars) {
  $publication_type_name = '';
  if (!empty($vars['row']->_entity_properties['biblio_publication_type'])) {
    $publication_type_id = $vars['row']->_entity_properties['biblio_publication_type'];
    $publication_type_name = db_query('SELECT name FROM {biblio_types} WHERE tid = :tid', array(':tid' => $publication_type_id))->fetchField();
  }
  return $publication_type_name;
}

/**
 * Returns source title with publication year and format.
 *
 */
function sources_theme_get_source_title_info($year, $publication_format) {
  if (!empty($publication_format)) {
    $publication_format = '<span class="publication-type">' . $publication_format . '</span>';
  }
  $publication_info = array($year, $publication_format);
  $source_title_info = '';
  $info_index = 1;
  foreach ($publication_info as $info) {
    if (!empty($info)) {
      if ($info_index > 1) {
        $source_title_info .= ', ' . $info;
      }
      else {
        $source_title_info .= $info;
      }
      $info_index++;
    }
  }
  if (!empty($source_title_info)) {
      $source_title_info = ' (' . $source_title_info . ')';
  }
  return $source_title_info;
}


/**
 * Hook Preprocess for Views
 *  - Circumventing the Acquia Varnish Cache
 */
function sources_theme_preprocess_views_view(&$vars)
{
    $view = $vars['view']; // Get the view
    if (isset($view->name)) {
        $nocacheviews = array(
            'collection_sources',
            'biblio_search_api',
            'sources_content_pages',
        );
        if (in_array($view->name, $nocacheviews)) {
            // Set Caching to Zero so new images show up right away
            drupal_add_http_header('Cache-Control', 'public, max-age=0');
        }
    }
}