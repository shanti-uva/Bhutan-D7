<h4 class="visuals-title"><?php print $title; ?></h4>
<div class="kmaps-visuals-grid">
  <ul class="shanti-gallery">
  <?php foreach($data->docs as $aItem): ?>
    <li class="shanti-thumbnail visual">
      <div class="shanti-thumbnail-image shanti-field-visuals">
        <a href="<?php print base_path() . $app . '/' . $sid . '/visuals/node/' . $aItem->id . '/nojs'; ?>" class="use-ajax shanti-thumbnail-link">
          <span class="overlay"><span class="icon"></span></span>
          <img typeof="foaf:Image" src="<?php print $aItem->url_thumb; ?>" alt="Trumps Acceptance Speech">     
          <span class="icon shanticon-visuals"></span>
        </a>
      </div>
      <!-- End of shanti-thumbnail-image -->
      <div class="shanti-thumbnail-info">
        <div class="body-wrap">
          <div class="shanti-thumbnail-field clearfix shanti-field-title">
            <span class="field-content">
              <a href="<?php print base_path() . $app . '/' . $sid . '/visuals/node/' . $aItem->id . '/nojs'; ?>" class="use-ajax shanti-thumbnail-link">
                <?php print $aItem->title[0]; ?>
              </a>
            </span>
          </div>
          <div class="shanti-thumbnail-field clearfix shanti-field-agent">
            <span rel="sioc:has_creator">
               <?php $u = user_load_by_name($aItem->node_user); print l($u->name, 'user/' . $u->uid);  ?>
            </span>            
          </div>
          <div class="shanti-thumbnail-field clearfix shanti-field-created">
            <span class="shanti-field-content"><?php 
                $ts = strtotime($aItem->node_created);
                $date = format_date($ts, 'short');
                $date = array_shift(explode('-', $date));
                print $date; ?></span>
          </div>
          <div class="shanti-thumbnail-field clearfix shanti-field-type">
            <span class="shanti-field-content"><?php print array_shift(explode(':', $aItem->asset_subtype)); ?></span>
          </div>
        </div>
        <!-- end body-wrap -->
        <div class="footer-wrap">
          <div class="shanti-field-content">
          </div>
        </div>
        <!-- end footer -->
      </div>
      <!-- end shanti-thumbnail-info -->
    </li>
  <?php endforeach; ?>
  </ul>
</div>