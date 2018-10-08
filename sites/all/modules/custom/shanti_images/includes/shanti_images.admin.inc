<?php

/**
 * Page callback: Shanti Images settings
 *
 */
function shanti_images_admin_form($form, &$form_state) {
    $form['shanti_images_upload_url'] = array(
        '#type' => 'textfield',
        '#title' => t('IIIF Upload URL'),
        '#default_value' => variable_get('shanti_images_upload_url', ''),
        '#description' => t('The URL for posting images to the IIIF Server. Must include protocol. Image files are POSTed to this URL via CURL.'),
        '#size' => 80,
        '#required' => TRUE,
    );
    $form['shanti_images_delete_url'] = array(
        '#type' => 'textfield',
        '#title' => t('IIIF Delete URL'),
        '#default_value' => variable_get('shanti_images_delete_url', ''),
        '#description' => t('The URL for deleting images from the IIIF Server. Must include protocol. Use "__FILE__" to indicate where the file name is in the URL. This is a GET call to delete the image.'),
        '#size' => 80,
        '#required' => TRUE,
    );
    $form['shanti_images_view_url'] = array(
        '#type' => 'textfield',
        '#title' => t('IIIF View URL'),
        '#default_value' => variable_get('shanti_images_view_url', ''),
        '#description' => t('The base URL for viewing images on the IIIF Server include protocol.'),
        '#size' => 80,
        '#required' => TRUE,
    );
    $form['shanti_images_view_path'] = array(
        '#type' => 'textfield',
        '#title' => t('IIIF View Path'),
        '#default_value' => variable_get('shanti_images_view_path', ''),
        '#description' => t('The relative path on the IIIF server to view an uploaded image'),
        '#size' => 80,
        '#required' => FALSE,
    );
    $form['shanti_images_extensions'] = array(
        '#type' => 'textfield',
        '#title' => t('Valid Image Extensions'),
        '#default_value' => variable_get('shanti_images_extensions', 'jpg jpeg jp2 png tif tiff'),
        '#description' => t('Enter all the valid image format extensions separated by spaces or commas'),
        '#size' => 80,
        '#required' => FALSE,
    );

    return system_settings_form($form);
}

function shanti_images_admin_form_validate($form, &$form_state) {
    // Validate and normalize upload url
    $up_url = $form_state['values']['shanti_images_upload_url'];
    if (!preg_match('/^https?\:\/\//', $up_url)){
        form_set_error('shanti_images_upload_url', t('The upload url must begin with a protocol (http:// or https://)'));
    }
    $form_state['values']['shanti_images_upload_url'] = rtrim($up_url, '/');

    // Validate and normalize upload url
    $del_url = $form_state['values']['shanti_images_delete_url'];
    if (!preg_match('/^https?\:\/\//', $del_url)){
        form_set_error('shanti_images_delete_url', t('The delete url must begin with a protocol (http:// or https://)'));
    }
    if (!strstr($del_url, '__FILE__')) {
        form_set_error('shanti_images_delete_url', t('The delete url must contain "__FILE__" to indicate where the file name belongs'));
    }
    $form_state['values']['shanti_images_delete_url'] = rtrim($del_url, '/');

    // Validate and normalize view url
    $view_url = $form_state['values']['shanti_images_view_url'];
    if (!preg_match('/^https?\:\/\//', $view_url)){
        form_set_error('shanti_images_view_url', t('The view url must begin with a protocol (http:// or https://)'));
    }
    $form_state['values']['shanti_images_view_url'] = rtrim($view_url, '/');

    // Normalize path
    $path = trim($form_state['values']['shanti_images_view_path'], '/');
    if ($path == '') {
        $form_state['values']['shanti_images_view_path'] = '/';
    } else {
        $form_state['values']['shanti_images_view_path'] = '/' . $path . '/';
    }

    // Deal with Extensions
    $exts = strtolower(trim($form_state['values']['shanti_images_extensions']));
    if (empty($exts)) {
      drupal_set_message(t("No extensions given. Setting to default: jpg jpeg jp2 png tif tiff"), 'warning');
      $exts = 'jpg jpeg jp2 png tif tiff';
    }
    $exts = str_replace('.', ' ', $exts);
    $exts = str_replace(',', ' ', $exts);
    $exts = preg_replace('/ {2,}/', ' ', $exts);
    $form_state['values']['shanti_images_extensions'] = $exts;
}

