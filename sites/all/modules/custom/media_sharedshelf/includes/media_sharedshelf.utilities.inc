<?php
/**
 * @file
 * Utility functions for Media: SharedShelf.
 */

/**
 * Establish ARTStor SharedShelf connection and return cookies for future use.
 *
 * This makes a POST /account request to SharedShelf.
 *
 * @param string $email
 *   The email address used to log into SharedShelf.
 * @param string $password
 *   The password for the SharedShelf account.
 *
 * @return string
 *   The SharedShelf cookies needed for subsequent requests as name/value pairs
 *   with path options separated by semicolons.
 */
function _media_sharedshelf_api_account_post($email, $password) {
	$sharedshelf_cookies = '';
	$error = '';
	$options = array('data' => "email=$email&password=$password", 'method' => 'POST', 'timeout' => 15, 'headers' => array('Content-Type' => 'application/x-www-form-urlencoded'), );
	$response = drupal_http_request(url(media_sharedshelf_variable_get('host_server') . '/account'), $options);
	switch ($response->code) {
		case 200 :
			$data = json_decode($response->data, TRUE);
			// Successful access is indicated in a flag passed back in the JSON data.
			if (isset($data['success'])) {
				if ($data['success'] == 1) {
					if (isset($response->headers['set-cookie'])) {
						$cookies = explode(',', $response->headers['set-cookie']);
						if (is_array($cookies)) {
							foreach ($cookies as $cookie) {
								// Expected cookie to send back with each call is sharedshelf one.
								if (strpos($cookie, 'sharedshelf=', 0) !== FALSE) {
									$sharedshelf_cookies = $cookie;
								}
							}
							// Indicate an error if the correct cookie was not returned.
							if ($sharedshelf_cookies == '') {
								$error = 'Invalid SharedShelf cookie returned. API changes may have been made.';
							}
						} else {
							$sharedshelf_cookies = $response->headers['set-cookie'];
						}
					}
				} else {
					// First time through always seems to generate this error. It may be
					// due to some sort of Drupal cache/database/variable update delay.
					watchdog('media_sharedshelf', t('Data[success] value does not exist. Try SharedShelf API settings again.'));
				}
			} else {
				// If the credentials did not work, first check to see if the email
				// and password are not empty.
				if (($email != '') && ($password != '')) {
					$error = check_plain($data['message']) . ' Please check your authentication settings';
				} else {
					$error = 'You have not set your SharedShelf credentials. Please enter your email address and password';
				}
			}
			// Catch any error that occurred during authentication.
			if ($error != '') {
				$error_msg = t("@error in the !settings before accessing SharedShelf content.", array('@error' => $error, '!settings' => l(t('SharedShelf API administration page'), check_plain('admin/config/media/media_sharedshelf/api')), ));
				if (user_access('administer site configuration')) {
					drupal_set_message(filter_xss($error_msg), 'error');
				}
				watchdog('media_sharedshelf', $error_msg);
			}
			break;

		default :
			// If we got here there is an issue, so we want to log the error.
			$error_message = isset($response->error) ? $response->error : '';
			$status_message = isset($response->status_message) ? $response->status_message : '';
			_media_sharedshelf_error_log($error_message, $response->code, $status_message);
	}
	return $sharedshelf_cookies;
}

/**
 * Gets the user account info for the established SharedShelf connection.
 *
 * This makes a GET /account request to SharedShelf.
 *
 * @global string $_media_sharedshelf_cookies
 *   The cookies sent by SharedShelf during login that are sent with future
 *   active session requests.
 *
 * @return array
 *   An associative array:
 *     'username' - contains the email address used to login
 *     'logged_in' - 1 means the session is still valid and user logged in
 *     'user_id' - an integer value representing the user account
 *     'institution' - an integer value indicating the associated institution
 *       for the account
 */
function _media_sharedshelf_api_account_get() {
	global $_media_sharedshelf_cookies;
	$account_status = array('username' => '', 'profile_id' => 0, 'institution_id' => 0, 'admin_for' => array(), 'ga_key' => '', 'additional_institutions' => array(), 'logged_in' => 0, 'show_controlled_list_tab' => 0, );
	$options = array('headers' => array('Cookie' => $_media_sharedshelf_cookies), 'method' => 'GET');
	$sharedshelf_url = url(media_sharedshelf_variable_get('host_server') . '/account');
	$response = drupal_http_request($sharedshelf_url, $options);
	switch ($response->code) {
		case 401 :
		case 403 :
			// For access denied issues, try authenticating again with SharedShelf
			// and get new cookies. The session may have timed out. Then try the
			// request again.
			$_media_sharedshelf_cookies = _media_sharedshelf_api_account_post(media_sharedshelf_variable_get('login_email'), media_sharedshelf_variable_get('login_password'));
			$options['headers']['Cookie'] = $_media_sharedshelf_cookies;
			$response = drupal_http_request($sharedshelf_url, $options);
		case 200 :
			// Since the request may have been submitted again because of access
			// issues, make sure response is good before attempting to get data.
			if ($response->code == 200) {
				$account_status = json_decode($response->data, TRUE);
			}
			break;

		default :
			// If we got here there is an issue, so we want to log the error.
			$error_message = isset($response->error) ? $response->error : '';
			$status_message = isset($response->status_message) ? $response->status_message : '';
			_media_sharedshelf_error_log($error_message, $response->code, $status_message);
	}
	return $account_status;
}

/**
 * Gets a list of projects accessible for the user session.
 *
 * This makes a GET /projects request to SharedShelf.
 *
 * @global string $_media_sharedshelf_cookies
 *   The cookies sent by SharedShelf during login that are sent with future
 *   active session requests.
 *
 * @return array
 *   A multidimensional array where each element in the first dimension
 *   contains an associative array:
 *     'id' - integer id for project
 *     'name' - project name from SharedShelf
 *     'template_id' - integer template id relates to template used for project
 *     'adam_project_id' -
 *     'admin' -
 */
function _media_sharedshelf_api_projects_get() {
	global $_media_sharedshelf_cookies;
	$projects = array();
	$options = array('headers' => array('Cookie' => $_media_sharedshelf_cookies), 'method' => 'GET');
	$sharedshelf_url = url(media_sharedshelf_variable_get('host_server') . '/projects');
	$response = drupal_http_request($sharedshelf_url, $options);
	switch ($response->code) {
		case 401 :
		case 403 :
			// For access denied issues, try authenticating again with SharedShelf
			// and get new cookies. The session may have timed out. Then try the
			// request again.
			$_media_sharedshelf_cookies = _media_sharedshelf_api_account_post(media_sharedshelf_variable_get('login_email'), media_sharedshelf_variable_get('login_password'));
			$options['headers']['Cookie'] = $_media_sharedshelf_cookies;
			$response = drupal_http_request($sharedshelf_url, $options);
		case 200 :
			// Since the request may have been submitted again because of access
			// issues, make sure response is good before attempting to get data.
			if ($response->code == 200) {
				$projects = json_decode($response->data, TRUE);
			}
			break;

		default :
			// If we got here there is an issue, so we want to log the error.
			$error_message = isset($response->error) ? $response->error : '';
			$status_message = isset($response->status_message) ? $response->status_message : '';
			_media_sharedshelf_error_log($error_message, $response->code, $status_message);
	}
	return $projects;
}

