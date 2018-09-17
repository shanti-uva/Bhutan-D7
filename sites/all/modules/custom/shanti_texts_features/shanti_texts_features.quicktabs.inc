<?php
/**
 * @file
 * shanti_texts_features.quicktabs.inc
 */

/**
 * Implements hook_quicktabs_default_quicktabs().
 */
function shanti_texts_features_quicktabs_default_quicktabs() {
  $export = array();

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'search_qt';
  $quicktabs->ajax = 0;
  $quicktabs->hide_empty_tabs = FALSE;
  $quicktabs->default_tab = 0;
  $quicktabs->title = 'Search';
  $quicktabs->tabs = array(
    0 => array(
      'vid' => 'text_search',
      'display' => 'block_3',
      'args' => '',
      'title' => 'Title',
      'weight' => '-100',
      'type' => 'view',
    ),
    1 => array(
      'vid' => 'full_text_local',
      'display' => 'block_1',
      'args' => '',
      'title' => 'Full Text',
      'weight' => '-99',
      'type' => 'view',
    ),
  );
  $quicktabs->renderer = 'bh_bootstrapquicktabs_tabs';
  $quicktabs->style = 'default';
  $quicktabs->options = array(
    'tabtype' => 'basic',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Full Text');
  t('Search');
  t('Title');

  $export['search_qt'] = $quicktabs;

  return $export;
}
