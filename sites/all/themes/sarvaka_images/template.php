<?php

/**
 * @file
 * template.php
 */

 /**
  *   This is the template.php file for a child sub-theme of the Shanti Sarvaka theme.
  *   Use it to implement custom functions or override existing functions in the theme. 
  */ 
  
function sarvaka_images_preprocess_page(&$vars) {
    // Remove extra search tabs for pages with "search/site" in the current path
    $cp = current_path();
    if (strpos($cp, 'search/site/') > -1) {
        $vars['tabs']['#primary'] = array();
    }
    if (isset($vars['node']) && $vars['node']->type == "shanti_image") {
        $vars['theme_hook_suggestions'][] = "page__node__shanti_image";
    }
    $imgrep = theme_get_setting('sarvaka_images_replace_broken_images');
    drupal_add_js(array(
        'shanti_images' => array('replace_broken_images' => $imgrep),
    ), 'setting');
}


function sarvaka_images_form_alter(&$form, &$form_state, $form_id) {
    global $base_path;
    //dpm($form['#id'], $form_id);
    // Update the Search Form in the Flyout
    if (strstr($form['#id'],'views-exposed-form-shanti-images-search')) {
        //$form['search_api_views_fulltext_op']['#type'] = 'radios';
        $form['search_api_views_fulltext_op']['#options'] = array(
            'AND' => t('All'),
            'OR' => t('Any'),
            'NOT' => t('None'),
        );
        $form['search_api_views_fulltext_op']['#size'] = 5; 
        $form['search_api_views_fulltext_op']['#prefix'] = '<span>' . t('Contains') . '</span>';
        $form['search_api_views_fulltext_op']['#suffix'] = '<span>' . t('of these words') . '</span>';
        $form['submit']['#value'] = t('Search');
        //dpm($form, 'exposed form state'); 
    }
    if ($form_id == 'shanti_image_node_form') {
        $css = drupal_get_path('theme', 'sarvaka_images') . '/css/shanti-image-node-edit.css';
        $test = drupal_add_css($css, array('group' => CSS_THEME));
        $cp = current_path();
        $url = ($form['nid']['#value']) ? $base_path . drupal_get_path_alias("node/{$form['nid']['#value']}") :
                                            $base_path;
        if (!strstr($cp, '/add/')) {
            $ltxt = t('View without saving');
            $msg = t('Back to viewing the image without saving changes made here');
            $form['#prefix'] = '<a href="' . $url . '" title="' . $msg . '" class="backarrow"><span class="icon shanticon-arrow-left_2"></span> ' . $ltxt . '</a>';
        }
    } 
}

/**
 * Implements hook_preprocess_node
 *      Mainly for collections and subcollections for now
 */
function sarvaka_images_preprocess_node(&$vars) {
    switch ($vars['type']) {
        case 'image_agent':
            sarvaka_images_preprocess_image_agent($vars);
            break;
        case 'image_descriptions':
            sarvaka_images_preprocess_image_descriptions($vars);
            break;
        case 'shanti_image':
            sarvaka_images_preprocess_shanti_image($vars);
            break;
        case 'external_classification':
            sarvaka_images_preprocess_ext_class($vars);
            break;
        case 'external_classification_scheme':
            sarvaka_images_preprocess_ext_class_scheme($vars);
            break;
        case 'collection':
        case 'subcollection':
            if ($vars['view_mode'] == 'teaser') {
                $vars['thumbnail_url'] = '';
                if (!empty($vars['field_general_featured_image'])) {
                    $uri = (isset($vars['field_general_featured_image'][0]['uri'])) ? $vars['field_general_featured_image'][0]['uri'] : $vars['field_general_featured_image']['und'][0]['uri'];
                    $vars['thumbnail_url'] = image_style_url('image_collection_thumbnail', $uri);
                } else {
                    $vars['thumbnail_url'] = '/sites/all/themes/shanti_sarvaka/images/default/collections-generic.png';
                }
                $vars['item_count'] = _get_items_in_collection($vars['nid']);
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
                } // End of collection teasers
            }
    }
}