/**
 * Gets the assets for a project.
 *
 * GET /projects/{project_id}/assets
 *
 * @global string $_media_sharedshelf_cookies
 *   The cookies sent by SharedShelf during login that are sent with future
 *   active session requests.
 *
 * @param string $project_id
 *   The project id for the assets you want.
 * @param int $start_page
 *   The starting page of assets that you want. Defaults to 0 (first page) if
 *   not specified.
 * @param int $page_size
 *   The number of images to retrieve per page. Defaults to 1 image per page.
 * @param bool $metadata
 *   Indicates if the metadata that facilitates matching internal field names
 *   to SharedShelf labels should be included in the results.
 * @param string $query
 *   Allows you to search for keyword in any field.
 * @param array $filters
 *   Allows you to filter the results by a value in a field. The array element
 *   contains an associative array with these keys:
 *     'type' - a string specifying the data type of the field e.g., "date"
 *     'field' - a string indicating the field to be used for filtering
 *     'comparison' - string indicating conditional test, eg. "lt" for less than
 *     'value' - string containing the value to use for comparison to the field
 * @param string $sort
 *   The field on which you want to sort the results.
 * @param string $sort_order
 *   The display order of the field values. Must be 'ASC' or 'DEC'.
 *
 * @return array
 *   A multidimensional array where each element contains an associative array
 *   representing an asset. Assets vary depending on the project and have index
 *   values representing field IDs, i.e. fd_5545_s. With_meta option is true
 *   and provides results that allow you to map the fd_5545_s to its label,
 *   i.e. dataIndex value 'fd_5545_s' is associated with header value 'Subject'
 */
function _media_sharedshelf_api_project_assets_get($project_id, $start_page = 0, $page_size = 1, $metadata = FALSE, $query = '', $filters = array(), $sort = '', $sort_order = 'ASC') {
	global $_media_sharedshelf_cookies;
	$result = array('total' => 0, 'success' => FALSE, 'assets' => array(), 'metaData' => array(), );
	$data = array('with_meta' => 'false', 'start' => $start_page, 'limit' => $page_size, );
	if ($metadata) {
		$data['with_meta'] = 'true';
	}
	if ($sort != '') {
		$data['sort'] = $sort;
		$data['dir'] = $sort_order;
	}
	if (count($filters) > 0) {
		$data['filter'] = json_encode($filters);
	}
	if ($query != '') {
		$data['query'] = $query;
	}
	$sharedshelf_url = url(media_sharedshelf_variable_get('host_server') . "/projects/$project_id/assets", array('query' => $data));
	$options = array('headers' => array('Cookie' => $_media_sharedshelf_cookies), 'method' => 'GET');
	$response = drupal_http_request($sharedshelf_url, $options);
	switch ($response->code) {
		case 401 :
		case 403 :
			// For access denied issues, try authenticating again with SharedShelf
			// and get new cookies. The session may have timed out. Then try the
			// request again.
			$_media_sharedshelf_cookies = _media_sharedshelf_api_account_post(media_sharedshelf_variable_get('login_email'), media_sharedshelf_variable_get('login_password'));
			$options['headers']['Cookie'] = $_media_sharedshelf_cookies;
			$response = drupal_http_request($sharedshelf_url, $options);
		case 200 :
			// Since the request may have been submitted again because of access
			// issues, make sure response is good before attempting to get data.
			if ($response->code == 200) {
				$result = json_decode($response->data, TRUE);
			}
			break;

		default :
			// If we got here there is an issue, so we want to log the error.
			$error_message = isset($response->error) ? $response->error : '';
			$status_message = isset($response->status_message) ? $response->status_message : '';
			_media_sharedshelf_error_log($error_message, $response->code, $status_message);
	}
	return $result;
}

/**
 * Gets the asset groups associated with a project.
 *
 * GET /projects/{project_id}/asset-groups
 *
 * @global string $_media_sharedshelf_cookies
 *   The cookies sent by SharedShelf during login that are sent with future
 *   active session requests.
 *
 * @param string $project_id
 *   The id for the project for which you want to get the asset groups.
 *
 * @return array
 *   An associative array containing:
 *     'results' - count of asset groups
 *     'success' - 1 if the request was successful
 *     'asset_groups' - an array of the asset groups information
 *     'metadata' - array of fields for the asset groups
 */
function _media_sharedshelf_api_project_asset_groups_get($project_id) {
	global $_media_sharedshelf_cookies;
	$result = array('total' => 0, 'success' => FALSE, 'items' => array(), 'metaData' => array(), );
	$options = array('headers' => array('Cookie' => $_media_sharedshelf_cookies), 'method' => 'GET', );
	$sharedshelf_url = url(media_sharedshelf_variable_get('host_server') . "/projects/$project_id/asset-groups");
	$response = drupal_http_request($sharedshelf_url, $options);
	switch ($response->code) {
		case 401 :
		case 403 :
			// For access denied issues, try authenticating again with SharedShelf
			// and get new cookies. The session may have timed out. Then try the
			// request again.
			$_media_sharedshelf_cookies = _media_sharedshelf_api_account_post(media_sharedshelf_variable_get('login_email'), media_sharedshelf_variable_get('login_password'));
			$options['headers']['Cookie'] = $_media_sharedshelf_cookies;
			$response = drupal_http_request($sharedshelf_url, $options);
		case 200 :
			// Since the request may have been submitted again because of access
			// issues, make sure response is good before attempting to get data.
			if ($response->code == 200) {
				$result = json_decode($response->data, TRUE);
			}
			break;

		default :
			// If we got here there is an issue, so we want to log the error.
			$error_message = isset($response->error) ? $response->error : '';
			$status_message = isset($response->status_message) ? $response->status_message : '';
			_media_sharedshelf_error_log($error_message, $response->code, $status_message);
	}
	return $result;
}

/**
 * Gets the image data along with its metadata for an asset group.
 *
 * Paging is used to access the images.
 * GET /asset-groups/{asset_group_id}/assets
 *
 * @global string $_media_sharedshelf_cookies
 *   The cookies sent by SharedShelf during login that are sent with future
 *   active session requests.
 *
 * @param string $asset_group_id
 *   The asset group identifier.
 * @param int $start_page
 *   Indicate which page of images to display. Default to 0, the first page.
 * @param int $page_size
 *   The number of images to be displayed per page. Defaults to 1 image.
 * @param bool $metadata
 *   Indicates if the metadata that facilitates matching internal field names
 *   to SharedShelf labels should be included in the results.
 * @param string $query
 *   The keyword to search for in any of the fields.
 * @param array $filters
 *   Allows filtering the result by the value in the field. The multidimensional
 *   associative array contains these fields in second dimension of the array:
 *     type - the data type of the filter field
 *     comparison - string indicating conditional test, i.e. lt for less than
 *     value - the field value to use in the comparison
 *     field - the field to be used in the filter
 * @param string $sort
 *   The name of the field to sort on
 * @param string $sort_order
 *   The way to sort on the field specified: ascending (ASC) or descending (DEC)
 *
 * @return array
 *   An associative array containing:
 *     'results' - count of asset groups
 *     'success' - 1 if the request was successful
 *     'assets' - an array of the assets information
 *     'metadata' - array of user info and field identifiers for the assets
 */
