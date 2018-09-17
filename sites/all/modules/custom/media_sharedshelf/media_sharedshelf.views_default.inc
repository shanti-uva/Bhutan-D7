<?php
/**
 * @file
 * The view for displaying the SharedShelf media downloaded to Drupal so that
 * paging is available within the Add from SharedShelf media feature.
 */

/**
 * Implements hook_views_default_view().
 */
function media_sharedshelf_views_default_views() {
	/** My Images View **/
	$view = new view();
	$view -> name = 'media_sharedshelf_my_images';
	$view -> description = 'Display the existing SharedShelf media downloaded to Drupal';
	$view -> tag = 'default';
	$view -> base_table = 'file_managed';
	$view -> human_name = 'My SharedShelf Images';
	$view -> core = 7;
	$view -> api_version = '3.0';
	$view -> disabled = FALSE;
	/* Edit this to true to make a default view disabled initially */

	/* Display: Master */
	$handler = $view -> new_display('default', 'Master', 'default');
	$handler -> display -> display_options['title'] = 'My SharedShelf Images';
	$handler -> display -> display_options['use_more_always'] = FALSE;
	$handler -> display -> display_options['access']['type'] = 'none';
	$handler -> display -> display_options['cache']['type'] = 'none';
	$handler -> display -> display_options['query']['type'] = 'views_query';
	$handler -> display -> display_options['exposed_form']['type'] = 'basic';
	$handler -> display -> display_options['pager']['type'] = 'full';
	$handler -> display -> display_options['pager']['options']['items_per_page'] = '12';
	$handler -> display -> display_options['style_plugin'] = 'grid';
	$handler -> display -> display_options['row_plugin'] = 'file';
	$handler -> display -> display_options['row_options']['view_mode'] = 'preview';
	$handler -> display -> display_options['row_options']['links'] = 1;
	/* Field: File: Name */
	$handler -> display -> display_options['fields']['filename']['id'] = 'filename';
	$handler -> display -> display_options['fields']['filename']['table'] = 'file_managed';
	$handler -> display -> display_options['fields']['filename']['field'] = 'filename';
	$handler -> display -> display_options['fields']['filename']['label'] = '';
	$handler -> display -> display_options['fields']['filename']['alter']['word_boundary'] = FALSE;
	$handler -> display -> display_options['fields']['filename']['alter']['ellipsis'] = FALSE;
	/* Sort criterion: File: Upload date */
	$handler -> display -> display_options['sorts']['timestamp']['id'] = 'timestamp';
	$handler -> display -> display_options['sorts']['timestamp']['table'] = 'file_managed';
	$handler -> display -> display_options['sorts']['timestamp']['field'] = 'timestamp';
	$handler -> display -> display_options['sorts']['timestamp']['order'] = 'DESC';
	/* Filter criterion: File: Path */
	$handler -> display -> display_options['filters']['uri']['id'] = 'uri';
	$handler -> display -> display_options['filters']['uri']['table'] = 'file_managed';
	$handler -> display -> display_options['filters']['uri']['field'] = 'uri';
	$handler -> display -> display_options['filters']['uri']['operator'] = 'contains';
	$handler -> display -> display_options['filters']['uri']['value'] = 'sharedshelf';
	/* Filter criterion: File: Path
	 $handler->display->display_options['filters']['uri_1']['id'] = 'uri_1';
	 $handler->display->display_options['filters']['uri_1']['table'] = 'file_managed';
	 $handler->display->display_options['filters']['uri_1']['field'] = 'uri';
	 $handler->display->display_options['filters']['uri_1']['operator'] = 'not';
	 $handler->display->display_options['filters']['uri_1']['value'] = 'pdfthumbs';
	 */

	/* Display: Block */
	$handler = $view -> new_display('block', 'Block', 'block');
	// Export ends here.

	// Add view to list of views provided.
	$views[$view -> name] = $view;
	/** End of My Images View **/
	
	/** File Admin View **/
	$view = new view();
	$view->name = 'sharedshelf_images_admin';
	$view->description = 'Display the existing SharedShelf media downloaded to Drupal';
	$view->tag = 'default';
	$view->base_table = 'file_managed';
	$view->human_name = 'SharedShelf Images Admin';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
	
	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'SharedShelf Images Admin';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'role';
	$handler->display->display_options['access']['role'] = array(
	  3 => '3',
	);
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'pagerer';
	$handler->display->display_options['pager']['options']['items_per_page'] = '50';
	$handler->display->display_options['pager']['options']['offset'] = '0';
	$handler->display->display_options['pager']['options']['id'] = '0';
	$handler->display->display_options['pager']['options']['quantity'] = '1';
	$handler->display->display_options['pager']['options']['preset'] = 'core_replace';
	$handler->display->display_options['style_plugin'] = 'table';
	$handler->display->display_options['style_options']['columns'] = array(
	  'views_bulk_operations' => 'views_bulk_operations',
	  'fid' => 'fid',
	  'filename' => 'filename',
	  'filemime' => 'filemime',
	  'field_sharedshelf_creator' => 'field_sharedshelf_creator',
	  'field_sharedshelf_date' => 'field_sharedshelf_date',
	  'field_sharedshelf_project_id' => 'field_sharedshelf_project_id',
	  'field_sharedshelf_ssid' => 'field_sharedshelf_ssid',
	  'filesize' => 'filesize',
	);
	$handler->display->display_options['style_options']['default'] = 'filename';
	$handler->display->display_options['style_options']['info'] = array(
	  'views_bulk_operations' => array(
	    'align' => '',
	    'separator' => '',
	    'empty_column' => 0,
	  ),
	  'fid' => array(
	    'sortable' => 1,
	    'default_sort_order' => 'asc',
	    'align' => '',
	    'separator' => '',
	    'empty_column' => 0,
	  ),
	  'filename' => array(
	    'sortable' => 1,
	    'default_sort_order' => 'asc',
	    'align' => '',
	    'separator' => '',
	    'empty_column' => 0,
	  ),
	  'filemime' => array(
	    'sortable' => 1,
	    'default_sort_order' => 'asc',
	    'align' => '',
	    'separator' => '',
	    'empty_column' => 0,
	  ),
	  'field_sharedshelf_creator' => array(
	    'align' => '',
	    'separator' => '',
	    'empty_column' => 0,
	  ),
	  'field_sharedshelf_date' => array(
	    'sortable' => 1,
	    'default_sort_order' => 'asc',
	    'align' => '',
	    'separator' => '',
	    'empty_column' => 0,
	  ),
	  'field_sharedshelf_project_id' => array(
	    'sortable' => 0,
	    'default_sort_order' => 'asc',
	    'align' => '',
	    'separator' => '',
	    'empty_column' => 0,
	  ),
	  'field_sharedshelf_ssid' => array(
	    'sortable' => 1,
	    'default_sort_order' => 'asc',
	    'align' => '',
	    'separator' => '',
	    'empty_column' => 0,
	  ),
	  'filesize' => array(
	    'sortable' => 0,
	    'default_sort_order' => 'asc',
	    'align' => '',
	    'separator' => '',
	    'empty_column' => 0,
	  ),
	);
	/* Field: Bulk operations: File */
	$handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
	$handler->display->display_options['fields']['views_bulk_operations']['table'] = 'file_managed';
	$handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
	$handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
	  'action::views_bulk_operations_delete_item' => array(
	    'selected' => 1,
	    'postpone_processing' => 0,
	    'skip_confirmation' => 0,
	    'override_label' => 0,
	    'label' => '',
	  ),
	  'action::views_bulk_operations_script_action' => array(
	    'selected' => 1,
	    'postpone_processing' => 0,
	    'skip_confirmation' => 0,
	    'override_label' => 0,
	    'label' => '',
	  ),
	);
	/* Field: File: File ID */
	$handler->display->display_options['fields']['fid']['id'] = 'fid';
	$handler->display->display_options['fields']['fid']['table'] = 'file_managed';
	$handler->display->display_options['fields']['fid']['field'] = 'fid';
	$handler->display->display_options['fields']['fid']['element_label_colon'] = FALSE;
	/* Field: File: Name */
	$handler->display->display_options['fields']['filename']['id'] = 'filename';
	$handler->display->display_options['fields']['filename']['table'] = 'file_managed';
	$handler->display->display_options['fields']['filename']['field'] = 'filename';
	$handler->display->display_options['fields']['filename']['label'] = '';
	$handler->display->display_options['fields']['filename']['alter']['word_boundary'] = FALSE;
	$handler->display->display_options['fields']['filename']['alter']['ellipsis'] = FALSE;
	/* Field: File: Mime type */
	$handler->display->display_options['fields']['filemime']['id'] = 'filemime';
	$handler->display->display_options['fields']['filemime']['table'] = 'file_managed';
	$handler->display->display_options['fields']['filemime']['field'] = 'filemime';
	$handler->display->display_options['fields']['filemime']['element_label_colon'] = FALSE;
	/* Field: File: Creator */
	$handler->display->display_options['fields']['field_sharedshelf_creator']['id'] = 'field_sharedshelf_creator';
	$handler->display->display_options['fields']['field_sharedshelf_creator']['table'] = 'field_data_field_sharedshelf_creator';
	$handler->display->display_options['fields']['field_sharedshelf_creator']['field'] = 'field_sharedshelf_creator';
	$handler->display->display_options['fields']['field_sharedshelf_creator']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['field_sharedshelf_creator']['delta_offset'] = '0';
	/* Field: File: Date */
	$handler->display->display_options['fields']['field_sharedshelf_date']['id'] = 'field_sharedshelf_date';
	$handler->display->display_options['fields']['field_sharedshelf_date']['table'] = 'field_data_field_sharedshelf_date';
	$handler->display->display_options['fields']['field_sharedshelf_date']['field'] = 'field_sharedshelf_date';
	$handler->display->display_options['fields']['field_sharedshelf_date']['element_label_colon'] = FALSE;
	/* Field: File: Project ID */
	$handler->display->display_options['fields']['field_sharedshelf_project_id']['id'] = 'field_sharedshelf_project_id';
	$handler->display->display_options['fields']['field_sharedshelf_project_id']['table'] = 'field_data_field_sharedshelf_project_id';
	$handler->display->display_options['fields']['field_sharedshelf_project_id']['field'] = 'field_sharedshelf_project_id';
	$handler->display->display_options['fields']['field_sharedshelf_project_id']['element_label_colon'] = FALSE;
	/* Field: File: SSID */
	$handler->display->display_options['fields']['field_sharedshelf_ssid']['id'] = 'field_sharedshelf_ssid';
	$handler->display->display_options['fields']['field_sharedshelf_ssid']['table'] = 'field_data_field_sharedshelf_ssid';
	$handler->display->display_options['fields']['field_sharedshelf_ssid']['field'] = 'field_sharedshelf_ssid';
	$handler->display->display_options['fields']['field_sharedshelf_ssid']['element_label_colon'] = FALSE;
	/* Field: File: Size */
	$handler->display->display_options['fields']['filesize']['id'] = 'filesize';
	$handler->display->display_options['fields']['filesize']['table'] = 'file_managed';
	$handler->display->display_options['fields']['filesize']['field'] = 'filesize';
	$handler->display->display_options['fields']['filesize']['element_label_colon'] = FALSE;
	/* Sort criterion: File: Upload date */
	$handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
	$handler->display->display_options['sorts']['timestamp']['table'] = 'file_managed';
	$handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
	$handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
	/* Filter criterion: File: Path */
	$handler->display->display_options['filters']['uri']['id'] = 'uri';
	$handler->display->display_options['filters']['uri']['table'] = 'file_managed';
	$handler->display->display_options['filters']['uri']['field'] = 'uri';
	$handler->display->display_options['filters']['uri']['operator'] = 'contains';
	$handler->display->display_options['filters']['uri']['value'] = 'sharedshelf';
	$handler->display->display_options['filters']['uri']['group'] = 1;
	/* Filter criterion: File: Project ID (field_sharedshelf_project_id) */
	$handler->display->display_options['filters']['field_sharedshelf_project_id_value']['id'] = 'field_sharedshelf_project_id_value';
	$handler->display->display_options['filters']['field_sharedshelf_project_id_value']['table'] = 'field_data_field_sharedshelf_project_id';
	$handler->display->display_options['filters']['field_sharedshelf_project_id_value']['field'] = 'field_sharedshelf_project_id_value';
	$handler->display->display_options['filters']['field_sharedshelf_project_id_value']['group'] = 1;
	$handler->display->display_options['filters']['field_sharedshelf_project_id_value']['exposed'] = TRUE;
	$handler->display->display_options['filters']['field_sharedshelf_project_id_value']['expose']['operator_id'] = 'field_sharedshelf_project_id_value_op';
	$handler->display->display_options['filters']['field_sharedshelf_project_id_value']['expose']['label'] = 'Project ID (field_sharedshelf_project_id)';
	$handler->display->display_options['filters']['field_sharedshelf_project_id_value']['expose']['operator'] = 'field_sharedshelf_project_id_value_op';
	$handler->display->display_options['filters']['field_sharedshelf_project_id_value']['expose']['identifier'] = 'field_sharedshelf_project_id_value';
	$handler->display->display_options['filters']['field_sharedshelf_project_id_value']['expose']['remember_roles'] = array(
	  2 => '2',
	  1 => 0,
	  3 => 0,
	);
	/* Filter criterion: File: SSID (field_sharedshelf_ssid) */
	$handler->display->display_options['filters']['field_sharedshelf_ssid_value']['id'] = 'field_sharedshelf_ssid_value';
	$handler->display->display_options['filters']['field_sharedshelf_ssid_value']['table'] = 'field_data_field_sharedshelf_ssid';
	$handler->display->display_options['filters']['field_sharedshelf_ssid_value']['field'] = 'field_sharedshelf_ssid_value';
	$handler->display->display_options['filters']['field_sharedshelf_ssid_value']['operator'] = 'starts';
	$handler->display->display_options['filters']['field_sharedshelf_ssid_value']['exposed'] = TRUE;
	$handler->display->display_options['filters']['field_sharedshelf_ssid_value']['expose']['operator_id'] = 'field_sharedshelf_ssid_value_op';
	$handler->display->display_options['filters']['field_sharedshelf_ssid_value']['expose']['label'] = 'SSID (field_sharedshelf_ssid)';
	$handler->display->display_options['filters']['field_sharedshelf_ssid_value']['expose']['operator'] = 'field_sharedshelf_ssid_value_op';
	$handler->display->display_options['filters']['field_sharedshelf_ssid_value']['expose']['identifier'] = 'field_sharedshelf_ssid_value';
	$handler->display->display_options['filters']['field_sharedshelf_ssid_value']['expose']['remember_roles'] = array(
	  2 => '2',
	  1 => 0,
	  3 => 0,
	);
	$handler->display->display_options['filters']['field_sharedshelf_ssid_value']['group_info']['label'] = 'SSID (field_sharedshelf_ssid)';
	$handler->display->display_options['filters']['field_sharedshelf_ssid_value']['group_info']['identifier'] = 'field_sharedshelf_ssid_value';
	$handler->display->display_options['filters']['field_sharedshelf_ssid_value']['group_info']['group_items'] = array(
	  1 => array(
	    'title' => '',
	    'operator' => '=',
	    'value' => '',
	  ),
	  2 => array(
	    'title' => '',
	    'operator' => '=',
	    'value' => '',
	  ),
	  3 => array(
	    'title' => '',
	    'operator' => '=',
	    'value' => '',
	  ),
	);
	/* Filter criterion: File: Title (field_sharedshelf_title) */
	$handler->display->display_options['filters']['field_sharedshelf_title_value']['id'] = 'field_sharedshelf_title_value';
	$handler->display->display_options['filters']['field_sharedshelf_title_value']['table'] = 'field_data_field_sharedshelf_title';
	$handler->display->display_options['filters']['field_sharedshelf_title_value']['field'] = 'field_sharedshelf_title_value';
	$handler->display->display_options['filters']['field_sharedshelf_title_value']['operator'] = 'contains';
	$handler->display->display_options['filters']['field_sharedshelf_title_value']['exposed'] = TRUE;
	$handler->display->display_options['filters']['field_sharedshelf_title_value']['expose']['operator_id'] = 'field_sharedshelf_title_value_op';
	$handler->display->display_options['filters']['field_sharedshelf_title_value']['expose']['label'] = 'Title';
	$handler->display->display_options['filters']['field_sharedshelf_title_value']['expose']['operator'] = 'field_sharedshelf_title_value_op';
	$handler->display->display_options['filters']['field_sharedshelf_title_value']['expose']['identifier'] = 'field_sharedshelf_title_value';
	$handler->display->display_options['filters']['field_sharedshelf_title_value']['expose']['remember_roles'] = array(
	  2 => '2',
	  1 => 0,
	  3 => 0,
	);
	
	/* Display: Shared Shelf Admin Page */
	$handler = $view->new_display('page', 'Shared Shelf Admin Page', 'page_1');
	$handler->display->display_options['path'] = 'files/admin';
	
	// Add view to list of views provided.
	$views[$view -> name] = $view;
	/** End of File Admin View **/

	return $views;
}