function sarvaka_images_preprocess_shanti_image(&$vars) {
    global $user;
    list($markup, $activeslide) =  _sarvaka_images_get_flexslider($vars['node']);
    $vars['flexslider_markup'] = $markup;
    if (isset($vars['field_image'][0]) && !empty($vars['field_image'][0]['filename'])) {
        $vars['original_filename'] = $vars['field_image'][0]['filename'];
    } else {
        module_load_include('inc', 'shanti_images', 'includes/shanti_images');
        $siobj = _shanti_images_get_node_image($vars['node']->nid);
        $vars['original_filename'] = $siobj->filename;
    }
    // Get record creator user's name, use realname module if it exists
    $nodeowner = user_load($vars['node']->uid);
    if (module_exists('realname')) {
        if ($user->uid > 0) {
            $vars['username'] = l($nodeowner->realname, drupal_get_path_alias('user/' . $nodeowner->uid));
        } else {
            $vars['username'] = $nodeowner->realname;
        }
    } else {
        $vars['username'] = theme('username', array(  'account' => $nodeowner  ));
    }
    drupal_add_css(drupal_get_path('theme', 'sarvaka_images') . '/css/shanti-image-page.css', array('group' => CSS_THEME));
    drupal_add_css(drupal_get_path('theme', 'sarvaka_images') . '/css/photoswipe.css', array('group' => CSS_THEME));
    drupal_add_css(drupal_get_path('theme', 'sarvaka_images') . '/css/pswp-default-skin.css', array('group' => CSS_THEME)); 
    drupal_add_js(array('shanti_images' => array('flexindex' => $activeslide)), 'setting');

    // For grid view details use the first agent's date (photographer) to display as date
    if ($vars['view_mode'] == 'grid_details') {
        $aid = $vars['node']->field_image_agents['und'][0]['target_id'];
        $photographer = node_load($aid);
        if (!empty($photographer->field_agent_dates_approx['und'][0]['value'])) {
            $to = $photographer->field_agent_dates_approx['und'][0]['value'];
            if (strstr($to, '00:00:00 UTC')) {
                $to = str_replace(' UTC', '', $to);
            }
            $ts = strtotime($to);
            if (empty($ts)) {
                $vars['taken_on'] = $to;
            } else {
                $vars['taken_on'] = date("M j, Y", $ts);
            }
        } elseif (!empty($photographer->field_agent_dates['und'][0]['value'])) {
            $dt = strtotime($photographer->field_agent_dates['und'][0]['value']);
            $vars['taken_on'] = date("M j, Y", $dt);
        }
    }
}

/**
 * Creates the flex slider markup for an image page
 */
