<!-- TODO (samchrisinger): Is this template used? Can we delete it? -->
<?php foreach ($rows as $id => $row): ?>
	<span<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
	<?php print $row; ?>
	</span>
<?php endforeach; ?>
