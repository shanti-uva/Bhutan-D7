<?php
/**
 * @file
 * bhutan_spash_page.features.inc
 */

/**
 * Implements hook_node_info().
 */
function bhutan_spash_page_node_info() {
  $items = array(
    'splash_page' => array(
      'name' => t('Splash Page'),
      'base' => 'node_content',
      'description' => t('Content type used for project introductions, primarily home pages'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
