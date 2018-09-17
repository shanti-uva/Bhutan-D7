<?php

/**
 * @file
 */
?>
<div class="breadcrumb-child-container breadcrumb-dropdown" term_id="<?php print $value['term_id']; ?>">
  <div class="inner-breadcrumb-child-container">
    <div class="breadcrumb-child-top"><?php print $value['all_sources_top_link']?></div>
    <div class="breadcrumb-child-sub-top">
      <ul>
        <li>
          <span class="fancytree-node fancytree-has-children fancytree-exp-c fancytree-ico-c">
            <span class="fancytree-expander glyphicon glyphicon-plus-sign"></span>
            <span class="fancytree-title"><?php print $value['all_sources_sub_top_link']?></span>
          </span>
        </li>
      </ul>
    </div>
    <div class="breadcrumb-child">
      <div class="breadcrumb-tree" data-collection-parent-id="<?php print $value['term_id']; ?>" id="column-<?php print $value['breadcrumb_column_id']; ?>"></div>
    </div>
  </div>
</div>
