<?php

/**
 * @file
 */
?>
<div class="custom-pager">
  <div class="custom-pager-left">
    <span class="count">Displaying <?php print $value['current_row_list']; ?> of <?php print $value['total_items']; ?> sources</span>
  </div>
  <div class="custom-pager-right">
    <ul class="pager">
      <li class="pager-first first"><?php print ($value['first_page_link']) ? $value['first_page_link'] : '<span class="icon"></span>'; ?></li>
      <li class="pager-previous "><?php print ($value['prev_page_link']) ? $value['prev_page_link'] : '<span class="icon"></span>'; ?></li>
      <li class="pager-item">Page</li>
      <li class="pager-item widget active"><input type="text" name="pager-input" id="pager-input" value="<?php print $value['current_page']; ?>"/></li>
      <li class="pager-item">of &nbsp;<?php print $value['max_page']; ?></li>
      <li class="pager-next active"><?php print ($value['next_page_link']) ? $value['next_page_link'] : '<span class="icon"></span>'; ?></li>
      <li class="pager-last last active"><?php print ($value['last_page_link']) ? $value['last_page_link'] : '<span class="icon"></span>'; ?></li>
    </ul>
  </div>
  <input type="hidden" value="<?php print $value['max_page']; ?>" id="max-page-input">
</div>