function _media_sharedshelf_api_asset_group_assets_get($asset_group_id, $start_page = 0, $page_size = 1, $metadata = FALSE, $query = '', $filters = array(), $sort = '', $sort_order = 'ASC') {
	global $_media_sharedshelf_cookies;
	$result = array('total' => 0, 'assets' => array(), 'success' => FALSE, 'metaData' => array(), );
	$data = array('with_meta' => 'false', 'start' => $start_page, 'limit' => $page_size, );
	if ($metadata) {
		$data['with_meta'] = 'true';
	}
	if ($sort != '') {
		$data['sort'] = $sort;
		$data['dir'] = $sort_order;
	}
	if (count($filters) > 0) {
		$data['filter'] = json_encode($filters);
	}
	if ($query != '') {
		$data['query'] = $query;
	}
	$sharedshelf_url = url(media_sharedshelf_variable_get('host_server') . "/asset-groups/$asset_group_id/assets", array('query' => $data));
	$options = array('headers' => array('Cookie' => $_media_sharedshelf_cookies), 'method' => 'GET');
	$response = drupal_http_request($sharedshelf_url, $options);
	switch ($response->code) {
		case 401 :
		case 403 :
			// For access denied issues, try authenticating again with SharedShelf
			// and get new cookies. The session may have timed out. Then try the
			// request again.
			$_media_sharedshelf_cookies = _media_sharedshelf_api_account_post(media_sharedshelf_variable_get('login_email'), media_sharedshelf_variable_get('login_password'));
			$options['headers']['Cookie'] = $_media_sharedshelf_cookies;
			$response = drupal_http_request($sharedshelf_url, $options);
		case 200 :
			// Since the request may have been submitted again because of access
			// issues, make sure response is good before attempting to get the data.
			if ($response->code == 200) {
				$result = json_decode($response->data, TRUE);
			}
			break;

		default :
			// If we got here there is an issue, so we want to log the error.
			$error_message = isset($response->error) ? $response->error : '';
			$status_message = isset($response->status_message) ? $response->status_message : '';
			_media_sharedshelf_error_log($error_message, $response->code, $status_message);
	}
	return $result;
}

/**
 * Gets the image for the specified thumbnail size.
 *
 * This is the byte stream of the image, not a URL. Since different image types
 * can be stored in Shared Shelf an array is returned that contains the mime
 * type and byte stream.
 *
 * @global string $_media_sharedshelf_cookies
 *   The cookies sent by SharedShelf during login that are sent with future
 *   active session requests.
 *
 * @param string $asset_id
 *   Asset identifier for the image asset that you want to view.
 * @param int $size
 *   An integer value (0-4) representing one of the 5 thumbnail sizes available.
 *
 * @return mixed
 *   If the image representation is not found false is returned. Otherwise an
 *   associative array containing:
 *     'mimetype' - the image representation's mime type
 *     'bytestream' - the content of an actual image
 */
function _media_sharedshelf_api_representation_size_get($asset_id, $size = 0) {
	global $_media_sharedshelf_cookies;
	// Check Cache for previously made calls
	$cache_var = "sharedshelf_{$asset_id}_{$size}";
	if ($cache = cache_get($cache_var)) {
		return $cache->data;
	}

	$representation = array('mimetype' => '', 'bytestream' => '');
	$options = array('headers' => array('Cookie' => $_media_sharedshelf_cookies), 'method' => 'GET');
	$sharedshelf_url = url(media_sharedshelf_variable_get('host_server') . "/assets/$asset_id/representation/size/$size");
	$response = drupal_http_request($sharedshelf_url, $options);
	switch ($response->code) {
		case 401 :
		case 403 :
			// For access denied issues, try authenticating again with SharedShelf
			// and get new cookies. The session may have timed out. Then try the
			// request again.
			$_media_sharedshelf_cookies = _media_sharedshelf_api_account_post(media_sharedshelf_variable_get('login_email'), media_sharedshelf_variable_get('login_password'));
			$options['headers']['Cookie'] = $_media_sharedshelf_cookies;
			$response = drupal_http_request($sharedshelf_url, $options);
		case 200 :
		case 404 :
			// Since the request may have been submitted again because of access
			// issues, make sure response is good before attempting to get the data.
			if ($response->code == 200) {
				$representation['mimetype'] = $response->headers['content-type'];
				$representation['bytestream'] = $response->data;
			} elseif ($response->code == 404) {
				$representation = FALSE;
			}
			break;

		default :
			// If we got here there is an issue, so we want to log the error.
			$error_message = isset($response->error) ? $response->error : '';
			$status_message = isset($response->status_message) ? $response->status_message : '';
			_media_sharedshelf_error_log($error_message, $response->code, $status_message);
	}
	//watchdog('media_sharedshelf cache', $cache_var);
	cache_set($cache_var, $representation, 'cache');
	// Set cache if it makes it here
	return $representation;
}

/**
 * Gets the metadata for an asset.
 *
 * GET /assets/{asset_id}
 *
 * @global string $_media_sharedshelf_cookies
 *   The cookies sent by SharedShelf during login that are sent with future
 *   active session requests.
 *
 * @param string $asset_id
 *   The asset id for which you want the metadata.
 *
 * @return array
 *   An associative array containing the metadata for the asset:
 *   asset - an array containing a single asset array within it.
 *   success - indicates if the object as successfully retrieved.
 */
function _media_sharedshelf_api_assets_get($asset_id) {
	global $_media_sharedshelf_cookies;
	$result = array('url' => '', 'success' => FALSE);
	$options = array('headers' => array('Cookie' => $_media_sharedshelf_cookies), 'method' => 'GET');
	$sharedshelf_url = url(media_sharedshelf_variable_get('host_server') . "/assets/$asset_id");
	$response = drupal_http_request($sharedshelf_url, $options);
	switch ($response->code) {
		case 401 :
		case 403 :
			// For access denied issues, try authenticating again with SharedShelf
			// and get new cookies. The session may have timed out. Then try the
			// request again.
			$_media_sharedshelf_cookies = _media_sharedshelf_api_account_post(media_sharedshelf_variable_get('login_email'), media_sharedshelf_variable_get('login_password'));
			$options['headers']['Cookie'] = $_media_sharedshelf_cookies;
			$response = drupal_http_request($sharedshelf_url, $options);
		case 200 :
			// Since the request may have been submitted again because of access
			// issues, make sure response is good before attempting to get the data.
			if ($response->code == 200) {
				$result = json_decode($response->data, TRUE);
			}
			break;

		default :
			// If we got here there is an issue, so we want to log the error.
			$error_message = isset($response->error) ? $response->error : '';
			$status_message = isset($response->status_message) ? $response->status_message : '';
			_media_sharedshelf_error_log($error_message, $response->code, $status_message);
	}
	return $result;
}

