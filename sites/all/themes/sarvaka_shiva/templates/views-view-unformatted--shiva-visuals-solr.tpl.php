<?php 
  
 /**
 * @file
 *Takes default simple view template to display a list of rows and removes wrapping div
 *
 * @ingroup views_templates
 */
?>
<?php foreach ($rows as $id => $row): ?>
  <?php print $row; ?>
<?php endforeach; ?>