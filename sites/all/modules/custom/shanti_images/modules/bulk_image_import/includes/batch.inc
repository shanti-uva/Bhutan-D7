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

function _bulk_image_import_task_handle_error($task, $error) {
  $res = db_query(
    'UPDATE bulk_image_import_task SET errors = :error WHERE tid = :tid',
    array(
      'tid' => $task['tid'],
      'error' => $error,
    )
  );
}

function bulk_image_import_process_task($tid, &$context) {
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
    'euid' => $external_uid,
    'tid' => $tid,
  ));

  $filename = trim(preg_replace('/\s\s+/', ' ', (string) $xml->AssetProperties->Filename));
  $res = db_query(
    'SELECT * FROM bulk_image_import_task WHERE external_uid = :euid AND catalog = :catalog AND tid != :tid',
    array(
      'euid' => $external_uid,
      'catalog' => $task['catalog'],
      'tid' => $task['tid'],
    )
  );
  if($res->rowCount() >= 1) {
    $existing = db_query(
      'SELECT * FROM bulk_image_import_task WHERE external_uid = :euid AND catalog = :catalog AND node_id IS NOT NULL',
      array(
        'euid' => $external_uid,
        'catalog' => $task['catalog'],
      )
    )->fetchAssoc();
    db_query('UPDATE bulk_image_import_task SET node_id = :nid, image_linked = 1, complete = 1 WHERE tid = :tid', array(
      'nid' => $existing->nid,
      'tid' => $tid,
    ));
    watchdog(
      'shanti_images_bulk_image_import',
      "Skipping import of @filename (tid: @tid, eid: @eid)",
      array(
        '@filename' => $filename,
        '@tid' => $task['tid'],
        '@eid' => $external_uid,
      ),
      WATCHDOG_DEBUG
    );
    return;
  }

  // Create a Node
  $node = bulk_image_import_map_xml_to_node($xml);
  db_query('UPDATE bulk_image_import_task SET node_id = :nid WHERE tid = :tid', array(
    'nid' => $node->nid,
    'tid' => $tid
  ));
  // Download the image to the temp directory
  $auth = $context['results']['auth'];
  $folder_id = $context['results']['folder_id'];
  $filename = trim(preg_replace('/\s\s+/', ' ', (string) $xml->AssetProperties->Filename));
  try {
    $file = bulk_image_import_download_box_file($auth, $filename, $folder_id);
  }
  catch (Exception $e) {
    _bulk_image_import_task_handle_error($task, "Could not download Box file. Reason: " . $e->getMessage());
    return;
  }
  db_query('UPDATE bulk_image_import_task SET image_linked = 1 WHERE tid = :tid', array('tid' => $tid));
  $siid = _shanti_images_create_record(
    $node->nid,
    $file->fid,
    $filename,
    (integer) $xml->MediaProperties->Width,
    (integer) $xml->MediaProperties->Height
  );
  $res = shanti_images_upload_iiif($node->nid, $file->fid, $siid);
  if (!$res) {
    _bulk_image_import_task_handle_error($task, "Could not convert Box file");
    return;
  }
  $collection_id = $context['results']['collection_id'];
  if ($collection_id != 0) {
    $node->field_og_collection_ref['und'][0]['target_id'] = $collection_id;
  }
  node_save($node);

  db_query('UPDATE bulk_image_import_task SET complete = 1 WHERE tid = :tid', array('tid' => $tid));
}
