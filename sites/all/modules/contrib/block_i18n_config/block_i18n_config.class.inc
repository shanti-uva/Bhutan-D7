<?php


class block_i18n_config_object extends i18n_block_object {

  /**
   * Get object strings for translation
   */
  protected function build_properties() {

    $info = block_i18n_config_info();

    foreach ($info as $property_name => $data) {

      if ($this->inBlocks($data['blocks'])) {
        $property = $data['property getter']($property_name, $this->object->delta);

        if (is_array($property)) {
          $this->object->$property_name = $property['value'];
          if (!empty($data['info']['format'])) {
            $this->object->$data['info']['format'] = $property['format'];
          }
        }
        else {
          $this->object->$property_name = $property;
        }
      }
    }

    $properties = parent::build_properties();

    foreach ($info as $property_name => $data) {
      if (!$this->inBlocks($data['blocks'])) {
        unset($properties[$this->get_textgroup()][$this->object->module][$this->object->delta][$property_name]);
      }
    }

    return $properties;
  }

  private function inBlocks($blocks) {
    return in_array($this->object->delta, $blocks, TRUE);
  }
}
