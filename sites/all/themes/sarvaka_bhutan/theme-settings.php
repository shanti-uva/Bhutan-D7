<?php
/**
 * Implements HOOK_form_system_theme_settings_alter
 * Adds base color field to theme settings
 */
function sarvaka_bhutan_form_system_theme_settings_alter(&$form, $form_state) {
  global $base_path;
  $form['sarvaka_bhutan_flyout_open'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Search Flyout Open Pages'),
    '#default_value' => theme_get_setting('sarvaka_bhutan_flyout_open'),
    '#description'   => t("Enter one path per line for pages where the search flyout should load open"),
  );
} 
