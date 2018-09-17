<?php

/**
 * @file
 * template.php
 */

/**
 *   This is the template.php file for Sarvaka Shiva, a child sub-theme of the Shanti Sarvaka theme.
 *
 */

/**
* Implements hook admin paths
*
*  Define custom paths that are either admins or not.
*/
function sarvaka_shiva_admin_paths_alter(&$paths)
{
    $paths['node/*/group'] = FALSE;
    $paths['group/node/*/admin/people'] = FALSE;
    $paths['group/node/*/admin/people/*'] = FALSE;
}

function sarvaka_shiva_menu_local_tasks_alter(&$data, $router_item, $root_path)
{
    // Replace title of tab "Group" with "Members"
    if (!empty($data['tabs'][0]['output'])) {
        foreach ($data['tabs'][0]['output'] as $n => &$tab) {
            if ($tab['#link']['path'] == 'node/%/group') {
                $tab['#link']['title'] = t("Members");
            }
        }
    }
} 

 /**
  * Implements hook_menu_breadcrumb_alter
  *     - Adds link to all collections page (collections/all) to collection, subcollection pages and visual pages that belong to a colleciton or subcoll
  */
function sarvaka_shiva_menu_breadcrumb_alter(&$active_trail, $item) {
    $map = $item['map']; // Item map tells us about what page we are on
    if ($map[0] == "node") {
        //dpm($item, 'itme in bc alter');
        $node = $map[1];
        // if it's a collection node, add link to all collections before it's name 
        if (is_object($node) && in_array($node->type, array('collection', 'subcollection')) || $node->type == 'shivanode' && !empty($node->field_og_collection_ref)) {
            $collslink = array(
              'title' => t('Collections'), 
              'href' => 'collections/all', 
              'link_path' => 'collections/all', 
              'localized_options' => array(), 
              'type' => 0,
            );
            $newat = array();
            $newat[0] = array_shift($active_trail);
            $newat[1] = $collslink;
            $active_trail = array_merge($newat, $active_trail);
        } 
    } else if ($item['path'] == 'collections/all' && count($active_trail) == 3 && $active_trail[1]['link_title'] == "Collections") {
        unset($active_trail[1]); // Remove the extra "collections" breadcrumb from user menu set up.
    }  else if ($item['path'] == 'group/%/%/admin/people') {
        $group = node_load($item['page_arguments'][1]);
        $active_trail[1] =  array(
              'title' => $group->title, 
              'href' => url('node/' . $group->nid), 
              'link_path' => url('node/' . $group->nid), 
              'localized_options' => array(), 
              'type' => 0,
            );
            $item = array();
    }
}

/**
 * Implements hook_form_alter
 * 
 * Update views exposed form for gallery filters
 */
function sarvaka_shiva_form_alter(&$form, &$form_state, $form_id) {
    if ($form_id == 'views_exposed_form') {
        if ($form['#id'] == 'views-exposed-form-visuals-galleries-all-vis-page') {
            $form['title']['#size'] = 15;
            $form['shivanode_element_type_value']['#attributes'] = array(  'title' => t('Select a Type') );
        } else if ($form['#id'] == 'views-exposed-form-visuals-galleries-my-vis-page') {
            $form['title']['#size'] = 15;
            $form['shivanode_element_type_value']['#attributes'] = array(  'title' => t('Select a Type') );
            $form['sort_by']['#title'] = '';
            $form['sort_order']['#title'] = '';
        }
    }
}

/**
 * Implements hook_preprocess_node:
 * 		adds variable "can_edit" to determine whether to display an edit button
 * 		creates info popup and share link
 */
function sarvaka_shiva_preprocess_node(&$vars) {
    switch ($vars['type']) {
        case 'shivanode':
            switch ($vars['view_mode'] ) {
                case 'teaser':
                     sarvaka_shiva_preprocess_shivanode_teaser($vars);
                    break;
                case 'full':
                     sarvaka_shiva_preprocess_shivanode_full($vars);
                    break;
            }
            break;
        
        case 'collection':
        case 'subcollection':
            sarvaka_shiva_preprocess_collection($vars);
    }
}

