<?php

define('SHANTI_SARVAKA_TEXTS_PATH',drupal_get_path('theme','shanti_sarvaka_texts'));

/**
 * Alter Breadcrumbs to add Collection before item or if not part of collection, then creators name.
 */
 /*
function shanti_sarvaka_texts_menu_breadcrumb_alter(&$active_trail, $item)
{
 if ($active_trail[0]['title'] == 'Home') {
   array_shift($active_trail);
 }
}
*/
function shanti_sarvaka_texts_menu_breadcrumb_alter(&$active_trail, $item) {
   $map = $item['map']; // Item map tells us about what page we are on
   if ($map[0] == "node") {
       //dpm($item, 'itme in bc alter');
       $node = $map[1];
       // if it's a collection node, add link to all collections before it's name
       if (in_array($node->type, array('collection', 'subcollection')) || $node->type == 'shivanode' && !empty($node->field_og_collection_ref)) {
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
   }
}


// views-exposed-form-full-text-local-block-1
// views-exposed-form-text-search-block-3
function shanti_sarvaka_texts_form_alter(&$form, $form_state, $form_id)
{
  // Note that $form_id != $form['#id']
  if ($form_id == 'views_exposed_form'
    && preg_match('/^views-exposed-form-all-texts/', $form['#id']))
  {
    $form['title'] += array(
      '#attributes' => array(
        'placeholder' => 'Search by Title',
      ),
    );
    $form['field_book_author_value'] += array(
      '#attributes' => array(
        'placeholder' => 'Search by Author',
      ),
    );
  }
}

function shanti_sarvaka_texts_preprocess_node(&$vars)
{
  if ($vars['type'] == 'book' && $vars['teaser'] == FALSE) {
    // If not top of book, redirect to the book
    // THIS COULD BE HANDLED IN PAGE MANAGER -- SO NOT THEME DEPENDENT
    // But, not sure how to keep the query arg   ('s')
    $nid = $vars['nid'];
    $bid = $vars['book']['bid'];
    if (!$bid) {
    	drupal_set_message("This is not a book!");
    }
    elseif ($bid != $nid) {
		$s = '';
		if (array_key_exists('s',$_GET)) {
		    $s = $_GET['s'];
		}
		drupal_goto("node/$bid", array('query' => array('s' => $s), 'fragment' => "shanti-texts-$nid"));
	}
    $top_mlid = $vars['book']['p1'];

    // Highlight search hits (a bit of a kludge)
    if (isset($_GET['s']) && !preg_match("/^\s*$/",$_GET['s'])) {
      $s = $_GET['s'];
      $book_body_rendered = preg_replace_callback(
        "/($s)/i",
        function($match) use (&$count) {
          $count++;
          return "<span id='shanti-texts-search-hit-{$count}' "
            . "class='shanti-texts-search-hit'>$match[1]</span>";
        },
        $book_body_rendered,-1,$count
      );
    }

    if ($vars['view_mode'] == 'embed') {
        // May want to Do something special here
    }

    // Add CSS and JS
    $js_settings = array(
      'book'        => $vars['book'],
      'book_title'  => $vars['book']['link_title'],
      'kwic_n'      => isset($_GET['n']) ? $_GET['n'] : 0,
      #'edit_rights'	=> user_access('add content to books') && user_access('create new books'),
    );

    drupal_add_js('sites/all/libraries/jquery.inview/jquery.inview.min.js', 'file');
    drupal_add_js('sites/all/libraries/jquery.scrollTo/jquery.scrollTo.min.js', 'file');
    drupal_add_js(SHANTI_SARVAKA_TEXTS_PATH . '/js/shanti_texts.js', 'file');
    drupal_add_js(SHANTI_SARVAKA_TEXTS_PATH . '/js/jquery.localscroll.min.js', 'file'); # MOVE THIS TO LIBRARIES
    drupal_add_js(array('shantiTexts' => $js_settings), 'setting');
    drupal_add_css(SHANTI_SARVAKA_TEXTS_PATH . '/css/shanti_texts.css');
    drupal_add_css(SHANTI_SARVAKA_TEXTS_PATH . '/css/shanti_texts_footnotes.css');

    // Remove things we don't want to see
    foreach(array_keys($vars['content']) as $k) {
      if ($k != 'shanti_texts_container') {
        unset($vars['content'][$k]);
      }
    }

    // NOT SURE WHY THIS IS HERE
    unset($vars['submitted']);

  }
}

function shanti_sarvaka_texts_views_pre_render($view) {
    /*$view->result[0]->node_og_membership_nid  = "<div>12 items</div>";
    foreach($view->result as &$row) {
        $nid = $row->node_og_membership_nid;
        $num_of_items = shanti_collections_get_items_in_collection($nid, 'count');
        $row->node_og_membership_nid = t('@num items', array(
            '@num' => $num_of_items,
        ));
    }
    dpm($view->result[0], 'first row');*/
}

function shanti_sarvaka_texts_get_edit_widget($nid,$coll_id) {
    $node = node_load($nid);
    $lang = $node->language;
    $bid  = $node->book['bid'];
    $mlid = $node->book['mlid'];
    $node_edit_link = l('<i class="fa fa-pencil-square-o" aria-hidden="true"></i>',
        "node/$nid/edit",
        array(
            'html' => TRUE,
            'attributes' => array('title' => t('Edit this page'), 'class' => array('text-edit-button')),
        )
    );
    $node_add_link = l('<i class="fa fa-plus" aria-hidden="true"></i>',
        "node/add/book",
        array(
            'html' => TRUE,
            'query' => array(
                'field_og_collection_ref' => $coll_id,
                'parent' => $mlid
            ),
            'attributes' => array('title' => t('Add a new page under this one'), 'class' => array('text-edit-button')),
        )
    );
    $widget = array(
        'shanti-texts-section-controls' => array(
            '#type' => 'markup',
            '#prefix' => '<span class="shanti-texts-section-controls">',
            '#suffix' => '</span>',
            '#markup' => $node_edit_link . $node_add_link,
            '#access' => (
                user_has_role(3) || (
                    user_access('add content to books')
                    //&& og_is_member('node',$coll_id,'user')
                    && og_user_access('node',$coll_id,'create book content')
                    && og_user_access('node',$coll_id,'update own book content')
                )
            ),
        ),
    );
    return $widget;
}
