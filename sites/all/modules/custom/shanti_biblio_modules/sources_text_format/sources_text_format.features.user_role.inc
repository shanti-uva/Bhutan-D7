<?php
/**
 * @file
 * sources_text_format.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function sources_text_format_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  // Exported role: editor.
  $roles['editor'] = array(
    'name' => 'editor',
    'weight' => 3,
  );

  return $roles;
}
