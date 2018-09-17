<?php
/**
 * @file
 * Administrative page callbacks for Media: SharedShelf.
 */

/**
 * Callback for /admin/configure/media/media_sharedshelf/api.
 *
 * Provides configuring the necessary authentication for SharedShelf API access.
 */
function media_sharedshelf_api_form() {
	$form = array();
	$form['api'] = array('#type' => 'fieldset', '#title' => t('SharedShelf API'), '#description' => t('You need to have an account for <a href="@sharedshelf" target="_blank">ARTstor\'s SharedShelf</a>.', array('@sharedshelf' => MEDIA_SHAREDSHELF_MAIN_URL)), );
	$form['api'][media_sharedshelf_variable_name('host_server')] = array('#type' => 'select', '#title' => t('SharedShelf Server'), '#default_value' => media_sharedshelf_variable_get('host_server'), '#description' => t('Please choose whether you want to access the production or demo version of SharedShelf.'), '#options' => media_sharedshelf_host_servers(), );
	$form['api'][media_sharedshelf_variable_name('login_email')] = array('#type' => 'textfield', '#title' => t('SharedShelf Login Email'), '#default_value' => media_sharedshelf_variable_get('login_email'), '#description' => t('Please enter your SharedShelf login email here.'), );
	$form['api'][media_sharedshelf_variable_name('login_password')] = array('#type' => 'password', '#title' => t('SharedShelf Login Password'), '#default_value' => media_sharedshelf_variable_get('login_password'), '#description' => t('Please enter your SharedShelf login password here.'), );

	return system_settings_form($form);
}

/**
 * Callback for /admin/configure/media/media_sharedshelf/settings.
 *
 * Provides for creating default values to use when access forms for adding
 * content and retrieving SharedShelf media.
 */
function media_sharedshelf_settings_form() {
	module_load_include('inc', 'media_sharedshelf', 'includes/media_sharedshelf.utilities');
	$form = array();
	$form['media_settings'] = array('#type' => 'fieldset', '#title' => t('SharedShelf Media Settings'), );
	$form['media_settings']['image_settings'] = array('#type' => 'fieldset', '#title' => t('Image Performance Settings'), '#description' => filter_xss(t('Indicate the image size to download to local cache when using !addmedia.', array('!addmedia' => l(t('Add media from SharedShelf'), check_plain('admin/content/media/add/media_sharedshelf'))))), );
	$form['media_settings']['image_settings'][media_sharedshelf_variable_name('local_cache_image_size')] = array('#type' => 'select', '#title' => t('Local Cache Image Size'), '#default_value' => media_sharedshelf_variable_get('local_cache_image_size'), '#description' => t('Please specify the image size to pull down to local cache.'), '#options' => media_sharedshelf_image_sizes(), );

	$form['media_settings']['image_settings']['clear_cache_button'] = array('#type' => 'button', '#value' => t('Clear Cache Variables'), '#submit' => cache_clear_all(), '#suffix' => '<div class="description">' . t('Clear stored results from Shared Shelf to refresh data. Use this when changes have been made in shared shelf that are not reflected on this site.') . '</div><div id="mss-cc-result"></div>', '#ajax' => array('callback' => 'media_sharedshelf_clear_cache', 'wrapper' => 'mss-cc-result', 'method' => 'replace', 'effect' => 'fade', ));

	$form['media_settings']['form_defaults'] = array('#type' => 'fieldset', '#title' => t('Form Default Settings'), '#description' => t('These form default settings will be applied to the appropriate add content forms.'), );
	$project_list = _media_sharedshelf_get_projects();
	$form['media_settings']['form_defaults'][media_sharedshelf_variable_name('default_project')] = array('#type' => 'select', '#title' => t('Default Project'), '#description' => t('Choose a project to have selected whenever a project list is displayed.'), '#options' => ( array('0' => '') + $project_list), '#default_value' => media_sharedshelf_variable_get('default_project'), );
	$form['media_settings']['form_defaults'][media_sharedshelf_variable_name('search_images_per_page')] = array('#type' => 'select', '#title' => t('Images Per Page'), '#default_value' => media_sharedshelf_variable_get('search_images_per_page'), '#description' => t('Please select the number of images per project to display per page when showing search results.'), '#options' => media_sharedshelf_number_images_per_page(), );

	return system_settings_form($form);
}

/**
 * Clear the Drupal cache for Shared shelf HTTP calls. Called from settings form submit button
 */
function media_sharedshelf_clear_cache($form, $form_state) {
	cache_clear_all();
	return '<div id="mss-cc-result" class="messages status">All cached Sharedshelf data has been cleared!</div>';
}

/**
 * Callback for /media/add/media_sharedshelf.
 *
 * Provides a way to add SharedShelf items to the Media module.
 */
