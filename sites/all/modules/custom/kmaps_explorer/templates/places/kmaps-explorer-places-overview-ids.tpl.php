<div>
  <p><strong>Place ID</strong>: F<?php print $data->feature->fid; ?></p>
</div>
<?php foreach($data->feature->geo_codes as $geo_code): ?>
<div>
  <p>
    <strong>Geocode Name</strong>: <?php print $geo_code->geo_code_type->name; ?>,
    <strong>Code</strong>: <?php print $geo_code->geo_code_type->code; ?>
  </p>
</div>
<?php endforeach; ?>
