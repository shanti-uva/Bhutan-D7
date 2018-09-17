<?php

/*************** Page Functions *******************************/

	module_load_include('inc', 'shivanode', 'includes/shivanode.types');
/**
 * Function to create a entry page for creating a visualizations, listing all registered types.
 */
function explore_vis_page($mode) {
	$stypes = shivanode_get_types('full', FALSE);
    $access = (user_access('create shivanode content')) ? "create" : "explore";
    if ($mode == "create" && $access =="explore") { drupal_goto("explore"); }
	$collapsed = TRUE ;
	$page = array(
		'header' => array(
			'#markup' => t('<h3>Explore Visualization Types</h3>'),
		),
		'description' => array(
			'#markup' => t('<p>Listed below are the various types of visualizations one can make in SHIVA, ' .
                'organized by the three major categories: Charts, Graphs, and Media & Maps. ' .
                'Each type has links for documentation or examples of that type of visualization</p>'),
		),
		'#attributes' => array(
			'class' => array('shanti-gallery'),
		),
		'charts' => array(
			'#type' => 'fieldset',
            '#title' => t('Charts'),
            '#collapsible' => FALSE,
            //'#description' => t("this is a fieldset element"),
            'items' => array(
				'#prefix' => '<ul class="sn-explore-list shanti-gallery">',
				'#suffix' => '</ul>',
			),
		),
		'relationships' => array(
			'#type' => 'fieldset',
            '#title' => t('Relationships'),
            '#collapsible' => FALSE,
            //'#description' => t("this is a fieldset element"),
            'items' => array(
				'#prefix' => "<ul class=\"sn-explore-list shanti-gallery $mode\">",
				'#suffix' => '</ul>',
			),
		),
		'mediatypes' => array(
			'#type' => 'fieldset',
            '#title' => t('Media & Maps'),
            '#collapsible' => FALSE,
            //'#description' => t("this is a fieldset element"),
            'items' => array(
				'#prefix' => "<ul class=\"sn-explore-list shanti-gallery $mode\">",
				'#suffix' => '</ul>',
			),
		),
		/*
		'maps' => array(
			'#type' => 'fieldset',
            '#title' => t('Maps'),
            '#collapsible' => FALSE,
            //#description' => t("this is a fieldset element"),
            'items' => array(
				'#prefix' => "<ul class=\"sn-explore-list shanti-gallery $mode\">",
				'#suffix' => '</ul>',
			),
		),*/
	);
	
	// Fill Charts
	foreach($stypes['chart']['subtypes'] as $sind => $subtype) {
		$subtype['type'] = 'chart';
		$page['charts']['items'][] = array(
			'#markup' => shivanode_explore_thumb($sind, $subtype, TRUE, $mode),
		);
	}
	
	// Fill Relationships
	// Graph subtypes first
	foreach($stypes['graph']['subtypes'] as $sind => $subtype) {
		$subtype['type'] = 'graph';
		$page['relationships']['items'][] = array(
			'#markup' => shivanode_explore_thumb($sind, $subtype, TRUE, $mode),
		);
	}
	
	// Then other relationship types
	$reltypes = array('subway', 'timeline', 'word_cloud' ) ;
	foreach ($reltypes as $tname) {
		$type = $stypes[$tname];
		$item = array( $type['name'], $tname, $type['image'], $type['help_url'] );
		$page['relationships']['items'][] = array(
			'#markup' => shivanode_explore_thumb($type['index'], $item, FALSE, $mode),
		);
	}
	
	// Fill mediatypes
	$reltypes = array('image', 'video', 'multimedia', 'map' ) ;
	foreach ($reltypes as $tname) {
		if (isset($stypes[$tname])) {
			$type = $stypes[$tname];
			$item = array( $type['name'], $tname, $type['image'], $type['help_url'] );
			$page['mediatypes']['items'][] = array(
				'#markup' => shivanode_explore_thumb($type['index'], $item, FALSE, $mode),
			);
		}
	}
	
	// Fill maps
    /*
	$reltypes = array('map' ) ;
	foreach ($reltypes as $tname) {
		$type = $stypes[$tname];
		$item = array( $type['name'], $tname, $type['image'], $type['help_url'] );
		$page['maps']['items'][] = array(
			'#markup' => shivanode_explore_thumb($type['index'], $item, FALSE, $mode),
		);
	}
	*/
	return $page;
	
}
/**
 * Creates thumbnail for the explore visualization page
 * 
 * @param $ind : index of the item in the php array that defines shivanode types
 * @param $item : an sequential array of info about the item with title, machine-name, img variable name, and help link in that order
 * @param $isSubtype : whether or not this is a visualization subtype
 * 
 * @return html markup for the thubmnail wrapped in an <li> element for inclusion in a <ul class="shiva-gallery"></ul> list
 */
