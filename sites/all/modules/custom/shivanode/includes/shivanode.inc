<?php
/**
 * @file
 * An include files with functions specific to the SHIVA Visualization Manager.
 */

/**
 * Returns a indexed array defining the value/Name items for the chart type list
 *
 * @return
 *  An associative array specifying the values we wish to add for the chart type.
 *  This is used as allowed values function for shivanode_element_type and in the shivanode_form_alter,
 *  and a few other form related functions for on change and submit
 * 
 * 	Use this for an index/Name list of active types. Deprecated types and subtypes are exculded.
 *  For other versions of the type list use the shivanode_get_types() function in shivanode.type.inc
 * 
 *  @see shivanode_get_types() in shivanode.type.inc
 * 
 * TODO: Make sure all references to this are replaced with shivanode_get_types calls
 *  
 */
 
function _shivanode_element_typelist() {
	module_load_include('inc', 'shivanode', 'includes/shivanode.types');
    $include_deprecated = FALSE;
    // Check to see if editing a previously created deprecated type
    if (preg_match('/\/(\d+)\/edit/', current_path(), $m)) {
        $include_deprecated = TRUE;
    }
 	$options = shivanode_get_types('nameindex', $include_deprecated); // returns all types by index=>name excluding deprecated ones by default
  return $options;
}

/** 
 * Returns list of subtypes for all visualization. Initial array each item has a label (1) and then it's json value (2)
 * A call without parameters returns an array of labels, _shivanode_subtypelist('json') returns an array of json values, and
 * _shivanode_subtypelist('index', 'rgraph') will return the index for the second item. Search value can be either label or json val.
 * 
 * Important: This is the allowed_values_function for shivanode_subtype field and cannot be removed or have its name changed.
 */
function _shivanode_subtypelist($type='label', $search=FALSE) {
	module_load_include('inc', 'shivanode', 'includes/shivanode.types');
  $types = array('label', 'json', 'index');
  $typeval = array_search($type, $types);
	$options = shivanode_get_types('subtypes');
  if(is_numeric($type)) {
    if(isset($options[$type][0])){
      return $options[$type][0];
    } else {
      return FALSE;
    }
  }
  if($type == 'index') {
    if(!$search) { return FALSE; } // If no search string, no match
    foreach($options as $key => $value) {
      if($value[0] == $search || $value[1] == $search) {
        return $key;
      }
    }
    return FALSE;  // no match
  } else {
    foreach($options as $key => &$value) {
      $value = $value[$typeval];
    }
    return $options; // return "filtered" options
  }
}

/**
 * Implements hook_options_list for the options widget of the visualization type field
 * Returns a structured array defining the values for the chart type list
 *
 * @return
 *  An associative array specifying the values we wish to add for the chart type.
 *  
 */
function _shivanode_options_list($option = NULL) {
  $options = array(
    t('Visualizations') => _shivanode_element_typelist(FALSE, TRUE), // show deprecated? 
  );
  if (isset($option)) {
    if (!is_numeric($option)) {
      return "The option index, $option, is not a numeric.";
    }
    $subtype = ($option != 8 && $option != 9) ? t('Visualizations'):t('Other');
    return $options[$subtype][$option];
  }
  else {
    return $options;
  }
}

/**
 * Returns a structured array defining the values for the privileges 
 *
 * @return
 *  An associative array specifying the values we wish to add for the chart type.
 *  
 */
function _shivanode_access_modes() {
  $options = array(
    1 => t('Draft'),
    //2 => 'Group',
    //3 => 'University',
    4 => t('Published'),
  );
  return $options;
}

/**
 * Helper function that gets all Shiva nodes most recent first
 *  options can either be a space separated list of options or a element type number. Options include:
 *    stype:\d+ (the number after the colon will be the element type number and will show only elements of this type)
 *    nodata (will exclude data elements)
 *    recent (will give most recent elements first)
 *    mine (will return only current users nodes. This will override the following.) 
 *    user => uid (will return for a specific uid)
 * 
 *  If options is just a numeric it will return only elements of that type
 * 
 *  Old Common Options strings:
 *    'sntype:1 mine' : Returns user's data elements (No longer used. See below.)
 *
 */

function _get_shivanodes($options = array()) {
  global $user;
  if(is_string($options)) {
    $options = explode(' ', $options); 
    $options = array_flip($options);
    foreach($options as $key => $value ) {
      if(preg_match('/stype\:(\d+)/', $key, $matches)) {
        $options['stype'] = $matches[1];
        break;
      }
    }
  }
  if(is_numeric($options)) { $options = array('stype' => $options); }
  $stype = (array_key_exists('stype', $options)) ? $options['stype'] : 0;
  $uid = $user->uid;
  $query = db_select('node', 'n');
  $query->join('field_data_shivanode_element_type', 'stype', 'n.nid = stype.entity_id');
  $query->join('field_data_shivanode_access', 'sac', 'n.nid = sac.entity_id');
  $query->join('field_data_shivanode_json', 'sjson', 'n.nid = sjson.entity_id');
  $query->fields('n')
    ->fields('stype', array('shivanode_element_type_value'))
    ->fields('sac', array('shivanode_access_value'))
    ->fields('sjson', array('shivanode_json_value'))
    ->condition('n.type', 'shivanode')
    ->condition('n.status', NODE_PUBLISHED);
  if(array_key_exists('mine', $options)) {
    $query->condition('n.uid', $user->uid);
  } else if(array_key_exists('user', $options)) {
    $query->condition('n.uid', $options['user']);
  }
  if (array_key_exists('recent', $options)) {
    $query->orderBy('n.changed', 'DESC');
  } 
  else {
    $query->orderBy('n.title', 'ASC');
  }
  // if stype variable is supplied and its a number get only that type of shivanode
  if (is_numeric($stype) && $stype > 0) {
    $query->condition('stype.shivanode_element_type_value', $stype);
  }
  $results = $query->execute();
  $nodes = array();
  foreach ($results as $row) {
    if ($row->uid == $uid || $row->shivanode_access_value == "Published" ||  user_access('bypass node access')) {
      if(isset($row->shivanode_json_value)) {
        $json = json_decode($row->shivanode_json_value);
        if(isset($json->dataSourceUrl)) {
          if($gid = _get_gid_from_url($json->dataSourceUrl)) { 
            $row->dataGid = $gid;
          }
        }
      }
      if (array_key_exists('nodata', $options)) {
        if ($row->shivanode_element_type_value > 1) {
          $nodes[] = $row; // This was returning node objects but it was too intensive to load each node.
        }
      } 
      else {
        $nodes[] = $row;
      }
    }
  }
  return $nodes;
}

