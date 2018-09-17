<div id='myTabs'>
  <ul class='nav nav-tabs' role="tablist">
    <li role="presentation" class="active">
      <a href='#relation_tree' aria-controls="profile" role="tab" data-toggle="tab" aria-expanded="true">Relationships</a>
    </li>
    <li role="presentation">
      <a id="summary-tab-link" href='#relation_details' aria-controls="home" role="tab" data-toggle="tab" aria-expanded="false">Summary</a>
    </li>
  </ul>
</div>
<div class='tab-content'>
  <div class='tab-pane active' role="tabpanel" id="relation_tree">
    <section class='panel panel-content'>
      <div class='panel-body'>
        <p>
           <strong><span class="latin"><?php echo $title ?></span></strong> has <strong class="relatedCountContainer"><?php echo $places_in_places_count ?></strong> subordinate <?php echo pluralize(intval($places_in_places_count), 'place') ?>. You can browse <?php echo pluralize(intval($places_in_places_count), 'this', 'those') ?> subordinate <?php echo pluralize(intval($places_in_places_count), 'place') ?> as well as its superordinate places with the tree below. See the summary tab if you instead prefer to view only its immediately subordinate places grouped together in useful ways, as well as places non-hierarchically related to it.
        </p>
        <div class='relation_tree_container'></div>
      </div>
    </section>
  </div>
  <div class='tab-pane' role="tabpanel" id="relation_details">
    <section class='panel panel-content'>
      <div class='panel-body'>
          <p>
              <strong><span class="latin"><?php echo $title ?></span></strong> has <strong class="relatedCountContainer"><?php echo $original_places_count ?></strong> other <?php echo pluralize(intval($original_places_count), 'place') ?> directly related to it, which <?php echo pluralize(intval($original_places_count), 'is', 'are') ?> presented here. See the relationships tab if you instead prefer to browse  all subordinate and superordinate places for <span class="latin"><?php echo $title ?></span>.
          </p>
          <div class='tab-content-loading' style="display:none">Loading...</div>
          <div class="collapsible_btns_container" style="display:none" >
              <h5> <span class="collapsible_all_btn collapsible_expand_all">Expand all</span> / <span class="collapsible_all_btn collapsible_collapse_all">Collapse all</span></h5>
          </div>
          <a href="https://places.kmaps.virginia.edu/features/<?php echo $kid; ?>.csv" class="btn btn-sm btn-primary kmaps-btn-down">Download</a>
          <div class="places-in-places kmaps-list-columns related-features-categories has-ajax-pagination has-hash-feature-links"></div>
          <div class="collapsible_btns_container" style="display:none">
              <h5> <span class="collapsible_all_btn collapsible_expand_all">Expand all</span> / <span class="collapsible_all_btn collapsible_collapse_all">Collapse all</span> </h5>
          </div>
          <br />
      </div><!--End of .panel-body -->
    </section>
  </div>
</div>