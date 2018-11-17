<?php

function bulk_image_import_make_box_request($url, $options, &$auth) {
  $should_refresh = time() > $auth['expires_at'];
  if ($should_refresh) {
    watchdog('shanti_images_bulk_image_import', 'Attempting to refresh BOX token: @refresh_token, @auth_token', array('@refresh_token' => $auth['refresh_token'], '@auth_token' => $auth['access_token'],), WATCHDOG_INFO);
    bulk_image_import_refresh_box_token($auth);
  }
  $options['headers']['Authorization'] = 'Bearer ' . $auth['access_token'];
  return drupal_http_request($url, $options);
}

function bulk_image_import_refresh_box_token(&$auth) {
  $data = array(
    'refresh_token' => $auth['refresh_token'],
    'client_id' => variable_get('box_client_id'),
    'grant_type' => 'refresh_token',
    'client_secret' => variable_get('box_client_secret'),
  );
  $options = array(
    'method' => 'POST',
    'data' => http_build_query($data, '', '&'),
    'headers' => array('Content-Type' => 'application/x-www-form-urlencoded'),
  );
  $response = drupal_http_request('https://www.box.com/api/oauth2/token', $options);
  $json_data = drupal_json_decode($response->data);
  if (empty($response->error)) {
    $json_data['expires_at']  = time() + $json_data['expires_in'];
    $auth = $json_data;
    watchdog('shanti_images_bulk_image_import', 'Successfully refreshed BOX token: @refresh_token, @auth_token', array('@refresh_token' => $auth['refresh_token'], '@auth_token' => $auth['access_token'],), WATCHDOG_INFO);
    return;
  } else {
    watchdog('shanti_images_bulk_image_import', 'Error while refreshing token @refresh_token (@error): @error_description', array('@refresh_token' => $auth['refresh_token'], '@error' => $json_data['error'], '@error_description' => $json_data['error_description']), WATCHDOG_ERROR);
    throw new Exception($json_data['error']);
  }
}

/* No longer used
function bulk_image_import_find_box_folder($catalog_name, &$context) {
  $folder_id = NULL;
  $auth = $context['results']['auth'];
  $folder_contents = bulk_image_import_fetch_folder_contents(
    $auth,
    variable_get('box_root_folder_id')
  );
  $sub_folders = array_filter($folder_contents, function($entry) {
    return $entry['type'] == 'folder';
  });
  foreach($sub_folders as $sf) {
    if(strpos($sf['name'], $catalog_name) != NULL) {
      $folder_id = $sf['id'];
      break;
    }
  }

  $context['results']['folder_id'] = $folder_id;
}
*/

// h/t: http://drupalsun.com/patrick/2013/08/22/drupal-7-how-programmatically-download-files-optionally-save-them-managed-files
function bulk_image_import_download_box_file(&$auth, $filename) {
  $file_id = bulk_image_import_find_box_file($auth, $filename);

  $url = 'https://api.box.com/2.0/files/' . $file_id. '/content';
  $options = array(
    'method' => 'GET',
    'timeout' => 120,
  );
  watchdog('shanti_images_bulk_image_import', 'Downloading BOX file: @filename', array(
    '@filename' => $filename
  ), WATCHDOG_DEBUG);
  $response = bulk_image_import_make_box_request($url, $options, $auth);
  if(!$response->data && $response->redirect_url) {
    $response = bulk_image_import_make_box_request($response->redirect_url, $options, $auth);
  }
  if(!$response->data) {
    throw new Exception($response->status_message);
  }

  $uri = 'temporary://' . $filename;
  $path = file_stream_wrapper_uri_normalize($uri);
  if(file_exists(drupal_realpath($path))) {
    $existing = file_load_multiple(array(), array('uri' => $uri));
    if(count($existing)) {
      watchdog('shanti_images_bulk_image_import', 'File already exists, skipping save.', array(), WATCHDOG_DEBUG);
      return reset($existing);
    }
  }
  else {
    return file_save_data($response->data, $path, FILE_EXISTS_REPLACE);
  }
}

function bulk_image_import_find_box_file(&$auth, $filename) {
  $access_token = $auth['access_token'];
  $url = url(
    'https://api.box.com/2.0/search',
    array(
      'query' => array(
        'query' => trim($filename),
        'scope' => 'user_content',
        'limit' => 5,
        'type' => 'file',
      )
    )
  );
  $options = array(
    'method' => 'GET',
  );
  $response = bulk_image_import_make_box_request($url, $options, $auth);

  $data = drupal_json_decode($response->data);
  if(!isset($data) || empty($data['entries'])) {
    drupal_set_message('Could not find the Box file for this import. Reason: ' . $response->status_message, 'error');
    throw new Exception($response->status_message);
  }
  $file_hits = array_filter($data['entries'], function($entry) use ($filename) {
    return $entry['name'] == $filename;
  });
  if(count($file_hits) === 1) {
    return $file_hits[0]['id'];
  } else if (count($file_hits) === 0) {
    throw new Exception("No file matching \"". $filename . "\" found.");
  } else if (count($file_hits) > 1) {
    throw new Exception("More than one file matching \"". $filename . "\" was found.");
  }
}

/* No longer used
function bulk_image_import_fetch_folder_contents(&$auth, $folder_id) {
  $url = 'https://api.box.com/2.0/folders/' . $folder_id;
  $options = array(
    'method' => 'GET',
  );
  watchdog('shanti_images_bulk_image_import', 'Fetching BOX folder contents', array(), WATCHDOG_DEBUG);
  $response = bulk_image_import_make_box_request($url, $options, $auth);

  $data = drupal_json_decode($response->data);
  return $data['item_collection']['entries'];
}
*/

// h/t: https://projectricochet.com/blog/integrating-drupal-boxcom-api
function bulk_image_import_handle_box_code($code) {
  global $base_url;

  $data = array(
    'grant_type' => 'authorization_code',
    'code' => $code,
    'client_id' => variable_get('box_client_id'),
    'client_secret' => variable_get('box_client_secret'),
  );

  $options = array(
    'method' => 'POST',
    'data' => http_build_query($data, '', '&'),
    'headers' => array('Content-Type' => 'application/x-www-form-urlencoded'),
  );

  $response = drupal_http_request('https://www.box.com/api/oauth2/token', $options);
  $data = drupal_json_decode($response->data);
  if (empty($response->error)) {
    $data['expires_at']  = time() + $data['expires_in'];
    return $data;
  } else {

    drupal_set_message('Could not authenticate with box.com. Reason: '.$data['error_description'], 'error');
    watchdog('shanti_images_bulk_image_import', 'Error while fetching access token for @username (@error): @error_description', array('@username' => $user->name, '@error' => $data['error'], '@error_description' => $data['error_description']), WATCHDOG_ERROR);
  }
}
