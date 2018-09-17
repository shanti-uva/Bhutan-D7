<?php

/**
 * @file
 */
if ($option['key'] == 0): ?>
  <span class="result-item-type <?php print $option['base_class_name']; ?>-group-label"><?php print $option['header_label']; ?></span>
<?php endif; ?>
<span>
  <?php print $option['value']; ?>
  <?php if (!empty($option['year'])): ?>
    <?php print ' ' . $option['year']; ?>
  <?php endif;?>
  <?php if (!empty($option['author'])): ?>
    <?php print '<br/>' . $option['author']; ?>
  <?php endif;?>
</span>
