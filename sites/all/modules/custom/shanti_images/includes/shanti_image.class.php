<?php
/**
 * ShantiImage class: a class for managing shanti images
 */

class ShantiImage
{
    // Properties
    private $id = 0;
    private $nid = 0;
    var $index = 0;
    var $prefix = 'shanti-image-';
    var $fid = 0;
    var $filename = '';
    var $i3fid = FALSE;
    var $height = FALSE;
    var $width = FALSE;
    var $rotation = 0;
    private $ratio = FALSE;
    var $server = 'https://iiif.lib.virginia.edu';
    var $servpath = '/mandala/';
    var $title = '';
    var $path = '';
    var $uid = 0;

    /**
     * ShantiImage constructor.
     *
     * @param bool $id
     *      The ID of the ShantiImage (required)
     * @param bool $nid
     *      The Node ID that the image is associated with (required)
     * @param bool $index
     *      The index of the image in a list of images associated with a node. If a node has more than one image
     *      associated with it. This number is the index of this image in that list of images. (Defaults to 0)
     * @param bool $width
     *      The width of the image (Not required, can be set by IIIF info. Defaults to FALSE)
     * @param bool $height
     *      The height of the image (Not required, can be set by IIIF info. Defaults to FALSE)
     */
    function __construct($id, $nid = FALSE, $index = 0, $width = FALSE, $height = FALSE)
    {
        $this->server = variable_get('shanti_images_view_url', 'https://iiif.lib.virginia.edu');
        $this->servpath = variable_get('shanti_images_view_path', '/mandala/');
        $this->id = $id;
        $this->prefix .= $this->getEnvSuff(); // Add an environment suffix for localhost and stage. Only on new images.

        if ($nid) {
            $this->nid = $nid;
        }

        // Adds filename, fid, height, width, etc. to image object for those that have a record in the table
        $this->updateFromTable();

        // From node it adds title, path, and rotation
        $this->updateFromNode();

        // If width and height are still missing, update from IIIF and save to shanti_images table
        if (!$this->width || !$this->height) {
            $this->setDimensionsByIIIF();
            if ($this->width && $this->height) {
                $data = array(
                    'width' => $this->width,
                    'height' => $this->height,
                );
                $this->updateTable($data);
            }
        }

    }

    /**
     * Get a suffix string to distinguish images from different environements.
     * Dev and Prod take no suffix because they are the main users of test and prod IIIF servers respectively
     * Use -loc- for localhost and -stage- for staging, to differentiate files on those two.
     *
     * @return string
     */
    function getEnvSuff() {
        global $base_url;
        $env = '';
        if (strstr($base_url, 'predev.dd')) {
            $env = 'predev-loc-';
        } elseif (strstr($base_url, 'stage.dd')) {
          $env = 'stage-loc-';
        } elseif (strstr($base_url, '.dd')) {
            $env = 'loc-';
        } elseif (strstr($base_url, '-dev')) {
            $env = 'dev-';
        } elseif (strstr($base_url, '-stage')) {
            $env = 'stage-';
        }
        return $env;
    }

    /**
     * Sets the dimensions (width and height) of the image in one call
     *
     * @param $width
     * @param $height
     */
    function setDimensions($width, $height)
    {
        $this->width = $width;
        $this->height = $height;
        $this->setRatio();
    }

    /**
     * Sets the dimensions of the image by using the IIIF info url
     *
     */
    function setDimensionsByIIIF()
    {
        $info = $this->getIIIFInfo();
        if (!empty($info->width) && !empty($info->height)) {
            $this->setDimensions($info->width, $info->height);
            return TRUE;
        }
        return FALSE;
    }

    function setNID($nid) {
        $this->nid = $nid;
    }

    /**
     * A private function to set the ratio for the image to be called whenever the dimensions are changed.
     * The ratio can then be called by $this->get('ratio'). If either height or width is unset, then the
     * ratio defaults to 1.
     */
    private function setRatio()
    {
        // If height and width exists, calculate ratio
        if (is_numeric($this->height) && $this->height > 0 && is_numeric($this->width) && $this->width > 0) {
            $this->ratio = $this->width / $this->height;
            // Otherwise try to set dimensions by IIIF info
        } else {
            $this->setDimensionsByIIIF();
            // If height and width now exist set ratio
            if (is_numeric($this->height) && $this->height > 0 && is_numeric($this->width) && $this->width > 0) {
                $this->ratio = $this->width / $this->height;
                // Otherwise return 1
            } else {
                $this->ratio = 1;
            }
        }
        if ($this->rotation == '90' || $this->rotation == '270') {
            $this->ratio = 1 / $this->ratio;
        }
    }

    function getDimensions($pretty_print = FALSE)
    {
        if (!$this->width) {
            $this->setDimensionsByIIIF();
        }
        if ($pretty_print) {
            return $this->width . "x" . $this->height;
        }
        return array('width' => $this->width, 'height' => $this->height);
    }