function media_sharedshelf_add($form, &$form_state = array(), $redirect = NULL) {
    
	module_load_include('inc', 'media_sharedshelf', 'includes/media_sharedshelf.utilities');
	$form = array();
	$form['sharedshelf'] = array('#type' => 'vertical_tabs', );
	$form['sharedshelf']['all'] = array('#type' => 'fieldset', '#title' => t('My SharedShelf images'), );

	// Use a view to display the sharedshelf content already downloaded.
	$form['sharedshelf']['all']['sharedshelf_media'] = array('#markup' => views_embed_view('media_sharedshelf_my_images', 'block'), );

	$form['sharedshelf']['redirect'] = array('#type' => 'value', '#value' => $redirect, );

	// Allow the user to enter a specific SharedShelf ID for an image.
	$form['sharedshelf']['add_sharedshelf_id'] = array('#type' => 'fieldset', '#title' => t('Add Using SharedShelf ID'), );

	$form['sharedshelf']['add_sharedshelf_id']['ssid'] = array('#type' => 'textfield', '#title' => t('SSID'), '#description' => t('Enter the SharedShelf ID for the image.'), );
    
    $form['sharedshelf']['add_sharedshelf_id']['collection_select_id'] = media_sharedshelf_collection_select();  // See media_sharedshelf.module
    
	$form['sharedshelf']['add_sharedshelf_id']['reimport_metadata'] = array('#type' => 'checkbox', '#title' => t('Reimport Metadata'), '#description' => t('If checked, will reimport metadata from Shared Shelf for images already on this site. <br/><strong>Warning:</strong> This will overwrite the currently stored metadata (title, description, etc.) for this image.'), );

	$form['sharedshelf']['add_sharedshelf_id']['submit_ssid'] = array('#type' => 'submit', '#name' => 'add_image', '#value' => t('Add'), );

	// Allow a user to select projects or sets to load images.
	// @TODO Add checkbox to dynamically get project/set and store reference?
	$form['sharedshelf']['add_project_imageset'] = array('#type' => 'fieldset', '#title' => t('Add Project/Image Sets'), );

	// Retrieve the a list of projects from SharedShelf to use in two of the add
	// options.
	$projects = _media_sharedshelf_get_projects();

	// If returned to the form get the previous project value otherwise use the
	// default project from the configuration feature when accessing this form
	// initially.
	$default_project = !empty($form_state['values']['project']) ? check_plain($form_state['values']['project']) : media_sharedshelf_variable_get('default_project');
	$form['sharedshelf']['add_project_imageset']['project'] = array('#prefix' => '<div class="sharedshelf_project">', '#type' => 'select', '#title' => t('Project'), '#description' => t('Choose a project from which to add images.'), '#options' => ( array('0' => '') + $projects), '#default_value' => $default_project, '#suffix' => '</div>', '#ajax' => array('callback' => 'media_sharedshelf_add_ajax_select_image_set_callback', 'wrapper' => 'sharedshelf-project-image-set-selection', 'method' => 'replace', 'effect' => 'fade', ), );

	// Create a div that will hold the ajax callback content for the image set
	// selection list.
	if ($default_project == MEDIA_SHAREDSHELF_DEFAULT_PROJECT) {
		$default_project_description = 'After selecting a project, image sets will be displayed here and you can choose one or more of them.';
	} else {
		$default_project_description = 'There are no image sets for this selected project. All images in the project will be added.';
	}
	$option_image_sets = (count($projects) > 0) ? _media_sharedshelf_get_asset_groups($default_project) : array();
	if (count($option_image_sets) > 0) {
		$project_name = _media_sharedshelf_get_project_name($default_project);
		$default_project_description = 'Choose from the ' . $project_name . ' image sets below to add images only from them if preferred.';
	}
	$form['sharedshelf']['add_project_imageset']['project_sets'] = array('#prefix' => '<div id="sharedshelf-project-image-set-selection">', '#type' => 'fieldset', '#title' => t('Available Image Sets'), '#description' => t("@description", array('@description' => $default_project_description)), '#suffix' => '</div>', );

	if (count($option_image_sets) > 0) {
		$form['sharedshelf']['add_project_imageset']['project_sets']['image_sets'] = array('#type' => 'select', '#multiple' => TRUE, '#options' => $option_image_sets, );
	}
    
    $form['sharedshelf']['add_project_imageset']['collection_select_project'] = media_sharedshelf_collection_select();   // See media_sharedshelf.module

	$form['sharedshelf']['add_project_imageset']['reimport_metadata'] = array('#type' => 'checkbox', '#title' => t('Reimport Metadata'), '#description' => t('If checked, will reimport metadata from Shared Shelf for images already on this site. <br/><strong>Warning:</strong> This will overwrite the currently stored metadata (title, description, etc.) for the images in this project.'), );

	$form['sharedshelf']['add_project_imageset']['submit_project_imageset'] = array('#type' => 'submit', '#name' => 'add_project_imagesets', '#value' => t('Add'), );

	// Allow for searching projects, etc. for images to use.
	// @TODO Add checkbox to dynamically get search results and store reference?
	$form['sharedshelf']['add_from_search'] = array('#type' => 'fieldset', '#title' => t('Search SharedShelf'), );

	$form['sharedshelf']['add_from_search']['search'] = array('#type' => 'fieldset', '#title' => t('Search for Images on SharedShelf'), '#description' => t('Specify the desired criteria and select search to retrieve results from SharedShelf. After seeing the results you can choose to add some or all of the results.'), );

	// Use default project from configuration settings as initial project selected
	// when form loaded.
	$default_search_projects = !empty($form_state['values']['search_projects']) ? $form_state['values']['search_projects'] : array(media_sharedshelf_variable_get('default_project'));
	$form['sharedshelf']['add_from_search']['search']['search_projects'] = array('#type' => 'select', '#multiple' => TRUE, '#title' => t('Projects'), '#description' => t('Select which project(s) to search.'), '#options' => $projects, '#default_value' => $default_search_projects, );

	foreach (media_sharedshelf_search_filter_fields() as $field) {
		$l_field = str_replace(' ', '_', drupal_strtolower($field));
		$form['sharedshelf']['add_from_search']['search'][$l_field] = array('#type' => 'textfield', '#title' => t("@title", array('@title' => $field)), '#description' => t("Filter results to only show images from a @lfield containing this value. This is only applicable if your project schema contains a @field field.", array('@lfield' => check_plain($l_field), '@field' => check_plain($field))), );
	}

	$form['sharedshelf']['add_from_search']['search']['keywords'] = array('#type' => 'textfield', '#title' => t('Keywords'), '#description' => t('Text entered here will be searched for in all image data fields.'), );

	$form['sharedshelf']['add_from_search']['search']['search_sharedshelf'] = array('#type' => 'button', '#name' => 'search_button', '#attributes' => array('onclick' => 'return false;'), '#value' => t('Search'), '#ajax' => array('callback' => 'media_sharedshelf_add_ajax_search_results_callback', 'wrapper' => 'sharedshelf-search-results-section', 'method' => 'replace', 'effect' => 'fade', 'keypress' => TRUE, ), );

	// Create a div that will hold the ajax callback content for the search
	// results.
	$default_search_results_title = 'Results';
	$default_search_results_description = '';
	// If the search button, previous page, or next page was clicked then update
	// the results description information.
	$search_projects = $search_field_filters = array();
	$search_project_count = 0;
	if (isset($form_state['triggering_element']) && ($form_state['triggering_element']['#name'] != 'project')) {
		// The search_projects array winds up being an associative array where the
		// project ID is both the key and value for each element.
		// So you cannot retrieve elements using indices of 0, 1, etc. For example,
		// ['180' => '180', '183' => '183']
		$search_projects = ($form_state['triggering_element']['#name'] == 'search_button') ? $form_state['values']['search_projects'] : explode(',', $form_state['values']['results_projects']);
		$search_project_count = count($search_projects);
		if ($search_project_count > 0) {
			// Get the current form values for the different search fields to retrieve
			// results from SharedShelf.
			// Perform a security check on text fields to prevent malicious code.
			foreach (media_sharedshelf_search_filter_fields() as $field) {
				$l_field = str_replace(' ', '_', drupal_strtolower($field));
				$search_field_filters[$l_field] = ($form_state['triggering_element']['#name'] == 'search_button') ? check_plain($form_state['values'][$l_field]) : check_plain($form_state['values']['results_' . $l_field]);
			}
			$search_keywords = ($form_state['triggering_element']['#name'] == 'search_button') ? check_plain($form_state['values']['keywords']) : check_plain($form_state['values']['results_keywords']);
			$default_search_results_title = 'Results for';
			// Change the DIV description to show search criteria used.
			$default_search_results_description = 'Project(s):';
			$project_names = array();
			foreach ($search_projects as $project_id) {
				$project_names[] = _media_sharedshelf_get_project_name(check_plain($project_id));
			}
			$default_search_results_description .= implode(', ', $project_names) . '<br />';
			foreach (media_sharedshelf_search_filter_fields() as $field) {
				$l_field = str_replace(' ', '_', drupal_strtolower($field));
				$default_search_results_description .= !empty($search_field_filters[$l_field]) ? $field . ': ' . $search_field_filters[$l_field] . '<br/>' : '';
			}
			$default_search_results_description .= !empty($search_keywords) ? 'Keywords: ' . $search_keywords . '<br/>' : '';
		} else {
			$default_search_results_description = 'One or more projects must be selected in order to perform a search.';
		}

		// Check to see what the value of this checkbox is and save it for future
		// use unless the search button was used to perform a new search.
		$default_select_all_search_results = ($form_state['triggering_element']['#name'] != 'search_button') ? check_plain($form_state['values']['select_all_search_results']) : 0;
	}

	$results_fieldset_description = ($default_search_results_description == '') ? 'After specifying the desired search criteria, select Search and the results will display in this area.' : '';
	$form['sharedshelf']['add_from_search']['results'] = array('#prefix' => '<div id="sharedshelf-search-results-section">', '#type' => 'fieldset', '#title' => t("@title", array('@title' => $default_search_results_title)), '#description' => t("@description", array('@description' => $results_fieldset_description)), '#suffix' => '</div>', );

	// If search button, previous page, or next page clicked then define hidden
	// fields for all search fields to be able to page through results.
	if (($search_project_count > 0) && isset($form_state['triggering_element']) && ($form_state['triggering_element']['#name'] != 'project')) {
		$form['sharedshelf']['add_from_search']['results']['results_projects'] = array('#type' => 'hidden', '#value' => implode(',', $search_projects), );
		foreach (media_sharedshelf_search_filter_fields() as $field) {
			$l_field = str_replace(' ', '_', drupal_strtolower($field));
			$form['sharedshelf']['add_from_search']['results']['results_' . $l_field] = array('#type' => 'hidden', '#value' => $search_field_filters[$l_field], );
		}
		$form['sharedshelf']['add_from_search']['results']['results_keywords'] = array('#type' => 'hidden', '#value' => $search_keywords, );
	}

	// Create the filter array needed for the search to be performed.
	$search_filters = array();
	// Retrieve a single record for each project to identify the metaData
	// fields/columns to use in the search.
	if ($search_project_count > 0) {
		foreach ($search_projects as $project_id) {
			$one_record = _media_sharedshelf_api_project_assets_get($project_id, 0, 1, TRUE);
			$search_fields = _media_sharedshelf_get_filters_mapping($one_record['metaData']);
			$filters = array();
			foreach (media_sharedshelf_search_filter_fields() as $field) {
				$l_field = str_replace(' ', '_', drupal_strtolower($field));
				// Use the real field name instead of the header for the filter search.
				$field_name = array_key_exists($field, $search_fields) ? $search_fields[$field] : $l_field;
				// If paging through search results then use hidden result field values.
				if ($search_field_filters[$l_field] != '') {
					array_push($filters, _media_sharedshelf_create_search_filter($field_name, check_plain($search_field_filters[$l_field])));
				}
			}
			if (media_sharedshelf_variable_get('published_images_only')) {
				array_push($filters, _media_sharedshelf_create_search_filter('publication_statuses.status', array('Published'), 'list'));
			}
			$search_filters[$project_id] = $filters;
		}
	}

	// Search results should be displayed if the search button, previous page, or
	// next page was selected.
	if ($search_project_count > 0) {
		$header = array('image' => t('Image'), 'project' => t('Project'), 'title' => t('Title'), 'date' => t('Date'), 'photographer' => t('Photographer'), 'creator' => t('Creator'), );

		// Check to see what the value of this checkbox is and save it for future
		// use unless the search button was used to perform a new search.
		$default_select_all_search_results = isset($form_state['values']['select_all_search_results']) ? check_plain($form_state['values']['select_all_search_results']) : $default_select_all_search_results;

		// Add a hidden field to store the current page being displayed.
		$results_current_page = ($form_state['triggering_element']['#name'] != 'search_button') ? check_plain($form_state['values']['results_current_page']) : 0;
		// If the previous/next page button was clicked then adjust the current page
		// value to be used for the selection of images.
		if ($form_state['triggering_element']['#name'] == 'previous_page_button') {
			$results_current_page = ($results_current_page > 0) ? ($results_current_page - 1) : 0;
		}
		if ($form_state['triggering_element']['#name'] == 'next_page_button') {
			$results_current_page = $results_current_page + 1;
		}
		// Keep track of checked images before displaying the current page, making
		// sure to include any previously saved checked images.
		$clicked_asset_ids = array();
		if (($form_state['triggering_element']['#name'] == 'previous_page_button') || ($form_state['triggering_element']['#name'] == 'next_page_button')) {
			// Put existing checked assets into an array so that if items are
			// unchecked as moving between pages then they can be removed from the
			// list.
			if (isset($form_state['values']['results_selected_asset_ids'])) {
				$clicked_asset_ids = explode(',', $form_state['values']['results_selected_asset_ids']);
			}
			foreach ($form_state['values']['asset_id'] as $key => $asset_id) {
				// Add a checked box to the list of selected assets if not already in
				// the list.
				if (($asset_id != '') && (!in_array($key, $clicked_asset_ids))) {
					$clicked_asset_ids[] = $key;
				}
				// In case the person has unchecked a box from a previously visited
				// page make sure it is removed if the value is empty.
				if (($asset_id == '') && (in_array($key, $clicked_asset_ids))) {
					$index = array_search($key, $clicked_asset_ids);
					if ($index !== FALSE) {
						$clicked_asset_ids = array_splice($clicked_asset_ids, $index, 1);
					}
				}
			}
		}

		// If the select all search results item checkbox is clicked then adjust the
		// hidden field that keeps track of the selected assets.
		if ($form_state['triggering_element']['#name'] == 'select_all_search_results') {
			// When checked, loop through all the search results pages and put the
			// SSID values into the clicked items array.
			if ($form_state['values']['select_all_search_results'] == '1') {
				// Loop through all the selected projects to search for matching items.
				foreach ($search_projects as $project_id) {
					// Identify the total number of project items matching the search
					// criteria and how many "pages" need to be processed.
					$search_results = _media_sharedshelf_api_project_assets_get($project_id, 0, media_sharedshelf_variable_get('search_images_per_page'), FALSE, $search_keywords, $search_filters[$project_id]);
					$number_of_pages = intval(ceil($search_results['total'] / media_sharedshelf_variable_get('search_images_per_page')));
					// Page through a project's matching search results to add them to
					// the clicked items.
					for ($pg = 0; $pg <= $number_of_pages; $pg++) {
						$starting_record = $pg * media_sharedshelf_variable_get('search_images_per_page');
						$search_results = _media_sharedshelf_api_project_assets_get($project_id, $starting_record, media_sharedshelf_variable_get('search_images_per_page'), FALSE, $search_keywords, $search_filters[$project_id]);
						$number_of_images = min(media_sharedshelf_variable_get('search_images_per_page'), $search_results['total']);
						for ($i = 0; $i < $number_of_images; $i++) {
							if (isset($search_results['assets'][$i])) {
								$ssid = $search_results['assets'][$i]['id'];
								// Check to see if this item is already added to the media so
								// it can be ignored.
								$uri = _media_sharedshelf_media_parse(media_sharedshelf_variable_get('host_server') . '/assets/' . $ssid . '/representation');
								$already_added = db_query("SELECT fid FROM {file_managed} WHERE uri LIKE :uri", array(':uri' => $uri)) -> fetchAll();
								if (count($already_added) == 0) {
									// Make sure a thumbnail exists that can be retrieve and used
									// from SharedShelf.
									if ($thumbnail = _media_sharedshelf_api_representation_size_get($search_results['assets'][$i]['id'], 0)) {
										// Make sure each item is added to the clicked items list.
										if (array_search($ssid, $clicked_asset_ids) === FALSE) {
											$clicked_asset_ids[] = $ssid;
										}
									}
								}
							}
						}
					}
				}
			}
			// When not checked, clear out the clicked items array.
			else {
				$clicked_asset_ids = array();
			}
		}

		if (($form_state['triggering_element']['#name'] == 'previous_page_button') || ($form_state['triggering_element']['#name'] == 'next_page_button') || ($form_state['triggering_element']['#name'] == 'select_all_search_results')) {
			$form['sharedshelf']['add_from_search']['results']['results_selected_asset_ids'] = array('#type' => 'hidden', '#value' => implode(',', $clicked_asset_ids), );
		}

		// Loop through projects to search on so that all search results can be
		// combined into single massive group to page through to display content.
		$images = $disabled_images = $selected_images = array();
		$projects_page_max = array();
		$max_pages = 0;
		$search_results_total_images = 0;
		foreach ($search_projects as $project_id) {
			$proj_name = _media_sharedshelf_get_project_name($project_id);
			$starting_record = $results_current_page * media_sharedshelf_variable_get('search_images_per_page');
			$search_results = _media_sharedshelf_api_project_assets_get($project_id, $starting_record, media_sharedshelf_variable_get('search_images_per_page'), TRUE, $search_keywords, $search_filters[$project_id]);
			// Get column mappings so that correct fields are displayed in results.
			$proj_columns = _media_sharedshelf_get_columns_mapping($search_results['metaData']);
			// Identify how many images will be displayed on this page of results.
			// This will depend on the number of items per page, the current page and
			// how many total images exist.
			$number_of_images = min(media_sharedshelf_variable_get('search_images_per_page'), $search_results['total']);
			// Calculate the number of result pages for the project's search.
			$number_of_pages = intval(ceil($search_results['total'] / media_sharedshelf_variable_get('search_images_per_page')));
			array_push($projects_page_max, $number_of_pages);
			$search_results_total_images += $search_results['total'];
			$max_pages = max($max_pages, $number_of_pages);
			// Set an image with metadata for each row in the search results table.
			for ($i = 0; $i < $number_of_images; $i++) {
				if (isset($search_results['assets'][$i])) {
					$ssid = $search_results['assets'][$i]['id'];

					// Check to see if this item is already added to the media so it can
					// be disabled.
					$uri = _media_sharedshelf_media_parse(media_sharedshelf_variable_get('host_server') . '/assets/' . $ssid . '/representation');
					$already_added = db_query("SELECT fid FROM {file_managed} WHERE uri LIKE :uri", array(':uri' => $uri)) -> fetchAll();
					if (count($already_added) != 0) {
						$disabled_images[$ssid] = TRUE;
					}

					// Always use the smallest thumbnail size for search results so as to
					// get the best performance.
					if ($thumbnail = _media_sharedshelf_api_representation_size_get($search_results['assets'][$i]['id'], 0)) {
						$thumbnail_image = '<img src="data:' . $thumbnail['mimetype'] . ';base64,' . base64_encode($thumbnail['bytestream']) . '"' . ' alt="' . $search_results['assets'][$i]['filename'] . '"><br/>';
						// If disabling this image selection of then indicate the item is
						// already added.
						if (!isset($disabled_images[$ssid])) {
							$thumbnail_image .= $ssid;
						} else {
							$thumbnail_image .= 'Already added!';
						}
					} else {
						$thumbnail_image = 'Image Not Found!<br/><img src=""' . ' alt="' . $search_results['assets'][$i]['filename'] . '"><br/>' . $ssid;
						// If there is no image then do not allow the item to be selected
						// and added.
						$disabled_images[$ssid] = TRUE;
					}
					// Creator may require some additional work to successfully pull data
					// for display since it could be a multi value field???
					$creator = MEDIA_SHAREDSHELF_NOT_APPLICABLE;
					if (isset($proj_columns['Creator'])) {
						if (stripos($proj_columns['Creator'], '_lookup') !== FALSE) {
							if (isset($search_results['assets'][$i][$proj_columns['Creator']]['display_value'])) {
								$creator = $search_results['assets'][$i][$proj_columns['Creator']]['display_value'];
							}
						} else {
							if (isset($search_results['assets'][$i][$proj_columns['Creator']])) {
								$creator = $search_results['assets'][$i][$proj_columns['Creator']];
							}
						}
					}
					// Photographer may require some additional work to successfully pull
					// data for display since it could be a multi value field???
					$photographer = MEDIA_SHAREDSHELF_NOT_APPLICABLE;
					if (isset($proj_columns['Photographer'])) {
						if (stripos($proj_columns['Photographer'], '_lookup') !== FALSE) {
							if (isset($search_results['assets'][$i][$proj_columns['Photographer']]['display_value'])) {
								$photographer = $search_results['assets'][$i][$proj_columns['Photographer']]['display_value'];
							}
						} else {
							if (isset($search_results['assets'][$i][$proj_columns['Photographer']])) {
								$photographer = $search_results['assets'][$i][$proj_columns['Photographer']];
							}
						}
					}
					if (isset($search_results['assets'][$i][$proj_columns['Title']])) {
						$title = $search_results['assets'][$i][$proj_columns['Title']];
					} else {
						$title = MEDIA_SHAREDSHELF_NOT_APPLICABLE;
					}
					if (isset($search_results['assets'][$i][$proj_columns['Date']])) {
						$date = $search_results['assets'][$i][$proj_columns['Date']];
					} else {
						$date = MEDIA_SHAREDSHELF_NOT_APPLICABLE;
					}
					$images[$ssid] = array('image' => $thumbnail_image, 'project' => t("@proj", array('@proj' => $proj_name)), 'title' => t("@title", array('@title' => $title)), 'date' => t("@date", array('@date' => $date)), 'photographer' => t("@photographer", array('@photographer' => $photographer)), 'creator' => t("@creator", array('@creator' => $creator)), );
					if (!$default_select_all_search_results) {
						$selected_images[$ssid] = (in_array($ssid, $clicked_asset_ids)) ? TRUE : FALSE;
					} else {
						$selected_images[$ssid] = TRUE;
					}
				}
			}
		}
		if ($search_results_total_images > 0) {
			$default_search_results_description .= $search_results_total_images . ' items found matching this criteria.<br />';
		}
		$page_x_of_max = '';
		if ($max_pages > 0) {
			$temp_page = $results_current_page + 1;
			$page_x_of_max = t('Page') . ' ' . $temp_page . ' ' . t('of') . ' ' . $max_pages . t('.') . '<br />';
		}

		// Include information about the number of items found and the total pages.
		$form['sharedshelf']['add_from_search']['results']['search_results_info'] = array('#prefix' => '<div>', '#type' => 'fieldset', '#description' => t("!description !page", array('!description' => $default_search_results_description, '!page' => $page_x_of_max)), '#suffix' => '</div>', );

		// Provide a checkbox to select/unselect all items contained in the search
		// results.
		$form['sharedshelf']['add_from_search']['results']['select_all_search_results'] = array('#type' => 'checkbox', '#name' => 'select_all_search_results', '#title' => t('Select/Unselect all search result items.'), '#default_value' => $default_select_all_search_results, '#return_value' => '1', '#attributes' => array('title' => t('Select/Unselect all items from all pages of the search results.')), '#ajax' => array('callback' => 'media_sharedshelf_add_ajax_search_results_callback', 'wrapper' => 'sharedshelf-search-results-section', 'method' => 'replace', 'effect' => 'none', ), );

		// Have prior checked boxes show as checked with paging by unsetting the
		// input values, which IS necessary when using AJAX to page through the
		// form content.
		unset($form_state['input']['asset_id']);
		$form['sharedshelf']['add_from_search']['results']['asset_id'] = array('#type' => 'tableselect', '#header' => $header, '#options' => $images, '#default_value' => $selected_images, '#empty' => t('No images found that match your criteria.'), );
		// Disable items that are already added.
		foreach ($disabled_images as $ssid => $value) {
			$form['sharedshelf']['add_from_search']['results']['asset_id'][$ssid]['#disabled'] = TRUE;
		}

		// Adjust current page to reflect maximum page allowed if it exceeds that.
		$maximum_project_page = max($projects_page_max);
		if ($results_current_page >= $maximum_project_page) {
			$results_current_page = $maximum_project_page - 1;
		}
		$form['sharedshelf']['add_from_search']['results']['results_current_page'] = array('#type' => 'hidden', '#value' => $results_current_page, );

		// Include information about the total pages.
		$form['sharedshelf']['add_from_search']['results']['total_pages'] = array('#prefix' => '<div>', '#type' => 'fieldset', '#description' => $page_x_of_max, '#suffix' => '</div>', );

		// Only display the previous button if not on the first page.
		if ($results_current_page != 0) {
			$form['sharedshelf']['add_from_search']['results']['previous_page'] = array('#type' => 'button', '#name' => 'previous_page_button', '#attributes' => array('onclick' => 'return false;'), '#value' => t('Previous'), '#ajax' => array('callback' => 'media_sharedshelf_add_ajax_search_results_callback', 'wrapper' => 'sharedshelf-search-results-section', 'method' => 'replace', 'effect' => 'fade', 'keypress' => TRUE, ), );
		}
		// Only display the next button if not on the last page.
		if ($results_current_page != ($maximum_project_page - 1)) {
			$form['sharedshelf']['add_from_search']['results']['next_page'] = array('#type' => 'button', '#name' => 'next_page_button', '#attributes' => array('onclick' => 'return false;'), '#value' => t('Next'), '#ajax' => array('callback' => 'media_sharedshelf_add_ajax_search_results_callback', 'wrapper' => 'sharedshelf-search-results-section', 'method' => 'replace', 'effect' => 'fade', 'keypress' => TRUE, ), );
		}
	}
    
    $form['sharedshelf']['add_from_search']['collection_select_search'] = media_sharedshelf_collection_select();   // See media_sharedshelf.module
    
	$form['sharedshelf']['add_from_search']['add_results'] = array('#type' => 'submit', '#name' => 'add_search_results', '#value' => t('Add'), );

	return $form;
}

