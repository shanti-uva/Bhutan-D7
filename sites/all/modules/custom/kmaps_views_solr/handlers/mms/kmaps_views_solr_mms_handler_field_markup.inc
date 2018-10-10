<?php
/**
 * @file
 *   Views field handler for MMS Numeric fields.
 */

/**
 * Views field handler for MMS Numeric fields.
 *
 * The only thing we're doing here is making sure the field_alias
 * gets set properly, and that none of the sql-specific query functionality
 * gets called.
 */
class kmaps_views_solr_mms_handler_field_markup extends views_handler_field_markup {
    function query() {
        $this->field_alias = $this->real_field;
    }
}
