<?php
/**
 * @file
 * shiva_views_new.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function shiva_views_new_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access media browser'.
  $permissions['access media browser'] = array(
    'name' => 'access media browser',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'media',
  );

  // Exported permission: 'create collection content'.
  $permissions['create collection content'] = array(
    'name' => 'create collection content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
