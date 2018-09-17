<?php
/**
 * @file
 * sources_collection_views_links.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sources_collection_views_links_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: user-menu_all-collections:collections
  $menu_links['user-menu_all-collections:collections'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'collections',
    'router_path' => 'collections',
    'link_title' => 'All Collections',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_all-collections:collections',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'user-menu_collections:collections',
  );
  // Exported menu link: user-menu_collections:collections
  $menu_links['user-menu_collections:collections'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'collections',
    'router_path' => 'collections',
    'link_title' => 'Collections',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_collections:collections',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: user-menu_create-a-biblio-entry:node/add/biblio
  $menu_links['user-menu_create-a-biblio-entry:node/add/biblio'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/biblio',
    'router_path' => 'node/add/biblio',
    'link_title' => 'Create a Biblio Entry',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_create-a-biblio-entry:node/add/biblio',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: user-menu_create-new-collection:node/add/collection
  $menu_links['user-menu_create-new-collection:node/add/collection'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/collection',
    'router_path' => 'node/add/collection',
    'link_title' => 'Create New Collection',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_create-new-collection:node/add/collection',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 5,
    'customized' => 1,
    'parent_identifier' => 'user-menu_collections:collections',
  );
  // Exported menu link: user-menu_my-collections:my_collections
  $menu_links['user-menu_my-collections:my_collections'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'my_collections',
    'router_path' => 'my_collections',
    'link_title' => 'My Collections',
    'options' => array(
      'identifier' => 'user-menu_my-collections:my_collections',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'user-menu_collections:collections',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('All Collections');
  t('Collections');
  t('Create New Collection');
  t('Create a Biblio Entry');
  t('My Collections');


  return $menu_links;
}