/**
 * Refresh project image set selection list depending on project value selected.
 *
 * @param array $form
 *   The form content.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The part of the form to be refreshed.
 */
function media_sharedshelf_add_ajax_select_image_set_callback($form, &$form_state) {
	return $form['sharedshelf']['add_project_imageset']['project_sets'];
}

/**
 * Refresh search results fieldset after search so items can be selected.
 *
 * @param array $form
 *   The form content.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The part of the form to be refreshed.
 */
function media_sharedshelf_add_ajax_search_results_callback($form, &$form_state) {
	// Projects need to be selected in order to perform any sort of search.
	if ($form_state['triggering_element']['#name'] == 'search_button') {
		module_load_include('inc', 'media_sharedshelf', 'includes/media_sharedshelf.utilities');
		$projects = _media_sharedshelf_get_projects();
		if (count($form_state['values']['search_projects']) > 0) {
			// Project values from the selection list need to match those the user
			// has access to.
			foreach ($form_state['values']['search_projects'] as $id) {
				if (!array_key_exists($id, $projects)) {
					form_set_error('projects', $id . ' ' . t('is an invalid project ID.'));
				}
			}
		}
	}
	// Make sure a project exists in the search criteria when paging through
	// results.
	elseif (($form_state['triggering_element']['#name'] == 'previous_page_button') || ($form_state['triggering_element']['#name'] == 'previous_page_button')) {
		if ($form_state['values']['results_projects'] == '') {
			form_set_error('projects', t('Project information seems to be lost. Please perform the search again.'));
		}
	}
	// If the checkbox to select all search result items is clicked/triggers the
	// reload then check its value.
	elseif ($form_state['triggering_element']['#name'] == 'select_all_search_results') {
		// If the box is unchecked then we should clear out the value of the hidden
		// field holding the checked item SSIDs.
		if ($form_state['values']['select_all_search_results'] != '1') {
			$form_state['values']['results_selected_asset_ids'] = '';
		}
	}
	return $form['sharedshelf']['add_from_search']['results'];
}

