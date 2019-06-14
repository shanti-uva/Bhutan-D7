<div class="front-list clearfix">
  <div class="front-pager"><?php echo count($data) > 0 ? $pager : ''; ?></div>
  <div class="list-contents">
    <?php if (count($data) === 0): ?>
      <div class="no-results">
        No Results Found. Please refine your search.
      </div>
    <?php endif; ?>
    <?php foreach($data as $place): ?>
    
    <div class="place">
      <div class="place-link">
        <span class="icon shanticon-<?php echo $app; ?>"></span>
          <div class="place-title-wrapper">
            <a class="place-title" href="/<?php echo $app; ?>/<?php echo explode('-', $place->id)[1]; ?>/overview/nojs"><strong><?php echo $place->header; ?></strong></a>  
            <span>
              <?php if ($app === 'places'): ?>
                <?php echo $place->feature_types[0]; ?>
              <?php endif; ?>
            </span>
          </div>
        <span class="parents-path">
          <?php $toEnd = count($place->ancestors); ?>
            <?php foreach($place->ancestors as $key => $ancestor): ?>
              <a href="/<?php echo $place->tree . '/' . $place->ancestor_ids_generic[$key]; ?>/overview/nojs">
                <?php echo $ancestor; ?>
              </a> <?php if (0 !== --$toEnd): ?>&gt;<?php endif; ?>
            <?php endforeach; ?>
        </span>
        <span class="landing-popover open-task icon shanticon-plus" data-app="<?php echo $app; ?>" data-id="<?php echo explode('-', $place->id)[1]; ?>"></span>
      </div>
      <div class="pop-content closeup place-open-<?php echo explode('-', $place->id)[1]; ?>"></div>
    </div>
    <?php endforeach; ?>
  </div>
  <div class="front-pager"><?php echo count($data) > 0 ? $pager : ''; ?></div>
</div>