<?php
/**
 * @file
 *   Views field handler for basic Visuals group fields.
 */

/**
 * Views field handler for basic Visuals group fields.
 *
 * The only thing we're doing here is making sure the field_alias
 * gets set properly, and that none of the sql-specific query functionality
 * gets called.
 */
class kmaps_views_solr_images_handler_field extends views_handler_field {
  function query() {
    $this->field_alias = $this->real_field;
  }
}