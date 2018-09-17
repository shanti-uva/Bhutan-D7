<?php

/**
 * @file
 * template.php
 *  
 * @description
 * The main template.php file for Bhutan Oral Traditions Theme subtheme of Shanti Sarvaka
 * 
 */

/**
 * Implements hook_preprocess_html
 */  
function sarvaka_bhutan_preprocess_html(&$vars) {
	// Adjust banner color based on path (i.e. resource type)
	$path = current_path();
	if(strpos($path, '/audio-video/')) {
		$vars['classes_array'][] = 'audio-video';
	} elseif (strpos($path, '/texts/')) {
		$vars['classes_array'][] = 'texts';
	} elseif (strpos($path, '/photos/')) {
		$vars['classes_array'][] = 'images';
	} elseif (strpos($path, '/images/')) {
		$vars['classes_array'][] = 'images';
	} 
	//_sarvaka_bhutan_add_head_tags(); // Adds favicon link tags and meta tags for various devices
	
	// Add flyout-open class to pages designated in theme-settings for sarvaka bhutan
	$sfopen = theme_get_setting('sarvaka_bhutan_flyout_open');
	$paths = explode("\n", $sfopen);
	$mypath = current_path();
	foreach($paths as $path) {
		$path = trim($path);
		$path = str_replace('/','\/', $path);
		$path = '/^' . str_replace('*', '\d+', $path) . '$/'; // allow for wildcard * to represent ID #s.
		if (preg_match($path, $mypath)) {
			$vars['classes_array'][] = 'flyout-open';
			break;
		}
	}

	//Add kmaps class to body for contextual styling of search flyout and tabs
    $vars['classes_array'][] = 'kmaps';
}
 
/**
 * Implements hook_preprocess_page
 */  
 
function sarvaka_bhutan_preprocess_page(&$vars) {
 	$theme_path = drupal_get_path('theme', 'sarvaka_bhutan');
	// Front Page processing
 	if($vars['is_front']) {
		drupal_add_css("{$theme_path}/css/bhutan-front.css"); 
		$vars['submitted'] = '';
	}
	if(isset($vars['node']) && $vars['node']->type == 'sponsor') {
		drupal_set_title(t('Bhutan Cultural Library Sponsor'));
	}
}

/**
 * Implements hook_preprocess_region: switch adjust variables on a case by case basis as needed
 */
function sarvaka_bhutan_preprocess_region(&$vars) {
	switch ($vars['region']) {
		// Header Region
		case 'header':
			$vars['shanti_site'] = theme_get_setting('shanti_site');
			$vars['home_url'] = url(variable_get('site_frontpage', 'node'));
			$vars['site_name'] =  variable_get('site_name');
			$vars['logo'] =  theme_get_setting('logo');
			$vars['site_slogan'] =  variable_get('site_slogan');
			break;
		
		// Banner Region
		case 'banner':
			if(!empty($vars['is_front'])) {
				$vars['theme_hook_suggestions'][] = 'region__banner_front';
				// Use try block incase front page is not a node
				try {
					$fpath = variable_get('site_frontpage', 'node');
					$fppts = explode('/', $fpath);
					if(is_array($fppts) && count($fppts) > 1) {
						$fid = $fppts[1];
						$fode = node_load($fid);
						$vars['node'] = $fode;
						$ew = entity_metadata_wrapper('node', $fode);
						$vars['grid_inset_text'] = $ew->field_grid_inset->value();
						$vars['overview_text'] = $ew->field_overview->value();
					} else {
						throw new Exception('Front Page is not a node in preprocess_region');
					}
				 
				} catch (Exception $e) {
					watchdog('bhutan theme', 'Exception caught in preprocess banner region: ' . $e->getMessage());
				}
				
				// Add Search block to variables for rendering on Front Page
				if(module_exists('search')) {
					$vars['search_block'] = module_invoke('search', 'block_view', 'form');
				}
			}
			break;
			
		// Main Content Region
		case 'content':
				if(!empty($vars['is_front'])) {
					//dpm($vars, 'front vars');
					//$vars['content'] = '<div> I AM HERE</div>';
				}
				break;
				
		// Default only for debugging
		default:
			//print "<p><b>REGION: </b> {$vars['region']}</p>";
	}
}


