<?php
/**
 * @file
 * Definition for Styles.
 * @TODO Update if needed for new schema created for project/saved search.
 */

/**
 * Media SharedShelf Styles.
 */
class MediaSharedShelfStyles extends FileStyles {

  /**
   * Get the image URI.
   *
   * @return string
   *   A string representing the URI.
   */
  public function getImageUri() {
    if ($image_uri = $this->get('imageUri')) {
      return $image_uri;
    }
    $object = $this->getObject();
    if ($object->uri) {
      $wrapper = file_stream_wrapper_get_instance_by_uri($object->uri);
      return $wrapper->getLocalThumbnailPath();
    }
  }
  /**
   * The SharedShelf image.
   *
   * @param string $effect
   *   The effect.
   */
  public function sharedShelfImage($effect) {
    $variables = array(
      'uri' => $this->getUri(),
      'width' => $this->getWidth(),
      'height' => $this->getHeight(),
    );
    $variables = array_merge($variables, $this->variables);
    $this->setOutput(theme('media_sharedshelf_embed', $variables));
  }
}
