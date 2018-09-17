<?php
/**
 * @file
 * audio_video.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function audio_video_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create audio content'.
  $permissions['create audio content'] = array(
    'name' => 'create audio content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'site admin' => 'site admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create field_workflow'.
  $permissions['create field_workflow'] = array(
    'name' => 'create field_workflow',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'site admin' => 'site admin',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create video content'.
  $permissions['create video content'] = array(
    'name' => 'create video content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'site admin' => 'site admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any audio content'.
  $permissions['delete any audio content'] = array(
    'name' => 'delete any audio content',
    'roles' => array(
      'content admin' => 'content admin',
      'site admin' => 'site admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any video content'.
  $permissions['delete any video content'] = array(
    'name' => 'delete any video content',
    'roles' => array(
      'content admin' => 'content admin',
      'site admin' => 'site admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own audio content'.
  $permissions['delete own audio content'] = array(
    'name' => 'delete own audio content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'content admin' => 'content admin',
      'site admin' => 'site admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own video content'.
  $permissions['delete own video content'] = array(
    'name' => 'delete own video content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'site admin' => 'site admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any audio content'.
  $permissions['edit any audio content'] = array(
    'name' => 'edit any audio content',
    'roles' => array(
      'content admin' => 'content admin',
      'site admin' => 'site admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any video content'.
  $permissions['edit any video content'] = array(
    'name' => 'edit any video content',
    'roles' => array(
      'content admin' => 'content admin',
      'site admin' => 'site admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit field_workflow'.
  $permissions['edit field_workflow'] = array(
    'name' => 'edit field_workflow',
    'roles' => array(
      'content admin' => 'content admin',
      'site admin' => 'site admin',
      'workflow editor' => 'workflow editor',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own audio content'.
  $permissions['edit own audio content'] = array(
    'name' => 'edit own audio content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'site admin' => 'site admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own field_workflow'.
  $permissions['edit own field_workflow'] = array(
    'name' => 'edit own field_workflow',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'site admin' => 'site admin',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own video content'.
  $permissions['edit own video content'] = array(
    'name' => 'edit own video content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'site admin' => 'site admin',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view field_workflow'.
  $permissions['view field_workflow'] = array(
    'name' => 'view field_workflow',
    'roles' => array(
      'content admin' => 'content admin',
      'site admin' => 'site admin',
      'workflow editor' => 'workflow editor',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_workflow'.
  $permissions['view own field_workflow'] = array(
    'name' => 'view own field_workflow',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'site admin' => 'site admin',
    ),
    'module' => 'field_permissions',
  );

  return $permissions;
}