function _get_gid_from_url($url) {
  if (preg_match('/\?key=([^\#\&]+)[\#\&]?/', $url, $matches)) { 
    return $matches[1];
  } else if (preg_match('/\/d\/([^\/]+)\/edit/', $url, $matches)) {
    return $matches[1];
  } else {
    return FALSE;
  }
}

/*
 * Gets the type of visualization in the Shiva node
 */
function _get_shivanode_type($node, $mode = 'string') {
  if ($node && isset($node->shivanode_element_type)) {
  	module_load_include('inc', 'shivanode', 'includes/shivanode.types');
 	$options = shivanode_get_types('nameindex', TRUE); 
    $typefield = $node->shivanode_element_type;
    if (count($typefield) == 0 || !isset($typefield['und']['0']['value'])) { return FALSE; }
    $val = $typefield['und']['0']['value'] * 1;
    if ($val == 5) { $val = 13; }  // account for old simile 5 
    if ($mode == 'string' && isset($options[$val])) { return $options[$val]; } // Return string if set
    if ($mode == 'number' || $mode == 'int') { return $val; } // Return int if that's what's needed
  }
  return FALSE; // Otherwise return FALSE
}


/*
 * Gets the access value (0 = private, 1 = public) of visualization in the Shiva node
 */
function _get_shivanode_access_status($node) {
  $status = FALSE;
  if ($node && !empty($node->shivanode_access)) {
    $options = _shivanode_access_modes();
    $accessfield = $node->shivanode_access;
    $val = $accessfield['und']['0']['value'] * 1;
    if (isset($options[$val])) {
      $status = $options[$val];  
    }
  }
  return $status;
}

/**
 * Function for turning a JSON Hash Object into a Shiva Go URL query string
 *
 * @return
 *   a query string for a Shiva Go Url
 *
 */
function _shivanode_parse_json($jdata) {
  $jobj = $jdata;
  $outstr = FALSE;
  $debug = "";
  if (is_string($jobj)) {
    $jobj = json_decode($jdata);
  }
  if (is_object($jobj)) {
    foreach ($jobj as $key => $value) {
      if ($value != '') {
        if (is_string($outstr)) {
          $outstr .= '&';
        }
        if (!is_string($value)) { $value = json_encode($value); }
        $outstr .= $key . "=" . $value;
      }
    }
  }
  return $outstr;
}

/*
 * A function to return the number of recent shivanode set in the admin settings, default is 5
 *
 */

function _get_recent_shivanodes() {
  $recent_num = variable_get('shivanode_block_entries', SHIVA_RECENT_ENTRIES);
  $all_recent = _get_shivanodes('recent nodata');
  $shiva_recent = array();
  foreach ($all_recent as $node) {
    $shiva_recent[] = $node;
    if (--$recent_num == 0) {
      break;
    }
  }
  return $shiva_recent;
}

/**
 * Returns an array of shiva node types that use spreadsheet info for a select in machinenm => label format
 * Or the Label associated with a value
 * 
 * @param mixed $val
 * 	Either an integer index value or FALSE to return whole list
 *  
 **/
function _shivanode_types_using_gdocs($val = FALSE) {
	module_load_include('inc', 'shivanode', 'includes/shivanode.types');
	$gdtypes = _shivanode_get_data_types('select');
      if(!$val) {
        return $gdtypes;
      } else if (!isset($gdtypes[$val])) {
        return FALSE;
      } else {
        return $gdtypes[$val];
      }
}

/**
 * Returns the editor url for each active visualiztion type to be included in the edit form for shivanodes
 * If type has been deprecated, returns only player url. Shivadata handled seprately in its own submodule
 * 
 * @param mixed $int
 * 	The integer index or machine name of the desired visualization type
 * 
 * @return string Url for the editor
 */
function _get_shivaframe_url($opt, $nid = FALSE) {
  if (is_array($opt)) { $opt = $opt[0]; } // if it's an array take first element value
  if (!is_numeric($opt)) { $opt = _shivanode_get_index($opt);  }  // convert machine name to index
  $player = FALSE;
  switch ($opt) {
    /*case 1:  // Data (Deprecated)
    	drupal_set_message('Shivanode data types have been migrated to shivadata nodes. Fix call to this function', 'warning');
		  ddebug_backtrace();
      if ($nid != '') {
        $njson = _shivanode_get_json($nid);
        if(isset($njson['dataSourceUrl'])) {
          $player = str_replace('https','http', $njson['dataSourceUrl']);
        }
      }
       //$player = variable_get('shivanode_data_editor', SHIVA_DATA_EDITOR); //"$otherroot/data.htm?pr=d";
      break;*/
    case 2:   // Image
      $player =  SHIVA_IMAGE_EDITOR;
      break;
    case 3:  // Maps
      $player =  SHIVA_MAP_EDITOR;
      break;
    case 4: // Subway
      $player =  SHIVA_SUBWAY_EDITOR;
      break;
    case 5: // Timelines
      // removing ability to add simile timelines but calling timeglider editor for any existing ones
      $player =  SHIVA_TIMEGLIDER_EDITOR;
      //$player =  variable_get('shivanode_timeline_editor', SHIVA_TIMELINE_EDITOR);
      break;
    case 6: // Videos
      $player =  SHIVA_VIDEO_EDITOR;
      break;
    case 7:  // Chart
      $player =  SHIVA_CHART_EDITOR;
      break;
    /*case 8:  // Controls
      $player =  SHIVA_CONTROL_EDITOR;
      break;
    case 9:  // Canvas
      $player =  SHIVA_CANVAS_EDITOR;
      break;
    case 10:  // Network
      $player =  SHIVA_NETWORK_EDITOR;
      break;
    case 11:  // Draw
      $player = SHIVA_DRAW_EDITOR; 
      break;
    case 12:  // Earth
      $player = SHIVA_EARTH_EDITOR; 
      break;*/
    case 13: // Timeglider
      $player =  SHIVA_TIMEGLIDER_EDITOR;
      break;
    /*case 14: // Poster
      $player =  SHIVA_POSTER_EDITOR;
      break;*/
    case 15: // Word Cloud
      $player =  SHIVA_WCLOUD_EDITOR;
      break;
    case 16: // Graph
      $player =  SHIVA_GRAPH_EDITOR;
      break;
		case 17: // Qmedia Multimedia
			$player = SHIVA_QMEDIA_EDITOR;
			break;
  }
  // If $player is not set after that, set it to the viewer and add node id to it
	if (!$player) {
		$player = SHIVA_VIEWER;
		if($nid) {
			$nurl = url('/data/json/' . $nid, array('absolute'=>TRUE));
			$nurl = preg_replace('/https?:/','', $nurl);
			$player .= '?m=' . $nurl;
		}
	} else if ($opt != 1 && $opt != 17) {
    $player = variable_get('shivanode_shiva_home', SHIVA_HOME) . $player; 
  }

	$dsuff = (strpos($player, '?') === FALSE) ? '?pr=d' : '&pr=d';
  $player = $player . $dsuff;
  $player = preg_replace('/https?\:\/\//', '//', $player); // added 2013-08-19 for Firefox 23 which blocks mixed content in iframes
  return $player;
}