/**
 * Gets the URL for the full size image.
 *
 * GET /assets/{asset_id}/representation/details
 * Note: The URL returned from this call will perform a redirect to another
 * location where the full size image is located.
 *
 * @global string $_media_sharedshelf_cookies
 *   The cookies sent by SharedShelf during login that are sent with future
 *   active session requests.
 *
 * @param string $asset_id
 *   The asset id for which you want the full size image.
 *
 * @return array
 *   An associative array containing:
 *    'url' - this URL does not point directly to the full size image.
 *    'name' - the file name used at upload time to Shared Shelf.
 *    'success' - 1 indicates that the image exists.
 */
function _media_sharedshelf_api_assets_representation_details_get($asset_id) {
	global $_media_sharedshelf_cookies;
	$cache_var = "sharedshelf_repdetails_${asset_id}";
	if ($cacheval = cache_get($cache_var)) {
		$result = $cacheval->data;
		if (is_object($result)) { $result = (array)$result;
		}
		if (isset($result['url']) && isset($result['name'])) {
			return $result;
		}
	}

	$result = array('url' => '', 'name' => '', 'success' => FALSE);
	$options = array('headers' => array('Cookie' => $_media_sharedshelf_cookies), 'method' => 'GET');
	$sharedshelf_url = url(media_sharedshelf_variable_get('host_server') . "/assets/$asset_id/representation/details");
	$response = drupal_http_request($sharedshelf_url, $options);

	switch ($response->code) {
		case 401 :
		case 403 :
			// For access denied issues, try authenticating again with SharedShelf
			// and get new cookies. The session may have timed out. Then try the
			// request again.
			$_media_sharedshelf_cookies = _media_sharedshelf_api_account_post(media_sharedshelf_variable_get('login_email'), media_sharedshelf_variable_get('login_password'));
			$options['headers']['Cookie'] = $_media_sharedshelf_cookies;
			$response = drupal_http_request($sharedshelf_url, $options);

		case 200 :
			// Since the request may have been submitted again because of access
			// issues, make sure response is good before attempting to get the data.
			if ($response->code == 200) {
				$result = json_decode($response->data, TRUE);
			}
			break;

		default :
			// If we got here there is an issue, so we want to log the error.
			$error_message = isset($response->error) ? $response- error : '';
			$status_message = isset($response->status_message) ? $response->status_message : '';
			_media_sharedshelf_error_log($error_message, $response->code, $status_message);
	}
	//if (isset($response)) {dpm($response, 'response');} *
	if ($response->data == '{"success": true}') {
		$result = json_decode('{"name": "ss_noimage-0.png", "success": true, "url": "http://catalog.sharedshelf.artstor.org/images/ss_noimage-0.png"}');
	}
	if (is_object($result)) { $result = (array)$result;
	}
	cache_set($cache_var, $result, 'cache');
	return $result;
}

/**
 * Log an error that occurs. If the user is an admin, we'll display an error.
 *
 * @param string $error_msg
 *   The error message to be logged.
 * @param string $http_code
 *   Optional - the return code status of the HTTP request
 * @param string $http_status_msg
 *   Optional - the status message returned from the HTTP request
 */
function _media_sharedshelf_error_log($error_msg, $http_code = '', $http_status_msg = '') {
	$error = '';
	// If the configuration is properly set, then display the error message.
	// Include the HTTP info if passed along.
	if ($http_code != '') {
		$error .= 'HTTP response code: ' . $http_code . "\n";
	}
	if ($http_status_msg != '') {
		$error .= ' HTTP response status: ' . $http_status_msg . "\n";
	}
	$error .= $error_msg;
	if (user_access('administer site configuration')) {
		drupal_set_message(check_plain(t("@error", array('@error' => $error))), 'error');
	}
	watchdog('media_sharedshelf', $error);
}

/**
 * This will return the appropriate array key for the image size we wish.
 *
 * @param int $width
 *   Maximum pixel width of resulting image
 * @param int $height
 *   Maximum pixel height of resulting image
 */
function _media_sharedshelf_guess_size($width = 0, $height = 0) {
	$max = max($width, $height);

	if ($max) {
		foreach (media_sharedshelf_image_sizes() as $size => $value) {
			if ($max <= $value) {
				return $size;
			}
		}
	}

	// If we don't have width or height set, then get the original (full) size.
	return '5';
}

/**
 * Returns a URL for the preferred image size specified.
 *
 * @TODO Need to expand this to address project/image set or saved search?
 *
 * @param string $url
 *   Internal file entity schema representation for the image, project, saved
 *   search, or full size image.
 * @param int $width
 *   Preferred maximum image width
 * @param int $height
 *   Preferred maximum image height
 * @param bool $cached
 *   Indicates if cached content should be used.
 *
 * @return string
 *   The URI for the SharedShelf image.
 */
function _media_sharedshelf_image_url($url, $width = 0, $height = 0, $cached = TRUE) {
	// An asset ID reference for an image exists.
	if (preg_match('@sharedshelf://a/([0-9]+)@i', $url, $matches)) {
		$size = _media_sharedshelf_guess_size($width, $height);
		return _media_sharedshelf_image_url_from_size($matches[1], $size);
	}
	// A URL for the full size image was copied from SharedShelf.
	if (preg_match('@sharedshelf://l/([a-z]*)/f/([0-9a-z\-]+)@i', $url, $matches)) {
		$url = _media_sharedshelf_get_image_full_size_url($matches[1] . '/' . $matches[2]);
		return $url;
	}
}

/**
 * Returns the mime type for the image specified.
 *
 * @TODO Need to expand this to address project/image set or saved search?
 *
 * @param string $url
 *   Internal file entity schema representation for the image, project, saved
 *   search, or full size image.
 *
 * @return string
 *   The mime type of the SharedShelf image
 */
function _media_sharedshelf_get_image_mimetype($url) {
	$image_reference = '';
	// An asset ID reference for an image exists.
	if (preg_match('@sharedshelf://a/([0-9]+)@i', $url, $matches)) {
		$image_reference = $matches[1];
	}
	// A URL for the full size image was copied from SharedShelf.
	if (preg_match('@sharedshelf://l/([a-z]*)/f/([0-9a-z\-]+)@i', $url, $matches)) {
		$image_reference = $matches[1] . '/' . $matches[2];
	}
	return _media_sharedshelf_get_full_size_image_mimetype($image_reference);
}

/**
 * Returns a URL for the preferred image size.
 *
 * This means that it will create a SharedShelf API assets...representation
 * (size image) URL string when not wanting the full size image.
 *
 * @param string $asset_id
 *   The SharedShelf ID/asset ID.
 * @param int $size
 *   The preferred image size to retrieve, where 0 to 4 represent values used
 *   for API representation call and 5 indicates full size.
 *
 * @return string
 *   The URL for the specified image size for the asset id.
 */
