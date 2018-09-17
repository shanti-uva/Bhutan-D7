<?php

function bulk_image_import_read_xml_streaming($file) {
  $reader = new XMLReader;
  $reader->open($file);

  while ($reader->read()) {
    if ($reader->name == 'Catalog' && $reader->nodeType == XMLReader::ELEMENT) {
      yield 'catalog' => $reader->readInnerXML();
    }
    if ($reader->name == 'MediaItem' && $reader->nodeType == XMLReader::ELEMENT) {
      yield 'item' => $reader->readOuterXML();
      $reader->next('MediaItem');
    }
  }
  $reader->close();
}
