<?php
/**
 * @file
 *   Views field handler for basic Sources group fields.
 */

/**
 * Views field handler for basic Sources group fields.
 *
 * The only thing we're doing here is making sure the field_alias
 * gets set properly, and that none of the sql-specific query functionality
 * gets called.
 */
class kmaps_views_solr_sources_handler_filter_asset_subtype extends views_handler_filter_in_operator {
  function get_value_options() {
    $this->value_options = array(
      'Book' => t('Book'),
    );
  }

  function query() {
  }
}