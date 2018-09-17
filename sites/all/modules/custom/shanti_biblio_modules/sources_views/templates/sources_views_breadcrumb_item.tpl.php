<?php

/**
 * @file
 */
?>
<div class="breadcrumb-item non-default-item <?php print $value['current_breadcrumb_class']; ?>">
  <?php if(count($value) <= 2): ?>
    <?php print $value['term_name']; ?>
  <?php else: ?>
    <?php print $value['term_name_link']; ?>
    <div class="breadcrumb-child-container">
      <div class="inner-breadcrumb-child-container">
        <div class="breadcrumb-child-top"><?php print $value['all_sources_top_link']?></div>
        <div class="breadcrumb-child-sub-top"><?php print $value['all_sources_sub_top_link']?></div>
        <div class="breadcrumb-child"><?php print $value['breadcrumb_term_child']?></div>
      </div>
    </div>
  <?php endif; ?>
</div>
