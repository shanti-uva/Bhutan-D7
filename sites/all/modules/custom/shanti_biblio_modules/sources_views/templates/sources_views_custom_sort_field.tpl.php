<?php

/**
 * @file
 */
?>
<div class="left-side">
  <div class="sources-search-title-container">
  </div>
</div>
<div class="right-side">
  <div class="detail-level-container">
    <span>Details</span>
    <ul class="detail-level-option">
      <li><a id="short-detail" href="#">Short</a></li>
      <li><a id="medium-detail" class="active" href="#">Medium</a></li>
      <li><a id="long-detail" href="#">Long</a></li>
    </ul>
  </div>
  <div class="custom-sort-container">
    <form id="custom-sort-form" accept-charset="UTF-8">
      <div class="btn-group bootstrap-select form-control form-select ss-select select-wrapper">
        <button type="button" class="btn dropdown-toggle selectpicker btn-default" data-toggle="dropdown" data-id="edit-custom-sort" title="<?php print t('Sort by'); ?>">
          <span class="filter-option pull-left"><?php print t('Sort by'); ?></span>&nbsp;
          <span class="caret"></span>
        </button>
        <div class="dropdown-menu open ">
          <ul class="dropdown-menu inner selectpicker">
            <li rel="default" class="selected"><a tabindex="0"><span class="text"><?php print t('Sort by'); ?></span><span class="glyphicon glyphicon-ok icon-ok check-mark"></span></a></li>
          </ul>
          <label>Title</label>
            <ul class="dropdown-menu inner selectpicker">
              <li rel="title_asc"><a tabindex="0"><span class="text">A-Z</span><span class="glyphicon glyphicon-ok icon-ok check-mark"></span></a></li>
              <li rel="title_desc"><a tabindex="0"><span class="text">Z-A</span><span class="glyphicon glyphicon-ok icon-ok check-mark"></span></a></li>
            </ul>
          <label>Author</label>
            <ul class="dropdown-menu inner selectpicker">
              <li rel="author_asc"><a tabindex="0"><span class="text">A-Z</span><span class="glyphicon glyphicon-ok icon-ok check-mark"></span></a></li>
              <li rel="author_desc"><a tabindex="0"><span class="text">Z-A</span><span class="glyphicon glyphicon-ok icon-ok check-mark"></span></a></li>
            </ul>
          <label>Year</label>
            <ul class="dropdown-menu inner selectpicker">
              <li rel="year_asc"><a tabindex="0"><span class="text"><?php print $value['publish_year_asc']; ?></span><span class="glyphicon glyphicon-ok icon-ok check-mark"></span></a></li>
              <li rel="year_desc"><a tabindex="0"><span class="text"><?php print $value['publish_year_desc']; ?></span><span class="glyphicon glyphicon-ok icon-ok check-mark"></span></a></li>
            </ul>
        </div>
      </div>
    </form>
  </div>
</div>
