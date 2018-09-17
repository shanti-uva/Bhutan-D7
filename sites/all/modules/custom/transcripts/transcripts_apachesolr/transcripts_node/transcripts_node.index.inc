<?php

function transcripts_node_file_delete($file) {
    //remove any orphaned transcript associated with this file
    transcripts_apachesolr_remove_transcript('transcripts_node', 'node', 0, $file->fid);
}

function transcripts_node_node_delete($node)
{
    $fields = array_filter(transcripts_node_all_file_fields(), 'is_transcript_field');

    if (count($fields) > 0) {
        transcripts_apachesolr_remove_transcript('transcripts_node', 'node', $node->nid);
    }
}

function transcripts_node_node_insert($node)
{
    $fields = array_filter(transcripts_node_all_file_fields(), 'is_transcript_field');

    foreach ($fields as $field_name) {
        if (isset($node->$field_name)) {
            $field = $node->$field_name;

            if (!(empty($field) || (empty($field[$node->language]) && empty($field['und'])))) {
                $lang = empty($field[$node->language]) ? 'und' : $node->language;

                $file = file_load($field[$lang][0]['fid']);
                if ($trid = transcripts_apachesolr_already_indexed_trid('transcripts_node', 'node', 0, $file->fid)) {
                    transcripts_apachesolr_insert_id('transcripts_node', 'node', $node->nid, $file->fid);
                    module_invoke_all('transcripts_apachesolr_add_transcript', $node->nid, $trid);
                }
            }
        }
    }
}

function transcripts_node_add_transcript($file, $nid, $tiers = NULL)
{
    //pass nid so it can be used in transcripts_xslt_saxon_params alter hook
    $tcus = $tiers == NULL ?
      transcripts_xslt_as_tcus($file, array('nid' => $nid)) :
      transcripts_xslt_as_tcus($file, array('nid' => $nid, 'tier_id' => $tiers));

    if ($tcus === false) {
        return false;
    } else {
        transcripts_apachesolr_add_transcript('transcripts_node', 'node', $file->fid, $nid, $tcus);
        return true;
    }
}

function transcripts_node_add_processed_transcript($file, $nid, $xml, $tiers = NULL)
{
  //pass nid so it can be used in transcripts_xslt_saxon_params alter hook
  $tcus = json_decode(json_encode(simplexml_load_string($xml)), TRUE);

  if ($tcus === false) {
    return false;
  } else {
    transcripts_apachesolr_add_transcript('transcripts_node', 'node', $file->fid, $nid, $tcus);
    return true;
  }
}
