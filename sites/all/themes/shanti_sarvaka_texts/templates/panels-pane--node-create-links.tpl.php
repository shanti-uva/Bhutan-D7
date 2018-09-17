<?php 
	foreach($variables['content']['og_node_create_links']['#items'] as $item) 
	{
		preg_match('/<a href="([^"]+)">([^<]+)<\/a>/',$item['data'],$matches);
		$url  = $matches[1];
		$text = $matches[2];
		$text == 'Book page' ? $text = 'Text' : 1;
		print "<a class='btn btn-primary' href='$url'>Add $text</a>";
	}
?>