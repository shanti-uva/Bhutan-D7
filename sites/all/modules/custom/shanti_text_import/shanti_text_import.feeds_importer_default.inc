<?php
/**
 * @file
 * shanti_text_import.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function shanti_text_import_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'mms_text_importer';
  $feeds_importer->config = array(
    'name' => 'MMS Text Importer',
    'description' => 'To Import Texts from MMS',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml html htm',
        'delete_uploaded_file' => FALSE,
        'direct' => FALSE,
        'directory' => 'private://feeds',
        'allowed_schemes' => array(
          0 => 'public',
          1 => 'private',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsXPathParserXML',
      'config' => array(
        'sources' => array(
          'xpathparser:0' => 'title',
          'xpathparser:1' => 'content/div',
          'xpathparser:3' => 'info/div',
          'xpathparser:2' => 'authors/person/@fullname',
          'xpathparser:5' => 'created_at',
          'xpathparser:6' => '',
        ),
        'rawXML' => array(
          'xpathparser:1' => 'xpathparser:1',
          'xpathparser:0' => 0,
          'xpathparser:3' => 0,
          'xpathparser:2' => 0,
          'xpathparser:5' => 0,
          'xpathparser:6' => 0,
        ),
        'context' => '/essays/description',
        'exp' => array(
          'errors' => 0,
          'tidy' => 0,
          'tidy_encoding' => 'UTF8',
          'debug' => array(
            'context' => 0,
            'xpathparser:0' => 0,
            'xpathparser:1' => 0,
            'xpathparser:3' => 0,
            'xpathparser:2' => 0,
            'xpathparser:5' => 0,
            'xpathparser:6' => 0,
          ),
        ),
        'allow_override' => 1,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'xpathparser:0',
            'target' => 'title',
            'unique' => FALSE,
            'language' => 'und',
          ),
          1 => array(
            'source' => 'xpathparser:1',
            'target' => 'field_book_content',
            'unique' => FALSE,
            'language' => 'und',
          ),
          2 => array(
            'source' => 'xpathparser:3',
            'target' => 'field_dc_description',
            'format' => 'full_html',
            'language' => 'und',
          ),
          3 => array(
            'source' => 'xpathparser:2',
            'target' => 'field_book_author',
            'unique' => FALSE,
            'language' => 'und',
          ),
          4 => array(
            'source' => 'Blank source 1',
            'target' => 'field_og_collection_ref:etid',
            'unique' => FALSE,
            'language' => 'und',
          ),
          5 => array(
            'source' => 'xpathparser:5',
            'target' => 'created',
            'unique' => FALSE,
            'language' => 'und',
          ),
          6 => array(
            'source' => 'xpathparser:6',
            'target' => 'field_dc_date_publication_year:start',
            'unique' => FALSE,
            'language' => 'und',
          ),
        ),
        'insert_new' => '1',
        'update_existing' => '2',
        'update_non_existent' => 'skip',
        'input_format' => 'full_html',
        'skip_hash_check' => 0,
        'bundle' => 'book',
        'language' => 'und',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['mms_text_importer'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'text_importer';
  $feeds_importer->config = array(
    'name' => 'Text Importer',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'delete_uploaded_file' => FALSE,
        'direct' => FALSE,
        'directory' => 'private://feeds',
        'allowed_schemes' => array(
          0 => 'public',
          1 => 'private',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsXPathParserXML',
      'config' => array(
        'sources' => array(),
        'rawXML' => array(),
        'context' => '',
        'exp' => array(
          'errors' => FALSE,
          'tidy' => FALSE,
          'debug' => array(),
          'tidy_encoding' => 'UTF8',
        ),
        'allow_override' => TRUE,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'xpathparser:0',
            'target' => 'title',
            'unique' => FALSE,
            'language' => 'und',
          ),
          1 => array(
            'source' => 'xpathparser:1',
            'target' => 'field_book_content',
            'unique' => FALSE,
            'language' => 'und',
          ),
          2 => array(
            'source' => 'xpathparser:3',
            'target' => 'field_dc_description',
            'format' => 'full_html',
            'language' => 'und',
          ),
          3 => array(
            'source' => 'xpathparser:2',
            'target' => 'field_book_author',
            'unique' => FALSE,
            'language' => 'und',
          ),
          4 => array(
            'source' => 'Blank source 1',
            'target' => 'field_og_collection_ref:etid',
            'unique' => FALSE,
            'language' => 'und',
          ),
          5 => array(
            'source' => 'xpathparser:5',
            'target' => 'created',
            'unique' => FALSE,
            'language' => 'und',
          ),
          6 => array(
            'source' => 'xpathparser:6',
            'target' => 'field_dc_date_publication_year:start',
            'unique' => FALSE,
            'language' => 'und',
          ),
        ),
        'insert_new' => '1',
        'update_existing' => '2',
        'update_non_existent' => 'skip',
        'input_format' => 'full_html',
        'skip_hash_check' => 0,
        'bundle' => 'book',
        'language' => 'und',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['text_importer'] = $feeds_importer;

  return $export;
}
