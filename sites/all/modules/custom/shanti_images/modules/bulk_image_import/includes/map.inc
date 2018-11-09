<?php

function bulk_image_import_link_kmaps_term($node, $domain, $term) {
  shanti_kmaps_fields_add_kmap_to_node(
    $node,
    'field_' . $domain,
    $domain,
    $term
  );
}

function _bulk_image_import_clean_field($field) {
  return trim(preg_replace('/\s\s+/', ' ', (string) $field));
}

function _bulk_image_import_clean_date_field($field) {
  $value = _bulk_image_import_clean_field($field);
  list($date, $time) = explode(" ", $value);
  $date = preg_replace("/:/", "-", $date);
  return $date;
}

function bulk_image_import_map_xml_to_node($xml) {
  $node = new stdClass();
  $node->title = _bulk_image_import_clean_field($xml->UserFields->UserField_4);
  $node->type = 'shanti_image';
  node_object_prepare($node);
  $node->uid = $GLOBALS['user']->uid;
  $node->status = 1;
  $node_wrapper = entity_metadata_wrapper('node', $node);
  $node_wrapper->field_original_filename->set(_bulk_image_import_clean_field($xml->AssetProperties->Filename));
  $node_wrapper->field_image_capture_device->set(_bulk_image_import_clean_field($xml->MetaDataFields->Model));
  $node_wrapper->field_copyright_holder->set(_bulk_image_import_clean_field($xml->AnnotationFields->Copyright));
  $node_wrapper->field_rights_notes->set(array(_bulk_image_import_clean_field($xml->AnnotationFields->Rights),));
  $orientation_code = _bulk_image_import_clean_field($xml->MediaProperties->ViewRotation);
  switch($orientation_code) {
  case 1:
    $node_wrapper->field_image_rotation->set(0);
    break;
  case 3:
    $node_wrapper->field_image_rotation->set(180);
    break;
  case 6:
    $node_wrapper->field_image_rotation->set(90);
    break;
  case 8:
    $node_wrapper->field_image_rotation->set(270);
    break;
  }
  $node_wrapper->field_iso_speed_rating->set((integer)_bulk_image_import_clean_field($xml->MetaDataFields->ISOSpeedRating));
  $node_wrapper->field_exposure_bias->set(_bulk_image_import_clean_field($xml->MetaDataFields->ExposureBias));
  $node_wrapper->field_aperture->set(_bulk_image_import_clean_field($xml->MetaDataFields->Aperture));
  $node_wrapper->field_metering_mode->set(_bulk_image_import_clean_field($xml->MetaDataFields->MeteringMode));
  $node_wrapper->field_light_source->set(_bulk_image_import_clean_field($xml->MetaDataFields->LightSource));
  $node_wrapper->field_flash_settings->set(_bulk_image_import_clean_field($xml->MetaDataFields->Flash));
  $node_wrapper->field_focal_length->set((float) _bulk_image_import_clean_field($xml->MetaDataFields->FocalLength));
  $node_wrapper->field_sensing_method->set(_bulk_image_import_clean_field($xml->MetaDataFields->SensingMethod));
  $node_wrapper->field_noise_reduction->set((_bulk_image_import_clean_field($xml->MetaDataFields->NoiseReduction) == "ON"));
  $node_wrapper->field_lens->set(_bulk_image_import_clean_field($xml->MetaDataFields->Lens));
  $node_wrapper->field_latitude->set(_bulk_image_import_clean_field($xml->MetaDataFields->Latitude));
  $node_wrapper->field_longitude->set(_bulk_image_import_clean_field($xml->MetaDataFields->Longitude));
  $node_wrapper->field_altitude->set((float) rtrim(
    _bulk_image_import_clean_field($xml->MetaDataFields->Altitude),
    "m"
  ));
  $node_wrapper->field_admin_notes->set(array($xml->asXML(),));
  if (property_exists($xml->AnnotationFields, 'Keyword')) {
    $node_wrapper->field_keywords->set(_bulk_image_import_clean_field($xml->AnnotationFields->Keyword));
  }
  if (property_exists($xml->UserFields, 'UserField_1')) {
    $node_wrapper->field_organization_name->set(_bulk_image_import_clean_field($xml->UserFields->UserField_1));
  }
  if (property_exists($xml->UserFields, 'UserField_2')) {
    $node_wrapper->field_project_name->set(_bulk_image_import_clean_field($xml->UserFields->UserField_2));
  }
  if (property_exists($xml->UserFields, 'UserField_3')) {
    $node_wrapper->field_sponsor_name->set(_bulk_image_import_clean_field($xml->UserFields->UserField_3));
  }
  if (property_exists($xml->UserFields, 'UserField_5')) {
    $node_wrapper->field_spot_feature->set(_bulk_image_import_clean_field($xml->UserFields->UserField_5));
  }
  if (property_exists($xml->UserFields, 'UserField_6')) {
    $node_wrapper->field_general_note->set(_bulk_image_import_clean_field($xml->UserFields->UserField_6));
  }
  if (property_exists($xml->UserFields, 'UserField_7')) {
    $node_wrapper->field_private_note->set(_bulk_image_import_clean_field($xml->UserFields->UserField_7));
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
    array('title' => _bulk_image_import_clean_field($xml->AnnotationFields->Author))
  )->fetchAssoc();
  if($response) {
    $agent = node_load($response['nid']);
  }
  if(!$agent) {
    $agent = new stdClass();
    $agent->type = 'image_agent';
    $agent->title = _bulk_image_import_clean_field($xml->AnnotationFields->Author);
    $agent->field_agent_dates = _bulk_image_import_clean_date_field($xml->MetaDataFields->CaptureDate);
    $agent->status = 1;
    node_object_prepare($agent);
    node_save($agent);
  }
  $node->field_image_agents['und'][0]['target_id'] = $agent->nid;
  $node->field_image_agents['und'][0]['target_type'] = 'image_agent';

  $caption = new stdClass();
  $caption->type = 'image_descriptions';
  $caption->title = _bulk_image_import_clean_field($xml->UserFields->UserField_4);
  $caption->field_description =_bulk_image_import_clean_field($xml->AnnotationFields->Caption);
  node_object_prepare($caption);
  node_save($caption);
  $node->field_image_descriptions['und'][0]['target_id'] = $caption->nid;
  $node->field_image_descriptions['und'][0]['target_type'] = 'image_descriptions';

  node_save($node);
  shanti_kmaps_fields_node_insert($node);
  return $node;
}


