<?php

/**
 * @file
 * universal_faceted_search_setup.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function universal_faceted_search_setup_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'search content'.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'search',
  );

  return $permissions;
}
