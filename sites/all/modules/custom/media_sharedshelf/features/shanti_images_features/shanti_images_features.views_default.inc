<?php
/**
 * @file
 * shanti_images_features.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function shanti_images_features_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'collection_images_sharedshelf';
  $view->description = 'Display the existing SharedShelf media downloaded to Drupal';
  $view->tag = 'default';
  $view->base_table = 'file_managed';
  $view->human_name = 'Collection Images Sharedshelf';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Collection Contents';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '518400';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '518400';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'pagerer';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '1';
  $handler->display->display_options['pager']['options']['preset'] = 'pagerer_core';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['row_plugin'] = 'file';
  $handler->display->display_options['row_options']['view_mode'] = 'preview';
  $handler->display->display_options['row_options']['links'] = 1;
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  /* Field: File: Name */
  $handler->display->display_options['fields']['filename']['id'] = 'filename';
  $handler->display->display_options['fields']['filename']['table'] = 'file_managed';
  $handler->display->display_options['fields']['filename']['field'] = 'filename';
  $handler->display->display_options['fields']['filename']['label'] = '';
  $handler->display->display_options['fields']['filename']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['filename']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: File: Upload date */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'file_managed';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Contextual filter: Field: Collection (field_og_collection_ref) */
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['id'] = 'field_og_collection_ref_target_id';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['field'] = 'field_og_collection_ref_target_id';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_og_collection_ref_target_id']['break_phrase'] = TRUE;
  /* Filter criterion: File: Path */
  $handler->display->display_options['filters']['uri']['id'] = 'uri';
  $handler->display->display_options['filters']['uri']['table'] = 'file_managed';
  $handler->display->display_options['filters']['uri']['field'] = 'uri';
  $handler->display->display_options['filters']['uri']['operator'] = 'contains';
  $handler->display->display_options['filters']['uri']['value'] = 'sharedshelf';

  /* Display: Collection Content Block */
  $handler = $view->new_display('block', 'Collection Content Block', 'block');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: File: Path */
  $handler->display->display_options['filters']['uri']['id'] = 'uri';
  $handler->display->display_options['filters']['uri']['table'] = 'file_managed';
  $handler->display->display_options['filters']['uri']['field'] = 'uri';
  $handler->display->display_options['filters']['uri']['operator'] = 'contains';
  $handler->display->display_options['filters']['uri']['value'] = 'sharedshelf';
  $handler->display->display_options['filters']['uri']['group'] = 1;

  /* Display: Collection Content Pane */
  $handler = $view->new_display('panel_pane', 'Collection Content Pane', 'collection_content_pane');
  $export['collection_images_sharedshelf'] = $view;

  return $export;
}
