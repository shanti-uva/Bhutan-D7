<?php
/**
 * @file
 * shanti_texts_features.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function shanti_texts_features_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: user-menu_create-text:node/add/book
  $menu_links['user-menu_create-text:node/add/book'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/book',
    'router_path' => 'node/add/book',
    'link_title' => 'Create Text',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a new text',
      ),
      'identifier' => 'user-menu_create-text:node/add/book',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: user-menu_log-out:user/logout
  $menu_links['user-menu_log-out:user/logout'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log out',
    'options' => array(
      'identifier' => 'user-menu_log-out:user/logout',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: user-menu_my-texts:mytexts
  $menu_links['user-menu_my-texts:mytexts'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'mytexts',
    'router_path' => 'mytexts',
    'link_title' => 'My Texts',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_my-texts:mytexts',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: user-menu_user-account:user
  $menu_links['user-menu_user-account:user'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'User account',
    'options' => array(
      'alter' => TRUE,
      'identifier' => 'user-menu_user-account:user',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Create Text');
  t('Log out');
  t('My Texts');
  t('User account');


  return $menu_links;
}
