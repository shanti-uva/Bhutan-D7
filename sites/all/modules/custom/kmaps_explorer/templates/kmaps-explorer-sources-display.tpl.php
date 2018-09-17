<h4 class="sources-title"><?php print $title; ?></h4>
<div class="kmaps-sources-summary">
  <ul class="summary-list">
  <?php foreach($data->docs as $aItem): ?>
    <li>
      <span class="icon shanticon-essays"></span>
      <a href="<?php print base_path() . $app . '/' . $sid . '/sources/node/' . $aItem->id . '/nojs'; ?>" class="use-ajax">
        <?php print $aItem->title ? $aItem->title[0] : $aItem->caption; ?>
      </a>
    </li>
  <?php endforeach; ?>
  </ul>
</div>