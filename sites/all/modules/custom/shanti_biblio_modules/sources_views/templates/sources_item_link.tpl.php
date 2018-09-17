<?php

/**
 * @file
 */
if ($item): ?>
  <span class="fancytree-node <?php print $item['parent_class_name']; ?> fancytree-exp-e fancytree-ico-e">
    <span class="fancytree-expander glyphicon glyphicon-plus-sign"></span>
    <span class="fancytree-title"><?php print $item['link']; ?></span>
  </span>        
<?php endif; ?>