/**
 * Validate and save the form data entered in the API authentication form.
 *
 * Validation includes checking to see if the email and password can
 * successfully connect to the SharedShelf API. If successfully connnected
 * the required cookies for further API calls are saved for future use.
 *
 * @global string $_media_sharedshelf_cookies
 *   Cookies sent after authenticating SharedShelf to be included in calls back.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The state of the form.
 */
function media_sharedshelf_api_form_validate($form, &$form_state) {
	global $_media_sharedshelf_cookies;
	$errors = FALSE;
	// Make sure that the host server is one of the allowed values.
	$host = $form_state['values'][media_sharedshelf_variable_name('host_server')];
	if (!array_key_exists($host, media_sharedshelf_host_servers())) {
		form_set_error('host_server', t('You have selected an invalid SharedShelf server.'));
		$errors = TRUE;
	}
	// Make sure the email address is a valid form.
	$email = $form_state['values'][media_sharedshelf_variable_name('login_email')];
	if (!valid_email_address($email)) {
		form_set_error('login_email', t('The format of your email address is invalid.'));
		$errors = TRUE;
	}
	// Make sure the password field is not empty.
	$pwd = $form_state['values'][media_sharedshelf_variable_name('login_password')];
	if (trim($pwd) == '') {
		form_set_error('login_password', t('You must specify the password for your SharedShelf account in order to retreive content from the server.'));
		$errors = TRUE;
	}
	if (!$errors) {
		// Save the email and password since they are not empty.
		media_sharedshelf_variable_set('login_email', $email);
		media_sharedshelf_variable_set('login_password', $pwd);
		module_load_include('inc', 'media_sharedshelf', 'includes/media_sharedshelf.utilities');
		// Login using the credentials from the admin settings form.
		$_media_sharedshelf_cookies = _media_sharedshelf_api_account_post($email, $pwd);
	}
}

