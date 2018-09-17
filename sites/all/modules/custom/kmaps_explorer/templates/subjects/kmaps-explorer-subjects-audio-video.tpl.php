<h4><?php print $title; ?></h4>
<ul class="related-audio-video shanti-gallery">
  <?php foreach($data as $aItem): ?>
    <li class="shanti-thumbnail video">
      <div class="shanti-thumbnail-image shanti-field-video">
        <a href="<?php print base_path() . $app . '/' . $main_id . '/audio-video-node/' . $aItem->id . '/nojs'; ?>" class="shanti-thumbnail-link use-ajax">
          <span class="overlay"><span class="icon"></span></span>
          <img src="<?php print $aItem->url_thumb; ?>" alt="Video" typeof="foaf:Image" class="k-no-rotate">
          <span class="icon shanticon-video"></span>
        </a>
      </div>
      <div class="shanti-thumbnail-info">
        <div class="body-wrap">
            <div class="shanti-thumbnail-field shanti-field-title">
              <span class="field-content">
                <a href="<?php print base_path() . $app . '/' . $main_id . '/audio-video-node/' . $aItem->id . '/nojs'; ?>" class="shanti-thumbnail-link use-ajax">
                  <?php if (isset($aItem->title)) { print $aItem->title[0]; } ?>
                </a>
              </span>
            </div>
            <div class="shanti-thumbnail-field shanti-field-created">
              <span class="shanti-field-content">
                <?php print date('F j, Y', strtotime($aItem->node_created)); ?>
              </span>
            </div>
            <?php if(isset($aItem->duration_s)): ?>
            <div class="shanti-thumbnail-field shanti-field-duration">
              <span class="field-content"><?php print $aItem->duration_s; ?></span>
            </div>
            <?php endif; ?>
        </div>
        <div class="footer-wrap">
          <div class="shanti-thumbnail-field shanti-field-group-audience">
            <div class="shanti-field-content">
              <a href="#" class="shanti-thumbnail-link">
                <?php echo isset($aItem->collection_title) ? $aItem->collection_title : ''; ?>
              </a>
            </div>
          </div>
        </div>
      </div>
    </li>
  <?php endforeach; ?>
</ul>
