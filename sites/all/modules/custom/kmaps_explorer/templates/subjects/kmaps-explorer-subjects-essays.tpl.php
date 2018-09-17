<div class="related-essays">
  <?php foreach($data->descriptions as $aItem): ?>
    <article>
      <h6><?php print $aItem->title; ?> 
        <small>by 
          <?php foreach($aItem->authors as $author): ?>
            <?php print $author->fullname; ?>, 
          <?php endforeach; ?>
          (<?php print date('F j, Y', strtotime($aItem->created_at)); ?>)
        </small>
      </h6>
      <?php print $aItem->content; ?>
      <hr>
    </article>
  <?php endforeach; ?>
</div>