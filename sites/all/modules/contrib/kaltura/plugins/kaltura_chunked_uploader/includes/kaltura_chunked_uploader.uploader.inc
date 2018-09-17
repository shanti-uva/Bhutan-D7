<?php
/**
 * @file
 * Contains functions for upload handling
 */

/**
 * @param $js
 * @param $widget
 * @return string
 * @throws Exception
 */
function kaltura_chunked_uploader_uploader($js, $widget)
{
  if ($js) {
    ctools_include('modal');
    ctools_include('ajax');
  }

  drupal_add_library('system', 'drupal.ajax');
  drupal_add_library('kaltura_chunked_uploader', 'chunked-file-upload-jquery');

  $fileTypes = kaltura_chunked_uploader_get_allowed_file_types($widget);
  $helpers = new KalturaHelpers();
  $weakClient = $helpers->getKalturaClient(false, 'enableentitlement', 7200);
  $id = time();

  drupal_add_js(array(
    'kaltura_chunked_uploader' => array(
      'fileTypes' => $fileTypes,
      'ks' => $weakClient->getKs(),
      'serviceUrl' => KalturaHelpers::getKalturaServerUrl(),
      'uploaderId' => $id,
    ),
  ), 'setting');

  $contents = theme('kaltura_chunked_uploader_uploader', array(
    'fileTypes' => $fileTypes,
    'uploaderId' => $id,
  ));

  if ($js) {
    ctools_modal_render(t('Add New Media'), $contents);
    drupal_exit();
  }

  return $contents;
}

/**
 * @param string $uploadTokenId
 * @param string $fileName
 * @throws Exception
 */
function kaltura_chunked_uploader_ajax_add_media($uploadTokenId, $fileName) {
  ctools_include('modal');
  ctools_include('ajax');

  $extension = pathinfo($fileName, PATHINFO_EXTENSION);
  $mediaType = KALTURA_MEDIA_TYPE_VIDEO;
  $supportedExtension = kaltura_chunked_uploader_get_supported_file_types();
  foreach ($supportedExtension as $key => $item) {
    if (in_array($extension, $item)) {
      $mediaType = $key;
      break;
    }
  }

  $commands = array();

  try {
    $entry = kaltura_chunked_uploader_add_media_from_uploaded_token($uploadTokenId, $fileName, $mediaType);
    $entity = kaltura_entry_create(array('kaltura_entryid' => $entry->id));
    kaltura_map_properties($entry, $entity);
    // No need to call kaltura_save_entry_metadata() because we've just created
    // the entry and there's no fields filled yet.
    kaltura_entry_save($entity);

    $commands[] = array(
      'command' => 'kalturaCallFunction',
      'function' => 'kalturaUpdateMediaField',
      'arguments' => array(
        $entry->id,
        $entry->mediaType,
      ),
    );

    $commands[] = ctools_modal_command_dismiss();
  }
  catch (Exception $e) {
    watchdog_exception('kaltura', $e);
    drupal_set_message(t('Failed to create media from the uploaded file.'), 'error');
    $commands[] = ajax_command_after('#successmsg', theme('status_messages'));
  }

  print ajax_render($commands);

  drupal_exit();
}

/**
 * @param $widget
 * @return array
 */
function kaltura_chunked_uploader_get_allowed_file_types($widget) {
  $fileTypes = kaltura_chunked_uploader_get_supported_file_types();
  $fileTypes[0] = array_merge($fileTypes[KALTURA_MEDIA_TYPE_VIDEO], $fileTypes[KALTURA_MEDIA_TYPE_IMAGE], $fileTypes[KALTURA_MEDIA_TYPE_AUDIO]);

  $allowedMediaType = kaltura_widget_to_media_type($widget);
  $allowedMediaType = !empty($allowedMediaType) ? $allowedMediaType : 0;
  $allowedFileTypes = array_reduce($fileTypes[$allowedMediaType], function ($carry, $item) {
    return array_merge($carry, array($item, strtoupper($item)));
  }, array());

  return $allowedFileTypes;
}

/**
 * @return array
 */
function kaltura_chunked_uploader_get_supported_file_types() {
  return array(
    KALTURA_MEDIA_TYPE_VIDEO => array('ogm', 'ogv', 'mts', 'qt', 'mov', 'mpg', 'mpeg', 'avi', 'mp4', 'vob', 'flv', 'f4v', 'asf', 'wmv', 'm4v', '3gp', 'mkv', 'arf', 'webm', 'rm', 'rv'),
    KALTURA_MEDIA_TYPE_IMAGE => array('jpg', 'jpeg', 'bmp', 'png', 'gif', 'tif', 'tiff'),
    KALTURA_MEDIA_TYPE_AUDIO => array('ogg', 'oga', 'flac', 'mp3', 'm3a', 'm4a', 'wav', 'wma', 'ra', 'aiff'),
  );
}

/**
 * @param string $token
 * @param string $name
 * @param KalturaMediaType|int $mediaType
 * @return KalturaMediaEntry|KalturaBaseEntry
 * @throws KalturaClientException
 */
function kaltura_chunked_uploader_add_media_from_uploaded_token($token, $name, $mediaType) {
  $helpers = new KalturaHelpers();
  $kaltura_client = $helpers->getKalturaClient(false, 'enableentitlement');

  $entry = new KalturaMediaEntry();
  $entry->name = !empty($name) ? $name : date("F j, Y, g:i a");
  $entry->type = KalturaEntryType::AUTOMATIC;
  $entry->mediaType = $mediaType;

  $res = $kaltura_client->baseEntry->add($entry);

  $resource = new KalturaUploadedFileTokenResource();
  $resource->token = $token;

  $res = $kaltura_client->baseEntry->addContent($res->id, $resource);

  return $res;
}
