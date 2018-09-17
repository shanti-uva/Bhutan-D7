<?php
/**
 * @file
 * kmaps_views_solr_features.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function kmaps_views_solr_features_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'related_audio_video';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'kmaps_views_solr';
  $view->human_name = 'Related Audio-Video';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Related Audio-Video';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '>';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'input_required' => 0,
      'text_input_required' => array(
        'text_input_required' => array(
          'value' => 'Select any filter and click on Apply to see results',
          'format' => 'filtered_html',
        ),
      ),
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
      'secondary_collapse_override' => '0',
    ),
    'sort' => array(
      'bef_format' => 'default',
      'advanced' => array(
        'collapsible' => 0,
        'collapsible_label' => 'Sort options',
        'combine' => 1,
        'combine_param' => 'sort_bef_combine',
        'combine_rewrite' => '',
        'reset' => 0,
        'reset_label' => '',
        'is_secondary' => 0,
        'autosubmit' => 0,
      ),
    ),
    'asset_type' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 0,
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'av_title' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
  );
  $handler->display->display_options['pager']['type'] = 'pagerer';
  $handler->display->display_options['pager']['options']['items_per_page'] = '60';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['preset'] = 'mandala_pager';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'shanti-thumbnail [asset_type]';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = '<span class="label">Recent Additions</span> <span class="count">(Displaying @start - @end of @total)</span>';
  /* Field: Audio-Video Group: Title */
  $handler->display->display_options['fields']['av_title']['id'] = 'av_title';
  $handler->display->display_options['fields']['av_title']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['fields']['av_title']['field'] = 'av_title';
  $handler->display->display_options['fields']['av_title']['label'] = '';
  $handler->display->display_options['fields']['av_title']['alter']['max_length'] = '42';
  $handler->display->display_options['fields']['av_title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['av_title']['element_label_colon'] = FALSE;
  /* Field: Audio-Video Group: Asset Type */
  $handler->display->display_options['fields']['asset_type']['id'] = 'asset_type';
  $handler->display->display_options['fields']['asset_type']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['fields']['asset_type']['field'] = 'asset_type';
  $handler->display->display_options['fields']['asset_type']['label'] = '';
  $handler->display->display_options['fields']['asset_type']['element_label_colon'] = FALSE;
  /* Field: Audio-Video Group: Caption */
  $handler->display->display_options['fields']['caption']['id'] = 'caption';
  $handler->display->display_options['fields']['caption']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['fields']['caption']['field'] = 'caption';
  $handler->display->display_options['fields']['caption']['label'] = '';
  $handler->display->display_options['fields']['caption']['element_label_colon'] = FALSE;
  /* Field: Audio-Video Group: Collection */
  $handler->display->display_options['fields']['collection']['id'] = 'collection';
  $handler->display->display_options['fields']['collection']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['fields']['collection']['field'] = 'collection';
  $handler->display->display_options['fields']['collection']['label'] = '';
  $handler->display->display_options['fields']['collection']['element_label_colon'] = FALSE;
  /* Field: Audio-Video Group: Create Date */
  $handler->display->display_options['fields']['created_date']['id'] = 'created_date';
  $handler->display->display_options['fields']['created_date']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['fields']['created_date']['field'] = 'created_date';
  $handler->display->display_options['fields']['created_date']['label'] = '';
  $handler->display->display_options['fields']['created_date']['element_label_colon'] = FALSE;
  /* Field: Audio-Video Group: Creator */
  $handler->display->display_options['fields']['creator']['id'] = 'creator';
  $handler->display->display_options['fields']['creator']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['fields']['creator']['field'] = 'creator';
  $handler->display->display_options['fields']['creator']['label'] = '';
  $handler->display->display_options['fields']['creator']['element_label_colon'] = FALSE;
  /* Field: Audio-Video Group: Id */
  $handler->display->display_options['fields']['av_id']['id'] = 'av_id';
  $handler->display->display_options['fields']['av_id']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['fields']['av_id']['field'] = 'av_id';
  $handler->display->display_options['fields']['av_id']['label'] = '';
  $handler->display->display_options['fields']['av_id']['element_label_colon'] = FALSE;
  /* Field: Audio-Video Group: Language */
  $handler->display->display_options['fields']['language']['id'] = 'language';
  $handler->display->display_options['fields']['language']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['fields']['language']['field'] = 'language';
  $handler->display->display_options['fields']['language']['label'] = '';
  $handler->display->display_options['fields']['language']['element_label_colon'] = FALSE;
  /* Field: Audio-Video Group: Summary */
  $handler->display->display_options['fields']['summary']['id'] = 'summary';
  $handler->display->display_options['fields']['summary']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['fields']['summary']['field'] = 'summary';
  $handler->display->display_options['fields']['summary']['label'] = '';
  $handler->display->display_options['fields']['summary']['element_label_colon'] = FALSE;
  /* Field: Audio-Video Group: Ajax Url */
  $handler->display->display_options['fields']['ajax_url']['id'] = 'ajax_url';
  $handler->display->display_options['fields']['ajax_url']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['fields']['ajax_url']['field'] = 'ajax_url';
  $handler->display->display_options['fields']['ajax_url']['label'] = '';
  $handler->display->display_options['fields']['ajax_url']['element_label_colon'] = FALSE;
  /* Field: Audio-Video Group: Thumb */
  $handler->display->display_options['fields']['thumb']['id'] = 'thumb';
  $handler->display->display_options['fields']['thumb']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['fields']['thumb']['field'] = 'thumb';
  $handler->display->display_options['fields']['thumb']['label'] = '';
  $handler->display->display_options['fields']['thumb']['element_label_colon'] = FALSE;
  /* Field: Audio-Video Group: HTML Url */
  $handler->display->display_options['fields']['html_url']['id'] = 'html_url';
  $handler->display->display_options['fields']['html_url']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['fields']['html_url']['field'] = 'html_url';
  $handler->display->display_options['fields']['html_url']['label'] = '';
  $handler->display->display_options['fields']['html_url']['element_label_colon'] = FALSE;
  /* Sort criterion: Audio-Video Group: Create Date */
  $handler->display->display_options['sorts']['created_date']['id'] = 'created_date';
  $handler->display->display_options['sorts']['created_date']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['sorts']['created_date']['field'] = 'created_date';
  $handler->display->display_options['sorts']['created_date']['order'] = 'DESC';
  $handler->display->display_options['sorts']['created_date']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['created_date']['expose']['label'] = 'Post date';
  /* Sort criterion: Audio-Video Group: Title */
  $handler->display->display_options['sorts']['av_title']['id'] = 'av_title';
  $handler->display->display_options['sorts']['av_title']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['sorts']['av_title']['field'] = 'av_title';
  $handler->display->display_options['sorts']['av_title']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['av_title']['expose']['label'] = 'Title';
  /* Sort criterion: Audio-Video Group: Creator */
  $handler->display->display_options['sorts']['creator']['id'] = 'creator';
  $handler->display->display_options['sorts']['creator']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['sorts']['creator']['field'] = 'creator';
  $handler->display->display_options['sorts']['creator']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['creator']['expose']['label'] = 'Creator';
  /* Filter criterion: Audio-Video Group: Asset Type */
  $handler->display->display_options['filters']['asset_type']['id'] = 'asset_type';
  $handler->display->display_options['filters']['asset_type']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['filters']['asset_type']['field'] = 'asset_type';
  $handler->display->display_options['filters']['asset_type']['value'] = array(
    'video' => 'video',
    'audio' => 'audio',
  );
  $handler->display->display_options['filters']['asset_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['asset_type']['expose']['operator_id'] = 'asset_type_op';
  $handler->display->display_options['filters']['asset_type']['expose']['operator'] = 'asset_type_op';
  $handler->display->display_options['filters']['asset_type']['expose']['identifier'] = 'asset_type';
  $handler->display->display_options['filters']['asset_type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['asset_type']['expose']['reduce'] = TRUE;
  /* Filter criterion: Audio-Video Group: Title */
  $handler->display->display_options['filters']['av_title']['id'] = 'av_title';
  $handler->display->display_options['filters']['av_title']['table'] = 'kmaps_views_solr';
  $handler->display->display_options['filters']['av_title']['field'] = 'av_title';
  $handler->display->display_options['filters']['av_title']['operator'] = 'contains';
  $handler->display->display_options['filters']['av_title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['av_title']['expose']['operator_id'] = 'av_title_op';
  $handler->display->display_options['filters']['av_title']['expose']['operator'] = 'av_title_op';
  $handler->display->display_options['filters']['av_title']['expose']['identifier'] = 'av_title';
  $handler->display->display_options['filters']['av_title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = '<span class="label">Recent Additions</span> <span class="count">(Displaying @start - @end of @total)</span>';
  $handler->display->display_options['path'] = 'related-audio-video';

  /* Display: Audio Video Block */
  $handler = $view->new_display('block', 'Audio Video Block', 'audio_video_block');
  $handler->display->display_options['block_description'] = 'Audio-Video Tiles';
  $export['related_audio_video'] = $view;

  $view = new view();
  $view->name = 'related_sources';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'kmaps_views_solr_sources';
  $view->human_name = 'Related Sources';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Related Sources';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '>';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'input_required' => 0,
      'text_input_required' => array(
        'text_input_required' => array(
          'value' => 'Select any filter and click on Apply to see results',
          'format' => 'filtered_html',
        ),
      ),
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
      'secondary_collapse_override' => '0',
    ),
    'sort' => array(
      'bef_format' => 'default',
      'advanced' => array(
        'collapsible' => 0,
        'collapsible_label' => 'Sort options',
        'combine' => 1,
        'combine_param' => 'sort_bef_combine',
        'combine_rewrite' => '',
        'reset' => 0,
        'reset_label' => '',
        'is_secondary' => 0,
        'autosubmit' => 0,
      ),
    ),
    'asset_subtype' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 0,
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'sources_title' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
  );
  $handler->display->display_options['pager']['type'] = 'pagerer';
  $handler->display->display_options['pager']['options']['items_per_page'] = '60';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['preset'] = 'mandala_pager';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = '<span class="label">Recent Additions</span> <span class="count">(Displaying @start - @end of @total)</span>';
  /* Field: Sources Group: Id */
  $handler->display->display_options['fields']['sources_id']['id'] = 'sources_id';
  $handler->display->display_options['fields']['sources_id']['table'] = 'kmaps_views_solr_sources';
  $handler->display->display_options['fields']['sources_id']['field'] = 'sources_id';
  $handler->display->display_options['fields']['sources_id']['label'] = '';
  $handler->display->display_options['fields']['sources_id']['element_label_colon'] = FALSE;
  /* Field: Sources Group: Asset SubType */
  $handler->display->display_options['fields']['asset_subtype']['id'] = 'asset_subtype';
  $handler->display->display_options['fields']['asset_subtype']['table'] = 'kmaps_views_solr_sources';
  $handler->display->display_options['fields']['asset_subtype']['field'] = 'asset_subtype';
  $handler->display->display_options['fields']['asset_subtype']['label'] = '';
  $handler->display->display_options['fields']['asset_subtype']['element_label_colon'] = FALSE;
  /* Field: Sources Group: Create Date */
  $handler->display->display_options['fields']['created_date']['id'] = 'created_date';
  $handler->display->display_options['fields']['created_date']['table'] = 'kmaps_views_solr_sources';
  $handler->display->display_options['fields']['created_date']['field'] = 'created_date';
  $handler->display->display_options['fields']['created_date']['label'] = '';
  $handler->display->display_options['fields']['created_date']['element_label_colon'] = FALSE;
  /* Field: Sources Group: Title */
  $handler->display->display_options['fields']['sources_title']['id'] = 'sources_title';
  $handler->display->display_options['fields']['sources_title']['table'] = 'kmaps_views_solr_sources';
  $handler->display->display_options['fields']['sources_title']['field'] = 'sources_title';
  $handler->display->display_options['fields']['sources_title']['label'] = '';
  $handler->display->display_options['fields']['sources_title']['element_label_colon'] = FALSE;
  /* Sort criterion: Sources Group: Create Date */
  $handler->display->display_options['sorts']['created_date']['id'] = 'created_date';
  $handler->display->display_options['sorts']['created_date']['table'] = 'kmaps_views_solr_sources';
  $handler->display->display_options['sorts']['created_date']['field'] = 'created_date';
  $handler->display->display_options['sorts']['created_date']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['created_date']['expose']['label'] = 'Post date';
  /* Filter criterion: Sources Group: Asset SubType */
  $handler->display->display_options['filters']['asset_subtype']['id'] = 'asset_subtype';
  $handler->display->display_options['filters']['asset_subtype']['table'] = 'kmaps_views_solr_sources';
  $handler->display->display_options['filters']['asset_subtype']['field'] = 'asset_subtype';
  $handler->display->display_options['filters']['asset_subtype']['value'] = array(
    'Book' => 'Book',
  );
  $handler->display->display_options['filters']['asset_subtype']['exposed'] = TRUE;
  $handler->display->display_options['filters']['asset_subtype']['expose']['operator_id'] = 'asset_subtype_op';
  $handler->display->display_options['filters']['asset_subtype']['expose']['operator'] = 'asset_subtype_op';
  $handler->display->display_options['filters']['asset_subtype']['expose']['identifier'] = 'asset_subtype';
  $handler->display->display_options['filters']['asset_subtype']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Sources Group: Title */
  $handler->display->display_options['filters']['sources_title']['id'] = 'sources_title';
  $handler->display->display_options['filters']['sources_title']['table'] = 'kmaps_views_solr_sources';
  $handler->display->display_options['filters']['sources_title']['field'] = 'sources_title';
  $handler->display->display_options['filters']['sources_title']['operator'] = 'contains';
  $handler->display->display_options['filters']['sources_title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['sources_title']['expose']['operator_id'] = 'sources_title_op';
  $handler->display->display_options['filters']['sources_title']['expose']['operator'] = 'sources_title_op';
  $handler->display->display_options['filters']['sources_title']['expose']['identifier'] = 'sources_title';
  $handler->display->display_options['filters']['sources_title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'related-sources';

  /* Display: Sources Block */
  $handler = $view->new_display('block', 'Sources Block', 'sources_block');
  $export['related_sources'] = $view;

  $view = new view();
  $view->name = 'related_texts';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'kmaps_views_solr_texts';
  $view->human_name = 'Related Texts';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Related Texts';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '>';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'input_required' => 0,
      'text_input_required' => array(
        'text_input_required' => array(
          'value' => 'Select any filter and click on Apply to see results',
          'format' => 'filtered_html',
        ),
      ),
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
      'secondary_collapse_override' => '0',
    ),
    'sort' => array(
      'bef_format' => 'default',
      'advanced' => array(
        'collapsible' => 0,
        'collapsible_label' => 'Sort options',
        'combine' => 1,
        'combine_param' => 'sort_bef_combine',
        'combine_rewrite' => '',
        'reset' => 0,
        'reset_label' => '',
        'is_secondary' => 0,
        'autosubmit' => 0,
      ),
    ),
    'texts_title' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
  );
  $handler->display->display_options['pager']['type'] = 'pagerer';
  $handler->display->display_options['pager']['options']['items_per_page'] = '60';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['preset'] = 'mandala_pager';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = '<span class="label">Recent Additions</span> <span class="count">(Displaying @start - @end of @total)</span>';
  /* Field: Texts Group: Id */
  $handler->display->display_options['fields']['texts_id']['id'] = 'texts_id';
  $handler->display->display_options['fields']['texts_id']['table'] = 'kmaps_views_solr_texts';
  $handler->display->display_options['fields']['texts_id']['field'] = 'texts_id';
  $handler->display->display_options['fields']['texts_id']['label'] = '';
  $handler->display->display_options['fields']['texts_id']['element_label_colon'] = FALSE;
  /* Field: Texts Group: Collection */
  $handler->display->display_options['fields']['collection']['id'] = 'collection';
  $handler->display->display_options['fields']['collection']['table'] = 'kmaps_views_solr_texts';
  $handler->display->display_options['fields']['collection']['field'] = 'collection';
  $handler->display->display_options['fields']['collection']['label'] = '';
  $handler->display->display_options['fields']['collection']['element_label_colon'] = FALSE;
  /* Field: Texts Group: Create Date */
  $handler->display->display_options['fields']['created_date']['id'] = 'created_date';
  $handler->display->display_options['fields']['created_date']['table'] = 'kmaps_views_solr_texts';
  $handler->display->display_options['fields']['created_date']['field'] = 'created_date';
  $handler->display->display_options['fields']['created_date']['label'] = '';
  $handler->display->display_options['fields']['created_date']['element_label_colon'] = FALSE;
  /* Field: Texts Group: Creator */
  $handler->display->display_options['fields']['creator']['id'] = 'creator';
  $handler->display->display_options['fields']['creator']['table'] = 'kmaps_views_solr_texts';
  $handler->display->display_options['fields']['creator']['field'] = 'creator';
  $handler->display->display_options['fields']['creator']['label'] = '';
  $handler->display->display_options['fields']['creator']['element_label_colon'] = FALSE;
  /* Field: Texts Group: Title */
  $handler->display->display_options['fields']['texts_title']['id'] = 'texts_title';
  $handler->display->display_options['fields']['texts_title']['table'] = 'kmaps_views_solr_texts';
  $handler->display->display_options['fields']['texts_title']['field'] = 'texts_title';
  $handler->display->display_options['fields']['texts_title']['label'] = '';
  $handler->display->display_options['fields']['texts_title']['element_label_colon'] = FALSE;
  /* Sort criterion: Texts Group: Create Date */
  $handler->display->display_options['sorts']['created_date']['id'] = 'created_date';
  $handler->display->display_options['sorts']['created_date']['table'] = 'kmaps_views_solr_texts';
  $handler->display->display_options['sorts']['created_date']['field'] = 'created_date';
  $handler->display->display_options['sorts']['created_date']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['created_date']['expose']['label'] = 'Post date';
  /* Filter criterion: Texts Group: Title */
  $handler->display->display_options['filters']['texts_title']['id'] = 'texts_title';
  $handler->display->display_options['filters']['texts_title']['table'] = 'kmaps_views_solr_texts';
  $handler->display->display_options['filters']['texts_title']['field'] = 'texts_title';
  $handler->display->display_options['filters']['texts_title']['operator'] = 'contains';
  $handler->display->display_options['filters']['texts_title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['texts_title']['expose']['operator_id'] = 'texts_title_op';
  $handler->display->display_options['filters']['texts_title']['expose']['operator'] = 'texts_title_op';
  $handler->display->display_options['filters']['texts_title']['expose']['identifier'] = 'texts_title';
  $handler->display->display_options['filters']['texts_title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'related-texts';

  /* Display: Texts Block */
  $handler = $view->new_display('block', 'Texts Block', 'texts_block');
  $export['related_texts'] = $view;

  $view = new view();
  $view->name = 'related_visuals';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'kmaps_views_solr_visuals';
  $view->human_name = 'Related Visuals';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Related Visuals';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '>';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'input_required' => 0,
      'text_input_required' => array(
        'text_input_required' => array(
          'value' => 'Select any filter and click on Apply to see results',
          'format' => 'filtered_html',
        ),
      ),
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
      'secondary_collapse_override' => '0',
    ),
    'sort' => array(
      'bef_format' => 'default',
      'advanced' => array(
        'collapsible' => 0,
        'collapsible_label' => 'Sort options',
        'combine' => 1,
        'combine_param' => 'sort_bef_combine',
        'combine_rewrite' => '',
        'reset' => 0,
        'reset_label' => '',
        'is_secondary' => 0,
        'autosubmit' => 0,
      ),
    ),
    'asset_subtype' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 0,
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'visuals_title' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'autosubmit' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
  );
  $handler->display->display_options['pager']['type'] = 'pagerer';
  $handler->display->display_options['pager']['options']['items_per_page'] = '60';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['preset'] = 'mandala_pager';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'shanti-thumbnail visual';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = '<span class="label">Recent Additions</span> <span class="count">(Displaying @start - @end of @total)</span>';
  /* Field: Visuals Group: Id */
  $handler->display->display_options['fields']['visuals_id']['id'] = 'visuals_id';
  $handler->display->display_options['fields']['visuals_id']['table'] = 'kmaps_views_solr_visuals';
  $handler->display->display_options['fields']['visuals_id']['field'] = 'visuals_id';
  $handler->display->display_options['fields']['visuals_id']['label'] = '';
  $handler->display->display_options['fields']['visuals_id']['element_label_colon'] = FALSE;
  /* Field: Visuals Group: Title */
  $handler->display->display_options['fields']['visuals_title']['id'] = 'visuals_title';
  $handler->display->display_options['fields']['visuals_title']['table'] = 'kmaps_views_solr_visuals';
  $handler->display->display_options['fields']['visuals_title']['field'] = 'visuals_title';
  $handler->display->display_options['fields']['visuals_title']['label'] = '';
  $handler->display->display_options['fields']['visuals_title']['element_label_colon'] = FALSE;
  /* Field: Visuals Group: Ajax Url */
  $handler->display->display_options['fields']['ajax_url']['id'] = 'ajax_url';
  $handler->display->display_options['fields']['ajax_url']['table'] = 'kmaps_views_solr_visuals';
  $handler->display->display_options['fields']['ajax_url']['field'] = 'ajax_url';
  $handler->display->display_options['fields']['ajax_url']['label'] = '';
  $handler->display->display_options['fields']['ajax_url']['element_label_colon'] = FALSE;
  /* Field: Visuals Group: Asset SubType */
  $handler->display->display_options['fields']['asset_subtype']['id'] = 'asset_subtype';
  $handler->display->display_options['fields']['asset_subtype']['table'] = 'kmaps_views_solr_visuals';
  $handler->display->display_options['fields']['asset_subtype']['field'] = 'asset_subtype';
  $handler->display->display_options['fields']['asset_subtype']['label'] = '';
  $handler->display->display_options['fields']['asset_subtype']['element_label_colon'] = FALSE;
  /* Field: Visuals Group: Collection */
  $handler->display->display_options['fields']['collection']['id'] = 'collection';
  $handler->display->display_options['fields']['collection']['table'] = 'kmaps_views_solr_visuals';
  $handler->display->display_options['fields']['collection']['field'] = 'collection';
  $handler->display->display_options['fields']['collection']['label'] = '';
  $handler->display->display_options['fields']['collection']['element_label_colon'] = FALSE;
  /* Field: Visuals Group: Create Date */
  $handler->display->display_options['fields']['created_date']['id'] = 'created_date';
  $handler->display->display_options['fields']['created_date']['table'] = 'kmaps_views_solr_visuals';
  $handler->display->display_options['fields']['created_date']['field'] = 'created_date';
  $handler->display->display_options['fields']['created_date']['label'] = '';
  $handler->display->display_options['fields']['created_date']['element_label_colon'] = FALSE;
  /* Field: Visuals Group: Thumb */
  $handler->display->display_options['fields']['thumb']['id'] = 'thumb';
  $handler->display->display_options['fields']['thumb']['table'] = 'kmaps_views_solr_visuals';
  $handler->display->display_options['fields']['thumb']['field'] = 'thumb';
  $handler->display->display_options['fields']['thumb']['label'] = '';
  $handler->display->display_options['fields']['thumb']['element_label_colon'] = FALSE;
  /* Field: Visuals Group: Creator */
  $handler->display->display_options['fields']['creator']['id'] = 'creator';
  $handler->display->display_options['fields']['creator']['table'] = 'kmaps_views_solr_visuals';
  $handler->display->display_options['fields']['creator']['field'] = 'creator';
  $handler->display->display_options['fields']['creator']['label'] = '';
  $handler->display->display_options['fields']['creator']['element_label_colon'] = FALSE;
  /* Sort criterion: Visuals Group: Create Date */
  $handler->display->display_options['sorts']['created_date']['id'] = 'created_date';
  $handler->display->display_options['sorts']['created_date']['table'] = 'kmaps_views_solr_visuals';
  $handler->display->display_options['sorts']['created_date']['field'] = 'created_date';
  $handler->display->display_options['sorts']['created_date']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['created_date']['expose']['label'] = 'Post date';
  /* Filter criterion: Visuals Group: Asset SubType */
  $handler->display->display_options['filters']['asset_subtype']['id'] = 'asset_subtype';
  $handler->display->display_options['filters']['asset_subtype']['table'] = 'kmaps_views_solr_visuals';
  $handler->display->display_options['filters']['asset_subtype']['field'] = 'asset_subtype';
  $handler->display->display_options['filters']['asset_subtype']['value'] = array(
    'Graph:Chord' => 'Graph:Chord',
    'Timeline' => 'Timeline',
    'Chart:AreaChart' => 'Chart:AreaChart',
    'Word Cloud' => 'Word Cloud',
  );
  $handler->display->display_options['filters']['asset_subtype']['exposed'] = TRUE;
  $handler->display->display_options['filters']['asset_subtype']['expose']['operator_id'] = 'asset_subtype_op';
  $handler->display->display_options['filters']['asset_subtype']['expose']['operator'] = 'asset_subtype_op';
  $handler->display->display_options['filters']['asset_subtype']['expose']['identifier'] = 'asset_subtype';
  $handler->display->display_options['filters']['asset_subtype']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Visuals Group: Title */
  $handler->display->display_options['filters']['visuals_title']['id'] = 'visuals_title';
  $handler->display->display_options['filters']['visuals_title']['table'] = 'kmaps_views_solr_visuals';
  $handler->display->display_options['filters']['visuals_title']['field'] = 'visuals_title';
  $handler->display->display_options['filters']['visuals_title']['operator'] = 'contains';
  $handler->display->display_options['filters']['visuals_title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['visuals_title']['expose']['operator_id'] = 'visuals_title_op';
  $handler->display->display_options['filters']['visuals_title']['expose']['operator'] = 'visuals_title_op';
  $handler->display->display_options['filters']['visuals_title']['expose']['identifier'] = 'visuals_title';
  $handler->display->display_options['filters']['visuals_title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'related-visuals';

  /* Display: Visuals Block */
  $handler = $view->new_display('block', 'Visuals Block', 'visuals_block');
  $export['related_visuals'] = $view;

  return $export;
}
