<h4>Subjects Related to <?php print $title; ?> </h4>
<a href="https://places.kmaps.virginia.edu/features/<?php echo $kid; ?>.csv" class="btn btn-sm btn-primary kmaps-btn-down">Download</a>
<div class="subjects-in-places kmaps-list-columns">
  <?php if(count($data) > 0): ?>
    <h6>FEATURE TYPES:</h6>
    <ul>
      <?php foreach($data as $aItem => $aItemValue): ?>
        <li>
          <span><?php print $aItemValue->block_child_type == 'feature_types' ? $aItemValue->feature_type_name_s : $aItemValue->related_subjects_header_s; ?></span>
          <span class="popover-kmaps" data-app="subjects" data-id="<?php print $aItemValue->block_child_type == 'feature_types' ? $aItemValue->feature_type_id_i : $aItemValue->related_subjects_id_i; ?>">
            <span class="popover-kmaps-tip"></span>
            <span class="icon shanticon-menu3"></span>
          </span>
        </li>
      <?php endforeach; ?>
    </ul>
  <?php endif; ?>
</div>