function sarvaka_shiva_preprocess_shivanode_teaser(&$vars) {
    // Add coll data to teasers if it exists
    //dpm($vars, 'vars');
    $vars['coll'] = '';
    if (!empty($vars['field_og_collection_ref'])) {
        if ($coll = node_load($vars['field_og_collection_ref']['und'][0]['target_id'])) {
            $coll->url = url('node/' . $coll->nid);
            $vars['coll'] = $coll;
        }
    }
   $vars['access_string'] = shivanode_get_access_string($vars['node']);
}

function sarvaka_shiva_preprocess_shivanode_full(&$vars) {
    global $user;
    module_load_include('inc', 'shivanode', 'shivanode');

    $author = user_load($vars['uid']);
    $author_link = l($author -> name, 'user/' . $vars['uid']);
    
    // For Shiva Visualization Nodes
    $vars['can_edit'] = FALSE;
    if (node_access('update', $vars['node'], $user)) {
        $vars['can_edit'] = TRUE;
    }
    
    // Link to Data
    $linktxt = '';
    $ndjson = _shivanode_get_json($vars['node']);
    if (!empty($ndjson['dataSourceUrl'])) {
        $linktxt = l(t('External Spreadsheet'), $ndjson['dataSourceUrl'], array('attributes' => array('target' => '_blank')));
    }

    // Type of Visual
    $vtype = "";
    if (!empty($vars['content']['shivanode_element_type'][0]['#markup'])) {
        $vtype = $vars['content']['shivanode_element_type'][0]['#markup'];
        unset($vars['content']['shivanode_element_type']);
    }
    $vsubtype = "";
    if (!empty($vars['content']['shivanode_subtype'][0]['#markup'])) {
        $vsubtype = $vars['content']['shivanode_subtype'][0]['#markup'];
        unset($vars['content']['shivanode_subtype']);
    }
    
    $vstatus = _get_shivanode_access_status($vars['node']);
    unset($vars['content']['shivanode_access']);
    
    // Group info
    $vgroups = '';
    if (!empty($vars['field_og_collection_ref'])) {
        foreach ($vars['field_og_collection_ref'] as $n => $ginfo) {
            if (!empty($ginfo['target_id'])) {
                $gid = $ginfo['target_id'];
                $gnode = $ginfo['entity'];
                $link = l($gnode -> title, "node/$gid");
                $vgroups .= "$link,";
            }
        }
        unset($vars['content']['field_og_collection_ref']);
    }
    $vgroups = trim($vgroups, ' ,');
    $vgrpaccess = "";
    $vars['isprivate'] = FALSE;
    if (!empty($vars['content']['group_content_access'])) {
        $vgrpaccess = $vars['content']['group_content_access'][0]['#markup'];
        // Code to replace "Use Group Defaults" with what that default is
        $el = &$vars['content']['group_content_access'];
        if ($el['#items'][0]['value'] == 0) { // if it is set to use group defaults.
            if (!empty($el['#object']->field_og_collection_ref['und']) && $el['#object']->field_og_collection_ref['und'][0]['target_id']) {
                $gp = node_load($el['#object']->field_og_collection_ref['und'][0]['target_id']);
                $visindex  = $gp->group_access['und'][0]['value'];
                $vis = t("Public");
                if ($visindex == 1  ) { // 1 is private, 0 is public.
                     $vars['isprivate'] = TRUE;
                    $vis = t("Private");
                } else if ($visindex == 2) {
                    $vis = t("UVa Only");
                }
                $vgrpaccess = $vis . t(' (group default)');
            } else {
                $vgrpaccess = t("Public");
            }
        } else {
            $vgrpaccess = ($el['#items'][0]['value'] ==1) ?  t("Public") :  t("Private");
            $vars['isprivate'] = ($el['#items'][0]['value'] ==1) ? FALSE : TRUE;
        }
    }
    unset($vars['content']['group_content_access']); // Unset whether or not there is a group assigned to node
    // Draft visualizations are by default private, despite group setting
    if (strtolower($vstatus) == "draft") {
        $vars['isprivate'] = TRUE;
        $vgrpaccess = t("Private");
    }
    
    // Description
    $desc = '';
    if (isset($vars['shivanode_description'][0]) && !empty($vars['shivanode_description'][0]['safe_value'])) {
        $desc = $vars['shivanode_description'][0]['safe_value'];
        unset($vars['content']['shivanode_description']);
    }
    if (empty($desc)) { $desc = '<i>No description</i>'; }

    $infovars = array(
        'icon' => 'fa-info-circle', 
        'title' => $vars['title'], 
        'vtype' => $vtype, 
        'vsubtype' => $vsubtype, 
        'vstatus' => '',
        'vauthor' => $author_link, 
        'vdate' => date('M j, Y', $vars['created']), 
        'vdata' => $linktxt, 
        'vgroups' => $vgroups, 
        'vgrpaccess' =>$vgrpaccess . ', ' . $vstatus,
        'vdesc' => $desc, //render($desc), 
        'vfooter' => '', 
     );
    $vars['infopop'] = sarvaka_shiva_custom_info_popover($infovars);
    // Variables/markup for Share pop
    $vars['sharepop'] = "<div class=\"share-link\"><a href=\"/node/{$vars['node']->nid}/share?format=simple&amp;class=lightbox\" 
									class=\"sharelink\"
									rel=\"lightframe[|width:800px; height:450px; scrolling: no;]\" 
									title=\"Click to view sharing options\" >
									<span class=\"icon shanticon-share\"></span>
									</a></div>";
}

