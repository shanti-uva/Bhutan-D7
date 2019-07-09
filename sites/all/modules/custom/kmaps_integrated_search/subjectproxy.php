<?php
$sserv = 'http://subjects.kmaps.virginia.edu';
if (isset($_GET['server']) && strpos($_GET['server'], 'http://') > -1) {
	$sserv = $_GET['server'];
}
$url = $sserv . '/features/fancy_nested.json';
$cnt = file_get_contents($url);
header('Content-Type: application/json'); 
print '[{"key": "1", "title": "Subjects", "children": ' . $cnt . ', "server":"' . $sserv . '"}]';
?>
