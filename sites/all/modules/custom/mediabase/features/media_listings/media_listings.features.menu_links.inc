<?php
/**
 * @file
 * media_listings.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function media_listings_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: user-menu_add-content:node/add.
  $menu_links['user-menu_add-content:node/add'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add',
    'router_path' => 'node/add',
    'link_title' => 'Add Content',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_add-content:node/add',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: user-menu_all-collections:collections/all.
  $menu_links['user-menu_all-collections:collections/all'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'collections/all',
    'router_path' => 'collections/all',
    'link_title' => 'All Collections',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_all-collections:collections/all',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'user-menu_collections:collections/all',
  );
  // Exported menu link: user-menu_av-content-admin:shanti/admin/avcontent.
  $menu_links['user-menu_av-content-admin:shanti/admin/avcontent'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'shanti/admin/avcontent',
    'router_path' => 'shanti/admin/avcontent',
    'link_title' => 'AV Content Admin',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_av-content-admin:shanti/admin/avcontent',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'user-menu_my-content:mycontent/media',
  );
  // Exported menu link: user-menu_collections:collections/all.
  $menu_links['user-menu_collections:collections/all'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'collections/all',
    'router_path' => 'collections/all',
    'link_title' => 'Collections',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_collections:collections/all',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: user-menu_contact-us:contact.
  $menu_links['user-menu_contact-us:contact'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'contact',
    'router_path' => 'contact',
    'link_title' => 'Contact Us',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_contact-us:contact',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'user-menu_help:<front>',
  );
  // Exported menu link: user-menu_create-a-collection:node/add/collection.
  $menu_links['user-menu_create-a-collection:node/add/collection'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/collection',
    'router_path' => 'node/add/collection',
    'link_title' => 'Create a Collection',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_create-a-collection:node/add/collection',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'user-menu_collections:collections/all',
  );
  // Exported menu link: user-menu_help:<front>.
  $menu_links['user-menu_help:<front>'] = array(
    'menu_name' => 'user-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Help',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_help:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: user-menu_knowledge-base-docs:https://wiki.shanti.virginia.edu/x/KCvHAg.
  $menu_links['user-menu_knowledge-base-docs:https://wiki.shanti.virginia.edu/x/KCvHAg'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'https://wiki.shanti.virginia.edu/x/KCvHAg',
    'router_path' => '',
    'link_title' => 'Knowledge Base Docs',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_knowledge-base-docs:https://wiki.shanti.virginia.edu/x/KCvHAg',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'user-menu_help:<front>',
  );
  // Exported menu link: user-menu_my-collections:mycontent/collections.
  $menu_links['user-menu_my-collections:mycontent/collections'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'mycontent/collections',
    'router_path' => 'mycontent/collections',
    'link_title' => 'My Collections',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_my-collections:mycontent/collections',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'user-menu_my-content:mycontent/media',
  );
  // Exported menu link: user-menu_my-content:mycontent/media.
  $menu_links['user-menu_my-content:mycontent/media'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'mycontent/media',
    'router_path' => 'mycontent/media',
    'link_title' => 'My Content',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_my-content:mycontent/media',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: user-menu_my-media:mycontent/media.
  $menu_links['user-menu_my-media:mycontent/media'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'mycontent/media',
    'router_path' => 'mycontent/media',
    'link_title' => 'My Media',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_my-media:mycontent/media',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'user-menu_my-content:mycontent/media',
  );
  // Exported menu link: user-menu_my-memberships:mycontent/memberships.
  $menu_links['user-menu_my-memberships:mycontent/memberships'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'mycontent/memberships',
    'router_path' => 'mycontent/memberships',
    'link_title' => 'My Memberships',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_my-memberships:mycontent/memberships',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'user-menu_my-content:mycontent/media',
  );
  // Exported menu link: user-menu_my-workflow:mycontent/workflow.
  $menu_links['user-menu_my-workflow:mycontent/workflow'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'mycontent/workflow',
    'router_path' => 'mycontent/workflow',
    'link_title' => 'My Workflow',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_my-workflow:mycontent/workflow',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'user-menu_my-content:mycontent/media',
  );
  // Exported menu link: user-menu_upload-a-video:node/add/video.
  $menu_links['user-menu_upload-a-video:node/add/video'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/video',
    'router_path' => 'node/add/video',
    'link_title' => 'Upload a Video',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_upload-a-video:node/add/video',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'user-menu_add-content:node/add',
  );
  // Exported menu link: user-menu_upload-audio:node/add/audio.
  $menu_links['user-menu_upload-audio:node/add/audio'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/audio',
    'router_path' => 'node/add/audio',
    'link_title' => 'Upload Audio',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_upload-audio:node/add/audio',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'user-menu_add-content:node/add',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('AV Content Admin');
  t('Add Content');
  t('All Collections');
  t('Collections');
  t('Contact Us');
  t('Create a Collection');
  t('Help');
  t('Knowledge Base Docs');
  t('My Collections');
  t('My Content');
  t('My Media');
  t('My Memberships');
  t('My Workflow');
  t('Upload Audio');
  t('Upload a Video');

  return $menu_links;
}
