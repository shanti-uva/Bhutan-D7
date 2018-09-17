<?php 
$tagname = 'h' . $depth;
$id = 'node-' . $node->nid;
?><section id="<?php print $id; ?>" class="sec">
  <<?php print $tagname; ?> id="<?php print $id; ?>-title" class="head"><?php print $title; ?></<?php print $tagname; ?>>  
  <?php print $content; ?>
  <?php print $children; ?>
</section>