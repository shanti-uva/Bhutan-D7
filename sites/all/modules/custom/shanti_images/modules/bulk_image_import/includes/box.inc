<?php

function bulk_image_import_make_box_request($url, $options, &$auth) {
  $should_refresh = (($auth['expires_at'] - 90) - time()) <= 0;
  if ($should_refresh) {
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
  $data = drupal_json_decode($response->data);
  if (empty($response->error)) {
    $data['expires_at']  = time() + $data['expires_in'];
    $auth = $data;
    return;
  } else {
    watchdog('shanti_images_bulk_image_import', 'Error while refreshing token @refresh_token (@error): @error_description', array('@refresh_token' => $refresh_token, '@error' => $data['error'], '@error_description' => $data['error_description']), WATCHDOG_ERROR);
    drupal_access_denied();
  }
}

function bulk_image_import_find_box_folder($catalog_name, &$context) {
  $folder_id;
  $access_token = $context['results']['auth']['access_token'];
  $folder_contents = bulk_image_import_fetch_folder_contents(
    $access_token,
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


// h/t: http://drupalsun.com/patrick/2013/08/22/drupal-7-how-programmatically-download-files-optionally-save-them-managed-files
function bulk_image_import_download_box_file(&$auth, $filename, $folder_id) {
  $file_id = bulk_image_import_find_box_file($auth, $filename, $folder_id);

  $url = 'https://api.box.com/2.0/files/' . $file_id. '/content';
  $options = array(
    'method' => 'GET',
    'headers' => array(
      'Authorization' => 'Bearer ' . $auth['access_token'],
    ),
    'timeout' => 120,
  );
  $response = bulk_image_import_make_box_request($url, $options, $auth);
  if($response->data == FALSE) {
    drupal_set_message('Could download Box file for this import. Reason: ' . $response->status_message, 'error');
    throw new Exception($response->status_message);
  }

  $uri = 'temporary://' . $filename;
  $path = file_stream_wrapper_uri_normalize($uri);
  $new_file = file_save_data($response->data, $path, FILE_EXISTS_REPLACE);
  // TODO handle errors
  return $new_file;
}

function bulk_image_import_find_box_file(&$auth, $filename, $folder_id) {
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
    'headers' => array(
      'Authorization' => 'Bearer ' . $access_token,
    )
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

function bulk_image_import_fetch_folder_contents($access_token, $folder_id) {
  $url = 'https://api.box.com/2.0/folders/' . $folder_id;
  $options = array(
    'method' => 'GET',
    'headers' => array(
      'Authorization' => 'Bearer ' . $access_token,
    )
  );
  $response = bulk_image_import_make_box_request($url, $options, $auth);

  $data = drupal_json_decode($response->data);
  return $data['item_collection']['entries'];
}

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
    unset($data['restricted_to']);
    $data['generated'] = time();
    $data['username'] = $user->name;

    return $data;
  } else {

    drupal_set_message('Could not authenticate with box.com. Reason: '.$data['error_description'], 'error');
    watchdog('shanti_images_bulk_image_import', 'Error while fetching access token for @username (@error): @error_description', array('@username' => $user->name, '@error' => $data['error'], '@error_description' => $data['error_description']), WATCHDOG_ERROR);
  }
}
