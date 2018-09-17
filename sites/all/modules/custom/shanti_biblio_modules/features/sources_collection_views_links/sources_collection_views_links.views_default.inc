<?php
/**
 * @file
 * sources_collection_views_links.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function sources_collection_views_links_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'biblio_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Biblio List';
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
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = '<div class="view-result-count-info">Displaying @start - @end of @total sources</div>';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  /* Field: Biblio: Biblio Citation */
  $handler->display->display_options['fields']['citation']['id'] = 'citation';
  $handler->display->display_options['fields']['citation']['table'] = 'biblio';
  $handler->display->display_options['fields']['citation']['field'] = 'citation';
  $handler->display->display_options['fields']['citation']['label'] = '';
  $handler->display->display_options['fields']['citation']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['citation']['alter']['path'] = '[path]';
  $handler->display->display_options['fields']['citation']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['citation']['style_name'] = 'mla';
  $handler->display->display_options['fields']['citation']['export_links'] = 0;
  $handler->display->display_options['fields']['citation']['file_attachments'] = 0;
  $handler->display->display_options['fields']['citation']['open_url_link'] = 0;
  /* Sort criterion: Biblio: Author last name */
  $handler->display->display_options['sorts']['lastname']['id'] = 'lastname';
  $handler->display->display_options['sorts']['lastname']['table'] = 'biblio_contributor_data';
  $handler->display->display_options['sorts']['lastname']['field'] = 'lastname';
  $handler->display->display_options['sorts']['lastname']['rank'] = '0';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
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
    'biblio' => 'biblio',
  );

  /* Display: Sources List Block */
  $handler = $view->new_display('block', 'Sources List Block', 'block');
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['block_description'] = 'Biblio List Block';

  /* Display: Sources List Pane */
  $handler = $view->new_display('panel_pane', 'Sources List Pane', 'panel_pane_1');
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['label'] = 'Collection';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['required'] = TRUE;
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['id'] = 'og_membership_related_node_group_1';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group_1']['relationship'] = 'og_membership_related_node_group';
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
  $handler->display->display_options['pane_title'] = 'Source List Pane for Collections';
  $handler->display->display_options['pane_description'] = 'A content pane to list source items associated with a collection';
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
  $export['biblio_list'] = $view;

  return $export;
}