function sarvaka_shiva_preprocess_collection(&$vars) {
    // Collection Teasers
    if ($vars['view_mode'] == 'teaser') {
        $uri = (isset($vars['field_general_featured_image'][0]['uri'])) ?$vars['field_general_featured_image'][0]['uri'] : $vars['field_general_featured_image']['und'][0]['uri'];
        $vars['thumbnail_url'] = (empty($uri)) ? url('sites/all/themes/shanti_sarvaka/images/default/collections-generic.png') : image_style_url('shiva_collection_teaser', $uri);
        
        $vars['item_count'] = get_items_in_collection($vars['nid']);
        $user = user_load($vars['uid']);
        $vars['user_link'] = l($user->name, 'user/' . $user->uid); // User Link
        // Collection
        $vars['coll'] = '';
        if (!empty($vars['content']['field_og_parent_collection_ref'])) {
            $coll = $vars['content']['field_og_parent_collection_ref']['#items'][0]['entity'];
            $coll->url = url('node/' . $coll->nid);
            $vars['coll'] = $vars['content']['field_og_parent_collection_ref']['#items'][0]['entity'];
        }
        
        // Description
        $vars['desc'] = '';
        if (isset($vars['body']['und'][0]['safe_value'])) {
            $safeval =$vars['body']['und'][0]['safe_value'];
            if (strlen($safeval) > 60) {
                $vars['desc'] = substr($safeval, 0, strpos($safeval, ' ', 60)) . '... </p>';
            } else {
                $vars['desc'] = $safeval;
            }
        }
        
        // Access
        $vars['access'] = '';
        if (isset($vars['group_access']['und'][0]['value']) ) {
            $vars['access'] = ($vars['group_access']['und'][0]['value'] == 0) ? t("Public") : t("Private");
        }
    // End of collection teasers
    }  else {
    // Collection Node Pages
        
    }
}

/**
 * Return the count of number of items in a collection
 */
function get_items_in_collection($coll=FALSE, $return="count") {
    $nids = array();
    if (is_numeric($coll)) {  $coll = node_load($coll); } // Load collection node if id given
    if ($coll) {
        // Get all collection and subcollection nids invovled
        $nids[] = $coll->nid;
        $nids = array_merge($nids, get_subcollections_in_collection($coll));
        /**
         * Sample Query:
         *      select count(etid) from og_membership where entity_type='node' and field_name='field_og_collection_ref' and gid in (3,1721,1725,1769,2228,2258,3498,3939,4836,4835,1760,1748,1841);
         */
        $result = db_select('og_membership', 'ogm')
                            ->fields('ogm', array('etid'))
                            ->condition('entity_type', 'node')
                            ->condition('field_name', 'field_og_collection_ref')
                            ->condition('gid', $nids, 'IN')
                            ->execute();
        $nids = $result->fetchCol();
        $nodes = node_load_multiple($nids);
        $filtered_nids = array();
        foreach ($nodes as $n => $node) {
            if (node_access('view', $node)) {
                $filtered_nids[] = $node->nid;
            }
        }
        if ($return == "nids") {   return $filtered_nids;  }
    }
    return count($filtered_nids);
}

