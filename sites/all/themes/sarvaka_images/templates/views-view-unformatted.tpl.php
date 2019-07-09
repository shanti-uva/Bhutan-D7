<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */

?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<ul <?php if (!strstr($view->name, '_search')) { print 'class="shanti-no-wookmark"'; }?>>
    <?php foreach ($rows as $id => $row): ?>
        <?php if (strstr($view->name, '_search')): ?>
            <li<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
        <?php endif; ?>
        
            <?php print $row; ?>
            
        <?php if (strstr($view->name, '_search')): ?>
            </li>
        <?php endif; ?>
    <?php endforeach; ?>
</ul>
