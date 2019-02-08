<?php

include 'map.inc';

module_load_include('inc', 'shanti_images', 'includes/shanti_images');
module_load_include('module', 'shanti_images', 'shanti_images');

function bulk_image_import_batch_finished($success, $results, $operations) {
  drupal_goto('admin/content/bulk_image_import/' . $results['group_id'] . '/review');
}

function bulk_image_import_set_context($box_auth, $group_id, $collection_id, &$context) {
  $context['results']['auth'] = $box_auth;
  $context['results']['auth']['expires_at']  = time() + $box_auth['expires_in'];
  $context['results']['group_id'] = $group_id;
  $context['results']['collection_id'] = $collection_id;
}

function _bulk_image_import_task_handle_error($task, $error, $node=NULL, $delete=FALSE) {
  $res = db_query(
    'UPDATE bulk_image_import_task SET errors = :error WHERE tid = :tid',
    array(
      'tid' => $task['tid'],
      'error' => $error,
    )
  );
  if($node) {
    if($delete) {
      node_delete($node->nid);
    }
    else {
      $node->status = NODE_NOT_PUBLISHED;
      node_save($node);
    }
  }
}

function _bulk_image_import_create_node($xml, $tid, $context) {
  $node = bulk_image_import_map_xml_to_node($xml);
  db_query('UPDATE bulk_image_import_task SET node_id = :nid WHERE tid = :tid', array(
    'nid' => $node->nid,
    'tid' => $tid
  ));
  $collection_id = $context['results']['collection_id'];
  if ($collection_id != 0) {
    $node->field_og_collection_ref['und'][0]['target_id'] = $collection_id;
  }
  node_save($node);
  return $node;
}

function _bulk_image_import_link_image_to_node($task, $node, $xml, &$context, &$auth) {
  // Download the image to the temp directory
  $filename = trim(preg_replace('/\s\s+/', ' ', (string) $xml->AssetProperties->Filename));
  // Hack for handling RAW image files
  list($dirname, $basename, $extension, $fname) = array_values(pathinfo($filename));
  if (in_array($extension, array('RAF', 'NEF', 'raf', 'nef'))) {
    $filename = "$fname.jp2";
  }
  try {
    $file = bulk_image_import_download_box_file($auth, $filename);
  }
  catch (Exception $e) {
    _bulk_image_import_task_handle_error($task, "Could not download Box file: $filename. Reason: " . $e->getMessage(), $node);
    throw($e);
  }
  if (!$file) {
    _bulk_image_import_task_handle_error($task, "Could not download Box file: $filename.", $node);
    throw(new Exception("Could not download Box file"));
  }
  watchdog('shanti_images_bulk_image_import', 'Downloaded BOX file: @filename', array(
    '@filename' => $file->filename
  ), WATCHDOG_DEBUG);
  db_query('UPDATE bulk_image_import_task SET image_linked = 1 WHERE tid = :tid', array('tid' => $task['tid']));
  $siid = _shanti_images_create_record(
    $node->nid,
    $file->fid,
    $file->filename,
    (integer) $xml->MediaProperties->Width,
    (integer) $xml->MediaProperties->Height
  );
  $res = shanti_images_upload_iiif($node->nid, $file->fid, $siid);
  if (!$res) {
    _bulk_image_import_task_handle_error($task, "Could not convert Box file", $node);
    throw(new Exception("Could not convert Box file"));
  }
  else {
    _shanti_images_expunge_image_file($node);
  }
}


function bulk_image_import_process_group($tids, $allow_duplicates, &$context) {
  $auth = &$context['results']['auth'];
  foreach($tids as $tid) {
    try {
      watchdog('shanti_images_bulk_image_import', 'Running import for @tid', array('@tid' => $tid), WATCHDOG_DEBUG);
      bulk_image_import_process_task($tid, $allow_duplicates, $auth, $context);
      watchdog('shanti_images_bulk_image_import', 'Finished import for @tid', array('@tid' => $tid), WATCHDOG_DEBUG);
    }
    catch (Exception $e){
      continue;
    }
  }
}

function bulk_image_import_process_task($tid, $allow_duplicates, &$auth, &$context) {
  $task = db_query('SELECT * from bulk_image_import_task where tid = :tid', array('tid' => $tid))->fetchAssoc();
  $xml = simplexml_load_string($task['xml_data']);
  if(!$xml){
    $message = 'Couldn\'t parse XML: ' . $task['xml_data'];
    watchdog(
      'shanti_images_bulk_image_import',
      $message,
      array(),
      WATCHDOG_ERROR
    );
    _bulk_image_import_task_handle_error($task, $message);
    return;
  }
  $external_uid = (string) $xml->AssetProperties->UniqueID;
  db_query('UPDATE bulk_image_import_task SET external_uid = :euid WHERE tid = :tid', array(
    ':euid' => $external_uid,
    ':tid' => $tid,
  ));
  if(!$allow_duplicates) {
    $dup_task = db_query(
      'SELECT * FROM bulk_image_import_task WHERE external_uid = :euid AND catalog = :catalog',
      array(
        ':euid' => $external_uid,
        ':catalog' => $task['catalog'],
      )
    )->fetchAssoc('tid');
    if($dup_task) {
      $node = NULL;
      if(!$dup_task['node_id']) {
        $node = _bulk_image_import_create_node($xml, $tid, $context);
        db_query('UPDATE bulk_image_import_task SET node_id = :nid WHERE tid IN (:tids)', array(
          ':nid' => $node->nid,
          ':tids' => array($tid, $dup_task['tid'],),
        ));
      }
      else {
        $node = node_load($dup_task['node_id']);
      }
      if(!$dup_task['image_linked']) {
        _bulk_image_import_link_image_to_node($task, $node, $xml, $context, $auth);
      }
      db_query(
        'UPDATE bulk_image_import_task SET complete = 1 WHERE tid IN (:tids)',
        array(':tids' => array($tid, $dup_task['tid'],),)
      );
    }
  }
  else {
    $node = _bulk_image_import_create_node($xml, $tid, $context);
    _bulk_image_import_link_image_to_node($task, $node, $xml, $context, $auth);
    db_query('UPDATE bulk_image_import_task SET complete = 1 WHERE tid = :tid', array(':tid' => $tid));
  }
}
