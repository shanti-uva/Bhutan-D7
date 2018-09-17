<h4><?php print $title; ?></h4>
<div class="kmaps-list-columns">
<ul class="texts-list">
<?php foreach($data->doclist->docs as $aItem): ?>
  <li>
    <a href="<?php print base_path() . $app . '/' . $sid . '/' . 'text_node/' . $aItem->id . '/nojs'; ?>" class="use-ajax">
      <?php print (isset($aItem->title) && !empty($aItem->title)) ? $aItem->title[0] : $aItem->caption; ?>
    </a>
  </li>
<?php endforeach; ?>
</ul>
</div>