<div class="related-texts">
  <h4>Texts in <?php print $title; ?></h4>
  <?php foreach($data as $aItem): ?>
    <?php if(isset($aItem->images)): ?>
      <div class="each-text">
        <a href="#pid<?php print $aItem->id; ?>" data-toggle="modal">
          <img src="<?php print $aItem->images[1]->url; ?>" class="img-responsive" alt="<?php print (count($aItem->captions) > 0 ? $aItem->captions[0]->title : ''); ?>">
        </a>
      </div>
      <div class="modal fade" tabindex="-1" role="dialog" id="pid<?php print $aItem->id; ?>">
        <div class="modal-dialog">
          <div class="modal-content">
            <div class="modal-header">
              <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
              <p class="modal-title" id="myModalLabel"><?php print (count($aItem->captions) > 0 ? $aItem->captions[0]->title : ''); ?></p>
            </div>
            <div class="modal-body">
              <img src="<?php print $aItem->images[6]->url; ?>" class="img-responsive" alt="<?php print (count($aItem->captions) > 0 ? $aItem->captions[0]->title : ''); ?>">
              <p><strong>Resource #:</strong> <?php print $aItem->id; ?></p>
            </div>
          </div>
        </div>
      </div>
    <?php endif; ?>
  <?php endforeach; ?>
</div>