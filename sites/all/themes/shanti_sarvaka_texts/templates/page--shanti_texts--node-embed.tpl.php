<?php 
drupal_add_css(drupal_get_path('theme','shanti_sarvaka_texts').'/css/shanti_texts_embed.css');
print drupal_render($page['content']);
?>