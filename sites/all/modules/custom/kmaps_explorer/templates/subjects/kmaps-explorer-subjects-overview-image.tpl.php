<div class="resource-overview-image">
  <figure class="cap-bot">
    <img src="<?php print preg_replace('/^http:/i', 'https:', $data->picture->images[6]->url); ?>"
    alt="<?php print (count($data->picture->captions) > 0 ? $data->picture->captions[0]->title : ''); ?>">
    <figcaption>
      <?php if(false && count($data->picture->captions) > 0): ?>
        <div class="center-caption"><?php print $data->picture->captions[0]->title; ?></div>
      <?php endif; ?>
      <?php if(count($data->picture->descriptions) > 0): ?>
        <?php //print truncate($data->picture->descriptions[0]->title, 50) ?>
      <?php endif; ?>
    </figcaption>
  </figure>
</div>