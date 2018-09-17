<?php
/**
 * @file
 * texts_security_settings_feature.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function texts_security_settings_feature_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'seckit_clickjacking';
  $strongarm->value = array(
    'x_frame' => '0',
    'x_frame_allow_from' => 'ALLOW-ALL',
    'js_css_noscript' => 0,
    'noscript_message' => 'Sorry, you need to enable JavaScript to visit this website.',
  );
  $export['seckit_clickjacking'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'seckit_csrf';
  $strongarm->value = array(
    'origin' => 0,
    'origin_whitelist' => '',
  );
  $export['seckit_csrf'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'seckit_ssl';
  $strongarm->value = array(
    'hsts' => 0,
    'hsts_max_age' => '1000',
    'hsts_subdomains' => 0,
  );
  $export['seckit_ssl'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'seckit_various';
  $strongarm->value = array(
    'from_origin' => 0,
    'from_origin_destination' => 'same',
  );
  $export['seckit_various'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'seckit_xss';
  $strongarm->value = array(
    'csp' => array(
      'checkbox' => 1,
      'report-only' => 0,
      'default-src' => '\'self\' \'unsafe-inline\' \'unsafe-eval\' ajax.googleapis.com cdn.ckeditor.com cdn.mathjax.org cdnjs.cloudflare.com fonts.googleapis.com fonts.gstatic.com maxcdn.bootstrapcdn.com ss558499-us-east-1-aws.measuredsearch.com themes.googleusercontent.com www.google-analytics.com',
      'script-src' => '',
      'object-src' => '',
      'style-src' => '',
      'img-src' => '',
      'media-src' => '',
      'frame-src' => '',
      'font-src' => '',
      'connect-src' => '',
      'report-uri' => 'admin/config/system/seckit/csp-report',
      'policy-uri' => '',
    ),
    'x_xss' => array(
      'select' => '0',
    ),
    'x_content_type' => array(
      'checkbox' => 0,
    ),
  );
  $export['seckit_xss'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplesamlphp_auth_allowdefaultlogin';
  $strongarm->value = 1;
  $export['simplesamlphp_auth_allowdefaultlogin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplesamlphp_auth_allowdefaultloginroles';
  $strongarm->value = array(
    3 => '3',
    6 => '6',
  );
  $export['simplesamlphp_auth_allowdefaultloginroles'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplesamlphp_auth_allowdefaultloginusers';
  $strongarm->value = '181,1';
  $export['simplesamlphp_auth_allowdefaultloginusers'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplesamlphp_auth_allowsetdrupalpwd';
  $strongarm->value = 0;
  $export['simplesamlphp_auth_allowsetdrupalpwd'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplesamlphp_auth_authsource';
  $strongarm->value = 'default-sp';
  $export['simplesamlphp_auth_authsource'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplesamlphp_auth_forcehttps';
  $strongarm->value = 1;
  $export['simplesamlphp_auth_forcehttps'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplesamlphp_auth_installdir';
  $strongarm->value = '../simplesamlphp';
  $export['simplesamlphp_auth_installdir'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplesamlphp_auth_logoutgotourl';
  $strongarm->value = '';
  $export['simplesamlphp_auth_logoutgotourl'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplesamlphp_auth_mailattr';
  $strongarm->value = 'urn:oid:0.9.2342.19200300.100.1.3';
  $export['simplesamlphp_auth_mailattr'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplesamlphp_auth_registerusers';
  $strongarm->value = 1;
  $export['simplesamlphp_auth_registerusers'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplesamlphp_auth_roleevaleverytime';
  $strongarm->value = 0;
  $export['simplesamlphp_auth_roleevaleverytime'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplesamlphp_auth_rolepopulation';
  $strongarm->value = '';
  $export['simplesamlphp_auth_rolepopulation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplesamlphp_auth_unique_id';
  $strongarm->value = 'urn:oid:0.9.2342.19200300.100.1.1';
  $export['simplesamlphp_auth_unique_id'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplesamlphp_auth_user_name';
  $strongarm->value = 'urn:oid:0.9.2342.19200300.100.1.1';
  $export['simplesamlphp_auth_user_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplesamlphp_auth_user_register_original';
  $strongarm->value = '0';
  $export['simplesamlphp_auth_user_register_original'] = $strongarm;

  return $export;
}
