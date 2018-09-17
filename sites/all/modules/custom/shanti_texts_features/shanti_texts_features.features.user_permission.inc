<?php
/**
 * @file
 * shanti_texts_features.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function shanti_texts_features_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access ckeditor link'.
  $permissions['access ckeditor link'] = array(
    'name' => 'access ckeditor link',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'ckeditor_link',
  );

  // Exported permission: 'access media browser'.
  $permissions['access media browser'] = array(
    'name' => 'access media browser',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'media',
  );

  // Exported permission: 'access printer-friendly version'.
  $permissions['access printer-friendly version'] = array(
    'name' => 'access printer-friendly version',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'book',
  );

  // Exported permission: 'add content to books'.
  $permissions['add content to books'] = array(
    'name' => 'add content to books',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'book',
  );

  // Exported permission: 'administer book outlines'.
  $permissions['administer book outlines'] = array(
    'name' => 'administer book outlines',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'book',
  );

  // Exported permission: 'administer ckeditor'.
  $permissions['administer ckeditor'] = array(
    'name' => 'administer ckeditor',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'ckeditor',
  );

  // Exported permission: 'administer ckeditor link'.
  $permissions['administer ckeditor link'] = array(
    'name' => 'administer ckeditor link',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'ckeditor_link',
  );

  // Exported permission: 'administer shanti_kmaps_admin'.
  $permissions['administer shanti_kmaps_admin'] = array(
    'name' => 'administer shanti_kmaps_admin',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'shanti_kmaps_admin',
  );

  // Exported permission: 'administer shanti_kmaps_fields'.
  $permissions['administer shanti_kmaps_fields'] = array(
    'name' => 'administer shanti_kmaps_fields',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'shanti_kmaps_fields',
  );

  // Exported permission: 'administer shanti_texts_splitter'.
  $permissions['administer shanti_texts_splitter'] = array(
    'name' => 'administer shanti_texts_splitter',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'shanti_texts_splitter',
  );

  // Exported permission: 'create book content'.
  $permissions['create book content'] = array(
    'name' => 'create book content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create collection content'.
  $permissions['create collection content'] = array(
    'name' => 'create collection content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create new books'.
  $permissions['create new books'] = array(
    'name' => 'create new books',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'book',
  );

  // Exported permission: 'customize ckeditor'.
  $permissions['customize ckeditor'] = array(
    'name' => 'customize ckeditor',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'ckeditor',
  );

  // Exported permission: 'delete any book content'.
  $permissions['delete any book content'] = array(
    'name' => 'delete any book content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any image files'.
  $permissions['delete any image files'] = array(
    'name' => 'delete any image files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own book content'.
  $permissions['delete own book content'] = array(
    'name' => 'delete own book content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own image files'.
  $permissions['delete own image files'] = array(
    'name' => 'delete own image files',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download any image files'.
  $permissions['download any image files'] = array(
    'name' => 'download any image files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download own image files'.
  $permissions['download own image files'] = array(
    'name' => 'download own image files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit any book content'.
  $permissions['edit any book content'] = array(
    'name' => 'edit any book content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any image files'.
  $permissions['edit any image files'] = array(
    'name' => 'edit any image files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own book content'.
  $permissions['edit own book content'] = array(
    'name' => 'edit own book content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own image files'.
  $permissions['edit own image files'] = array(
    'name' => 'edit own image files',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'publish any book content'.
  $permissions['publish any book content'] = array(
    'name' => 'publish any book content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'publish any content'.
  $permissions['publish any content'] = array(
    'name' => 'publish any content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'publish editable book content'.
  $permissions['publish editable book content'] = array(
    'name' => 'publish editable book content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'publish editable content'.
  $permissions['publish editable content'] = array(
    'name' => 'publish editable content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'publish own book content'.
  $permissions['publish own book content'] = array(
    'name' => 'publish own book content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'show book reorder tab'.
  $permissions['show book reorder tab'] = array(
    'name' => 'show book reorder tab',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'book_made_simple',
  );

  // Exported permission: 'show core Outline form element'.
  $permissions['show core Outline form element'] = array(
    'name' => 'show core Outline form element',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'book_made_simple',
  );

  // Exported permission: 'show core Outline tab'.
  $permissions['show core Outline tab'] = array(
    'name' => 'show core Outline tab',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'book_made_simple',
  );

  // Exported permission: 'unpublish any book content'.
  $permissions['unpublish any book content'] = array(
    'name' => 'unpublish any book content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'unpublish any content'.
  $permissions['unpublish any content'] = array(
    'name' => 'unpublish any content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'unpublish editable book content'.
  $permissions['unpublish editable book content'] = array(
    'name' => 'unpublish editable book content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'unpublish editable content'.
  $permissions['unpublish editable content'] = array(
    'name' => 'unpublish editable content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'unpublish own book content'.
  $permissions['unpublish own book content'] = array(
    'name' => 'unpublish own book content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'use shanti_texts_splitter'.
  $permissions['use shanti_texts_splitter'] = array(
    'name' => 'use shanti_texts_splitter',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'shanti_texts_splitter',
  );

  return $permissions;
}