/**
 * Admin form for settings other than IIIF
 * @param $form
 * @param $form_state
 *
 * @return array
 */
function shanti_images_admin_form_other($form, &$form_state) {
    drupal_add_css(drupal_get_path('module', 'shanti_images') . '/css/shanti-images-admin.css');
    $cron_hr = _get_cron_hours();
    $form['shanti_images_cron'] = array(
        '#type' => 'checkbox',
        '#title' => t('Expunge Images'),
        '#default_value' => variable_get('shanti_images_cron', FALSE),
        '#description' => t('Remove image files from site through cron once they have been converted to IIIF. <br/>' .
            '<strong>Note:</strong> this only removes the original uploaded file but not the IIIF image created from it.'),
        '#required' => FALSE,
    );

    // Age images must be to expunge
    $form['shanti_images_cron_age'] = array(
        '#type' => 'textfield',
        '#title' => t('Expiration Age (hrs)'),
        '#prefix' => t('<div class="currcron">The current cron interval is @crh hrs.</div>', array(
                                '@crh' => $cron_hr,
                        )),
        '#default_value' => variable_get('shanti_images_cron_age', $cron_hr),
        '#description' => t('Enter the amount of time after which a file should be expunged. ' .
                            'Files are expunged during cron runs.' ),
        '#size' => 5,
        '#states' => array(
            // Hide the settings when the cancel notify checkbox is disabled.
            'invisible' => array(
                ':input[name="shanti_images_cron"]' => array('checked' => FALSE),
            ),
        ),
        '#required' => FALSE,
    );

    $form['shanti_images_cron_unit'] = array(
        '#type' => 'select',
        '#title' => '',
        '#options' => drupal_map_assoc(array('hour(s)', 'week(s)', 'month(s)', 'year(s)')),
        '#default_value' => variable_get('shanti_images_cron_unit', 'hours'),
        '#states' => array(
            // Hide the settings when the cancel notify checkbox is disabled.
            'invisible' => array(
                ':input[name="shanti_images_cron"]' => array('checked' => FALSE),
            ),
        ),
        '#required' => FALSE,
    );

    // Number of images to process each cron batch
    $form['shanti_images_cron_batch_size'] = array(
        '#type' => 'textfield',
        '#title' => t('Cron Batch Size'),
        '#default_value' => variable_get('shanti_images_cron_batch_size', FALSE),
        '#description' => t('Enter the number of Image files to remove from Drupal with each cron run.'),
        '#size' => 5,
        '#states' => array(
            // Hide the settings when the cancel notify checkbox is disabled.
            'invisible' => array(
                ':input[name="shanti_images_cron"]' => array('checked' => FALSE),
            ),
        ),
        '#required' => FALSE,
    );

    if ($cron_hr == 0) {
        $form['shanti_images_cron']['#prefix'] = '<p><b>Cron is disabled.</b></p>';
        $form['shanti_images_cron']['#disabled'] = TRUE;
        $form['shanti_images_cron_age']['#disabled'] = TRUE;
    }

    $form['shanti_images_debug'] = array(
        '#type' => 'checkbox',
        '#prefix' => t('<label for="edit-shanti-images-debug">Debugging </label>'),
        '#title' => t('IIIF Debugging'),
        '#default_value' => variable_get('shanti_images_debug', FALSE),
        '#description' => t('Check this bug to send messages to the Drupal log for debuging'),
        '#required' => FALSE,
    );
    return system_settings_form($form);
}

