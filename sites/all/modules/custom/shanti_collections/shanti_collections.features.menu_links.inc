<?php
/**
 * @file
 * shanti_collections.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function shanti_collections_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: user-menu_create-collection:node/add/collection
  $menu_links['user-menu_create-collection:node/add/collection'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/collection',
    'router_path' => 'node/add/collection',
    'link_title' => 'Create Collection',
    'options' => array(
      'attributes' => array(
        'title' => 'Create a Collection to organize groups of texts and users',
      ),
      'identifier' => 'user-menu_create-collection:node/add/collection',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: user-menu_view-collections:collections
  $menu_links['user-menu_view-collections:collections'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'collections',
    'router_path' => 'collections',
    'link_title' => 'View Collections',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_view-collections:collections',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Create Collection');
  t('View Collections');


  return $menu_links;
}