function _media_sharedshelf_image_url_from_size($asset_id, $size = 5) {
	// Check to make sure we have a valid image asset id.
	if (is_numeric($asset_id)) {
		$asset_info = _media_sharedshelf_api_assets_representation_details_get($asset_id);
		$filepath = $asset_info['url'];
		if ($asset_info['success']) {
			if ($size < 5) {
				$filepath = media_sharedshelf_variable_get('host_server') . "/assets/$asset_id/representation/size/$size";
			}
		} else {
			_media_sharedshelf_error_log('Invalid image asset SharedShelf ID ' . $asset_id . ' specified.');
		}
		// URLize that path...
		$filepath = url($filepath, array('absolute' => TRUE));
		return $filepath;
	} else {
		return '';
	}
}

/**
 * Checks to see if the Shared Shelf resource is a PDF
 *
 * @param string $asset_id
 *   Represents the resources's SharedShelf ID.
 *
 * @return bool
 *   Returns TRUE if resource is a PDF; otherwise FALSE.
 */
function _media_sharedshelf_is_pdf($asset_id) {
	$info = _media_sharedshelf_api_assets_representation_details_get($asset_id);
	if (isset($info['type']) && $info['type'] == 'pdf') {
		return TRUE;
	} else {
		return FALSE;
	}
}

/**
 * Checks to see if the specified full size image exists.
 *
 * @param string $image_reference
 *   Represents the image's SharedShelf ID.
 *
 * @return bool
 *   Returns TRUE if the mime type indicates an image; otherwise FALSE.
 */
function _media_sharedshelf_full_size_image_exists($image_reference) {
	$mimetype = _media_sharedshelf_get_full_size_image_mimetype($image_reference);
	if (stripos($mimetype, 'image') !== FALSE) {
		return TRUE;
	}
	return FALSE;
}

/**
 * Get mimetype for full size image based on full size image URL.
 *
 * @param string $image_reference
 *   Represents the image's SharedShelf ID.
 *
 * @return string
 *   Returns the mime type of the object.
 */
function _media_sharedshelf_get_full_size_image_mimetype($image_reference) {
	$mimetype = 'application/octet-stream';
	$url = _media_sharedshelf_get_image_full_size_url($image_reference);
	if ($file_pointer = curl_init($url)) {
		if ($file_pointer !== FALSE) {
			$info = _media_sharedshelf_api_assets_representation_details_get($image_reference);
			$mimetype = file_get_mimetype($info['name']);
			return $mimetype;
		} else {
			return $mimetype;
		}
		curl_close($file_pointer);
	}
	// RFC 2046 states in section 4.5.1:
	// The octet-stream subtype is used to indicate that a body contains
	// arbitrary binary data.
	return $mimetype;
}

/**
 * Gets the URL for the full size image.
 *
 * @param string $image_reference
 *   Represents the image's SharedShelf ID.
 *
 * @return string
 *   A string containing the URL for the full size representation of the image.
 */
function _media_sharedshelf_get_image_full_size_url($image_reference) {
	global $_media_sharedshelf_cookies;
	$info = array('url' => '', 'success' => 0);
	if (is_numeric($image_reference)) {
		$info = _media_sharedshelf_api_assets_representation_details_get($image_reference);
	} else {
		_media_sharedshelf_error_log('SSID format is not valid.');
	}

	if (isset($info['success']) && $info['success']) {
		// PDFs full size is just the same url so return that
		if (isset($info['type']) && $info['type'] == 'pdf') {
			return $info['url'];
		}
		$options = array('headers' => array('Cookie' => $_media_sharedshelf_cookies), 'method' => 'GET');
		$response = drupal_http_request(url($info['url']), $options);
		switch ($response->code) {
			case 301 :
			case 303 :
			case 307 :
				// Image URL moved temporarily so redirect.
				$response = drupal_http_request(url($response->location), $options);
			default :
			// Do nothing if a different response code was returned from first call.
		}
		$url = '';
		switch ($response->code) {
			case 302 :
				// Item found but has a different location for the actual item.
				$url = $response->location;
				break;

			case -1002 :
				// The schema is missing: from testing it appears that http and the
				// domain are not included in the header Location value.
				$url = media_sharedshelf_variable_get('host_server') . $response->redirect_url;
				break;

			case 200 :
				$url = $info['url'];
				break;

			default :
				// If we got here there is an issue, so we want to log the error.
				$error_message = isset($response->error) ? $response->error : '';
				$error_message .= " ($image_reference)";
				$status_message = isset($response->status_message) ? $response->status_message : '';
				_media_sharedshelf_error_log($error_message, $response->code, $status_message);
				if (isset($response->redirect_url)) {
					_media_sharedshelf_error_log($response->redirect_url);
				}
		}
	}
	return url($url, array('absolute' => TRUE));
}

/**
 * Checks to see if an asset image exists.
 *
 * @param int $asset_id
 *   The SharedShelf ID for the image asset.
 *
 * @return bool
 *   Returns TRUE if the asset is found at SharedShelf site; otherwise FALSE.
 */
function _media_sharedshelf_asset_exists($asset_id) {
	$info = _media_sharedshelf_api_assets_get($asset_id);
	if (isset($info['success']) && $info['success']) {
		return TRUE;
	}
	return FALSE;
}

/**
 * Check if an image asset group (set) exists by getting one of its images.
 *
 * @param int $asset_group_id
 *   The SharedShelf asset group id as it exists in the API.
 *
 * @return bool
 *   Returns TRUE if an image asset is found for the asset group.
 */
function _media_sharedshelf_asset_group_exists($asset_group_id) {
	$info = _media_sharedshelf_api_asset_group_assets_get($asset_group_id, 0, 1);
	if (isset($info['success']) && $info['success']) {
		return TRUE;
	}
	return FALSE;
}

/**
 * Checks to see if a project exists by attempting to get one of its images.
 *
 * @param int $project_id
 *   The SharedShelf project id as it exists in the API.
 *
 * @return bool
 *   Returns TRUE if an image asset is found for the project.
 */
function _media_sharedshelf_project_exists($project_id) {
	$info = _media_sharedshelf_api_project_assets_get($project_id, 0, 1);
	if (isset($info['success']) && $info['success']) {
		return TRUE;
	}
	return FALSE;
}

/**
 * Checks to make sure that the projec and asset group combination exists.
 *
 * @param int $project_id
 *   The SharedShelf project id as it exists in the API.
 * @param int $asset_group_id
 *   The SharedShelf asset group id as it exists in the API.
 *
 * @return bool
 *   Returns TRUE if the image asset group is found within the project.
 */
function _media_sharedshelf_project_asset_group_exists($project_id, $asset_group_id) {
	$asset_groups = _media_sharedshelf_get_asset_groups($project_id);
	if (array_key_exists($asset_group_id, $asset_groups)) {
		return TRUE;
	}
	return FALSE;
}

