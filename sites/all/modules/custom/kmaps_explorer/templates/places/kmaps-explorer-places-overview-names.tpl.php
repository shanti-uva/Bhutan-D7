<ul>
  <?php foreach($data->names as $val1): ?>
    <li><?php print $val1->name; ?> (<?php print $val1->language->name; ?>, <?php print $val1->writing_system->name; ?>, <?php print $val1->relationship->name; ?>)</li>
    <?php if(count($val1->names) > 0): ?>
      <ul>
        <?php foreach($val1->names as $val2): ?>
          <li><?php print $val2->name; ?> (<?php print $val2->language->name; ?>, <?php print $val2->writing_system->name; ?>, <?php print $val2->relationship->name; ?>)</li>
          <?php if(count($val2->names) > 0): ?>
            <ul>
              <?php foreach($val2->names as $val3): ?>
                <li><?php print $val3->name; ?> (<?php print $val3->language->name; ?>, <?php print $val3->writing_system->name; ?>, <?php print $val3->relationship->name; ?>)</li>
              <?php endforeach; ?>
            </ul>
          <?php endif; ?>
        <?php endforeach; ?>
      </ul>
    <?php endif; ?>
  <?php endforeach; ?>
</ul>
