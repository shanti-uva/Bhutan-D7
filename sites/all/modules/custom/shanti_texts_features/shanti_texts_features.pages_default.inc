<?php
/**
 * @file
 * shanti_texts_features.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function shanti_texts_features_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'front_page';
  $page->task = 'page';
  $page->admin_title = 'Front Page';
  $page->admin_description = 'A front page with slider, etc.';
  $page->path = 'home';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_front_page__template';
  $handler->task = 'page';
  $handler->subtask = 'front_page';
  $handler->handler = 'template';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'Texts',
    'contexts' => array(),
    'relationships' => array(),
    'module' => 'strongarm',
    'theme' => 'shanti_sarvaka_texts',
    'module_or_theme' => 'theme',
    'template' => 'shanti-texts-front-page',
    'template_path' => 'templates',
    'hook_theme' => 1,
    'full_page' => 0,
    'name' => 'template',
    'theme_function' => 'shanti_sarvaka_texts_template_shanti_texts_front_page',
    'base' => 'shanti_sarvaka_texts',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'front',
          'settings' => NULL,
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $page->default_handlers[$handler->name] = $handler;
  $pages['front_page'] = $page;

  $page = new stdClass();
  $page->disabled = TRUE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'front_page_new';
  $page->task = 'page';
  $page->admin_title = 'Front Page';
  $page->admin_description = '';
  $page->path = 'home';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $pages['front_page_new'] = $page;

  return $pages;

}
