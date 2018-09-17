<?php

/**
 * Shanti views plugin to display images in a google-like grid view
 *
 * @ingroup views_style_plugins
 */
class shanti_grid_view_plugin_style extends views_plugin_style {
    
  /**
   * Set default options
   */
    //function options(&$options) {
     function option_definition() {
        $options = parent::option_definition();
        $options['view_subtitle'] = array('default' => '');
        $options['iiif_view'] = array('default' => FALSE);
        $options['iiif_options']['iiif_url_syntax'] = array('default' => '');
        $options['iiif_options']['iiif_tiny_size'] = array('default' => '');
        $options['iiif_options']['iiif_thumb_size'] = array('default' => '');
        $options['iiif_options']['iiif_pd_size'] = array('default' => '');
        $options['iiif_options']['iiif_full_size'] = array('default' => '');
        $options['iiif_options']['iiif_img_field'] = array('default' => '');
        $options['entity_type'] = array('default' => 'file');
        $options['node_type_info']['thumbnail_image'] = array('default' => '');
        $options['node_type_info']['large_image'] = array('default' => '');
        $options['node_type_info']['xlarge_image'] = array('default' => '');
        return $options; 
    }
 
  /**
   * Create forms to hold these values allowing the user to change the values
   */
  function options_form(&$form, &$form_state) {
    $view = $this->view;
    $type = $view->base_table;
    $view->execute(); // need to execute the view to get list of fields ???? TODO: Check this
    $options = array();
    foreach ($view->field as $fid => $field) {
        $options[$fid] = (!empty($field->options['label'] )) ? "$fid ({$field->options['label']})" : $fid;
    }
    $form['view_subtitle'] = array(
         '#type' => 'textfield',
          '#title' => t('Subtitle to appear above view results'),
          '#description' => t('A subtitle to appear above the view results'),
          '#default_value' => '',   
    );
    // Whether view is IIIF (Hides all other options)
    $form['iiif_view'] = array(
        '#type' => 'checkbox',
        '#title' => t('IIIF View'),
        '#description' => t('Check this box if you are using a IIIF server to display the images of the grid'),
        '#default_value' => $this->options['iiif_view'],
    );
    // IIIF Options
    $form['iiif_options'] = array(
        '#type' => 'fieldset',
        '#title' => t('IIIF Options'),
        '#states' => array(
            'visible' => array(
                'input[name="style_options[iiif_view]"]' => array('checked' => TRUE),
            ),
        ),
    );
    $form['iiif_options']['iiif_url_syntax'] = array(
        '#type' => 'textfield',
        '#title' => t('IIIF URL Syntax'),
        '#description' => t('Enter the syntax of the <em>relative</em> URL with __FNAME__ for the file name and __SIZE__ ' .
            'for the Popdown Image Size replacements. <strong>Note: </strong> The host name is for the ' .
            'IIIF server is set as IIIF View URL in <a href="/admin/config/media/shanti_images">Shanti Images settings</a>.'),
        '#default_value' => (!empty($this->options['iiif_options']['iiif_url_syntax'])) ? $this->options['iiif_options']['iiif_url_syntax'] : 'https://iiif-test.lib.virginia.edu/mandala/__FNAME__/full/__SIZE__/0/default.jpg',
        '#size' => 100,
    );
    $form['iiif_options']['iiif_img_field'] = array(
        '#type' => 'select',
        '#title' => t('Field to use for Image'),
        '#description' => t('Choose the field that in the view that is the image field'),
        '#default_value' => $this->options['iiif_options']['iiif_img_field'],
        '#options' => $options,
    );
    $form['iiif_options']['iiif_tiny_size'] = array(
        '#type' => 'textfield',
        '#title' => t('Tiny Image Size'),
        '#description' => t('Enter the size for the placeholder tiny image for progressive loading'),
        '#default_value' => $this->options['iiif_options']['iiif_tiny_size'],
        '#size' => 5,
    );
    $form['iiif_options']['iiif_thumb_size'] = array(
        '#type' => 'textfield',
        '#title' => t('Thumbnail Image Size'),
        '#description' => t('Enter the size for the thumbnails in the grid'),
        '#default_value' => $this->options['iiif_options']['iiif_thumb_size'],
        '#size' => 5,
    );
    $form['iiif_options']['iiif_pd_size'] = array(
        '#type' => 'textfield',
        '#title' => t('Popdown Image Size'),
        '#description' => t('Enter the size for the image in the popdown'),
        '#default_value' => $this->options['iiif_options']['iiif_pd_size'],
        '#size' => 5,
    );
    $form['iiif_options']['iiif_full_size'] = array(
        '#type' => 'textfield',
        '#title' => t('Full Image Size'),
        '#description' => t('Enter the full image size for the light box'),
        '#default_value' => $this->options['iiif_options']['iiif_full_size'],
        '#size' => 5,
    );
    
    // Non IIIF Options
    $entity_type = ($type == 'file_managed') ? 'file' : 'node';
    $form['entity_type'] = array(
         '#type' => 'select',
          '#title' => t('Type of Entity Listed in View'),
          '#description' => t('Entity type being shown in this view: File or Node'),
          '#default_value' => $entity_type,   
          '#options' => drupal_map_assoc(array('file', 'node')),
          '#disabled' => TRUE, 
          '#states' => array(
              'visible' => array(
                'input[name="style_options[iiif_view]"]' => array('checked' => FALSE),
               ),
            ),
    );
    $form['file_type_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('File Image Selectors'),
        '#description' => t('Galleries showing image files use the image styles applied to the file itself.'),
        '#states' => array(
              'visible' => array(
                'input[name="style_options[iiif_view]"]' => array('checked' => FALSE),
                'select[name="style_options[entity_type]"]' => array('value' => 'file'),
              ),
        ),
    );
    $form['node_type_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('Node Image Selectors'),
        '#description' => t('Select the fields to be used for the teaser thumbnails and the full version from the drop down lists below:'),
         '#states' => array(
              'visible' => array(
                'input[name="style_options[iiif_view]"]' => array('checked' => FALSE),
                'select[name="style_options[entity_type]"]' => array('value' => 'node'),
              ),
        ),
    );
    $form['node_type_info']['thumbnail_image'] = array(
      '#type' => 'select',
      '#title' => t('Thumbnail Image'),
      '#description' => t('Select the image field to use as the thumbnail in the grid'),
      '#default_value' => $this->options['node_type_info']['thumbnail_image'],   
      '#options' => $options,
       '#states' => array(
              'visible' => array(
                'input[name="style_options[iiif_view]"]' => array('checked' => FALSE),
              ),
        ),
    );
    $form['node_type_info']['large_image'] = array(
      '#type' => 'select',
      '#title' => t('Large Image'),
      '#description' => t('Select the image field to use for the large version of the image used in the drop down under an image'),
      '#default_value' => $this->options['node_type_info']['large_image'],   
      '#options' => $options,
       '#states' => array(
              'visible' => array(
                'input[name="style_options[iiif_view]"]' => array('checked' => FALSE),
              ),
        ),
    );
    
    $form['node_type_info']['xlarge_image'] = array(
      '#type' => 'select',
      '#title' => t('Extra Large Image'),
      '#description' => t('Select the image field to use for the extra large version of the image used for the lightbox full image'),
      '#default_value' => $this->options['node_type_info']['xlarge_image'],   
      '#options' => $options,
       '#states' => array(
              'visible' => array(
                'input[name="style_options[iiif_view]"]' => array('checked' => FALSE),
              ),
        ),
    );
  } 
}
