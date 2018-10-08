<?php
/**
 * @file
 *   Views query plugin for Visuals.
 */

/**
 * Views query plugin for Audio-Video related data.
 */
class kmaps_views_solr_images_plugin_query extends views_plugin_query {
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
  
    $solrURL = variable_get('shanti_kmaps_admin_server_solr', SHANTI_KMAPS_ADMIN_SERVER_SOLR);
    $solrURL .= '/select?q=kmapid:' . $app . '-' . $kid;
    $solrURL .= '%20AND%20asset_type:images';
    if (!empty($view->exposed_input['asset_subtype']) && !in_array($view->exposed_input['asset_subtype'], array('All'))) {
      $asset_subtype = trim($view->exposed_input['asset_subtype']);
      $asset_subtype = preg_replace('/\s+/', '%20', $asset_subtype);
      $asset_subtype = preg_replace('/:/', '\:', $asset_subtype);
      $solrURL .= '%20AND%20asset_subtype:' . $asset_subtype;
    }
    if (!empty($view->exposed_input['images_title'])) {
      //Remove spaces from start and end
      $search = trim($view->exposed_input['images_title']);
      //Make sure only single space betweeen words
      $search = preg_replace('/\s+/', ' ', $search);
      $search_array = explode(' ', $search);
      $search = implode('%20AND%20', $search_array);
      $solrURL .= '%20AND%20title:' . '%28' . $search . '%29';
    }
    //Sorting
    if (!empty($view->exposed_input['sort_bef_combine'])) {
      $sort = $view->exposed_input['sort_bef_combine'];
      $sort = trim($sort);
      $sort = strtolower($sort);
      $sort = preg_replace('/\s+/', ' ', $sort);
      $sort_array = explode(' ', $sort);
      $sort_str = '';
      switch ($sort_array[0]) {
        case 'created_date':
          $sort_str .= 'node_created%20';
          break;
        case 'images_title':
          $sort_str .= 'title%20';
          break;
        case 'creator':
          $sort_str .= 'creator%20';
          break;
      }
      $sort_str .= $sort_array[1];

      $solrURL .= '&sort=' . $sort_str;
    } else {
      //Default sort order
      $sort_str = 'node_created%20desc';
      $solrURL .= '&sort=' . $sort_str;
    }

    $solrURL .= '&rows=' . $items_per_page . '&start=' . ($current_page * $items_per_page) . '&wt=json';
    //watchdog('kmaps views solr images plugin', "Solr Url: $solrURL");
    //dpm($solrURL);

    $related_solr = save_to_cache('images' . $app . $kid, $app, $kid, $solrURL);
    $solrObj = json_decode($related_solr);

    $this->pager->total_items = intval($solrObj->response->numFound);

    //Set some variables
    $view->total_rows = intval($solrObj->response->numFound);
    $view->items_per_page = intval($this->pager->options['items_per_page']);
    $view->current_page = $current_page;

    $this->pager->update_page_info();

    foreach ($solrObj->response->docs as $doc) {
      $row = new stdClass;

      $kmaps = array('subjects' => array(), 'places' => array());
      foreach ($doc->kmapid_strict as $kmpid) {
        $pts = explode('-', $kmpid);
        if (isset($kmaps[$pts[0]])) {
          $kmaps[$pts[0]][] = $pts[1];
        } else {
          watchdog('kmaps views solr image', "unknown kmap type: {$pts[0]}");
        }
      }

      $thumb_url = (!empty($doc->url_thumb)) ? $doc->url_thumb : '';
      $filename = $this->get_iiif_filename($thumb_url);

      //Populate fields
      $row->images_id = $doc->id;
      $row->images_title = $doc->title[0];
      $row->images_filename = $filename;
      $row->images_desc = (!empty($doc->summary)) ? $doc->summary : '';
      $row->created_date = (isset($doc->date_start))? $doc->date_start : $doc->node_created;
      $row->collection = (!empty($doc->collection_title)) ? $doc->collection_title : '';
      $row->creator = (isset( $doc->creator[0])) ? $doc->creator[0] : $doc->node_user;
      $row->subjects = implode('|', $kmaps['subjects']);
      $row->places = implode('|', $kmaps['places']);
      //$row->asset_subtype = $doc->asset_subtype;
      $row->thumb = $thumb_url;
      $row->thumb_width = (!empty($doc->url_thumb_width)) ? $doc->url_thumb_width : '';
      $row->thumb_height = (!empty($doc->url_thumb_height)) ? $doc->url_thumb_height : '';
      $row->image_width = (isset($doc->img_width_s)) ? $doc->img_width_s : '';
      $row->image_height = (isset($doc->img_height_s)) ? $doc->img_height_s : '';

      $row->ajax_url = $doc->url_ajax;
      $row->html_url = $doc->url_html;

      $view->result[] = $row;
    }

  }

  // Get the iiif filename from the thumbnail URL
  function get_iiif_filename($url) {
    preg_match('/shanti-image[\-a-z]+\d+/',$url, $mtchs);
    if (!empty($mtchs)) {
      return $mtchs[0];
    } else {
      return '';
    }
  }

}