<?php
/**
 * @file
 * Define MediaSharedShelfSearchFilter class which is used to create a filter
 * option when retrieving assets from SharedShelf via the API, if needed.
 * Switched to using the function _media_sharedshelf_create_search_filter
 * in version 7.x-2.x so this is deprecated.
 */

/**
 * Media SharedShelf search filter object.
 */
class MediaSharedShelfSearchFilter {
  public $type;
  public $field;
  public $comparison;
  public $value;

  // SharedShelf values allowed for use in a filter construction.
  protected $typeValues = array(
    'string',
    'numeric',
    'date',
    'thumbnail',
    'profile',
  );
  protected $comparisonValues = array('eq', 'lt', 'gt');

  /**
   * Constructor for an instance.
   *
   * @param string $field
   *   The name of the field.
   * @param string $value
   *   The value for the field.
   * @param string $comparison
   *   A comparison operator.
   * @param string $type
   *   The type of the field.
   */
  public function __construct($field, $value, $comparison = 'eq', $type = 'string') {
    // Make sure only a valid type value is set.
    if (in_array($type, $this->typeValues)) {
      $this->type = $type;
    }
    else {
      // Default to string if an invalid value is passed.
      $this->type = $this->typeValues[0];
    }
    $this->field = $field;
    // Make sure only a valid comparison value is set.
    if (in_array($comparison, $this->comparisonValues)) {
      $this->comparison = $comparison;
    }
    else {
      // Default to eq if an invalid value is passed.
      $this->comparison = $this->comparisonValues[0];
    }
    // Make sure the value is converted to a string for numbers because the
    // SharedShelf filter will fail otherwise.
    $this->value = strval($value);
  }

  /**
   * String representation of the object.
   *
   * @return string
   *   JSON encoded string representation of the object.
   */
  public function __toString() {
    return json_encode($this);
  }

  /**
   * Checks to make sure that an object is valid.
   *
   * @return bool
   *   Returns TRUE if object is valid.
   */
  public function exists() {
    if (($this->field == '') or ($this->value == '')) {
      return FALSE;
    }
    return TRUE;
  }
}