/**
 * Test the connection to the Shared Shelf server.
 * @param type $form
 * @param type $form_state
 */
function media_sharedshelf_api_form_connect_to_server($form, &$form_state) {
	global $_media_sharedshelf_cookies;
	module_load_include('inc', 'media_sharedshelf', 'includes/media_sharedshelf.utilities');
	// Check to see if a session cookie was successfully generated.
	$connect = _media_sharedshelf_api_account_get();
	// Make sure logged in and that the user is the same as the one on the form.
	if (isset($connect['logged_in'])) {
		if (($connect['logged_in'] == 1) && ($connect['username'] == media_sharedshelf_variable_get('login_email'))) {
			drupal_set_message(t('Successfully established a connection to SharedShelf.'));
		} else {
			drupal_set_message(t('Login not successful. Please re-enter your email and password settings.'), 'error');
		}
	} else {
		drupal_set_message(t('Cannot establish connection to SharedShelf. Please check your settings.'), 'error');
	}

}

/**
 * Validates and saves the default settings to use for SharedShelf.
 *
 * @global string $_media_sharedshelf_cookies
 *   Cookies sent after authenticating SharedShelf to be included in calls back.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The state of the form.
 */
function media_sharedshelf_settings_form_validate($form, &$form_state) {
	// Make sure the local cache image size is one of the allowed values.
	$local_cache_image_size = $form_state['values'][media_sharedshelf_variable_name('local_cache_image_size')];
	if (!array_key_exists($local_cache_image_size, media_sharedshelf_image_sizes())) {
		form_set_error('local_cache_image_size', t('You have selected an invalid local cache image size.'));
	}
	// Make sure that the number of images per page is one of the allowed values.
	$images_per_page = $form_state['values'][media_sharedshelf_variable_name('search_images_per_page')];
	if (!array_key_exists($images_per_page, media_sharedshelf_number_images_per_page())) {
		form_set_error('search_images_per_page', t('You have selected an invalid number of images per page.'));
	}
	module_load_include('inc', 'media_sharedshelf', 'includes/media_sharedshelf.utilities');
	// Make sure that if a value exists for the default project then it needs to
	// be a valid project.
	if ($form_state['values'][media_sharedshelf_variable_name('default_project')] != 0) {
		if (!_media_sharedshelf_project_exists($form_state['values'][media_sharedshelf_variable_name('default_project')])) {
			form_set_error('default_project', t('Please select a valid project from the list.'));
		}
	}
}