/**
 * Builds an internal URI for use with the Media module.
 *
 * @TODO Need to expand this to address project/image set or saved search?
 *
 * @param array $parts
 *   Array containing the parts of the internal schema used to store the file
 *
 * @return string
 *   A Media module URI representing the SharedShelf item.
 */
function _media_sharedshelf_build_uri($parts) {
	$uri = '';
	if (isset($parts['a'])) {
		if (_media_sharedshelf_asset_exists($parts['a'])) {
			$uri = file_stream_wrapper_uri_normalize('sharedshelf://a/' . $parts['a']);
		}
	} elseif (isset($parts['f'])) {
		if (_media_sharedshelf_full_size_image_exists($parts['l'] . '/' . $parts['f'])) {
			$uri = file_stream_wrapper_uri_normalize('sharedshelf://l/' . $parts['l'] . '/f/' . $parts['f']);
		}
	}
	return $uri;
}

/**
 * Called by the hook implementation function in the module file.
 *
 * @param string $url
 *   The Shared Shelf URI for the image.
 *
 * @return string
 *   A Media module URI representation of the image (full size or thumbnail),
 *   image set, or project. Formats are sharedshelf://a/{asset_id}, etc.
 */
function _media_sharedshelf_media_parse($url) {
	$matches = array();
	// @TODO This needs to be updated to reflect the various internal schemas???
	// An asset ID reference to a full size image representation exists.
	if (preg_match('@artstor\.org/assets/([0-9]+)/representation@i', $url, $matches)) {
		return _media_sharedshelf_build_uri(array('a' => $matches[1]));
	}
	// URL for the full size image copied from SharedShelf. Two tests are checked:
	// one for URL provided in SharedShelf and other for redirected URL in case
	// someone were to get to that and copy it into Media>Add File>Web option.
	if (preg_match('@artstor\.org/([a-z]*)/([0-9a-z\-]+)@i', $url, $matches) || preg_match('@artstor\.org/([a-z]*)/([0-9a-z\-]+)\.([a-z]+)@i', $url, $matches)) {
		// @TODO Search each project and pull the asset IDs.
		// @TODO Then get the full size URL for each media asset.
		// @TODO If the full size URL matches the one passed to this function
		// @TODO then create an array with the asset ID and build a URI that way.
		// @TODO Otherwise return the existing URL passed to this function.
		// See media_sharedshelf.admin.inc, function media_sharedshelf_add
		// around this line: foreach ($search_projects as $project_id) {
		return _media_sharedshelf_build_uri(array('l' => $matches[1], 'f' => $matches[2]));
	}
}

/**
 * Retrieve an array of the projects available to this account.
 *
 * @return array
 *   An array containing where the key is the SharedShelf project ID and the
 *   value is the project name.
 */
function _media_sharedshelf_get_projects() {
	$projects = array();
	$project_info = _media_sharedshelf_api_projects_get();
	if (isset($project_info['success']) && $project_info['success']) {
		foreach ($project_info['items'] as $project) {
			$projects[$project['id']] = $project['name'];
		}
	}
	return $projects;
}

/**
 * Return the project name for a specified project id.
 *
 * @param int $project_id
 *   The SharedShelf project id as defined in the API.
 *
 * @return string
 *   The name of the project. If the project id is invalid then an empty
 *   string is returned.
 */
function _media_sharedshelf_get_project_name($project_id) {
	$project_info = _media_sharedshelf_api_projects_get();
	if (isset($project_info['success']) && $project_info['success']) {
		foreach ($project_info['items'] as $project) {
			if ($project_id == $project['id']) {
				return $project['name'];
			}
		}
	}
	return '';
}

/**
 * Returns an array of asset groups (image sets) for a project.
 *
 * @param int $project_id
 *   The SharedShelf project id as defined in the API.
 *
 * @return array
 *   An array where the key is the asset group ID and the value is the asset
 *   group name.
 */
function _media_sharedshelf_get_asset_groups($project_id) {
	$asset_groups = array();
	$asset_groups_info = _media_sharedshelf_api_project_asset_groups_get($project_id);
	if (isset($asset_groups_info['success']) && $asset_groups_info['success']) {
		foreach ($asset_groups_info['items'] as $asset_group) {
			$asset_groups[$asset_group['id']] = $asset_group['name'];
		}
	}
	return $asset_groups;
}

/**
 * Get the asset group's name from the project id and asset group id.
 *
 * @param int $project_id
 *   The SharedShelf project id as it exists in the API.
 * @param int $asset_group_id
 *   The SharedShelf asset group id as it exists in the API.
 *
 * @return string
 *   The name of the asset group. If the project and/or asset group is invalid
 *   then an empty string is returned.
 */
function _media_sharedshelf_get_asset_group_name($project_id, $asset_group_id) {
	$asset_groups_info = _media_sharedshelf_api_project_asset_groups_get($project_id);
	if (isset($asset_groups_info['success']) && $asset_groups_info['success']) {
		foreach ($asset_groups_info['items'] as $asset_group) {
			if ($asset_group_id == $asset_group['id']) {
				return $asset_group['name'];
			}
		}
	}
	return '';
}

/**
 * Retrieve a list of the predefined fields found in the search results.
 *
 * The predefined fields list will match those on the search form which are
 * filterable and return the column header and real field name.
 *
 * @param array $metadata
 *   The metaData portion of the SharedShelf results of an assets search.
 *
 * @return array
 *   Each array element has the SharedShelf column heading used as the key and
 *   the database field name as the value for example,
 *   array('Title' => 'fd_5533_s', 'Creator' => 'fd_4587').
 */
function _media_sharedshelf_get_filters_mapping($metadata) {
	$search_filters = media_sharedshelf_search_filter_fields();
	$filters = array();
	if (isset($metadata['columns'])) {
		foreach ($metadata['columns'] as $column) {
			// Only use fields that have been set up as filterable.
			if (isset($column['filterable']) && $column['filterable']) {
				if (in_array($column['header'], $search_filters)) {
					$filters[$column['header']] = $column['dataIndex'];
				}
			}
		}
	}
	return $filters;
}

/**
 * Retrieve a list of the fieldnames and their user labels.
 *
 * Allows us to display the user label instead of the cryptic fieldname.
 *
 * @param array $metadata
 *   The metaData portion of the SharedShelf results of an assets search.
 *
 * @return array
 *   Each array element has the SharedShelf column heading used as the key and
 *   the database field name as the value for example,
 *   array('Title' => 'fd_5533_s', 'Creator' => 'fd_4587').
 */
function _media_sharedshelf_get_columns_mapping($metadata) {
	$columns = array();
	if (isset($metadata['columns'])) {
		foreach ($metadata['columns'] as $column) {
			$columns[$column['header']] = $column['dataIndex'];
		}
	}
	return $columns;
}

/**
 * Get the asset id from a local file URI.
 *
 * @param string $uri
 *   The local file field URI for the image after it is added as media.
 *
 * @return mixed
 *   The asset ID for the SharedShelf image. If the URI does not contain an
 *   asset ID then FALSE is returned.
 */
