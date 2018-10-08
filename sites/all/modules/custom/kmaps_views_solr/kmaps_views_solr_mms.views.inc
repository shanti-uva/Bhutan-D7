<?php

/**
 * Implementation of hook_views_plugins().
 */
function kmaps_views_solr_mms_views_plugins()
{
    $plugin = array();
    $plugin['query']['kmaps_views_solr_mms_plugin_query'] = array(
        'title' => t('Solr MMS Related Assets Query'),
        'help' => t('Fields for mms pulled as queries from Solr'),
        'handler' => 'kmaps_views_solr_mms_plugin_query',
    );
    return $plugin;
}

/**
 * Implementation of hook_views_data().
 */
function kmaps_views_solr_mms_views_data()
{
    $data = array();

    // Base data
    $data['kmaps_views_solr_mms']['table']['group'] = t('MMS Group');
    $data['kmaps_views_solr_mms']['table']['base'] = array(
        'title' => t('MMS Data'),
        'help' => t('MMS Query'),
        'query class' => 'kmaps_views_solr_mms_plugin_query'
    );

    // Fields
    $data['kmaps_views_solr_mms']['mms_id'] = array(
        'title' => t('Id'),
        'help' => t('The ID of the Image Node'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field_numeric',
        ),
    );

    $data['kmaps_views_solr_mms']['mms_title'] = array(
        'title' => t('Title'),
        'help' => t('The title of the related MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
        'filter' => array(
            'handler' => 'kmaps_views_solr_mms_handler_filter_title'
        ),
        'sort' => array(
            'handler' => 'kmaps_views_solr_mms_handler_sort_title'
        ),
    );

    $data['kmaps_views_solr_mms']['resource_type'] = array(
        'title' => t('Resource Type'),
        'help' => t('The Resource Type of the related MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
    );

    $data['kmaps_views_solr_mms']['photographer'] = array(
        'title' => t('Photographer'),
        'help' => t('The Photographer of the related MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
    );

    $data['kmaps_views_solr_mms']['taken_on'] = array(
        'title' => t('Taken On'),
        'help' => t('The Date when the MMS Resource was taken'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
    );

    $data['kmaps_views_solr_mms']['recording_note'] = array(
        'title' => t('Recording Note'),
        'help' => t('Any notes from Recording the MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field_markup',
        ),
    );

    $data['kmaps_views_solr_mms']['private_note'] = array(
        'title' => t('Private Note'),
        'help' => t('Private notes from Recording the MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field_markup',
        ),
    );

    $data['kmaps_views_solr_mms']['rotation'] = array(
        'title' => t('Rotation'),
        'help' => t('Rotation of the related MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
    );

    $data['kmaps_views_solr_mms']['capture_device'] = array(
        'title' => t('Capture Device'),
        'help' => t('Capture Device of the related MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
    );

    $data['kmaps_views_solr_mms']['caption'] = array(
        'title' => t('Caption'),
        'help' => t('Caption of the related MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
    );

    $data['kmaps_views_solr_mms']['description'] = array(
        'title' => t('Description'),
        'help' => t('Description of the MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field_markup',
        ),
    );

    $data['kmaps_views_solr_mms']['copyright_holder'] = array(
        'title' => t('copyright holder'),
        'help' => t('copyright holder of the related mms resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
    );

    $data['kmaps_views_solr_mms']['copyright_holder_website'] = array(
        'title' => t('Copyright Holder\'s website'),
        'help' => t('Copyright Holder\'s website of the related mms resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
    );

    $data['kmaps_views_solr_mms']['reproduction_type'] = array(
        'title' => t('Reproduction Type'),
        'help' => t('Reproduction Type of the related MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
    );

    $data['kmaps_views_solr_mms']['reproduction_type_website'] = array(
        'title' => t('Reproduction Type Website'),
        'help' => t('Reproduction Type Website of the related MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
    );

    $data['kmaps_views_solr_mms']['locations'] = array(
        'title' => t('Locations'),
        'help' => t('Locations of the related MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
    );

    $data['kmaps_views_solr_mms']['keywords'] = array(
        'title' => t('Keywords'),
        'help' => t('Keywords of the related MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
    );

    $data['kmaps_views_solr_mms']['affiliations'] = array(
        'title' => t('Affiliations'),
        'help' => t('Affiliations of the related MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
    );

    $data['kmaps_views_solr_mms']['image_url'] = array(
        'title' => t('Image URL'),
        'help' => t('Image URL of the related MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
    );

    $data['kmaps_views_solr_mms']['image'] = array(
        'title' => t('Image'),
        'help' => t('Image of the related MMS Resource'),
        'field' => array(
            'handler' => 'kmaps_views_solr_images_handler_field_image',
        ),
    );

    $data['kmaps_views_solr_mms']['image_dimension'] = array(
        'title' => t('Image Dimensions'),
        'help' => t('The Width and Height of the original image (format: WWWWxHHHH)'),
        'field' => array(
            'handler' => 'kmaps_views_solr_mms_handler_field',
        ),
    );

    return $data;
}