/**
 * Validation for media_sharedshelf_add().
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The state of the form.
 */
function media_sharedshelf_add_validate($form, &$form_state) {
	module_load_include('inc', 'media_sharedshelf', 'includes/media_sharedshelf.utilities');
	if ($form_state['triggering_element']['#name'] == 'add_project_imagesets') {
		if (!_media_sharedshelf_project_exists($form_state['values']['project'])) {
			form_set_error('project', t('Please select a valid project from the list.'));
		} else {
			$project_id = $form_state['values']['project'];
			$project_name = _media_sharedshelf_get_project_name($project_id);
			if (isset($form_state['values']['image_sets']) && (count($form_state['values']['image_sets']) > 0)) {
				foreach ($form_state['values']['image_sets'] as $image_set_id) {
					if (!_media_sharedshelf_project_asset_group_exists($project_id, $image_set_id)) {
						_media_sharedshelf_error_log($project_id . ': ' . $image_set_id);
						form_set_error('image_sets', t('Please choose valid image sets for the @project project selected.', array('@project' => $project_name)));
						continue;
					}
				}
			}
		}
	} elseif ($form_state['triggering_element']['#name'] == 'add_image') {
	    $form_state['values']['ssid'] = trim($form_state['values']['ssid']);
		// SSID is an all numeric format.
		if (!preg_match('@^\d+$@', $form_state['values']['ssid'])) {
			form_set_error('ssid', t('Please enter digits for the SharedShelf image ID.'));
		} else {
			if (!_media_sharedshelf_asset_exists($form_state['values']['ssid'])) {
				form_set_error('ssid', t('The SharedShelf ID @ssid does not exist.', array('@ssid' => $form_state['values']['ssid'])));
			}
		}
	} elseif ($form_state['triggering_element']['#name'] == 'add_search_results') {
		// @TODO Validate the checkbox entry exists for dynamic project retrieval?
		// @TODO Validate the checkbox exists to dynamically save search criteria?
		// Project values from the selection list need to match those the user has
		// access to.
		$projects = _media_sharedshelf_get_projects();
		if (count($form_state['values']['search_projects']) > 0) {
			foreach ($form_state['values']['search_projects'] as $id) {
				if (!array_key_exists($id, $projects)) {
					form_set_error('projects', $id . ' ' . t('is an invalid project ID.'));
				}
			}
		} else {
			form_set_error('projects', t('One or more projects must be selected in order to perform a search.'));
		}
	}
}

/**
 * Form submission for media_sharedshelf_add().
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The state of the form.
 */
function media_sharedshelf_add_submit($form, &$form_state) {
	if ($form_state['triggering_element']['#name'] == 'add_project_imagesets') {
	    $form_state['values']['collection_id'] = $form_state['values']['collection_select_project'];
		media_sharedshelf_add_project_image_sets_submit($form, $form_state);
	} elseif ($form_state['triggering_element']['#name'] == 'add_image') {
        $form_state['values']['collection_id'] = $form_state['values']['collection_select_id'];
		media_sharedshelf_add_ssid_submit($form, $form_state);
	} elseif ($form_state['triggering_element']['#name'] == 'add_search_results') {
        $form_state['values']['collection_id'] = $form_state['values']['collection_select_search'];
		media_sharedshelf_add_search_submit($form, $form_state);
	}
	cache_clear_all('*', 'cache_views_data', TRUE);
}

/**
 * Submission for media_sharedshelf_add project image sets tab.
 *
 * This will create file objects for all the SharedShelf images associated with
 * the project and sets selected.
 * @TODO Adjust this method to save a project/image set reference if checked?
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The state of the form.
 */
