<?php
/**
 * @file
 * shanti_text_import.feeds_tamper_default.inc
 */

/**
 * Implements hook_feeds_tamper_default().
 */
function shanti_text_import_feeds_tamper_default() {
  $export = array();

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'text_importer-blank_source_1-default_value';
  $feeds_tamper->importer = 'text_importer';
  $feeds_tamper->source = 'Blank source 1';
  $feeds_tamper->plugin_id = 'default_value';
  $feeds_tamper->settings = array(
    'default_value' => '12468',
    'only_if_empty' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Default Collection ID';
  $export['text_importer-blank_source_1-default_value'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'text_importer-xpathparser_1-html_entity_decode';
  $feeds_tamper->importer = 'text_importer';
  $feeds_tamper->source = 'xpathparser:1';
  $feeds_tamper->plugin_id = 'html_entity_decode';
  $feeds_tamper->settings = array();
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'HTML entity decode';
  $export['text_importer-xpathparser_1-html_entity_decode'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'text_importer-xpathparser_3-rewrite';
  $feeds_tamper->importer = 'text_importer';
  $feeds_tamper->source = 'xpathparser:3';
  $feeds_tamper->plugin_id = 'rewrite';
  $feeds_tamper->settings = array(
    'text' => 'Description ID: [xpathparser:3]',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Rewrite';
  $export['text_importer-xpathparser_3-rewrite'] = $feeds_tamper;

  return $export;
}
