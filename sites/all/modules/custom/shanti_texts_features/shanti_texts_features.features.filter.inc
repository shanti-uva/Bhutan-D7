<?php
/**
 * @file
 * shanti_texts_features.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function shanti_texts_features_filter_default_formats() {
  $formats = array();

  // Exported format: Full HTML.
  $formats['full_html'] = array(
    'format' => 'full_html',
    'name' => 'Full HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => -10,
    'filters' => array(
      'media_filter' => array(
        'weight' => -50,
        'status' => 1,
        'settings' => array(),
      ),
      'media_filter_paragraph_fix' => array(
        'weight' => -49,
        'status' => 1,
        'settings' => array(
          'replace' => 0,
        ),
      ),
      'ckeditor_link_filter' => array(
        'weight' => -48,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_htmlcorrector' => array(
        'weight' => -47,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_mathjax' => array(
        'weight' => -40,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
