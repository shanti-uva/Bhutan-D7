<?php

/**
 * @file
 * Provide views handlers and plugins that allow usage of PHP.
 */

/**
 * Implements hook_views_data().
 */
function mb_kaltura_views_data() {
  $data['views']['total_minutes'] = array(
    'title' => t('Total AV Minutes'),
    'help' => t('Show total minutes of AV results.'),
    'area' => array(
      'help' => t('A block for the header or footer to show total minutes of an AV results page.'),
      'handler' => 'mb_kaltura_handler_area',
    ),
  );
  return $data;
}

