<?php

/**
 * @file
 * sources_biblio_search.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function sources_biblio_search_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'biblio_search_api';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'search_api_index_database_node_index';
  $view->human_name = 'biblio_search_api';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Contemplative Science Bibliography';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['search_api_bypass_access'] = 0;
  $handler->display->display_options['query']['options']['entity_access'] = 0;
  $handler->display->display_options['query']['options']['parse_mode'] = 'single';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<p class="no-results">There are no search results that match your criteria.</p>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: Indexed Node: Zotero Collections */
  $handler->display->display_options['relationships']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['relationships']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['relationships']['field_zotero_collections']['field'] = 'field_zotero_collections';
  /* Field: Indexed Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 1;
  /* Field: Indexed Node: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['separator'] = '';
  $handler->display->display_options['fields']['nid']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_authors */
  $handler->display->display_options['fields']['biblio_authors']['id'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_authors']['field'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['exclude'] = TRUE;
  /* Field: Indexed Node: biblio_year */
  $handler->display->display_options['fields']['biblio_year']['id'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_year']['field'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['label'] = '';
  $handler->display->display_options['fields']['biblio_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['text'] = '[biblio_year].';
  $handler->display->display_options['fields']['biblio_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_year']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['empty_zero'] = TRUE;
  /* Field: Indexed Node: biblio_publisher */
  $handler->display->display_options['fields']['biblio_publisher']['id'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_publisher']['field'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['exclude'] = TRUE;
  /* Field: citation */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'citation';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[biblio_authors] [biblio_year] [title] [biblio_publisher]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Indexed Node: biblio_abst_e */
  $handler->display->display_options['fields']['biblio_abst_e']['id'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_abst_e']['field'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['label'] = '';
  $handler->display->display_options['fields']['biblio_abst_e']['element_label_colon'] = FALSE;
  /* Field: Indexed Node: Zotero Tags */
  $handler->display->display_options['fields']['field_zotero_tags']['id'] = 'field_zotero_tags';
  $handler->display->display_options['fields']['field_zotero_tags']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_zotero_tags']['field'] = 'field_zotero_tags';
  $handler->display->display_options['fields']['field_zotero_tags']['element_label_type'] = 'strong';
  $handler->display->display_options['fields']['field_zotero_tags']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_zotero_tags']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_zotero_tags']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_zotero_tags']['bypass_access'] = 0;
  /* Field: Indexed Node: Zotero Collections */
  $handler->display->display_options['fields']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['fields']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_zotero_collections']['field'] = 'field_zotero_collections';
  $handler->display->display_options['fields']['field_zotero_collections']['element_label_type'] = 'strong';
  $handler->display->display_options['fields']['field_zotero_collections']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_zotero_collections']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_zotero_collections']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_zotero_collections']['bypass_access'] = 0;
  /* Field: linebreak */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'linebreak';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<br>';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  /* Sort criterion: Indexed Node: Author */
  $handler->display->display_options['sorts']['author']['id'] = 'author';
  $handler->display->display_options['sorts']['author']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['author']['field'] = 'author';
  $handler->display->display_options['sorts']['author']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['author']['expose']['label'] = 'Author';
  /* Sort criterion: Indexed Node: Date created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Filter criterion: Search: Fulltext search */
  $handler->display->display_options['filters']['search_api_views_fulltext']['id'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_api_views_fulltext']['field'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator_id'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['identifier'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
  );
  /* Filter criterion: Indexed Node: Content type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'biblio' => 'biblio',
  );
  /* Filter criterion: Indexed Node: Node ID */
  $handler->display->display_options['filters']['nid']['id'] = 'nid';
  $handler->display->display_options['filters']['nid']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['nid']['field'] = 'nid';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Sources';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'input_required';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Clear';
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'full_html';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'pagerer';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '1, 25';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '';
  $handler->display->display_options['pager']['options']['preset'] = 'shanti_pager';
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<p class="no-results">There are no search results that match your criteria.</p>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Indexed Node: Zotero Collections */
  $handler->display->display_options['relationships']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['relationships']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['relationships']['field_zotero_collections']['field'] = 'field_zotero_collections';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Indexed Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 1;
  /* Field: Indexed Node: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['separator'] = '';
  $handler->display->display_options['fields']['nid']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_authors */
  $handler->display->display_options['fields']['biblio_authors']['id'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_authors']['field'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['label'] = '';
  $handler->display->display_options['fields']['biblio_authors']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_authors']['list']['mode'] = 'list';
  $handler->display->display_options['fields']['biblio_authors']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_year */
  $handler->display->display_options['fields']['biblio_year']['id'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_year']['field'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['label'] = '';
  $handler->display->display_options['fields']['biblio_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['text'] = '[biblio_year].';
  $handler->display->display_options['fields']['biblio_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_year']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['empty_zero'] = TRUE;
  /* Field: Indexed Node: biblio_publisher */
  $handler->display->display_options['fields']['biblio_publisher']['id'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_publisher']['field'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['exclude'] = TRUE;
  /* Field: citation */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'citation';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[biblio_authors] [biblio_year] [title] [biblio_publisher]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Indexed Node: biblio_abst_e */
  $handler->display->display_options['fields']['biblio_abst_e']['id'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_abst_e']['field'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['label'] = '';
  $handler->display->display_options['fields']['biblio_abst_e']['element_label_colon'] = FALSE;
  /* Field: Indexed Node: Zotero Tags */
  $handler->display->display_options['fields']['field_zotero_tags']['id'] = 'field_zotero_tags';
  $handler->display->display_options['fields']['field_zotero_tags']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_zotero_tags']['field'] = 'field_zotero_tags';
  $handler->display->display_options['fields']['field_zotero_tags']['element_label_type'] = 'strong';
  $handler->display->display_options['fields']['field_zotero_tags']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_zotero_tags']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_zotero_tags']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_zotero_tags']['bypass_access'] = 0;
  /* Field: Indexed Node: Zotero Collections */
  $handler->display->display_options['fields']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['fields']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_zotero_collections']['field'] = 'field_zotero_collections';
  $handler->display->display_options['fields']['field_zotero_collections']['element_label_type'] = 'strong';
  $handler->display->display_options['fields']['field_zotero_collections']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_zotero_collections']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_zotero_collections']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_zotero_collections']['bypass_access'] = 0;
  /* Field: linebreak */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'linebreak';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<br>';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  /* Field: Indexed Node: Publication Type */
  $handler->display->display_options['fields']['biblio_publication_type']['id'] = 'biblio_publication_type';
  $handler->display->display_options['fields']['biblio_publication_type']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_publication_type']['field'] = 'biblio_publication_type';
  $handler->display->display_options['fields']['biblio_publication_type']['label'] = '';
  $handler->display->display_options['fields']['biblio_publication_type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_publication_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_publication_type']['link_to_entity'] = 0;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Indexed Node: Sorting Stripped Node Title */
  $handler->display->display_options['sorts']['sort_stripped_node_title']['id'] = 'sort_stripped_node_title';
  $handler->display->display_options['sorts']['sort_stripped_node_title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['sort_stripped_node_title']['field'] = 'sort_stripped_node_title';
  $handler->display->display_options['sorts']['sort_stripped_node_title']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['sort_stripped_node_title']['expose']['label'] = 'Stripped Node Title';
  /* Sort criterion: Indexed Node: Sorting Biblio Author */
  $handler->display->display_options['sorts']['sort_biblio_author']['id'] = 'sort_biblio_author';
  $handler->display->display_options['sorts']['sort_biblio_author']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['sort_biblio_author']['field'] = 'sort_biblio_author';
  $handler->display->display_options['sorts']['sort_biblio_author']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['sort_biblio_author']['expose']['label'] = 'Biblio Author';
  /* Sort criterion: Indexed Node: Sorting Custom Publication Year */
  $handler->display->display_options['sorts']['sort_custom_publication_year']['id'] = 'sort_custom_publication_year';
  $handler->display->display_options['sorts']['sort_custom_publication_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['sort_custom_publication_year']['field'] = 'sort_custom_publication_year';
  $handler->display->display_options['sorts']['sort_custom_publication_year']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['sort_custom_publication_year']['expose']['label'] = 'Custom Publication Year';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Search: Fulltext search */
  $handler->display->display_options['filters']['search_api_views_fulltext']['id'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_api_views_fulltext']['field'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['group'] = 1;
  $handler->display->display_options['filters']['search_api_views_fulltext']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator_id'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['identifier'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['search_api_views_fulltext']['fields'] = array(
    'title' => 'title',
    'search_text_biblio_author' => 'search_text_biblio_author',
    'search_text_biblio_publisher' => 'search_text_biblio_publisher',
    'search_text_biblio_publish_place' => 'search_text_biblio_publish_place',
    'search_text_biblio_abstract' => 'search_text_biblio_abstract',
    'search_text_zotero_tags' => 'search_text_zotero_tags',
  );
  /* Filter criterion: Indexed Node: Content type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'biblio' => 'biblio',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Indexed Node: Zotero Collections */
  $handler->display->display_options['filters']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['filters']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['field_zotero_collections']['field'] = 'field_zotero_collections';
  $handler->display->display_options['filters']['field_zotero_collections']['value'] = array();
  $handler->display->display_options['filters']['field_zotero_collections']['group'] = 1;
  $handler->display->display_options['filters']['field_zotero_collections']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_zotero_collections']['expose']['operator_id'] = 'field_zotero_collections_op';
  $handler->display->display_options['filters']['field_zotero_collections']['expose']['operator'] = 'field_zotero_collections_op';
  $handler->display->display_options['filters']['field_zotero_collections']['expose']['identifier'] = 'field_zotero_collections';
  $handler->display->display_options['filters']['field_zotero_collections']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_zotero_collections']['expose']['reduce'] = 0;
  /* Filter criterion: Indexed Node: Publication Type */
  $handler->display->display_options['filters']['biblio_publication_type']['id'] = 'biblio_publication_type';
  $handler->display->display_options['filters']['biblio_publication_type']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_publication_type']['field'] = 'biblio_publication_type';
  $handler->display->display_options['filters']['biblio_publication_type']['group'] = 1;
  $handler->display->display_options['filters']['biblio_publication_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['operator_id'] = 'biblio_publication_type_op';
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['label'] = 'Source Type';
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['operator'] = 'biblio_publication_type_op';
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['identifier'] = 'biblio_publication_type';
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: biblio_authors */
  $handler->display->display_options['filters']['biblio_authors']['id'] = 'biblio_authors';
  $handler->display->display_options['filters']['biblio_authors']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_authors']['field'] = 'biblio_authors';
  $handler->display->display_options['filters']['biblio_authors']['group'] = 1;
  $handler->display->display_options['filters']['biblio_authors']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_authors']['expose']['operator_id'] = 'biblio_authors_op';
  $handler->display->display_options['filters']['biblio_authors']['expose']['label'] = 'Authors';
  $handler->display->display_options['filters']['biblio_authors']['expose']['operator'] = 'biblio_authors_op';
  $handler->display->display_options['filters']['biblio_authors']['expose']['identifier'] = 'biblio_authors';
  $handler->display->display_options['filters']['biblio_authors']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: biblio_publisher */
  $handler->display->display_options['filters']['biblio_publisher']['id'] = 'biblio_publisher';
  $handler->display->display_options['filters']['biblio_publisher']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_publisher']['field'] = 'biblio_publisher';
  $handler->display->display_options['filters']['biblio_publisher']['group'] = 1;
  $handler->display->display_options['filters']['biblio_publisher']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_publisher']['expose']['operator_id'] = 'biblio_publisher_op';
  $handler->display->display_options['filters']['biblio_publisher']['expose']['label'] = 'Publishers';
  $handler->display->display_options['filters']['biblio_publisher']['expose']['operator'] = 'biblio_publisher_op';
  $handler->display->display_options['filters']['biblio_publisher']['expose']['identifier'] = 'biblio_publisher';
  $handler->display->display_options['filters']['biblio_publisher']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: biblio_place_published */
  $handler->display->display_options['filters']['biblio_place_published']['id'] = 'biblio_place_published';
  $handler->display->display_options['filters']['biblio_place_published']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_place_published']['field'] = 'biblio_place_published';
  $handler->display->display_options['filters']['biblio_place_published']['group'] = 1;
  $handler->display->display_options['filters']['biblio_place_published']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_place_published']['expose']['operator_id'] = 'biblio_place_published_op';
  $handler->display->display_options['filters']['biblio_place_published']['expose']['label'] = 'Location';
  $handler->display->display_options['filters']['biblio_place_published']['expose']['operator'] = 'biblio_place_published_op';
  $handler->display->display_options['filters']['biblio_place_published']['expose']['identifier'] = 'biblio_place_published';
  $handler->display->display_options['filters']['biblio_place_published']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Zotero Tags */
  $handler->display->display_options['filters']['field_zotero_tags']['id'] = 'field_zotero_tags';
  $handler->display->display_options['filters']['field_zotero_tags']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['field_zotero_tags']['field'] = 'field_zotero_tags';
  $handler->display->display_options['filters']['field_zotero_tags']['group'] = 1;
  $handler->display->display_options['filters']['field_zotero_tags']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['operator_id'] = 'field_zotero_tags_op';
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['label'] = 'Tags';
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['operator'] = 'field_zotero_tags_op';
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['identifier'] = 'field_zotero_tags';
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Search text biblio authors */
  $handler->display->display_options['filters']['search_text_biblio_author']['id'] = 'search_text_biblio_author';
  $handler->display->display_options['filters']['search_text_biblio_author']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_text_biblio_author']['field'] = 'search_text_biblio_author';
  $handler->display->display_options['filters']['search_text_biblio_author']['group'] = 1;
  $handler->display->display_options['filters']['search_text_biblio_author']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_text_biblio_author']['expose']['operator_id'] = 'search_text_biblio_author_op';
  $handler->display->display_options['filters']['search_text_biblio_author']['expose']['label'] = 'Author';
  $handler->display->display_options['filters']['search_text_biblio_author']['expose']['operator'] = 'search_text_biblio_author_op';
  $handler->display->display_options['filters']['search_text_biblio_author']['expose']['identifier'] = 'search_text_biblio_author';
  $handler->display->display_options['filters']['search_text_biblio_author']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Search text abstract */
  $handler->display->display_options['filters']['search_text_biblio_abstract']['id'] = 'search_text_biblio_abstract';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['field'] = 'search_text_biblio_abstract';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['group'] = 1;
  $handler->display->display_options['filters']['search_text_biblio_abstract']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_text_biblio_abstract']['expose']['operator_id'] = 'search_text_biblio_abstract_op';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['expose']['label'] = 'Enter words in abstract';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['expose']['operator'] = 'search_text_biblio_abstract_op';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['expose']['identifier'] = 'search_text_biblio_abstract';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Search text publish place */
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['id'] = 'search_text_biblio_publish_place';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['field'] = 'search_text_biblio_publish_place';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['group'] = 1;
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['expose']['operator_id'] = 'search_text_biblio_publish_place_op';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['expose']['label'] = 'Publish place';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['expose']['operator'] = 'search_text_biblio_publish_place_op';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['expose']['identifier'] = 'search_text_biblio_publish_place';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Search text publisher */
  $handler->display->display_options['filters']['search_text_biblio_publisher']['id'] = 'search_text_biblio_publisher';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['field'] = 'search_text_biblio_publisher';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['group'] = 1;
  $handler->display->display_options['filters']['search_text_biblio_publisher']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_text_biblio_publisher']['expose']['operator_id'] = 'search_text_biblio_publisher_op';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['expose']['label'] = 'Publisher';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['expose']['operator'] = 'search_text_biblio_publisher_op';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['expose']['identifier'] = 'search_text_biblio_publisher';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Search text zotero tags */
  $handler->display->display_options['filters']['search_text_zotero_tags']['id'] = 'search_text_zotero_tags';
  $handler->display->display_options['filters']['search_text_zotero_tags']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_text_zotero_tags']['field'] = 'search_text_zotero_tags';
  $handler->display->display_options['filters']['search_text_zotero_tags']['group'] = 1;
  $handler->display->display_options['filters']['search_text_zotero_tags']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_text_zotero_tags']['expose']['operator_id'] = 'search_text_zotero_tags_op';
  $handler->display->display_options['filters']['search_text_zotero_tags']['expose']['label'] = 'Tags';
  $handler->display->display_options['filters']['search_text_zotero_tags']['expose']['operator'] = 'search_text_zotero_tags_op';
  $handler->display->display_options['filters']['search_text_zotero_tags']['expose']['identifier'] = 'search_text_zotero_tags';
  $handler->display->display_options['filters']['search_text_zotero_tags']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Publish Year Start */
  $handler->display->display_options['filters']['biblio_year']['id'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_year']['field'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['ui_name'] = 'Publish Year Start';
  $handler->display->display_options['filters']['biblio_year']['operator'] = '>=';
  $handler->display->display_options['filters']['biblio_year']['group'] = 2;
  $handler->display->display_options['filters']['biblio_year']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_year']['expose']['operator_id'] = 'biblio_year_op';
  $handler->display->display_options['filters']['biblio_year']['expose']['operator'] = 'biblio_year_op';
  $handler->display->display_options['filters']['biblio_year']['expose']['identifier'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['biblio_year']['group_info']['label'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['group_info']['identifier'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['biblio_year']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Publish Year End */
  $handler->display->display_options['filters']['biblio_year_1']['id'] = 'biblio_year_1';
  $handler->display->display_options['filters']['biblio_year_1']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_year_1']['field'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year_1']['ui_name'] = 'Publish Year End';
  $handler->display->display_options['filters']['biblio_year_1']['operator'] = '<=';
  $handler->display->display_options['filters']['biblio_year_1']['group'] = 2;
  $handler->display->display_options['filters']['biblio_year_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_year_1']['expose']['operator_id'] = 'biblio_year_1_op';
  $handler->display->display_options['filters']['biblio_year_1']['expose']['operator'] = 'biblio_year_1_op';
  $handler->display->display_options['filters']['biblio_year_1']['expose']['identifier'] = 'biblio_year_1';
  $handler->display->display_options['filters']['biblio_year_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Node ID */
  $handler->display->display_options['filters']['nid']['id'] = 'nid';
  $handler->display->display_options['filters']['nid']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['nid']['field'] = 'nid';
  $handler->display->display_options['path'] = 'sources-search';

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Sources';
  $handler->display->display_options['defaults']['sorts'] = FALSE;

  /* Display: Individual Content Page */
  $handler = $view->new_display('page', 'Individual Content Page', 'biblio_full');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Sources';
  $handler->display->display_options['enabled'] = FALSE;
  $handler->display->display_options['display_description'] = 'Shows one piece of content / source in detail on it\'s dedicated page';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '1, 25';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No results';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Indexed Node: Zotero Collections */
  $handler->display->display_options['relationships']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['relationships']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['relationships']['field_zotero_collections']['field'] = 'field_zotero_collections';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Indexed Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title] [biblio_year]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 0;
  /* Field: Indexed Node: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['separator'] = '';
  $handler->display->display_options['fields']['nid']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_authors */
  $handler->display->display_options['fields']['biblio_authors']['id'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_authors']['field'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['label'] = '';
  $handler->display->display_options['fields']['biblio_authors']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['biblio_authors']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['biblio_authors']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_authors']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_authors']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_authors']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_year */
  $handler->display->display_options['fields']['biblio_year_1']['id'] = 'biblio_year_1';
  $handler->display->display_options['fields']['biblio_year_1']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_year_1']['field'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year_1']['label'] = 'Publication Year';
  $handler->display->display_options['fields']['biblio_year_1']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_year_1']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_year_1']['link_to_entity'] = 0;
  /* Field: Indexed Node: Publication Type */
  $handler->display->display_options['fields']['biblio_publication_type_1']['id'] = 'biblio_publication_type_1';
  $handler->display->display_options['fields']['biblio_publication_type_1']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_publication_type_1']['field'] = 'biblio_publication_type';
  $handler->display->display_options['fields']['biblio_publication_type_1']['label'] = 'Format';
  $handler->display->display_options['fields']['biblio_publication_type_1']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_publication_type_1']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_publication_type_1']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_publisher */
  $handler->display->display_options['fields']['biblio_publisher']['id'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_publisher']['field'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['exclude'] = TRUE;
  /* Field: Indexed Node: biblio_place_published */
  $handler->display->display_options['fields']['biblio_place_published']['id'] = 'biblio_place_published';
  $handler->display->display_options['fields']['biblio_place_published']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_place_published']['field'] = 'biblio_place_published';
  $handler->display->display_options['fields']['biblio_place_published']['label'] = '';
  $handler->display->display_options['fields']['biblio_place_published']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_place_published']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_abst_f */
  $handler->display->display_options['fields']['biblio_abst_f']['id'] = 'biblio_abst_f';
  $handler->display->display_options['fields']['biblio_abst_f']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_abst_f']['field'] = 'biblio_abst_f';
  $handler->display->display_options['fields']['biblio_abst_f']['label'] = 'French Abstract';
  $handler->display->display_options['fields']['biblio_abst_f']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_abst_f']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_abst_f']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_abst_e */
  $handler->display->display_options['fields']['biblio_abst_e']['id'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_abst_e']['field'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['label'] = '';
  $handler->display->display_options['fields']['biblio_abst_e']['element_label_colon'] = FALSE;
  /* Field: Indexed Node: Zotero Tags */
  $handler->display->display_options['fields']['field_zotero_tags']['id'] = 'field_zotero_tags';
  $handler->display->display_options['fields']['field_zotero_tags']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_zotero_tags']['field'] = 'field_zotero_tags';
  $handler->display->display_options['fields']['field_zotero_tags']['label'] = '';
  $handler->display->display_options['fields']['field_zotero_tags']['element_label_type'] = 'strong';
  $handler->display->display_options['fields']['field_zotero_tags']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_zotero_tags']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_zotero_tags']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_zotero_tags']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_zotero_tags']['bypass_access'] = 0;
  /* Field: The main body text: Summary (indexed) */
  $handler->display->display_options['fields']['body_summary']['id'] = 'body_summary';
  $handler->display->display_options['fields']['body_summary']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['body_summary']['field'] = 'body_summary';
  $handler->display->display_options['fields']['body_summary']['label'] = 'Summary';
  $handler->display->display_options['fields']['body_summary']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['body_summary']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['body_summary']['link_to_entity'] = 0;
  /* Field: The main body text: Text (indexed) */
  $handler->display->display_options['fields']['body_value']['id'] = 'body_value';
  $handler->display->display_options['fields']['body_value']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['body_value']['field'] = 'body_value';
  $handler->display->display_options['fields']['body_value']['label'] = 'Full Text';
  $handler->display->display_options['fields']['body_value']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['body_value']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['body_value']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_secondary_title */
  $handler->display->display_options['fields']['biblio_secondary_title']['id'] = 'biblio_secondary_title';
  $handler->display->display_options['fields']['biblio_secondary_title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_secondary_title']['field'] = 'biblio_secondary_title';
  $handler->display->display_options['fields']['biblio_secondary_title']['label'] = 'Published In';
  $handler->display->display_options['fields']['biblio_secondary_title']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_secondary_title']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_secondary_title']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_tertiary_title */
  $handler->display->display_options['fields']['biblio_tertiary_title']['id'] = 'biblio_tertiary_title';
  $handler->display->display_options['fields']['biblio_tertiary_title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_tertiary_title']['field'] = 'biblio_tertiary_title';
  $handler->display->display_options['fields']['biblio_tertiary_title']['label'] = 'Tertiary Title';
  $handler->display->display_options['fields']['biblio_tertiary_title']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_tertiary_title']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_tertiary_title']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_volume */
  $handler->display->display_options['fields']['biblio_volume']['id'] = 'biblio_volume';
  $handler->display->display_options['fields']['biblio_volume']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_volume']['field'] = 'biblio_volume';
  $handler->display->display_options['fields']['biblio_volume']['label'] = 'Volume';
  $handler->display->display_options['fields']['biblio_volume']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_volume']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_edition */
  $handler->display->display_options['fields']['biblio_edition']['id'] = 'biblio_edition';
  $handler->display->display_options['fields']['biblio_edition']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_edition']['field'] = 'biblio_edition';
  $handler->display->display_options['fields']['biblio_edition']['label'] = 'Edition';
  $handler->display->display_options['fields']['biblio_edition']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_edition']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_edition']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_number_of_volumes */
  $handler->display->display_options['fields']['biblio_number_of_volumes']['id'] = 'biblio_number_of_volumes';
  $handler->display->display_options['fields']['biblio_number_of_volumes']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_number_of_volumes']['field'] = 'biblio_number_of_volumes';
  $handler->display->display_options['fields']['biblio_number_of_volumes']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_number_of_volumes']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_number_of_volumes']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_section */
  $handler->display->display_options['fields']['biblio_section']['id'] = 'biblio_section';
  $handler->display->display_options['fields']['biblio_section']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_section']['field'] = 'biblio_section';
  $handler->display->display_options['fields']['biblio_section']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_section']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_section']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_number */
  $handler->display->display_options['fields']['biblio_number']['id'] = 'biblio_number';
  $handler->display->display_options['fields']['biblio_number']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_number']['field'] = 'biblio_number';
  $handler->display->display_options['fields']['biblio_number']['label'] = 'Start Page';
  $handler->display->display_options['fields']['biblio_number']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_number']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_number']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_pages */
  $handler->display->display_options['fields']['biblio_pages']['id'] = 'biblio_pages';
  $handler->display->display_options['fields']['biblio_pages']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_pages']['field'] = 'biblio_pages';
  $handler->display->display_options['fields']['biblio_pages']['label'] = 'Pages';
  $handler->display->display_options['fields']['biblio_pages']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_pages']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_date */
  $handler->display->display_options['fields']['biblio_date']['id'] = 'biblio_date';
  $handler->display->display_options['fields']['biblio_date']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_date']['field'] = 'biblio_date';
  $handler->display->display_options['fields']['biblio_date']['label'] = 'Date Published';
  $handler->display->display_options['fields']['biblio_date']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_date']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_type_of_work */
  $handler->display->display_options['fields']['biblio_type_of_work']['id'] = 'biblio_type_of_work';
  $handler->display->display_options['fields']['biblio_type_of_work']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_type_of_work']['field'] = 'biblio_type_of_work';
  $handler->display->display_options['fields']['biblio_type_of_work']['label'] = 'Type of Work';
  $handler->display->display_options['fields']['biblio_type_of_work']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_type_of_work']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_reprint_edition */
  $handler->display->display_options['fields']['biblio_reprint_edition']['id'] = 'biblio_reprint_edition';
  $handler->display->display_options['fields']['biblio_reprint_edition']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_reprint_edition']['field'] = 'biblio_reprint_edition';
  $handler->display->display_options['fields']['biblio_reprint_edition']['label'] = 'Reprint Edition';
  $handler->display->display_options['fields']['biblio_reprint_edition']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_reprint_edition']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_issn */
  $handler->display->display_options['fields']['biblio_issn']['id'] = 'biblio_issn';
  $handler->display->display_options['fields']['biblio_issn']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_issn']['field'] = 'biblio_issn';
  $handler->display->display_options['fields']['biblio_issn']['label'] = 'ISSN';
  $handler->display->display_options['fields']['biblio_issn']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_issn']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_issn']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_isbn */
  $handler->display->display_options['fields']['biblio_isbn']['id'] = 'biblio_isbn';
  $handler->display->display_options['fields']['biblio_isbn']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_isbn']['field'] = 'biblio_isbn';
  $handler->display->display_options['fields']['biblio_isbn']['label'] = 'ISBN Number';
  $handler->display->display_options['fields']['biblio_isbn']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_isbn']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_isbn']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_accession_number */
  $handler->display->display_options['fields']['biblio_accession_number']['id'] = 'biblio_accession_number';
  $handler->display->display_options['fields']['biblio_accession_number']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_accession_number']['field'] = 'biblio_accession_number';
  $handler->display->display_options['fields']['biblio_accession_number']['label'] = 'Accession Number';
  $handler->display->display_options['fields']['biblio_accession_number']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_accession_number']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_accession_number']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_call_number */
  $handler->display->display_options['fields']['biblio_call_number']['id'] = 'biblio_call_number';
  $handler->display->display_options['fields']['biblio_call_number']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_call_number']['field'] = 'biblio_call_number';
  $handler->display->display_options['fields']['biblio_call_number']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_call_number']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_call_number']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_other_number */
  $handler->display->display_options['fields']['biblio_other_number']['id'] = 'biblio_other_number';
  $handler->display->display_options['fields']['biblio_other_number']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_other_number']['field'] = 'biblio_other_number';
  $handler->display->display_options['fields']['biblio_other_number']['label'] = 'Other Numbers';
  $handler->display->display_options['fields']['biblio_other_number']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_other_number']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_other_number']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_doi */
  $handler->display->display_options['fields']['biblio_doi']['id'] = 'biblio_doi';
  $handler->display->display_options['fields']['biblio_doi']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_doi']['field'] = 'biblio_doi';
  $handler->display->display_options['fields']['biblio_doi']['label'] = 'DOI';
  $handler->display->display_options['fields']['biblio_doi']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_doi']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_notes */
  $handler->display->display_options['fields']['biblio_notes']['id'] = 'biblio_notes';
  $handler->display->display_options['fields']['biblio_notes']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_notes']['field'] = 'biblio_notes';
  $handler->display->display_options['fields']['biblio_notes']['label'] = 'Notes';
  $handler->display->display_options['fields']['biblio_notes']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_notes']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_notes']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_alternate_title */
  $handler->display->display_options['fields']['biblio_alternate_title']['id'] = 'biblio_alternate_title';
  $handler->display->display_options['fields']['biblio_alternate_title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_alternate_title']['field'] = 'biblio_alternate_title';
  $handler->display->display_options['fields']['biblio_alternate_title']['label'] = 'Alternate Title';
  $handler->display->display_options['fields']['biblio_alternate_title']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_alternate_title']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_original_publication */
  $handler->display->display_options['fields']['biblio_original_publication']['id'] = 'biblio_original_publication';
  $handler->display->display_options['fields']['biblio_original_publication']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_original_publication']['field'] = 'biblio_original_publication';
  $handler->display->display_options['fields']['biblio_original_publication']['label'] = 'Original Publication';
  $handler->display->display_options['fields']['biblio_original_publication']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_original_publication']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_refereed */
  $handler->display->display_options['fields']['biblio_refereed']['id'] = 'biblio_refereed';
  $handler->display->display_options['fields']['biblio_refereed']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_refereed']['field'] = 'biblio_refereed';
  $handler->display->display_options['fields']['biblio_refereed']['label'] = 'Refereed Designation';
  $handler->display->display_options['fields']['biblio_refereed']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_refereed']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_refereed']['link_to_entity'] = 0;
  /* Field: Indexed Node: Zotero Collections */
  $handler->display->display_options['fields']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['fields']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_zotero_collections']['field'] = 'field_zotero_collections';
  $handler->display->display_options['fields']['field_zotero_collections']['element_label_type'] = 'strong';
  $handler->display->display_options['fields']['field_zotero_collections']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_zotero_collections']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_zotero_collections']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_zotero_collections']['bypass_access'] = 0;
  /* Field: Indexed Node: biblio_issue */
  $handler->display->display_options['fields']['biblio_issue']['id'] = 'biblio_issue';
  $handler->display->display_options['fields']['biblio_issue']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_issue']['field'] = 'biblio_issue';
  $handler->display->display_options['fields']['biblio_issue']['label'] = 'Issue';
  $handler->display->display_options['fields']['biblio_issue']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_issue']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_url */
  $handler->display->display_options['fields']['biblio_url']['id'] = 'biblio_url';
  $handler->display->display_options['fields']['biblio_url']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_url']['field'] = 'biblio_url';
  $handler->display->display_options['fields']['biblio_url']['label'] = 'URL';
  $handler->display->display_options['fields']['biblio_url']['alter']['text'] = '<a href="[biblio_url]">[biblio_url]</a>';
  $handler->display->display_options['fields']['biblio_url']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['biblio_url']['alter']['path'] = '[biblio_url]';
  $handler->display->display_options['fields']['biblio_url']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_url']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_url']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_lang */
  $handler->display->display_options['fields']['biblio_lang']['id'] = 'biblio_lang';
  $handler->display->display_options['fields']['biblio_lang']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_lang']['field'] = 'biblio_lang';
  $handler->display->display_options['fields']['biblio_lang']['label'] = 'Publication Language';
  $handler->display->display_options['fields']['biblio_lang']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_lang']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_lang']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_other_author_affiliations */
  $handler->display->display_options['fields']['biblio_other_author_affiliations']['id'] = 'biblio_other_author_affiliations';
  $handler->display->display_options['fields']['biblio_other_author_affiliations']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_other_author_affiliations']['field'] = 'biblio_other_author_affiliations';
  $handler->display->display_options['fields']['biblio_other_author_affiliations']['label'] = 'Other Author Affiliations';
  $handler->display->display_options['fields']['biblio_other_author_affiliations']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_other_author_affiliations']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_other_author_affiliations']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_research_notes */
  $handler->display->display_options['fields']['biblio_research_notes']['id'] = 'biblio_research_notes';
  $handler->display->display_options['fields']['biblio_research_notes']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_research_notes']['field'] = 'biblio_research_notes';
  $handler->display->display_options['fields']['biblio_research_notes']['label'] = 'Research Notes';
  $handler->display->display_options['fields']['biblio_research_notes']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_research_notes']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_research_notes']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_translated_title */
  $handler->display->display_options['fields']['biblio_translated_title']['id'] = 'biblio_translated_title';
  $handler->display->display_options['fields']['biblio_translated_title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_translated_title']['field'] = 'biblio_translated_title';
  $handler->display->display_options['fields']['biblio_translated_title']['label'] = 'Translated Title';
  $handler->display->display_options['fields']['biblio_translated_title']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_translated_title']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_translated_title']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_citekey */
  $handler->display->display_options['fields']['biblio_citekey']['id'] = 'biblio_citekey';
  $handler->display->display_options['fields']['biblio_citekey']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_citekey']['field'] = 'biblio_citekey';
  $handler->display->display_options['fields']['biblio_citekey']['label'] = 'Source ID';
  $handler->display->display_options['fields']['biblio_citekey']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['biblio_citekey']['alter']['text'] = 'shanti-sources-[biblio_citekey]';
  $handler->display->display_options['fields']['biblio_citekey']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_citekey']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_citekey']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_coins */
  $handler->display->display_options['fields']['biblio_coins']['id'] = 'biblio_coins';
  $handler->display->display_options['fields']['biblio_coins']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_coins']['field'] = 'biblio_coins';
  $handler->display->display_options['fields']['biblio_coins']['label'] = 'COinS Data';
  $handler->display->display_options['fields']['biblio_coins']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_coins']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_coins']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_coins']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_auth_address */
  $handler->display->display_options['fields']['biblio_auth_address']['id'] = 'biblio_auth_address';
  $handler->display->display_options['fields']['biblio_auth_address']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_auth_address']['field'] = 'biblio_auth_address';
  $handler->display->display_options['fields']['biblio_auth_address']['label'] = 'Author Address';
  $handler->display->display_options['fields']['biblio_auth_address']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_auth_address']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_auth_address']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_label */
  $handler->display->display_options['fields']['biblio_label']['id'] = 'biblio_label';
  $handler->display->display_options['fields']['biblio_label']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_label']['field'] = 'biblio_label';
  $handler->display->display_options['fields']['biblio_label']['label'] = 'Label';
  $handler->display->display_options['fields']['biblio_label']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_label']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_label']['link_to_entity'] = 0;
  /* Field: Indexed Node: Long Title */
  $handler->display->display_options['fields']['field_biblio_long_title']['id'] = 'field_biblio_long_title';
  $handler->display->display_options['fields']['field_biblio_long_title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_biblio_long_title']['field'] = 'field_biblio_long_title';
  $handler->display->display_options['fields']['field_biblio_long_title']['label'] = 'Title';
  $handler->display->display_options['fields']['field_biblio_long_title']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_biblio_long_title']['empty_zero'] = TRUE;
  /* Field: Indexed Node: Language */
  $handler->display->display_options['fields']['language']['id'] = 'language';
  $handler->display->display_options['fields']['language']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['language']['field'] = 'language';
  $handler->display->display_options['fields']['language']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['language']['link_to_entity'] = 0;
  $handler->display->display_options['fields']['language']['format_name'] = 1;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['field_kmap_subjects']['id'] = 'field_kmap_subjects';
  $handler->display->display_options['fields']['field_kmap_subjects']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_kmap_subjects']['field'] = 'field_kmap_subjects';
  $handler->display->display_options['fields']['field_kmap_subjects']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_kmap_subjects']['hide_empty'] = TRUE;
  /* Field: Indexed Node: Places */
  $handler->display->display_options['fields']['field_kmaps_places']['id'] = 'field_kmaps_places';
  $handler->display->display_options['fields']['field_kmaps_places']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_kmaps_places']['field'] = 'field_kmaps_places';
  $handler->display->display_options['fields']['field_kmaps_places']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_kmaps_places']['click_sort_column'] = 'raw';
  $handler->display->display_options['fields']['field_kmaps_places']['type'] = 'kmap_popover_formatter';
  $handler->display->display_options['fields']['field_kmaps_places']['settings'] = array(
    'target' => '_blank',
  );
  $handler->display->display_options['fields']['field_kmaps_places']['delta_offset'] = '0';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Indexed Node: Sorting Stripped Node Title */
  $handler->display->display_options['sorts']['sort_stripped_node_title']['id'] = 'sort_stripped_node_title';
  $handler->display->display_options['sorts']['sort_stripped_node_title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['sort_stripped_node_title']['field'] = 'sort_stripped_node_title';
  $handler->display->display_options['sorts']['sort_stripped_node_title']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['sort_stripped_node_title']['expose']['label'] = 'Stripped Node Title';
  /* Sort criterion: Indexed Node: Sorting Biblio Author */
  $handler->display->display_options['sorts']['sort_biblio_author']['id'] = 'sort_biblio_author';
  $handler->display->display_options['sorts']['sort_biblio_author']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['sort_biblio_author']['field'] = 'sort_biblio_author';
  $handler->display->display_options['sorts']['sort_biblio_author']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['sort_biblio_author']['expose']['label'] = 'Biblio Author';
  /* Sort criterion: Indexed Node: Sorting Custom Publication Year */
  $handler->display->display_options['sorts']['sort_custom_publication_year']['id'] = 'sort_custom_publication_year';
  $handler->display->display_options['sorts']['sort_custom_publication_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['sort_custom_publication_year']['field'] = 'sort_custom_publication_year';
  $handler->display->display_options['sorts']['sort_custom_publication_year']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['sort_custom_publication_year']['expose']['label'] = 'Custom Publication Year';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Indexed Node: Node ID */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['nid']['not'] = 0;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Search: Fulltext search */
  $handler->display->display_options['filters']['search_api_views_fulltext']['id'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_api_views_fulltext']['field'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['group'] = 1;
  $handler->display->display_options['filters']['search_api_views_fulltext']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator_id'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['identifier'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['search_api_views_fulltext']['fields'] = array(
    'title' => 'title',
    'search_text_biblio_author' => 'search_text_biblio_author',
    'search_text_biblio_publisher' => 'search_text_biblio_publisher',
    'search_text_biblio_publish_place' => 'search_text_biblio_publish_place',
    'search_text_biblio_abstract' => 'search_text_biblio_abstract',
    'search_text_zotero_tags' => 'search_text_zotero_tags',
  );
  /* Filter criterion: Indexed Node: Content type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'biblio' => 'biblio',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Indexed Node: Zotero Collections */
  $handler->display->display_options['filters']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['filters']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['field_zotero_collections']['field'] = 'field_zotero_collections';
  $handler->display->display_options['filters']['field_zotero_collections']['value'] = array();
  $handler->display->display_options['filters']['field_zotero_collections']['group'] = 1;
  $handler->display->display_options['filters']['field_zotero_collections']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_zotero_collections']['expose']['operator_id'] = 'field_zotero_collections_op';
  $handler->display->display_options['filters']['field_zotero_collections']['expose']['operator'] = 'field_zotero_collections_op';
  $handler->display->display_options['filters']['field_zotero_collections']['expose']['identifier'] = 'field_zotero_collections';
  $handler->display->display_options['filters']['field_zotero_collections']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_zotero_collections']['expose']['reduce'] = 0;
  /* Filter criterion: Indexed Node: Publication Type */
  $handler->display->display_options['filters']['biblio_publication_type']['id'] = 'biblio_publication_type';
  $handler->display->display_options['filters']['biblio_publication_type']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_publication_type']['field'] = 'biblio_publication_type';
  $handler->display->display_options['filters']['biblio_publication_type']['group'] = 1;
  $handler->display->display_options['filters']['biblio_publication_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['operator_id'] = 'biblio_publication_type_op';
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['label'] = 'Source Type';
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['operator'] = 'biblio_publication_type_op';
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['identifier'] = 'biblio_publication_type';
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: biblio_authors */
  $handler->display->display_options['filters']['biblio_authors']['id'] = 'biblio_authors';
  $handler->display->display_options['filters']['biblio_authors']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_authors']['field'] = 'biblio_authors';
  $handler->display->display_options['filters']['biblio_authors']['group'] = 1;
  $handler->display->display_options['filters']['biblio_authors']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_authors']['expose']['operator_id'] = 'biblio_authors_op';
  $handler->display->display_options['filters']['biblio_authors']['expose']['label'] = 'Authors';
  $handler->display->display_options['filters']['biblio_authors']['expose']['operator'] = 'biblio_authors_op';
  $handler->display->display_options['filters']['biblio_authors']['expose']['identifier'] = 'biblio_authors';
  $handler->display->display_options['filters']['biblio_authors']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: biblio_publisher */
  $handler->display->display_options['filters']['biblio_publisher']['id'] = 'biblio_publisher';
  $handler->display->display_options['filters']['biblio_publisher']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_publisher']['field'] = 'biblio_publisher';
  $handler->display->display_options['filters']['biblio_publisher']['group'] = 1;
  $handler->display->display_options['filters']['biblio_publisher']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_publisher']['expose']['operator_id'] = 'biblio_publisher_op';
  $handler->display->display_options['filters']['biblio_publisher']['expose']['label'] = 'Publishers';
  $handler->display->display_options['filters']['biblio_publisher']['expose']['operator'] = 'biblio_publisher_op';
  $handler->display->display_options['filters']['biblio_publisher']['expose']['identifier'] = 'biblio_publisher';
  $handler->display->display_options['filters']['biblio_publisher']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: biblio_place_published */
  $handler->display->display_options['filters']['biblio_place_published']['id'] = 'biblio_place_published';
  $handler->display->display_options['filters']['biblio_place_published']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_place_published']['field'] = 'biblio_place_published';
  $handler->display->display_options['filters']['biblio_place_published']['group'] = 1;
  $handler->display->display_options['filters']['biblio_place_published']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_place_published']['expose']['operator_id'] = 'biblio_place_published_op';
  $handler->display->display_options['filters']['biblio_place_published']['expose']['label'] = 'Location';
  $handler->display->display_options['filters']['biblio_place_published']['expose']['operator'] = 'biblio_place_published_op';
  $handler->display->display_options['filters']['biblio_place_published']['expose']['identifier'] = 'biblio_place_published';
  $handler->display->display_options['filters']['biblio_place_published']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Zotero Tags */
  $handler->display->display_options['filters']['field_zotero_tags']['id'] = 'field_zotero_tags';
  $handler->display->display_options['filters']['field_zotero_tags']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['field_zotero_tags']['field'] = 'field_zotero_tags';
  $handler->display->display_options['filters']['field_zotero_tags']['group'] = 1;
  $handler->display->display_options['filters']['field_zotero_tags']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['operator_id'] = 'field_zotero_tags_op';
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['label'] = 'Tags';
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['operator'] = 'field_zotero_tags_op';
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['identifier'] = 'field_zotero_tags';
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Search text biblio authors */
  $handler->display->display_options['filters']['search_text_biblio_author']['id'] = 'search_text_biblio_author';
  $handler->display->display_options['filters']['search_text_biblio_author']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_text_biblio_author']['field'] = 'search_text_biblio_author';
  $handler->display->display_options['filters']['search_text_biblio_author']['group'] = 1;
  $handler->display->display_options['filters']['search_text_biblio_author']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_text_biblio_author']['expose']['operator_id'] = 'search_text_biblio_author_op';
  $handler->display->display_options['filters']['search_text_biblio_author']['expose']['label'] = 'Author';
  $handler->display->display_options['filters']['search_text_biblio_author']['expose']['operator'] = 'search_text_biblio_author_op';
  $handler->display->display_options['filters']['search_text_biblio_author']['expose']['identifier'] = 'search_text_biblio_author';
  $handler->display->display_options['filters']['search_text_biblio_author']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Search text abstract */
  $handler->display->display_options['filters']['search_text_biblio_abstract']['id'] = 'search_text_biblio_abstract';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['field'] = 'search_text_biblio_abstract';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['group'] = 1;
  $handler->display->display_options['filters']['search_text_biblio_abstract']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_text_biblio_abstract']['expose']['operator_id'] = 'search_text_biblio_abstract_op';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['expose']['label'] = 'Enter words in abstract';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['expose']['operator'] = 'search_text_biblio_abstract_op';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['expose']['identifier'] = 'search_text_biblio_abstract';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Search text publish place */
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['id'] = 'search_text_biblio_publish_place';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['field'] = 'search_text_biblio_publish_place';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['group'] = 1;
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['expose']['operator_id'] = 'search_text_biblio_publish_place_op';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['expose']['label'] = 'Publish place';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['expose']['operator'] = 'search_text_biblio_publish_place_op';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['expose']['identifier'] = 'search_text_biblio_publish_place';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Search text publisher */
  $handler->display->display_options['filters']['search_text_biblio_publisher']['id'] = 'search_text_biblio_publisher';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['field'] = 'search_text_biblio_publisher';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['group'] = 1;
  $handler->display->display_options['filters']['search_text_biblio_publisher']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_text_biblio_publisher']['expose']['operator_id'] = 'search_text_biblio_publisher_op';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['expose']['label'] = 'Publisher';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['expose']['operator'] = 'search_text_biblio_publisher_op';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['expose']['identifier'] = 'search_text_biblio_publisher';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Search text zotero tags */
  $handler->display->display_options['filters']['search_text_zotero_tags']['id'] = 'search_text_zotero_tags';
  $handler->display->display_options['filters']['search_text_zotero_tags']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_text_zotero_tags']['field'] = 'search_text_zotero_tags';
  $handler->display->display_options['filters']['search_text_zotero_tags']['group'] = 1;
  $handler->display->display_options['filters']['search_text_zotero_tags']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_text_zotero_tags']['expose']['operator_id'] = 'search_text_zotero_tags_op';
  $handler->display->display_options['filters']['search_text_zotero_tags']['expose']['label'] = 'Tags';
  $handler->display->display_options['filters']['search_text_zotero_tags']['expose']['operator'] = 'search_text_zotero_tags_op';
  $handler->display->display_options['filters']['search_text_zotero_tags']['expose']['identifier'] = 'search_text_zotero_tags';
  $handler->display->display_options['filters']['search_text_zotero_tags']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Publish Year Start */
  $handler->display->display_options['filters']['biblio_year']['id'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_year']['field'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['ui_name'] = 'Publish Year Start';
  $handler->display->display_options['filters']['biblio_year']['operator'] = '>=';
  $handler->display->display_options['filters']['biblio_year']['group'] = 2;
  $handler->display->display_options['filters']['biblio_year']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_year']['expose']['operator_id'] = 'biblio_year_op';
  $handler->display->display_options['filters']['biblio_year']['expose']['operator'] = 'biblio_year_op';
  $handler->display->display_options['filters']['biblio_year']['expose']['identifier'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['biblio_year']['group_info']['label'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['group_info']['identifier'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['biblio_year']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Publish Year End */
  $handler->display->display_options['filters']['biblio_year_1']['id'] = 'biblio_year_1';
  $handler->display->display_options['filters']['biblio_year_1']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_year_1']['field'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year_1']['ui_name'] = 'Publish Year End';
  $handler->display->display_options['filters']['biblio_year_1']['operator'] = '<=';
  $handler->display->display_options['filters']['biblio_year_1']['group'] = 2;
  $handler->display->display_options['filters']['biblio_year_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_year_1']['expose']['operator_id'] = 'biblio_year_1_op';
  $handler->display->display_options['filters']['biblio_year_1']['expose']['operator'] = 'biblio_year_1_op';
  $handler->display->display_options['filters']['biblio_year_1']['expose']['identifier'] = 'biblio_year_1';
  $handler->display->display_options['filters']['biblio_year_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Node ID */
  $handler->display->display_options['filters']['nid']['id'] = 'nid';
  $handler->display->display_options['filters']['nid']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['nid']['field'] = 'nid';
  $handler->display->display_options['path'] = 'sources-search/biblio';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Similar Content';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Indexed Node: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['separator'] = '';
  $handler->display->display_options['fields']['nid']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_year */
  $handler->display->display_options['fields']['biblio_year']['id'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_year']['field'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['label'] = '';
  $handler->display->display_options['fields']['biblio_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['text'] = '([biblio_year])';
  $handler->display->display_options['fields']['biblio_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_year']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['link_to_entity'] = 0;
  /* Field: Indexed Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title] [biblio_year]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 1;
  /* Field: Indexed Node: biblio_authors */
  $handler->display->display_options['fields']['biblio_authors']['id'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_authors']['field'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['label'] = '';
  $handler->display->display_options['fields']['biblio_authors']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_authors']['link_to_entity'] = 0;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Indexed Node: biblio_authors */
  $handler->display->display_options['filters']['biblio_authors']['id'] = 'biblio_authors';
  $handler->display->display_options['filters']['biblio_authors']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_authors']['field'] = 'biblio_authors';
  $handler->display->display_options['filters']['biblio_authors']['group'] = 1;
  $handler->display->display_options['filters']['biblio_authors']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_authors']['expose']['operator_id'] = 'biblio_authors_op';
  $handler->display->display_options['filters']['biblio_authors']['expose']['operator'] = 'biblio_authors_op';
  $handler->display->display_options['filters']['biblio_authors']['expose']['identifier'] = 'biblio_authors';
  $handler->display->display_options['filters']['biblio_authors']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Start Year */
  $handler->display->display_options['filters']['biblio_year']['id'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_year']['field'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['ui_name'] = 'Start Year';
  $handler->display->display_options['filters']['biblio_year']['operator'] = '>=';
  $handler->display->display_options['filters']['biblio_year']['group'] = 1;
  $handler->display->display_options['filters']['biblio_year']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_year']['expose']['operator_id'] = 'biblio_year_op';
  $handler->display->display_options['filters']['biblio_year']['expose']['operator'] = 'biblio_year_op';
  $handler->display->display_options['filters']['biblio_year']['expose']['identifier'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: End Year */
  $handler->display->display_options['filters']['biblio_year_1']['id'] = 'biblio_year_1';
  $handler->display->display_options['filters']['biblio_year_1']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_year_1']['field'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year_1']['ui_name'] = 'End Year';
  $handler->display->display_options['filters']['biblio_year_1']['operator'] = '<=';
  $handler->display->display_options['filters']['biblio_year_1']['group'] = 1;
  $handler->display->display_options['filters']['biblio_year_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_year_1']['expose']['operator_id'] = 'biblio_year_1_op';
  $handler->display->display_options['filters']['biblio_year_1']['expose']['operator'] = 'biblio_year_1_op';
  $handler->display->display_options['filters']['biblio_year_1']['expose']['identifier'] = 'biblio_year_end';
  $handler->display->display_options['filters']['biblio_year_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: biblio_place_published */
  $handler->display->display_options['filters']['biblio_place_published']['id'] = 'biblio_place_published';
  $handler->display->display_options['filters']['biblio_place_published']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_place_published']['field'] = 'biblio_place_published';
  $handler->display->display_options['filters']['biblio_place_published']['group'] = 1;
  $handler->display->display_options['filters']['biblio_place_published']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_place_published']['expose']['operator_id'] = 'biblio_place_published_op';
  $handler->display->display_options['filters']['biblio_place_published']['expose']['operator'] = 'biblio_place_published_op';
  $handler->display->display_options['filters']['biblio_place_published']['expose']['identifier'] = 'biblio_place_published';
  $handler->display->display_options['filters']['biblio_place_published']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: biblio_publisher */
  $handler->display->display_options['filters']['biblio_publisher']['id'] = 'biblio_publisher';
  $handler->display->display_options['filters']['biblio_publisher']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_publisher']['field'] = 'biblio_publisher';
  $handler->display->display_options['filters']['biblio_publisher']['group'] = 1;
  $handler->display->display_options['filters']['biblio_publisher']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_publisher']['expose']['operator_id'] = 'biblio_publisher_op';
  $handler->display->display_options['filters']['biblio_publisher']['expose']['operator'] = 'biblio_publisher_op';
  $handler->display->display_options['filters']['biblio_publisher']['expose']['identifier'] = 'biblio_publisher';
  $handler->display->display_options['filters']['biblio_publisher']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Publication Type */
  $handler->display->display_options['filters']['biblio_publication_type']['id'] = 'biblio_publication_type';
  $handler->display->display_options['filters']['biblio_publication_type']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_publication_type']['field'] = 'biblio_publication_type';
  $handler->display->display_options['filters']['biblio_publication_type']['group'] = 1;
  $handler->display->display_options['filters']['biblio_publication_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['operator_id'] = 'biblio_publication_type_op';
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['operator'] = 'biblio_publication_type_op';
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['identifier'] = 'biblio_publication_type';
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Zotero Tags */
  $handler->display->display_options['filters']['field_zotero_tags']['id'] = 'field_zotero_tags';
  $handler->display->display_options['filters']['field_zotero_tags']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['field_zotero_tags']['field'] = 'field_zotero_tags';
  $handler->display->display_options['filters']['field_zotero_tags']['group'] = 1;
  $handler->display->display_options['filters']['field_zotero_tags']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['operator_id'] = 'field_zotero_tags_op';
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['operator'] = 'field_zotero_tags_op';
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['identifier'] = 'field_zotero_tags';
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );

  /* Display: All Sources Page */
  $handler = $view->new_display('page', 'All Sources Page', 'allpage');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Sources';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'pagerer';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['preset'] = 'shanti_pager';
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Indexed Node: Publication Type */
  $handler->display->display_options['fields']['biblio_publication_type']['id'] = 'biblio_publication_type';
  $handler->display->display_options['fields']['biblio_publication_type']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_publication_type']['field'] = 'biblio_publication_type';
  $handler->display->display_options['fields']['biblio_publication_type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_publication_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_publication_type']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_year */
  $handler->display->display_options['fields']['biblio_year']['id'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_year']['field'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['label'] = '';
  $handler->display->display_options['fields']['biblio_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['text'] = '[biblio_year].';
  $handler->display->display_options['fields']['biblio_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_year']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['empty_zero'] = TRUE;
  /* Field: Indexed Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 1;
  /* Field: Indexed Node: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['separator'] = '';
  $handler->display->display_options['fields']['nid']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_authors */
  $handler->display->display_options['fields']['biblio_authors']['id'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_authors']['field'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['label'] = '';
  $handler->display->display_options['fields']['biblio_authors']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_authors']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_publisher */
  $handler->display->display_options['fields']['biblio_publisher']['id'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_publisher']['field'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['exclude'] = TRUE;
  /* Field: Indexed Node: biblio_abst_e */
  $handler->display->display_options['fields']['biblio_abst_e']['id'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_abst_e']['field'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['label'] = '';
  $handler->display->display_options['fields']['biblio_abst_e']['element_label_colon'] = FALSE;
  /* Field: Indexed Node: Zotero Tags */
  $handler->display->display_options['fields']['field_zotero_tags']['id'] = 'field_zotero_tags';
  $handler->display->display_options['fields']['field_zotero_tags']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_zotero_tags']['field'] = 'field_zotero_tags';
  $handler->display->display_options['fields']['field_zotero_tags']['label'] = '';
  $handler->display->display_options['fields']['field_zotero_tags']['element_label_type'] = 'strong';
  $handler->display->display_options['fields']['field_zotero_tags']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_zotero_tags']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_zotero_tags']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_zotero_tags']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_zotero_tags']['bypass_access'] = 0;
  /* Field: Indexed Node: Zotero Collections */
  $handler->display->display_options['fields']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['fields']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_zotero_collections']['field'] = 'field_zotero_collections';
  $handler->display->display_options['fields']['field_zotero_collections']['label'] = '';
  $handler->display->display_options['fields']['field_zotero_collections']['element_label_type'] = 'strong';
  $handler->display->display_options['fields']['field_zotero_collections']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_zotero_collections']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_zotero_collections']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_zotero_collections']['view_mode'] = 'token';
  $handler->display->display_options['fields']['field_zotero_collections']['bypass_access'] = 0;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Indexed Node: Sorting Stripped Node Title */
  $handler->display->display_options['sorts']['sort_stripped_node_title']['id'] = 'sort_stripped_node_title';
  $handler->display->display_options['sorts']['sort_stripped_node_title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['sort_stripped_node_title']['field'] = 'sort_stripped_node_title';
  $handler->display->display_options['sorts']['sort_stripped_node_title']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['sort_stripped_node_title']['expose']['label'] = 'Title';
  /* Sort criterion: Indexed Node: Sorting Biblio Author */
  $handler->display->display_options['sorts']['sort_biblio_author']['id'] = 'sort_biblio_author';
  $handler->display->display_options['sorts']['sort_biblio_author']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['sort_biblio_author']['field'] = 'sort_biblio_author';
  $handler->display->display_options['sorts']['sort_biblio_author']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['sort_biblio_author']['expose']['label'] = 'Biblio Author';
  /* Sort criterion: Indexed Node: Sorting Custom Publication Year */
  $handler->display->display_options['sorts']['sort_custom_publication_year']['id'] = 'sort_custom_publication_year';
  $handler->display->display_options['sorts']['sort_custom_publication_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['sort_custom_publication_year']['field'] = 'sort_custom_publication_year';
  $handler->display->display_options['sorts']['sort_custom_publication_year']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['sort_custom_publication_year']['expose']['label'] = 'Publication Year';
  $handler->display->display_options['path'] = 'home';

  /* Display: My Sources Page */
  $handler = $view->new_display('page', 'My Sources Page', 'mypage');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My Sources';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'pagerer';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['preset'] = 'shanti_pager';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'teaser';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<p>This page lists all sources that you have created.</p>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = '<span class="count">Displaying @start - @end of @total</span>';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Indexed Node: Publication Type */
  $handler->display->display_options['fields']['biblio_publication_type']['id'] = 'biblio_publication_type';
  $handler->display->display_options['fields']['biblio_publication_type']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_publication_type']['field'] = 'biblio_publication_type';
  $handler->display->display_options['fields']['biblio_publication_type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_publication_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_publication_type']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_year */
  $handler->display->display_options['fields']['biblio_year']['id'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_year']['field'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['label'] = '';
  $handler->display->display_options['fields']['biblio_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['text'] = '[biblio_year].';
  $handler->display->display_options['fields']['biblio_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_year']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['empty_zero'] = TRUE;
  /* Field: Indexed Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 1;
  /* Field: Indexed Node: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['separator'] = '';
  $handler->display->display_options['fields']['nid']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_authors */
  $handler->display->display_options['fields']['biblio_authors']['id'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_authors']['field'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['label'] = '';
  $handler->display->display_options['fields']['biblio_authors']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_authors']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_publisher */
  $handler->display->display_options['fields']['biblio_publisher']['id'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_publisher']['field'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['exclude'] = TRUE;
  /* Field: Indexed Node: biblio_abst_e */
  $handler->display->display_options['fields']['biblio_abst_e']['id'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_abst_e']['field'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['label'] = '';
  $handler->display->display_options['fields']['biblio_abst_e']['element_label_colon'] = FALSE;
  /* Field: Indexed Node: Zotero Tags */
  $handler->display->display_options['fields']['field_zotero_tags']['id'] = 'field_zotero_tags';
  $handler->display->display_options['fields']['field_zotero_tags']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_zotero_tags']['field'] = 'field_zotero_tags';
  $handler->display->display_options['fields']['field_zotero_tags']['label'] = '';
  $handler->display->display_options['fields']['field_zotero_tags']['element_label_type'] = 'strong';
  $handler->display->display_options['fields']['field_zotero_tags']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_zotero_tags']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_zotero_tags']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_zotero_tags']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_zotero_tags']['bypass_access'] = 0;
  /* Field: Indexed Node: Zotero Collections */
  $handler->display->display_options['fields']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['fields']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_zotero_collections']['field'] = 'field_zotero_collections';
  $handler->display->display_options['fields']['field_zotero_collections']['label'] = '';
  $handler->display->display_options['fields']['field_zotero_collections']['element_label_type'] = 'strong';
  $handler->display->display_options['fields']['field_zotero_collections']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_zotero_collections']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_zotero_collections']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_zotero_collections']['view_mode'] = 'token';
  $handler->display->display_options['fields']['field_zotero_collections']['bypass_access'] = 0;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Indexed Node: Sorting Stripped Node Title */
  $handler->display->display_options['sorts']['sort_stripped_node_title']['id'] = 'sort_stripped_node_title';
  $handler->display->display_options['sorts']['sort_stripped_node_title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['sort_stripped_node_title']['field'] = 'sort_stripped_node_title';
  $handler->display->display_options['sorts']['sort_stripped_node_title']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['sort_stripped_node_title']['expose']['label'] = 'Title';
  /* Sort criterion: Indexed Node: Sorting Biblio Author */
  $handler->display->display_options['sorts']['sort_biblio_author']['id'] = 'sort_biblio_author';
  $handler->display->display_options['sorts']['sort_biblio_author']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['sort_biblio_author']['field'] = 'sort_biblio_author';
  $handler->display->display_options['sorts']['sort_biblio_author']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['sort_biblio_author']['expose']['label'] = 'Author';
  /* Sort criterion: Indexed Node: Sorting Custom Publication Year */
  $handler->display->display_options['sorts']['sort_custom_publication_year']['id'] = 'sort_custom_publication_year';
  $handler->display->display_options['sorts']['sort_custom_publication_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['sort_custom_publication_year']['field'] = 'sort_custom_publication_year';
  $handler->display->display_options['sorts']['sort_custom_publication_year']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['sort_custom_publication_year']['expose']['label'] = 'Date Published';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Indexed Node: Author */
  $handler->display->display_options['arguments']['author']['id'] = 'author';
  $handler->display->display_options['arguments']['author']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['arguments']['author']['field'] = 'author';
  $handler->display->display_options['arguments']['author']['default_action'] = 'default';
  $handler->display->display_options['arguments']['author']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['author']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['author']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['author']['not'] = 0;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Indexed Node: Content type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'biblio' => 'biblio',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['path'] = 'mycontent/sources/old';
  $export['biblio_search_api'] = $view;

  return $export;
}
