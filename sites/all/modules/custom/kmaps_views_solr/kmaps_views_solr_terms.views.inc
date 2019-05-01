<?php

/**
 * Implementation of hook_views_plugins().
 */
function kmaps_views_solr_terms_views_plugins() {
  $plugin = array();
  $plugin['query']['kmaps_views_solr_terms_plugin_query'] = array(
    'title' => t('Solr Terms Related Assets Query'),
    'help' => t('Fields for Terms pulled as queries from Solr'),
    'handler' => 'kmaps_views_solr_terms_plugin_query',
  );
  return $plugin;
}

/**
 * Implementation of hook_views_data().
 */
function kmaps_views_solr_terms_views_data() {
  $data = array();

  // Base data
  $data['kmaps_views_solr_terms']['table']['group']  = t('Terms Group');
  $data['kmaps_views_solr_terms']['table']['base'] = array(
    'title' => t('Terms Data'),
    'help' => t('Terms Query'),
    'query class' => 'kmaps_views_solr_terms_plugin_query'
  );

  // Fields
  $data['kmaps_views_solr_terms']['terms_id'] = array(
    'title' => t('ID'),
    'help' => t('The ID of the node'),
    'field' => array(
      'handler' => 'kmaps_views_solr_terms_handler_field',
    ),
  );

  $data['kmaps_views_solr_terms']['terms_title'] = array(
    'title' => t('Title'),
    'help' => t('The title of the related Terms'),
    'field' => array(
      'handler' => 'kmaps_views_solr_terms_handler_field',
    ),
    'filter' => array(
      'handler' => 'kmaps_views_solr_terms_handler_filter_title'
    ),
  );

  return $data;
}