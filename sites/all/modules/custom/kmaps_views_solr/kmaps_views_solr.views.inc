<?php

/**
 * Implementation of hook_views_plugins().
 */
function kmaps_views_solr_views_plugins() {
  $plugin = array();
  $plugin['query']['kmaps_views_solr_plugin_query'] = array(
    'title' => t('Solr AV Related Assets Query'),
    'help' => t('Fields for audio-video pulled as queries from Solr'),
    'handler' => 'kmaps_views_solr_plugin_query',
  );
  return $plugin;
}

/**
 * Implementation of hook_views_data().
 */
function kmaps_views_solr_views_data() {
  $data = array();

  // Base data
  $data['kmaps_views_solr']['table']['group']  = t('Audio-Video Group');
  $data['kmaps_views_solr']['table']['base'] = array(
    'title' => t('Audio Video Data'),
    'help' => t('Audio Video Query'),
    'query class' => 'kmaps_views_solr_plugin_query'
  );

  // Fields
  $data['kmaps_views_solr']['av_id'] = array(
    'title' => t('Id'),
    'help' => t('The Id of the node'),
    'field' => array(
      'handler' => 'kmaps_views_solr_handler_field',
    ),
  );

  $data['kmaps_views_solr']['av_title'] = array(
    'title' => t('Title'),
    'help' => t('The title of the related Audio-Video'),
    'field' => array(
      'handler' => 'kmaps_views_solr_handler_field',
    ),
    'filter' => array(
      'handler' => 'kmaps_views_solr_handler_filter_title'
    ),
    'sort' => array(
      'handler' => 'kmaps_views_solr_handler_sort_title'
    ),
  );

  $data['kmaps_views_solr']['caption'] = array(
    'title' => t('Caption'),
    'help' => t('Caption'),
    'field' => array(
      'handler' => 'kmaps_views_solr_handler_field',
    ),
  );

  $data['kmaps_views_solr']['summary'] = array(
    'title' => t('Summary'),
    'help' => t('Summary'),
    'field' => array(
      'handler' => 'kmaps_views_solr_handler_field',
    ),
  );

  $data['kmaps_views_solr']['created_date'] = array(
    'title' => t('Create Date'),
    'help' => t('Created at date'),
    'field' => array(
      'handler' => 'kmaps_views_solr_handler_field',
    ),
    'sort' => array(
      'handler' => 'kmaps_views_solr_handler_sort_created_date'
    ),
  );

  $data['kmaps_views_solr']['collection'] = array(
    'title' => t('Collection'),
    'help' => t('Collection title'),
    'field' => array(
      'handler' => 'kmaps_views_solr_handler_field',
    ),
  );

  $data['kmaps_views_solr']['creator'] = array(
    'title' => t('Creator'),
    'help' => t('Author of the node'),
    'field' => array(
      'handler' => 'kmaps_views_solr_handler_field',
    ),
    'sort' => array(
      'handler' => 'kmaps_views_solr_handler_sort_creator'
    ),
  );

  $data['kmaps_views_solr']['asset_type'] = array(
    'title' => t('Asset Type'),
    'help' => t('Asset Sub-type'),
    'field' => array(
      'handler' => 'kmaps_views_solr_handler_field',
    ),
    'filter' => array(
      'handler' => 'kmaps_views_solr_handler_filter_asset_type'
    ),
  );

  $data['kmaps_views_solr']['language'] = array(
    'title' => t('Language'),
    'help' => t('Language'),
    'field' => array(
      'handler' => 'kmaps_views_solr_handler_field',
    ),
  );

  $data['kmaps_views_solr']['thumb'] = array(
    'title' => t('Thumb'),
    'help' => t('Link to thumb image'),
    'field' => array(
      'handler' => 'kmaps_views_solr_handler_field',
    ),
  );

  $data['kmaps_views_solr']['ajax_url'] = array(
    'title' => t('Ajax Url'),
    'help' => t('Ajax link to node'),
    'field' => array(
      'handler' => 'kmaps_views_solr_handler_field',
    ),
  );

  $data['kmaps_views_solr']['html_url'] = array(
    'title' => t('HTML Url'),
    'help' => t('HTML link to node'),
    'field' => array(
      'handler' => 'kmaps_views_solr_handler_field',
    ),
  );
  
  return $data;
}