function _media_sharedshelf_get_asset_id($uri) {
	// Use internal scheme to determine if local file is identifable as an asset.
	$target = file_uri_target($uri);
	$parts = explode('/', $target);
	// If an asset then return the asset id.
	if (isset($parts['0']) && ($parts[0] == 'a')) {
		return $parts[1];
	}
	return FALSE;
}

/**
 * Get the metadata for an image asset.
 *
 * @param int $asset_id
 *   The Shared Shelf ID for the image asset.
 *
 * @return array
 *   An associative array containing Shared Shelf field labels as the keys.
 */
function _media_sharedshelf_get_asset_metadata($asset_id) {
	$metadata = array();
	if (is_numeric($asset_id)) {
		// Need basic asset data to get project ID to retrieve the metadata labels.
		$data = _media_sharedshelf_api_assets_get($asset_id);
		$project_id = $data['asset'][0]['project_id'];
		// Can only get metadata with labels using a project search. So create a
		// filter for the project search that contains this asset only.
		$id_filter = array();
		array_push($id_filter, _media_sharedshelf_create_search_filter('id', $asset_id, 'numeric', 'eq'));
		$result = _media_sharedshelf_api_project_assets_get($project_id, 0, 1, TRUE, '', $id_filter);
		// Get column mappings so that correct fields are displayed in results.
		$proj_columns = _media_sharedshelf_get_columns_mapping($result['metaData']);
		// Loop through all the column mappings to create an array containing
		// useful key/values that are the same as the label in Shared Shelf.
		foreach ($proj_columns as $key => $value) {
			if (isset($result['assets'][0][$value])) {
				$metadata[$key] = $result['assets'][0][$value];
				// Get user identifier if working with created or updated admin field.
				if (($value == 'created_by') || ($value == 'updated_by')) {
					foreach ($result['metaData']['columns'] as $meta_info) {
						if ($meta_info['dataIndex'] == $value) {
							foreach ($meta_info['filter']['options'] as $user) {
								if ($user['id'] == $result['assets'][0][$value]) {
									$metadata[$key] = $user['text'];
								}
							}
						}
					}
				}
				if (stripos($value, '_lookup') !== FALSE) {
					if (is_array($result['assets'][0][$value])) {
						// Split up a display value into an array so that the user sees the
						// same as it is displayed in SharedShelf.
						if (array_key_exists('display_value', $result['assets'][0][$value])) {
							$metadata[$key] = explode('; ', $result['assets'][0][$value]['display_value']);
						}
						// Look for links to authority and create array of preferred terms.
						elseif (array_key_exists('links', $result['assets'][0][$value])) {
							$temp_array = array();
							foreach ($result['assets'][0][$value]['links'] as $links_value) {
								if (array_key_exists('data', $links_value)) {
									if (array_key_exists('preferredTerm', $links_value['data'])) {
										$temp_array[] = $links_value['data']['preferredTerm'];
									}
								}
							}
							$metadata[$key] = $temp_array;
						}
					}
				}
			}
		}
	}
	$metadata['Project ID'] = $project_id;
	return $metadata;
}

/**
 * Build a search filter array for use in retrieving content from SharedShelf.
 *
 * @param string $field
 *   The name of the SharedShelf project field to filter against.
 * @param mixed $value
 *   The value to filter the field on.
 * @param string $type
 *   The data type of the SharedShelf field. Valid values are 'string',
 *   'numeric', 'date', 'thumbnail', 'profile', and 'list'.
 * @param string $comparison
 *   The comparison to be performed with the value of the field. Valid values
 *   are 'eq', 'lt', and 'gt'. This parameter is ignored for field types 'list',
 *   'thumbnail', and 'profile'.
 *
 * @return array
 *   An associative array containing three or four keys:
 *     'field' is the field to filter on
 *     'value' is the value of the field to be used in the filter
 *     'type' is the type of the field
 *     'comparison' is the comparison to be performed, if appropriate
 */
function _media_sharedshelf_create_search_filter($field, $value, $type = 'string', $comparison = 'eq') {
	// SharedShelf values allowed for use in a filter construction.
	$comparison_type_values = array('string', 'numeric', 'date');
	$noncomparison_type_values = array('thumbnail', 'profile', 'list');
	$comparison_values = array('eq', 'lt', 'gt');
	// Create filter option.
	$filter = array();
	$filter['field'] = $field;
	// Make sure only a valid type value is specified.
	if (in_array($type, $comparison_type_values) or in_array($type, $noncomparison_type_values)) {
		$filter['type'] = $type;
	} else {
		// Default to string if an invalid value is passed.
		$filter['type'] = $comparison_type_values[0];
	}
	// Only some types take a comparison value.
	if (in_array($filter['type'], $comparison_type_values)) {
		// Make sure only a valid comparison value is set.
		if (in_array($comparison, $comparison_values)) {
			$filter['comparison'] = $comparison;
		} else {
			// Default to eq if an invalid value is passed.
			$filter['comparison'] = $comparison_values[0];
		}
	}
	// Make sure the value is converted to a string for numbers because the
	// SharedShelf filter will fail otherwise.
	if (in_array($filter['type'], $comparison_type_values)) {
		$filter['value'] = strval($value);
	} else {
		$filter['value'] = $value;
	}
	return $filter;
}

/**
 * Add the SharedShelf basic metadata to the file entity object.
 *
 * @param file_entity $file
 *   The file entity just created for which metadata should be retrieved.
 *
 * @param int $ssid
 * 	 The Shared Shelf asset ID, used for PDFs where the file stored is an image version of PDF
 */
