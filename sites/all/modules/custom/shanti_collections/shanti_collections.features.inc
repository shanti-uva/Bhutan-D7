<?php
/**
 * @file
 * shanti_collections.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function shanti_collections_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ctools_custom_content" && $api == "ctools_content") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function shanti_collections_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function shanti_collections_node_info() {
  $items = array(
    'collection' => array(
      'name' => t('Collection'),
      'base' => 'node_content',
      'description' => t('Collections are used to organize media assets into broad thematic or organizational subsets that can be used to control access to their contents. Collections also contain users with assigned roles, so that project teams can collaboratively create and edit assets. Collections may also contain Subcollections, to further organize contents, users, and permissions.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'subcollection' => array(
      'name' => t('Subcollection'),
      'base' => 'node_content',
      'description' => t('Subcollections can be used to partition Collections into groups of assets and users that owner may not want shared across an entire Collection. The contents of Subcollections remain part of their parent Collections. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
