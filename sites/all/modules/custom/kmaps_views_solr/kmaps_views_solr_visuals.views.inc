<?php

/**
 * Implementation of hook_views_plugins().
 */
function kmaps_views_solr_visuals_views_plugins() {
  $plugin = array();
  $plugin['query']['kmaps_views_solr_visuals_plugin_query'] = array(
    'title' => t('Solr Visuals Related Assets Query'),
    'help' => t('Fields for Visuals pulled as queries from Solr'),
    'handler' => 'kmaps_views_solr_visuals_plugin_query',
  );
  return $plugin;
}

/**
 * Implementation of hook_views_data().
 */
function kmaps_views_solr_visuals_views_data() {
  $data = array();

  // Base data
  $data['kmaps_views_solr_visuals']['table']['group']  = t('Visuals Group');
  $data['kmaps_views_solr_visuals']['table']['base'] = array(
    'title' => t('Visuals Data'),
    'help' => t('Visuals Query'),
    'query class' => 'kmaps_views_solr_visuals_plugin_query'
  );

  // Fields
  $data['kmaps_views_solr_visuals']['visuals_id'] = array(
    'title' => t('Id'),
    'help' => t('The Id of the node'),
    'field' => array(
      'handler' => 'kmaps_views_solr_visuals_handler_field',
    ),
  );

  $data['kmaps_views_solr_visuals']['visuals_title'] = array(
    'title' => t('Title'),
    'help' => t('The title of the related Visuals'),
    'field' => array(
      'handler' => 'kmaps_views_solr_visuals_handler_field',
    ),
    'filter' => array(
      'handler' => 'kmaps_views_solr_visuals_handler_filter_title'
    ),
    'sort' => array(
      'handler' => 'kmaps_views_solr_visuals_handler_sort_title'
    ),
  );

  $data['kmaps_views_solr_visuals']['created_date'] = array(
    'title' => t('Create Date'),
    'help' => t('Created at date'),
    'field' => array(
      'handler' => 'kmaps_views_solr_visuals_handler_field',
    ),
    'sort' => array(
      'handler' => 'kmaps_views_solr_visuals_handler_sort_created_date'
    ),
  );

  $data['kmaps_views_solr_visuals']['collection'] = array(
    'title' => t('Collection'),
    'help' => t('Collection title'),
    'field' => array(
      'handler' => 'kmaps_views_solr_visuals_handler_field',
    ),
  );

  $data['kmaps_views_solr_visuals']['creator'] = array(
    'title' => t('Creator'),
    'help' => t('Author of the node'),
    'field' => array(
      'handler' => 'kmaps_views_solr_visuals_handler_field',
    ),
    'sort' => array(
      'handler' => 'kmaps_views_solr_visuals_handler_sort_creator'
    ),
  );

  $data['kmaps_views_solr_visuals']['asset_subtype'] = array(
    'title' => t('Asset SubType'),
    'help' => t('Asset Sub-type'),
    'field' => array(
      'handler' => 'kmaps_views_solr_visuals_handler_field',
    ),
    'filter' => array(
      'handler' => 'kmaps_views_solr_visuals_handler_filter_asset_subtype'
    ),
  );

  $data['kmaps_views_solr_visuals']['thumb'] = array(
    'title' => t('Thumb'),
    'help' => t('Link to thumb image'),
    'field' => array(
      'handler' => 'kmaps_views_solr_visuals_handler_field',
    ),
  );

  $data['kmaps_views_solr_visuals']['thumb_width'] = array(
    'title' => t('Thumb Width'),
    'help' => t('Width of thumb image'),
    'field' => array(
      'handler' => 'kmaps_views_solr_visuals_handler_field',
    ),
  );

  $data['kmaps_views_solr_visuals']['thumb_height'] = array(
    'title' => t('Thumb Height'),
    'help' => t('Height of thumb image'),
    'field' => array(
      'handler' => 'kmaps_views_solr_visuals_handler_field',
    ),
  );

  $data['kmaps_views_solr_visuals']['ajax_url'] = array(
    'title' => t('Ajax Url'),
    'help' => t('Ajax link to node'),
    'field' => array(
      'handler' => 'kmaps_views_solr_visuals_handler_field',
    ),
  );
  
  return $data;
}