function _get_cron_hours() {
    $cron_sec = variable_get('cron_safe_threshold', 0);
    $cron_hours = floor($cron_sec / 3600);
    return $cron_hours;
}

function shanti_images_admin_form_other_validate($form, &$form_state) {
    // Validation for Cron Expunge settings.
    if($form_state['values']['shanti_images_cron']) {
        $time = $form_state['values']['shanti_images_cron_age'];
        if (is_numeric($time)) {
            $time = $time * 1;
            if (is_integer($time)) {
                $crhr = _get_cron_hours();
                if ($time < 1) {
                    form_set_error('shanti_images_cron_age', t('Age must be 1 or greater'));
                } else if ($time < $crhr) {
                    $msg = t('The age given at which files will be expunged is less than the current cron setting, ' .
                              'which is set for @crhr hours.', array('@crhr' => $crhr));
                    drupal_set_message($msg, 'warning');
                }
            } else {
                form_set_error('shanti_images_cron_age', t('Age in hours must be an integer'));
            }
        } else {
            form_set_error('shanti_images_cron_age', t('Age in hours must be an integer number'));
        }

        // Validataion for Batch Size
        $batchsize = $form_state['values']['shanti_images_cron_batch_size'];
        if (is_numeric($batchsize)) {
            $batchsize = $batchsize * 1;
            if ($batchsize > 0) {
                if (!is_int($batchsize)) {
                    form_set_error('shanti_images_cron_batch_size', t('The batch size must be an interger number!'));
                }
            } else {
                form_set_error('shanti_images_cron_batch_size', t('The batch size must be greater than zero!'));
            }
        } else {
            form_set_error('shanti_images_cron_batch_size', t('The batch size must be an interger greater than zero!'));
        }
    }
}


/**
 * Admin form for settings other than IIIF
 * @param $form
 * @param $form_state
 *
 * @return array
 */
/* The image name update is done. Saving in case another update is needed
function shanti_images_admin_update_form($form, &$form_state)
{
    $q = db_query('select i3fid from {shanti_images}');
    $i3fids = $q->fetchCol();
    $match = FALSE;
    foreach ($i3fids as $i3fid) {
        if (preg_match('/shanti-image-\d+-\d+/', $i3fid)) {
            $match = TRUE;
            break;
        }
    }
    if ($match) {
        $form['desc'] = array(
            '#markup' => "<p>The IIIF filenames for the Shanti Images need to be converted. Do you want to convert them?</p>",
        );

        $form['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Convert IIIF IDs'),
        );

    } else {
        $form['desc'] = array(
            '#markup' => "<p>All the IIIF filenames have been converted.</p>",
        );
    }
    $res = variable_get('shanti_images_admin_update_form_results', FALSE);
    if ($res) {
        $form['preresults'] = array(
            '#markup' => t("<p>The conversion was successfull! @count records updated.</p>",
                    array('@count' => count($res))),
        );
        $res = '<ul><li style="list-style-type: none;">' . implode('</li><li style="list-style-type: none;">', $res)
            . "</li></ul>";
        $form['results'] = array(
            '#markup' => $res,
        );
        variable_set('shanti_images_admin_update_form_results', FALSE);
    }

    return $form;
}

function shanti_images_admin_update_form_submit($form, &$form_state) {
    module_load_include('php', 'shanti_images', 'includes/shanti_image.class');
    $q = db_query('select siid from {shanti_images}');
    $sids = $q->fetchCol();
    $out = array();
    foreach ($sids as $sid) {
        $siobj = new ShantiImage($sid);
        $old_i3fid = $siobj->i3fid;
        $new_i3fid = 'shanti-image-' . $sid;
        if ($new_i3fid != $old_i3fid) {
            $out[] = "mv {$old_i3fid}.jp2 {$new_i3fid}.jp2";
            $data = array('i3fid' => $new_i3fid);
            $siobj->updateTable($data);
        }
    }
    variable_set('shanti_images_admin_update_form_results', $out);
}
*/

