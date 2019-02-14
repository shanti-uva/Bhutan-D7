<?php

/**
 * @file
 * kmaps_views_solr_features.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function kmaps_views_solr_features_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pagerer';
  $strongarm->value = array(
    'core_override_preset' => 'mandala_pager',
  );
  $export['pagerer'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pagerer.preset.mandala_pager';
  $strongarm->value = array(
    'left_pane' => array(
      'theme_name' => 'none',
    ),
    'center_pane' => array(
      'theme_name' => 'pagerer_mini',
      'theme_variables' => array(
        'pager_breaker' => '…',
        'pager_separator' => 'none',
        'range_separator' => '-',
        'display' => 'pages',
        'quantity' => '9',
        'label_display' => 'before_current',
        'current_display' => 'widget',
        'total_display' => 'after_current',
        'first_link' => 'always',
        'previous_link' => 'always',
        'next_link' => 'always',
        'last_link' => 'always',
        'widget_resize' => 1,
        'slider_action' => 'tickmark',
        'slider_action_timelapse' => '0',
        'slider_navigation_icons' => 'yes',
      ),
    ),
    'right_pane' => array(
      'theme_name' => 'none',
    ),
  );
  $export['pagerer.preset.mandala_pager'] = $strongarm;

  return $export;
}
