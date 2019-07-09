<?php

/**
 * Adds the Shanti Images table as a data source to views
 */

function shanti_images_views_data() {
    $data = array();
    // Shanti Images Table
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
    );

    $data['shanti_images']['siid'] = array(
        'title' => t('Shanti Images ID'),
        'help' => t('The auto-incremented Shanti Image ID'),
        'field' => array(
            'handler' => 'views_handler_field_numeric',
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
        ),
    );

    $data['shanti_images']['nid'] = array(
        'title' => t('Node ID'),
        'help' => t('The record node ID.'),
        'field' => array(
            'handler' => 'views_handler_field_node',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_numeric',
        ),
        'relationship' => array(
            'base' => 'node',
            'field' => 'nid',
            'handler' => 'views_handler_relationship',
            'label' => t('Node'),
        ),
        'argument' => array(
            'handler' => 'views_handler_argument_node_nid',
            'numeric' => TRUE,
            'validate type' => 'nid',
        ),
    );

    $data['shanti_images']['uid'] = array(
        'title' => t('Shanti Images User ID'),
        'help' => t('The user ID of person posting images'),
        'field' => array(
            'handler' => 'views_handler_field_numeric',
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
        'argument' => array(
            'handler' => 'views_handler_argument_numeric',
        ),
    );

    $data['shanti_images']['fid'] = array(
        'title' => t('Shanti Images File ID'),
        'help' => t('The original file ID'),
        'field' => array(
            'handler' => 'views_handler_field_numeric',
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
        ),
    );

    $data['shanti_images']['mmsid'] = array(
        'title' => t('Shanti Images MMSID'),
        'help' => t('The MMS ID of the original image'),
        'field' => array(
            'handler' => 'views_handler_field_numeric',
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
        ),
    );

    $data['shanti_images']['i3fid'] = array(
        'title' => t('Shanti Images IIIF Name'),
        'help' => t('The IIIF filename for image'),
        'field' => array(
            'handler' => 'views_handler_field',
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

    $data['shanti_images']['width'] = array(
        'title' => t('Width'),
        'help' => t('The original width of the image'),
        'field' => array(
            'handler' => 'views_handler_field_numeric',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_numeric',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
        ),
    );

    $data['shanti_images']['height'] = array(
        'title' => t('Height'),
        'help' => t('The original height of the image'),
        'field' => array(
            'handler' => 'views_handler_field_numeric',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_numeric',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_string',
        ),
    );
    return $data;
}