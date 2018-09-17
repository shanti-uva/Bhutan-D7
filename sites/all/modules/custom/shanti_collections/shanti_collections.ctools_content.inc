<?php
/**
 * @file
 * shanti_collections.ctools_content.inc
 */

/**
 * Implements hook_default_ctools_custom_content().
 */
function shanti_collections_default_ctools_custom_content() {
  $export = array();

  $content = new stdClass();
  $content->disabled = FALSE; /* Edit this to true to make a default content disabled initially */
  $content->api_version = 1;
  $content->name = 'view_collections_content';
  $content->admin_title = 'View Collections Content';
  $content->admin_description = 'A view of all Collection items, including those from Subcollections.';
  $content->category = 'SHANTI';
  $content->settings = array(
    'admin_title' => '',
    'title' => 'Collection Items',
    'body' => '<?php

$nid =   arg(1);
$args = array();
$args[] = $nid;
$v1 = views_get_view(\'collections\');
$v1->set_display(\'views_data_export_1\');
$v1->set_arguments(array($nid));
$v1->pre_execute();
$v1->execute();
foreach ($v1->result as $item) { $args[] = $item->nid; }
$arg_str = implode(",",$args);

// Pass the argument to the texts view
// REPLACE all_texts and panel_pane_2 with your own view and display
// MAKE SURE your view accepts multiple arguments!
$v2 = views_embed_view(\'all_texts\',\'panel_pane_2\',$arg_str);
print($v2);
?>',
    'format' => 'php_code',
    'substitute' => 0,
  );
  $export['view_collections_content'] = $content;

  return $export;
}
