<?php
/**
 * @file
 * shanti_images_features.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function shanti_images_features_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: user-menu_add-new-collection:node/add/collection.
  $menu_links['user-menu_add-new-collection:node/add/collection'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/collection',
    'router_path' => 'node/add/collection',
    'link_title' => 'Add New Collection',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_add-new-collection:node/add/collection',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'user-menu_collections:<front>',
  );
  // Exported menu link: user-menu_all-collections:collections.
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
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'user-menu_collections:<front>',
  );
  // Exported menu link: user-menu_collections:<front>.
  $menu_links['user-menu_collections:<front>'] = array(
    'menu_name' => 'user-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Collections',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_collections:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: user-menu_my-collections:mycontent/collections.
  $menu_links['user-menu_my-collections:mycontent/collections'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'mycontent/collections',
    'router_path' => 'mycontent/collections',
    'link_title' => 'My Collections',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_my-collections:mycontent/collections',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'user-menu_collections:<front>',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Add New Collection');
  t('All Collections');
  t('Collections');
  t('My Collections');

  return $menu_links;
}
