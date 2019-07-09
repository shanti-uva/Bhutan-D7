<?php

/**
 * @file
 * shanti_image_views.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function shanti_image_views_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_image-agents:admin/image/agents.
  $menu_links['management_image-agents:admin/image/agents'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/image/agents',
    'router_path' => 'admin/image/agents',
    'link_title' => 'Image Agents',
    'options' => array(
      'attributes' => array(
        'title' => 'An admin page for managing agents associated with images',
      ),
      'identifier' => 'management_image-agents:admin/image/agents',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'management_shanti-images:admin/config/media/shanti_images/iiif-list-view',
  );
  // Exported menu link: management_image-descriptions:admin/image/descriptions.
  $menu_links['management_image-descriptions:admin/image/descriptions'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/image/descriptions',
    'router_path' => 'admin/image/descriptions',
    'link_title' => 'Image Descriptions',
    'options' => array(
      'attributes' => array(
        'title' => 'Admin page for managing descriptions associated with images',
      ),
      'identifier' => 'management_image-descriptions:admin/image/descriptions',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'management_shanti-images:admin/config/media/shanti_images/iiif-list-view',
  );
  // Exported menu link: management_shanti-images:admin/config/media/shanti_images/iiif-list-view.
  $menu_links['management_shanti-images:admin/config/media/shanti_images/iiif-list-view'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/media/shanti_images/iiif-list-view',
    'router_path' => 'admin/config/media/shanti_images/iiif-list-view',
    'link_title' => 'Shanti Images',
    'options' => array(
      'attributes' => array(
        'title' => 'List of all Shanti Images',
      ),
      'identifier' => 'management_shanti-images:admin/config/media/shanti_images/iiif-list-view',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'management_content:admin/content',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Image Agents');
  t('Image Descriptions');
  t('Shanti Images');

  return $menu_links;
}