/**
 * Implements hook_preprocess_entity: for preprocessing field collections
 */

function sarvaka_bhutan_preprocess_entity(&$vars) {
	if($vars['entity_type'] == 'field_collection_item' && $vars['elements']['#bundle'] == 'field_collection_teaser') {
		//dpm($vars, 'vars in pp entity');
		// TODO: Adjust this hack to a more sustainable version for I18N
		$vars['title'] = $vars['field_title'][0]['safe_value'];
		$vars['description'] = $vars['field_description'][0]['safe_value'];
		$vars['icon_class'] = $vars['field_icon_class'][0]['safe_value'];
		$vars['title'] = $vars['field_title'][0]['safe_value'];
		$vars['url'] = $vars['field_url'][0]['safe_value'];
		$vars['is_odd'] = (($vars['id'] % 2) == 0) ? FALSE : TRUE;
		$vars['tier'] = "tier{$vars['id']}";
		$fl = '<ul>';
		foreach($vars['field_featured_resources'] as $n => $item) {
			$fl .= "<li><a href=\"{$item['url']}\">{$item['title']}</a></li>";
		}
		$fl .= '</ul>';
		$vars['featured_links'] = $fl;
	}
}

function sarvaka_bhutan_preprocess_block(&$vars) {
	// Replace the system content block for front page with just field collection content
	if($vars['is_front'] && $vars['block_html_id'] == 'block-system-main') {
		$children = element_children($vars['elements']['nodes']);
		$nid = array_shift($children);
		$node = $vars['elements']['nodes'][$nid];
		$children = element_children($node['field_collection_teaser']);
		$html = '';
		foreach($children as $k => $cid) {
			render($node['field_collection_teaser'][$cid]);
			$html .= $node['field_collection_teaser'][$cid]['entity']['#children'];
		}
		$vars['content'] = $html;
	}
}

function sarvaka_bhutan_preprocess_field(&$vars) {
	$el = &$vars['element'];
	if($el['#field_name'] == 'field_url') {
		//dpm($vars, 'field');
	}
}

function sarvaka_bhutan_menu_breadcrumb_alter(&$active_trail, $item) {
	$node = menu_get_object();
	if(is_object($node) && isset($node->type) && $node->type == 'sponsor') {
		$active_trail[] = array('title' => t('Sponsors'), 'href' => url('sponsors'), 'localized_options' => array());
	}
}

/**
 * Function for creating meta data tags in head
 */