function bulk_image_import_map_meta_to_node($meta) {
  $node = new stdClass();
  $node->title = _bulk_image_import_clean_field($meta['Title']);
  $node->type = 'shanti_image';
  node_object_prepare($node);
  $node->uid = $GLOBALS['user']->uid;
  $node->status = 1;
  $node_wrapper = entity_metadata_wrapper('node', $node);
  $node_wrapper->field_original_filename->set(_bulk_image_import_clean_field($meta['Filename']));
  $node_wrapper->field_image_capture_device->set(_bulk_image_import_clean_field($meta['Model']));
  $node_wrapper->field_copyright_holder->set(_bulk_image_import_clean_field($meta['Copyright']));
  $node_wrapper->field_rights_notes->set(array(_bulk_image_import_clean_field($meta['Rights']),));
  $orientation_code = $meta['ViewRotation'];
  switch($orientation_code) {
  case 1:
    $node_wrapper->field_image_rotation->set(0);
    break;
  case 3:
    $node_wrapper->field_image_rotation->set(180);
    break;
  case 6:
    $node_wrapper->field_image_rotation->set(90);
    break;
  case 8:
    $node_wrapper->field_image_rotation->set(270);
    break;
  }
  $node_wrapper->field_iso_speed_rating->set((integer)_bulk_image_import_clean_field($meta['ISOSpeedRating']));
  $node_wrapper->field_exposure_bias->set(_bulk_image_import_clean_field($meta['ExposureBias']));
  $node_wrapper->field_aperture->set(_bulk_image_import_clean_field($meta['Aperture']));
  $node_wrapper->field_metering_mode->set(_bulk_image_import_clean_field($meta['MeteringMode']));
  $node_wrapper->field_light_source->set(_bulk_image_import_clean_field($meta['LightSource']));
  $node_wrapper->field_flash_settings->set(_bulk_image_import_clean_field($meta['Flash']));
  $node_wrapper->field_focal_length->set((float) _bulk_image_import_clean_field($meta['FocalLength']));
  $node_wrapper->field_sensing_method->set(_bulk_image_import_clean_field($meta['SensingMethod']));
  $node_wrapper->field_noise_reduction->set((_bulk_image_import_clean_field($meta['NoiseReduction']) == "ON"));
  $node_wrapper->field_lens->set(_bulk_image_import_clean_field($meta['Lens']));
  $node_wrapper->field_latitude->set(_bulk_image_import_clean_field($meta['Latitude']));
  $node_wrapper->field_longitude->set(_bulk_image_import_clean_field($meta['Longitude']));
  $node_wrapper->field_altitude->set((float) rtrim(
    _bulk_image_import_clean_field($meta['Altitude']),
    "m"
  ));
  $node_wrapper->field_admin_notes->set(array(json_encode($meta),));
  if (isset($meta['Keyword'])) {
    $node_wrapper->field_keywords->set(_bulk_image_import_clean_field($meta['Keyword']));
  }
  $node_wrapper->field_organization_name->set(_bulk_image_import_clean_field($meta['OrganizationName']));
  $node_wrapper->field_project_name->set(_bulk_image_import_clean_field($meta['ProjectName']));
  $node_wrapper->field_sponsor_name->set(_bulk_image_import_clean_field($meta['SponsorName']));
  $node_wrapper->field_spot_feature->set(_bulk_image_import_clean_field($meta['SpotFeature']));
  $node_wrapper->field_general_note->set(_bulk_image_import_clean_field($meta['GeneralNote']));
  $node_wrapper->field_private_note->set(_bulk_image_import_clean_field($meta['PrivateNote']));

  $matches = NULL;
  $match = preg_match('/\{(?<id>\d+)\}/', (string) $meta['SubjectReference'], $matches);
  if($match) {
    bulk_image_import_link_kmaps_term($node, 'subjects', $matches['id']);
  }
  $matches = NULL;
  $match = preg_match('/\{(?<id>\d+)\}/', (string) $meta['Category'], $matches);
  if($match) {
    bulk_image_import_link_kmaps_term($node, 'places', $matches['id']);
  }

  $agent = FALSE;
  $response = db_query(
    "SELECT * FROM node where type = 'image_agent' AND title = :title",
    array('title' => _bulk_image_import_clean_field($meta['Author']))
  )->fetchAssoc();
  if($response) {
    $agent = node_load($response['nid']);
  }
  if(!$agent) {
    $agent = new stdClass();
    $agent->type = 'image_agent';
    $agent->title = _bulk_image_import_clean_field($meta['Author']);
    $agent->field_agent_dates = _bulk_image_import_clean_date_field($meta['CaptureDate']);
    $agent->status = 1;
    node_object_prepare($agent);
    node_save($agent);
  }
  $node->field_image_agents['und'][0]['target_id'] = $agent->nid;
  $node->field_image_agents['und'][0]['target_type'] = 'image_agent';

  $caption = new stdClass();
  $caption->type = 'image_descriptions';
  $caption->title = _bulk_image_import_clean_field($meta['Title']);
  $caption->field_description =_bulk_image_import_clean_field($meta['Caption']);
  node_object_prepare($caption);
  node_save($caption);
  $node->field_image_descriptions['und'][0]['target_id'] = $caption->nid;
  $node->field_image_descriptions['und'][0]['target_type'] = 'image_descriptions';

  node_save($node);
  shanti_kmaps_fields_node_insert($node);
  return $node;
}
