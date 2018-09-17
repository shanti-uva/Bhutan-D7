<?php
/**
 * @file
 * shanti_collections.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function shanti_collections_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer group'.
  $permissions['administer group'] = array(
    'name' => 'administer group',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'og',
  );

  // Exported permission: 'create subcollection content'.
  $permissions['create subcollection content'] = array(
    'name' => 'create subcollection content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any collection content'.
  $permissions['delete any collection content'] = array(
    'name' => 'delete any collection content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any subcollection content'.
  $permissions['delete any subcollection content'] = array(
    'name' => 'delete any subcollection content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own collection content'.
  $permissions['delete own collection content'] = array(
    'name' => 'delete own collection content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own subcollection content'.
  $permissions['delete own subcollection content'] = array(
    'name' => 'delete own subcollection content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any collection content'.
  $permissions['edit any collection content'] = array(
    'name' => 'edit any collection content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any subcollection content'.
  $permissions['edit any subcollection content'] = array(
    'name' => 'edit any subcollection content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own collection content'.
  $permissions['edit own collection content'] = array(
    'name' => 'edit own collection content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own subcollection content'.
  $permissions['edit own subcollection content'] = array(
    'name' => 'edit own subcollection content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
