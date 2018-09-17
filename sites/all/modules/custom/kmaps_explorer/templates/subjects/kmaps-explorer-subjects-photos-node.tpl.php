<div class="related-photos">
  <?php if(count($photo->picture->captions) > 0): ?>
    <p><?php print $photo->picture->captions[0]->title; ?></p>
  <?php endif; ?>
  <figure>
    <img src="<?php print $photo->picture->images[3]->url; ?>">
    <?php if(!empty($photo->picture->photographer)): ?>
      <figcaption><strong>Photographer:</strong> <?php print $photo->picture->photographer->fullname; ?></figcaption>
    <?php endif; ?>
  </figure><br>
  <?php if(!empty($photo->picture->copyrights)): ?>
    <p><strong>Copyright Holder:</strong> <?php print $photo->picture->copyrights[0]->copyright_holder->title; ?></p>
  <?php endif; ?>
  <?php if(!empty($photo->picture->copyrights[0]->reproduction_type)): ?>
    <p><strong>Reproduction Type:</strong> <?php print $photo->picture->copyrights[0]->reproduction_type->title; ?></p>
  <?php endif; ?>
</div>
