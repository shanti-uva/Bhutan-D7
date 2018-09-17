<?php
/**
 * @file
 *   Views field handler for basic AV group fields.
 */

/**
 * Views field handler for basic AV group fields.
 *
 * The only thing we're doing here is making sure the field_alias
 * gets set properly, and that none of the sql-specific query functionality
 * gets called.
 */
class kmaps_views_solr_handler_sort_title extends views_handler_sort {
  function query() {
  }
}