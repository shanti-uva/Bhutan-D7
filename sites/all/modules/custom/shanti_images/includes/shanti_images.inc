<?php


/**
 * A function to monitor files associated with nodes and intiated the processing if newly attached or the deletion if removed
 * If file does not have a IIIF file ID, it is aded to the $files_to_add array. This is returned and added as a session setting (see node update and insert)
 * If node view page senses this variable is not empty, it calls the API image/upload/{nid}/{fid} to push the image to IIIF server
 * The API call is done through AJAX so the node view page loads (without the image) before the processing is complete. See Drupal.behaviors.shanti_images_add_images
 * Once the image is done processing the node view page automatically refreshes to show it.
 *
 * Update: In new version, files are only attached to node until they are uploaded to IIIF server. Once uploaded a file
 * will be deleted from Drupal, the only archived version will be the JPEG-2000 version on the IIIF Server. So any files
 * attached to node should be added to the DB.
 */
function _shanti_images_process_image_files($node) {
    $files_to_add = array();
    // Load the Shanti Image object
    $nid = $node->nid;
    $siobj = _shanti_images_get_node_image($node);
    $file = _shanti_images_get_node_files($node);
    if (is_array($file) && isset($file[0])) {
        $file = $file[0];
    }
    if (isset($file['fid'])) {
        $upload = FALSE;
        $fid = $file['fid'];
        $dbrec = _shanti_images_get_record($nid, 'nid');
        // If no db rec it's a new file
        if (!$dbrec) {
            $upload = TRUE;
        // If db rec fid is not same as current fid, it's a new image so upload
        } else if (empty($dbrec->fid) || $dbrec->fid != $fid) {

            // Delete image up on IIIF server
            $ifnm = $siobj->getIIIFName();
            _shanti_images_remove_iiif_image($ifnm);
            // Remove old image file if it still exists
            $dfile = file_load($dbrec->fid);
            if ($dfile) {
                file_delete($dfile, TRUE);
            }
            _shanti_images_delete_record($siobj->getID());
            $upload = TRUE;
        }
        // If the node is saved with the same file then upload will not be TRUE. Only upload if it's a new file
        if ($upload) {
            $fnm = $file['filename'] ?: '';
            $width = $file['width'] ?: 0;
            $height = $file['height'] ?: 0;
            $siid = _shanti_images_create_record($nid, $fid, $fnm, $width, $height);
            $files_to_add[] = array('nid' => $nid, 'fid' => $fid, 'siid' => $siid);
        }
    } else {
        $siobj->updateTable(array('fid' => 0));
    }
    return $files_to_add;
}

/**
 * Takes an IIIF filename ($i3fid) and retrieves the node associated with it
 *
 * @param $i3fid
 * @return bool|mixed
 */
function _shanti_images_get_node_by_filename($i3fid) {
    // TODO: Replace following line with just a sql query
    $dbrec = _shanti_images_get_record($i3fid, 'i3fid');
    if ($dbrec) {
        $node = node_load($dbrec->nid);
        return $node;
    } else {
        $sid = (isset($dbrec->siid)) ? $dbrec->siid : '-1';
        watchdog('shanti_images', t("No node associated with @fid (@sid)", array(
            '@fid' => $i3fid,
            '@sid' => $sid,
        )));
        return FALSE;
    }
}

/**
 * Helper function to get files attached to a node
 *
 * @param $node object
 *          The node object to be searchded
 *
 * @param $fids boolean
 *          Whether to return a list of FIDs
 *
 * @return mixed
 *          Returns either a list of FIDs or else a File Object
 */

function _shanti_images_get_node_files($node, $fids=FALSE) {
    $ew = entity_metadata_wrapper('node', $node);
    if ($fids) {
        $fids = array();
        foreach($ew->field_image->value() as $n => $file) {
            $fids[] = $file['fid'];
        }
        return $fids;
    }

    $file = $ew->field_image->value();  // Returns an object with an fid but not the file object
    if (!empty($file->fid)) {
        return file_load($file->fid);
    } else  {
        return $file;
    }
}