function _sarvaka_images_get_flexslider($node) {
    module_load_include('inc', 'shanti_images', 'includes/shanti_images');
    //dpm($node, 'node');
    $sidecount = 5; // number of images on either side of flexslider
    $mainwidth = 1000;
    $thumbwidth = 150;
    $rotation = (!empty($node->field_image_rotation['und'][0]['value'])) ?
        (360 - $node->field_image_rotation['und'][0]['value']) % 360 : 0;
    $back_arrow = '<div class="toppadding">-</div>'; // use toppadding div if no back arrow (no session info) to pad the space above image with dark background
    if (isset($_SESSION['shanti_gallery_url'])) {
        $back_arrow = '<a href="__PATH__" class="backarrow"><span class="icon shanticon-arrow-left_2"></span> Back</a>';
        $back_arrow = str_replace('__PATH__', $_SESSION['shanti_gallery_url'], $back_arrow);
    }
     
    $action_icons = _sarvaka_images_get_action_links($node); 
    
    /**
     * Process Gallery Info from session info. 
     * The session variable 'shanti_gallery_info' must have an array of items that are objects with the following properties:
     * 
     *          nid: The node's ID
     *          filename: The IIIF filename for the image such as shanti-image-123-456
     *          title: the title of the image's node
     *          path: a path to the node itself (not the image url)
     * 
     * To make this adaptable to non-IIIF images, an image property such as $item->img could be added, 
     * but the code to handle this would have to be written.
     */
    $galinfo = array();
    if (!empty($_SESSION['shanti_gallery_info'])) {
        $galinfo = $_SESSION['shanti_gallery_info'];
        //dpm($galinfo, 'gallery session info');
    } else {
        // When there is no session information, then check if node is part of collection and use the collection node list for gallery
        $coll = shanti_collections_get_collection($node); // Get node's collection
        if ($coll) {
            // Get items in node's collection and iterate through
            $items = shanti_collections_get_items_in_collection($coll, 'nids'); // Get list of coll nids
            //dpm($items, 'items in collection');
            if (!empty($items)) {
                $items = node_load_multiple($items);  // Turn list of nids into node objects
                // Process list of node objects into gallery item objects per specifications above
                foreach($items as $item) {
                    $gitem = new stdClass;
                    $gitem->nid = $item->nid;
                    $gitem->filename = $item->i3ffiles;
                    $gitem->title = $item->title;
                    $gitem->path = drupal_get_path_alias('node/' . $item->nid);
                    $galinfo[] = $gitem;
                }
            }
        } else {
            // If a node does not have a collection, use all node list from home page or query
            $vname = 'shanti_images_gallery';
            $dname = 'page';
            $view = views_get_view($vname);
            $view->set_display($dname);
            $view->execute();
            foreach ($view->result as $item) {
                $json = $item->field_field_image[0]['rendered']['#markup'];
                $jobj = json_decode($json);
                $gitem = new stdClass;
                $gitem->nid = $jobj->nid;
                $gitem->filename = $jobj->i3ffiles;
                $gitem->title = $jobj->title;
                $gitem->path = $jobj->path;
                $galinfo[] = $gitem;
            }
        }
    }
    
    // Find index of current image in gallery data
    $myindex = FALSE;
    if (!empty($galinfo)) {
        foreach ($galinfo as $n => $item) {
            //watchdog('sarvaka_images item: ' . $aitem['nid'], json_encode($item));
            if (!isset($item->nid) || !isset($node->nid)) { continue; }
            if ($item->nid == $node->nid) {
                $myindex = $n;
                break;
            }
        }
    }
   // If there is an array of gallery images and an index for the current image
   // Create Markup for Flexslider and Carousel
    if (!empty($galinfo) && $myindex !== FALSE) {
        $galsplice = $galinfo;
        $main_image = '';
        $carousel_slides = '<ul class="slides">';
        $mylistindex = $myindex; // $mylistindex = -1;
        foreach($galsplice as $n => $item) {
            if (!is_object($item) || empty($item->nid)) { continue; } // Took out || empty($item->filename) from condition
            //$dbrec = _shanti_images_get_record($item->nid, 'nid');
            $si = _shanti_images_get_node_image($item->nid);
            $item_rotate = (!empty($item->rotation)) ? (360 - $item->rotation) % 360 : 0;
            if ($item->nid == $node->nid) {
                 $mylistindex = $n;
                 $blururl = $si->getURL(150, '', $rotation); // _shanti_images_build_IIIFURL($fnm, 150, '', $rotation);
                 $url = $si->getURL($mainwidth, '', $rotation); // _shanti_images_build_IIIFURL($fnm, $mainwidth, '', $rotation);
                 $prevlink = ($n > 0) ? '<li><span class="fa fa-spinner fa-spin" style="display:none;"></span><img src="#prev" style="display:none;" /></li>' : '';
                 $nextlink = ($n < count($galsplice) - 1) ? '<li><span class="fa fa-spinner fa-spin" style="display:none;"></span><img src="#next"  style="display:none;"/></li>' : '';
                 $main_image = '<ul class="slides">' . $prevlink . '<li><div data-href="' . $url . '" class="progressive replace"><img src="' . $blururl . '" class="preview"/></div></li>' . $nextlink . '</ul>';
                 $action_icons = str_replace('__MYURL__', $url, $action_icons);
                 $action_icons = str_replace('__MYTITLE__', $item->title, $action_icons);
                 $url = $si->getCropped(90, 65, $item_rotate); //_shanti_images_build_croppedURL($fnm, $dbrec->width, $dbrec->height, 90, 65, $item_rotate);
                 $carousel_slides .= "<li class=\"flex-active-slide\"><img src=\"$url\" /></li>";
                 continue;
            }
            $url = $si->getCropped(90, 65, $item_rotate); // _shanti_images_build_croppedURL($dbrec->i3fid, $dbrec->width, $dbrec->height,90, 65, $item_rotate);
            $ipath = trim($item->path);
            if (substr($ipath, 0, 1) !== '/' && strpos($ipath, 'http') !== 0) { $ipath = '/' . $ipath; }
            $carousel_slides .= "<li><a href=\"{$ipath}\"><img src=\"$url\" /></a></li>";
        }
        $carousel_slides .= '</ul>';
        $markup = '<div id="fsslider" class="flexslider fsmain">' . $main_image .
            '</div><div id="fscarousel" class="flexslider fscarousel">' . $carousel_slides . '</div>';
        $markup = $back_arrow . $markup . $action_icons;
        return array($markup, $mylistindex);
        
    } else if ($myindex === FALSE && variable_get('shanti_images_debug', FALSE)) {
        watchdog('sarvaka_images', 'No display of flexslider for node ' . $node->nid . '. Image not found in gallery list. (template.php)');
    }

    // No Session info available or image not found in carousel array
    // If not gallery info, just show image (Add related images at some point)
    //watchdog('sarvaka_images', 'No session information available for page creation for node: ' . $node->nid);
    $si = _shanti_images_get_node_image($node->nid);
    $url = $si->getURL($mainwidth);
    $action_icons = str_replace('__MYURL__', $url, $action_icons);
    $action_icons = str_replace('__MYTITLE__', $node->title, $action_icons);
    $slides = '<ul class="slides"><li><img src="' . $url . '"></li></ul>';
    $markup = $back_arrow . '<div id="fsslider" class="flexslider fsmain fssolo">' . $slides . '</div>';
    $markup .= $action_icons;
    return array($markup, 0);
}   

/**
 * Returns the markup for the action links on an image page
 */
