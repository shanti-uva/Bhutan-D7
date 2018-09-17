<?php

/**
 * @file
 * View template for shanti gallery of thumbnails
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

<ul<?php if ($css_class) { print ' class="' . $css_class .'"';  } ?>>
	 <?php print $rows; ?>
</ul>