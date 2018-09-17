<li>
  <a href="<?php print base_path() . $app; ?>"><?php print ucfirst($app); ?>: </a>
</li>
<?php foreach($data as $key => $ancestor): ?>
  <li>
    <a href="<?php print base_path(); ?><?php print $app; ?>/<?php echo $key; ?>/overview/nojs" class="use-ajax"><?php echo $ancestor; ?></a>
    <span class="icon shanticon-arrow3-right"></span>
  </li>
<?php endforeach; ?>