/**
 * Remove an image attached to a node after it has been uploaded to the IIIF server
 * Called periodically from hook_cron or from admin function. This does not delete the image but only the
 * original file associated with it after it has been successfully uploaded to the IIIF server
 *
 * @param $node
 *
 * @return Boolean $success - True/False whether successful or not
 */
function _shanti_images_expunge_image_file($node) {
    $success = FALSE;
    $ret = FALSE;
    if (is_numeric($node)) { $node = node_load($node); }
    $siobj = _shanti_images_get_node_image($node);
    // Only proceed deleting the image if there is an IIIF version of the image and Drupal file associated with the object
    // Otherwise the image should not be deleted or there is no image to delete.
    if ($siobj->imageExists('both')) {
        try {
            $file = $siobj->getLocalImage();
            if ($file && file_exists($file->uri)) {
                $node->field_image[LANGUAGE_NONE] = array();
                node_save($node); // Saving node without file image value automatically deletes the file.
            }
            _shanti_images_update_record($siobj->getID(), array('fid' => 0));
        } catch (Exception $e) {
            watchdog_exception('shanti_images expunge', $e);
        }
    } else if (!$siobj->imageExists('iiif')) {
        watchdog('shanti_images expunge', "Unable to expunge file associated with {$node->nid} because it has not been successfully uploaded to the IIIF server");
    } else {
        // If the file is not found anywhere, remove the reference to it on the node
        $node->field_image[LANGUAGE_NONE] = array();
        node_save($node);
    }
    if ($ret !== FALSE) { $success = TRUE; }
    return $success;
}

/**
 * Read the shanti image table for shanti image record by node ID and create a shanti image object from the record
 *
 * @param $nid
 * @return ShantiImage
 */
function _shanti_images_get_node_image($nid) {
    if (is_object($nid)) { $nid = $nid->nid; }
    $record = _shanti_images_get_record($nid, 'nid');
    // TODO: Check if the following can be removed without consequence, since it is in the class itself
    if (!empty($record) && is_object($record) && isset($record->siid)) {
        $imgObj = new ShantiImage($record->siid, $nid);
        if (!empty($record->i3fid)) {
            $imgObj->i3fid = $record->i3fid;
        }
        if (!empty($record->fid)) {
            $imgObj->fid = $record->fid;
        }
        if (!empty($record->i3fid)) {
            $imgObj->filename = $record->filename;
        }
        if (!empty($record->uid)) {
            $imgObj->uid = $record->uid;
        }
        if (!empty($record->width) && !empty($record->height)) {
            $imgObj->setDimensions($record->width, $record->height);
        }
    } else {
        $imgObj = new ShantiImage('none', $nid);

        //watchdog('shanti_images inc', "No shanti_image record found in database for node {$nid}");
    }
    return $imgObj;
}

/**
 * POST file to iiif webservice
 * Called from shanti_images_upload_iiif()
 * Code for uploading files to service is lifted from this page:
 *              http://stackoverflow.com/questions/18563594/drupal-form-api-file-upload-using-drupal-http-request
 *
 */
