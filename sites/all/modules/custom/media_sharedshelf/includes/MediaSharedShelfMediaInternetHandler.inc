<?php

/**
 * @file
 * Define MediaSharedShelfMediaInternetHandler class.
 */

/**
 * SharedShelf Media Internet Handler.
 */
class MediaSharedShelfMediaInternetHandler extends MediaInternetBaseHandler {
  /**
   * Parse the internal URI to make it a unique URI.
   *
   * @param string $embed_code
   *   The internal string used to represent the ShareShelf object.
   *
   * @return string
   *   The unique URI for the SharedShelf object.
   */
  public function parse($embed_code) {
    return media_sharedshelf_media_parse($embed_code);
  }

  /**
   * Indicate if this object belongs to SharedShelf.
   *
   * @param string $embed_code
   *   The internal string used to represent the SharedShelf object.
   *
   * @return bool
   *   Returns TRUE to indicate it is a SharedShelf object.
   */
  public function claim($embed_code) {
    return ($this->parse($embed_code) != '') ? TRUE : FALSE;
  }

  /**
   * Before saving the file object perform these actions.
   *
   * @param object $file_obj
   *   The file object to be saved.
   */
  public function preSave(&$file_obj) {
    // If a user enters a duplicate, the object will be saved again.
    // Set the timestamp to the current time, so that the media item shows up
    // at the top of the media library, where they would expect to see it.
    $file_obj->timestamp = REQUEST_TIME;
  }

  /**
   * Save the file object.
   *
   * @return object
   *   Returns the saved file object.
   */
  public function save() {
    $file = $this->getFileObject();
    $this->preSave($file);
    file_save($file);
    return $file;
  }

  /**
   * Gets the file object based on its URI.
   *
   * @return object
   *   Returns the file object representation for this object's embed code.
   */
  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    return file_uri_to_object($uri, TRUE);
  }
}
