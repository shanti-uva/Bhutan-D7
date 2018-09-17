<?php
/**
 * @file
 * shanti_pager.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function shanti_pager_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pagerer';
  $strongarm->value = array(
    'pagerer_enable_adaptive' => 0,
    'core_override_preset' => 'shanti_pager',
  );
  $export['pagerer'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pagerer.preset.shanti_pager';
  $strongarm->value = array(
    'left_pane' => array(
      'theme_name' => 'none',
    ),
    'center_pane' => array(
      'theme_name' => 'pagerer_mini',
    ),
    'right_pane' => array(
      'theme_name' => 'none',
    ),
  );
  $export['pagerer.preset.shanti_pager'] = $strongarm;

  return $export;
}