function _shanti_images_do_upload_to_iiif($file, $i3fid) {
    if (variable_get('shanti_images_debug', FALSE)) {
        watchdog('shanti images DEBUG', "i3fid: $i3fid");
        watchdog('shanti images DEBUG', "File: " . json_encode($file));
    }

    if (!is_array($file)) { $file = (array)$file; }
    $file_uri = $file['uri'];
    $file_loc = drupal_realpath($file_uri);
    $filename = $file['filename'];
    $fnpts = explode('.', $filename);
    $fext = array_pop($fnpts);

    // Check for valid image formats
    if (variable_get('shanti_images_debug', FALSE)) {
        $msg = "File URI: {$file_uri} <br/> File Loc: {$file_loc} <br/> File Name: {$filename} <br/> Extension: {$fext}";
        watchdog("shanti_images", $msg);
    }

    $res;
    if (in_array(strtolower($fext), shanti_images_get_valid_extensions())) {
        $uploaddest = variable_get('shanti_images_upload_url', FALSE);
        if ($uploaddest) {
            if (_iiif_image_exists($i3fid)) {
                $deleteurl = variable_get('shanti_images_delete_url', FALSE);
                if ($deleteurl) {
                    $deleteurl = str_replace('__FILE__', $i3fid . '.jp2', $deleteurl);
                    $res = @file_get_contents($deleteurl);
                }
            }

            $curlcmd = 'curl -F"uploadFile=@' . $file_loc . ';filename=' . $i3fid . '.jp2" ' . $uploaddest . '/uploadFile';
            $resjson = shell_exec($curlcmd);
            $res = json_decode($resjson);
            if (!empty($res->retcode) && $res->retcode != "200") {
                $errmsg = (!empty($res->msg)) ? $res->msg : 'No message';
                $errmsg .= " ({$res->retcode})";
                drupal_set_message(t("We were unable to post your file to the server. ") . "($errmsg)", 'warning');
                watchdog('shanti_images', "Upload to IIIF failed: FID: {$file->fid} ($i3fid); msg: $errmsg");
            } else {
                $restr = json_encode($res);
                watchdog('shanti_images', "Upload cmd failed: $curlcmd Resp: $restr");
            }
            if (variable_get('shanti_images_debug', FALSE)) {
                watchdog('shanti_images DEBUG', "Curl cmd: $curlcmd");
                watchdog('shanti_images DEBUG', "Response: $resjson");
            }
        } else {
            watchdog('shanti_images' , "No upload destination set to post images to!");
        }
    } else {
        watchdog('shanti_images', "Invalid extension $fext for image $i3fid");
        drupal_set_message(t("Your image (@fn) failed to upload because it had an unacceptable extension: @ext",
            array('@ext' => $fext, '@fn' => $i3fid)));
    }
    return $res;
}

function _iiif_image_exists($inm) {
    $serv = variable_get('shanti_images_view_url', FALSE);
    if ($serv) {
        $url = $serv . "/mandala/{$inm}/info.json";
        $file_headers = @get_headers($url);
        if (!strstr($file_headers[0], '404 Not Found')) { return TRUE; }
    }
    return FALSE;
}

/**
 * Helper function to return the full path to view IIIF images if both settings are set
 */
function _get_iiif_view_url() {
    $url = variable_get('shanti_images_view_url', FALSE);
    $path = variable_get('shanti_images_view_path', FALSE);
    if ($url && $path) {
        return $url . $path;
    }
    return FALSE;
}

/**
 * Remove callback for Ajax Button in Shanti Image Edit form to remove image
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */
function _shanti_images_remove_callback($form, $form_state) {
    $imgfield = $form['field_image'];

    // Replace image field with one where the field itself is not hidden so it can be replaced
    // use timeout to trigger pressing the delete file button to disassociate from node
    $fi = field_info_instance('node', 'field_image', 'shanti_image');
    $desc = $fi['description'];
    $imgfield['#prefix'] = '<p><strong>Replace image by uploading a new one:</strong></p><p>' . $desc . '</p>';
    $imgfield['#suffix'] = '<script type="text/javascript">setTimeout(function() {  ' .
        "jQuery('button#edit-field-image-und-0-remove-button--2.btn-delete').trigger('mousedown'); }, 400);</script>";
    return $imgfield;
}