/**
 * Writes a list of files on IIIF server
 *
 * TODO: need to add pagination and filters
 * @return string
 * @throws Exception
 */
function shanti_images_admin_list() {
    // http://fuploadtest.lib.virginia.edu:8091/fupload/dirList
    $sortby = (isset($_GET['sortby'])) ? $_GET['sortby'] : FALSE;
    if (!$sortby && isset($_SESSION['iiif_list_sortby'])) {
        $sortby = $_SESSION['iiif_list_sortby'];
    } else if ($sortby) {
        $_SESSION['iiif_list_sortby'] = $sortby;
    }
    $header = array('<a href="?sortby=id">Image ID</a>', '<a href="?sortby=date">Date Uploaded</a>', '<a href="?sortby=size">Size</a>', '<a href="?sortby=node">Node</a>');
    $rows = array();
    drupal_set_title(t("Images on IIIF Server"));
    // Get ListURL which is the upload URL plus /dirList (for UVA IIIF servers)
    $listurl = variable_get('shanti_images_upload_url', FALSE);
    if ($listurl) {
        $json = file_get_contents($listurl . '/dirList');
        $jobj = json_decode($json, TRUE);
        if (isset($jobj['dirlisting'])) {
            $servlist = $jobj['dirlisting'];  // Get list of files on the IIIF server
            $count = count($servlist);
            $notfnd = 0;

            //Process JP2 file list into an array of arrays for display
            foreach ($servlist as $n => $item) {
                if (!empty($item['fileName']) && strstr($item['fileName'], '.jp2')) {
                    $fname = str_replace('.jp2', '', $item['fileName']);
                    $node = _shanti_images_get_node_by_filename($fname);
                    $link = ($node) ? l($node->title, 'node/' . $node->nid) : t('none') . ' <span style="float:right;"><a href="/image/iiif/remove/' . $fname . '">Delete</a></span>';
                    if (!$node) {
                        $notfnd++;
                    }
                    $rows[] = array($fname, $item['modDate'], $item['fileLen'], $link);
                }
            }

            // Check if sorting is chosen and sort appropriately
            _shanti_image_admin_list_sort($rows, $sortby); // Sort the rows

            // format filesize after sorting so easier to sort
            foreach ($rows as &$row) { $row[2] = shanti_image_format_bytes($row[2]); }

            // Create the output markup using theme('table')
            $out = '<p style="margin-top:0px;">' . t("This is a list of images that are on the IIIF server whether or not they have a corresponding node on the site. " .
                    "<br/>You can sort the table by clicking on a header. You can see the raw JSON from the request below.<br/>" .
                    "You can delete images that do not have corresponding nodes on the site. To delete images that <em>are</em> associated with a node, delete the node itself.<br/>" .
                    "However, <strong>be careful!</strong> Several environments share the same servers but may have different data, for instance Dev and Staging or sometimes Staging and Production.") . '</p>';
            $out .= '<p><span>&bull;</span>&nbsp;<strong>Items on server: </strong>' . $count;
            $out .= '&nbsp;<span style="margin-left: 12px;">&bull;</span>&nbsp;<strong>Not found locally: </strong>' . $notfnd . '</p>';
            $cp = current_path();
            $out .= '<div style="float: right; margin-top: -28px;"><a href="/' . $cp . '">Clear Sort</a></div>';
            $out .= theme('table', array('header' => $header, 'rows' => $rows));
            // Add Raw JSON in hidden div at bottom (enable show in shanti_images.js)
            $out .= '<div id="iiif-filelist-json"><a class="toggle">Raw JSON</a><div class="togglediv" style="display:none;"><pre>' . $json . '</pre></div>';
            // Return markup
            return $out;

        } else {
            return '<div><p>No images found.</p></div>';
        }
    } else {
        drupal_set_message(t('The IIIF Image upload URL has not been set'), 'warning', FALSE);
        return '<div><p>Cannot list images as no server is set. <br/>Please go to ' . l('the settings page', 'admin/config/media/shanti_images') . ' to sett the IIIF server URL.</p></div>';
    }
}

