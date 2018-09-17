<?php
/**
 * @file
 * audio_video.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function audio_video_user_default_roles() {
  $roles = array();

  // Exported role: content admin.
  $roles['content admin'] = array(
    'name' => 'content admin',
    'weight' => 3,
  );

  // Exported role: jmeter.
  $roles['jmeter'] = array(
    'name' => 'jmeter',
    'weight' => 6,
  );

  // Exported role: workflow editor.
  $roles['workflow editor'] = array(
    'name' => 'workflow editor',
    'weight' => 4,
  );

  return $roles;
}
