<?php

/**
 * @file
 * PHP content type.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Custom php'),
  'no title override' => TRUE,
  'defaults' => array('admin_title' => '', 'title' => '', 'body' => "<h4>Example PHP code</h4>\n<p>Time: <?php print date('H:i', time());?></p>\n"),
  'js' => array('misc/autocomplete.js', 'misc/textarea.js', 'misc/collapse.js'),
  // Make sure the edit form is only used for some subtypes.
  'edit form' => '',
  'add form' => '',
  'edit text' => t('Edit'),
  'all contexts' => TRUE,
  'icon' => 'icon_php.png',
);

/**
 * Return the php content types with the specified $subtype_id.
 */
function panels_php_php_content_type_content_type($subtype_id) {
  if ($subtype_id == 'php') {
    return _panels_php_default_content_type_content_type();
  }
  elseif (module_exists('ctools_custom_content')) {
    ctools_include('export');
    $content = ctools_export_crud_load('ctools_custom_content', $subtype_id);
    if ($content) {
      return _panels_php_php_content_type_content_type($content);
    }
  }
}

/**
 * Return all php content types available.
 */
function panels_php_php_content_type_content_types() {
  ctools_include('export');
  $types = array();
  $types['php'] = _panels_php_default_content_type_content_type();

  if (module_exists('ctools_custom_content')) {
    foreach (ctools_export_crud_load_all('ctools_custom_content') as $name => $content) {
      $types[$name] = _panels_php_php_content_type_content_type($content);
    }
  }

  return $types;
}

/**
 * Settings for the default php content type.
 *
 * The default is the one that allows the user to actually create a type.
 */
function _panels_php_default_content_type_content_type() {
  $info = array(
    'name' => 'php',
    'title' => t('New custom php'),
    'top level' => TRUE,
    'category' => t('Custom'),
    'description' => t('Create a completely custom piece of PHP content.'),
    'edit form' => 'panels_php_php_content_type_edit_form',
    'all contexts' => TRUE,
    'check editable' => 'panels_php_php_content_type_editable',
  );

  return $info;
}

/**
 * Return an info array for a specific php content type.
 */
function _panels_php_php_content_type_content_type($content) {
  $info = array(
    'name' => $content->name,
    'title' => check_plain($content->admin_title),
    'description' => check_plain($content->admin_description),
    'category' => $content->category ? check_plain($content->category) : t('Miscellaneous'),
    'all contexts' => TRUE,
    'icon' => 'icon_php.png',
    // Store this here to make it easy to access.
    'content' => $content,
  );

  return $info;
}

/**
 * Given a subtype and a $conf, return the actual settings to use.
 *
 * The actual settings may be stored directly in the pane or this may
 * be a pointer to re-usable content that may be in the database or in
 * an export. We have to determine from the subtype whether or not it
 * is local or shared custom content.
 */
function panels_php_php_content_type_get_conf($subtype, $conf) {
  if ($subtype['name'] != 'php') {
    $settings = $subtype['content']->settings;
    $settings['custom_type'] = 'fixed';
    $settings['content'] = $subtype['content'];
  }
  else {
    // This means they created it as php content and then set it as
    // reusable. Since we're not allowed to change the subtype, we're
    // still stored as though we are local, but are pointing off to
    // non-local.
    if (!empty($conf['name']) && module_exists('ctools_custom_content')) {
      ctools_include('export');
      $content = ctools_export_crud_load('ctools_custom_content', $conf['name']);
      if ($content) {
        $settings = $content->settings;
        $settings['custom_type'] = 'fixed';
        $settings['content'] = $content;
        $settings['admin_title'] = $content->admin_title;
      }
      else {
        $content = ctools_export_crud_new('ctools_custom_content');
        $content->name = $conf['name'];
        $settings = array(
          'admin_title' => t('Missing/deleted content'),
          'title' => '',
          'body' => '',
          'custom_type' => 'fixed',
          'content' => $content,
        );
      }
    }
    // This means that it is created as php and has not been set to
    // reusable.
    else {
      $settings = $conf;
      $settings['custom_type'] = 'local';
    }
  }

  return $settings;
}

function panels_php_php_content_type_editable($content_type, $subtype, $conf) {
  if ($subtype['name'] == 'php' && !empty($conf['name'])) {
    return FALSE;
  }

  return TRUE;
}

