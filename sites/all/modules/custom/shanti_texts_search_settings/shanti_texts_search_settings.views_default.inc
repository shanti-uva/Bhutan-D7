<?php
/**
 * @file
 * shanti_texts_search_settings.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function shanti_texts_search_settings_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'full_text_solr';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'search_api_index_full_text_local';
  $view->human_name = 'Full Text Solr';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Full Text Solr';
  $handler->display->display_options['css_class'] = 'view-fulltext-search';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '&#8203;';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'pagerer';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['preset'] = 'shanti_default';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<p>Enter a search string, consisting of a word or a phrase enclosed in quotes, to find matching text content.</p>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: Indexed Node: Book */
  $handler->display->display_options['relationships']['book']['id'] = 'book';
  $handler->display->display_options['relationships']['book']['table'] = 'search_api_index_full_text_local';
  $handler->display->display_options['relationships']['book']['field'] = 'book';
  /* Field: Indexed Node: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_full_text_local';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['link_to_entity'] = 0;
  /* Field: Indexed Node: Book ancestors */
  $handler->display->display_options['fields']['book_ancestors']['id'] = 'book_ancestors';
  $handler->display->display_options['fields']['book_ancestors']['table'] = 'search_api_index_full_text_local';
  $handler->display->display_options['fields']['book_ancestors']['field'] = 'book_ancestors';
  $handler->display->display_options['fields']['book_ancestors']['label'] = '';
  $handler->display->display_options['fields']['book_ancestors']['exclude'] = TRUE;
  $handler->display->display_options['fields']['book_ancestors']['alter']['text'] = '[book_ancestors] >';
  $handler->display->display_options['fields']['book_ancestors']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['book_ancestors']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['book_ancestors']['view_mode'] = 'full';
  $handler->display->display_options['fields']['book_ancestors']['bypass_access'] = 0;
  /* Field: Indexed Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_full_text_local';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 0;
  /* Field: Search: Excerpt */
  $handler->display->display_options['fields']['search_api_excerpt']['id'] = 'search_api_excerpt';
  $handler->display->display_options['fields']['search_api_excerpt']['table'] = 'search_api_index_full_text_local';
  $handler->display->display_options['fields']['search_api_excerpt']['field'] = 'search_api_excerpt';
  $handler->display->display_options['fields']['search_api_excerpt']['label'] = '';
  $handler->display->display_options['fields']['search_api_excerpt']['exclude'] = TRUE;
  $handler->display->display_options['fields']['search_api_excerpt']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['search_api_excerpt']['link_to_entity'] = 0;
  /* Field: Result */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Result';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<!-- __SEARCHTERM__ is replaced by the value of the search input filter in the template for this field -->
<h3>[book_ancestors] <a href="/node/[nid_1]?s=__SEARCHTERM__">[title]</a></h3>
<p>[search_api_excerpt]</p>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Sort criterion: Search: Relevance */
  $handler->display->display_options['sorts']['search_api_relevance']['id'] = 'search_api_relevance';
  $handler->display->display_options['sorts']['search_api_relevance']['table'] = 'search_api_index_full_text_local';
  $handler->display->display_options['sorts']['search_api_relevance']['field'] = 'search_api_relevance';
  /* Filter criterion: Search: Fulltext search */
  $handler->display->display_options['filters']['search_api_views_fulltext']['id'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['table'] = 'search_api_index_full_text_local';
  $handler->display->display_options['filters']['search_api_views_fulltext']['field'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator_id'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['identifier'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['required'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    6 => 0,
    11 => 0,
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $translatables['full_text_solr'] = array(
    t('Master'),
    t('Full Text Solr'),
    t('more'),
    t('&#8203;'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('<p>Enter a search string, consisting of a word or a phrase enclosed in quotes, to find matching text content.</p>'),
    t('Book'),
    t('.'),
    t(','),
    t('[book_ancestors] >'),
    t('<!-- __SEARCHTERM__ is replaced by the value of the search input filter in the template for this field -->
<h3>[book_ancestors] <a href="/node/[nid_1]?s=__SEARCHTERM__">[title]</a></h3>
<p>[search_api_excerpt]</p>'),
    t('Block'),
  );
  $export['full_text_solr'] = $view;

  return $export;
}
