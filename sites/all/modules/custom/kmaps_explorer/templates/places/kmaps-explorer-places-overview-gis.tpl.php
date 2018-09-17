<?php if(!empty($data->feature->resources)): ?>
  <h4>GIS Resources (feature alone)</h4>
  <ul>
    <li><a href="<?php print $data->feature->resources->gml_url; ?>" target="_blank">GML</a></li>
    <li><a href="<?php print $data->feature->resources->kml_url; ?>" target="_blank">KML</a></li>
    <li><a href="<?php print $data->feature->resources->shapefile_url; ?>" target="_blank">Shapefile</a></li>
  </ul>
<?php endif; ?>
<?php if(!empty($data->feature->resources_contained)): ?>
  <h4>GIS Resources (including contained features)</h4>
  <ul>
    <li><a href="<?php print $data->feature->resources_contained->gml_url; ?>" target="_blank">GML</a></li>
    <li><a href="<?php print $data->feature->resources_contained->kml_url; ?>" target="_blank">KML</a></li>
    <li><a href="<?php print $data->feature->resources_contained->shapefile_url; ?>" target="_blank">Shapefile</a></li>
  </ul>
<?php endif; ?>