    function getID()
    {
        return $this->id;
    }

    function getLocalImage()
    {
        if ($this->fid > 0) {
            return file_load($this->fid);
        } else {
            return FALSE;
        }
    }

    function getNID()
    {
        return $this->nid;
    }

    function getNode()
    {
        return node_load($this->nid);
    }

    function getRatio()
    {
        if (!$this->ratio) {
            $this->setRatio();
        }
        return $this->ratio;
    }

    /**
     * Returns the IIIF Name for the image in the format of {prefix}{id}, which by default returns "shanti-image-1234"
     * Checks data associated with entry first. If not there, creates it and puts in data table
     *
     * @param $update Boolean
 *          Whether to update the data table or not
     *
     * @return string
     *      The IIIF name for this image
     */
    function getIIIFName($update = FALSE)
    {
        if ($this->i3fid) {
            $i3fid = $this->i3fid;
        } else {
            $i3fid = $this->prefix . $this->id;
            if ($update) {
                $this->updateTable(array(
                    'i3fid' => $i3fid,
                ));
            }
        }
        return $i3fid;
    }

    /**
     * Returns the URL for a specifically defined derrivative of an image
     *
     * @param string $width
     *      The width of the returned derivative
     * @param string $height
     *      The height of the derivative
     * @param bool $rotation
     *      The degree of rotation for the image
     * @param string $crop
     *      The dimensions of the crop in the format of (x, y, width, height)
     * @param bool $scaled
     *      Whether or not to scale the image keeping the aspect ration (TRUE prepends the "!" to the dimensions)
     *
     * @return string
     *      The full url to the desired derivative
     *
     */
    function getURL($width = '800', $height = '', $rotation = FALSE, $crop = 'full', $scaled = TRUE)
    {
        $fname = $this->getIIIFName();
        if (!$rotation) {
            $rotation = $this->rotation;
        }
        return _shanti_images_build_IIIFURL($fname, $width, $height, $rotation, $crop, $scaled);
    }

    static function buildIIIFURL($fname, $width = '800', $height = '', $rotation = 0, $crop = 'full', $scaled = TRUE)
    {
        $server = variable_get('shanti_images_view_url', 'https://iiif.lib.virginia.edu');
        $servpath = variable_get('shanti_images_view_path', '/mandala/');
        $url = $server . $servpath . $fname . '/' . $crop . '/';
        if (strstr($url, '-test') && preg_match('/shanti-image-\d+/', $fname, $mtch)) {
          $url = str_replace('-test', '', $url);
        }
        $dimensions = "{$width},{$height}";
        if (empty($width) && empty($height)) {
            $dimensions = "full";
        } else if ($scaled) {
            $url .= '!';
        }
        $url .= $dimensions . '/' . $rotation . '/default.jpg';
        return $url;
    }

    /**
     * Returns the full URL to the json info API for the image from the IIIF server
     *
     * @return string
     *      The URL to the JSON info
     */
    function getInfoURL()
    {
        global $base_url;
        $iiifname = $this->getIIIFName();
        $url = $this->server . $this->servpath . $iiifname . '/' . 'info.json';
        // account for PROD images on DEV and Stage
        if (preg_match('/(-dev)|(-stage)|(.dd)/', $base_url)) {
            if (preg_match('/shanti-image-\d+/', $iiifname)) {
                $url = str_replace('-test', '', $url);
            }
        }
        return $url;
    }

    /**
     * Returns a JSON object or array with the info about the file from the IIIF server
     *
     * @param bool $as_array
     *      When true returns an associative array. Otherwise, returns an object. Default is FALSE.
     *
     * @return array|mixed
     *      Returns either an array or a PHP Object of the JSON info for the object
     */
    function getIIIFInfo($as_array = FALSE)
    {
        $jobj = FALSE;
        if ($this->id == 'none') {
            $jobj = json_decode('{"status": "404", "height":1, "width":1, "msg":"No Shanti Image ID"}');
        } else {
            $iurl = $this->getInfoUrl();
            $iurl = str_replace('https://cicada.shanti.virginia.edu/images-test', 'http://iiif-test.lib.virginia.edu', $iurl);
            $iurl = str_replace('https://cicada.shanti.virginia.edu/images', 'http://iiif.lib.virginia.edu', $iurl);
            if (_url_exists($iurl)) {
                $json = file_get_contents($iurl);
                if ($json) {
                    $jobj = json_decode($json);
                }
            } else {
                //watchdog('shanti_image class', 'No info at: ' . $iurl);
            }
        }
        if ($as_array) {
            $jobj = (array)$jobj;
        }
        if (!$jobj) {
            //watchdog("shanti image class", "Unable to get IIIF info for Shanti Image: {$this->id} (NID: {$this->nid})");
        }
        return $jobj;
    }

