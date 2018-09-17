<?php
/**
 * @file
 * sources_misc_config.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sources_misc_config_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: user-menu_add-a-collection:node/add/collection.
  $menu_links['user-menu_add-a-collection:node/add/collection'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/collection',
    'router_path' => 'node/add/collection',
    'link_title' => 'Add a Collection',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_add-a-collection:node/add/collection',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'user-menu_collections:mycontent/collections',
  );
  // Exported menu link: user-menu_add-a-source:node/add/biblio.
  $menu_links['user-menu_add-a-source:node/add/biblio'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/biblio',
    'router_path' => 'node/add/biblio',
    'link_title' => 'Add a Source',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_add-a-source:node/add/biblio',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
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
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'user-menu_collections:mycontent/collections',
  );
  // Exported menu link: user-menu_all-sources:<front>.
  $menu_links['user-menu_all-sources:<front>'] = array(
    'menu_name' => 'user-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'All Sources',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_all-sources:<front>',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: user-menu_collections:mycontent/collections.
  $menu_links['user-menu_collections:mycontent/collections'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'mycontent/collections',
    'router_path' => 'mycontent/collections',
    'link_title' => 'Collections',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_collections:mycontent/collections',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
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
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'user-menu_collections:mycontent/collections',
  );
  // Exported menu link: user-menu_my-content:mycontent/sources.
  $menu_links['user-menu_my-content:mycontent/sources'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'mycontent/sources',
    'router_path' => 'mycontent/sources',
    'link_title' => 'My Content',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_my-content:mycontent/sources',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: user-menu_my-sources:mycontent/sources.
  $menu_links['user-menu_my-sources:mycontent/sources'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'mycontent/sources',
    'router_path' => 'mycontent/sources',
    'link_title' => 'My Sources',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_my-sources:mycontent/sources',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'user-menu_my-content:mycontent/sources',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Add a Collection');
  t('Add a Source');
  t('All Collections');
  t('All Sources');
  t('Collections');
  t('My Collections');
  t('My Content');
  t('My Sources');

  return $menu_links;
}
