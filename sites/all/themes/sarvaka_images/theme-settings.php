<?php
/**
 * Implements HOOK_form_system_theme_settings_alter
 */
function sarvaka_images_form_system_theme_settings_alter(&$form, $form_state) {
    $form['sarvaka_images'] = array(
        '#type' => 'fieldset',
        '#title' => t('Shanti Images Theme Settings'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );
    $form['sarvaka_images']['sarvaka_images_replace_broken_images'] = array(
        '#type'          => 'checkbox',
        '#title'         => t('Replace Broken Images'),
        '#default_value' => theme_get_setting('sarvaka_images_replace_broken_images'),
        '#description'   => t("When checked will replace not-found images with a generic image tiles"),
    );
} 
