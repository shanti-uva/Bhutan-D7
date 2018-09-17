<?php

/**
 * @file
 */
?>
<div class="library-dropdown breadcrumb-dropdown" term_id="all">
  <div class="inner-library">
    <div class="home-link-container">
      <?php print l(t('HOME'), $GLOBALS['base_url']); ?>
    </div>
    <div class="view-all-library-container">
      <?php print $value['all_source_link']; ?>
    </div>
    <div class="breadcrumb-tree" id="column-all-sources"></div>
  </div>
</div>