/**
 * Return list of subcollections in collection
 *      Returns an array of nids
 */
 
 function get_subcollections_in_collection($coll=FALSE) {
    $nids = array();
    if (is_numeric($coll)) {  $coll = node_load($coll);   } // convert nid to node
    // Only collections have subcollections
    if ($coll->type == "collection") {
        /**
         * Sample Query:
         *       select etid from og_membership where entity_type='node' and field_name='field_og_parent_collection_ref' and gid=3;
         **/
        $result = db_select('og_membership', 'ogm')
                            ->fields('ogm', array('etid'))
                            ->condition('entity_type', 'node')
                            ->condition('field_name', 'field_og_parent_collection_ref')
                            ->condition('gid', $coll->nid)
                            ->execute();
        $nids = $result->fetchCol();
        //drupal_set_message(count($nids) . ' subcols found');
    }
    $nodes = node_load_multiple($nids);
    $filtered_nids = array();
    foreach ($nodes as $n => $node) {
        if (node_access('view', $node)) {
            $filtered_nids[] = $node->nid;
        }
    }
    return $filtered_nids;
 }

/**
 * Implements hook_preprocess_search_results
 */
function sarvaka_shiva_preprocess_search_result(&$vars) {
    $url = drupal_get_path('theme', 'sarvaka_shiva') . '/images/sngen-chart-default.png';
    $node = $vars['result']['node'];
    $vars['url'] = url("node/{$node->nid}");
    $author = user_load($node -> uid);
    $vars['result']['author'] = l($author -> name, "/user/{$node->uid}");
    $vars['snippet'] = '';
    if (module_exists('shivanode')) {
        module_load_include('inc', 'shivanode', 'includes/shivanode');
        $vars['result']['thumb_url'] = _get_thumb_image($node);
        $vars['result']['sntype'] = _get_shivanode_type($node);
    }
    if (!empty($vars['result']['date'])) {
        $vars['result']['date'] = date('M j, Y', $vars['result']['date']);
    }
}

/**
 * Implements hook_preprocess_views_view_fields
 *
 * Removes width/height settings from thumb images in shiva_visuals_solr view.
 * Not sure where these are coming from.
 *
 * TODO: Find out where height and width settings are coming from for thumbnails and remove. Is it legacy?
 */
function sarvaka_shiva_preprocess_views_view_fields(&$vars) {
    $view = $vars['view'];
    if ($view -> name == 'shiva_visuals_solr') {
        $imgurl = $vars['fields']['field_image']->content;
        $imgurl = preg_replace('/height="[^"]+"/', '', $imgurl);
        $imgurl = preg_replace('/width="[^"]+"/', '', $imgurl);
        $vars['fields']['field_image']->content = $imgurl;
        $vars['fields']['coll'] = sarvaka_shiva_get_visuals_collection_link($vars['fields']['nid']->content);
    }
}

/**
 * Get the collection link for visualization from node ID 
 */
function sarvaka_shiva_get_visuals_collection_link($nid) {
    if (empty($nid)) { return ""; }
    $node = node_load($nid);
    if (empty($node->field_og_collection_ref)) { return ""; }
    $coll = field_view_field('node', $node, 'field_og_collection_ref', array('label' => 'hidden', 'settings' => array('link' => TRUE)));
    $collhtml = render($coll);
    return $collhtml;
};

/**
 * Implements theme_field for shivadata_source_url
 * 	Gives link to open in separate window followed by Iframe with showing the data.
 * 	Currently only shows when it's a google doc.
 *
 * 	TODO: Need to account for other types of datasource than google docs
 */