function _sarvaka_images_get_action_links($node) {
    global $base_path;
    $title = $node->title; // Get node title
    // Make filename (taken from https://stackoverflow.com/questions/2021624/string-sanitizer-for-filename)
    $filetitle = mb_ereg_replace("([^\w\s\d\-_~,;\[\]\(\).])", '', $title);
    $filetitle = mb_ereg_replace("([\.]{2,})", '', $filetitle);
    $filetitle = str_replace(' ', '_', strtolower($filetitle)); // added this to take out whitespaces and lowercase

    // Get IIIF image info
    $dbrec = _shanti_images_get_record($node->nid, 'nid');
    $imgnm = $dbrec->i3fid;
    // Get width and height
    $width = $dbrec->width;
    $height = $dbrec->height;
    // Get IIIF full url for images
    $fullurl = $base_path . 'image/download/' . $imgnm . '/full';
    
    // Define different download sizes
    $sizes = array('Large' => 1200, 'Medium' => 800, 'Small' => 400);
    
    // Create action link markup
    $editbtn = (node_access("update", $node) === TRUE) ?  '<a href="/node/' . $node->nid . '/edit" title="' . t('Edit this image’s information') . '"><span class="icon shanticon-editor"></span></a> ' : '';
    $almu = '<div class="image-actions">' . $editbtn . '<a href="#" title="View in IIIF Viewer"><span class="icon shanticon-preview iiif-icon"></span></a>
    <!-- Single button dropdown -->
    <div class="btn-group img-size-options">
      <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
      <span class="icon shanticon-download"></span></button>
      <span class="drop-arrow"></span>
      <ul class="dropdown-menu">';
      
     // Full image download link
     $almu .= '<li><a href="' . $fullurl . '" download="' . $filetitle . '-full" title="Download Original"><span class="icon shanticon-download"></span>Original (' . $width . 'x' . $height . ')</a></li>';
        
     // Create download links for each size
     if ($width > 0) {
         foreach($sizes as $sstr => $swidth) {
             $surl = $base_path . 'image/download/' . $imgnm . '/' . $swidth;
             $sheight = ceil($height * ($swidth / $width));
             $almu .= '<li><a href="' . $surl . '" download="' . $filetitle . '-' . strtolower($sstr) . '.jpg" title="Download ' . $sstr . ' Size"><span class="icon shanticon-download"></span>' . $sstr . '  (' . $swidth . 'x' . $sheight . ')</a></li>';
         }
     }
       
     // Close action link markup and return it 
     $almu .=  '</ul></div>';
    return $almu;
}
    
function sarvaka_images_preprocess_image_agent(&$vars) {
    if ($vars['view_mode'] == 'teaser') {
        // Rework display of agent in teaser incorporated in image node
        $cnt = $vars['content'];
        //dpm($vars, 'vars');
        // Add field_agent to top of content for all markup
        $mu = '<li class="field field-name-field-agent shanti-image-field " data-nid="'. $vars['nid'] . '">';
        $mu .= '<span class="field-label">' . ucfirst($cnt['field_agent_role'][0]['#markup']) . ': </span> ';
        $mu .= '<span class="field-value"> ' . $vars['title'] ;
        $parencnt = '';
        if (!empty($cnt['field_agent_place'][0]['info_popover'])) {
            $parencnt = theme('info_popover', $cnt['field_agent_place'][0]['info_popover']);
            $parencnt = str_replace('"popover-link"', '"ppltemp"', $parencnt);
            $parencnt = str_replace('"popover"', '"pptemp"', $parencnt);
        }
        // Use approx date for display if it is set
        if (!empty($vars['field_agent_dates_approx'][LANGUAGE_NONE][0]['safe_value'])) {
            if (!empty($parencnt)) { $parencnt .= '– '; }
            // Get date string and format it to display date for record
            $to = $vars['field_agent_dates_approx'][LANGUAGE_NONE][0]['safe_value'];
            if (strstr($to, '00:00:00 UTC')) {
                $to = str_replace(' UTC', '', $to); // Remove UTC so it doesn't add a day for different timezone
            }
            $ts = strtotime($to); // Convert to timestamp, if possible
            if (empty($ts)) {
                $tostr = $to;
            } else {
                $tostr = date("M j, Y", $ts); // Format timestamp as Month day, Year
            }
            $parencnt .= $tostr;
        } elseif (!empty($cnt['field_agent_dates'][0]['#markup'])) {
            if (!empty($parencnt)) { $parencnt .= '– '; }
            $parencnt .= $cnt['field_agent_dates'][0]['#markup'];
        }
        if (!empty($parencnt)) {$mu .= ' (' . $parencnt . ')'; }
        $mu .= '</span></li>';
        
        $field_agent = array('#markup' => $mu);
        $vars['content'] = array_merge(array('field_agent' => $field_agent), $vars['content']);

        //dpm($vars, 'honooyo in image agent 3');
        unset($vars['content']['field_agent_role']);
        unset($vars['content']['field_agent_place']);
        unset($vars['content']['field_agent_dates']);
        
    }

    // For image agent (hide title in template) use role field changing title of role field (label) to its value and its value to the title (the name)
    /*
    $vars['content']['field_agent_role']['#title'] = ucfirst($vars['content']['field_agent_role'][0]['#markup']);
    
    $markup = $vars['title'];
    $pd = false;
    // Date
    //$pd = json_encode($vars['content']['field_agent_place']);
    if (!empty($vars['content']['field_agent_place'])) {
        $pd =  render($vars['content']['field_agent_place']);
        $vars['content']['field_agent_place'] = array();
    }
    
    // Date
    if (!empty($vars['content']['field_agent_dates'][0]['#markup'])) {
        if ($pd) { $pd .= ', '; } 
        $pd .= $vars['content']['field_agent_dates'][0]['#markup'];
        $vars['content']['field_agent_dates']= array();
    }
    
    if ($pd) {
        $markup .= ' (' . $pd . ')';
    }
    
    // Notes
    if (!empty($vars['content']['field_agent_notes'][0]['#markup'])) {
        $note = $vars['content']['field_agent_notes'][0]['#markup'];
        $markup .= '<a href="#" data-toggle="popover" title="Note on ' . $vars['title'] .'" data-content="' . $note . '">*</a>';
    }
    
    $vars['content']['field_agent_role'][0]['#markup'] = $markup;
    //dpm($vars, 'vars in ia pp');
     */
}