/**
 * Confirmation form for removing image from IIIF Server (admins only)
 */
function shanti_images_iiif_image_remove($form, &$form_state, $ifnm) {
    // Get Current IIIF Server. Return to home page if not set
    $srv = variable_get('shanti_images_view_url', FALSE);
    if (!$srv) {
        drupal_set_message(t("The IIIF server setting is not set in the Shanti Images Admin page"), 'warning');
        drupal_goto();
        return FALSE;
    }

    // Initialize confirmation form render array with IIIF Filename as value
    $form = array();
    $form['ifnm'] = array(
        '#type' => 'value',
        '#value' => $ifnm,
    );

    // Set other variables to be used in confirm_form function: title and msg
    $title = t('Delete IIIF Image: @fnm', array('@fnm' => $ifnm));
    $msg = t('<p>You have asked to delete the image, <strong>@inm</strong>, from the current IIIF server: <strong>@srv</strong><br/>This cannot be undone. Are you sure you want to do this?', array(
        '@inm' => $ifnm,
        '@srv' => $srv,
    ));

    // Create and return the full confirmation form
    return confirm_form(
        $form,
        $title,
        '/admin/config/media/shanti_images/list',
        $msg,
        t('Delete')
    );
}

/**
 * Submit function for removing IIIF images from server
 * Only called if deletion is confirmed
 */
function shanti_images_iiif_image_remove_submit($form, &$form_state) {
    // Set redirect back to list of IIIF Files
    $form_state['redirect'] = '/admin/config/media/shanti_images/list';

    // Get IIIF Filename from Form
    $inm = $form_state['values']['ifnm'];

    // If Filename not empty, then delete
    if (!empty($inm)) {
        _shanti_images_remove_iiif_image($inm);
    }
}

/**
 * Sorts rows of shanti_image admin list by column
 * used in "shanti_images_admin_list()" function
 */
function _shanti_image_admin_list_sort(&$rows, $sortby) {
    switch ($sortby) {
        case 'id':
            usort($rows, function($a, $b) {
                $a1 = strtolower($a[0]);
                $b1 = strtolower($b[0]);
                return strcmp($a1, $b1);
            });
            break;
        case 'date':
            usort($rows, function($a, $b) {
                $a1 = strtotime($a[1]);
                $b1 = strtotime($b[1]);
                if ($a1 == $b1) {return 0;}
                return ($a1 > $b1) ? 1 : -1;
            });
            break;
        case 'size':
            usort($rows, function($a, $b) {
                $a1 = $a[2];
                $b1 = $b[2];
                if ($a1 == $b1) {return 0;}
                return ($a1 > $b1) ? 1 : -1;
            });
            break;
        case 'node':
            usort($rows, function($a, $b) {
                $a1 = strtolower($a[3]);
                $b1 = strtolower($b[3]);
                return strcmp($a1, $b1);
            });
            break;
        default:
            // if false don't sort
    }
}


function shanti_image_format_bytes($bytes, $precision = 2) {
    // Taken from https://stackoverflow.com/questions/2510434/format-bytes-to-kilobytes-megabytes-gigabytes
    $units = array('B', 'KB', 'MB', 'GB', 'TB');

    $bytes = max($bytes, 0);
    $pow = floor(($bytes ? log($bytes) : 0) / log(1024));
    $pow = min($pow, count($units) - 1);

    // Uncomment one of the following alternatives
    $bytes /= pow(1024, $pow);
    // $bytes /= (1 << (10 * $pow));

    return round($bytes, $precision) . ' ' . $units[$pow];
}