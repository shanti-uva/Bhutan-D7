<?php
/**
 * @file
 * Variable defaults for Media: SharedShelf.
 */

/**
 * Define our constants.
 */

/**
 * This is the variable namespace, automatically prepended to module variables.
 */
define('MEDIA_SHAREDSHELF_NAMESPACE', 'media_sharedshelf__');

define('MEDIA_SHAREDSHELF_MAIN_URL', 'http://catalog.sharedshelf.artstor.org/');
define('MEDIA_SHAREDSHELF_API_URL_DEMO', 'http://catalog.sharedshelf.demo.artstor.org');
define('MEDIA_SHAREDSHELF_API_URL_PRODUCTION', 'http://catalog.sharedshelf.artstor.org');

define('MEDIA_SHAREDSHELF_DEFAULT_PROJECT', '0');
define('MEDIA_SHAREDSHELF_DEFAULT_SEARCH_IMAGES_PER_PAGE', 12);
define('MEDIA_SHAREDSHELF_DEFAULT_LOCAL_CACHE_IMAGE_SIZE', 3);

define('MEDIA_SHAREDSHELF_NOT_APPLICABLE', 'N/A');

/**
 * Used for storing the cookies returned by SharedShelf after successful login
 * so that successive calls can be performed.
 */
$_media_sharedshelf_cookies = '';

/**
 * Used to define a list of SharedShelf servers that have the API available.
 *
 * @return array
 *   An associative array with URI keys and values indicating production vs.
 *   demo server.
 */
function media_sharedshelf_host_servers() {
  return array(MEDIA_SHAREDSHELF_API_URL_PRODUCTION => 'Production', MEDIA_SHAREDSHELF_API_URL_DEMO => 'Demo');
}

/**
 * Used to define constant array of image sizes available from SharedShelf.
 *
 * @return array
 *   An array with keys from 0 to 4 and values representing the pixel dimension.
 */
function media_sharedshelf_image_sizes() {
  return array(
    '0' => '64',
    '1' => '128',
    '2' => '256',
    '3' => '512',
    '4' => '1024',
  );
}

/**
 * Define array of images per page for displaying media from SharedShelf.
 *
 * @return array
 *   An array with the values 12, 24, 36, 48, and 60.
 */
function media_sharedshelf_number_images_per_page() {
  return array(
    '12' => '12',
    '24' => '24',
    '36' => '36',
    '48' => '48',
    '60' => '60',
  );
}

/**
 * An array of basic fields used in all SharedShelf projects.
 *
 * @return array
 *   Contains field definitions for creator, title, place, date, photographer,
 *   worktype, description and knowledge maps.
 */
function media_sharedshelf_basic_fields() {
  return array(
    // Added by ndg8f, 2015-06-25
  	'ssid' => array(
      'field_name' => 'field_sharedshelf_ssid',
      'type' => 'text',
      'cardinality' => 1,
      'default' => '',
      'locked' => TRUE,
      'settings' => array(
        'label' => t('SSID'),
        'description' => t('Shared Shelf ID number for this image'),
      ),
    ),  // End of add
    'creator' => array(
      'field_name' => 'field_sharedshelf_creator',
      'type' => 'text',
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'default' => '',
      'settings' => array(
        'label' => t('Creator'),
        'description' => t('Creator of the work.'),
      ),
    ),
    'title' => array(
      'field_name' => 'field_sharedshelf_title',
      'type' => 'text_long',
      'cardinality' => 1,
      'default' => '',
      'settings' => array(
        'label' => t('Title'),
        'description' => t('Title for the work.'),
      ),
    ),
    // Added by ndg8f, 2015-10-12
  	'projectid' => array(
      'field_name' => 'field_sharedshelf_project_id',
      'type' => 'text',
      'cardinality' => 1,
      'default' => '',
      'locked' => TRUE,
      'settings' => array(
        'label' => t('Project ID'),
        'description' => t('ID for the Shared Shelf Project to which this image belongs'),
      ),
    ),  // End of add
    'place' => array(
      'field_name' => 'field_sharedshelf_place',
      'type' => 'text_long',
      'cardinality' => 1,
      'default' => '',
      'settings' => array(
        'label' => t('Location'),
        'description' => t('Where the work is located.'),
      ),
    ),
    'date' => array(
      'field_name' => 'field_sharedshelf_date',
      'type' => 'text_long',
      'cardinality' => 1,
      'default' => '',
      'settings' => array(
        'label' => t('Date'),
        'description' => t('Date(s) associated with the work.'),
      ),
    ),
    'photographer' => array(
      'field_name' => 'field_sharedshelf_photographer',
      'type' => 'text_long',
      'cardinality' => 1,
      'default' => '',
      'settings' => array(
        'label' => t('Photographer'),
        'description' => t('Photagrapher of this media object.'),
      ),
    ),
    'worktype' => array(
      'field_name' => 'field_sharedshelf_worktype',
      'type' => 'text',
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'default' => '',
      'settings' => array(
        'label' => t('Work Type'),
        'description' => t('Type of work.'),
      ),
    ),
    'description' => array(
      'field_name' => 'field_sharedshelf_description',
      'type' => 'text_long',
      'cardinality' => 1,
      'default' => '',
      'settings' => array(
        'label' => t('Description'),
        'description' => t('Description of the media object.'),
      ),
    ),
    'kmaps' => array(
      'field_name' => 'field_sharedshelf_kmaps',
      'type' => 'text',
      'cardinality' => FIELD_CARDINALITY_UNLIMITED,
      'default' => '',
      'length' => 12,
      'settings' => array(
        'label' => t('Knowledge Maps'),
        'description' => t('Knowledge map identifiers.'),
      ),
    ),
    'solr_search_data' => array(
      'field_name' => 'field_sharedshelf_solr_search',
      'type' => 'text_long',
      'cardinality' => 1,
      'default' => '',
      'settings' => array(
        'label' => t('All Shared Shelf Metadata'),
        'description' => t('This field should only be modified to remove email addresses and URLs in Drupal when embedding an image and its data in a filtered or full HTML text format. This field is intended to store a complete copy of the Shared Shelf metadata for the media object to be used by the Solr indexing process only.'),
      ),
    ),
    
  );
}