/**
 * Preprocess image description nodes
 */
function sarvaka_images_preprocess_image_descriptions(&$vars) {
    // For teasers, create a clean, trimmed description with read more link.
    if ($vars['view_mode'] == 'teaser') {
        $origdesc = $vars['field_description'][0]['safe_value'];
        $stripdesc = strip_tags($origdesc);
        if (strlen($stripdesc) < 400) {
            $vars['description_markup'] = '<div class="short-desc"><p>' . $stripdesc . '</p></div>';
        } else {
            $desctxt = substr(strip_tags($origdesc), 0, 400);
            $desctxt = substr($desctxt, 0, strrpos($desctxt, ' '));
            $author = (isset($vars['field_author'][0]['safe_value'])) ? $vars['field_author'][0]['safe_value'] : '';
            $auth = '<span class="desc-author">' . $author . '</span>';
            $readlink = '<div class="desc morelink">&nbsp;<span class="icon shanticon-arrow-dbl-right"></span>&nbsp;' . t('Read All') . '&nbsp;</div>';
            $mkup = '<div class="teaser-text dontsplit">';
            $mkup .= "<h2>" . $vars['title_str'] . " {$auth}</h2><p>$desctxt";
            if (strlen($desctxt) < strlen($origdesc)) {
                $mkup .= " $readlink";
            }
            $vars['description_markup'] = $mkup . '</p></div>';
        }
    }
}

function sarvaka_images_preprocess_ext_class(&$vars) {
    //dpm($vars, 'vas in ext class');
   $vars['title_suffix'] = array(); // Gets rid of contextual links

    $ew = entity_metadata_wrapper('node', $vars['node']);
    $scheme = $ew->field_external_class_scheme->value();
    
    $ew2 = entity_metadata_wrapper('node', $scheme);
    if (!empty($ew2->field_scheme_abbreviation)) {
        $abbr = $ew2->field_scheme_abbreviation->value();
        $scheme_name = $scheme->title;
        $scheme_url = url('/node/' . $scheme->nid);
        $title =  $vars['node']->title;
        $id = $vars['content']['field_external_class_id'][0]['#markup'];
        if (!empty($ew2->field_scheme_item_url)) {
            $record_url = str_replace('__ID__', $id, $ew2->field_scheme_item_url->value());
            $id = '<a href="' . $record_url . '" target="_blank">' . $id . '</a>';
        }
        $mu = "<a href=\"{$scheme_url}\" title=\"{$scheme_name}\">{$abbr}</a>, $title ($id)";
        if (!empty($vars['content']['field_external_class_note'][0]['#markup'])) {
            $note = $vars['content']['field_external_class_note'][0]['#markup'];
            $mu .= '<a href="#" data-toggle="popover" title="Note on ' . $vars['title'] .'" data-content="' . $note . '">*</a>';
        }
        $vars['content']['field_external_class_id'][0]['#markup'] = $mu;
    }
}

function sarvaka_images_preprocess_ext_class_scheme(&$vars) {
   $vars['title_suffix'] = array(); // Gets rid of contextual links
}

/**
 * Impelments hook_preprocess_views_view
 * 
 * Used to adjust markup and add js/css for the image grid on the home page.
 * Old code for Cultural Landscapes project page. By passed by changing grid_views var.
 */
