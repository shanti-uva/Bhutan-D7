<?php

/**
 * Implementation of hook_views_plugins().
 */
function kmaps_views_solr_sources_views_plugins() {
  $plugin = array();
  $plugin['query']['kmaps_views_solr_sources_plugin_query'] = array(
    'title' => t('Solr Sources Related Assets Query'),
    'help' => t('Fields for Sources pulled as queries from Solr'),
    'handler' => 'kmaps_views_solr_sources_plugin_query',
  );
  return $plugin;
}

/**
 * Implementation of hook_views_data().
 */
function kmaps_views_solr_sources_views_data() {
  $data = array();

  // Base data
  $data['kmaps_views_solr_sources']['table']['group']  = t('Sources Group');
  $data['kmaps_views_solr_sources']['table']['base'] = array(
    'title' => t('Sources Data'),
    'help' => t('Sources Query'),
    'query class' => 'kmaps_views_solr_sources_plugin_query'
  );

  // Fields
  $data['kmaps_views_solr_sources']['sources_id'] = array(
    'title' => t('Id'),
    'help' => t('The Id of the node'),
    'field' => array(
      'handler' => 'kmaps_views_solr_sources_handler_field',
    ),
  );

  $data['kmaps_views_solr_sources']['sources_title'] = array(
    'title' => t('Title'),
    'help' => t('The title of the related Sources'),
    'field' => array(
      'handler' => 'kmaps_views_solr_sources_handler_field',
    ),
    'filter' => array(
      'handler' => 'kmaps_views_solr_sources_handler_filter_title'
    ),
    'sort' => array(
      'handler' => 'kmaps_views_solr_sources_handler_sort_title'
    ),
  );

  $data['kmaps_views_solr_sources']['created_date'] = array(
    'title' => t('Create Date'),
    'help' => t('Created at date'),
    'field' => array(
      'handler' => 'kmaps_views_solr_sources_handler_field',
    ),
    'sort' => array(
      'handler' => 'kmaps_views_solr_sources_handler_sort_created_date'
    ),
  );

  $data['kmaps_views_solr_sources']['asset_subtype'] = array(
    'title' => t('Asset SubType'),
    'help' => t('Asset Sub-type'),
    'field' => array(
      'handler' => 'kmaps_views_solr_sources_handler_field',
    ),
    'filter' => array(
      'handler' => 'kmaps_views_solr_sources_handler_filter_asset_subtype'
    ),
  );
  
  return $data;
}