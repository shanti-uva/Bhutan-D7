<?php

include 'batch.inc';

function bulk_image_import_api_get() {
  if($_GET['filename']) {
    $result = db_query('SELECT * from bulk_image_import_task WHERE filename = :filename order by tid desc', array(
      'filename' => $_GET['filename']
    ));
    if($result->rowCount()) {
      $item = $result->fetchAssoc();
      drupal_json_output($item);
      drupal_exit();
    }
    drupal_json_output(array());
    drupal_exit();
  }
  else {
    // TODO is an endpoint for listing imports really needed?
    drupal_json_output(array());
    drupal_exit();
  }
}

function bulk_image_import_api_post() {
  $meta = array();
  $collection_id = 0;
  foreach($_POST as $key => $value) {
    if($key === 'CollectionId') {
      $collection_id = $value;
      continue;
    }
    $meta[$key] = $value;
  }
  $tid = db_insert('bulk_image_import_task')
       ->fields(array(
         'meta_data' => json_encode($meta),
         'catalog' => $meta['Catalog'],
         'filename' => $meta['Filename']
       ))
       ->execute();
  $node = bulk_image_import_map_meta_to_node($meta);
  db_query('UPDATE bulk_image_import_task SET node_id = :nid WHERE tid = :tid', array(
    'nid' => $node->nid,
    'tid' => $tid
  ));
  if ($collection_id != 0) {
    $node->field_og_collection_ref['und'][0]['target_id'] = $collection_id;
  }
  node_save($node);
  $data = file_get_contents($_FILES['file']['tmp_name']);
  $file = file_save_data($data, 'temporary://'.$_FILES['file']['name'], FILE_EXISTS_REPLACE);
  $siid = _shanti_images_create_record(
    $node->nid,
    $file->fid,
    $file->filename,
    (integer) $meta['Width'],
    (integer) $meta['Height']
  );
  $res = shanti_images_upload_iiif($node->nid, $file->fid, $siid);
  if (!$res) {
    _bulk_image_import_task_handle_error($task, "Could not convert Box file", $node, TRUE);
    drupal_json_output(array(
      'success'=> 0,
      'message'=> t('Import failed for ').$meta['Title'].'.'
    ));
    drupal_exit();
  }
  else {
    db_query('UPDATE bulk_image_import_task SET image_linked = 1 WHERE tid = :tid', array('tid' => $tid));
    //_shanti_images_expunge_image_file($node);
    drupal_json_output(array(
      'success'=> 1,
      'nodeID'=> $node->nid,
      'message'=> t('A node was succesfully created for the import ').$meta['Title'].' ('.$meta['Filename'].').',
    ));
    drupal_exit();
  }

}

function bulk_image_import_api() {
  if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    bulk_image_import_api_post();
  }
  else if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    bulk_image_import_api_get();
  }
}
