<?php
/**
 * @file
 * shiva_views_new.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function shiva_views_new_menu_default_menu_links() {
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
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'user-menu_collections:<front>',
  );
  // Exported menu link: user-menu_all-collections:collections/all.
  $menu_links['user-menu_all-collections:collections/all'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'collections/all',
    'router_path' => 'collections/all',
    'link_title' => 'All Collections',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_all-collections:collections/all',
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
  // Exported menu link: user-menu_create:create.
  $menu_links['user-menu_create:create'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'create',
    'router_path' => 'create',
    'link_title' => 'Create',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_create:create',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: user-menu_explore:explore.
  $menu_links['user-menu_explore:explore'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'explore',
    'router_path' => 'explore',
    'link_title' => 'Explore',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_explore:explore',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
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
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'user-menu_my-content:mycontent/visuals',
  );
  // Exported menu link: user-menu_my-content:mycontent/visuals.
  $menu_links['user-menu_my-content:mycontent/visuals'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'mycontent/visuals',
    'router_path' => 'mycontent/visuals',
    'link_title' => 'My Content',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_my-content:mycontent/visuals',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: user-menu_my-visualizations:mycontent/visuals.
  $menu_links['user-menu_my-visualizations:mycontent/visuals'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'mycontent/visuals',
    'router_path' => 'mycontent/visuals',
    'link_title' => 'My Visualizations',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_my-visualizations:mycontent/visuals',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'user-menu_my-content:mycontent/visuals',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Add New Collection');
  t('All Collections');
  t('Collections');
  t('Create');
  t('Explore');
  t('My Collections');
  t('My Content');
  t('My Visualizations');

  return $menu_links;
}