/**
 * Output function for the 'php' content type. Outputs a custom
 * based on the module and delta supplied in the configuration.
 */
function panels_php_php_content_type_render($subtype, $conf, $args, $contexts) {
  $settings = panels_php_php_content_type_get_conf(panels_php_php_content_type_content_type($subtype), $conf);

  static $delta = 0;

  $block          = new stdClass();
  $block->subtype = ++$delta;
  $block->title   = filter_xss_admin($settings['title']);

  $content = $settings['body'];
  $available_variables = array();
  foreach ($contexts as $context) {
    $available_variables[$context->keyword] = $context->data;
  }
  $block->content = _panels_php_php_eval($content, $available_variables);
  
  if ($settings['custom_type'] == 'fixed' && user_access('administer custom content')) {
    $block->admin_links = array(
      array(
        'title' => t('Configure content pane'),
        'alt' => t("Configure this pane in administer >> structure >> custom content panes"),
        'href' => 'admin/structure/ctools-content/list/' . $settings['content']->name . '/edit',
        'query' => drupal_get_destination(),
      ),
    );
  }

  return $block;
}

/**
 * Callback to provide the administrative title of the php content.
 */
function panels_php_php_content_type_admin_title($subtype, $conf) {
  $settings = panels_php_php_content_type_get_conf(panels_php_php_content_type_content_type($subtype), $conf);

  $output = t('Custom');
  $title = !empty($settings['admin_title']) ? $settings['admin_title'] : $settings['title'];
  if ($title) {
    if ($settings['custom_type'] != 'fixed') {
      $output = t('PHP: @title', array('@title' => $title));
    }
    else {
      $output = $title;
    }
  }

  return $output;
}

/**
 * Callback to provide administrative info. In this case we'll render the
 * content as long as it's not PHP, which is too risky to render here.
 */
function panels_php_php_content_type_admin_info($subtype, $conf) {
  $settings = panels_php_php_content_type_get_conf(panels_php_php_content_type_content_type($subtype), $conf);

  $block = new stdClass();
  $block->title = filter_xss_admin($settings['title']);
  
  // We don't want to render php output on preview here, because if something is
  // wrong the whole display will be borked. So we check to see if the php
  // evaluator filter is being used, and make a temporary change to the filter
  // so that we get the printed php, not the eval'ed php.
  $block->content = '<pre>' . check_plain($settings['body']) . '</pre>';
  
  return $block;
}

/**
 * Returns an edit form for the php type.
 */
function panels_php_php_content_type_edit_form($form, &$form_state) {
  $contexts = $form_state['contexts'];
  $settings = panels_php_php_content_type_get_conf($form_state['subtype'], $form_state['conf']);
  $form_state['settings'] = $settings;

  if ($settings['custom_type'] == 'fixed') {
    return $form; // no form for this case.
  }

  $form['admin_title'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($settings['admin_title']) ? $settings['admin_title'] : '',
    '#title' => t('Administrative title'),
    '#description' => t('This title will be used administratively to identify this pane. If blank, the regular title will be used.'),
  );

  $form['title'] = array(
    '#type' => 'textfield',
    '#default_value' => $settings['title'],
    '#title' => t('Title'),
  );

  $form['body'] = array(
    '#type' => 'textarea',
    '#title' => t('Body'),
    '#default_value' => $settings['body'],
    '#required' => TRUE,
    '#disabled' => user_access('use PHP for settings') ? FALSE : TRUE,
    '#description' => 'Users only with "Use PHP for settings" permission can edit this.',
  );

  if (!empty($form_state['contexts'])) {
    $form['contexts'] = array(
      '#title' => t('Available variables'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $items = array();
    foreach ($contexts as $context) {
      if ($context->type == 'string') {
        $items[] = array(
          'data' => '<a href="javascript:void(0);">$' . $context->keyword . '</a>: The ' . $context->type . ' variable for "' . $context->identifier . '".',
        );
      }
      else {
        $items[] = array(
          'data' => '<a href="javascript:void(0);">$' . $context->keyword . '</a>: The ' . $context->type[2] . ' object for "' . $context->identifier . '".',
        );
      }
      
    }
    $form['contexts']['context'] = array('#markup' => theme('item_list', array('items' => $items)));
  }

  if (!user_access('administer custom content') || !module_exists('ctools_custom_content')) {
    return $form;
  }

  // Make the other form items dependent upon it.
  ctools_include('dependent');
  ctools_add_js('dependent');

  $form['reusable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make this content reusable'),
    '#default_value' => FALSE,
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Machine name'),
    '#description' => t('The machine readable name of this content. It must be unique, and it must contain only alphanumeric characters and underscores. Once created, you will not be able to change this value!'),
    '#dependency' => array('edit-reusable' => array(1)),
  );

  $form['category'] = array(
    '#type' => 'textfield',
    '#title' => t('Category'),
    '#description' => t('What category this content should appear in. If left blank the category will be "Miscellaneous".'),
    '#dependency' => array('edit-reusable' => array(1)),
  );

  $form['admin_description'] = array(
    '#type' => 'textarea',
    '#title' => t('Administrative description'),
    '#description' => t('A description of what this content is, does or is for, for administrative use.'),
    '#dependency' => array('edit-reusable' => array(1)),
  );
  return $form;
}

function _panels_php_php_content_type_edit_save(&$content, $form_state) {
  // Apply updates to the content object.
  $content->category = $form_state['values']['category'];
  $content->admin_title = $form_state['values']['admin_title'];
  $content->admin_description = $form_state['values']['admin_description'];
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $content->settings[$key] = $form_state['values'][$key];
    }
  }

  ctools_export_crud_save('ctools_custom_content', $content);
}

