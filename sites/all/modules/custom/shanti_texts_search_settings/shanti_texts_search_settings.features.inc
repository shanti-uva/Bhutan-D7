<?php
/**
 * @file
 * shanti_texts_search_settings.features.inc
 */

/**
 * Implements hook_views_api().
 */
function shanti_texts_search_settings_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_search_api_index().
 */
function shanti_texts_search_settings_default_search_api_index() {
  $items = array();
  $items['full_text_local'] = entity_import('search_api_index', '{
    "name" : "Full Text Local",
    "machine_name" : "full_text_local",
    "description" : null,
    "server" : "solr_search",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [] },
      "index_directly" : 1,
      "cron_limit" : "50",
      "fields" : {
        "field_book_author" : { "type" : "list\\u003Ctext\\u003E" },
        "field_book_content:value" : { "type" : "text" },
        "field_dc_date_orginial_year" : { "type" : "date" },
        "field_dc_date_publication_year" : { "type" : "date" },
        "search_api_language" : { "type" : "string" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 1,
          "weight" : "-10",
          "settings" : { "default" : "0", "bundles" : { "book" : "book" } }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : { "field_book_content:value" : true } }
        },
        "search_api_html_filter" : {
          "status" : 1,
          "weight" : "10",
          "settings" : {
            "fields" : { "field_book_content:value" : true },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 1,
          "weight" : "20",
          "settings" : {
            "fields" : { "field_book_content:value" : true },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 1,
          "weight" : "30",
          "settings" : {
            "fields" : { "field_book_content:value" : true },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 1,
          "weight" : "35",
          "settings" : {
            "prefix" : "\\u003Cstrong class=\\u0022full-text-search-hit\\u0022\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : { "field_book_author" : "field_book_author" },
            "highlight" : "always"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0"
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function shanti_texts_search_settings_default_search_api_server() {
  $items = array();
  $items['solr_search'] = entity_import('search_api_server', '{
    "name" : "Solr Search",
    "machine_name" : "solr_search",
    "description" : "",
    "class" : "search_api_solr_service",
    "options" : {
      "clean_ids" : true,
      "site_hash" : true,
      "scheme" : "https",
      "host" : "ss251856-us-east-1-aws.measuredsearch.com",
      "port" : "443",
      "path" : "\\/solr\\/texts_solrapi_dev",
      "http_user" : "solradmin",
      "http_pass" : "IdskBsk013",
      "excerpt" : 0,
      "retrieve_data" : 0,
      "highlight_data" : 0,
      "skip_schema_check" : 0,
      "solr_version" : "",
      "http_method" : "AUTO",
      "log_query" : 0,
      "log_response" : 0,
      "commits_disabled" : 0,
      "autocorrect_spell" : 1,
      "autocorrect_suggest_words" : 1
    },
    "enabled" : "1"
  }');
  return $items;
}