function shivanode_explore_thumb($ind, $item, $isSubtype=FALSE, $mode="explore") {
	$img = variable_get($item[2], FALSE); // load image file variable (contains fid for thumb image)
	if($img) {
		$f = file_load($img); // Load thumb image file
		if (isset($f->uri)) {
			$img = image_style_url('shiva_teaser', $f->uri); // Get image tag
		} else {
			watchdog('shivanode', "No image found for $item[2]", array(), WATCHDOG_WARNING);
		}
	} else {
		return ''; // No image file then return nothing.
	}
	$facet = ($isSubtype) ? 'shivanode_subtype%3A' . $ind : 'shivanode_element_type%3A' . $ind;
    $createlink = "";
    $image = '<div class="shanti-thumbnail-image shanti-field-visuals"><span class="overlay"><span class="icon"></span></span>
                    <img class="img-responsive" typeof="foaf:Image" src="' . $img . '" />       
                    <span class="icon shanticon-visuals"></span></div>';
    if ($mode == 'create') {
        $create = ($isSubtype) ? "/node/add/shivanode/{$item['type']}/{$item[1]}" : "/node/add/shivanode/{$item[1]}";
        $createlink = '<li class="sn-create-link"><a href="' . $create .'" class="btn btn-primary">Create</a></li>';
        $image = '<a href="' . $create .'"><div class="shanti-thumbnail-image shanti-field-visuals"><span class="overlay"><span class="icon"></span></span>
                    <img class="img-responsive" typeof="foaf:Image" src="' . $img . '" />       
                    <span class="icon shanticon-visuals"></span></div></a>';
    }
	$out = '<li class="shanti-thumbnail visual" >
	    	 			' . $image . '
        			  <div class="shanti-thumbnail-info">
        					<div class="body-wrap">
        						<div class="title">' . $item[0] . '</div>
        						<ul class="links">
        							<li><a href="' . $item[3] .'" target="_blank">Documentation</a></li>
        							<li><a href="/examples?f[0]=' . $facet .'">Examples</a></li>
        							' . $createlink . '
        						</ul>
        					</div> 
        				</div> 
        		</li>';

	return $out;
}

/**
 * Creates thumbnail for the create visualization page
 * 
 * @param $ind : index of the item in the php array that defines shivanode types
 * @param $item : an sequential array of info about the item with title, machine-name, img variable name, and help link in that order
 * @param $isSubtype : whether or not this is a visualization subtype
 * @param mixed $did
 * 	The data id to use in creating the visualization
 * @return html markup for the thubmnail wrapped in an <li> element for inclusion in a <ul class="shiva-gallery"></ul> list
 */
function shivanode_create_thumb($ind, $item, $isSubtype=FALSE) {
	$img = variable_get($item[2], FALSE); // load image file variable (contains fid for thumb image)
	if($img) {
		$f = file_load($img); // Load thumb image file
		if (is_object($f) && !empty($f->uri)) {
			$img = image_style_url('shiva_teaser', $f->uri); // Get image tag
		} else {
			drupal_set_message(t("No file found for thumbnail image @img", array('@img' => $item[2])), 'warning');
		}
	} else {
		$img = '';
	}
	//$did = ($did) ? $did . '/' : '';
	$create = ($isSubtype) ? "/node/add/shivanode/{$item['type']}/{$item[1]}" : "/node/add/shivanode/{$item[1]}";
	$out = '<li class="shanti-thumbnail visual" ><a href="' . $create .'">
			
		  <div class="shanti-thumbnail-image shanti-field-visuals">
		   <img class="img-responsive" typeof="foaf:Image" src="' . $img . '">       
		   <span class="icon shanticon-visuals"></span>
		  </div> 
		  
		  <div class="shanti-thumbnail-info">
				<div class="body-wrap">
					<div class="title">' . $item[0] . '</div>
				</div> 
			</div> 
		</a></li>';
	return $out;
}

