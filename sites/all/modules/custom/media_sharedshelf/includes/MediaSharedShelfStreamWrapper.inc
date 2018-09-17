<?php
/**
 * @file
 * Create a SharedShelf Stream Wrapper class for the Media/Resource module.
 * @TODO Do we want to handle different options for SharedShelf?
 * @TODO Review different internal schema formats with SHANTI.
 * @TODO Determine which ones need to be added e.g., project or search results.
 */

/**
 * Create an instance like one of these options below:
 * 1. An individual asset (image) using its SharedShelf ID
 *  new MediaSharedShelfStreamWrapper('sharedshelf://a/[asset-id]');
 * 2. Selecting a project means to dynamically retrieve a group of images and
 * display them.
 *  new MediaSharedShelfStreamWrapper('sharedshelf://p/[proj-id]');
 * 3. Select asset group(s) within a project to dynamically retrieve just the
 * images for those sets and display them.
 * NOTE: One or more asset groups (image sets) can be specified by separating
 * their values with a period.
 *  MediaSharedShelfStreamWrapper('sharedshelf://p/[proj-id]/g/[asset-grp-id]');
 * 4. Select a group of images to display dynamically based on a saved search.
 *   new MediaSharedShelfStreamWrapper('sharedshelf://search/?????');
 * 5. An individual asset (image) using its full size image URL retrieved from
 * SharedShelf manually.
 *  new MediaSharedShelfStreamWrapper('sharedshelf://l/[stor]/f/[unique-file]');
 */
class MediaSharedShelfStreamWrapper extends MediaReadOnlyStreamWrapper {
  protected $parameters = array(
    'a' => NULL,
    'f' => NULL,
    'l' => NULL,
    'search' => NULL,
  );

  /**
   * Interpolates the URL.
   *
   * @return string
   *   Returns a string containing the internal schema stored URI.
   */
  public function interpolateUrl() {
    if (isset($this->parameters['a']) || isset($this->parameters['f'])) {
      return media_sharedshelf_image_url($this->uri);
    }
  }

  /**
   * Get the url of the original image.
   *
   * @return string
   *   Returns the SharedShelf location URL of the object.
   */
  public function getExternalUrl() {
    // Look for asset image representations.
    if (isset($this->parameters['a']) || isset($this->parameters['f'])) {
      return media_sharedshelf_image_url($this->uri);
    }
  }

  /**
   * Get the original object.
   *
   * @return string
   *   Returns the URL of the SharedShelf location of the object.
   */
  public function getOriginalThumbnailPath() {
    return $this->getExternalUrl();
  }

  /**
   * Get one of the 5 reduced file size representations of the image.
   *
   * @param int $size
   *   The preferred image representation size: 0 for 64px, 1 for 128px,
   *   2 for 256px, 3 for 512px, and 4 for 1024px.
   *
   * @return string
   *   Returns the bytestream content for the image size specified.
   */
  public function getFixedSizeImageRepresentation($size = 1) {
    // Look for asset image representations.
    if (isset($this->parameters['a'])) {
      return media_sharedshelf_image_representation($this->parameters['a'], $size);
    }
  }

  /**
   * Gets a locally stored copy of the object.
   *
   * @return string
   *   The local path to the object when it was copied to the file system.
   */
  public function getLocalThumbnailPath() {
    $local_path = str_replace('sharedshelf://', 'public://media-sharedshelf/', check_plain($this->uri));
    // Determine if the person added an image using the asset or an image URL.
    if (isset($this->parameters['f'])) {
      $mimetype = $this->getMimeType($this->uri);
    }
    elseif (isset($this->parameters['a'])) {
      $representation = $this->getFixedSizeImageRepresentation(media_sharedshelf_variable_get('local_cache_image_size'));
      $mimetype = $representation['mimetype'];
    }
    // Identify the appropriate file extension for the local copy of the image.
    switch ($mimetype) {
      case 'image/jpeg':
        $local_path .= '.jpg';
        break;

      case 'image/tiff':
        $local_path .= '.tif';
        break;

      case 'image/png':
        $local_path .= '.png';
        break;

      case 'image/gif':
        $local_path .= '.gif';
        break;

      default:
        $local_path .= '';
    }
    // If the local copy of the file does not already exist then create it.
    if (!file_exists($local_path)) {
      $dirname = drupal_dirname($local_path);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
      // For a full size image URL we just need to copy it as if it were a file.
      if (isset($this->parameters['f'])) {
        copy($this->getOriginalThumbnailPath(), $local_path);
      }
      // For an asset we need to write the bytes to the local file.
      elseif (isset($this->parameters['a'])) {
        if ($file_handle = fopen($local_path, 'wb')) {
          if (fwrite($file_handle, $representation['bytestream']) === FALSE) {
            $this->_report_error(t('Error writing to @localpath.', array('@localpath' => $local_path)));
          }
          if (!fclose($file_handle)) {
            $this->_report_error(t('Unable to close @localpath after writing.', array('@localpath' => $local_path)));
          }
        }
        else {
          $this->_report_error(t('Unable to open @localpath for writing.', array('@localpath' => $local_path)));
        }
      }
    }
    return $local_path;
  }

  /**
   * Get the mime type of the SharedShelf object.
   *
   * @param string $uri
   *   The URI of the SharedShelf object.
   * @param object $mapping
   *   The mapping.
   *
   * @return string
   *   The mime type of the SharedShelf object.
   */
  static public function getMimeType($uri, $mapping = NULL) {
    return media_sharedshelf_image_mimetype($uri);
  }
}
