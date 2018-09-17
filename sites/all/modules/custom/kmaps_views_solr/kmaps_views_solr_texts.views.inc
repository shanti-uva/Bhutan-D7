<?php

/**
 * Implementation of hook_views_plugins().
 */
function kmaps_views_solr_texts_views_plugins() {
  $plugin = array();
  $plugin['query']['kmaps_views_solr_texts_plugin_query'] = array(
    'title' => t('Solr Texts Related Assets Query'),
    'help' => t('Fields for Texts pulled as queries from Solr'),
    'handler' => 'kmaps_views_solr_texts_plugin_query',
  );
  return $plugin;
}

/**
 * Implementation of hook_views_data().
 */
function kmaps_views_solr_texts_views_data() {
  $data = array();

  // Base data
  $data['kmaps_views_solr_texts']['table']['group']  = t('Texts Group');
  $data['kmaps_views_solr_texts']['table']['base'] = array(
    'title' => t('Texts Data'),
    'help' => t('Texts Query'),
    'query class' => 'kmaps_views_solr_texts_plugin_query'
  );

  // Fields
  $data['kmaps_views_solr_texts']['texts_id'] = array(
    'title' => t('Id'),
    'help' => t('The Id of the node'),
    'field' => array(
      'handler' => 'kmaps_views_solr_texts_handler_field',
    ),
  );

  $data['kmaps_views_solr_texts']['texts_title'] = array(
    'title' => t('Title'),
    'help' => t('The title of the related Texts'),
    'field' => array(
      'handler' => 'kmaps_views_solr_texts_handler_field',
    ),
    'filter' => array(
      'handler' => 'kmaps_views_solr_texts_handler_filter_title'
    ),
    'sort' => array(
      'handler' => 'kmaps_views_solr_texts_handler_sort_title'
    ),
  );

  $data['kmaps_views_solr_texts']['created_date'] = array(
    'title' => t('Create Date'),
    'help' => t('Created at date'),
    'field' => array(
      'handler' => 'kmaps_views_solr_texts_handler_field',
    ),
    'sort' => array(
      'handler' => 'kmaps_views_solr_texts_handler_sort_created_date'
    ),
  );

  $data['kmaps_views_solr_texts']['collection'] = array(
    'title' => t('Collection'),
    'help' => t('Collection title'),
    'field' => array(
      'handler' => 'kmaps_views_solr_texts_handler_field',
    ),
  );

  $data['kmaps_views_solr_texts']['creator'] = array(
    'title' => t('Creator'),
    'help' => t('Author of the node'),
    'field' => array(
      'handler' => 'kmaps_views_solr_texts_handler_field',
    ),
    'sort' => array(
      'handler' => 'kmaps_views_solr_texts_handler_sort_creator'
    ),
  );
  
  return $data;
}