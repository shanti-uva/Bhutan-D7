<?php

/**
 * Adds the Shanti Images table as a data source to views
 */

function shanti_images_views_data() {
    $data = array();
    $data['shanti_images']['table']['group'] = t('Shanti Images');

    $data['shanti_images']['table']['base'] = array(
        'field' => 'siid',
        'title' => t('Shanti Images Data'),
        'help' => t('IIIF images on this site'),
        'weight' => -10,
    );

    $data['shanti_images']['table']['join'] = array(
        'node' => array(
            'left_field' => 'nid',
            'field' => 'nid',
        ),
        'users' => array(
            'left_field' => 'uid',
            'field' => 'uid',
        ),
    );

    $data['shanti_images']['siid'] = array(
        'title' => t('Shanti Images ID'),
        'help' => t('The auto-incremented Shanti Image ID'),
        'field' => array(
            'handler' => 'views_handler_field_numeric',
            'click sortable' => TRUE,
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data['shanti_images']['nid'] = array(
        'title' => t('Shanti Images Node ID'),
        'help' => t('The node associated with the image'),
        'relationship' => array(
            'base' => 'node',
            'base field' => 'nid', // The name of the field on the joined table.
            // 'field' => 'nid' -- see hook_views_data_alter(); not needed here.
            'handler' => 'views_handler_relationship',
            'label' => t('Image Node'),
        ),
    );

    $data['shanti_images']['fid'] = array(
        'title' => t('Shanti Images File ID'),
        'help' => t('The original file ID'),
        'field' => array(
            'handler' => 'views_handler_field_numeric',
            'click sortable' => TRUE,
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data['shanti_images']['uid'] = array(
        'title' => t('Shanti Images User ID'),
        'help' => t('The ID of the user who uploaded the image'),
        'relationship' => array(
            'base' => 'users',
            'base field' => 'uid', // The name of the field on the joined table.
            // 'field' => 'nid' -- see hook_views_data_alter(); not needed here.
            'handler' => 'views_handler_relationship',
            'label' => t('Image User'),
        ),
    );

    $data['shanti_images']['mmsid'] = array(
        'title' => t('Shanti Images MMSID'),
        'help' => t('The MMS ID of the original image'),
        'field' => array(
            'handler' => 'views_handler_field_numeric',
            'click sortable' => TRUE,
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data['shanti_images']['i3fid'] = array(
        'title' => t('Shanti Images IIIF Name'),
        'help' => t('The IIIF filename for image'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_string',
        ),
        'argument' => array(
            'handler' => 'views_handler_argument_string',
        ),
    );

    $data['shanti_images']['filename'] = array(
        'title' => t('Original File Name'),
        'help' => t('The original filename for the image'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_string',
        ),
        'argument' => array(
            'handler' => 'views_handler_argument_string',
        ),
    );
    return $data;
}