function _shanti_images_remove_iiif_image($inm) {
    if (empty($inm)) { return; }
    $deleteurl = variable_get('shanti_images_delete_url', FALSE);
    if (substr($inm, -4) != '.jp2') { $inm .= '.jp2'; } // Needs to have .jp2 extension on the name

    if ($deleteurl) {
        if (_shanti_images_can_delete($deleteurl, $inm)) {
            $deleteurl = str_replace('__FILE__', $inm, $deleteurl);
            // watchdog('shanit images remove delete url', $deleteurl);
            $res = @file_get_contents($deleteurl);
            if ($res === FALSE) {
                drupal_set_message(t('Unable to contact IIIF server to delete image'), 'warning');
            } else {
                $res = json_decode($res);
                if (strstr($res->msg, ' not ') && $inm != '.jp2') {
                    watchdog('shanti_images', t('No image, @inm, found on IIIF server to delete.', array('@inm' => $inm)));
                } else {
                    //watchdog('shanti_images', t('Image @inm deleted from IIIF server', array('@inm' => $inm)));
                    $dbrec = _shanti_images_get_record($inm, 'i3fid');
                    if (!empty($dbrec) && isset($dbrec->siid)) {
                        _shanti_images_delete_record($dbrec->siid);
                    }
                }
            }
        } else {
            drupal_set_message(t("The IIIF image @inm was not deleted from the IIIF production server, because you are on a non-production site. " .
                "<br/>The local Drupal record however has been deleted.",
                array('@inm' => $inm)), 'warning');
            watchdog('shanti_images', "Not allowing to delete production IIIF image ($inm) from non-production site ($base_url).");
        }
    } else {
        drupal_set_message(t('No url for IIIF server set. Cannot delete iiif image.'), 'warning', FALSE);
    }
}

/**
 * Function to prevent staging from deleting images on production since they use the same server
 *
 * @param $deleteurl
 * @param $inm
 *
 * @return boolean whether to allow delete or not
 */
function _shanti_images_can_delete($deleteurl, $inm) {
    if (strstr($deleteurl, 'fupload.lib.virginia.edu')) {
        // if the image is a production image it won't have -dev or -stage in the name
        if (preg_match('/shanti-image-\d+\.jp2/', $inm)) {
            global $base_url;
            // if the base url of the site is not the prod images site, then do not allow
            if ($base_url != 'https://images.shanti.virginia.edu') {
                return FALSE;
            }
        }
    }
    return TRUE;
}

/**
 * Function called by node insert/update for authors dates
 */
function _shanti_image_process_dates(&$node) {
    $mnths_full = '/(january|february|march|april|may|june|july|august|september|october|november|december)\s+(\d{4})/';
    $mnts_abbr = '/(jan|feb|mar|apr|may|jun|jul|aug|sept|oct|nov|dec)\s+(\d{4})/';
    if (!empty($node->field_agent_dates_approx) && empty($node->field_agent_dates[LANGUAGE_NONE])) {
        $dpts = array();
        $currtz = date_default_timezone_get();
        $tz = 'UTC';
        date_default_timezone_set($tz);
        $dstr = $node->field_agent_dates_approx[LANGUAGE_NONE][0]['value'];
        $ts = strtotime($dstr);
        if (!empty($ts) && is_numeric($ts)) {
            $dpts['value1'] = $ts;
        } elseif (preg_match("/(\d{2}\/\d{2}\/\d{4})(\?*)/", $dstr, $mtchs)) {
            $dpts['value1'] = strtotime("{$mtchs[1]}");
            if ($mtchs[2] == '?') { $dpts['uncertain'] = TRUE; }
        } elseif (preg_match("/(\d{4})(\?*)/", $dstr, $mtchs)) {
            $dpts['value1'] = strtotime("01/01/{$mtchs[1]}");
            $dpts['value2'] = strtotime("12/31/{$mtchs[1]}");
            if ($mtchs[2] == '?') { $dpts['uncertain'] = TRUE; }
        } elseif (preg_match("/(\d{4})(\?*)\s*\-\s*(\d{4})(\?*)/", $dstr, $mtchs)) {
            $dpts['value1'] = strtotime("01/01/{$mtchs[1]}");
            $dpts['value2'] = strtotime("12/31/{$mtchs[3]}");
            if ($mtchs[2] == '?' || $mtchs[4] == '?') { $dpts['uncertain'] = TRUE; }
        }

        if (!empty($dpts)) {
            $node->field_agent_dates[LANGUAGE_NONE][0] = array(
                'value' => format_date($dpts['value1'], 'custom', 'Y-m-d H:i:s', $tz),
                'timezone' => $tz,
                'timezone_db' => $tz,
            );
            if (isset($dpts['value2'])) {
                $node->field_agent_dates[LANGUAGE_NONE][0]['value2'] = format_date($dpts['value2'],
                    'custom','Y-m-d H:i:s', $tz);
            }
        }

        date_default_timezone_set($currtz);
    }
}

