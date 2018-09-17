<?php

function bulk_image_import_link_kmaps_term($node, $domain, $term) {
  shanti_kmaps_fields_add_kmap_to_node(
    $node,
    'field_' . $domain,
    $domain,
    $term
  );
}

function _bulk_image_import_clean_xml_field($field) {
  return trim(preg_replace('/\s\s+/', ' ', (string) $field));
}

function _bulk_image_import_clean_date_field($field) {
  $value = _bulk_image_import_clean_xml_field($field);
  list($date, $time) = explode(" ", $value);
  $date = preg_replace("/:/", "-", $date);
  return $date;
}

function bulk_image_import_map_xml_to_node($xml) {
  $node = new stdClass();
  $node->title = _bulk_image_import_clean_xml_field($xml->UserFields->UserField_4);
  $node->type = 'shanti_image';
  node_object_prepare($node);
  $node->uid = $GLOBALS['user']->uid;
  $node->status = 1;
  $node->field_image_description = _bulk_image_import_clean_xml_field($xml->AnnotationFields->Caption);
  $node->field_orginial_filename = _bulk_image_import_clean_xml_field($xml->AssetProperties->Filename);
  $node->field_image_capture_device = _bulk_image_import_clean_xml_field($xml->MetaDataFields->Model);
  $node->field_copyright_holder = _bulk_image_import_clean_xml_field($xml->AnnotationFields->Copyright);
  $node->field_rights_notes = _bulk_image_import_clean_xml_field($xml->AnnotationFields->Rights);
  $orientation_code = _bulk_image_import_clean_xml_field($xml->MediaProperties->ViewRotation);
  switch($orientation_code) {
  case 1:
    $node->field_image_rotation = 0;
    break;
  case 3:
    $node->field_image_rotation = 180;
    break;
  case 6:
    $node->field_image_rotation = 90;
    break;
  case 8:
    $node->field_image_rotation = 270;
    break
  }
  $node->field_iso_speed_rating = _bulk_image_import_clean_xml_field($xml->MetaDataFields->ISOSpeedRating);
  $node->field_exposure_bias = _bulk_image_import_clean_xml_field($xml->MetaDataFields->ExposureBias);
  $node->field_aperture = _bulk_image_import_clean_xml_field($xml->MetaDataFields->Aperture);
  $node->field_metering_mode = _bulk_image_import_clean_xml_field($xml->MetaDataFields->MeteringMode);
  $node->field_light_source = _bulk_image_import_clean_xml_field($xml->MetaDataFields->LightSource);
  $node->field_flash_settings = _bulk_image_import_clean_xml_field($xml->MetaDataFields->Flash);
  $node->field_focal_length = (float) _bulk_image_import_clean_xml_field($xml->MetaDataFields->FocalLength);
  $node->field_sensing_method = _bulk_image_import_clean_xml_field($xml->MetaDataFields->SensingMethod);
  $node->field_noise_reduction = (_bulk_image_import_clean_xml_field($xml->MetaDataFields->NoiseReduction) == "ON");
  $node->field_lens = _bulk_image_import_clean_xml_field($xml->MetaDataFields->Lens);
  $node->field_latitude = _bulk_image_import_clean_xml_field($xml->MetaDataFields->Latitude);
  $node->field_longitude = _bulk_image_import_clean_xml_field($xml->MetaDataFields->Longitude);
  $node->field_altitude = (float) rtrim(
    _bulk_image_import_clean_xml_field($xml->MetaDataFields->Altitude),
    "m"
  );
  $node->field_admin_notes = $xml->asXML();
  if (property_exists($xml->AnnotationFields, 'Keyword')) {
    $node->field_keywords = _bulk_image_import_clean_xml_field($xml->AnnotationFields->Keyword);
  }
  if (property_exists($xml->UserFields, 'UserField_1')) {
    $node->field_organization_name = _bulk_image_import_clean_xml_field($xml->UserFields->UserField_1);
  }
  if (property_exists($xml->UserFields, 'UserField_2')) {
    $node->field_project_name = _bulk_image_import_clean_xml_field($xml->UserFields->UserField_2);
  }
  if (property_exists($xml->UserFields, 'UserField_3')) {
    $node->field_sponsor_name = _bulk_image_import_clean_xml_field($xml->UserFields->UserField_3);
  }
  if (property_exists($xml->UserFields, 'UserField_5')) {
    $node->field_spot_feature = _bulk_image_import_clean_xml_field($xml->UserFields->UserField_5);
  }
  if (property_exists($xml->UserFields, 'UserField_6')) {
    $node->field_public_note = _bulk_image_import_clean_xml_field($xml->UserFields->UserField_6);
  }
  if (property_exists($xml->UserFields, 'UserField_7')) {
    $node->field_private_note = _bulk_image_import_clean_xml_field($xml->UserFields->UserField_7);
  }

  $matches = NULL;
  $match = preg_match('/\{(?<id>\d+)\}/', (string) $xml->AnnotationFields->SubjectReference, $matches);
  if($match) {
    bulk_image_import_link_kmaps_term($node, 'subjects', $matches['id']);
  }
  $matches = NULL;
  $match = preg_match('/\{(?<id>\d+)\}/', (string) $xml->AnnotationFields->Category, $matches);
  if($match) {
    bulk_image_import_link_kmaps_term($node, 'places', $matches['id']);
  }

  $agent = FALSE;
  $response = db_query(
    "SELECT * FROM node where type = 'image_agent' AND title = :title",
    array('title' => _bulk_image_import_clean_xml_field($xml->AnnotationFields->Author))
  )->fetchAssoc();
  if($response) {
    $agent = node_load($response['nid']);
  }
  if(!$agent) {
    $agent = new stdClass();
    $agent->type = 'image_agent';
    $agent->title = _bulk_image_import_clean_xml_field($xml->AnnotationFields->Author);
    $agent->field_agent_dates = _bulk_image_import_clean_date_field($xml->MetaDataFields->CaptureDate);
    $agent->status = 1;
    node_object_prepare($agent);
    node_save($agent);
  }
  $node->field_image_agents['und'][0]['target_id'] = $agent->nid;
  $node->field_image_agents['und'][0]['target_type'] = 'image_agent';

  node_save($node);
  shanti_kmaps_fields_node_insert($node);
  return $node;
}
