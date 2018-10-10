<?php

/**
 * Implements hook_drush_command().
 */
function explore_menu_drush_command() {

    $items['shanti_explore_menu_reset'] = array(
        'description' => 'Reset the links in the Shanti explore menu to match the current environemnt',
        'aliases' => array('emr'),
        'arguments' => array(
            'domain' => 'Set to a specific domain: local, local-predev, local-stage, predev, dev, stage, prod',
        ),
        'examples' => array(
            'drush emr stage' => 'Change the Explore Menu links to point to staging',
            'drush emr' => 'Defaults to production',
        ),
    );

    $items['shanti_explore_menu_current_domain'] = array(
        'description' => 'Get the current domain to which the Shanti Explore menu links point',
        'aliases' => array('emcd'),
    );

    return $items;
}

function drush_explore_menu_shanti_explore_menu_reset($dvar='') {
    $msg = explore_menu_update_links($dvar);
    $msg = strip_tags($msg);
    drush_print($msg);
}

function drush_explore_menu_shanti_explore_menu_current_domain() {
    $domain = explore_menu_get_current_domain();
    drush_print("The Explore Menu links currently point to: $domain");
}