/**
 * Private functions called from hook_node_view
 */

/**
 * Private function for image node view. See shanti_images_node_view() above.
 */
function _shanti_images_image_view($node, $view_mode) {
    //watchdog('shanti images', "view mode: $view_mode");
    if ($view_mode == 'full') {
        libraries_load('flexslider');
        libraries_load('columnizer');
        // TODO: convert open seadragon add js to add library if needed
        //drupal_add_js(drupal_get_path('module', 'shanti_images') . '/js/openseadragon.min.js', array('scope' => 'footer'));
        //drupal_add_js(drupal_get_path('module', 'shanti_images') . '/js/shanti_images_sdinit.js', array('scope' => 'footer'));
    }
}

/**
 * Private function for image description node view. See shanti_images_node_view() above.
 */
function _shanti_images_desc_view($node, $view_mode, $langcode) {
    // De-links description titles so they don't link to stand-alone description nodes
    // TODO: Make this activated by a setting so users can decide if they want to do it this way or in a template
    $title = $node->title;
    $node->title_str = $title; // In case needed in template
    $node->title = '';
    $node->content['field_description'][0]['#markup'] = '<h2>' . $title . '</h2>' . $node->content['field_description'][0]['#markup'];
}


function _shanti_images_build_IIIFURL($fname, $width = '800', $height = '', $rotation = 0, $crop = 'full', $scaled = TRUE)
{
    $server = variable_get('shanti_images_view_url', 'https://iiif.lib.virginia.edu');
    $servpath = variable_get('shanti_images_view_path', '/mandala/');
    $url = $server . $servpath . $fname . '/' . $crop . '/';
    $dimensions = "{$width},{$height}";
    if (empty($width) && empty($height)) {
        $dimensions = "full";
    } else if ($scaled) {
        $url .= '!';
    }
    $url .= $dimensions . '/' . $rotation . '/default.jpg';
    return $url;
}

function _shanti_images_build_InfoURL($fname)
{
    $server = variable_get('shanti_images_view_url', 'https://iiif.lib.virginia.edu');
    $servpath = variable_get('shanti_images_view_path', '/mandala/');
    $url = $server . $servpath . $fname . '/info.json';
    return $url;
}

function _shanti_images_build_croppedURL($fnm, $width, $height, $cropwidth, $cropheight, $rotation = FALSE, $centerx = TRUE, $centery = FALSE) {
    // If the rotation is on a side then exchange width and height values for landscape presentation
    if ($rotation == 90 || $rotation == 270) {
        $temp = $height;
        $height = $width;
        $width = $temp;
        $temp = $cropheight;
        $cropheight = $cropwidth;
        $cropwidth = $temp;
    }

    $url = '';
    if ($height > 0 && $cropheight > 0) {
        $oldratio = $width / $height;
        $newratio = $cropwidth / $cropheight;
        $x = 0;
        $y = 0;
        if ($oldratio < $newratio) {
            $newwidth = $width;
            $newheight = floor($width / $newratio);
            if ($centery) {
                $y = floor(($height - $newheight) / 2);
            }
        } else if ($oldratio > $newratio) {
            $newheight = $height;
            $newwidth = floor($height * $newratio);
            if ($centerx) {
                $x = floor(($width - $newwidth) / 2);
            }
        } else {
            $newheight = $height;
            $newwidth = $width;
        }
        $crop = "$x,$y,$newwidth,$newheight";
        $url = ShantiImage::buildIIIFURL($fnm, $cropwidth, $cropheight, $rotation, $crop);
    }
    return $url;
}

