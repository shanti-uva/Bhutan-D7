<?php

/**
 * @file
 * template.php
 */

 /**
  *   This is the template.php file for a child sub-theme of the Shanti Sarvaka theme.
  *   Use it to implement custom functions or override existing functions in the theme.
  */

/**
 * Implements HOOK_breadcrumb().
 * Customizes output of breadcrumbs
 */
function sarvaka_kmaps_breadcrumb($variables) {
  global $base_url;
  $app = explode("/", current_path());
  $app = $app[0];
  $breadcrumbs = is_array($variables['breadcrumb']) ? $variables['breadcrumb'] : array();
  $output = '<ol class="breadcrumb">';
  array_unshift($breadcrumbs, '<a href="' . base_path() . $app . '">' . theme_get_setting('shanti_sarvaka_breadcrumb_intro') . '</a>');
  if(count($breadcrumbs) > 1) {
    $breadcrumbs[0] = str_replace('</a>', ':</a>', $breadcrumbs[0]);
  }
  $lidx = count($breadcrumbs) - 1;
  $breadcrumbs[$lidx] = '<a href="#">' . $breadcrumbs[$lidx] . '</a>';
  if (count($breadcrumbs) > 2) {
      foreach($breadcrumbs as $crumb) {
          $icon = ($breadcrumbs[0] == $crumb) ? '' : ' <span class="icon shanticon-arrow3-right"></span>';
          $output .= "<li>$crumb$icon</li>";
      }
  }
  $output .= '</ol>';
  return $output;
}

/**
 * Implements hook_preprocess_page().
 */
function sarvaka_kmaps_preprocess_page(&$variables) {
    $path = current_path();
    if (preg_match("/^subjects/i", $path)) {
        $variables['home_url'] = '/subjects';
        $variables['site_slogan'] = t('Subjects');
    } else if (preg_match("/^places/i", $path)) {
        $variables['home_url'] = '/places';
        $variables['site_slogan'] = t('Places');
    } else {
        $variables['home_url'] = '/';
    }
}

/**
 * Implements template_preprocess_html().
 */
function sarvaka_kmaps_preprocess_html(&$variables) {
    //Add class 'home-carousel' to both homepages of places and subjects
    $path = current_path();
    if ($path === 'subjects' || $path === 'places') {
        $variables['classes_array'][] = 'home-carousel';
    }
}

