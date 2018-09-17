<div class="related-essays">
  <article>
    <h4><?php print isset($data->title) ? $data->title : ""; ?> 
      <small>by 
        <?php foreach($data->authors as $author): ?>
          <?php print $author->fullname; ?>, 
        <?php endforeach; ?>
        (<?php print date('F j, Y', strtotime($data->created_at)); ?>)
      </small>
    </h4>
    <?php print $data->content; ?>
  </article>
</div>