/**
 * Get an IIIF image ratio from data stored in the database using id and column name to identify row
 *
 * @param $id
 * @param $col
 *
 * @return float
 */
function _shanti_images_get_ratio($id, $col) {
    $info = _shanti_images_get_record($id, $col);
    if (empty($info->height)) { return 1; }
    return ($info->width / $info->height);
}


/**
 * Shanti Image Table Access Functions
 */
function _shanti_images_create_record($nid, $fid=0, $filename='', $width=0, $height=0, $uid=FALSE) {
    global $user;
    if (empty($uid)) { $uid = $user->uid; }
    $fields = array(
        'fid' => $fid,
        'nid' => $nid,
        'uid' => $uid,
        'i3fid' => '',
        'filename' => $filename,
        'width' => $width,
        'height' => $height,
        'created' => time(),
    );
    try {
        $siid = db_insert('shanti_images')
            ->fields($fields)
            ->execute();
    } catch (Exception $e) {
        $siid = FALSE;
        drupal_set_message(t("Problem creating Shanti Image record"), "warning");
        watchdog('shanti_images', 'Problem creating image record: ' . json_encode($e));
    }
    return $siid;
    /*
     *  Do we need to create an image object here?
     $siobj = new ShantiImage($siid, $nid);
    return $siobj;
    */
}

/**
 * Update the shanti_images table from a ShantiImage class object
 *
 * @param $siobj ShantiImage
 *      An ShantiImage class object
 *
 * @return bool
 *      Success or failure
 */
function _shanti_images_update_table_from_image($siobj) {
    $data = array();
    if (!empty($siobj->width)) { $data['width'] = $siobj->width; }
    if (!empty($siobj->height)) { $data['height'] = $siobj->height; }
    if (!empty($siobj->filename)) { $data['filename'] = $siobj->filename; }
    if (!empty($siobj->fid)) { $data['fid'] = $siobj->fid; }
    $i3fid = $siobj->getIIIFName();
    if (!empty($i3fid)) { $data['i3fid'] = $i3fid; }
    return _shanti_images_update_record($siobj->getID(), $data);
}


/**
 * Retrieve a record from the Shanti Images table
 *
 * @param $id : The id value
 * @param $col : The column searched on
 * @param $as_array : Whether to return as an array
 * @return mixed
 */
function _shanti_images_get_record($id, $col = 'siid', $as_array=FALSE) {
    $result = db_select('shanti_images', 'si')
        ->fields('si')
        ->condition($col, $id, '=')
        ->execute();
    $result = $result->fetchAll();
    if (empty($result)) { return FALSE; }
    if (count($result) > 0 and !$as_array) { $result = $result[0]; }
    return ($as_array) ? (array)$result : $result;
}

/**
 * Update the record in the shanti_images table with the data in an associative array field name -> value
 *
 * @param $siid
 * @param $fields
 * @return bool
 */
function _shanti_images_update_record($siid, $data) {
    $res = db_update('shanti_images')
        ->fields($data)
        ->condition('siid', $siid, '=')
        ->execute();

    return ($res == 1) ? TRUE : FALSE;
}

/**
 * Remove a record from the shanti images database table
 *
 * @param $siid
 * @return bool
 */
function _shanti_images_delete_record($siid) {
    $res = db_delete('shanti_images')
        ->condition('siid', $siid)
        ->execute();

    return ($res == 1) ? TRUE : FALSE;
}

/** End of Table Access Functions */

/** Generic Helper functions **/

function _url_exists($url) {
    $headers = get_headers($url);
    if ($headers[0] == 'HTTP/1.1 404 Not Found') {
        return FALSE;
    } else {
        return TRUE;
    }
}
