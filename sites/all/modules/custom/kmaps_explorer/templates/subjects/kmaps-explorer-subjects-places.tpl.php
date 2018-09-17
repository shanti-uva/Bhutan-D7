<h4><?php print $title; ?> </h4>
<a href="https://subjects.kmaps.virginia.edu/features/<?php echo $kid; ?>.csv" class="btn btn-sm btn-primary kmaps-btn-down">Download</a>
<ul class="related-places places-in-subjects kmaps-list-columns">
  <?php foreach($data as $aItem => $aItemValue): ?>
    <li>
      <span><?php print $aItemValue->header; ?></span>
      <span class="popover-kmaps" data-app="places" data-id="<?php print explode("-", $aItemValue->id)[1]; ?>">
        <span class="popover-kmaps-tip"></span>
        <span class="icon shanticon-menu3"></span>
      </span>
    </li>
  <?php endforeach; ?>
</ul>