/**
 * _shivanode_node_api: Return an html fragment for displaying a node
 */
function _shivanode_node_api($mode, $nid, $jsonp=FALSE) {
	$node = node_load($nid);
	switch($mode) { 
		case "ajax":
			$view = node_view($node, 'full');
			$rendered = drupal_render($view);
			$rendered = str_replace('class="vis-infoshare share-link', 'class="vis-infoshare share-link hidden', $rendered);
			$rendered .= '<script type="text/javascript" src="/sites/all/modules/contrib/jquery_update/replace/jquery/1.10/jquery.js"></script>
                    <script type="text/javascript">(function($){
                    $(".node-shivanode .vis-kmaps .vis-kmaps-show-link").click(function() {
                       var parentclass = $(this).parent().attr(\'class\');
                       $(".kmap-content:visible").not("." + parentclass).hide();
                       $(".kmap-content." + parentclass).toggle();
                   });
                   // Enable close icon for kmap popover (here)
                   $("a.vis-kmaps-close").click(function() {
                       $(this).parent().hide();
                   });
                   // When click on page outside of kmap popover, close any kmap popover that is open
                   $(".site-banner, .titlearea.banner, .node-shivanode .visualization, .footer").click(function() {
                       $(".kmap-content:visible").hide();
                   });
                })(jQuery);</script>';
            if ($jsonp) {
                header('Content-type:application/javascript');
                $rendered = preg_replace('/\s/', ' ', trim($rendered));
                $rendered = preg_replace('/ {2,}/', ' ', $rendered);
                preg_match('/(<iframe [^>]+>\s*<\/iframe>)/', $rendered, $mtch);
                $out = '<div><h2><a href="' . url('node/' . $node->nid) . '" target="_blank">' . $node->title . '</h2>' . $mtch[1] . '</div>';
                print 'cite(' . json_encode($out) . ')';
            } else {
        			print $rendered;
            }
			break;
		case "json":
			drupal_json_output($node);
			break;
		default:
			drupal_set_message(t("The API mode, @mode, has not been defined.", array('@mode' => $mode)), 'warning');
			drupal_goto();
	}
}

/*
 * _shivanode_node_json($nid): Function called by the menu path 'data/json/%' in shivanode_menu
 * 		This function retreives the node, gets its SHIVA json data and publishes that
 * 		Returned in jsonp format for the new viewer.
 */
function _shivanode_node_json($nid, $display) {
	global $user;
  $pwd = '';
  if (strpos($nid,'-') > -1) {
    $pts = explode('-',$nid);
    $nid = $pts[0];
    $pwd = $pts[1];
  }
  $node = node_load($nid);
  // only return JSON if private, or Drupal has added key for embedded visualizations
  if ($node && (_shivanode_get_access($node) == '4' || (is_object($user) && $user->uid == $node->uid) || $pwd == md5($node->title))) { 
    $json = '';
    drupal_add_http_header('Content-Type', 'application/javascript'); // JSONP is actually Javascript
    $json =  _shivanode_get_json($node, FALSE); // FALSE means do NOT return a PHP Object but a JSON string
    if($display == "teaser") {
    	$json = _shivanode_get_json($node, TRUE);
			$json['height'] = variable_get('shivanode_teaser_height', SHIVA_IFRAME_HEIGHT_TEASER);
			$json['width'] = variable_get('shivanode_teaser_width', SHIVA_IFRAME_WIDTH_TEASER);
			$json = json_encode($json);
    }
    $json = 'shivaDataWrapper(' . $json . ')'; // drupal_json_encode means turn a PHP object into JSON text
    echo $json;
  } else {
    echo 'shivaDataWrapper("private" : true)';
  }
}

function _shivanode_search_json($q) {
  //if(!isset($_GET['q']) && !isset($_POST['q']) && !isset($_GET['uid']) && !isset($_POST['uid'])) {
  //  return '{\'msg\': \'Cannot return all nodes. A user or query must be set.\'}';
  //}
  $q = '';
  $uid = '';
  $ntype = '';
  $etype = '';
  if (isset($_GET['q']) || isset($_GET['uid'])) {
    $q = (isset($_GET['q']))?$_GET['q']:'';
    $uid = (isset($_GET['uid']))?$_GET['uid']:'';
    $ntype = (isset($_GET['ntype']))?$_GET['ntype']:'shivanode';
    $etype = (isset($_GET['etype']))?$_GET['etype']:'';
  } 
  elseif (isset($_POST['q']) || isset($_POST['uid'])) {
    $q = (isset($_POST['q']))?$_POST['q']:'';
    $uid = (isset($_POST['uid']))?$_POST['uid']:'';
    $ntype = (isset($_POST['ntype']))?$_POST['ntype']:'shivanode';
    $etype = (isset($_POST['etype']))?$_POST['etype']:'';
  }
  $conditions = array();
  $conditions[] = array(
    'key' => 'n.type',
    'val' => $ntype,
  );
  if ($uid != '') {
    $conditions[] = array(
      'key' => 'n.uid',
      'val' => $uid,
    );
  }
  if ($etype != '') {
    $conditions[] = array(
      'key' => 'n.shivanode_element_type',
      'val' => $etype,
    );
  }
  //echo drupal_json_encode(_shivanode_search($q,$conditions));
}

/* code initially copied from node_search_execute */
function _shivanode_search($keys = NULL, $conditions = NULL) {
   // Build matching conditions
  $query = db_select('search_index', 'i', array('target' => 'slave'))->extend('SearchQuery')->extend('PagerDefault');
  $query->join('node', 'n', 'n.nid = i.sid');
  $query
    ->condition('n.status', 1)
    ->addTag('node_access')
    ->searchExpression($keys, 'node');
  
  if ($conditions != NULL) {
    foreach ($conditions as $cond) {
      $query->condition($cond['key'], $cond['val']);
    }
  }

  // Insert special keywords.
  $query->setOption('type', 'n.type');
  $query->setOption('language', 'n.language');
  if ($query->setOption('term', 'ti.tid')) {
    $query->join('taxonomy_index', 'ti', 'n.nid = ti.nid');
  }
  // Only continue if the first pass query matches.
  if (!$query->executeFirstPass()) {
    return array();
  }

  // Add the ranking expressions.
  //_node_rankings($query);

  // Load results.
  $find = $query
    ->limit(10)
    ->execute();
  $results = array();
  foreach ($find as $item) {
    // Build the node body.
    $node = node_load($item->sid);
    node_build_content($node, 'search_result');
    $node->body = drupal_render($node->content);

    // Fetch comments for snippet.
    $node->rendered .= ' ' . module_invoke('comment', 'node_update_index', $node);
    // Fetch terms for snippet.
    $node->rendered .= ' ' . module_invoke('taxonomy', 'node_update_index', $node);

    $extra = module_invoke_all('node_search_result', $node);

    $results[] = array(
      'link' => url('node/' . $item->sid, array('absolute' => TRUE)), 
      'type' => check_plain(node_type_get_name($node)), 
      'title' => $node->title, 
      'user' => theme('username', array('account' => $node)), 
      'date' => $node->changed, 
      'node' => $node, 
      'extra' => $extra, 
      'score' => $item->calculated_score, 
      'snippet' => search_excerpt($keys, $node->body),
    );
  }
  return $results;
}


/**
 * Function _shivanode_resource_index: 
 *    Return an array of optionally paged nids baed on a set of criteria.
 *
 * Copied from _node_resource_index in the services/resources/node_resources.inc file.
 * Modified to use "var" instead of "parameters" and to include a tags search on Taxonomy tags
 * 
 * An example request might look like
 *
 * http://domain/endpoint/node?fields=nid,title&var[tags]=India,Temple&parameters[uid]=1
 *
 * This would return an array of objects with only nid and title defined, which
 * have either the tage India or Temple and were created by UID = 1.
 *
 * @param $page
 *   Page number of results to return (in pages of 20).
 * @param $fields
 *   The fields you want returned.
 * @param $var
 *   An array containing fields and values used to build a sql WHERE clause
 *   indicating items to retrieve.
 * @param $page_size
 *   Integer number of items to be returned.
 * @return
 *   An array of node objects.
 *
 * @todo
 *   Evaluate the functionality here in general. Particularly around
 *     - Do we need fields at all? Should this just return full nodes?
 *     - Is there an easier syntax we can define which can make the urls
 *       for index requests more straightforward?
 */
function _shivanode_resource_index($fields, $var, $page, $page_size) {
  module_load_include('inc', 'services', 'services.module');
  $node_select = db_select('node', 't')
    ->addTag('node_access')
    ->orderBy('sticky', 'DESC')
    ->orderBy('created', 'DESC');
    
  // Add type = shivanode
  $node_select->condition('t.type', 'shivanode');
  /* 
  // set type to Shivanode
    if(!isset($var['type'])) {
      $var['type'] = 'shivanode';
    }*/
  
  
  // if var[tags] is set, find all shivanodes with the tid values
  // Just searches in the taxonomy vocabularies. Must do something different for KMAPS

  if (isset($var['tags'])) {
    $tags = $var['tags'];
    $delim = 'or';
    if (is_string($tags) && strpos($tags, ',') > -1 ) {
      $tags = explode(',', $tags); 
    }
    if (is_string($tags) && strpos($tags, '+') > -1 ) {
      $tags = explode('+', $tags);
    }
    $nids = _shivanode_taxterms_to_nids($tags, $delim);
    if (is_array($nids)) {
      if (count($nids) == 0) {
        return $nids; 
      }
      $node_select->condition('t.nid', $nids, 'IN');
    }
  }
  unset($var['tags']);
  // If UID is a true string, it's users name, so find the ID
  if (isset($var['uid']) && !is_numeric($var['uid'])) {
    if ($var['uid'] == 'my') {
      global $user;
      $var['uid'] = $user->uid;
    }
    $snuser = user_load_by_name($var['uid']);
    if (isset($snuser->uid)) {
      $var['uid'] = $snuser->uid;
    }
  }
  
  // Allow for use of fields=all
  if ($fields == 'all') {
    $fields = '*';
  }
  
  $gid = 0;
  // Search for nodes belonging to gid, if Og exists
  if (module_exists('og')) {
    if (isset($var['gid']) || isset($var['gnid']))  {
      // if gid variable is set, looking for a gid
      if (isset($var['gid']) ) {
        $gid = $var['gid'];
        unset($var['gid']); 
      } 
      else { 
        // if gnid is set, looking for a group by nid so convert to gid
        $gnid = $var['gnid'];
        unset($var['gnid']);
        $oggroup = og_get_group('node', $gnid);
        if (isset($oggroup->gid)) {
          $gid = $oggroup->gid;
        }
      }
      $var = '';
      $fields = '*';
      $node_select->join('field_data_group_audience', 'g', 't.nid=g.entity_id');
      $node_select->fields('g', array('group_audience_gid'))
        ->condition('g.group_audience_gid', $gid);
    }
  } 
  
  // Add the Shivanode JSON field to output
  if (strpos($fields, 'json') || $fields == '*') {
    $node_select->join('field_data_shivanode_json', 'j', 't.nid=j.entity_id');
    $node_select->addField('j', 'shivanode_json_value', 'json');
    // take out the json field from the list now that it is dealt with
    $fields = implode(',', _shivanode_array_remove_value(explode(',', $fields), 'json'));
  }
  services_resource_build_index_query($node_select, $page, $fields, $var, $page_size, 'node');

  if (!user_access('administer nodes')) {
    $node_select->condition('status', 1);
  }
  
  $results = services_resource_execute_index_query($node_select);
  $nodes = services_resource_build_index_list($results, 'node', 'nid');
  foreach ($nodes as $node) {
    $node->uri = str_replace('/node/', '/shivanode/', $node->uri) . '.json';
  }
  return $nodes;
}

/*
 * _shivanode_taxterms_to_nids($tags, $delim):
 *     Takes and array of tags and returns nids of shivanodes that match
 *     $tags: an array of various tags
 *      $delim: defaults to 'or', using 'and' will require all tags match in each node
 */ 

function _shivanode_taxterms_to_nids($tags, $delim = 'or') {
  if (!is_array($tags)) {
    $tags = array($tags); 
  }
  $out = array();
  $tids = array();
  
  // Turn Terms into term ids (tids)
  foreach ($tags as $key => $term) {
    $term = strtolower($term);
    $query = db_select('taxonomy_term_data', 't')
      ->fields('t', array('tid', 'name'))
      ->where('LOWER(t.name) = :term', array(':term' => $term));
    $result = $query->execute();
    foreach ($result as $record) {
      $tids[] = $record->tid;
    }
  }
  if (count($tids) == 0 ) {
    return $tids; 
  }
  
  // Find nodes with those terms
  // The basic query
  $query = db_select('field_data_shivanode_tags', 'f')
    ->fields('f', array('entity_id', 'shivanode_tags_tid'));
  if ($delim == 'and') {
    // the 'and' conditions
    foreach ($tids as $n => $tid) {
      $query->condition('f.shivanode_tags_tid', $tid, '=');
    }
  } 
  else {
    // the 'or' condition
    $query->condition('f.shivanode_tags_tid', $tids, 'IN');
  }
  
  // Perform query and put resulting nids in the out array removing duplicates
  $results = $query->execute();
  foreach ($results as $result) {
    $out[] = $result->entity_id;
  }
  return array_unique($out);
}

function _shivanode_array_remove_value($array, $item) {
  $i = -1;
  foreach ($array as $n => $value) {
    if ($value == $item) {
      $i = $n;
      break;
    }
  }
  if ( $i > -1 ) {
    unset($array[$i]);
  }
  return $array;
}

// For the Retreive service of shivanode
//   converts node->shivanode_json['und'][0]['value'] to node->json
function _shivanode_resource_retrieve($nid) {
  $node = node_load($nid);
  if ($node) {
    $uri = entity_uri('node', $node);
    $node->path = url($uri['path'], array('absolute' => TRUE));
    // Unset uri as it has complete entity and this
    // cause never ending recursion in rendering.
    unset($node->uri);
  }
  $node->json = $node->shivanode_json['und'][0]['value'];
  unset($node->shivanode_json);
  
  // add the tag name for each tag id
  if (isset($node->shivanode_tags['und']) && is_array($node->shivanode_tags['und'])) {
    foreach ($node->shivanode_tags['und'] as $n => &$t) {
      $query = db_select('taxonomy_term_data', 't')
        ->fields('t', array('tid', 'name'))
        ->condition('t.tid', $t['tid'], '=');
      $result = $query->execute();
      foreach ($result as $record) {
        $t['name'] = $record->name;
      }
    }
  }
  
  // add the kmap category name for each kmap tag id
  if (isset($node->field_kmap_tags['und']) && is_array($node->field_kmap_tags['und'])) {
    foreach ($node->field_kmap_tags['und'] as $n => &$t) {
      $query = db_select('taxonomy_term_data', 't')
        ->fields('t', array('tid', 'name'))
        ->condition('t.tid', $t['tid'], '=');
      $result = $query->execute();
      foreach ($result as $record) {
        $t['name'] = $record->name;
        $t['done'] = TRUE;
      }
    }
  }
  return $node;
}

/**
 * Returns the visualization type in different formats:
 * 
 * 	format values:
 * 		'string' = machine name (default) returns machine name
 * 		'label' =  label returns capitalized label string
 *    'number/int' = index return index value
 * 
 * if not set returns default value
 */
function _shivanode_get_element_type($node, $format="string") {
	  module_load_include('inc', 'shivanode', 'includes/shivanode.types');
      $typenum = 7; // default value;
      if (isset($node->shivanode_element_type['und'][0]['value'])) {
          $typenum = intval($node->shivanode_element_type['und'][0]['value']);
      } else {
          $nid = $node->nid;
          if (strpos(current_path(), $nid . '/edit') > -1) {
            drupal_set_message(t('Node @num does not have a visualization type!', array('@num' => $node->nid)), 'warning', FALSE);
          }
      }
      //if ($typenum == 5) { $typenum = 13; } // do we still need to look out for simile?
      if ($format == 'label') {
      	return _shivanode_get_type_label($typenum);
      } elseif ($format == 'number' || $format == 'int') {
      	return $typenum;
      } else {
		return _shivanode_get_machine_name($typenum);
	  }
}

/*
 * Gets a subtype of visualization in the Shiva node in different Formats:
 * 
 * 	format values:
 * 		'string' = machine name (default) returns machine name
 * 		'label' =  label returns capitalized label string
 *    'number/int = index return index value
 * 
 */
function _shivanode_get_subtype($node, $format = 'string') {
	module_load_include('inc', 'shivanode', 'includes/shivanode.types');
	$subtypenum = (isset($node->shivanode_subtype['und']['0']['value'])) ?  $node->shivanode_subtype['und']['0']['value'] : 11; // default is pie chart
  if ($format == 'label') {
  	return _shivanode_get_type_label($subtypenum, TRUE);
  } elseif ($format == 'number' || $format == 'int') {
  	return $subtypenum;
  } else {
		return _shivanode_get_machine_name($subtypenum, TRUE);
	}
}

function _shivanode_get_json($node, $as_obj = TRUE) {
  if (gettype($node) != "object") { $node = node_load($node); }
  if (isset($node->shivanode_json)) {
    $eljson = $node->shivanode_json['und'][0]['value'];
    return ($as_obj) ? drupal_json_decode($eljson) : $eljson;
  } 
  else {
    return 11; // default is 11 or pie chart
  }
}

/* _shivanode_get_tags() : 
 * 
 *  Returns an array of tag objects for shivanodes
 * 
 */
function _shivanode_get_tags() {
  $vs = taxonomy_get_vocabularies('shivanode');
  $vids = array();
  foreach ($vs as $voc) {
    if ($voc->module == 'taxonomy') {
      array_push($vids, $voc->vid);
    }
  }
  $size = 60;
  $tags = array();
  $result = db_query_range('SELECT COUNT(*) AS count, td.tid, td.vid, td.name, td.description FROM {taxonomy_term_data} td INNER JOIN {taxonomy_index} tn ON td.tid = tn.tid INNER JOIN {node} n ON tn.nid = n.nid WHERE td.vid IN (' . implode(',', array_fill(0, count($vids), '?')) . ') GROUP BY td.tid, td.vid, td.name, td.description HAVING COUNT(*) > 0 ORDER BY count DESC', 0, $size, $vids);
  foreach ($result as $tag) {
    $tags[$tag->tid] = $tag;
  }
  return $tags;
}


function _shivanode_is_deprecated($tindex, $isSubtype=FALSE) {
	module_load_include('inc', 'shivanode', 'includes/shivanode.types');
	return _shivanode_is_type_deprecated($tindex, $isSubtype);
}

/*
 * 
 */
function _shivanode_node_embed_page($nid) {
	global $base_url, $base_path;
	$node = node_load($nid);
	// Starting code for sharing url pattern: node/###/share
	// example taken from http://papermashup.com/simple-jquery-tabs/
	$bcontent = FALSE;
	$selcontent = '
    <ul class="nav nav-tabs" role="tablist">
    	 <li class="active"><a href="#tab-sm" aria-controls="profile" role="tab" data-toggle="tab" aria-expanded="true">Social Media</a></li>
	     <!--<li><a href="#tab-cf" aria-controls="profile" role="tab" data-toggle="tab">Confluence</a></li>-->
	     <li><a href="#tab-wp" aria-controls="profile" role="tab" data-toggle="tab">WordPress</a></li>
	     <li><a href="#tab-if" aria-controls="profile" role="tab" data-toggle="tab">IFrame</a></li>
	     <li><a href="#tab-lk" aria-controls="profile" role="tab" data-toggle="tab">Link</a></li>
	     <li><a href="#tab-url" aria-controls="profile" role="tab" data-toggle="tab">URL</a></li>
	     <li><a href="#tab-js" aria-controls="profile" role="tab" data-toggle="tab">JSON</a></li>
   </ul>'; // <aside class="content-resources col-xs-6 col-sm-3 col-md-3 col-lg-2 sidebar-offcanvas"></aside>
    $smtab = '';
	if(module_exists('sharethis')) {
	    // add meta tag for share image
	    // Can also be done through custom JS adding chicklets as outlined on http://support.sharethis.com/customer/portal/articles/475079-share-properties-and-sharing-custom-information
	    // but have been unable to get thumnail and node name to be shared.
	    _shivanode_add_share_meta($node);
	    $block = module_invoke('sharethis', 'block_view', 'sharethis_block');
	    $bcontent = $block['content'];
	    $bcontent = preg_replace('/node\/(\d+)\/share/','node/$1', $bcontent);
	    $bcontent = preg_replace('/stLight.options\(\{"publisher"\:"([^"]+)"/','stLight.options({"publisher":"$1", "onhover":"false", "doNotCopy":"true"', $bcontent);
	    $imgurl = _get_thumb_image($node);
	    $bcontent = preg_replace('/st\_title=""/','st_title="' . $node->title . '" st_image="' . $imgurl . '" ', $bcontent);
	    //$selcontent = str_replace(' style="display:none;"', '', $selcontent);
	    $smtab = '<div role="tabpanel" class="tab-pane active" id="tab-sm""><h3>Social Media</h3>' . str_replace('display: none;','', $bcontent) . '<p>Click on a button to share this visualization through the desired social media site. <br/> ' .
					'Don\'t see your preferred social media site? Then let us know by <a href="/contact" target="_blank">clicking here</a>.</p></div>';
	}

	$nurl = variable_get('shivanode_chart_viewer', SHIVA_VIEWER) . '?m=' . preg_replace('/https?\:/','', $base_url) . $base_path . 'data/json/' . $nid;
  $nurl = preg_replace('/https?:/', '', $nurl);
	$njson = _shivanode_get_json($nid);
	$width = isset($njson['width'])? $njson['width'] : '800';
	$height = isset($njson['height']) ? $njson['height'] : '800';
 
	$page =  array(
	    'head' => array(
	      '#type' => 'markup',
	      '#prefix' => '<div id="sharetabs">',
	      '#markup' => '<h2>How To Share <i>' . $node->title . '</i></h2>',
	    ),
	   /* 'instructions' => array(
	    	'#type' => 'markup',
	    	'#markup' => '<p>' . t('Choose the format you would like to use and copy the resulting code to your site.') . '</p>',
		),*/

	    'selectors' => array(
	    	'#type' => 'markup',
	    	'#markup' => $selcontent,
	      '#suffix' => '<div class="tab-content">',
		),
		'tabsm' => array(
			'#type' => 'markup',
			'#markup' => $smtab
		),
		/**  Removed because confluence no longer supports IFrames. To reenble also uncomment link above for tab
         * 'tabcf' => array(
			'#type' => 'markup',
			'#markup' => '<div role="tabpanel" class="tab-pane" id="tab-cf"><h3>Confluence</h3><p>Cut and paste the following macron into the "Wiki Markup" view of your Confluence site page:</p>' .
						'<pre class="code">{iframe:src=' . $nurl . '|width=' . $width .
						 '|height=' . $height .  '}Your browser does not support iframes{iframe}</pre>' .
						'<p>For information on other iframe macro parameters see the <a href="http://www.adaptavist.com/display/AtlassianConfluence/iframe+macro" target="_blank">Confluence IFrame Macro Overview</a>.</p> </div>'
		),*/
		'tabwp' => array(
			'#type' => 'markup',
			'#markup' => '<div role="tabpanel" class="tab-pane" id="tab-wp"><h3>WordPress</h3><p>Cut and paste the following code into your WordPress site: </p>' . 
						'<pre class="code">[iframe src="' . $nurl . '" width="' . $width . '" height="' . $height . '"]</pre>' .
						'<p>For information on other iframe parameters see the <a href="http://wordpress.org/extend/plugins/iframe/other_notes/" target="_blank">WP IFrame Plugin Notes</a>.</p> </div>'
		),
		'tabif' => array(
			'#type' => 'markup',
			'#markup' => '<div role="tabpanel" class="tab-pane" id="tab-if"><h3>IFrame</h3><p>Use this HTML code to put an iframe of this visualization on a web page: </p> ' .
							'<pre class="code">&lt;iframe src="' . $nurl . '" height="' . $height .  '" width="' . $width . '"></iframe></pre></div>'
		),
		'tablk' => array(
			'#type' => 'markup',
			'#markup' => '<div role="tabpanel" class="tab-pane" id="tab-lk"><h3>Link</h3><p>To link to this visualization on a web page use the following link code: </p>' .
							'<pre class="code">&lt;a href="' . $nurl . '">' . $node->title .  '&lt;/a></pre></div>'
		),
		'taburl' => array(
			'#type' => 'markup',
			'#markup' => '<div role="tabpanel" class="tab-pane" id="tab-url"><h3>URL</h3><p>The public URL to view this visualization is: </p>' .
							'<p><a href="' . $nurl . '" target="_blank">http:' . $nurl . '</a></p></div>'
		),
		'tabjs' => array(
			'#type' => 'markup',
			'#markup' => '<div role="tabpanel" class="tab-pane" id="tab-js"><h3>JSON Data</h3><p>The JSON code that defines this visualization is: </p>' .
							'<pre class="code">' . prettyJson(json_encode($njson)) . '</pre></div>'
		),
		'closing' => array(
			'#type' => 'markup',
			'#markup' => '',
			'#suffix' => '</div></div>',
		),
	);
	return $page;
}


/**
 * Indents a flat JSON string to make it more human-readable.
 *   Taken from: http://www.daveperrett.com/articles/2008/03/11/format-json-with-php/
 */
 
function prettyJson($json) {

    $result      = '';
    $pos         = 0;
    $strLen      = strlen($json);
    $indentStr   = '  ';
    $newLine     = "\n";
    $prevChar    = '';
    $outOfQuotes = true;

    for ($i=0; $i<=$strLen; $i++) {

        // Grab the next character in the string.
        $char = substr($json, $i, 1);

        // Are we inside a quoted string?
        if ($char == '"' && $prevChar != '\\') {
            $outOfQuotes = !$outOfQuotes;

        // If this character is the end of an element,
        // output a new line and indent the next line.
        } else if(($char == '}' || $char == ']') && $outOfQuotes) {
            $result .= $newLine;
            $pos --;
            for ($j=0; $j<$pos; $j++) {
                $result .= $indentStr;
            }
        }

        // Add the character to the result string.
        $result .= $char;

        // If the last character was the beginning of an element,
        // output a new line and indent the next line.
        if (($char == ',' || $char == '{' || $char == '[') && $outOfQuotes) {
            $result .= $newLine;
            if ($char == '{' || $char == '[') {
                $pos ++;
            }

            for ($j = 0; $j < $pos; $j++) {
                $result .= $indentStr;
            }
        }

        $prevChar = $char;
    }

    return $result;
}

// Add meta tag for facebook sharing to include title, desc, and a custom image/icon
function _shivanode_add_share_meta($node) {
  global $base_root, $base_path;
  //$imgurl = 'https://shiva.virginia.edu/sites/shiva/files/shivathumbs/hinduism-in-africa.PNG';
  $imgurl = _get_thumb_image($node);
  $element = array(
    '#tag' => 'meta',
    '#attributes' => array(
       "property" => "og:image",
       "content" => $imgurl,
     ),
  );
  drupal_add_html_head($element, 'og_image');
  
  // Add Meta Title tag
  $element = array(
    '#tag' => 'meta',
    '#attributes' => array(
       "property" => "og:title",
       "content" => $node->title,
     ),
  );
  drupal_add_html_head($element, 'og_title');
  
  // Add Meta Description
  $desc = 'A visualization created with the SHIVA application provided by SHANTI at the University of Virginia (http://visuals.shanti.virginia.edu/)';
  if(isset($node->shivanode_description['und'][0])) {
    if($node->shivanode_description['und'][0]['safe_summary'] != '') {
      $desc = trim(strip_tags($node->shivanode_description['und'][0]['safe_summary']));
    } else {
      $desc = trim(strip_tags($node->shivanode_description['und'][0]['safe_value']));
    }
  }
  $element = array(
    '#tag' => 'meta',
    '#attributes' => array(
       "property" => "og:description",
       "content" => $desc,
     ),
  );
  drupal_add_html_head($element, 'og_desc');
  
  // Meta URL
  $url = $base_root . $base_path . 'node/' . $node->nid;
  $element = array(
    '#tag' => 'meta',
    '#attributes' => array(
       "property" => "og:url",
       "content" => $url,
     ),
  );
  drupal_add_html_head($element, 'og_url');
}

function _shivanode_get_access($node) {
  if(isset($node->shivanode_access)) {
    $access = $node->shivanode_access;
    if(isset($access['und'])) {
      if(isset($access['und'][0])) {
        if(isset($access['und'][0]['value'])) {
          return $access['und'][0]['value'];
        }
      }
    }
  }
  return null;
}

/**
 * Gets thumbnail image for a visualization
 * 
 * @param object $node
 * 	The node that is a single search result
 * 
 */
function _get_thumb_image($node, $mode='url') {
  global $base_path;
	if (is_numeric($node)) { $node = node_load($node); }
  // Add image meta tag (og:image)
  //  e.g. <meta property="og:image" content="Image url here">
  $imgurl = url($base_path . drupal_get_path('module', 'shivanode') . '/images/sngen-chart-default.png', array('absolute' => TRUE)); // Default url for when there is no thumbnail
  if (isset($node->field_image['und'][0]['uri']) ) {
    $imgurl = file_create_url($node->field_image['und'][0]['uri']);
  } 
  if ($mode == 'img') { drupal_goto($imgurl); }
  return $imgurl;
}

function is_theme($tk) {
  global $theme_key;
  return ($theme_key == $tk) ? TRUE : FALSE ;
} 

function get_theme_info($tk) {
  global $theme_key;
  $themes = list_themes();
  return $themes[$theme_key];
} 

function _shivanode_popup_page($content) {
  drupal_send_headers();
  $out = drupal_render($content);
  print '<html><body>' . $out . '</body></html>';
}

function _shivanode_add_ms_metafix() {
  $meta = array(
    '#tag' => 'meta',
    '#attributes' => array(
      "http-equiv" => "X-UA-Compatible",
       "content" => "IE=Edge",
    ),
    '#weight' => '-99999', // To put it first in the head element
  );
  drupal_add_html_head($meta, 'iemetatag');
}

/**
 * Function get Help link
 *    Returns the html link code for the help page depending on the shivanode type value sent to function
 *
 * 		@param int $typeInd 
 *			Index of type or subtype value. Default -1 means general help string
 * 		@param boolean $isSubtype 
 * 			Indicates whether index is a subtype or not. Defaults to FALSE
 * 		@param mixed $linkStr 
 * 			String to include in link or FALSE if question mark icon is desired
 * 
 **/
function _shivanode_get_help_link($typeInd=-1, $isSubtype=FALSE, $linkStr=FALSE) {
  global $base_root;
	module_load_include('inc', 'shivanode', 'includes/shivanode.types');
	$helpurls = _shivanode_get_help_urls();
	if (!is_int($typeInd)) { $typeInd = _shivanode_get_type_index($typeInd, $isSubtype); }
  $hurl = 'https://wiki.shanti.virginia.edu/display/KB/Use+SHIVA';
  $label = 'Shiva Help'; 
	if ($typeInd > -1) {
		$hurl = ($isSubtype) ? $helpurls['subtypes'][$typeInd] : $helpurls['types'][$typeInd];
		$label = _shivanode_get_type_label($typeInd, $isSubtype);
	} else {
		$label = t('Visualization');
	}
  if ($linkStr) {
    return '<a href="' . $hurl . '" target="_blank" title="' . str_replace(' visualization type', '', $linkStr) . ' Help" >' . $linkStr . '</a>';
  } else { 
    return '<a class="sn-helplink" href="' . $hurl . '" target="_blank" title="' . $label . ' Help" ><img src="' . 
              $base_root . '/' .  drupal_get_path('module','shivanode') . '/images/help-bluer-3d-16px.png" /></a>';
  }
}

/**
 * _shivanode_get_generic_image_info($type): 
 *    A function that returns the variable name for the generic image of a certain type of visualization
 *    These Drupal variables contain the FID for the generic thumbnail for that type of visualization
 *    If $type is set to ALL (default), returns an named array of visualization type/variable name pairs
 *    If $type is set to a particular image type, it returns that variable name if set.
 *    Variables are set in shivanode.install (update 7005)
 * 
 *    The variable names must also be the name of the .png image file of the thumb. Generic Images are set for nodes in shivanode_node_presave($node).
 */
function _shivanode_get_generic_image_info($type = 'ALL', $isSubtype = FALSE) {
 
	$imgs = _shivanode_get_thumb_image_list(); // function in shivanode.types.inc
  if ($type == 'ALL') {
    return $imgs;
  } else if ($type == 'LIST') {
  	$out = array();
		foreach($imgs['types'] as $tind => $img) { $out[] = $img; }
		foreach($imgs['subtypes'] as $stind => $img) { $out[] = $img; }
		return $out;
  } else {
  	$ind = ($isSubtype) ? 'subtypes' : 'types';
	  if (isset($imgs[$ind][$type])) {
	    return variable_get($imgs[$ind][$type], FALSE);
	  } else {
	    return FALSE;
	  }
	}
}

function _shivanode_get_kmap_fields() {
	$kmfields = array();
	$fis = field_info_instances('node', 'shivanode');
	foreach($fis as $key => $field) {
	  if(isset($field['display']['default']['module']) && $field['display']['default']['module'] == 'shanti_kmaps_fields') {
	    $kmfields[] = $field['field_name'];
	  }
	}
	return $kmfields;
}

function _shivanode_get_nodes_by_kmap($kid, $domain = 'subjects', $nodes = TRUE) {
	$kmf = _shivanode_get_kmap_fields();
	$out = array();
	foreach($kmf as $fn) {
		$fif = field_info_field($fn);
		$fdom = $fif['settings']['kmap_domain'];
		if($fdom == $domain) {
	    $table = 'field_data_' . $fn;
	   	$col = $fn . '_id';
			if($kid == 'all') {
	    	$result = db_select($table, 't')->fields('t')->condition('t.' . $col, 0, '<>')->execute();
				foreach($result as $record) {
					$kmid = $record->{$col};
					if(isset($out[$kmid])) {
						$out[$kmid][] = $record->entity_id;
					} else {
						$out[$kmid] = array($record->entity_id);
					}
				}
			} else {
	    	$result = db_select($table, 't')->fields('t')->condition('t.' . $col, $kid, '=')->execute();
		    foreach($result as $record) {
		      $out[] = ($nodes) ? node_load($record->entity_id) : $record->entity_id;
		    }
			}
	  }
	}
	if(empty($out)) { return FALSE; }
	return $out;
}

/**
 * Returns a list of shivanodes associated with a particular kmap id
 *   TODO: implement pagination, list page (perhaps in views?)
 *   Example URL: http://shivamanager.dev/kmaps/json/places/15885
 *   
 */
function _shivanode_kmap_list($type, $kid, $domain = 'subjects') {
	$nodes = _shivanode_get_nodes_by_kmap($kid, $domain);
	if($type == 'json') { 
		$out = array(
			'total' => count($nodes),
			'type' => $domain, 
			'kmid' => $kid,
			'results' => $nodes,
		);
		drupal_json_output($out);
	}
}
