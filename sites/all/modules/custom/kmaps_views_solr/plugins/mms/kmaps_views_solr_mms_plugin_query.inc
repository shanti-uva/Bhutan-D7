<?php
/**
 * @file
 *   Views query plugin for Visuals.
 */

/**
 * Views query plugin for Audio-Video related data.
 */
class kmaps_views_solr_mms_plugin_query extends views_plugin_query
{
    function query($get_count = FALSE)
    {
    }

    function execute(&$view)
    {
        //dpm($view);
        $app = $view->args[0];
        $kid = $view->args[1];

        // Resolve $app to correct MMS name
        $resolve = array(
            'places' => 'places',
            'subjects' => 'topics',
        );
        //Initialize pager
        $view->init_pager();
        $items_per_page = intval($this->pager->options['items_per_page']);
        $current_page = intval($this->pager->current_page);
        ++$current_page;

        $mmsURL = 'https://mms.thlib.org/';
        $mmsURL .= $resolve[$app] . '/';
        $mmsURL .= $kid . '/pictures.json?';
        $mmsURL .= 'per_page=' . $items_per_page . '&';
        $mmsURL .= 'page=' . $current_page;
        //dpm($mmsURL);

        $related_mms = save_to_cache('mms' . $app . $kid, $app, $kid, $mmsURL);
        $mmsObj = json_decode($related_mms);

        //Get the singular name from resolve
        $name = rtrim($resolve[$app], 's');
        $this->pager->total_items = intval($mmsObj->{$name}->total_entries);

        //Set some variables
        $view->total_rows = $this->pager->total_items;
        $view->items_per_page = intval($this->pager->options['items_per_page']);
        $view->current_page = $current_page;

        $this->pager->update_page_info();

        foreach ($mmsObj->{$name}->media as $doc) {
            $row = new stdClass;

            //Populate fields
            $row->mms_id = $doc->id;
            $row->mms_title = count($doc->titles) > 0 ? $doc->titles[0]->title : $doc->captions[0]->title;
            $row->resource_type = isset($doc->resource_type) ? $doc->resource_type->header : '';
            $row->photographer = isset($doc->photographer) ? $doc->photographer->fullname : '';
            $row->taken_on = isset($doc->taken_on) ? $doc->taken_on : '';
            $row->recording_note = isset($doc->recording_note) ? $doc->recording_note : '';
            $row->private_note = isset($doc->private_note) ? $doc->private_note : '';
            $row->rotation = isset($doc->rotation) ? $doc->rotation : '';
            $row->capture_device = isset($doc->capture_device) ? $doc->capture_device->model_title : '';
            $row->caption = isset($doc->captions) ? $doc->captions[0]->title : '';
            $row->description = isset($doc->descriptions) ? $doc->descriptions[0]->title : '';
            $row->copyright_holder = isset($doc->copyrights) ? $doc->copyrights[0]->copyright_holder->title : '';
            $row->copyright_holder_website = isset($doc->copyrights) ? $doc->copyrights[0]->copyright_holder->website : '';
            $row->reproduction_type = isset($doc->copyrights) ? $doc->copyrights[0]->reproduction_type->title : '';
            $row->reproduction_type_website = isset($doc->copyrights) ? $doc->copyrights[0]->reproduction_type->website : '';
            $row->locations = isset($doc->locations) ? implode('|', $doc->locations) : '';

            $keywords = '';
            foreach ($doc->keywords as $keyword) {
                $keywords = $keyword->title . '|';
            }
            $row->keywords = rtrim($keywords, '|');
            $row->affiliations = isset($doc->affiliations) ? implode('|', $doc->affiliations) : '';

            foreach ($doc->images as $image) {
                if ($image->thumbnail === 'jiats_huge') {
                    $row->image_url = $image->url;
                    $row->image = $image->url;
                    $row->image_dimension = $image->width . '|' . $image->height;
                }
            }
            // Add a different image if thumbnail 'jiats_huge' is not present
            if (!isset($row->image_url)) {
                foreach ($doc->images as $image) {
                    if ($image->thumbnail === 'huge') {
                        $row->image_url = $image->url;
                        $row->image = $image->url;
                        $row->image_dimension = $image->width . '|' . $image->height;
                    }
                }
            }

            $view->result[] = $row;
        }

    }
}