
 <?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 * 
 * This was named views-views--media-by-kmap.tpl.php, but want to take out wrapping divs for browse-media 
 *  as well so making this more general (2015-10-28, ndg)
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php foreach ($rows as $id => $row): ?>
     <?php print $row; ?>
<?php endforeach; ?>