/**
 * An array of search filter fields for SharedShelf projects.
 *
 * @return array
 *   Contains values Creator, Title, Location, Date, Photographer, Work Type.
 */
function media_sharedshelf_search_filter_fields() {
  return array(
    'Creator',
    'Title',
    'Location',
    'Date',
    'Photographer',
    'Work Type');
}

/**
 * Wrapper for variable_get() using the Media: SharedShelf variable registry.
 *
 * @param string $name
 *   The variable name to retrieve. Note that it will be namespaced by
 *   pre-pending MEDIA_SHAREDSHELF_NAMESPACE, as to avoid variable collisions
 *   with other modules.
 * @param mixed $default
 *   An optional default variable to return if the variable hasn't been set
 *   yet. Note that within this module, all variables should already be set
 *   in the media_sharedshelf_variable_default() function.
 *
 * @return mixed
 *   Returns the stored variable or its default.
 *
 * @see media_sharedshelf_variable_set()
 * @see media_sharedshelf_variable_del()
 * @see media_sharedshelf_variable_default()
 */
function media_sharedshelf_variable_get($name, $default = NULL) {
  // Allow for an override of the default.
  // Useful when a variable is required (like $path), but namespacing is still
  // desired.
  if (!isset($default)) {
    $default = media_sharedshelf_variable_default($name);
  }
  // Namespace all variables.
  $variable_name = MEDIA_SHAREDSHELF_NAMESPACE . $name;
  return variable_get($variable_name, $default);
}

/**
 * Wrapper for variable_set() using the Media: SharedShelf variable registry.
 *
 * @param string $name
 *   The variable name to set. Note that it will be namespaced by
 *   pre-pending MEDIA_SHAREDSHELF_NAMESPACE, as to avoid variable collisions
 *   with other modules.
 * @param mixed $value
 *   The value for which to set the variable.
 *
 * @return mixed
 *   Returns the stored variable after setting.
 *
 * @see media_sharedshelf_variable_get()
 * @see media_sharedshelf_variable_del()
 * @see media_sharedshelf_variable_default()
 */
function media_sharedshelf_variable_set($name, $value) {
  $variable_name = MEDIA_SHAREDSHELF_NAMESPACE . $name;
  return variable_set($variable_name, $value);
}

/**
 * Wrapper for variable_del() using the Media: SharedShelf variable registry.
 *
 * @param string $name
 *   The variable name to delete. Note that it will be namespaced by
 *   pre-pending MEDIA_SHAREDSHELF_NAMESPACE, as to avoid variable collisions
 *   with other modules.
 *
 * @see media_sharedshelf_variable_get()
 * @see media_sharedshelf_variable_set()
 * @see media_sharedshelf_variable_default()
 */
function media_sharedshelf_variable_del($name) {
  $variable_name = MEDIA_SHAREDSHELF_NAMESPACE . $name;
  variable_del($variable_name);
}

/**
 * The default variables within the Media: SharedShelf namespace.
 *
 * @param string $name
 *   Optional variable name to retrieve the default. Note that it has not yet
 *   been pre-pended with MEDIA_SHAREDSHELF_NAMESPACE namespace at this time.
 *
 * @return mixed
 *   The default value of this variable, if it's been set, or NULL, unless
 *  $name is NULL, in which case we return an array of all default values.
 *
 * @see media_sharedshelf_variable_get()
 * @see media_sharedshelf_variable_set()
 * @see media_sharedshelf_variable_del()
 */
function media_sharedshelf_variable_default($name = NULL) {
  static $defaults;

  if (!isset($defaults)) {
    $defaults = array(
      'video_width' => 640,
      'video_height' => 390,
      'autoplay' => FALSE,
      'preview_uri' => '',
      'host_server' => MEDIA_SHAREDSHELF_API_URL_PRODUCTION,
      'login_email' => '',
      'login_password' => '',
      'search_images_per_page' => MEDIA_SHAREDSHELF_DEFAULT_SEARCH_IMAGES_PER_PAGE,
      'local_cache_image_size' => MEDIA_SHAREDSHELF_DEFAULT_LOCAL_CACHE_IMAGE_SIZE,
      'default_project' => MEDIA_SHAREDSHELF_DEFAULT_PROJECT,
    );
  }

  if (!isset($name)) {
    return $defaults;
  }

  if (isset($defaults[$name])) {
    return $defaults[$name];
  }
}

/**
 * Return the fully namespace variable name.
 *
 * @param string $name
 *   The variable name to retrieve the namespaced name.
 *
 * @return string
 *   The full variable name prepended with MEDIA_SHAREDSHELF_NAMESPACE.
 */
function media_sharedshelf_variable_name($name) {
  return MEDIA_SHAREDSHELF_NAMESPACE . $name;
}