function media_sharedshelf_add_project_image_sets_submit($form, &$form_state) {
	module_load_include('inc', 'media_sharedshelf', 'includes/media_sharedshelf.utilities');
	$project_id = $form_state['values']['project'];
	$project_name = _media_sharedshelf_get_project_name($project_id);
	$asset_groups = (isset($form_state['values']['image_sets'])) ? $form_state['values']['image_sets'] : array();
	$reimport_str = ($form_state['values']['reimport_metadata'] == 1) ? "and updated" : "without updating metadata";
	// If asset groups were selected then add all images associated with each
	// asset group. Otherwise add all images associated with the project selected.
	if (count($asset_groups) > 0) {
		// For each asset group add its images.

		foreach ($asset_groups as $asset_group_id) {
			$info = _media_sharedshelf_api_asset_group_assets_get($asset_group_id, 0, media_sharedshelf_variable_get('search_images_per_page'));
			$asset_group_name = _media_sharedshelf_get_asset_group_name($project_id, $asset_group_id);
			if (isset($info['success']) && $info['success']) {
				$page_count = (media_sharedshelf_variable_get('search_images_per_page') < $info['total']) ? intval($info['total'] / media_sharedshelf_variable_get('search_images_per_page')) : 0;
				if (($info['total'] % media_sharedshelf_variable_get('search_images_per_page')) != 0) {
					$page_count = $page_count + 1;
				}
				$i = $image_error_count = 0;
				do {
					foreach ($info['assets'] as $asset) {
						if (_media_sharedshelf_is_pdf($asset['id']) || _media_sharedshelf_full_size_image_exists($asset['id'])) {
							$error_msg = 'An error occurred in set ' . $asset_group_name . ' in project ' . $project_name . ' for SharedShelf image with SSID ' . $asset['id'] . ' and the file was not saved.';
							if (media_sharedshelf_add_media_object($asset['id'], $error_msg, $form, $form_state) === FALSE) {
								$image_error_count++;
							}
						}
					}
					$i = $i + 1;
					if ($i != $page_count) {
						$starting_record = $i * media_sharedshelf_variable_get('search_images_per_page');
						$info = _media_sharedshelf_api_asset_group_assets_get($asset_group_id, $starting_record, media_sharedshelf_variable_get('search_images_per_page'));
					}
				} while ($i < $page_count);
				if ($image_error_count == 0) {
					drupal_set_message(check_plain(t('All images for the !assetgroupname set in the !projectname project were successfully added.', array('!assetgroupname' => $asset_group_name, '!projectname' => $project_name))));
                    
                        if (isset($form_state['values']['collection_id'])) {
                            if ($node = node_load($form_state['values']['collection_id'])) {
                                 drupal_set_message("Resource added to the {$node->type}: <a href=\"" . url("node/{$node->nid}") . "\">{$node->title}</a>.");
                            }
                        }
				} else {
					$errors = array('@errorcount' => $image_error_count, '!assetgroupname' => $asset_group_name, '!projectname' => $project_name, );
					drupal_set_message(check_plain(t('There were @errorcount problems adding images for the !assetgroupname set in the !projectname project. Please view your site log for more details.', $errors), 'error'));
				}
			} else {
				drupal_set_message(check_plain(t('There was a problem accessing the images for the !assetgroupname set in the !projectname project.', array('!assetgroupname' => $asset_group_name . '', '!projectname' => $project_name)), 'error'));
			}
		}
	} else {
		// Add all the project's images.
		$info = _media_sharedshelf_api_project_assets_get($project_id, 0, media_sharedshelf_variable_get('search_images_per_page'));
		if (isset($info['success']) && $info['success']) {
			$page_count = (media_sharedshelf_variable_get('search_images_per_page') < $info['total']) ? intval($info['total'] / media_sharedshelf_variable_get('search_images_per_page')) : 0;
			if (($info['total'] % media_sharedshelf_variable_get('search_images_per_page')) != 0) {
				$page_count = $page_count + 1;
			}
			$i = $image_error_count = $act = 0;
			do {
				foreach ($info['assets'] as $asset) {
					$act++;
					//$ssid_url = media_sharedshelf_variable_get('host_server') . '/assets/' . $asset['id'] . '/representation';
					$error_msg = 'An error occurred with project ' . $project_name . ' for SharedShelf image with SSID ' . $asset['id'] . ' and the file was not saved.';
					// Make sure asset has image before allowing it to be added.
					if (_media_sharedshelf_is_pdf($asset['id']) || _media_sharedshelf_full_size_image_exists($asset['id'])) {
						if (media_sharedshelf_add_media_object($asset['id'], $error_msg, $form, $form_state) === FALSE) {
							$image_error_count++;
						} 
					} 
				}
				$i = $i + 1;
				if ($i != $page_count) {
					$starting_record = $i * media_sharedshelf_variable_get('search_images_per_page');
					$info = _media_sharedshelf_api_project_assets_get($project_id, $starting_record, media_sharedshelf_variable_get('search_images_per_page'));
				}
			} while ($i < $page_count);
			if ($image_error_count == 0) {
				drupal_set_message(check_plain(t('All images for the !projectname project were successfully added.', array('!projectname' => $project_name))));
                
                if (isset($form_state['values']['collection_id'])) {
                    if ($node = node_load($form_state['values']['collection_id'])) {
                         drupal_set_message("Resource added to the {$node->type}: <a href=\"" . url("node/{$node->nid}") . "\">{$node->title}</a>.");
                    }
                }
			} else {
				drupal_set_message(check_plain(t('There were @errorcount problems adding some of the images for the !projectname project.', array('@errorcount' => $image_error_count, '!projectname' => $project_name)), 'error'));
			}
			drupal_set_message(($act - $image_error_count) . " resources successfully imported " . $reimport_str);
		} else {
			drupal_set_message(check_plain(t('There was a problem accessing the images for the !projectname project.', array('!projectname' => $project_name)), 'error'));
		}
	}

	$redirect = 'admin/content/media/add/media_sharedshelf';
	if (isset($_GET['render']) && ($_GET['render'] == 'overlay')) {
		$redirect = '#overlay=?q=' . $redirect;
	}
	$form_state['redirect'] = !empty($form_state['values']['redirect']) ? $form_state['values']['redirect'] : $redirect;
}

/**
 * Submission for an individual image using the SSID found in SharedShelf.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The state of the form.
 */
function media_sharedshelf_add_ssid_submit($form, &$form_state) {

	//$ssid_url = media_sharedshelf_variable_get('host_server') . '/assets/' . $form_state['values']['ssid'] . '/representation';
	$error_msg = 'An error occurred with SharedShelf image ID ' . $form_state['values']['ssid'] . 'and no file was saved.';
	// Make sure asset has image before allowing it to be added.
	module_load_include('inc', 'media_sharedshelf', 'includes/media_sharedshelf.utilities');
	if (_media_sharedshelf_is_pdf($form_state['values']['ssid']) || _media_sharedshelf_full_size_image_exists($form_state['values']['ssid'])) {
		if (media_sharedshelf_add_media_object($form_state['values']['ssid'], $error_msg, $form, $form_state) !== FALSE) {
			drupal_set_message("Resource {$form_state['values']['ssid']} was successfully imported by its ID.");
            if (isset($form_state['values']['collection_id'])) {
                if ($node = node_load($form_state['values']['collection_id'])) {
                    drupal_set_message("Resource added to the {$node->type}: <a href=\"" . url("node/{$node->nid}") . "\">{$node->title}</a>.");
                }
            }
		} else {
			drupal_set_message("There was a problem importing resource {$form_state['values']['ssid']}.");
		}
	}
	// $redirect = 'media/' . $file->fid;
	$redirect = 'admin/content/media/add/media_sharedshelf';
	if (isset($_GET['render']) && ($_GET['render'] == 'overlay')) {
		$redirect = '#overlay=?q=' . $redirect;
	}
	$form_state['redirect'] = !empty($form_state['values']['redirect']) ? $form_state['values']['redirect'] : $redirect;
}

/**
 * Submission for media_sharedshelf_add search tab.
 *
 * This will create file objects for all the SharedShelf images associated with
 * the search query specified or the results selected.
 * @TODO Save a search reference for dynamic display later.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The state of the form.
 */
