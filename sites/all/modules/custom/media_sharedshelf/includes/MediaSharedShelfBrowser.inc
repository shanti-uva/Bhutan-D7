<?php
/**
 * @file
 * Definition of MediaSharedShelfBrowser.
 */

/**
 * Media browser plugin for displaying a specific view and display.
 */
class MediaSharedShelfBrowser extends MediaBrowserPlugin {
  /**
   * Implements MediaBrowserPluginInterface::access().
   */
  public function access($account = NULL) {
    // When creating content the second parameter is file type instead of file.
    return file_entity_access('create', 'image');
  }

  /**
   * Implements MediaBrowserPlugin::view().
   */
  public function view() {
    // Check if the user is able to add remote media.
    if (user_access('add media from remote sources')) {
      $build['form'] = drupal_get_form('media_sharedshelf_wysiwyg_add', $this->params['types'], $this->params['multiselect']);
      return $build;
    }
  }
}