function sarvaka_images_preprocess_views_view(&$vars) {
    $view = $vars['view']; // Get the view
    //dpm($view, 'view');
    if (isset($view->name)) {
        if ($view->name == 'shanti_images_gallery' || $view->name == 'collection_shanti_images') {
            // Set Caching to Zero so new images show up right away
            drupal_add_http_header('Cache-Control', 'public, max-age=0');
            // Add genurls for image gallery
            $genurls = array();
            $infourls = array();
            $ratios = array();
            foreach ($view->result as $n => $item) {
                if (!empty($item->field_field_image)) {
                    $json = $item->field_field_image[0]['rendered']['#markup'];
                    $iteminfo = json_decode($json, TRUE);
                    if (!empty($iteminfo['filename'])) {
                        // general URLs with width & height place holders
                        $fnm = $iteminfo['filename'];
                        $genurls[] = _shanti_images_build_IIIFURL($fnm, '__W__', '__H__');
                        $infourls[] = _shanti_images_build_InfoURL($fnm);  // URLs for the IIIF info from the IIIF server for each image. Used by IIIF viewers
                        $ratios[] = _shanti_images_get_ratio($fnm, 'i3fid');
                    } else {
                        $json = json_encode($item);
                        watchdog('sarvaka_images', 'Shanti image without json: @json', array('@json' => $json) );
                    }
                } else {
                    // Node has no image!
                    // Add empty string to arrays as placeholders, since they are keyed on image index in grid
                    $genurls[] = '';
                    $infourls[] = '';
                    $ratios[] = '';
                    watchdog('sarvaka_images', 'Shanti image without image:  @title (@nid)', array(
                        '@title' => $item->node_title,
                        '@nid' => $item->nid,
                    ));
                }
            }
            $settings = array('shanti_images' => array(
                'genurls' => $genurls, 
                'infourls' => $infourls, 
                'imgratios' => $ratios
            ));

            drupal_add_js($settings, 'setting');
            // Add photoswipe css
            drupal_add_css(drupal_get_path('theme', 'sarvaka_images') . '/css/photoswipe.css', array('group' => CSS_THEME));
            drupal_add_css(drupal_get_path('theme', 'sarvaka_images') . '/css/pswp-default-skin.css', array('group' => CSS_THEME)); 
        } else if ($view->name == 'my_collections' && $view->current_display == 'my_collections_page') {
            // Process My Collections (memberships) View into gallery of thumbnails
            $vars['rows'] = '';
            foreach ($view->result as $n => $item) {
                $vars['rows'] .= sarvaka_images_create_collection_thumb($item);
            }
        } else if ($view->name == 'media_sharedshelf_my_images' && $view->current_display == 'cultural_landscapes_block') {
            // Custom view handling for cultural landscapes project page
            // not used yet
        } else if ($view->name == 'shanti_images_search') {
            /*dpm($view, 'view');
            dpm($vars, 'vars');*/
        } else {
           // drupal_set_message($view->name);
        }
    }
}

/**
 * 
function sarvaka_images_metadata_process($mdinfo) {
    if (is_array($mdinfo)) {
        if(count($mdinfo) > 0) {
            return $mdinfo[0];
        } else {
            return "";
        }
    } else {
        return $mdinfo;
    }
}
 */
 
/**
 * Converts the view results of a OG Membership search into a list of thumbnails for gallery
 */
function sarvaka_images_create_collection_thumb($item) {
    global $base_path;
    $collurl = url('/node/' . $item->node_og_membership_nid);
    $imgurl = '/sites/all/modules/custom/mediabase/images/collections-generic.png';
    if (!empty($item->field_field_general_featured_image)) {
        $img = $item->field_field_general_featured_image[0];
        $imguri = $img['raw']['uri'];
        $imgsty = (!empty($img['rendered']['#image_style'])) ? $img['rendered']['#image_style'] : 'medium';
        $imgurl = image_style_url($imgsty, $imguri);
    }
    $usrlnk = l($item->users_node_name, '/user/' . $item->users_node_uid);
    $date = format_date($item->node_og_membership_created, 'custom', 'M j, Y');
    $access = t('Private');
    if ($item->field_group_access[0]['raw']['value'] == 0) { $access = t('Public'); }
    if ($item->field_group_access[0]['raw']['value'] == 2) { $access = t('UVa Only'); }
    $count = shanti_collections_get_items_in_collection($item->node_og_membership_nid) . ' ' . t('items');
    $collink = '';
    if (!empty($item->field_field_og_parent_collection_ref)) {
        $coll = node_load($item->field_field_og_parent_collection_ref[0]['raw']['target_id']);
        $collink = l($coll->title, $base_path . 'node/' . $coll->nid);
    }
    $tmpl = '<li class="shanti-thumbnail collection">  
        <div class="shanti-thumbnail-image shanti-field-collection">
            <a href="' . $collurl . '" class="shanti-thumbnail-link">
                <span class="overlay"><span class="icon"></span></span>
                <img class="img-responsive" typeof="Image" src="'. $imgurl . '" width="200" height="150" alt="">
                <span class="icon shanticon-grid"></span>
            </a>
        </div>
        <div class="shanti-thumbnail-info">      
            <div class="body-wrap">
                <div class="shanti-thumbnail-field shanti-field-title">        
                    <span class="field-content">
                        <a href="' . $collurl . '" class="">' . $item->node_og_membership_title . '</a>
                    </span>  
                </div>    
                <div class="shanti-thumbnail-field shanti-field-author">       
                    <span class="shanti-field-content">' . $usrlnk . '</span>  
                </div>    
                <div class="shanti-thumbnail-field shanti-field-created">       
                    <span class="shanti-field-content">' . $date . '</span>  
                </div>                
                <div class="shanti-thumbnail-field shanti-field-type">       
                    <span class="shanti-field-content">' . $access . ' ' . ucfirst($item->node_og_membership_type) . '</span>  
                </div>
                <div class="shanti-thumbnail-field shanti-field-itemcount">       
                    <span class="shanti-field-content">' . $count . '</span>  
                </div>
                <div class="shanti-thumbnail-field shanti-field-body">
                                    </div>
            </div> <!-- end of body wrap -->
            
            <div class="footer-wrap">
              
                              <div class="shanti-field shanti-field-group-audience">
                    <div class="shanti-field-content">' . $collink . '</div>
                </div>
                            
            </div> <!-- end footer -->
        </div>  <!-- end of thumbnail info -->
    </li>';
    
    return $tmpl;
}