/**
 * Function to add meta tags for favicons and the like
 
function _sarvaka_bhutan_add_head_tags() {
	$htags = array(
		'link1' => array(
			'#type' => 'html_tag',
			'#tag' => 'link',
			'#attributes' => array(
				'rel' => 'apple-touch-icon',
				'sizes' => '57x57',
				'href' => 'favicons/apple-touch-icon-57x57.png',
			),
			'#weight' => -999,
		),
		
		'link2' => array(
			'#type' => 'html_tag',
			'#tag' => 'link',
			'#attributes' => array(
				'rel' => 'apple-touch-icon',
				'sizes' => '60x60',
				'href' => 'favicons/apple-touch-icon-60x60.png',
			),
			'#weight' => -998,
		),
		
		'link3' => array(
			'#type' => 'html_tag',
			'#tag' => 'link',
			'#attributes' => array(
				'rel' => 'apple-touch-icon',
				'sizes' => '72x72',
				'href' => 'favicons/apple-touch-icon-72x72.png',
			),
			'#weight' => -997,
		),
		
		'link4' => array(
			'#type' => 'html_tag',
			'#tag' => 'link',
			'#attributes' => array(
				'rel' => 'apple-touch-icon',
				'sizes' => '76x76',
				'href' => 'favicons/apple-touch-icon-76x76.png',
			),
			'#weight' => -996,
		),
		
		'link5' => array(
			'#type' => 'html_tag',
			'#tag' => 'link',
			'#attributes' => array(
				'rel' => 'apple-touch-icon',
				'sizes' => '114x114',
				'href' => 'favicons/apple-touch-icon-114x114.png',
			),
			'#weight' => -995,
		),
		
		'link6' => array(
			'#type' => 'html_tag',
			'#tag' => 'link',
			'#attributes' => array(
				'rel' => 'apple-touch-icon',
				'sizes' => '120x120',
				'href' => 'favicons/apple-touch-icon-120x120.png',
			),
			'#weight' => -994,
		),
		
		'link7' => array(
			'#type' => 'html_tag',
			'#tag' => 'link',
			'#attributes' => array(
				'rel' => 'apple-touch-icon',
				'sizes' => '144x144',
				'href' => 'favicons/apple-touch-icon-144x144.png',
			),
			'#weight' => -993,
		),
		
		'link8' => array(
			'#type' => 'html_tag',
			'#tag' => 'link',
			'#attributes' => array(
				'rel' => 'apple-touch-icon',
				'sizes' => '152x152',
				'href' => 'favicons/apple-touch-icon-152x152.png',
			),
			'#weight' => -992,
		),
		
		'link9' => array(
			'#type' => 'html_tag',
			'#tag' => 'link',
			'#attributes' => array(
				'rel' => 'apple-touch-icon',
				'sizes' => '180x180',
				'href' => 'favicons/apple-touch-icon-180x180.png',
			),
			'#weight' => -991,
		),
		
		'link10' => array(
			'#type' => 'html_tag',
			'#tag' => 'link',
			'#attributes' => array(
				'rel' => 'icon',
				'type' => 'image/png',
				'href' => 'favicons/favicon-32x32.png',
				'sizes' => '32x32',
			),
			'#weight' => -990,
		),
		
		'link11' => array(
			'#type' => 'html_tag',
			'#tag' => 'link',
			'#attributes' => array(
				'rel' => 'icon',
				'type' => 'image/png',
				'href' => 'favicons/favicon-194x194.png',
				'sizes' => '194x194',
			),
			'#weight' => -989,
		),
		
		'link12' => array(
			'#type' => 'html_tag',
			'#tag' => 'link',
			'#attributes' => array(
				'rel' => 'icon',
				'type' => 'image/png',
				'href' => 'favicons/favicon-96x96.png',
				'sizes' => '96x96',
			),
			'#weight' => -988,
		),
		
		'link13' => array(
			'#type' => 'html_tag',
			'#tag' => 'link',
			'#attributes' => array(
				'rel' => 'icon',
				'type' => 'image/png',
				'href' => 'favicons/android-chrome-192x192.png',
				'sizes' => '192x192',
			),
			'#weight' => -987,
		),
		
		'link14' => array(
			'#type' => 'html_tag',
			'#tag' => 'link',
			'#attributes' => array(
				'rel' => 'icon',
				'type' => 'image/png',
				'href' => 'favicons/favicon-16x16.png',
				'sizes' => '16x16',
			),
			'#weight' => -986,
		),
		
		'link15' => array(
			'#type' => 'html_tag',
			'#tag' => 'link',
			'#attributes' => array(
				'rel' => 'manifest',
				'href' => 'favicons/manifest.json',
			),
			'#weight' => -985,
		),
		
		'meta1' => array(
			'#type' => 'html_tag',
			'#tag' => 'meta',
			'#attributes' => array(
				'name' => 'msapplication-TileColor',
				'content' => '#da532c',
			),
			'#weight' => -984,
		),
		
		'meta2' => array(
			'#type' => 'html_tag',
			'#tag' => 'meta',
			'#attributes' => array(
				'name' => 'msapplication-TileImage',
				'content' => 'favicons/mstile-144x144.png',
			),
			'#weight' => -983,
		),
		
		'meta3' => array(
			'#type' => 'html_tag',
			'#tag' => 'meta',
			'#attributes' => array(
				'name' => 'theme-color',
				'content' => '#ffffff',
			),
			'#weight' => -982,
		),
	);
	
	foreach($htags as $key => $details) {
		drupal_add_html_head($details, $key);
	}
}
*/