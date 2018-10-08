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

        $options['data_type_info']['id'] = array('default' => '');
        $options['data_type_info']['title'] = array('default' => '');
        $options['data_type_info']['thumbnail_image'] = array('default' => '');
        $options['data_type_info']['thumbnail_width'] = array('default' => '');
        $options['data_type_info']['thumbnail_height'] = array('default' => '');
        $options['data_type_info']['img_by_size_url'] = array('default' => '');
        $options['data_type_info']['ppd_info'] = array('default' => 'url');
        $options['data_type_info']['ppd_info_url'] = array('default' => '');
        $options['data_type_info']['ppd_info_func'] = array('default' => '');
        $options['data_type_info']['ppd_info_cache'] = array('default' => '');
        $options['data_type_info']['item_url'] = array('default' => '');

        /*$options['data_type_info']['title'] = array('default' => '');
        $options['data_type_info']['type'] = array('default' => '');
        $options['data_type_info']['creator'] = array('default' => '');
        $options['data_type_info']['collection'] = array('default' => '');
        $options['data_type_info']['description'] = array('default' => '');
        */
        return $options; 
    }
 
  /**
   * Create forms to hold these values allowing the user to change the values
   */
  function options_form(&$form, &$form_state) {
    $view = $this->view;
    $type = $view->base_table;
    $view->execute(); // need to execute the view to get list of fields ???? TODO: Check this
    $options = array(0 => "-- None --");
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
        '#description' => t('Check this box if this site is an images site that uses a IIIF server to display the images of the grid'),
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
    // File types can be file_managed or file_unmanaged
    $entity_type = _shanti_grid_view_get_item_type($type);
    $form['entity_type'] = array(
         '#type' => 'select',
          '#title' => t('Type of Entity Listed in View'),
          '#description' => t('Entity type being shown in this view: File, Node, or Data (detected automatically)'),
          '#default_value' => $entity_type,   
          '#options' => drupal_map_assoc(array('file', 'node', 'data')),
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

    // Data Source Type
    $form['data_type_info'] = array(
      '#type' => 'fieldset',
      '#title' => t('Data Source Selectors'),
      '#description' => t('Select the fields to be used for information for a custom data source:'),
      '#states' => array(
        'visible' => array(
          'input[name="style_options[iiif_view]"]' => array('checked' => FALSE),
          'select[name="style_options[entity_type]"]' => array('value' => 'data'),
        ),
      ),
    );

    $form['data_type_info']['id'] = array(
      '#type' => 'select',
      '#title' => t('Item ID'),
      '#description' => t('Select the field to use as for the ID of the item'),
      '#default_value' => $this->options['data_type_info']['id'],
      '#options' => $options,
      '#states' => array(
        'visible' => array(
          'input[name="style_options[iiif_view]"]' => array('checked' => FALSE),
        ),
      ),
    );

    $form['data_type_info']['filename'] = array(
      '#type' => 'select',
      '#title' => t('IIIF Filename'),
      '#description' => t('Select the field the IIIF file name if this view is of IIIF images'),
      '#default_value' => $this->options['data_type_info']['filename'],
      '#options' => $options,
      '#states' => array(
        'visible' => array(
          'input[name="style_options[iiif_view]"]' => array('checked' => FALSE),
        ),
      ),
    );

    $form['data_type_info']['title'] = array(
      '#type' => 'select',
      '#title' => t('Item Title'),
      '#description' => t('Select the field to use as for the title of the item'),
      '#default_value' => $this->options['data_type_info']['title'],
      '#options' => $options,
      '#states' => array(
        'visible' => array(
          'input[name="style_options[iiif_view]"]' => array('checked' => FALSE),
        ),
      ),
    );

    $form['data_type_info']['thumbnail_image'] = array(
      '#type' => 'select',
      '#title' => t('Thumbnail Image'),
      '#description' => t('Select the image field to use as the thumbnail in the grid'),
      '#default_value' => $this->options['data_type_info']['thumbnail_image'],
      '#options' => $options,
      '#states' => array(
        'visible' => array(
          'input[name="style_options[iiif_view]"]' => array('checked' => FALSE),
        ),
      ),
    );


    $form['data_type_info']['thumbnail_width'] = array(
      '#type' => 'select',
      '#title' => t('Thumbnail Width'),
      '#description' => t('Select the image field to use as the thumbnail width'),
      '#default_value' => $this->options['data_type_info']['thumbnail_width'],
      '#options' => $options,
      '#states' => array(
        'visible' => array(
          'input[name="style_options[iiif_view]"]' => array('checked' => FALSE),
        ),
      ),
    );


    $form['data_type_info']['thumbnail_height'] = array(
      '#type' => 'select',
      '#title' => t('Thumbnail Height'),
      '#description' => t('Select the image field to use as the thumbnail in the grid'),
      '#default_value' => $this->options['data_type_info']['thumbnail_height'],
      '#options' => $options,
      '#states' => array(
        'visible' => array(
          'input[name="style_options[iiif_view]"]' => array('checked' => FALSE),
        ),
      ),
    );

    $form['data_type_info']['img_by_size_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Image URL Syntax'),
      '#description' => t('Enter the syntax for the image by size url. Use __ID__ for resource id and __SIZE__ for the size parameter.'),
      '#default_value' => $this->options['data_type_info']['img_by_size_url'],
      '#size' => 100,
    );

    $form['data_type_info']['ppd_info'] = array(
      '#type' => 'select',
      '#title' => t('Item Info Source'),
      '#description' => t('Choose the method for retrieving information about a single item:'),
      '#default_value' => $this->options['data_type_info']['ppd_info'],
      '#options' => array(
          'url' => t("By URL Syntax"),
          'function' => t("By Implementing a Function"),
          'view' => t("By Cached View Results"),
      ),
    );

      $form['data_type_info']['ppd_info_url'] = array(
          '#type' => 'textfield',
          '#title' => t('Item Info URL Syntax'),
          '#description' => t('Enter the URL to retrieve the details about an item. Use __ID__ for item’s id. <br/>
                                This URL must return an HTML div with the information marked up.'),
          '#default_value' => $this->options['data_type_info']['ppd_info_url'],
          '#size' => 100,
          '#states' => array(
              'visible' => array(
                  'select[name="style_options[data_type_info][ppd_info]"]' => array('value' => 'url'),
              ),
          ),
          '#prefix' =>'<div style="margin-left: 24px">',
          '#suffix' => '</div>',
      );

      $form['data_type_info']['ppd_info_func'] = array(
          '#type' => 'textfield',
          '#title' => t('Item Info Function'),
          '#description' => t('Enter the name of the function used to retrieve details about an item. Leave blank for default function name. 
                               The items ID will be passed as the first parameter. This URL must return an HTML div with the information marked up.'),
          '#default_value' => (!empty($this->options['data_type_info']['ppd_info_func'])) ? $this->options['data_type_info']['ppd_info_func'] :
                    $view->name . '_' .$view->current_display . '_item_info',
          '#size' => 100,
          '#states' => array(
              'visible' => array(
                  'select[name="style_options[data_type_info][ppd_info]"]' => array('value' => 'function'),
              ),
          ),
          '#prefix' =>'<div style="margin-left: 24px">',
          '#suffix' => '</div>',
      );

      $form['data_type_info']['ppd_info_cache'] = array(
          '#type' => 'textarea',
          '#title' =>  t('Map of Fields'),
          '#description' => t('Map field names in view to placeholder strings in template, one per line, in the format {field name}|{placeholder string}. Strings are:  
                                GVID, GVTITLE, GVAUTH, GVSUBTYPE, GVWIDTH, GVHEIGHT, GVDATE, GVCOLLECTION, GVPLACES, GVSUBJECTS, GVDESC 
                                (Any undefined placeholder strings will be replaced with an empty string.)'),
          '#default_value' => $this->options['data_type_info']['ppd_info_cache'],
          '#states' => array(
              'visible' => array(
                  'select[name="style_options[data_type_info][ppd_info]"]' => array('value' => 'view'),
              ),
          ),
          '#row' => 20,
          '#prefix' =>'<div style="margin-left: 24px">',
          '#suffix' => '</div>',
      );

    $form['data_type_info']['item_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Resource Page URL Syntax'),
      '#description' => t('Enter the syntax for url to show a resource item by id. Use __ID__ for resource id. Or enter the name of the view field. If __ID__ is not present, will assume it is name of field.'),
      '#default_value' => $this->options['data_type_info']['item_url'],
      '#size' => 100,
    );
  }

  /**
   * Handle the submitted options form
   *
   * @param $form
   * @param $form_state
  public function options_submit(&$form, &$form_state) {

  }
   */
}
