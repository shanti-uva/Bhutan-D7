<?php
/**
 * @file
 * shanti_collections.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function shanti_collections_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:collection:add user'
  $permissions['node:collection:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:collection:administer group'
  $permissions['node:collection:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:collection:approve and deny subscription'
  $permissions['node:collection:approve and deny subscription'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:collection:create book content'
  $permissions['node:collection:create book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:collection:create post content'
  $permissions['node:collection:create post content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:collection:create subcollection content'
  $permissions['node:collection:create subcollection content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:collection:delete any book content'
  $permissions['node:collection:delete any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:collection:delete any post content'
  $permissions['node:collection:delete any post content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:collection:delete any subcollection content'
  $permissions['node:collection:delete any subcollection content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:collection:delete own book content'
  $permissions['node:collection:delete own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:collection:delete own post content'
  $permissions['node:collection:delete own post content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:collection:delete own subcollection content'
  $permissions['node:collection:delete own subcollection content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:collection:manage members'
  $permissions['node:collection:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:collection:manage permissions'
  $permissions['node:collection:manage permissions'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:collection:manage roles'
  $permissions['node:collection:manage roles'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:collection:publish any book content'
  $permissions['node:collection:publish any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:collection:publish any content'
  $permissions['node:collection:publish any content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:collection:publish editable book content'
  $permissions['node:collection:publish editable book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:collection:publish editable content'
  $permissions['node:collection:publish editable content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:collection:publish own book content'
  $permissions['node:collection:publish own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:collection:subscribe'
  $permissions['node:collection:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:collection:subscribe without approval'
  $permissions['node:collection:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:collection:unpublish any book content'
  $permissions['node:collection:unpublish any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:collection:unpublish any content'
  $permissions['node:collection:unpublish any content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:collection:unpublish editable book content'
  $permissions['node:collection:unpublish editable book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:collection:unpublish editable content'
  $permissions['node:collection:unpublish editable content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:collection:unpublish own book content'
  $permissions['node:collection:unpublish own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:collection:unsubscribe'
  $permissions['node:collection:unsubscribe'] = array(
    'roles' => array(
      'editor' => 'editor',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:collection:update any book content'
  $permissions['node:collection:update any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:collection:update any post content'
  $permissions['node:collection:update any post content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:collection:update any subcollection content'
  $permissions['node:collection:update any subcollection content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:collection:update group'
  $permissions['node:collection:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:collection:update own book content'
  $permissions['node:collection:update own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:collection:update own post content'
  $permissions['node:collection:update own post content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:collection:update own subcollection content'
  $permissions['node:collection:update own subcollection content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:subcollection:add user'
  $permissions['node:subcollection:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:subcollection:administer group'
  $permissions['node:subcollection:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:subcollection:approve and deny subscription'
  $permissions['node:subcollection:approve and deny subscription'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:subcollection:create book content'
  $permissions['node:subcollection:create book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:subcollection:create post content'
  $permissions['node:subcollection:create post content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:subcollection:create subcollection content'
  $permissions['node:subcollection:create subcollection content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:subcollection:delete any book content'
  $permissions['node:subcollection:delete any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:subcollection:delete any post content'
  $permissions['node:subcollection:delete any post content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:subcollection:delete any subcollection content'
  $permissions['node:subcollection:delete any subcollection content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:subcollection:delete own book content'
  $permissions['node:subcollection:delete own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:subcollection:delete own post content'
  $permissions['node:subcollection:delete own post content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:subcollection:delete own subcollection content'
  $permissions['node:subcollection:delete own subcollection content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:subcollection:manage members'
  $permissions['node:subcollection:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:subcollection:manage permissions'
  $permissions['node:subcollection:manage permissions'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:subcollection:manage roles'
  $permissions['node:subcollection:manage roles'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:subcollection:publish any book content'
  $permissions['node:subcollection:publish any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:subcollection:publish any content'
  $permissions['node:subcollection:publish any content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:subcollection:publish editable book content'
  $permissions['node:subcollection:publish editable book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:subcollection:publish editable content'
  $permissions['node:subcollection:publish editable content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:subcollection:publish own book content'
  $permissions['node:subcollection:publish own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:subcollection:subscribe'
  $permissions['node:subcollection:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:subcollection:subscribe without approval'
  $permissions['node:subcollection:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:subcollection:unpublish any book content'
  $permissions['node:subcollection:unpublish any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:subcollection:unpublish any content'
  $permissions['node:subcollection:unpublish any content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:subcollection:unpublish editable book content'
  $permissions['node:subcollection:unpublish editable book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:subcollection:unpublish editable content'
  $permissions['node:subcollection:unpublish editable content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:subcollection:unpublish own book content'
  $permissions['node:subcollection:unpublish own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:subcollection:unsubscribe'
  $permissions['node:subcollection:unsubscribe'] = array(
    'roles' => array(
      'editor' => 'editor',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:subcollection:update any book content'
  $permissions['node:subcollection:update any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
    ),
  );

  // Exported og permission: 'node:subcollection:update any post content'
  $permissions['node:subcollection:update any post content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:subcollection:update any subcollection content'
  $permissions['node:subcollection:update any subcollection content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:subcollection:update group'
  $permissions['node:subcollection:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:subcollection:update own book content'
  $permissions['node:subcollection:update own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'editor' => 'editor',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:subcollection:update own post content'
  $permissions['node:subcollection:update own post content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:subcollection:update own subcollection content'
  $permissions['node:subcollection:update own subcollection content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  return $permissions;
}
