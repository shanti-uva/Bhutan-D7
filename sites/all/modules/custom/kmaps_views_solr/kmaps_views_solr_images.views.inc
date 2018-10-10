<?php

/**
 * Implementation of hook_views_plugins().
 */
function kmaps_views_solr_images_views_plugins() {
  $plugin = array();
  $plugin['query']['kmaps_views_solr_images_plugin_query'] = array(
    'title' => t('Solr Images Related Assets Query'),
    'help' => t('Fields for Images pulled as queries from Solr'),
    'handler' => 'kmaps_views_solr_images_plugin_query',
  );
  return $plugin;
}

/**
 * Implementation of hook_views_data().
 */
function kmaps_views_solr_images_views_data() {
  $data = array();

  // Base data
  $data['kmaps_views_solr_images']['table']['group']  = t('Images Group');
  $data['kmaps_views_solr_images']['table']['base'] = array(
    'title' => t('Images Data'),
    'help' => t('Images Query'),
    'query class' => 'kmaps_views_solr_images_plugin_query'
  );

  // Fields
  $data['kmaps_views_solr_images']['images_id'] = array(
    'title' => t('Id'),
    'help' => t('The Id of the node'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
  );

  $data['kmaps_views_solr_images']['images_title'] = array(
    'title' => t('Title'),
    'help' => t('The title of the related Images'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
    'filter' => array(
      'handler' => 'kmaps_views_solr_images_handler_filter_title'
    ),
    'sort' => array(
      'handler' => 'kmaps_views_solr_images_handler_sort_title'
    ),
  );

  $data['kmaps_views_solr_images']['images_filename'] = array(
    'title' => t('IIIF Filename'),
    'help' => t('The IIIF Filename for the image'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
  );

  $data['kmaps_views_solr_images']['images_desc'] = array(
    'title' => t('Description'),
    'help' => t('The description of the related Images'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
  );

  $data['kmaps_views_solr_images']['created_date'] = array(
    'title' => t('Create Date'),
    'help' => t('Created at date'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
    'sort' => array(
      'handler' => 'kmaps_views_solr_images_handler_sort_created_date'
    ),
  );

  $data['kmaps_views_solr_images']['collection'] = array(
    'title' => t('Collection'),
    'help' => t('Collection title'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
  );

  $data['kmaps_views_solr_images']['creator'] = array(
    'title' => t('Creator'),
    'help' => t('Author of the node'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
    'sort' => array(
      'handler' => 'kmaps_views_solr_images_handler_sort_creator'
    ),
  );

  $data['kmaps_views_solr_images']['thumb'] = array(
    'title' => t('Thumb'),
    'help' => t('Link to thumb image'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
  );

  $data['kmaps_views_solr_images']['thumb_width'] = array(
    'title' => t('Thumb Width'),
    'help' => t('Width of thumb image'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
  );

  $data['kmaps_views_solr_images']['thumb_height'] = array(
    'title' => t('Thumb Height'),
    'help' => t('Height of thumb image'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
  );

  $data['kmaps_views_solr_images']['image_width'] = array(
    'title' => t('Image Width'),
    'help' => t('Width of the full image'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
  );

  $data['kmaps_views_solr_images']['image_height'] = array(
    'title' => t('Image Height'),
    'help' => t('Height of the full image'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
  );

  $data['kmaps_views_solr_images']['subjects'] = array(
    'title' => t('Kmaps Subjects'),
    'help' => t('Kmaps subject IDs associated with image'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
  );

  $data['kmaps_views_solr_images']['places'] = array(
    'title' => t('Kmaps Places'),
    'help' => t('Kmaps places IDs associated with image'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
  );

  $data['kmaps_views_solr_images']['ajax_url'] = array(
    'title' => t('Ajax Url'),
    'help' => t('Ajax link to node'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
  );

  $data['kmaps_views_solr_images']['html_url'] = array(
    'title' => t('HTML Url'),
    'help' => t('URL Alias to node'),
    'field' => array(
      'handler' => 'kmaps_views_solr_images_handler_field',
    ),
  );
  return $data;
}