    /**
     * Get the URL for a image cropped to a specific dimensions, centered on X and/or Y axis
     *
     * @param $cropwidth
     * @param $cropheight
     * @param $centerx
     * @param $centery
     * @return string
     */
    function getCropped($cropwidth, $cropheight, $rotation = FALSE, $centerx = TRUE, $centery = FALSE)
    {
        if (empty($this->width) && empty($this->height)) {

            //watchdog('shanti_image class', "No width or height for siid {$this->id} ({$this->nid} in get cropped");
            $this->setDimensionsByIIIF();
        }
        $fnm = $this->getIIIFName();
        $width = $this->width;
        $height = $this->height;
        if (!$rotation) {
            $rotation = (360 - $this->rotation) % 360;
        }
        return _shanti_images_build_croppedURL($fnm, $width, $height, $cropwidth, $cropheight, $rotation, $centerx, $centery);
    }

    /**
     * @param $data
     *      An associative array of column => values to replace in the shanti_image table for this shanti image object
     *
     * @return bool
     *      A boolean result indicating success
     */
    function updateTable($data) {
        return _shanti_images_update_record($this->id, $data);
    }

    /**
     * Update a ShantiImage class object from the shanti_images table
     *
     * @return bool
     *
     */

    function updateFromTable() {
        if ($this->id == 'none' || $this->id == 0) { return; }
        $rec = _shanti_images_get_record($this->id);
        if ($rec) {
            if (empty($this->nid) && !empty($rec->nid)) {
                $this->nid = $rec->nid;
            }
            if (!empty($rec->fid)) {
                $this->fid = $rec->fid;
            }
            if (!empty($rec->uid)) {
                $this->uid = $rec->uid;
            }
            if (!empty($rec->i3fid)) {
                $this->i3fid = $rec->i3fid;
            }
            if (!empty($rec->filename)) {
                $this->filename = $rec->filename;
            }
            if (!empty($rec->width) && !empty($rec->height)) {
                $this->setDimensions($rec->width, $rec->height);
            }
            return TRUE;
        } else {
            return FALSE;
        }
    }

    /**
     * Update information in Shanti Image from node object
     *
     * @param bool $node
     */
    function updateFromNode($node=FALSE)
    {
        global $base_path;
        if (is_numeric($node)) {
            $nid = $node;
        } elseif (isset($node->nid)) {
            $nid = $node->nid;
        } else {
            $nid = $this->nid;
        }

        $qry = db_select('node', 'n');
        $qry->condition('n.nid', $nid);
        $qry->join('field_data_field_image_rotation', 'rot', 'rot.entity_id = n.nid');
        $res =  $qry->fields('n', array('nid', 'title'))
            ->fields('rot', array('field_image_rotation_value'))
            ->execute();

        $res = $res->fetchAssoc($res);
        $this->title = $res['title'];
        $this->path = $base_path . drupal_get_path_alias('node/' . $nid);
        $this->rotation = $res['field_image_rotation_value'];

        /*  Loading node is too time consuming
        if (!$node) { $node = $this->nid; }
        if (is_numeric($node)) { $node = node_load($node); }
        if ($node) {
            $this->title = $node->title;
            $this->path = $base_path . drupal_get_path_alias('node/' . $node->nid);
            if (!empty($node->field_image_rotation[LANGUAGE_NONE][0]['value'])) {
                $this->rotation = $node->field_image_rotation[LANGUAGE_NONE][0]['value'];
            }
        }*/


    }

    /**
     * Writes certain data in Shanti Image object to table
     *
     * @return bool
     */
    function writeToTable() {
        $data = array(
            'i3fid' => $this->i3fid,
        );
        if (!empty($this->filename)) {
            $data['fid'] = $this->fid;
            $data['filename'] = $this->filename;
        }
        if (!empty($this->width) && !empty($this->height)) {
            $data['width'] = $this->width;
            $data['height'] = $this->height;
        }
        return $this->updateTable($data);
    }

    /**
     * Function to determine if either the original file uploaded associated with this image object exists as a Drupal managed file
     * or if the associated IIIF image is up on the server
     *
     * @param $loc
     *      The location where the test should be performed
     *      Values are: drupal, iiif, both
     *
     * @return bool
     */
    function imageExists($loc = "iiif")
    {
        $exists = FALSE;
        if ($loc == 'drupal') {
            $li = $this->getLocalImage();
            $exists = !empty($li);
        } else if ($loc == 'iiif') {
            $info = $this->getIIIFInfo();
            if (!empty($info->{'@id'}) && !empty($info->width) && !empty($info->height)) {
                $exists = TRUE;
            }
        } else if ($loc == 'both') {
            $li = $this->getLocalImage();
            $locexists = !empty($li);
            $info = $this->getIIIFInfo();
            if ($locexists && !empty($info->{'@id'}) && !empty($info->width) && !empty($info->height)) {
                $exists = TRUE;
            }
        }
        return $exists;
    }
}