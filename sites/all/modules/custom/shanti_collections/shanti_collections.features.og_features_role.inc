<?php
/**
 * @file
 * shanti_collections.features.og_features_role.inc
 */

/**
 * Implements hook_og_features_default_roles().
 */
function shanti_collections_og_features_default_roles() {
  $roles = array();

  // Exported OG Role: 'node:collection:editor'.
  $roles['node:collection:editor'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'collection',
    'name' => 'editor',
  );

  // Exported OG Role: 'node:subcollection:editor'.
  $roles['node:subcollection:editor'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'subcollection',
    'name' => 'editor',
  );

  return $roles;
}
