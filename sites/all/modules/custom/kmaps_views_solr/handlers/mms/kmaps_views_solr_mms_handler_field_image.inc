<?php
/**
 * @file
 *   Views field handler for MMS Image group fields.
 */

/**
 * Views field handler for basic Visuals group fields.
 *
 * The only thing we're doing here is making sure the field_alias
 * gets set properly, and that none of the sql-specific query functionality
 * gets called.
 */
class kmaps_views_solr_mms_handler_field_image extends views_handler_field {
    function query() {
        $this->field_alias = $this->real_field;
    }

    function option_definition() {
        $options = parent::option_definition();
        $options['image_style'] = array('' => '-');
        return $options;
    }

    function options_form(&$form, &$form_state) {
        // Offer a list of image styles for the user to choose from.
        parent::options_form($form, $form_state);

        $form['image_style'] = array(
            '#title' => t('Image style'),
            '#type' => 'select',
            '#default_value' => $this->options['image_style'],
            '#options' => image_style_options(FALSE),
        );
    }

    /**
     * Render the field.
     *
     * @param $values
     *   The values retrieved from the database.
     */
    function render($values) {
        $image_info = array(
            'path' => $values->{$this->field},
            'style_name' => $this->options['image_style'],
            'alt' => $values->caption,
        );
        $return = theme('imagecache_external', $image_info);
    }
}
