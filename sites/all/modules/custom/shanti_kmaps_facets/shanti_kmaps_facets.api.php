<?php
/**
 * @file
 *   Exposed Hooks in 7.x:
 */

/**
 * Performs a custom faceted search on the host site and returns both a list of all node id hits and kmap id facets (in the format, domain-kid)
 * The host site must index all kmap fields into a single field so that facets can be calculated.
 * 
 * There is a function shanti_kmaps_fields_get_kmaps_for_node() in shanti_kmaps_fields.module that will return all kmap values from all kmap
 * fields in a specific node. This is useful for indexing. 
 * 
 * How each site does the search for this information depends on the search module it uses. Hence, the hook.
 * 
 * The example here is from mb_solr.module and relies on apachesolr search module
 *
 * @param string $qstr
 *   The current search string.
 * @param array $kids
 *   The list of facet kmap ids.
 * 
 * @return array $qinfo
 *     An associative array with:
 *          "qids" => an array of all node ids that are hit by the query
 *          "facet_data" => an associative array of "kmapid" => facet counts
 * 
 */
function hook_node_facet_hits($qstr=FALSE, $kmids=FALSE) {
   $qinfo = FALSE;
    
    if (module_exists('apachesolr') && $qstr) {
        $keys = array(
            'q'=>$qstr, 
            'qf' => array('content^40', 'label^5.0', 'tags_h1^5.0', 'tags_h4_h5_h6^2.0', 'tags_inline^1.0', 'taxonomy_names^2.0', 'tos_content_extra^0.1', 'tos_name^3.0') ,
            'fl' => 'entity_id', 
            'facet' => TRUE,
            'facet.field' => 'sm_kmapid',
            'rows' => 2000,
         );
         
         if ($kmids) {
             $keys['fq'] = "sm_kmapid:(" .  implode(' AND ', $kmids)  . ")";
         }
        $q = apachesolr_drupal_query('facet-hit-query', $keys);
        $res = $q->search();
        $qids = array();
        foreach($res->response->docs as $doc) {
            $qids[] = $doc->entity_id;
        }
        $kmdata = (array)$res->facet_counts->facet_fields->sm_kmapid;
        $kmdata = array_filter($kmdata, function($ct) { return ($ct > 0); });
        $qinfo = array('qids' => $qids, 'facet_data' => $kmdata);
    }
    
    return $qinfo;
}