function _media_sharedshelf_add_metadata($file, $ssid = FALSE) {

	// Attach the SharedShelf metadata to the local item and save it.
	// Get metadata for the image if we know the asset id.
	if ($ssid || $asset_id = _media_sharedshelf_get_asset_id($file->uri)) {
		$asset_id = ($ssid) ? $ssid : $asset_id;
		$data = _media_sharedshelf_get_asset_metadata($asset_id);
		// Use an entity wrapper to retrieve the fields for this file.
		$file_type = media_sharedshelf_file_type($file);
		$info_bundle = array('bundle' => $file_type[0]);
		$wrapper = entity_metadata_wrapper('file', $file, $info_bundle);
		// Loop through the basic fields and save each data value to the entity.
		$basic_fields = media_sharedshelf_basic_fields();
		// search for summary field in data and use it for alt and title fields (added by ndg8f, 2015-06-25)
		if ($sumkey = _media_sharedshelf_find_data_key($data, 'Summary')) {
			if (!empty($data[$sumkey])) {
				$ttxt = $data[$sumkey];
				if (strlen($ttxt) > 255) {
					$ttxt = substr($ttxt, 0, 253);
					$ttxt = substr($ttxt, 0, strrpos($ttxt, ' ')) . '...';
				}
				try {
					$wrapper->{'field_file_image_title_text'}->set($ttxt);
				} catch (EntityMetadataWrapperException $emwe) {
					watchdog('media_sharedshelf.utilities.inc: 1319', $emwe->getMessage());
				}
			}
		}

		foreach ($basic_fields as $info) {
			// Added by ndg8f (2015-06-25) to deal with cases where there's not an exact match
			// between drupal field label and shared shelf field name,
			// finds ss field name containing drupal field label
			$flabel = $info['settings']['label'];
			$field_value = (isset($data[$flabel])) ? $data[$flabel] : FALSE;
			if (!$field_value) {
        				$dkey = _media_sharedshelf_find_data_key($data, $flabel);
        				if ($dkey && isset($data[$dkey])) { $field_value = $data[$dkey];
				}
			}
			// End of add
			if (!empty($field_value)) {// was isset($data[$info['settings']['label']]) etc. below
				if ($info['settings']['label'] == 'Title') {
					$file->filename = $field_value;
					// Use Title field for file name (may result in multiple file nodes with the same name)
					$wrapper->{'field_file_image_alt_text'}->set($field_value);
				}
				if ($info['cardinality'] == FIELD_CARDINALITY_UNLIMITED) {
					if (is_array($field_value)) {
						$wrapper->{$info['field_name']}->set($field_value);
					} else {
						$wrapper->{$info['field_name']}->set(array($field_value));
					}
				} elseif ($info['cardinality'] == '1') {
					if (is_array($field_value)) {
						$wrapper->{$info['field_name']}->set(implode($field_value));
					} else {
						$wrapper->{$info['field_name']}->set($field_value);
					}
				}
			}
		}
		// Add thumbnail for pdfs
		/* just using sharedshelf thumbs
		if ($ssid && _media_sharedshelf_is_pdf($ssid)) {
			$thumb = _media_sharedshelf_create_pdf_thumb($ssid);

		}
*/

		// Create a single text block containing all the SharedShelf metadata
		// which will be used strictly for Solr document creation.
		$solr_search_data = '';
		foreach ($data as $label => $value) {
			$solr_search_data .= $label . ': ';
			if (is_array($value)) {
				$solr_search_data .= implode('; ', $value);
			} else {
				$solr_search_data .= $value;
			}
			$solr_search_data .= "\n";
		}
		$wrapper->{$basic_fields['solr_search_data']['field_name']}->set($solr_search_data);
		$wrapper->save();
	}
}

/**
 * Finds the first key in the data array that contains the substring
 *
 * @param array $data
 *   The shared shelf metadata array
 *
 * @param string $subst
 * 	 The substring to search for in the keys
 */
function _media_sharedshelf_find_data_key($data, $subst) {
	$dkeys = array_keys($data);
	foreach ($dkeys as $dk) {
		if (strpos($dk, $subst) > -1) {
			return $dk;
		}
	}
	return FALSE;
}

/**
 * Creates a file object for a PDF Document file thumbnail to be used in teasers and preview
 *
 * @param int $ssid
 * 	The Shared Shelf resource ID
 *
 * @return file
 * 	The file object representing the thumb image added for PDF
 *
 */
 /* Just using the direct thumb from Sharedshelf without storing on site
function _media_sharedshelf_create_pdf_thumb($ssid) {
	$dir = MEDIA_SHAREDSHELF_PDF_THUMB_FOLDER;
	if (file_prepare_directory($dir, FILE_CREATE_DIRECTORY)) {
		$ssid_url = _media_sharedshelf_get_image_full_size_url($ssid) . '_size4';
		$dest = MEDIA_SHAREDSHELF_PDF_THUMB_FOLDER . "/{$ssid}.jpg";
		$docpath = system_retrieve_file($ssid_url, $dest, FALSE, FILE_EXISTS_REPLACE);
		$file = (object) array('filename' => basename($docpath), 'filepath' => $docpath, 'filemime' => file_get_mimetype($docpath), 'filesize' => filesize($docpath), 'uid' => 1, 'status' => FILE_STATUS_PERMANENT, 'timestamp' => time(), 'uri' => $docpath, 'type' => "image", );
		drupal_write_record('file_managed', $file);
	} else {
		drupal_set_message(t('Media_sharedshelf Module could not create or write to the pdf thumbnail directory: @dir', array('@dir' => MEDIA_SHAREDSHELF_PDF_THUMB_FOLDER)), 'warning', FALSE);
	}
}
*/

/**
 * Process the raw (solr search) data from Shared Shelf to get all project-custom field values for item
 *
 * @param string $raw
 * 	The raw sharedshelf string with all field values stored as field_sharedshelf_solr_search
 *
 * @return array
 * 	An array of the processed shared shelf data in field label->value pairs.
 *
 */
function _media_sharedshelf_process_raw($raw) {
	$rar = explode("\n", $raw);
	$ssfields = array();
	foreach ($rar as $el) {
	    $field = explode(':', $el, 2);
        if (count($field) == 2) {
            $ssfields[$field[0]] = rtrim($field[1]);
        } else {
            $ssfields[$field[0]] = '';
        }
	}
	return $ssfields;
}

/**
 * Process ssdata into themed output for display in file records
 *
 * @param string $raw
 *  The raw sharedshelf string with all field values stored as field_sharedshelf_solr_search
 * @param string $type
 *  The type of file the raw data comes from, either image or pdf
 *
 * @return array
 *  An array with two main items: metadata and fields. Each of these contains an array of label->value pairs.
 *
 */
function _media_sharedshelf_process_ssdata($raw, $type = 'image') {
    $inline = ($type == 'pdf') ? TRUE : FALSE;
    $ssfields = _media_sharedshelf_process_raw($raw);
    $out = array('ssmetadata' => '', 'ssfields' => '');
    $inmeta = TRUE;
    foreach ($ssfields as $fnm => $fval) {
        $fval = rtrim($fval);
        if (empty($fnm) || empty($fval)) {
            continue;
        }
        if (strpos($fnm, '(') > -1) {
            $pts = explode('(', $fnm);
            $fnm = $pts[0];
        }
        $class = str_replace(str_split(' \\/:*?"<>|+&!,'), '-', strtolower($fnm));
        $theme_array = array('class' => 'field-name-' . $class, 'inline' => $inline, 'label' => $fnm, 'value' => $fval, );
        if ($inmeta) {
            $out['ssmetadata'] .= theme('media_sharedshelf_custom_field', $theme_array);
            if ($fnm == 'Updated By') { $inmeta = FALSE; }
        } else {
            $out['ssfields'] .= theme('media_sharedshelf_custom_field', $theme_array);
        }
    }
    return $out;
}

 /**
  * Function to create necessary image derivatives.
  */
 function _media_sharedshelf_create_img_derivatives($uri) {
    $uri = str_replace('sharedshelf://', 'public://media-sharedshelf/', $uri) . ".jpg";
    $styles = array('media_large', 'media_lightbox_large');
    foreach ($styles as $style) {
        $destination = image_style_path($style, $uri);
        $style = image_style_load($style);
        $res = image_style_create_derivative($style, $uri, $destination);
    }
 }
 