function sarvaka_shiva_field__shivadata_source_url($variables) {
    $url = $variables['element'][0]['#markup'];
    $output = '';
    $output .= '<div class="outlink"><a href="' . $url . '" target="_blank">' . t("View in separate window") . '</a></div>';
    $output .= '<div class="shivaframe"><iframe id="shivaDataFrame" src="' . $variables['element'][0]['#markup'] . '" frameborder="0" ' . 'style="width: 98% !important; min-height: 1000px;"> </iframe></div>';
    // Render the top-level DIV.
    $output = '<div class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</div>';

    return $output;
}

/**
 * Creates custom popovers for Shivnode information based on shanti_sarvaka_info_popover
 *
 * Provides markup for the info popups from icons etc.
 * 	Variables:
 * 		- icon 		 (string) 	: icon class to use
 * 		- title 	 (string) 	: Header of popover
 * 		- vtype    (string) 	: Type of Visualization
 * 		- vsubtype (string) 	: Subtype
 * 		- vauthor   (string)  : Author
 * 		- vdate     (string) 	: Date
 * 		- footer 	 (string) 	: Footer content (optional)
 *    - options (string)    : "data-..." attribute options
 */
function sarvaka_shiva_custom_info_popover($variables) {
    $icon = $variables['icon'];
    $icon = (strpos($icon, 'fa') > -1) ? "fa $icon" : "icon $icon";
    $subtype = (!empty($variables['vsubtype'])) ? ", {$variables['vsubtype']}" : "";
    $infoitems = '';
    $vtype = '';
    $vdate = '';
    $vdata = '';
    $vgroups = '';
    $vgrpaccess = '';
    $vsubjs = '';
    $vtype = '<li>';
    if (!empty($variables['vtype'])) {
        $vtype .= "<span class=\"icon shanticon-visuals\" title=\"Visualization Type\"></span> {$variables['vtype']}{$subtype}";
    }
    if (!empty($variables['vstatus'])) {
        $vtype .= ", {$variables['vstatus']}";
    }
    if (!empty($variables['vauthor'])) {
        $vtype .= "</li><li><span class=\"icon shanticon-agents\" title=\"Author\"></span> {$variables['vauthor']}</li>";
    }
    $vtype .= '</li>';
    if (!empty($variables['vdate'])) {
        $vdate = "<li><span class=\"icon shanticon-calendar\" title=\"Date Created\"></span> {$variables['vdate']}</li>";
    } 
    if (!empty($variables['vgroups'])) {
        $vgroups = "<li><span class=\"icon shanticon-grid\" title=\"Collections\"></span> {$variables['vgroups']}</li>";
    }
    if (!empty($variables['vgrpaccess'])) {
        $vgrpaccess = "<li>{$variables['vgrpaccess']}</li>";
    }
    if (!empty($variables['vdata'])) {
        $vdata = "<li><span class=\"icon shanticon-list\" title=\"Data Used\"></span> {$variables['vdata']}</li>";
    }
    if (!empty($variables['vsubjects'])) {
        $vsubjs = "<li><span class=\"icon shanticon-subjects\" title=\"Subject Kmaps\"></span> {$variables['vsubjects']}</li>";
    }

    if (!empty($vtype) || !empty($vauthor) || !empty($vdate) || !empty($vgroups) ) {
        $infoitems = '<ul class="info">' . $vtype . $vdate . $vgroups . $vgrpaccess . $vdata . $vsubjs . '</ul>';
    }
    $options = (!empty($variables['options'])) ? $variables['options'] : '';
    $html = "<div class=\"visinfo\"><span class=\"popover-link\"><span class=\"{$icon}\"></span></span>
						<div class=\"popover\" data-title=\"{$variables['title']}\" {$options}>
							<div class=\"popover-body\">
								{$infoitems}
								<div class=\"desc\">{$variables['vdesc']}</div>
							</div>
							<div class=\"popover-footer\">{$variables['vfooter']}</div>
						</div></div>";
    return $html;
}
