<?php
/**
 * @file biblio_import_mods.batch.inc
 *
 * Batch processes used by biblio_import_mods.
 */

// Have to include default Biblio batch processes as well, since we override the import patch of the
// existing batch process. See biblio_import_mods.module#biblio_import_mods_batch_alter for more info.
include_once(drupal_get_path('module', 'biblio') . '/includes/biblio.import.export.inc');

/**
 * Batch process importing records:
 *      (1) to remove Bibtex braces from titles
 *      (2) to add Nodes imported by Biblio to a specific Collection indicated by modified import forom
 *
 * @param string $collection_id: nid of Collection to import into
 * @param BatchContext $context
 */
function biblio_import_mods_update_import($collection_id='', &$context) {
  $created_nodes = node_load_multiple($context['results']['nids']);
  $title_types = array('title', 'biblio_secondary_title', 'biblio_tertiary_title', 'biblio_short_title',
      'biblio_alternate_title', 'biblio_translated_title', 'field_biblio_long_title');
  foreach ($created_nodes as $node) {
      foreach($title_types as $titlevar) {
          // Remove Bibtex braces from titles
          if (!empty($node->{$titlevar})) {
              $title = $node->{$titlevar};
              $title = str_replace('{', '', $title);
              $title = str_replace('}', '', $title);
              $node->{$titlevar} = $title;
          }
      }
      // Assign node to collection
      if (!empty($collection_id)) {
          $node->field_og_collection_ref['und'][0]['target_id'] = $collection_id;
      }

      // Check for no author and supply "Anonymous"
      if (empty($node->biblio_contributors)) {
          $node->biblio_contributors[] = array(
              'name' => "Anonymous",
              'auth_category' => 1  // 1 = primary author
          );
      }

      // Check for nodes without a year and use 1st 4 digits from biblio_date
      if (empty($node->biblio_year) || $node->biblio_year == 'Submitted') {
          $date = FALSE;
          $date_fields = array('biblio_date', 'biblio_access_date', 'biblio_custom1');
          foreach ($date_fields as $df) {
              if (!empty($node->{$df})) { $date = $node->{$df}; }
          }
          if ($date && preg_match('/^(\d{4})[^\d]/', $date, $matches)) {
              $node->biblio_year = $matches[1];
          }
      }

      // Assign type if there is a biblio_url
      if ($node->biblio_type_name == 'Miscellaneous' && !empty($node->biblio_url)) {
          $node->biblio_type = 132;
          $node->biblio_type_name == 'Website';
          $url = $node->biblio_url;
          $vhosts = array('youtube', 'vimeo', 'kaltura', 'audio', 'video');
          foreach ($vhosts as $vh) {
              if (strstr($url, $vh)) {
                  $node->biblio_type = 114;
                  $node->biblio_type_name == 'Audiovisual';
                  break;
              }
          }
      }

      node_save($node);
  }
}