function sarvaka_images_get_image_extension($file) {
	$mimetype = $file->filemime;
	switch ($mimetype) {
      case 'image/jpeg':
        return '.jpg';
        break;

      case 'image/tiff':
        return '.tif';
        break;

      case 'image/png':
        return '.png';
        break;

      case 'image/gif':
        return '.png'; // Shared Shelf Gifs get saved as PNGs in Drupal (?)
        break;

      default:
        return '';
    }
}

/**
 * Implements hook_preprocess_file_entity
 * 
 * 	   (Not used yet.)
function sarvaka_images_preprocess_file_entity(&$vars) {
	dpm($vars, 'vars in file pp');
	//$vars['content_attributes'][] = "clearfix";
}

 */
 
/**
 * Implements hook preprocess field
 * 		Hide empty fields in image nodes
 *      Format fields based on type to work in list of info under image
 */
function sarvaka_images_preprocess_field(&$vars) {
	/*if ($vars['element']['#bundle'] == 'image' && count($vars['element']['#items']) == 1 && empty($vars['element'][0]['#markup'])) {
		$vars['classes_array'][] = "hidden";
	} (commenting out ndg8f 2017-06-02) */
    // For processing field collections 
    // From https://www.fourkitchens.com/blog/article/better-way-theme-field-collections/
    
    // Agents field (Photographer, editor, etc.)
     if ($vars['element']['#field_name'] == 'field_agents') {
        //$vars['theme_hook_suggestions'][] = 'field_agents_collected';
        $field_array = array('field_agent', 'field_agent_role','field_agent_place', 'field_agent_dates', 'field_agent_notes');
        rows_from_field_collection($vars, 'field_agents', $field_array);
    }
     
     // Simplify markup of general text fields to be list items with label: value using custom template: field--genfield--shanti-image.tpl.php
     $gen_fields = array(
        'field_image_digital', 
        'field_image_rotation',
        'field_image_quality',
        'field_image_color',
        'field_physical_size',
        'field_image_capture_device',
        'field_copyright_holder',
        'field_copyright_date',
        'field_license_url',
        'field_other_ids',
    );
     if (in_array($vars['element']['#field_name'], $gen_fields)) {
         $vars['theme_hook_suggestions'][] = 'field__genfield__shanti_image';
     }
    // Simplify markup of general long text fields with paragraphs
    if ($vars['element']['#field_name'] == 'field_license_url') {
        foreach ($vars['items'] as $n => &$item) {
            $title = shanti_images_get_license_title($item['#href']);
            $item['#title'] = ($title) ? html_entity_decode($title) : t('View License');
            $item['#attributes']['target'] = '_blank';
        }
    }
    $desc_fields = array(
        'field_copyright_statement',
        'field_image_notes',
        'field_origin_notes',
        'field_classification_notes',
        'field_image_materials',
        'field_image_enhancement',
        'field_technical_notes',
        'field_copyright_statement',
        'field_rights_notes',
        'field_admin_notes',
    );
    if (in_array($vars['element']['#field_name'], $desc_fields)) {
        $vars['theme_hook_suggestions'][] = 'field__gendesc__shanti_image';
    }
    
    // Simplify markup of list fields like External Classifications
    $list_fields = array(
        'field_external_classification',
    );
    if (in_array($vars['element']['#field_name'], $list_fields)) {
        $vars['theme_hook_suggestions'][] = 'field__genlist__shanti_image';
    }
    
}