function media_sharedshelf_add_search_submit($form, &$form_state) {
	module_load_include('inc', 'media_sharedshelf', 'includes/media_sharedshelf.utilities');
	$image_count = $image_error_count = 0;
	// If there are asset IDs that were checked off then these need to be saved
	// as images.
	$current_page_asset_ids = array();
	if ((isset($form_state['values']['asset_id'])) && (count($form_state['values']['asset_id']) > 0)) {
		foreach ($form_state['values']['asset_id'] as $key => $asset_id) {
			$current_page_asset_ids[$key] = $asset_id;
			if ($asset_id != '') {
				$ssid_url = media_sharedshelf_variable_get('host_server') . '/assets/' . $key . '/representation';
				$error_msg = 'An error occurred with SharedShelf image ID ' . $key . 'and no file was saved.';
				// Make sure asset has image before allowing it to be added.
				if (_media_sharedshelf_is_pdf($asset_id) || _media_sharedshelf_full_size_image_exists($key)) {
					$image_count++;
					if (media_sharedshelf_add_media_object($key, $error_msg, $form, $form_state) === FALSE) {
						$image_error_count++;
					}
				}
			}
		}
	}
	// Now check to make sure that items checked from any paging in the search
	// results get added.
	if (isset($form_state['values']['results_selected_asset_ids']) && ($form_state['values']['results_selected_asset_ids'] != '')) {
		$selected_asset_ids = explode(',', $form_state['values']['results_selected_asset_ids']);
		foreach ($selected_asset_ids as $asset_id) {
			// Only add checked search results saved in the hidden field if they were
			// not already included in the values already submitted when add clicked
			// from the current search results page.
			if (!array_key_exists($asset_id, $current_page_asset_ids)) {
				$ssid_url = media_sharedshelf_variable_get('host_server') . '/assets/' . $asset_id . '/representation';
				$error_msg = 'An error occurred with SharedShelf image ID ' . $asset_id . 'and no file was saved.';
				// Make sure asset has image before allowing it to be added.
				if (_media_sharedshelf_is_pdf($asset_id) || _media_sharedshelf_full_size_image_exists($asset_id)) {
					$image_count++;
					if (media_sharedshelf_add_media_object($asset_id, $error_msg, $form, $form_state) === FALSE) {
						$image_error_count++;
					}
				}
			}
		}
	}
	// Indicate how many errors occurred.
	if ($image_error_count > 0) {
		_media_sharedshelf_error_log($image_error_count . ' ShareShelf images out of ' . $image_count . ' could not be added.');
	}
	drupal_set_message(check_plain(t('@count SharedShelf images were successfully added.', array('@count' => ($image_count - $image_error_count)))));
    if (isset($form_state['values']['collection_id'])) {
        if ($node = node_load($form_state['values']['collection_id'])) {
             drupal_set_message("Resource added to the {$node->type}: <a href=\"" . url("node/{$node->nid}") . "\">{$node->title}</a>.");
        }
    }
}

/**
 * Adds an item to the media collection.
 *
 * @param string $url
 *   The internal media uri for the Shared Shelf item.
 * @param string $error_message
 *   The error message to display if the item fails to save to the database.
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The state of the form.
 *
 * @return int
 *   The record count added to the media collection. 0 is returned if the item
 *   already exists in the collection. Use === for testing because FALSE is
 *   returned if an error occurs when adding the item.
 */
function media_sharedshelf_add_media_object($ssid, $error_message, $form, &$form_state) {
	$url = media_sharedshelf_variable_get('host_server') . '/assets/' . $ssid . '/representation';
	$success = 1;
	// Define the appropriate internal URI to use e.g., sharedshelf://a/...
	$uri = media_sharedshelf_media_parse($url);
    
    // Get desired collection association
    $collid = (isset($form_state['values']['collection_id'])) ? $form_state['values']['collection_id'] : FALSE;
    if ($collid == "None" || $collid == -1) { $collid = FALSE; }
    
	// Check to see this item is already added to the media.
	$results = db_query("SELECT fid FROM {file_managed} WHERE uri LIKE :uri", array(':uri' => $uri)) -> fetchAll();

	// If the item is not already added then add it otherwise ignore it since
	// already in the system.
	// NOTE: User interface should have indicated already added and disabled
	// the item from being checked when using search option.
	if (count($results) == 0) {
		module_load_include('inc', 'media_sharedshelf', 'includes/media_sharedshelf.utilities');
		$defaults = array('display' => TRUE, );

		//watchdog('media sharedshelf getting file for uri', $uri);
		$file = file_uri_to_object($uri);
		//watchdog('media sharedshelf file object', serialize($file));
		if (file_save($file)) {
			field_attach_submit('media', $file, $form, $form_state);
			// Make a copy of the file object to use as the media object
			// (file is a field of media and the base table). This is weird.
			// $media = clone($file);
			$file -> file = array();
			$file -> file[LANGUAGE_NONE] = array();
			$file -> file[LANGUAGE_NONE][0] = (array)$file + $defaults;
			$file -> is_new = TRUE;
			field_attach_insert('media', $file);
            if ($collid) {
                $lang = field_language('file', $file, 'field_og_collection_ref');
               $file->field_og_collection_ref[$lang] = array( array(  'target_id' => $collid,  ), );
            }
			_media_sharedshelf_add_metadata($file, $ssid);
			media_sharedshelf_create_img_derivatives($file->uri);
		} else {
			_media_sharedshelf_error_log($error_message);
			$success = FALSE;
		}
	} else {
		// Image already in Drupal.
		$success = 0;
		// If checkbox checked, reimport metadata
		if (!empty($form_state['values']['reimport_metadata']) && $form_state['values']['reimport_metadata'] == 1) {
			module_load_include('inc', 'media_sharedshelf', 'includes/media_sharedshelf.utilities');
			if ($fid = $results[0] -> fid) {
				$file = file_load($fid);
                if ($collid) {
                    $lang = field_language('file', $file, 'field_og_collection_ref');
                    $file->field_og_collection_ref[$lang] = array( array(  'target_id' => $collid,  ), );
                }
				_media_sharedshelf_add_metadata($file);
			} else {
				$success = FALSE;
			}
		} 
	}
	return $success;
}

/**
 * Function to confirm sharedshelf metadata update. Calls media_sharedshelf_update_confirm_submit
 */
function media_sharedshelf_update_confirm($form, &$form_state, $fid) {
	$file = file_load($fid);
	$fname = $file -> filename;
	$form['#file'] = $file;
	return confirm_form($form, t('Update Shared Shelf Metadata for "@fname"', array('@fname' => $fname)), url("file/$fid/edit"), t('<p>Are you sure you want to update the metadata for the image "@fname"?</p><p>This cannot be undone.</p>', array('@fname' => $fname)), t('Update'), t('Cancel'));
}

/**
 * Updates a file's sharedshelf metadata if confirmed, using _media_sharedshelf_add_metadata() from media_sharedshelf.utilities.inc
 * Returns to image file edit form
 */
function media_sharedshelf_update_confirm_submit($form, &$form_state) {
	if ($form_state['values']['confirm']) {
		$file = $form['#file'];
		$fid = $file -> fid;
		module_load_include('inc', 'media_sharedshelf', 'includes/media_sharedshelf.utilities');
		_media_sharedshelf_add_metadata($file);
		drupal_set_message(t('Metadata for @fname has been updated from Shared Shelf', array('@fname' => $file -> filename)));
	}
	$form_state['redirect'] = "file/$fid/edit";
}
