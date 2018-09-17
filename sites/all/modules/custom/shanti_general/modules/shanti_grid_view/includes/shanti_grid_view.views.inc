<?php

/**
 * Implements of hook_views_plugins(). Adds a view style to views UI interface.
 */
function shanti_grid_view_views_plugins() {
  return array(
    'style' => array(
      'shanti_grid_view' => array(
        'title' => t('Shanti Grid View'),
        'help' => t('Displays images in a Google-like grid view'),
        'handler' => 'shanti_grid_view_plugin_style',
        'theme' => 'shanti_grid_view_gallery',
        'theme path' => drupal_get_path('module', 'shanti_grid_view') . '/includes',
        'path' => drupal_get_path('module', 'shanti_grid_view') . '/includes',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'even empty' => TRUE,
      ),
    ),
  );
}