/**
 * Creates a simple text rows array from a field collections, to be used in a
 * field_preprocess function.
 *     From https://www.fourkitchens.com/blog/article/better-way-theme-field-collections/ 
 * @param $vars
 *   An array of variables to pass to the theme template.
 *
 * @param $field_name
 *   The name of the field being altered.
 *
 * @param $field_array
 *   Array of fields to be turned into rows in the field collection.
 */

function rows_from_field_collection(&$vars, $field_name, $field_array) {
    $vars['rows'] = array();
    foreach($vars['element']['#items'] as $key => $item) {
        $entity_id = $item['value'];
        $entity = field_collection_item_load($entity_id);
        $wrapper = entity_metadata_wrapper('field_collection_item', $entity);
        $row = array();
        foreach($field_array as $field){
            $row[$field] = $wrapper->$field->value();
            if (strstr($field, 'date')) {
                $date1 = date_create($row[$field]['value']);
               $date2 = (!empty($row[$field]['value2']) && $row[$field]['value2'] != $row[$field]['value']) ? date_create($row[$field]['value']) : FALSE;
               $row[$field] = date_format($date1, 'M j, Y');
               if ($date2) { $row[$field] .= ' - ' . date_format($date2, 'M j, Y'); }
            }
        }
        $vars['rows'][] = $row;
    }
}


/**
 * Implements hook breadcrumb alter
 *    for search pages just make the breadcrumb search
 */
function sarvaka_images_menu_breadcrumb_alter(&$active_trail, $item) {
	if ($item['path'] == 'search/site/%') {
		$active_trail = array(); // remove default breadcrumbs which are messed up
		drupal_set_title(t("Search for “@term”", array('@term' => $item['page_arguments'][1])));
		return;
	} else {
	   $map = $item['map']; // Item map tells us about what page we are on
        if ($map[0] == "node" && is_object($map[1])) {
            $node = $map[1];
            // if it's a collection node, add link to all collections before it's name 
            if (in_array($node->type, array('collection', 'subcollection'))) {
                $collslink = array(
                  'title' => t('Collections'), 
                  'href' => 'collections', 
                  'link_path' => 'collections', 
                  'localized_options' => array(), 
                  'type' => 0,
                );
                $newat = array();
                $newat[0] = array_shift($active_trail);
                $newat[1] = $collslink;
                $active_trail = array_merge($newat, $active_trail);
            } 
        } else if ($item['path'] == 'collections' && count($active_trail) == 3 && $active_trail[1]['link_title'] == "Collections") {
            unset($active_trail[1]); // Remove the extra "collections" breadcrumb from user menu set up.
        }
	}
 }

/**
 * Implements preprocess search results
 */
 /*
function sarvaka_images_preprocess_search_results(&$vars) {
	$vars['query_params'] = $vars['query']->getParams();
}
	*/
/**
 * Implements preprocess search result
 * 		Removes snippet and info (for now) and adds thumb url
 */
/*
function sarvaka_images_preprocess_search_result(&$vars) {
	$vars['snippet'] = '';
	$vars['info'] = '';
	$vars['title_full'] = $vars['title'];
	$vars['title'] = truncate_utf8($vars['title'], 40, FALSE, TRUE);
	$file = file_load($vars['result']['fields']['entity_id']);
	$uri = str_replace('sharedshelf://', 'public://media-sharedshelf/', $file->uri);
	$surl = image_style_path('media_thumbnail', $uri . '.jpg');
	$turl = file_create_url($surl);
	$vars['thumb_url'] = $turl;
}
 * */


/**
 * Return the count of number of items in a collection
 */
function _get_items_in_collection($coll=FALSE, $return="count") {
    $nids = array();
    if (is_numeric($coll)) {  $coll = node_load($coll); } // Load collection node if id given
    if ($coll) {
        // Get all collection and subcollection nids invovled
        $nids[] = $coll->nid;
        $nids = array_merge($nids, _get_subcollections_in_collection($coll));
        /**
         * Sample Query:
         *      select count(etid) from og_membership where entity_type='node' and field_name='field_og_collection_ref' and gid in (3,1721,1725,1769,2228,2258,3498,3939,4836,4835,1760,1748,1841);
         * 
         * NOTE: TODO: the results of this query returns a larger number of results than the view shows for THL. WHY is this?
         */
        $result = db_select('og_membership', 'ogm')
                            ->fields('ogm', array('etid'))
                            ->condition('entity_type', 'node')
                            ->condition('field_name', 'field_og_collection_ref')
                            ->condition('gid', $nids, 'IN')
                            ->execute();
        $nids = $result->fetchCol();
        if ($return == "nids") {   return $nids;  }
    }
    return count($nids);
}


/**
 * Return list of subcollections in collection
 *      Returns an array of nids
 */
 
 function _get_subcollections_in_collection($coll=FALSE) {
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
    return $nids;
 }
 
 /*** THEMING ***/