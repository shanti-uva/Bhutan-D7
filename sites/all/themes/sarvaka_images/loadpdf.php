<?php

if (isset($_GET['url'])) {
    $url = $_GET['url'];
    $pts = explode('/', $url);
    $filename = array_pop($pts) . ".pdf";
    $data = file_get_contents($url);
     header('Content-type: application/pdf');
     header('Content-Disposition: inline; filename="' . $filename . '"');
     header('Content-Transfer-Encoding: binary');
     header('Accept-Ranges: bytes');
     print $data;
}
