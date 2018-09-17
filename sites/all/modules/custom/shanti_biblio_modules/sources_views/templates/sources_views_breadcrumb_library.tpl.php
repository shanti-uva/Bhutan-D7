<?php

/**
 * @file
 */
?>
<div class="library-dropdown">
  <div class="inner-library">
    <div class="home-link-container">
      <?php print l(t('HOME'), $GLOBALS['base_url']); ?>
    </div>
    <div class="view-all-library-container">
      <?php print $value['all_source_link']; ?>
    </div>
    <?php print $value['library_list']; ?>
  </div>
</div>
