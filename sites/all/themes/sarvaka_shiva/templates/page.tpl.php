
<?php
 /**
  * This template is used by the share popup and any other light box popups to display just content without header and footer
  * if ?format=simple, this will be activated
  * otherwise it uses the default page template from shanti sarvaka
  * 
  **/
	if(isset($_GET['format']) && $_GET['format'] == 'simple') {
		print render($variables['page']['content']); 
		return;
	} else {
		include_once(drupal_get_path('theme', 'shanti_sarvaka') . '/templates/page.tpl.php');
	}
?>