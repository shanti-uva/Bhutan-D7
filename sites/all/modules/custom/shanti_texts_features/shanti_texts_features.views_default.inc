<?php

/**
 * @file
 * shanti_texts_features.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function shanti_texts_features_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'all_texts';
  $view->description = 'A view to search all texts';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'All Texts';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'All Texts';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'pagerer';
  $handler->display->display_options['pager']['options']['items_per_page'] = '36';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '6, 24, 96';
  $handler->display->display_options['pager']['options']['preset'] = 'shanti_default';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'field_dc_date_orginial_year' => 'field_dc_date_orginial_year',
    'field_dc_date_publication_year' => 'field_dc_date_publication_year',
    'field_book_author' => 'field_book_author',
  );
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = '<div class="view-result-count-info">Displaying @start - @end of @total texts</div>';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Sorry, no texts match your search terms. Please try again.';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['label'] = 'Collection';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['id'] = 'og_membership_related_node_group_1';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['label'] = 'Parent Collection';
  /* Field: Content: Featured image */
  $handler->display->display_options['fields']['field_general_featured_image']['id'] = 'field_general_featured_image';
  $handler->display->display_options['fields']['field_general_featured_image']['table'] = 'field_data_field_general_featured_image';
  $handler->display->display_options['fields']['field_general_featured_image']['field'] = 'field_general_featured_image';
  $handler->display->display_options['fields']['field_general_featured_image']['label'] = '';
  $handler->display->display_options['fields']['field_general_featured_image']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_general_featured_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_general_featured_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_general_featured_image']['settings'] = array(
    'image_style' => 'card_square',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<h3><i class="icon shanticon-texts"></i>[title]</h3>';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'book-view-card-title';
  /* Field: Content: Original publication year */
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['id'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['table'] = 'field_data_field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['field'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['label'] = '';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['alter']['text'] = ' [[field_dc_date_orginial_year]]';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Publication year */
  $handler->display->display_options['fields']['field_dc_date_publication_year']['id'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['table'] = 'field_data_field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['field'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['label'] = '';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['alter']['text'] = '[field_dc_date_publication_year][field_dc_date_orginial_year]';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Author */
  $handler->display->display_options['fields']['field_book_author']['id'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['table'] = 'field_data_field_book_author';
  $handler->display->display_options['fields']['field_book_author']['field'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['label'] = '';
  $handler->display->display_options['fields']['field_book_author']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_book_author']['delta_offset'] = '0';
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_dc_description']['id'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['table'] = 'field_data_field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['field'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['label'] = '';
  $handler->display->display_options['fields']['field_dc_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_description']['element_wrapper_class'] = 'book-view-card-desc';
  $handler->display->display_options['fields']['field_dc_description']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['field_dc_description']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_2']['id'] = 'title_2';
  $handler->display->display_options['fields']['title_2']['table'] = 'node';
  $handler->display->display_options['fields']['title_2']['field'] = 'title';
  $handler->display->display_options['fields']['title_2']['relationship'] = 'og_membership_related_node_group_1';
  $handler->display->display_options['fields']['title_2']['label'] = '';
  $handler->display->display_options['fields']['title_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_2']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title_2']['alter']['text'] = '[title_2] > ';
  $handler->display->display_options['fields']['title_2']['element_label_colon'] = FALSE;
  /* Field: Collection */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Collection';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[title_2][title_1]';
  $handler->display->display_options['fields']['nothing']['element_class'] = 'collection';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'book' => 'book',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Book: Depth */
  $handler->display->display_options['filters']['depth']['id'] = 'depth';
  $handler->display->display_options['filters']['depth']['table'] = 'book_menu_links';
  $handler->display->display_options['filters']['depth']['field'] = 'depth';
  $handler->display->display_options['filters']['depth']['value']['value'] = '1';
  $handler->display->display_options['filters']['depth']['group'] = 1;
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
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
  );
  $handler->display->display_options['filters']['title']['expose']['autocomplete_items'] = '20';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_min_chars'] = '0';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_field'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_dependent'] = 0;
  /* Filter criterion: Content: Author (field_book_author) */
  $handler->display->display_options['filters']['field_book_author_value']['id'] = 'field_book_author_value';
  $handler->display->display_options['filters']['field_book_author_value']['table'] = 'field_data_field_book_author';
  $handler->display->display_options['filters']['field_book_author_value']['field'] = 'field_book_author_value';
  $handler->display->display_options['filters']['field_book_author_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_book_author_value']['group'] = 1;
  $handler->display->display_options['filters']['field_book_author_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_book_author_value']['expose']['operator_id'] = 'field_book_author_value_op';
  $handler->display->display_options['filters']['field_book_author_value']['expose']['label'] = 'Author';
  $handler->display->display_options['filters']['field_book_author_value']['expose']['operator'] = 'field_book_author_value_op';
  $handler->display->display_options['filters']['field_book_author_value']['expose']['identifier'] = 'field_book_author_value';
  $handler->display->display_options['filters']['field_book_author_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_book_author_value']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['field_book_author_value']['expose']['autocomplete_min_chars'] = '0';
  $handler->display->display_options['filters']['field_book_author_value']['expose']['autocomplete_field'] = 'field_book_author';
  $handler->display->display_options['filters']['field_book_author_value']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['field_book_author_value']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['field_book_author_value']['expose']['autocomplete_dependent'] = 0;

  /* Display: All */
  $handler = $view->new_display('page', 'All', 'page_3');
  $handler->display->display_options['path'] = 'alltexts';

  /* Display: By Subject */
  $handler = $view->new_display('page', 'By Subject', 'page_by_subject');
  $handler->display->display_options['display_description'] = 'All Texts by Subject KMap ID';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Sorry, no texts match your search terms. Please try again.

BOO';
  $handler->display->display_options['empty']['area']['format'] = 'php_code';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Subjects (field_kmap_term:id) */
  $handler->display->display_options['arguments']['field_kmap_term_id']['id'] = 'field_kmap_term_id';
  $handler->display->display_options['arguments']['field_kmap_term_id']['table'] = 'field_data_field_kmap_term';
  $handler->display->display_options['arguments']['field_kmap_term_id']['field'] = 'field_kmap_term_id';
  $handler->display->display_options['arguments']['field_kmap_term_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_kmap_term_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_kmap_term_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_kmap_term_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_kmap_term_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_kmap_term_id']['break_phrase'] = TRUE;
  $handler->display->display_options['path'] = 'alltexts/subjects/%';

  /* Display: By Place */
  $handler = $view->new_display('page', 'By Place', 'page_by_place');
  $handler->display->display_options['display_description'] = 'All Texts by Place KMap ID';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Places (field_kmap_places:id) */
  $handler->display->display_options['arguments']['field_kmap_places_id']['id'] = 'field_kmap_places_id';
  $handler->display->display_options['arguments']['field_kmap_places_id']['table'] = 'field_data_field_kmap_places';
  $handler->display->display_options['arguments']['field_kmap_places_id']['field'] = 'field_kmap_places_id';
  $handler->display->display_options['arguments']['field_kmap_places_id']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['field_kmap_places_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_kmap_places_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_kmap_places_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_kmap_places_id']['validate']['type'] = 'php';
  $handler->display->display_options['arguments']['field_kmap_places_id']['validate_options']['code'] = '$parents = shanti_kmaps_fields_get_my_parents(\'field_kmap_places\',$argument);
$new_arg = $argument .\'+\'. implode(\'+\',$parents);
$new_arg = preg_replace("/(subjects|places)-/","",$new_arg);
$handler->argument = $new_arg;
return 1;';
  $handler->display->display_options['arguments']['field_kmap_places_id']['validate']['fail'] = 'empty';
  $handler->display->display_options['arguments']['field_kmap_places_id']['break_phrase'] = TRUE;
  $handler->display->display_options['path'] = 'alltexts/places/%';

  /* Display: By Collection */
  $handler = $view->new_display('page', 'By Collection', 'page_by_collection');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Collection (field_og_collection_ref) */
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['id'] = 'field_og_collection_ref_target_id';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['field'] = 'field_og_collection_ref_target_id';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['break_phrase'] = TRUE;
  $handler->display->display_options['path'] = 'alltexts/collections/%';

  /* Display: My Texts (old) */
  $handler = $view->new_display('page', 'My Texts (old)', 'page_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My Texts (old)';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['path'] = 'mytexts-old';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My Texts';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-test';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Front Page */
  $handler = $view->new_display('panel_pane', 'Front Page', 'panel_pane_1');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<h3><i class="icon shanticon-texts"></i>[title]</h3>';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'book-view-card-title';
  /* Field: Content: Author */
  $handler->display->display_options['fields']['field_book_author']['id'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['table'] = 'field_data_field_book_author';
  $handler->display->display_options['fields']['field_book_author']['field'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['label'] = '';
  $handler->display->display_options['fields']['field_book_author']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_book_author']['delta_offset'] = '0';
  /* Field: Content: Original publication year */
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['id'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['table'] = 'field_data_field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['field'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['label'] = '';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['alter']['text'] = '[[field_dc_date_orginial_year]]';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Publication year */
  $handler->display->display_options['fields']['field_dc_date_publication_year']['id'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['table'] = 'field_data_field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['field'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['label'] = '';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['alter']['text'] = '[field_dc_date_publication_year] [field_dc_date_orginial_year]';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_dc_description']['id'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['table'] = 'field_data_field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['field'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['label'] = '';
  $handler->display->display_options['fields']['field_dc_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_description']['element_wrapper_class'] = 'book-view-card-desc';
  $handler->display->display_options['fields']['field_dc_description']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['field_dc_description']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_2']['id'] = 'title_2';
  $handler->display->display_options['fields']['title_2']['table'] = 'node';
  $handler->display->display_options['fields']['title_2']['field'] = 'title';
  $handler->display->display_options['fields']['title_2']['relationship'] = 'og_membership_related_node_group_1';
  $handler->display->display_options['fields']['title_2']['label'] = '';
  $handler->display->display_options['fields']['title_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_2']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title_2']['alter']['text'] = '[title_2] > ';
  $handler->display->display_options['fields']['title_2']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[title_2][title_1]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['pane_description'] = 'View All Texts';
  $handler->display->display_options['allow']['use_pager'] = 'use_pager';
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'nid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Nid',
    ),
  );
  $handler->display->display_options['inherit_panels_path'] = '1';

  /* Display: Pane by Collection */
  $handler = $view->new_display('panel_pane', 'Pane by Collection', 'panel_pane_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'All Texts by Collection';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<h3><i class="icon shanticon-texts"></i>[title]</h3>';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'book-view-card-title';
  /* Field: Content: Author */
  $handler->display->display_options['fields']['field_book_author']['id'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['table'] = 'field_data_field_book_author';
  $handler->display->display_options['fields']['field_book_author']['field'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['label'] = '';
  $handler->display->display_options['fields']['field_book_author']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_book_author']['delta_offset'] = '0';
  /* Field: Content: Original publication year */
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['id'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['table'] = 'field_data_field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['field'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['label'] = '';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['alter']['text'] = '[[field_dc_date_orginial_year]]';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Publication year */
  $handler->display->display_options['fields']['field_dc_date_publication_year']['id'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['table'] = 'field_data_field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['field'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['label'] = '';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['alter']['text'] = '[field_dc_date_publication_year] [field_dc_date_orginial_year]';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_dc_description']['id'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['table'] = 'field_data_field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['field'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['label'] = '';
  $handler->display->display_options['fields']['field_dc_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_description']['element_wrapper_class'] = 'book-view-card-desc';
  $handler->display->display_options['fields']['field_dc_description']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['field_dc_description']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Collection (field_og_collection_ref) */
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['id'] = 'field_og_collection_ref_target_id';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['field'] = 'field_og_collection_ref_target_id';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['break_phrase'] = TRUE;
  $handler->display->display_options['pane_title'] = 'All Texts by Collection';
  $handler->display->display_options['pane_description'] = 'View All Texts by Colleciton';
  $handler->display->display_options['pane_category']['name'] = 'SHANTI';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['allow']['use_pager'] = 'use_pager';
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 'fields_override';
  $handler->display->display_options['argument_input'] = array(
    'field_og_collection_ref_target_id' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Collection (field_og_collection_ref)',
    ),
  );
  $handler->display->display_options['inherit_panels_path'] = '1';

  /* Display: Pane by Collection 2 */
  $handler = $view->new_display('panel_pane', 'Pane by Collection 2', 'panel_pane_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'All Texts by Collection';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<h3><i class="icon shanticon-texts"></i>[title]</h3>';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'book-view-card-title';
  /* Field: Content: Author */
  $handler->display->display_options['fields']['field_book_author']['id'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['table'] = 'field_data_field_book_author';
  $handler->display->display_options['fields']['field_book_author']['field'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['label'] = '';
  $handler->display->display_options['fields']['field_book_author']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_book_author']['delta_offset'] = '0';
  /* Field: Content: Original publication year */
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['id'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['table'] = 'field_data_field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['field'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['label'] = '';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['alter']['text'] = '[[field_dc_date_orginial_year]]';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Publication year */
  $handler->display->display_options['fields']['field_dc_date_publication_year']['id'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['table'] = 'field_data_field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['field'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['label'] = '';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['alter']['text'] = '[field_dc_date_publication_year] [field_dc_date_orginial_year]';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_dc_description']['id'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['table'] = 'field_data_field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['field'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['label'] = '';
  $handler->display->display_options['fields']['field_dc_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_description']['element_wrapper_class'] = 'book-view-card-desc';
  $handler->display->display_options['fields']['field_dc_description']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['field_dc_description']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_2']['id'] = 'title_2';
  $handler->display->display_options['fields']['title_2']['table'] = 'node';
  $handler->display->display_options['fields']['title_2']['field'] = 'title';
  $handler->display->display_options['fields']['title_2']['relationship'] = 'og_membership_related_node_group_1';
  $handler->display->display_options['fields']['title_2']['label'] = '';
  $handler->display->display_options['fields']['title_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_2']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title_2']['alter']['text'] = '[title_2] > ';
  $handler->display->display_options['fields']['title_2']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[title_2][title_1]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Collection (field_og_collection_ref) */
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['id'] = 'field_og_collection_ref_target_id';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['field'] = 'field_og_collection_ref_target_id';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['break_phrase'] = TRUE;
  $handler->display->display_options['pane_title'] = 'All Texts by Collection + Subs';
  $handler->display->display_options['pane_description'] = 'View All Texts by Colleciton';
  $handler->display->display_options['pane_category']['name'] = 'SHANTI';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['allow']['use_pager'] = 'use_pager';
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 'fields_override';
  $handler->display->display_options['argument_input'] = array(
    'field_og_collection_ref_target_id' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Collection (field_og_collection_ref)',
    ),
  );
  $handler->display->display_options['inherit_panels_path'] = '1';
  $translatables['all_texts'] = array(
    t('Master'),
    t('All Texts'),
    t('more'),
    t('Search'),
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
    t('<div class="view-result-count-info">Displaying @start - @end of @total texts</div>'),
    t('Sorry, no texts match your search terms. Please try again.'),
    t('Collection'),
    t('Parent Collection'),
    t('<h3><i class="icon shanticon-texts"></i>[title]</h3>'),
    t(' [[field_dc_date_orginial_year]]'),
    t('[field_dc_date_publication_year][field_dc_date_orginial_year]'),
    t('[title_2] > '),
    t('[title_2][title_1]'),
    t('Title'),
    t('Author'),
    t('All'),
    t('By Subject'),
    t('All Texts by Subject KMap ID'),
    t('Sorry, no texts match your search terms. Please try again.

BOO'),
    t('By Place'),
    t('All Texts by Place KMap ID'),
    t('By Collection'),
    t('My Texts (old)'),
    t('Front Page'),
    t('[[field_dc_date_orginial_year]]'),
    t('[field_dc_date_publication_year] [field_dc_date_orginial_year]'),
    t('View All Texts'),
    t('View panes'),
    t('Pane by Collection'),
    t('All Texts by Collection'),
    t('Group node from OG membership'),
    t('View All Texts by Colleciton'),
    t('SHANTI'),
    t('Pane by Collection 2'),
    t('All Texts by Collection + Subs'),
  );
  $export['all_texts'] = $view;

  $view = new view();
  $view->name = 'all_texts_open';
  $view->description = 'A view to search all texts';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'All Texts Open';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'All Texts';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'pagerer';
  $handler->display->display_options['pager']['options']['items_per_page'] = '36';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '6, 24, 96';
  $handler->display->display_options['pager']['options']['preset'] = 'shanti_default';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'field_dc_date_orginial_year' => 'field_dc_date_orginial_year',
    'field_dc_date_publication_year' => 'field_dc_date_publication_year',
    'field_book_author' => 'field_book_author',
  );
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = '<div class="view-result-count-info">Displaying @start - @end of @total texts</div>';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Sorry, no texts match your search terms. Please try again.';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Field: Content: Featured image */
  $handler->display->display_options['fields']['field_general_featured_image']['id'] = 'field_general_featured_image';
  $handler->display->display_options['fields']['field_general_featured_image']['table'] = 'field_data_field_general_featured_image';
  $handler->display->display_options['fields']['field_general_featured_image']['field'] = 'field_general_featured_image';
  $handler->display->display_options['fields']['field_general_featured_image']['label'] = '';
  $handler->display->display_options['fields']['field_general_featured_image']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_general_featured_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_general_featured_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_general_featured_image']['settings'] = array(
    'image_style' => 'card_square',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<h3><i class="icon shanticon-texts"></i>[title]</h3>';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'book-view-card-title';
  /* Field: Content: Original publication year */
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['id'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['table'] = 'field_data_field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['field'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['label'] = '';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['alter']['text'] = ' [[field_dc_date_orginial_year]]';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Publication year */
  $handler->display->display_options['fields']['field_dc_date_publication_year']['id'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['table'] = 'field_data_field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['field'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['label'] = '';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['alter']['text'] = '[field_dc_date_publication_year][field_dc_date_orginial_year]';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Author */
  $handler->display->display_options['fields']['field_book_author']['id'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['table'] = 'field_data_field_book_author';
  $handler->display->display_options['fields']['field_book_author']['field'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['label'] = '';
  $handler->display->display_options['fields']['field_book_author']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_book_author']['delta_offset'] = '0';
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_dc_description']['id'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['table'] = 'field_data_field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['field'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['label'] = '';
  $handler->display->display_options['fields']['field_dc_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_description']['element_wrapper_class'] = 'book-view-card-desc';
  $handler->display->display_options['fields']['field_dc_description']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['field_dc_description']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: Collection */
  $handler->display->display_options['fields']['field_og_collection_ref']['id'] = 'field_og_collection_ref';
  $handler->display->display_options['fields']['field_og_collection_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['field_og_collection_ref']['field'] = 'field_og_collection_ref';
  $handler->display->display_options['fields']['field_og_collection_ref']['label'] = '';
  $handler->display->display_options['fields']['field_og_collection_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_og_collection_ref']['settings'] = array(
    'link' => 0,
  );
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'book' => 'book',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Book: Depth */
  $handler->display->display_options['filters']['depth']['id'] = 'depth';
  $handler->display->display_options['filters']['depth']['table'] = 'book_menu_links';
  $handler->display->display_options['filters']['depth']['field'] = 'depth';
  $handler->display->display_options['filters']['depth']['value']['value'] = '1';
  $handler->display->display_options['filters']['depth']['group'] = 1;
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
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
  );
  $handler->display->display_options['filters']['title']['expose']['autocomplete_items'] = '20';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_min_chars'] = '0';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_field'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_dependent'] = 0;
  /* Filter criterion: Content: Author (field_book_author) */
  $handler->display->display_options['filters']['field_book_author_value']['id'] = 'field_book_author_value';
  $handler->display->display_options['filters']['field_book_author_value']['table'] = 'field_data_field_book_author';
  $handler->display->display_options['filters']['field_book_author_value']['field'] = 'field_book_author_value';
  $handler->display->display_options['filters']['field_book_author_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_book_author_value']['group'] = 1;
  $handler->display->display_options['filters']['field_book_author_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_book_author_value']['expose']['operator_id'] = 'field_book_author_value_op';
  $handler->display->display_options['filters']['field_book_author_value']['expose']['label'] = 'Author';
  $handler->display->display_options['filters']['field_book_author_value']['expose']['operator'] = 'field_book_author_value_op';
  $handler->display->display_options['filters']['field_book_author_value']['expose']['identifier'] = 'field_book_author_value';
  $handler->display->display_options['filters']['field_book_author_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_book_author_value']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['field_book_author_value']['expose']['autocomplete_min_chars'] = '0';
  $handler->display->display_options['filters']['field_book_author_value']['expose']['autocomplete_field'] = 'field_book_author';
  $handler->display->display_options['filters']['field_book_author_value']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['field_book_author_value']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['field_book_author_value']['expose']['autocomplete_dependent'] = 0;

  /* Display: All */
  $handler = $view->new_display('page', 'All', 'page_3');
  $handler->display->display_options['path'] = 'alltexts_open';

  /* Display: By Subject */
  $handler = $view->new_display('page', 'By Subject', 'page_1');
  $handler->display->display_options['display_description'] = 'All Texts by Subject KMap ID';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['path'] = 'alltexts_open/subjects/%';

  /* Display: By Place */
  $handler = $view->new_display('page', 'By Place', 'page_2');
  $handler->display->display_options['display_description'] = 'All Texts by Place KMap ID';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Places (field_kmap_places:id) */
  $handler->display->display_options['arguments']['field_kmap_places_id']['id'] = 'field_kmap_places_id';
  $handler->display->display_options['arguments']['field_kmap_places_id']['table'] = 'field_data_field_kmap_places';
  $handler->display->display_options['arguments']['field_kmap_places_id']['field'] = 'field_kmap_places_id';
  $handler->display->display_options['arguments']['field_kmap_places_id']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['field_kmap_places_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_kmap_places_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_kmap_places_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_kmap_places_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_kmap_places_id']['validate']['type'] = 'php';
  $handler->display->display_options['arguments']['field_kmap_places_id']['validate_options']['code'] = '$parents = shanti_kmaps_fields_get_my_parents(\'field_kmap_places\',$argument);
$new_arg = $argument .\'+\'. implode(\'+\',$parents);
$new_arg = preg_replace("/(subjects|places)-/","",$new_arg);
$handler->argument = $new_arg;
return 1;';
  $handler->display->display_options['arguments']['field_kmap_places_id']['validate']['fail'] = 'empty';
  $handler->display->display_options['arguments']['field_kmap_places_id']['break_phrase'] = TRUE;
  $handler->display->display_options['path'] = 'alltexts_open/places/%';

  /* Display: By Collection */
  $handler = $view->new_display('page', 'By Collection', 'page_by_collection');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Collection (field_og_collection_ref) */
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['id'] = 'field_og_collection_ref_target_id';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['field'] = 'field_og_collection_ref_target_id';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['break_phrase'] = TRUE;
  $handler->display->display_options['path'] = 'alltexts_open/collections/%';

  /* Display: Front Page */
  $handler = $view->new_display('panel_pane', 'Front Page', 'panel_pane_1');
  $handler->display->display_options['defaults']['cache'] = FALSE;
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '21600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '21600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<h3><i class="icon shanticon-texts"></i>[title]</h3>';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'book-view-card-title';
  /* Field: Content: Author */
  $handler->display->display_options['fields']['field_book_author']['id'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['table'] = 'field_data_field_book_author';
  $handler->display->display_options['fields']['field_book_author']['field'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['label'] = '';
  $handler->display->display_options['fields']['field_book_author']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_book_author']['delta_offset'] = '0';
  /* Field: Content: Original publication year */
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['id'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['table'] = 'field_data_field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['field'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['label'] = '';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['alter']['text'] = '[[field_dc_date_orginial_year]]';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Publication year */
  $handler->display->display_options['fields']['field_dc_date_publication_year']['id'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['table'] = 'field_data_field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['field'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['label'] = '';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['alter']['text'] = '[field_dc_date_publication_year] [field_dc_date_orginial_year]';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_dc_description']['id'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['table'] = 'field_data_field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['field'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['label'] = '';
  $handler->display->display_options['fields']['field_dc_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_description']['element_wrapper_class'] = 'book-view-card-desc';
  $handler->display->display_options['fields']['field_dc_description']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['field_dc_description']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: Collection */
  $handler->display->display_options['fields']['field_og_collection_ref']['id'] = 'field_og_collection_ref';
  $handler->display->display_options['fields']['field_og_collection_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['field_og_collection_ref']['field'] = 'field_og_collection_ref';
  $handler->display->display_options['fields']['field_og_collection_ref']['label'] = '';
  $handler->display->display_options['fields']['field_og_collection_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_og_collection_ref']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['pane_description'] = 'View All Texts';
  $handler->display->display_options['allow']['use_pager'] = 'use_pager';
  $handler->display->display_options['allow']['items_per_page'] = 'items_per_page';
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'nid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Nid',
    ),
  );
  $handler->display->display_options['inherit_panels_path'] = '1';

  /* Display: My Texts New */
  $handler = $view->new_display('page', 'My Texts New', 'page_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My Texts';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Featured image */
  $handler->display->display_options['fields']['field_general_featured_image']['id'] = 'field_general_featured_image';
  $handler->display->display_options['fields']['field_general_featured_image']['table'] = 'field_data_field_general_featured_image';
  $handler->display->display_options['fields']['field_general_featured_image']['field'] = 'field_general_featured_image';
  $handler->display->display_options['fields']['field_general_featured_image']['label'] = '';
  $handler->display->display_options['fields']['field_general_featured_image']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_general_featured_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_general_featured_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_general_featured_image']['settings'] = array(
    'image_style' => 'card_square',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<h3><i class="icon shanticon-texts"></i>[title]</h3>';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'book-view-card-title';
  /* Field: Content: Original publication year */
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['id'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['table'] = 'field_data_field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['field'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['label'] = '';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['alter']['text'] = ' [[field_dc_date_orginial_year]]';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Publication year */
  $handler->display->display_options['fields']['field_dc_date_publication_year']['id'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['table'] = 'field_data_field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['field'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['label'] = '';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['alter']['text'] = '[field_dc_date_publication_year][field_dc_date_orginial_year]';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Author */
  $handler->display->display_options['fields']['field_book_author']['id'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['table'] = 'field_data_field_book_author';
  $handler->display->display_options['fields']['field_book_author']['field'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['label'] = '';
  $handler->display->display_options['fields']['field_book_author']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_book_author']['delta_offset'] = '0';
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_dc_description']['id'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['table'] = 'field_data_field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['field'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['label'] = '';
  $handler->display->display_options['fields']['field_dc_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_description']['element_wrapper_class'] = 'book-view-card-desc';
  $handler->display->display_options['fields']['field_dc_description']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['field_dc_description']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: Collection */
  $handler->display->display_options['fields']['field_og_collection_ref']['id'] = 'field_og_collection_ref';
  $handler->display->display_options['fields']['field_og_collection_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['field_og_collection_ref']['field'] = 'field_og_collection_ref';
  $handler->display->display_options['fields']['field_og_collection_ref']['label'] = '';
  $handler->display->display_options['fields']['field_og_collection_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_og_collection_ref']['settings'] = array(
    'bypass_access' => 0,
    'link' => 1,
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['path'] = 'mytexts';
  $translatables['all_texts_open'] = array(
    t('Master'),
    t('All Texts'),
    t('more'),
    t('Search'),
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
    t('<div class="view-result-count-info">Displaying @start - @end of @total texts</div>'),
    t('Sorry, no texts match your search terms. Please try again.'),
    t('<h3><i class="icon shanticon-texts"></i>[title]</h3>'),
    t(' [[field_dc_date_orginial_year]]'),
    t('[field_dc_date_publication_year][field_dc_date_orginial_year]'),
    t('Title'),
    t('Author'),
    t('All'),
    t('By Subject'),
    t('All Texts by Subject KMap ID'),
    t('By Place'),
    t('All Texts by Place KMap ID'),
    t('By Collection'),
    t('Front Page'),
    t('[[field_dc_date_orginial_year]]'),
    t('[field_dc_date_publication_year] [field_dc_date_orginial_year]'),
    t('View All Texts'),
    t('View panes'),
    t('My Texts New'),
    t('My Texts'),
  );
  $export['all_texts_open'] = $view;

  $view = new view();
  $view->name = 'single_text_body';
  $view->description = '';
  $view->tag = 'SHANTI Texts';
  $view->base_table = 'node';
  $view->human_name = 'Single Text Body';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Relationship: Book: Top level book */
  $handler->display->display_options['relationships']['bid']['id'] = 'bid';
  $handler->display->display_options['relationships']['bid']['table'] = 'book';
  $handler->display->display_options['relationships']['bid']['field'] = 'bid';
  $handler->display->display_options['relationships']['bid']['required'] = TRUE;
  /* Field: BID */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['relationship'] = 'bid';
  $handler->display->display_options['fields']['nid_1']['ui_name'] = 'BID';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid_1']['element_default_classes'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = FALSE;
  /* Field: Book: Depth */
  $handler->display->display_options['fields']['depth']['id'] = 'depth';
  $handler->display->display_options['fields']['depth']['table'] = 'book_menu_links';
  $handler->display->display_options['fields']['depth']['field'] = 'depth';
  $handler->display->display_options['fields']['depth']['label'] = '';
  $handler->display->display_options['fields']['depth']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['depth']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['depth']['separator'] = '';
  /* Field: Book: Weight */
  $handler->display->display_options['fields']['weight']['id'] = 'weight';
  $handler->display->display_options['fields']['weight']['table'] = 'book_menu_links';
  $handler->display->display_options['fields']['weight']['field'] = 'weight';
  $handler->display->display_options['fields']['weight']['label'] = '';
  $handler->display->display_options['fields']['weight']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['weight']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['weight']['separator'] = '';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['text'] = '<a name="shanti-text-[nid]"></a>
<header class="shanti-text-header depth-[depth]"><h[depth]>[title]</h[depth]></header>';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Collection NID */
  $handler->display->display_options['fields']['field_og_collection_ref_1']['id'] = 'field_og_collection_ref_1';
  $handler->display->display_options['fields']['field_og_collection_ref_1']['table'] = 'og_membership';
  $handler->display->display_options['fields']['field_og_collection_ref_1']['field'] = 'field_og_collection_ref';
  $handler->display->display_options['fields']['field_og_collection_ref_1']['ui_name'] = 'Collection NID';
  $handler->display->display_options['fields']['field_og_collection_ref_1']['label'] = '';
  $handler->display->display_options['fields']['field_og_collection_ref_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_og_collection_ref_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_og_collection_ref_1']['type'] = 'entityreference_entity_id';
  $handler->display->display_options['fields']['field_og_collection_ref_1']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Content */
  $handler->display->display_options['fields']['field_book_content']['id'] = 'field_book_content';
  $handler->display->display_options['fields']['field_book_content']['table'] = 'field_data_field_book_content';
  $handler->display->display_options['fields']['field_book_content']['field'] = 'field_book_content';
  $handler->display->display_options['fields']['field_book_content']['label'] = '';
  $handler->display->display_options['fields']['field_book_content']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_book_content']['element_default_classes'] = FALSE;
  /* Field: Content: MLID */
  $handler->display->display_options['fields']['field_book_mlid']['id'] = 'field_book_mlid';
  $handler->display->display_options['fields']['field_book_mlid']['table'] = 'field_data_field_book_mlid';
  $handler->display->display_options['fields']['field_book_mlid']['field'] = 'field_book_mlid';
  $handler->display->display_options['fields']['field_book_mlid']['label'] = '';
  $handler->display->display_options['fields']['field_book_mlid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_book_mlid']['element_default_classes'] = FALSE;
  /* Field: Content: Language */
  $handler->display->display_options['fields']['field_dc_lang_code']['id'] = 'field_dc_lang_code';
  $handler->display->display_options['fields']['field_dc_lang_code']['table'] = 'field_data_field_dc_lang_code';
  $handler->display->display_options['fields']['field_dc_lang_code']['field'] = 'field_dc_lang_code';
  $handler->display->display_options['fields']['field_dc_lang_code']['label'] = '';
  $handler->display->display_options['fields']['field_dc_lang_code']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dc_lang_code']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_lang_code']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_dc_lang_code']['type'] = 'list_key';
  /* Field: Display */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Display';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="shanti-texts-section">
<a name="shanti-texts-[nid]"></a>
<div id="shanti-texts-[nid]" class="shanti-texts-section-title text-level-[depth]">[title]</div>
<div class="shanti-texts-section-controls">
<a class="label label-default" href="/node/add/book?parent=[field_book_mlid]&field_og_collection_ref=[field_og_collection_ref_1]">Insert</a>
</div>
<div class="shanti-texts-section-content">
[field_book_content]
</div>
</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Content: Places */
  $handler->display->display_options['fields']['field_kmap_places']['id'] = 'field_kmap_places';
  $handler->display->display_options['fields']['field_kmap_places']['table'] = 'field_data_field_kmap_places';
  $handler->display->display_options['fields']['field_kmap_places']['field'] = 'field_kmap_places';
  $handler->display->display_options['fields']['field_kmap_places']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_kmap_places']['click_sort_column'] = 'raw';
  $handler->display->display_options['fields']['field_kmap_places']['type'] = 'kmap_popover_formatter';
  $handler->display->display_options['fields']['field_kmap_places']['settings'] = array(
    'target' => '_blank',
  );
  $handler->display->display_options['fields']['field_kmap_places']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_kmap_places']['separator'] = ' ';
  /* Field: Content: Subjects */
  $handler->display->display_options['fields']['field_kmap_term']['id'] = 'field_kmap_term';
  $handler->display->display_options['fields']['field_kmap_term']['table'] = 'field_data_field_kmap_term';
  $handler->display->display_options['fields']['field_kmap_term']['field'] = 'field_kmap_term';
  $handler->display->display_options['fields']['field_kmap_term']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_kmap_term']['click_sort_column'] = 'raw';
  $handler->display->display_options['fields']['field_kmap_term']['type'] = 'kmap_popover_formatter';
  $handler->display->display_options['fields']['field_kmap_term']['settings'] = array(
    'target' => '_blank',
  );
  $handler->display->display_options['fields']['field_kmap_term']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_kmap_term']['separator'] = ' ';
  /* Sort criterion: Book: Hierarchy */
  $handler->display->display_options['sorts']['p']['id'] = 'p';
  $handler->display->display_options['sorts']['p']['table'] = 'book_menu_links';
  $handler->display->display_options['sorts']['p']['field'] = 'p';
  $handler->display->display_options['sorts']['p']['sort_within_level'] = 1;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'bid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'book' => 'book',
  );

  /* Display: Default */
  $handler = $view->new_display('panel_pane', 'Default', 'panel_pane_default');
  $handler->display->display_options['pane_category']['name'] = 'SHANTI Texts';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['argument_input'] = array(
    'nid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Nid',
    ),
  );
  $translatables['single_text_body'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Book'),
    t('.'),
    t('<a name="shanti-text-[nid]"></a>
<header class="shanti-text-header depth-[depth]"><h[depth]>[title]</h[depth]></header>'),
    t('<div class="shanti-texts-section">
<a name="shanti-texts-[nid]"></a>
<div id="shanti-texts-[nid]" class="shanti-texts-section-title text-level-[depth]">[title]</div>
<div class="shanti-texts-section-controls">
<a class="label label-default" href="/node/add/book?parent=[field_book_mlid]&field_og_collection_ref=[field_og_collection_ref_1]">Insert</a>
</div>
<div class="shanti-texts-section-content">
[field_book_content]
</div>
</div>'),
    t('Places'),
    t('Subjects'),
    t('All'),
    t('Default'),
    t('SHANTI Texts'),
  );
  $export['single_text_body'] = $view;

  $view = new view();
  $view->name = 'single_text_kmaps';
  $view->description = 'View of all the kmap terms associated with a text';
  $view->tag = 'SHANTI Texts';
  $view->base_table = 'node';
  $view->human_name = 'Single Text KMaps';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Relationship: Book: Top level book */
  $handler->display->display_options['relationships']['bid']['id'] = 'bid';
  $handler->display->display_options['relationships']['bid']['table'] = 'book';
  $handler->display->display_options['relationships']['bid']['field'] = 'bid';
  $handler->display->display_options['relationships']['bid']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Places */
  $handler->display->display_options['fields']['field_kmap_places']['id'] = 'field_kmap_places';
  $handler->display->display_options['fields']['field_kmap_places']['table'] = 'field_data_field_kmap_places';
  $handler->display->display_options['fields']['field_kmap_places']['field'] = 'field_kmap_places';
  $handler->display->display_options['fields']['field_kmap_places']['alter']['text'] = 'Places in [title]: [field_kmap_places] ';
  $handler->display->display_options['fields']['field_kmap_places']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_kmap_places']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_kmap_places']['click_sort_column'] = 'raw';
  $handler->display->display_options['fields']['field_kmap_places']['type'] = 'kmap_popover_formatter';
  $handler->display->display_options['fields']['field_kmap_places']['settings'] = array(
    'target' => '_blank',
  );
  $handler->display->display_options['fields']['field_kmap_places']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_kmap_places']['multi_type'] = 'ul';
  /* Field: Content: Subjects */
  $handler->display->display_options['fields']['field_kmap_term']['id'] = 'field_kmap_term';
  $handler->display->display_options['fields']['field_kmap_term']['table'] = 'field_data_field_kmap_term';
  $handler->display->display_options['fields']['field_kmap_term']['field'] = 'field_kmap_term';
  $handler->display->display_options['fields']['field_kmap_term']['alter']['text'] = 'Subjects in [title]: [field_kmap_term]';
  $handler->display->display_options['fields']['field_kmap_term']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_kmap_term']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_kmap_term']['click_sort_column'] = 'raw';
  $handler->display->display_options['fields']['field_kmap_term']['type'] = 'kmap_popover_formatter';
  $handler->display->display_options['fields']['field_kmap_term']['settings'] = array(
    'target' => '_blank',
  );
  $handler->display->display_options['fields']['field_kmap_term']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_kmap_term']['multi_type'] = 'ul';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'bid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'book' => 'book',
  );

  /* Display: Default */
  $handler = $view->new_display('panel_pane', 'Default', 'panel_pane_default');
  $translatables['single_text_kmaps'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
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
    t('Book'),
    t('Places'),
    t('Places in [title]: [field_kmap_places] '),
    t('Subjects'),
    t('Subjects in [title]: [field_kmap_term]'),
    t('All'),
    t('Default'),
    t('View panes'),
  );
  $export['single_text_kmaps'] = $view;

  $view = new view();
  $view->name = 'single_text_meta';
  $view->description = '';
  $view->tag = 'SHANTI Texts';
  $view->base_table = 'node';
  $view->human_name = 'Single Text Meta';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_og_collection_ref_target_id']['id'] = 'field_og_collection_ref_target_id';
  $handler->display->display_options['relationships']['field_og_collection_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['field_og_collection_ref_target_id']['field'] = 'field_og_collection_ref_target_id';
  $handler->display->display_options['relationships']['field_og_collection_ref_target_id']['label'] = 'Collection Node';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Collection */
  $handler->display->display_options['fields']['field_og_collection_ref']['id'] = 'field_og_collection_ref';
  $handler->display->display_options['fields']['field_og_collection_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['field_og_collection_ref']['field'] = 'field_og_collection_ref';
  $handler->display->display_options['fields']['field_og_collection_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_og_collection_ref']['settings'] = array(
    'link' => 1,
  );
  /* Field: Content: Group visibility */
  $handler->display->display_options['fields']['group_access']['id'] = 'group_access';
  $handler->display->display_options['fields']['group_access']['table'] = 'field_data_group_access';
  $handler->display->display_options['fields']['group_access']['field'] = 'group_access';
  $handler->display->display_options['fields']['group_access']['relationship'] = 'field_og_collection_ref_target_id';
  $handler->display->display_options['fields']['group_access']['label'] = '';
  $handler->display->display_options['fields']['group_access']['exclude'] = TRUE;
  $handler->display->display_options['fields']['group_access']['element_label_colon'] = FALSE;
  /* Field: Content: Visibility */
  $handler->display->display_options['fields']['group_content_access_1']['id'] = 'group_content_access_1';
  $handler->display->display_options['fields']['group_content_access_1']['table'] = 'field_data_group_content_access';
  $handler->display->display_options['fields']['group_content_access_1']['field'] = 'group_content_access';
  $handler->display->display_options['fields']['group_content_access_1']['label'] = '';
  $handler->display->display_options['fields']['group_content_access_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['group_content_access_1']['element_label_colon'] = FALSE;
  /* Field: Content: Visibility */
  $handler->display->display_options['fields']['group_content_access']['id'] = 'group_content_access';
  $handler->display->display_options['fields']['group_content_access']['table'] = 'field_data_group_content_access';
  $handler->display->display_options['fields']['group_content_access']['field'] = 'group_content_access';
  $handler->display->display_options['fields']['group_content_access']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['group_content_access']['alter']['text'] = '[group_content_access_1]';
  $handler->display->display_options['fields']['group_content_access']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['group_content_access']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['group_content_access']['empty'] = '[group_access] (default)';
  $handler->display->display_options['fields']['group_content_access']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['group_content_access']['type'] = 'list_key';
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_dc_description']['id'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['table'] = 'field_data_field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['field'] = 'field_dc_description';
  $handler->display->display_options['fields']['field_dc_description']['label'] = '';
  $handler->display->display_options['fields']['field_dc_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_description']['hide_empty'] = TRUE;
  /* Field: Content: Author */
  $handler->display->display_options['fields']['field_book_author']['id'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['table'] = 'field_data_field_book_author';
  $handler->display->display_options['fields']['field_book_author']['field'] = 'field_book_author';
  $handler->display->display_options['fields']['field_book_author']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_book_author']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_book_author']['delta_offset'] = '0';
  /* Field: Content: Editor */
  $handler->display->display_options['fields']['field_book_editor']['id'] = 'field_book_editor';
  $handler->display->display_options['fields']['field_book_editor']['table'] = 'field_data_field_book_editor';
  $handler->display->display_options['fields']['field_book_editor']['field'] = 'field_book_editor';
  $handler->display->display_options['fields']['field_book_editor']['alter']['text'] = '<tr><td>Editor</td><td>[field_book_editor] </td></tr>';
  $handler->display->display_options['fields']['field_book_editor']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_book_editor']['hide_empty'] = TRUE;
  /* Field: Content: Translator */
  $handler->display->display_options['fields']['field_book_translator']['id'] = 'field_book_translator';
  $handler->display->display_options['fields']['field_book_translator']['table'] = 'field_data_field_book_translator';
  $handler->display->display_options['fields']['field_book_translator']['field'] = 'field_book_translator';
  $handler->display->display_options['fields']['field_book_translator']['alter']['text'] = '<tr><td>Translator</td><td>[field_book_translator] </td></tr>';
  $handler->display->display_options['fields']['field_book_translator']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_book_translator']['hide_empty'] = TRUE;
  /* Field: Content: Publication year */
  $handler->display->display_options['fields']['field_dc_date_publication_year']['id'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['table'] = 'field_data_field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['field'] = 'field_dc_date_publication_year';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['label'] = 'Year published';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['alter']['text'] = '<tr><td>Year</td><td>[field_dc_date_publication_year]</td></tr>';
  $handler->display->display_options['fields']['field_dc_date_publication_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_publication_year']['settings'] = array(
    'format_type' => 'year_only',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Original publication year */
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['id'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['table'] = 'field_data_field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['field'] = 'field_dc_date_orginial_year';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['label'] = 'Original year published';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['alter']['text'] = '<tr><td>Year</td><td>[field_dc_date_publication_year] [field_dc_date_orginial_year]</td></tr>';
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_dc_date_orginial_year']['settings'] = array(
    'format_type' => 'year_only',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Language */
  $handler->display->display_options['fields']['field_language_kmap']['id'] = 'field_language_kmap';
  $handler->display->display_options['fields']['field_language_kmap']['table'] = 'field_data_field_language_kmap';
  $handler->display->display_options['fields']['field_language_kmap']['field'] = 'field_language_kmap';
  $handler->display->display_options['fields']['field_language_kmap']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_language_kmap']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_language_kmap']['click_sort_column'] = 'raw';
  $handler->display->display_options['fields']['field_language_kmap']['type'] = 'kmap_popover_formatter';
  $handler->display->display_options['fields']['field_language_kmap']['settings'] = array(
    'target' => '_blank',
  );
  $handler->display->display_options['fields']['field_language_kmap']['delta_offset'] = '0';
  /* Field: Content: Subjects */
  $handler->display->display_options['fields']['field_kmap_term']['id'] = 'field_kmap_term';
  $handler->display->display_options['fields']['field_kmap_term']['table'] = 'field_data_field_kmap_term';
  $handler->display->display_options['fields']['field_kmap_term']['field'] = 'field_kmap_term';
  $handler->display->display_options['fields']['field_kmap_term']['alter']['text'] = '<tr><td>Subjects</td><td>[field_kmap_term]</td></tr>';
  $handler->display->display_options['fields']['field_kmap_term']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_kmap_term']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_kmap_term']['click_sort_column'] = 'raw';
  $handler->display->display_options['fields']['field_kmap_term']['type'] = 'kmap_popover_formatter';
  $handler->display->display_options['fields']['field_kmap_term']['settings'] = array(
    'target' => '_blank',
  );
  $handler->display->display_options['fields']['field_kmap_term']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_kmap_term']['multi_type'] = 'ul';
  $handler->display->display_options['fields']['field_kmap_term']['separator'] = '';
  /* Field: Content: Places */
  $handler->display->display_options['fields']['field_kmap_places']['id'] = 'field_kmap_places';
  $handler->display->display_options['fields']['field_kmap_places']['table'] = 'field_data_field_kmap_places';
  $handler->display->display_options['fields']['field_kmap_places']['field'] = 'field_kmap_places';
  $handler->display->display_options['fields']['field_kmap_places']['alter']['text'] = '<tr>
<td>Places</td>
<td>[field_kmap_places]</td>
</tr>';
  $handler->display->display_options['fields']['field_kmap_places']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_kmap_places']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_kmap_places']['click_sort_column'] = 'raw';
  $handler->display->display_options['fields']['field_kmap_places']['type'] = 'kmap_popover_formatter';
  $handler->display->display_options['fields']['field_kmap_places']['settings'] = array(
    'target' => '_blank',
  );
  $handler->display->display_options['fields']['field_kmap_places']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_kmap_places']['multi_type'] = 'ul';
  $handler->display->display_options['fields']['field_kmap_places']['separator'] = ' ';
  /* Field: Content: Terms */
  $handler->display->display_options['fields']['field_kmap_terms']['id'] = 'field_kmap_terms';
  $handler->display->display_options['fields']['field_kmap_terms']['table'] = 'field_data_field_kmap_terms';
  $handler->display->display_options['fields']['field_kmap_terms']['field'] = 'field_kmap_terms';
  $handler->display->display_options['fields']['field_kmap_terms']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_kmap_terms']['click_sort_column'] = 'raw';
  $handler->display->display_options['fields']['field_kmap_terms']['type'] = 'kmap_popover_formatter';
  $handler->display->display_options['fields']['field_kmap_terms']['settings'] = array(
    'target' => '_blank',
  );
  $handler->display->display_options['fields']['field_kmap_terms']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_kmap_terms']['multi_type'] = 'ul';
  $handler->display->display_options['fields']['field_kmap_terms']['separator'] = ' ';
  /* Field: Content: Rights */
  $handler->display->display_options['fields']['field_dc_rights_general']['id'] = 'field_dc_rights_general';
  $handler->display->display_options['fields']['field_dc_rights_general']['table'] = 'field_data_field_dc_rights_general';
  $handler->display->display_options['fields']['field_dc_rights_general']['field'] = 'field_dc_rights_general';
  $handler->display->display_options['fields']['field_dc_rights_general']['alter']['text'] = '<tr>
<td>Rights</td>
<td>[field_dc_rights_general]</td>
</tr>';
  $handler->display->display_options['fields']['field_dc_rights_general']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_rights_general']['hide_empty'] = TRUE;
  /* Field: Content: Rights (CC) */
  $handler->display->display_options['fields']['field_dc_rights_creativecommons']['id'] = 'field_dc_rights_creativecommons';
  $handler->display->display_options['fields']['field_dc_rights_creativecommons']['table'] = 'field_data_field_dc_rights_creativecommons';
  $handler->display->display_options['fields']['field_dc_rights_creativecommons']['field'] = 'field_dc_rights_creativecommons';
  $handler->display->display_options['fields']['field_dc_rights_creativecommons']['label'] = '';
  $handler->display->display_options['fields']['field_dc_rights_creativecommons']['alter']['text'] = '<tr>
<td colspan="2">[field_dc_rights_general]</td>
</tr>';
  $handler->display->display_options['fields']['field_dc_rights_creativecommons']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dc_rights_creativecommons']['hide_empty'] = TRUE;
  /* Field: Content: PDF Version */
  $handler->display->display_options['fields']['field_pdf_version_1']['id'] = 'field_pdf_version_1';
  $handler->display->display_options['fields']['field_pdf_version_1']['table'] = 'field_data_field_pdf_version';
  $handler->display->display_options['fields']['field_pdf_version_1']['field'] = 'field_pdf_version';
  $handler->display->display_options['fields']['field_pdf_version_1']['label'] = '';
  $handler->display->display_options['fields']['field_pdf_version_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_pdf_version_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pdf_version_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_pdf_version_1']['type'] = 'file_url_plain';
  /* Field: Content: PDF Version */
  $handler->display->display_options['fields']['field_pdf_version']['id'] = 'field_pdf_version';
  $handler->display->display_options['fields']['field_pdf_version']['table'] = 'field_data_field_pdf_version';
  $handler->display->display_options['fields']['field_pdf_version']['field'] = 'field_pdf_version';
  $handler->display->display_options['fields']['field_pdf_version']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_pdf_version']['alter']['text'] = '<a href="[field_pdf_version_1]" target="_blank">View</a> | [field_pdf_version]';
  $handler->display->display_options['fields']['field_pdf_version']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pdf_version']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_pdf_version']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_pdf_version']['type'] = 'file_download_link';
  $handler->display->display_options['fields']['field_pdf_version']['settings'] = array(
    'text' => 'Download',
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[title]
[field_dc_description]
<table class="table">
[field_book_author]
[field_book_editor]
[field_book_translator]
[field_dc_date_publication_year]
[field_dc_date_orginial_year]
[field_kmap_term]
[field_kmap_places]
[field_dc_rights_general]
[field_dc_rights_creativecommons]
</table>
';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'book' => 'book',
  );

  /* Display: Default */
  $handler = $view->new_display('panel_pane', 'Default', 'panel_pane_default');
  $handler->display->display_options['pane_category']['name'] = 'SHANTI Texts';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $translatables['single_text_meta'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Collection Node'),
    t('Collection'),
    t('Visibility'),
    t('[group_content_access_1]'),
    t('[group_access] (default)'),
    t('Author'),
    t('Editor'),
    t('<tr><td>Editor</td><td>[field_book_editor] </td></tr>'),
    t('Translator'),
    t('<tr><td>Translator</td><td>[field_book_translator] </td></tr>'),
    t('Year published'),
    t('<tr><td>Year</td><td>[field_dc_date_publication_year]</td></tr>'),
    t('Original year published'),
    t('<tr><td>Year</td><td>[field_dc_date_publication_year] [field_dc_date_orginial_year]</td></tr>'),
    t('Language'),
    t('Subjects'),
    t('<tr><td>Subjects</td><td>[field_kmap_term]</td></tr>'),
    t('Places'),
    t('<tr>
<td>Places</td>
<td>[field_kmap_places]</td>
</tr>'),
    t('Terms'),
    t('Rights'),
    t('<tr>
<td>Rights</td>
<td>[field_dc_rights_general]</td>
</tr>'),
    t('<tr>
<td colspan="2">[field_dc_rights_general]</td>
</tr>'),
    t('PDF Version'),
    t('<a href="[field_pdf_version_1]" target="_blank">View</a> | [field_pdf_version]'),
    t('[title]
[field_dc_description]
<table class="table">
[field_book_author]
[field_book_editor]
[field_book_translator]
[field_dc_date_publication_year]
[field_dc_date_orginial_year]
[field_kmap_term]
[field_kmap_places]
[field_dc_rights_general]
[field_dc_rights_creativecommons]
</table>
'),
    t('All'),
    t('Default'),
    t('SHANTI Texts'),
  );
  $export['single_text_meta'] = $view;

  $view = new view();
  $view->name = 'single_text_toc';
  $view->description = '';
  $view->tag = 'SHANTI Texts';
  $view->base_table = 'node';
  $view->human_name = 'Single Text TOC';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Text TOC';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'tree';
  $handler->display->display_options['style_options']['main_field'] = 'nid';
  $handler->display->display_options['style_options']['parent_field'] = 'nid_1';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Relationship: Book: Parent */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'book_parent';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  /* Relationship: Book: Top level book */
  $handler->display->display_options['relationships']['bid']['id'] = 'bid';
  $handler->display->display_options['relationships']['bid']['table'] = 'book';
  $handler->display->display_options['relationships']['bid']['field'] = 'bid';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Parent ID */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['relationship'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['ui_name'] = 'Parent ID';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<a href="#shanti-texts-[nid]" id="shanti-texts-toc-[nid]">[title]</a>';
  $handler->display->display_options['fields']['title']['alter']['path'] = '#shanti-texts-[nid]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Sort criterion: Book: Hierarchy */
  $handler->display->display_options['sorts']['p']['id'] = 'p';
  $handler->display->display_options['sorts']['p']['table'] = 'book_menu_links';
  $handler->display->display_options['sorts']['p']['field'] = 'p';
  $handler->display->display_options['sorts']['p']['sort_within_level'] = 1;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'bid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'book' => 'book',
  );
  /* Filter criterion: Book: Depth */
  $handler->display->display_options['filters']['depth']['id'] = 'depth';
  $handler->display->display_options['filters']['depth']['table'] = 'book_menu_links';
  $handler->display->display_options['filters']['depth']['field'] = 'depth';
  $handler->display->display_options['filters']['depth']['operator'] = '>';
  $handler->display->display_options['filters']['depth']['value']['value'] = '1';

  /* Display: Default */
  $handler = $view->new_display('panel_pane', 'Default', 'panel_pane_default');
  $handler->display->display_options['pane_title'] = 'Text TOC';
  $handler->display->display_options['pane_description'] = 'Use in a panel or template for viewing combined texts.';
  $handler->display->display_options['pane_category']['name'] = 'SHANTI Texts';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $translatables['single_text_toc'] = array(
    t('Master'),
    t('Text TOC'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Book parent'),
    t('Book'),
    t('<a href="#shanti-texts-[nid]" id="shanti-texts-toc-[nid]">[title]</a>'),
    t('All'),
    t('Default'),
    t('Use in a panel or template for viewing combined texts.'),
    t('SHANTI Texts'),
  );
  $export['single_text_toc'] = $view;

  $view = new view();
  $view->name = 'single_text_views';
  $view->description = '';
  $view->tag = 'SHANTI Texts';
  $view->base_table = 'node';
  $view->human_name = 'Single Text Views';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: PubReader Link */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'PubReader Link';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'View in PubReader';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'book_pubreader/[nid]';
  $handler->display->display_options['fields']['nothing']['alter']['alt'] = 'View book in NIH PubReader';
  $handler->display->display_options['fields']['nothing']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Stand-alone Link */
  $handler->display->display_options['fields']['nothing_4']['id'] = 'nothing_4';
  $handler->display->display_options['fields']['nothing_4']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_4']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_4']['ui_name'] = 'Stand-alone Link';
  $handler->display->display_options['fields']['nothing_4']['label'] = '';
  $handler->display->display_options['fields']['nothing_4']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing_4']['alter']['text'] = 'View as stand-alone text';
  $handler->display->display_options['fields']['nothing_4']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_4']['alter']['path'] = 'shanti_texts/node_embed/[nid]';
  $handler->display->display_options['fields']['nothing_4']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nothing_4']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['nothing_4']['element_label_colon'] = FALSE;
  /* Field: Voyant Link */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Voyant Link';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = 'View in Voyant';
  $handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_1']['alter']['path'] = 'shanti_texts/voyant/[nid]';
  $handler->display->display_options['fields']['nothing_1']['alter']['alt'] = 'View book in Voyant tools';
  $handler->display->display_options['fields']['nothing_1']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  /* Field: Raw Text Link */
  $handler->display->display_options['fields']['nothing_3']['id'] = 'nothing_3';
  $handler->display->display_options['fields']['nothing_3']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_3']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_3']['ui_name'] = 'Raw Text Link';
  $handler->display->display_options['fields']['nothing_3']['label'] = '';
  $handler->display->display_options['fields']['nothing_3']['alter']['text'] = 'View as raw text';
  $handler->display->display_options['fields']['nothing_3']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_3']['alter']['path'] = 'shanti_texts/node_ajax_text/[nid]';
  $handler->display->display_options['fields']['nothing_3']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nothing_3']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['nothing_3']['element_label_colon'] = FALSE;
  /* Field: Display */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['ui_name'] = 'Display';
  $handler->display->display_options['fields']['nothing_2']['label'] = '';
  $handler->display->display_options['fields']['nothing_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing_2']['element_default_classes'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'book' => 'book',
  );

  /* Display: Default */
  $handler = $view->new_display('panel_pane', 'Default', 'panel_pane_default');
  $handler->display->display_options['pane_category']['name'] = 'SHANTI Texts';
  $handler->display->display_options['pane_category']['weight'] = '0';
  $translatables['single_text_views'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
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
    t('View in PubReader'),
    t('View book in NIH PubReader'),
    t('View as stand-alone text'),
    t('View in Voyant'),
    t('View book in Voyant tools'),
    t('View as raw text'),
    t('All'),
    t('Default'),
    t('SHANTI Texts'),
  );
  $export['single_text_views'] = $view;

  $view = new view();
  $view->name = 'text_collections';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Text Collections';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Collections';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['hide_admin_links'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'pagerer';
  $handler->display->display_options['pager']['options']['items_per_page'] = '36';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['preset'] = 'shanti_default';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = '<div class="view-result-count-info">Displaying @start - @end of @total Collections</div>';
  /* Relationship: OG membership: OG membership from Node group */
  $handler->display->display_options['relationships']['og_membership_rel_group']['id'] = 'og_membership_rel_group';
  $handler->display->display_options['relationships']['og_membership_rel_group']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel_group']['field'] = 'og_membership_rel_group';
  $handler->display->display_options['relationships']['og_membership_rel_group']['required'] = TRUE;
  /* Relationship: OG membership: User from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_user']['id'] = 'og_membership_related_user';
  $handler->display->display_options['relationships']['og_membership_related_user']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_user']['field'] = 'og_membership_related_user';
  $handler->display->display_options['relationships']['og_membership_related_user']['relationship'] = 'og_membership_rel_group';
  $handler->display->display_options['relationships']['og_membership_related_user']['required'] = TRUE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<span class="icon shanticon-stack"></span>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = FALSE;
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[nothing][title]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['exclude'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '80',
  );
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'F Y';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: JMeter Data */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'JMeter Data';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = '<span class="jmeter-data-[nid]"/>';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'collection' => 'collection',
    'subcollection' => 'subcollection',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['title']['expose']['autocomplete_filter'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_min_chars'] = '0';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_field'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_dependent'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<span class="icon shanticon-stack"></span>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = FALSE;
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[nothing][title]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = '';
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_value'] = 'return shanti_collections_get_items_in_collection($row->nid, \'count\');';
  $handler->display->display_options['fields']['php']['php_output'] = '(<em><?php print $value; ?> Items</em>)';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['exclude'] = TRUE;
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'F Y';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '120';
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_plain';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '80',
  );
  /* Field: Content: Parent Collection */
  $handler->display->display_options['fields']['field_og_parent_collection_ref']['id'] = 'field_og_parent_collection_ref';
  $handler->display->display_options['fields']['field_og_parent_collection_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['field_og_parent_collection_ref']['field'] = 'field_og_parent_collection_ref';
  $handler->display->display_options['fields']['field_og_parent_collection_ref']['label'] = '';
  $handler->display->display_options['fields']['field_og_parent_collection_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_og_parent_collection_ref']['settings'] = array(
    'bypass_access' => 0,
    'link' => 1,
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'collection' => 'collection',
    'subcollection' => 'subcollection',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['title']['expose']['autocomplete_filter'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_min_chars'] = '0';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_field'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_dependent'] = 0;
  /* Filter criterion: Content: Group visibility (group_access) */
  $handler->display->display_options['filters']['group_access_value']['id'] = 'group_access_value';
  $handler->display->display_options['filters']['group_access_value']['table'] = 'field_data_group_access';
  $handler->display->display_options['filters']['group_access_value']['field'] = 'group_access_value';
  $handler->display->display_options['filters']['group_access_value']['operator'] = 'not';
  $handler->display->display_options['filters']['group_access_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['path'] = 'collections';
  $translatables['text_collections'] = array(
    t('Master'),
    t('Collections'),
    t('more'),
    t('Apply'),
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
    t('<div class="view-result-count-info">Displaying @start - @end of @total Collections</div>'),
    t('OG membership from node group'),
    t('user from OG membership'),
    t('<span class="icon shanticon-stack"></span>'),
    t('[nothing][title]'),
    t('<span class="jmeter-data-[nid]"/>'),
    t('Page'),
  );
  $export['text_collections'] = $view;

  $view = new view();
  $view->name = 'text_collections_by_users';
  $view->description = 'Show groups of a user.';
  $view->tag = 'og';
  $view->base_table = 'og_membership';
  $view->human_name = 'Text Collections by Users';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['content'] = 'User is not a member of any group.';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['title']['label'] = 'Group';
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  /* Field: OG membership: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'og_membership';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Member since';
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'time ago';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['relationship'] = 'og_membership_related_node_group';
  /* Contextual filter: We pass the user ID as the Entity ID. */
  $handler->display->display_options['arguments']['etid']['id'] = 'etid';
  $handler->display->display_options['arguments']['etid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['etid']['field'] = 'etid';
  $handler->display->display_options['arguments']['etid']['ui_name'] = 'We pass the user ID as the Entity ID.';
  $handler->display->display_options['arguments']['etid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['etid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['etid']['title'] = '%1\'s groups';
  $handler->display->display_options['arguments']['etid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['etid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['etid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['etid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['etid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['etid']['validate']['type'] = 'user';
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: OG membership: Entity_type */
  $handler->display->display_options['filters']['entity_type']['id'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['table'] = 'og_membership';
  $handler->display->display_options['filters']['entity_type']['field'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['value'] = 'user';
  $handler->display->display_options['filters']['entity_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['entity_type']['expose']['operator_id'] = 'entity_type_op';
  $handler->display->display_options['filters']['entity_type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['entity_type']['expose']['operator'] = 'entity_type_op';
  $handler->display->display_options['filters']['entity_type']['expose']['identifier'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['entity_type']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['entity_type']['expose']['autocomplete_min_chars'] = '0';
  $handler->display->display_options['filters']['entity_type']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['entity_type']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['entity_type']['expose']['autocomplete_dependent'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My Collections';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'pagerer';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['preset'] = 'shanti_default';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['type']['label'] = '';
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_value'] = 'return shanti_collections_get_items_in_collection($row->nid, \'count\');';
  $handler->display->display_options['fields']['php']['php_output'] = '(<em><?php print $value; ?> Items</em>)';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '120';
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['empty'] = ' ';
  $handler->display->display_options['fields']['body']['type'] = 'text_plain';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: Parent Collection */
  $handler->display->display_options['fields']['field_og_parent_collection_ref']['id'] = 'field_og_parent_collection_ref';
  $handler->display->display_options['fields']['field_og_parent_collection_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['field_og_parent_collection_ref']['field'] = 'field_og_parent_collection_ref';
  $handler->display->display_options['fields']['field_og_parent_collection_ref']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['field_og_parent_collection_ref']['label'] = '';
  $handler->display->display_options['fields']['field_og_parent_collection_ref']['element_type'] = '0';
  $handler->display->display_options['fields']['field_og_parent_collection_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_og_parent_collection_ref']['settings'] = array(
    'bypass_access' => 0,
    'link' => 1,
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['state']['group'] = 1;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['path'] = 'my_collections';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My Collections';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'user-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['text_collections_by_users'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
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
    t('User is not a member of any group.'),
    t('Group node from OG membership'),
    t('Group'),
    t('Member since'),
    t('All'),
    t('%1\'s groups'),
    t('Type'),
    t('Page'),
    t('My Collections'),
    t(' '),
  );
  $export['text_collections_by_users'] = $view;

  $view = new view();
  $view->name = 'text_search';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Text Search';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Text Search';
  $handler->display->display_options['display_description'] = 'Full Text Search';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['hide_admin_links'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '&#8203;';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'pagerer';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['preset'] = 'shanti_default';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'title_1',
      'rendered' => 0,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<p>Enter a search string, consisting of a word or a phrase enclosed in quotes, to find matching title content. </p>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: Book: Top level book */
  $handler->display->display_options['relationships']['bid']['id'] = 'bid';
  $handler->display->display_options['relationships']['bid']['table'] = 'book';
  $handler->display->display_options['relationships']['bid']['field'] = 'bid';
  $handler->display->display_options['relationships']['bid']['label'] = 'Parent';
  $handler->display->display_options['relationships']['bid']['required'] = TRUE;
  /* Field: Book: Depth */
  $handler->display->display_options['fields']['depth']['id'] = 'depth';
  $handler->display->display_options['fields']['depth']['table'] = 'book_menu_links';
  $handler->display->display_options['fields']['depth']['field'] = 'depth';
  $handler->display->display_options['fields']['depth']['label'] = '';
  $handler->display->display_options['fields']['depth']['exclude'] = TRUE;
  $handler->display->display_options['fields']['depth']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['depth']['separator'] = '';
  /* Field: Book: Weight */
  $handler->display->display_options['fields']['weight']['id'] = 'weight';
  $handler->display->display_options['fields']['weight']['table'] = 'book_menu_links';
  $handler->display->display_options['fields']['weight']['field'] = 'weight';
  $handler->display->display_options['fields']['weight']['label'] = '';
  $handler->display->display_options['fields']['weight']['exclude'] = TRUE;
  $handler->display->display_options['fields']['weight']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['weight']['separator'] = '';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'bid';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['element_default_classes'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'bid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = '[title_1]';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<li class="mega-search-title depth-[depth] weight-[weight]">[title]</li>';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
    if ($row->nid != $row->nid_1) {
      echo "<div class=\'mega-search-title depth-{$row->depth} weight-{$row->weight}\'><a href=\'/node/{$row->nid_1}\'>{$row->title}</a></div>";
    }
  ?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['relationship'] = 'bid';
  /* Sort criterion: Content: Nid */
  $handler->display->display_options['sorts']['nid']['id'] = 'nid';
  $handler->display->display_options['sorts']['nid']['table'] = 'node';
  $handler->display->display_options['sorts']['nid']['field'] = 'nid';
  $handler->display->display_options['sorts']['nid']['relationship'] = 'bid';
  /* Sort criterion: Book: Hierarchy */
  $handler->display->display_options['sorts']['p']['id'] = 'p';
  $handler->display->display_options['sorts']['p']['table'] = 'book_menu_links';
  $handler->display->display_options['sorts']['p']['field'] = 'p';
  $handler->display->display_options['sorts']['p']['sort_within_level'] = 0;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'book' => 'book',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  /* Filter criterion: Book: Depth */
  $handler->display->display_options['filters']['depth']['id'] = 'depth';
  $handler->display->display_options['filters']['depth']['table'] = 'book_menu_links';
  $handler->display->display_options['filters']['depth']['field'] = 'depth';
  $handler->display->display_options['filters']['depth']['operator'] = '>';
  $handler->display->display_options['filters']['depth']['value']['value'] = '1';

  /* Display: Default */
  $handler = $view->new_display('block', 'Default', 'block_1');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['block_description'] = 'Text Search Default';

  /* Display: Full */
  $handler = $view->new_display('block', 'Full', 'block_2');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'book' => 'book',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Content (field_book_content) */
  $handler->display->display_options['filters']['field_book_content_value']['id'] = 'field_book_content_value';
  $handler->display->display_options['filters']['field_book_content_value']['table'] = 'field_data_field_book_content';
  $handler->display->display_options['filters']['field_book_content_value']['field'] = 'field_book_content_value';
  $handler->display->display_options['filters']['field_book_content_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_book_content_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_book_content_value']['expose']['operator_id'] = 'field_book_content_value_op';
  $handler->display->display_options['filters']['field_book_content_value']['expose']['description'] = 'Search the content of texts';
  $handler->display->display_options['filters']['field_book_content_value']['expose']['operator'] = 'field_book_content_value_op';
  $handler->display->display_options['filters']['field_book_content_value']['expose']['identifier'] = 'field_book_content_value';
  $handler->display->display_options['filters']['field_book_content_value']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_book_content_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => '1',
    3 => '3',
  );

  /* Display: Title */
  $handler = $view->new_display('block', 'Title', 'block_3');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Book: Depth */
  $handler->display->display_options['fields']['depth']['id'] = 'depth';
  $handler->display->display_options['fields']['depth']['table'] = 'book_menu_links';
  $handler->display->display_options['fields']['depth']['field'] = 'depth';
  $handler->display->display_options['fields']['depth']['label'] = '';
  $handler->display->display_options['fields']['depth']['exclude'] = TRUE;
  $handler->display->display_options['fields']['depth']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['depth']['separator'] = '';
  /* Field: Book: Weight */
  $handler->display->display_options['fields']['weight']['id'] = 'weight';
  $handler->display->display_options['fields']['weight']['table'] = 'book_menu_links';
  $handler->display->display_options['fields']['weight']['field'] = 'weight';
  $handler->display->display_options['fields']['weight']['label'] = '';
  $handler->display->display_options['fields']['weight']['exclude'] = TRUE;
  $handler->display->display_options['fields']['weight']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['weight']['separator'] = '';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'bid';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['element_default_classes'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'bid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['alter']['text'] = '[title_1]';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<li class="mega-search-title depth-[depth] weight-[weight]">[title]</li>';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php 
if ($row->nid != $row->nid_1) {
echo "<div class=\'mega-search-title depth-{$row->depth} weight-{$row->weight}\'><a href=\'/node/{$row->nid_1}\'>{$row->title}</a></div>"; 
}
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'book' => 'book',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['description'] = 'Search the titles and subtitles of texts';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['required'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => '1',
    3 => '3',
    6 => 0,
  );
  $handler->display->display_options['filters']['title']['expose']['autocomplete_filter'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_min_chars'] = '1';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_field'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_dependent'] = 0;

  /* Display: My */
  $handler = $view->new_display('block', 'My', 'block_4');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'book' => 'book',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $translatables['text_search'] = array(
    t('Master'),
    t('Text Search'),
    t('Full Text Search'),
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
    t('<p>Enter a search string, consisting of a word or a phrase enclosed in quotes, to find matching title content. </p>'),
    t('Parent'),
    t('.'),
    t('[title_1]'),
    t('<li class="mega-search-title depth-[depth] weight-[weight]">[title]</li>'),
    t('Type'),
    t('Default'),
    t('All'),
    t('Text Search Default'),
    t('Full'),
    t('Search the content of texts'),
    t('Title'),
    t('Search the titles and subtitles of texts'),
    t('My'),
  );
  $export['text_search'] = $view;

  return $export;
}
