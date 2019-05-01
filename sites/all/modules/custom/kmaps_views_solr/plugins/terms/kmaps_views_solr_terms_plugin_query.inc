<?php
/**
 * @file
 *   Views query plugin for Terms.
 */

/**
 * Views query plugin for Terms related data.
 */
class kmaps_views_solr_terms_plugin_query extends views_plugin_query {
  function query($get_count = FALSE) {
  }

  function execute(&$view) {
    //dpm($view);
    $app = $view->args[0];
    $kid = $view->args[1];

    //Initialize pager
    $view->init_pager();
    $items_per_page = intval($this->pager->options['items_per_page']);
    $current_page = intval($this->pager->current_page);

    $solrURL = variable_get('shanti_kmaps_admin_server_solr_terms', SHANTI_KMAPS_ADMIN_SERVER_SOLR_TERMS);
    $solrURL .= '/select?q=associated_subject_ids:' . $kid;
    if (!empty($view->exposed_input['terms_title'])) {
      //Remove spaces from start and end
      $search = trim($view->exposed_input['terms_title']);
      //Make sure only single space betweeen words
      $search = preg_replace('/\s+/', ' ', $search);
      $search_array = explode(' ', $search);
      $search = implode('*%20AND%20*', $search_array);
      $solrURL .= '%20AND%20header:(*' . $search . '*)';
    }

    $solrURL .= '&fl=id,header&indent=true';
    $solrURL .= '&rows=' . $items_per_page . '&start=' . ($current_page * $items_per_page) . '&wt=json';

    //dpm($solrURL);

    $related_solr = save_to_cache('terms' . $app . $kid, $app, $kid, $solrURL);
    $solrObj = json_decode($related_solr);

    $this->pager->total_items = intval($solrObj->response->numFound);

    //Set some variables
    $view->total_rows = intval($solrObj->response->numFound);
    $view->items_per_page = intval($this->pager->options['items_per_page']);
    $view->current_page = $current_page;

    $this->pager->update_page_info();

    foreach ($solrObj->response->docs as $doc) {
      $row = new stdClass;

      //Populate fields
      $row->terms_id = $doc->id;
      $row->terms_title = $doc->header;

      $view->result[] = $row;
    }

  }
}