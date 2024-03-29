<?php

/**
 * Define all types here. 
 * 
 * Types are associative arrays which have the following field:
 * 		index: their unique index in an array because of development history these do not list type alphabetically
 * 		name:  name of the type
 * 		deprecated: (boolean)
 * 		uses_data: (boolean) whether this type uses a Google spreadsheet or similar data source
 * 		player: the player to use when displaying the chart either "shiva" or "qmedia" presently
 *  	help_url: Url to the help file
 * 		image: variable name that holds the file number for the thumb image
 * 		subtypes: an array of subtypes or FALSE if no subtypes.	See below for subtype fields
 * 		
 * Subtypes are sequential (i.e. non-associative arrays) which the following fields:
 * 		0: Label for subtype
 * 		1: Machine Name of subtype
 * 		2: Thumbnail image variable name (name of variable that contains file number for thumb image)
 * 		3: Help URL
 * 		4: Is Deprecated, include a fifth element set to TRUE to deprecate a subtype
 * 
 * Old prototypes not included are:
 * 
 *   8 => 'Control',
 *   9 => 'Canvas',
 */
function _get_sn_type_array() {
	$shivanode_types = array(
		'data' => array(
			'index' => 1,
			'name' => 'data',
			'deprecated' => TRUE,
			'uses_data' => FALSE,
			'player' => 'shiva',
			'help_url' => FALSE,
			'image' => FALSE,
			'subtypes' => FALSE,
		),
		'chart' => array(
			'index' => 7,
			'name' => t('Chart'),
			'deprecated' => FALSE,
			'uses_data' => TRUE,
			'player' => 'shiva',
			'help_url' => 'https://wiki.shanti.virginia.edu/display/KB/Use+the+Charts+Tool',
			'image' => 'sngen-chart-default',
			'subtypes' => array(
				1 => array(t('Timeline Chart'), 'AnnotatedTimeLine', 'sngen-chart-antime', 'https://wiki.shanti.virginia.edu/display/KB/Annotated+Time+Line'),
			  2 => array(t('Area Chart'), 'AreaChart', 'sngen-chart-area', 'https://wiki.shanti.virginia.edu/display/KB/Area+Chart'),
			  3 => array(t('Bar Chart'), 'BarChart', 'sngen-chart-bar', 'https://wiki.shanti.virginia.edu/display/KB/Bar+Chart'),
			  4 => array(t('Candlestick Chart'), 'CandlestickChart', 'sngen-chart-candle', 'https://wiki.shanti.virginia.edu/display/KB/Candlestick+Chart'),
			  5 => array(t('Column Chart'), 'ColumnChart', 'sngen-chart-column', 'https://wiki.shanti.virginia.edu/display/KB/Column+Chart'),
			  6 => array(t('Gauge'), 'Gauge', 'sngen-chart-gauge', 'https://wiki.shanti.virginia.edu/display/KB/Gauge'),
			  7 => array(t('Geo Chart'), 'GeoChart', 'sngen-chart-geo', 'https://wiki.shanti.virginia.edu/display/KB/Geo+Chart'),
			  8 => array(t('Line Chart'), 'LineChart', 'sngen-chart-line', 'https://wiki.shanti.virginia.edu/display/KB/Line+Chart'),
			  9 => array(t('Motion Chart'), 'MotionChart', 'sngen-chart-motion', 'https://wiki.shanti.virginia.edu/display/KB/Motion+Chart'),
			  10 => array(t('Organization Chart'), 'OrgChart', 'sngen-chart-org', 'https://wiki.shanti.virginia.edu/display/KB/Organization+Chart'),
			  11 => array(t('Pie Chart'), 'PieChart', 'sngen-chart-pie', 'https://wiki.shanti.virginia.edu/display/KB/Pie+Chart'),
			  12 => array(t('Scatter Chart'), 'ScatterChart', 'sngen-chart-scatter', 'https://wiki.shanti.virginia.edu/display/KB/Scatter+Chart'),
			  13 => array(t('Table'), 'Table', 'sngen-chart-table', 'https://wiki.shanti.virginia.edu/display/KB/Table'),
			  14 => array(t('Tree Map'), 'TreeMap', 'sngen-chart-tree', 'https://wiki.shanti.virginia.edu/display/KB/Tree+Map'),
			),
		),
		'draw' => array(
			'index' => 11,
			'name' => t('Draw'),
			'deprecated' => TRUE,
			'uses_data' => FALSE,
			'player' => 'shiva',
			'help_url' => FALSE,
			'image' => 'sngen-draw',
			'subtypes' => FALSE,
		),
		'earth' => array(
			'index' => 12,
			'name' => t('Earth'),
			'deprecated' => TRUE,
			'uses_data' => FALSE,
			'player' => 'shiva',
			'help_url' => 'https://wiki.shanti.virginia.edu/display/KB/Use+the+Maps+Tool+and+Earth+Tool',
			'image' => 'sngen-earth',
			'subtypes' => FALSE,
		),
		'graph' => array(
			'index' => 16,
			'name' => t('Graph'),
			'deprecated' => FALSE,
			'uses_data' => TRUE,
			'player' => 'shiva',
			'help_url' => 'https://wiki.shanti.virginia.edu/display/KB/Use+the+Graph+Tool',
			'image' => 'sngen-graph',
			'subtypes' => array(
		    23 => array(t('Bubble'), 'Bubble', 'sngen-graph', 'https://wiki.shanti.virginia.edu/display/KB/Bubble'),
		    26 => array(t('Chord'), 'Chord', 'sngen-graph-chord', 'https://wiki.shanti.virginia.edu/display/KB/Chord'),
				21 => array(t('Network'), 'Network', 'sngen-graph-network', 'https://wiki.shanti.virginia.edu/display/KB/Network'),
		    25 => array(t('Parallel'), 'Parallel', 'sngen-graph-parallel', 'https://wiki.shanti.virginia.edu/display/KB/Parallel'),
		    24 => array(t('Stream'), 'Stream', 'sngen-graph-stream', 'https://wiki.shanti.virginia.edu/display/KB/Stream'),
		    22 => array(t('Tree'), 'Tree', 'sngen-graph-tree', 'https://wiki.shanti.virginia.edu/display/KB/Tree'),
			),
		),
		'image' => array(
			'index' => 2,
			'name' => t('Image'),
			'deprecated' => FALSE,
			'uses_data' => TRUE,
			'player' => 'shiva',
			'help_url' => 'https://wiki.shanti.virginia.edu/pages/viewpage.action?pageId=78581956',
			'image' => 'sngen-image',
			'subtypes' => array(
				18 => array(t('Slideshow'), 'Slideshow', 'sngen-image', 'https://wiki.shanti.virginia.edu/pages/viewpage.action?pageId=78581956'),
		    19 => array(t('Image Montage'), 'Montage', 'sngen-image', 'https://wiki.shanti.virginia.edu/pages/viewpage.action?pageId=78581956'),
		    20 => array(t('Zoomable Image'), 'Zoomable', 'sngen-image', 'https://wiki.shanti.virginia.edu/pages/viewpage.action?pageId=78581956'),
			),
		),
		'map' => array(
			'index' => 3,
			'name' => t('Map'),
			'deprecated' => FALSE,
			'player' => 'shiva',
			'uses_data' => FALSE,
			'help_url' => 'https://wiki.shanti.virginia.edu/pages/viewpage.action?pageId=78582249',
			'image' => 'sngen-map',
			'subtypes' => FALSE,
		),
		'multimedia' => array(
			'index' => 17,
			'name' => t('Interactive Presentation'),
			'deprecated' => FALSE,
			'uses_data' => FALSE,
			'player' => 'qmedia',
			'help_url' => 'https://wiki.shanti.virginia.edu/display/KB/Qmedia+Interactive+Presentations',
			'image' => 'sngen-qmedia',
			'subtypes' => FALSE,
		),
		'network' => array(
			'index' => 10,
			'name' => t('Network'),
			'deprecated' => TRUE,
			'uses_data' => TRUE,
			'player' => 'shiva',
			'help_url' => 'https://wiki.shanti.virginia.edu/display/KB/Use+the+Network+Tool',
			'image' => 'sngen-network',
			'subtypes' => array(
				15 => array(t('Radial Graph'), 'rgraph', 'sngen-network', 'https://wiki.shanti.virginia.edu/display/KB/Use+the+Network+Tool'),
		    16 => array(t('Forced Directed'), 'forcedir', 'sngen-network', 'https://wiki.shanti.virginia.edu/display/KB/Use+the+Network+Tool'),
		    17 => array(t('Hyper Tree'), 'hypertree', 'sngen-network', 'https://wiki.shanti.virginia.edu/display/KB/Use+the+Network+Tool'),
			),
		),
		'poster' => array(
			'index' => 14,
			'name' => t('Poster'),
			'deprecated' => TRUE,
			'uses_data' => FALSE,
			'player' => 'shiva',
			'help_url' => FALSE,
			'image' => 'sngen-poster',
			'subtypes' => FALSE,
		),
		'subway' => array(
			'index' => 4,
			'name' => t('Subway'),
			'deprecated' => FALSE,
			'uses_data' => FALSE,
			'player' => 'shiva',
			'help_url' => 'https://wiki.shanti.virginia.edu/display/KB/Subway',
			'image' => 'sngen-subway',
			'subtypes' => FALSE,
		),
		'timeline_simile' => array(
			'index' => 5,
			'name' => t('Timeline (Simile)'),
			'deprecated' => TRUE,
			'uses_data' => TRUE,
			'player' => 'shiva',
			'help_url' => FALSE,
			'image' => 'sngen-timeline',
			'subtypes' => FALSE,
		),
		'timeline' => array(
			'index' => 13,
			'name' => t('Timeline'),
			'deprecated' => FALSE,
			'uses_data' => TRUE,
			'player' => 'shiva',
			'help_url' => 'https://wiki.shanti.virginia.edu/display/KB/Timeline',
			'image' => 'sngen-timeline',
			'subtypes' => FALSE,
		),
		'video' => array(
			'index' => 6,
			'name' => t('Video'),
			'deprecated' => FALSE,
			'uses_data' => FALSE,
			'player' => 'shiva',
			'help_url' => 'https://wiki.shanti.virginia.edu/pages/viewpage.action?pageId=78581959',
			'image' => 'sngen-video',
			'subtypes' => FALSE,
		),
		'word_cloud' => array(
			'index' => 15,
			'name' => t('Word Cloud'),
			'deprecated' => FALSE,
			'uses_data' => FALSE,
			'player' => 'shiva',
			'help_url' => 'https://wiki.shanti.virginia.edu/display/KB/Word+Cloud',
			'image' => 'sngen-wcloud',
			'subtypes' => FALSE,
		),
		/**
		'' => array(
			'index' => -1,
			'name' => t(''),
			'deprecated' => FALSE,
			'uses_data' => TRUE,
		  'player' => 'shiva',
			'help_url' => FALSE,
			'image' => '',
			'subtypes' => FALSE,
		),
		 **/
	);
	return $shivanode_types;
}

	/**
	 * shivanode_get_types: returns a list of shivanode types according to parameters
	 * 	format:
	 * 		full = full list 
	 * 		nameindex = just names by index value, e.g. index => Name
	 * 		datatypes = full type information for all types that use spreadsheet data keyed on machine-name
	 * 		subtypes = list of subtypes by index value
	 */
	function shivanode_get_types($format='nameindex', $show_deprecated=TRUE) {
		$shivanode_types = _get_sn_type_array();
		//dpm($shivanode_types, 'types');
		$data = array(); // Initialize the return array
		if($format == 'nameindex') {
			foreach($shivanode_types as $nind => $typeitem) {
				if($show_deprecated || $typeitem['deprecated'] === FALSE) {
					$data[$typeitem['index']] = $typeitem['name'];
				}
			}
		} elseif ($format == 'datatypes') {
			foreach($shivanode_types as $nind => $typeitem) {
				if($show_deprecated || $typeitem['deprecated'] === FALSE) {
					if($typeitem['uses_data']) {
						if($typeitem['subtypes']) {
							foreach($typeitem['subtypes'] as $sind => $subtype) {
								$data[$subtype[1]] = array(
								  'index' => $sind,
								  'type' => $nind,
									'create_url' => $nind . '/' . $subtype[1],
									'name' => $subtype[0],
									'image' => $subtype[2], 
									'help_url' => $subtype[3],
									'is_subtype' => TRUE,
								);
							} 
						} else {
							$data[$nind] = array(
								'create_url' => $nind,
								'is_subtype' => FALSE,
							);
							$data[$nind] += $typeitem;
						}
					}
				}
			}
			uasort($data, function($a, $b) {
				return strcmp($a['name'], $b['name']);
			});
		} elseif ($format == 'full') {
			if(!$show_deprecated) {
				$shivanode_types = array_filter($shivanode_types, function($v) {
					return !$v['deprecated'];
				});
			}
			return $shivanode_types;
		} elseif ($format == 'subtypes') {
			foreach($shivanode_types as $nind => $typeitem) {
				if($typeitem['subtypes'] && ($show_deprecated || $typeitem['deprecated'] == FALSE)) {
					$data = $data + $typeitem['subtypes']; // concatenate with return array
				}
			}
		} else {
			$data = t('Invalid format given in shivanode_get_types (@format) in shivanode.types.inc', array(
				'@format' => $format,
			));
		}
		if(is_array($data)) {
			return $data;
		} else {
			drupal_set_message($data, 'error');
			return FALSE;
		}
	}

	/**
	 * Get the label for a type or subtype
	 * 	@param $tind (integer) index for type of subtype (if given a machinename for a type will convert to index)
	 *  @param $isSubtype (boolean) whether the index represents a type or subtype
	 */
	function _shivanode_get_type_label($tind, $isSubtype=FALSE) {
		if($isSubtype) {
			$sts = shivanode_get_types('subtypes');
			return $sts[$tind][0];
		} else {
			if (!is_int($tind)) { $tind = _shivanode_get_index($tind); }
			$tps = shivanode_get_types('nameindex');
			return (isset($tps[$tind])) ? $tps[$tind] : ""; 
		}
	}
	
	/**
	 * Gets machine name index from numeric index
	 */
	 function _shivanode_get_machine_name($num_index, $isSubtype=FALSE) {
		 if($isSubtype) {
		 	$stypes = shivanode_get_types('subtypes');
			return (isset($stypes[$num_index][1])) ? $stypes[$num_index][1] : FALSE;
		 } else {
		 	$types = shivanode_get_types('full');
			foreach($types as $nind => $titem) {
				if ($titem['index'] == $num_index) { return $nind; }
			}
			return FALSE;
		 }
	 }

	/** 
	 * Get Index from machine name
	 */
	function _shivanode_get_index($mnm, $isSubtype=FALSE) {
		if($isSubtype) {
			$stypes = shivanode_get_types('subtypes');
			foreach ($stypes as $n => $stype) {
				if ($stype[1] == $mnm) {
					return $n;
				}
			}
			return FALSE;
		} else {
			$types = shivanode_get_types('full');
			foreach ($types as $nind => $titem) {
				if ($nind == $mnm) { return $titem['index']; }
			}
			return FALSE;
		}
	}
	
	/**
	 * Determines whether visualization type uses data from a spreadsheet or not. Only applies to main types
	 * Subtypes inherit their parent setting in this regard. The item in the array is 'uses_data'.
	 * 
	 * @param int $ind
	 * 	the integer index of the type from the type array
	 * 
	 * @return TRUE if uses data otherwise FALS
	 */
	function _shivanode_is_data_type($tind) {
		$dtypes = shivanode_get_types('full');
		if (isset($dtypes[$tind])) {
			return $dtypes[$tind]['uses_data'];
		} else {
			return FALSE;
		}
	}
	
	/**
	 * Determines whether a item is a subtype or type based on their machine name
	 * 
	 * @param string $mnm
	 * 	The machine name of the type to determine
	 * 
	 * @return int
	 * 	Returns the integer index of the subtype entry or -1 if not a subtype.
	 */
	function _shivanode_is_subtype($mnm) {
		$dtypes = shivanode_get_types('full');
		foreach ($dtypes as $indnm => $item) {
			if ($mnm == $indnm) { return -1; }
		}
		$stypes = shivanode_get_types('subtypes');
		foreach ($stypes as $ind => $stype) {
			if ($mnm == $stype[1]) { return $ind; }
		}
		return -1;
	}
	
	/**
	 * Returns all types that use data spreadsheets in a variety of formats
	 * 
	 * @param string $format
	 * 	Designates the format to return. Acceptible values are:
	 * 		full : gives the full list of data types
	 *    select : gives a list of data types alphabetically with initial blank for a select form
	 * 
	 * @return array
	 * 	A list of data types in the desired format
	 */
	function _shivanode_get_data_types($format='full', $show_deprecated=FALSE) {
		$alltypes = shivanode_get_types('full');
		$dtypes = array();
		foreach ($alltypes as $mnind => $titem) {
			if ($titem['uses_data']) {
				if($titem['subtypes']) {
					foreach ($titem['subtypes'] as $sn => $stype) {
						if($show_deprecated || !$titem['deprecated']) {
							$dtypes[] = array( 'index' => $sn, 'machine_name' => $stype[1], 'label' => $stype[0], 'is_subtype' => TRUE, );
						}
					}
				} else {
					if($show_deprecated || !$titem['deprecated']) {
						$dtypes[] = array( 'index' => $titem['index'], 'machine_name' => $mnind, 'label' => $titem['name'], 'is_subtype' => FALSE, );
					}
				}
			}
		}
		usort($dtypes, function($a, $b) { return ($a['label'] > $b['label']) ? TRUE : FALSE; });
		if ($format == 'select') {
			$outarray = array(0 => 'Visualize as');
			foreach ($dtypes as $nind => $type) {
				$outarray[$type['machine_name']] = $type['label'];
			}
			return $outarray;
		}
		return $dtypes;
	}
	
	/**
	 * Get a full list of help urls for both types and subtypes
	 * 
	 * @return an associative array of 'types' and 'subtypes' helpurls by index
	 */
	function _shivanode_get_help_urls() {
		$alltypes = shivanode_get_types('full');
		$outurls = array(
			'types' => array(),
			'subtypes' => array(),
		);
		foreach ($alltypes as $mnm => $type) {
			$outurls['types'][$type['index']] = $type['help_url'];
			if ($type['subtypes']) {
				foreach ($type['subtypes'] as $sind => $subtype) {
					if (!empty($subtype[3])) { $outurls['subtypes'][$sind] = $subtype[3]; }
	 			}
			}
		}
		return $outurls;
	}
	
	/**
	 * Get the array for that type
	 * 
	 * @param int $typeInd
	 * 	the index integer for that type
	 * @param boolean $isSubtype
	 *  whether it is a subtype or not
	 * 
	 * @return mixed 
	 * 	array of data about type or subtype or FALSE if not found
	 */
	function _shivanode_get_type_info($typeInd, $isSubtype=FALSE) {
		if($isSubtype) {
			$subtypes = shivanode_get_types('subtypes');
			return $subtypes[$typeInd];
		} else {
			$alltypes = shivanode_get_types('full');
			foreach ($alltypes as $mn => $type) {
				if ($type['index'] == $typeInd) {
					return $type;
				}
			}
		}
		return FALSE;
	}

	/**
	 * Get the index for a type or subtype given its name, either machine name or label
	 * 
	 * @param string $typeName
	 * 	The name of the type either as a machine name or label
	 * @param boolean $isSubtype
	 * 	Whether the $typeName is that of a subtype or not
	 * 
	 * @return int
	 * 	returns the integer index for the type or subtype or -1 if not found
	 * 
	 */
	function _shivanode_get_type_index($typeName, $isSubtype=FALSE) {
		if($isSubtype) {
			$subtypes = shivanode_get_types('subtypes');
			foreach($subtypes as $sind => $stype) {
				if($stype[0] == $typeName || $stype[1] == $typeName) {
					return $sind;
				}
			}
		} else {
			$alltypes = shivanode_get_types('full');
			foreach($alltypes as $tind => $type) {
				if ($tind == $typeName || $type['name'] == $typeName) {
					return $type['index'];
				}
			}
		}
		return -1;
	}
	
	/**
	 * Gets the parent machine name for a subtype
	 * 
	 * @param mixed $stind
	 * 	Subtype index or machine name of subtype
	 * 
	 * @return mixed
	 * 	Returns a string of the machine name of the parent, if found
	 *  Or returns FALSE if not found
	 */
	function _shivanode_get_parent_type($stind) {
		$alltypes = shivanode_get_types('full');
		foreach ($alltypes as $pind => $type) {
			if ($type['subtypes']) {
				// If it's an integer index
				if(is_int($stind) && isset($type['subtypes'][$stind])) {
					return $pind;
				// If it's a subtype machine name
				} else if (!is_int($stind)) {
					foreach ($type['subtypes'] as $sind => $stype) {
						if($stype[1] == $stind) {
							return $pind;
						}
					}
				}
			}
		}
		return FALSE; // Return FALSE if not found
	}
	
	/**
	 * Get a list of thumb images variable names. The variable names can be use with variable_get() to retreive the file Id
	 * for the thumbnail image stored in Drupal.
	 * 
	 * @return array
	 * 	Returns an array with two keys "types" and "subtypes" each listing the thumb image variable name under its index
	 */
	function _shivanode_get_thumb_image_list() {
		$alltypes = shivanode_get_types('full');
		$outurls = array(
			'types' => array(),
			'subtypes' => array(),
		);
		foreach ($alltypes as $mnm => $type) {
			$outurls['types'][$type['index']] = $type['image'];
			if ($type['subtypes']) {
				foreach ($type['subtypes'] as $sind => $subtype) {
					if (!empty($subtype[2])) { $outurls['subtypes'][$sind] = $subtype[2]; }
	 			}
			}
		}
		return $outurls;
	}
	
	/**
	 * Determines whether a type is deprecated or not called by _shivanode_is_deprecated in shivanode.inc to not require include load each time
	 * 
	 * @param int $tindex
	 * 	Type or subtype index
	 * 
	 * @param boolean $isSubtype
	 * 	Whether this is a subtype or not
	 * 
	 */
function _shivanode_is_type_deprecated($tindex, $isSubtype=FALSE) {
	$stindex = -1;
	if ($isSubtype) {
		$stindex = $tindex;
		$parentnm = _shivanode_get_parent_type($stindex);
		$tindex = _shivanode_get_index($parentnm);
	}
	$tinfo = _shivanode_get_type_info($tindex);
	if (is_array($tinfo) && isset($tinfo['deprecated'])) {
		return $tinfo['deprecated'];
	}
	return FALSE;
}	