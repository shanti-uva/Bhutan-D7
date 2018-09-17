<?php
/**
 * @file
 * shanti_collections.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function shanti_collections_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = TRUE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_52ee52a2-4d7c-48da-b5b0-f8e5d7a02ee7';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -25;
  $handler->conf = array(
    'title' => 'Subcollection',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => 'shanti-collection-page',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(
      0 => array(
        'identifier' => 'Parent Collection [field_og_parent_collection_ref]',
        'keyword' => 'collection',
        'name' => 'entity_from_field:field_og_parent_collection_ref-node-node',
        'delta' => 0,
        'context' => 'argument_entity_id:node_1',
        'id' => 1,
      ),
    ),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'subcollection' => 'subcollection',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'og_is_node_group',
          'settings' => NULL,
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'bootstrap_threecol_stacked';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => array(
        'column_type' => 'col-lg',
        'column_size' => '4',
        'offset_type' => 'col-lg-offset',
        'offset_size' => '0',
      ),
      'top' => NULL,
      'left' => array(
        'column_type' => 'col-lg',
        'column_size' => '3',
        'offset_type' => 'col-lg-offset',
        'offset_size' => '0',
      ),
      'right' => array(
        'column_type' => 'col-lg',
        'column_size' => '4',
        'offset_type' => 'col-lg-offset',
        'offset_size' => '0',
      ),
      'bottom' => array(
        'column_type' => 'col-lg',
        'column_size' => '12',
        'offset_type' => 'col-lg-offset',
        'offset_size' => '0',
      ),
      'middle' => array(
        'column_type' => 'col-lg',
        'column_size' => '5',
        'offset_type' => 'col-lg-offset',
        'offset_size' => '0',
      ),
    ),
    'left' => array(
      'style' => 'bootstrap_region',
    ),
    'right' => array(
      'style' => 'bootstrap_region',
    ),
    'bottom' => array(
      'style' => 'bootstrap_region',
    ),
    'middle' => array(
      'style' => 'bootstrap_region',
    ),
    'style' => 'bootstrap_region',
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'af3b1463-d896-4ca2-bca3-342c1d85a5e6';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'node_view__panel_context_52ee52a2-4d7c-48da-b5b0-f8e5d7a02ee7';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-c4cb6c8d-c522-476d-849c-f54fe1cbc148';
  $pane->panel = 'bottom';
  $pane->type = 'views';
  $pane->subtype = 'all_texts';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_pager_settings' => 0,
    'use_pager' => 1,
    'nodes_per_page' => '36',
    'pager_id' => '0',
    'offset' => '0',
    'more_link' => 0,
    'feed_icons' => 0,
    'panel_args' => 0,
    'link_to_view' => 0,
    'args' => '',
    'url' => '',
    'display' => 'page_by_collection',
    'context' => array(
      0 => 'argument_entity_id:node_1.nid',
    ),
    'override_title' => 1,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'c4cb6c8d-c522-476d-849c-f54fe1cbc148';
  $display->content['new-c4cb6c8d-c522-476d-849c-f54fe1cbc148'] = $pane;
  $display->panels['bottom'][0] = 'new-c4cb6c8d-c522-476d-849c-f54fe1cbc148';
  $pane = new stdClass();
  $pane->pid = 'new-c7d19d2f-a649-432a-a456-bd98ad158fdd';
  $pane->panel = 'left';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_general_featured_image';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'image',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'image_style' => 'medium',
      'image_link' => '',
    ),
    'context' => 'relationship_entity_from_field:field_og_parent_collection_ref-node-node_1',
    'override_title' => 1,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => '',
    'css_class' => 'shanti-collection-featured-image',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'c7d19d2f-a649-432a-a456-bd98ad158fdd';
  $display->content['new-c7d19d2f-a649-432a-a456-bd98ad158fdd'] = $pane;
  $display->panels['left'][0] = 'new-c7d19d2f-a649-432a-a456-bd98ad158fdd';
  $pane = new stdClass();
  $pane->pid = 'new-8a5cfb55-2cad-4bae-8c15-543ed9a5e51f';
  $pane->panel = 'middle';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:body';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'text_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'argument_entity_id:node_1',
    'override_title' => 1,
    'override_title_text' => 'Overview',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '8a5cfb55-2cad-4bae-8c15-543ed9a5e51f';
  $display->content['new-8a5cfb55-2cad-4bae-8c15-543ed9a5e51f'] = $pane;
  $display->panels['middle'][0] = 'new-8a5cfb55-2cad-4bae-8c15-543ed9a5e51f';
  $pane = new stdClass();
  $pane->pid = 'new-6a6f401a-eae8-475a-b6b2-c4ef7aeb55d5';
  $pane->panel = 'right';
  $pane->type = 'node_create_links';
  $pane->subtype = 'node_create_links';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'types' => array(
      'book' => 'book',
    ),
    'field_name' => 'field_og_collection_ref',
    'context' => 'argument_entity_id:node_1',
    'override_title' => 1,
    'override_title_text' => 'Content Creation',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '6a6f401a-eae8-475a-b6b2-c4ef7aeb55d5';
  $display->content['new-6a6f401a-eae8-475a-b6b2-c4ef7aeb55d5'] = $pane;
  $display->panels['right'][0] = 'new-6a6f401a-eae8-475a-b6b2-c4ef7aeb55d5';
  $pane = new stdClass();
  $pane->pid = 'new-fe0855bb-3ff2-4812-8d03-4f67e722154d';
  $pane->panel = 'right';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_og_parent_collection_ref';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'entityreference_label',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'link' => 1,
    ),
    'context' => 'argument_entity_id:node_1',
    'override_title' => 1,
    'override_title_text' => 'Parent Collection',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'fe0855bb-3ff2-4812-8d03-4f67e722154d';
  $display->content['new-fe0855bb-3ff2-4812-8d03-4f67e722154d'] = $pane;
  $display->panels['right'][1] = 'new-fe0855bb-3ff2-4812-8d03-4f67e722154d';
  $pane = new stdClass();
  $pane->pid = 'new-03ca1f90-b135-46d0-92bf-a0d5af13ce4d';
  $pane->panel = 'right';
  $pane->type = 'views_panes';
  $pane->subtype = 'collection_members-panel_pane_2';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'use_pager' => 0,
    'pager_id' => '0',
    'items_per_page' => '5',
    'fields_override' => array(
      'name' => 1,
    ),
    'context' => array(
      0 => 'argument_entity_id:node_1',
    ),
    'override_title' => 1,
    'override_title_text' => 'Members',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '03ca1f90-b135-46d0-92bf-a0d5af13ce4d';
  $display->content['new-03ca1f90-b135-46d0-92bf-a0d5af13ce4d'] = $pane;
  $display->panels['right'][2] = 'new-03ca1f90-b135-46d0-92bf-a0d5af13ce4d';
  $pane = new stdClass();
  $pane->pid = 'new-5d92aff6-154f-4397-a853-be91bb57793c';
  $pane->panel = 'right';
  $pane->type = 'views_panes';
  $pane->subtype = 'collection_members-panel_pane_2';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'use_pager' => 0,
    'pager_id' => '0',
    'items_per_page' => '5',
    'fields_override' => array(
      'name' => 1,
    ),
    'context' => array(
      0 => 'relationship_entity_from_field:field_og_parent_collection_ref-node-node_1',
    ),
    'override_title' => 1,
    'override_title_text' => 'Inherited Members',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = '5d92aff6-154f-4397-a853-be91bb57793c';
  $display->content['new-5d92aff6-154f-4397-a853-be91bb57793c'] = $pane;
  $display->panels['right'][3] = 'new-5d92aff6-154f-4397-a853-be91bb57793c';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-6a6f401a-eae8-475a-b6b2-c4ef7aeb55d5';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_52ee52a2-4d7c-48da-b5b0-f8e5d7a02ee7'] = $handler;

  $handler = new stdClass();
  $handler->disabled = TRUE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_61ca28d8-5f1f-4434-9613-f8954b9634e6';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -26;
  $handler->conf = array(
    'title' => 'Collection',
    'no_blocks' => 1,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => 'shanti-collection-page',
    'css_id' => 'shanti-texts-collection',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'collection' => 'collection',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'og_is_node_group',
          'settings' => NULL,
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
    'panels_css_js_files_css' => '',
    'panels_css_js_files_js' => '',
    'panels_css_js_code_css' => '',
    'panels_css_js_code_js' => '',
    'panels_css_js_code_js_wrapper' => '0',
  );
  $display = new panels_display();
  $display->layout = 'bootstrap_threecol_stacked';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'left' => array(
        'column_type' => 'col-sm',
        'column_size' => '3',
        'offset_type' => 'col-lg-offset',
        'offset_size' => '0',
      ),
      'middle' => array(
        'column_type' => 'col-lg',
        'column_size' => '5',
        'offset_type' => 'col-lg-offset',
        'offset_size' => '0',
      ),
      'bottom' => array(
        'column_type' => 'col-lg',
        'column_size' => '12',
        'offset_type' => 'col-lg-offset',
        'offset_size' => '0',
      ),
      'right' => array(
        'column_type' => 'col-sm',
        'column_size' => '4',
        'offset_type' => 'col-lg-offset',
        'offset_size' => '0',
      ),
    ),
    'right' => array(
      'style' => 'bootstrap_region',
    ),
    'middle' => array(
      'style' => 'bootstrap_region',
    ),
    'left' => array(
      'style' => 'bootstrap_region',
    ),
    'bottom' => array(
      'style' => 'bootstrap_region',
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = 'de7da5ca-bd6a-4157-9149-0bb1be877440';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'node_view__panel_context_61ca28d8-5f1f-4434-9613-f8954b9634e6';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-4a8dd07e-86c1-4e8a-9008-33c47862db9d';
  $pane->panel = 'bottom';
  $pane->type = 'php';
  $pane->subtype = 'view_collections_content';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'admin_title' => '',
    'title' => '',
    'body' => '<h4>Example PHP code</h4>
<p>Time: <?php print date(\'H:i\', time());?></p>
',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '4a8dd07e-86c1-4e8a-9008-33c47862db9d';
  $display->content['new-4a8dd07e-86c1-4e8a-9008-33c47862db9d'] = $pane;
  $display->panels['bottom'][0] = 'new-4a8dd07e-86c1-4e8a-9008-33c47862db9d';
  $pane = new stdClass();
  $pane->pid = 'new-77299824-f4ba-49de-9e84-f217a8627592';
  $pane->panel = 'left';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_general_featured_image';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'image',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'file_view_mode' => 'teaser',
      'image_style' => 'medium',
      'image_link' => '',
    ),
    'context' => 'argument_entity_id:node_1',
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => 'shanti-collection-featured-image',
    'css_class' => '',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '77299824-f4ba-49de-9e84-f217a8627592';
  $display->content['new-77299824-f4ba-49de-9e84-f217a8627592'] = $pane;
  $display->panels['left'][0] = 'new-77299824-f4ba-49de-9e84-f217a8627592';
  $pane = new stdClass();
  $pane->pid = 'new-ec3c11e8-72fd-421f-a63d-f1309c982ef8';
  $pane->panel = 'middle';
  $pane->type = 'node_body';
  $pane->subtype = 'node_body';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'context' => 'argument_entity_id:node_1',
    'override_title' => 1,
    'override_title_text' => 'Overview',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_id' => '',
    'css_class' => 'shanti-collection-body',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'ec3c11e8-72fd-421f-a63d-f1309c982ef8';
  $display->content['new-ec3c11e8-72fd-421f-a63d-f1309c982ef8'] = $pane;
  $display->panels['middle'][0] = 'new-ec3c11e8-72fd-421f-a63d-f1309c982ef8';
  $pane = new stdClass();
  $pane->pid = 'new-2612f008-948e-4bf0-b632-4d0ad9aa4f22';
  $pane->panel = 'right';
  $pane->type = 'node_create_links';
  $pane->subtype = 'node_create_links';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'types' => array(
      'book' => 'book',
    ),
    'field_name' => 'field_og_collection_ref',
    'context' => 'argument_entity_id:node_1',
    'override_title' => 1,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
    'style' => 'default',
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '2612f008-948e-4bf0-b632-4d0ad9aa4f22';
  $display->content['new-2612f008-948e-4bf0-b632-4d0ad9aa4f22'] = $pane;
  $display->panels['right'][0] = 'new-2612f008-948e-4bf0-b632-4d0ad9aa4f22';
  $pane = new stdClass();
  $pane->pid = 'new-041df933-5168-4432-8625-922dbfb4eed9';
  $pane->panel = 'right';
  $pane->type = 'node_create_links';
  $pane->subtype = 'node_create_links';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'types' => array(
      'subcollection' => 'subcollection',
    ),
    'field_name' => 'field_og_parent_collection_ref',
    'context' => 'argument_entity_id:node_1',
    'override_title' => 1,
    'override_title_text' => 'Content Creation',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
    'style' => 'default',
  );
  $pane->css = array(
    'css_id' => '',
    'css_class' => '',
  );
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '041df933-5168-4432-8625-922dbfb4eed9';
  $display->content['new-041df933-5168-4432-8625-922dbfb4eed9'] = $pane;
  $display->panels['right'][1] = 'new-041df933-5168-4432-8625-922dbfb4eed9';
  $pane = new stdClass();
  $pane->pid = 'new-7005d8fc-eac9-44b2-9015-3db2ccd79812';
  $pane->panel = 'right';
  $pane->type = 'views_panes';
  $pane->subtype = 'collections-panel_pane_1';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'context' => array(
      0 => 'argument_entity_id:node_1',
    ),
    'use_pager' => 1,
    'pager_id' => '0',
    'items_per_page' => '36',
    'fields_override' => array(
      'nothing' => 0,
      'title' => 1,
    ),
    'override_title' => 1,
    'override_title_text' => 'Subcollections',
    'override_title_heading' => 'h3',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
    'style' => 'default',
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '7005d8fc-eac9-44b2-9015-3db2ccd79812';
  $display->content['new-7005d8fc-eac9-44b2-9015-3db2ccd79812'] = $pane;
  $display->panels['right'][2] = 'new-7005d8fc-eac9-44b2-9015-3db2ccd79812';
  $pane = new stdClass();
  $pane->pid = 'new-d57fb538-5d88-4154-b4c0-56450f612416';
  $pane->panel = 'right';
  $pane->type = 'views_panes';
  $pane->subtype = 'collection_members-panel_pane_2';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'use_pager' => 1,
    'pager_id' => '0',
    'items_per_page' => '5',
    'fields_override' => array(
      'name' => 1,
    ),
    'context' => array(
      0 => 'argument_entity_id:node_1',
    ),
    'override_title' => 1,
    'override_title_text' => 'Members',
    'override_title_heading' => 'h3',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = 'd57fb538-5d88-4154-b4c0-56450f612416';
  $display->content['new-d57fb538-5d88-4154-b4c0-56450f612416'] = $pane;
  $display->panels['right'][3] = 'new-d57fb538-5d88-4154-b4c0-56450f612416';
  $pane = new stdClass();
  $pane->pid = 'new-92acdfa7-dbee-4f16-acfa-cda83b1dca0f';
  $pane->panel = 'right';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_og_parent_collection_ref';
  $pane->shown = FALSE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'entityreference_label',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'link' => 1,
    ),
    'context' => 'argument_entity_id:node_1',
    'override_title' => 1,
    'override_title_text' => 'Parent Collection',
    'override_title_heading' => 'h3',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = '92acdfa7-dbee-4f16-acfa-cda83b1dca0f';
  $display->content['new-92acdfa7-dbee-4f16-acfa-cda83b1dca0f'] = $pane;
  $display->panels['right'][4] = 'new-92acdfa7-dbee-4f16-acfa-cda83b1dca0f';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_61ca28d8-5f1f-4434-9613-f8954b9634e6'] = $handler;

  return $export;
}