/**
 * The validate form to ensure the php content data is okay.
 */
function panels_php_php_content_type_edit_form_validate(&$form, &$form_state) {
  if ($form_state['settings']['custom_type'] != 'fixed' && !empty($form_state['values']['reusable'])) {
    if (empty($form_state['values']['name'])) {
      form_error($form['name'], t('Name is required.'));
    }

    // Check for string identifier sanity
    if (!preg_match('!^[a-z0-9_]+$!', $form_state['values']['name'])) {
      form_error($form['name'], t('The name can only consist of lowercase letters, underscores, and numbers.'));
      return;
    }

    if (!module_exists('ctools_custom_content')) {
      return;
    }

    // Check for name collision
    if ($form_state['values']['name'] == 'php' || (ctools_export_crud_load('ctools_custom_content', $form_state['values']['name']))) {
      form_error($form['name'], t('Content with this name already exists. Please choose another name or delete the existing item before creating a new one.'));
    }
  }
}

/**
 * The submit form stores the data in $conf.
 */
function panels_php_php_content_type_edit_form_submit($form, &$form_state) {
  if ($form_state['settings']['custom_type'] == 'fixed') {
    _panels_php_php_content_type_edit_save($form_state['settings']['content'], $form_state);
  }
  // If the 'reusable' checkbox was checked, we will create a new
  // custom content and give it the proper values.
  else if (!empty($form_state['values']['reusable'])) {
    $content = ctools_export_crud_new('ctools_custom_content');
    $content->name = $form_state['values']['name'];
    _panels_php_php_content_type_edit_save($content, $form_state);
    $form_state['conf']['name'] = $content->name;
  }
  else {
    // Otherwise, just save values into $conf normally.

    foreach (array_keys($form_state['plugin']['defaults']) as $key) {
      $form_state['conf'][$key] = isset($form_state['values'][$key]) ? $form_state['values'][$key] : $form_state['plugin']['defaults'][$key];
    }
  }
}

/**
 * Helper function.
 * @see php_eval($code)
 */
function _panels_php_php_eval($code, $paras = array()) {
  global $theme_path, $theme_info, $conf;
  
  foreach ($paras as $key => $value) {
    ${$key} = $value;
  }

  // Store current theme path.
  $old_theme_path = $theme_path;

  // Restore theme_path to the theme, as long as php_eval() executes,
  // so code evaluated will not see the caller module as the current theme.
  // If theme info is not initialized get the path from theme_default.
  if (!isset($theme_info)) {
    $theme_path = drupal_get_path('theme', $conf['theme_default']);
  }
  else {
    $theme_path = dirname($theme_info->filename);
  }

  ob_start();
  print eval('?>' . $code);
  $output = ob_get_contents();
  ob_end_clean();

  // Recover original theme path.
  $theme_path = $old_theme_path;

  return $output;
}
