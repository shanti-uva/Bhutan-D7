<?php
   /**
    * Template for the details section of the grid view popdown.
    */
    //dpm($variables);
?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <div class="ppd-details-inner">
        <h2><?php print $title; ?></h2>
        <div class="specs">
            <div class="author"><?php 
                if (!empty($grid_fields['agent'])) { print $grid_fields['agent']; } else { print $name; }
            ?></div><span class="sep"></span><?php
                 if (isset($pixels)) {
                    print '<div class="size">' . $pixels  . '</div><span class="sep"></span>';
                 } else if ($grid_fields['size']) {
                    print '<div class="size">' . $grid_fields['size']  . '</div><span class="sep"></span>';
                }
             ?><div class="date"><?php
                if (!empty($taken_on)) {
                    print $taken_on;
                } else {
                    print $date;
                }?></div><?php
                if (!empty($grid_fields['type'])) {
                    print '<span class="sep"></span><div class="type">' . $grid_fields['type'];  '</div>';
                }
             ?>
        </div>
        <?php  if (!empty($grid_fields['collection'])): ?>
            <div class="collections">
                <span class="icon shanticon-stack"></span>  <?php print $grid_fields['collection']; ?>
            </div>
        <?php endif; ?>
        <?php if (!empty($grid_fields['place'])): ?>
            <div class="kmaps">
                 <div class="place"><span class="icon shanticon-places"></span> <?php print $grid_fields['place']; ?></div>
            </div>
        <?php endif; ?>
        <?php if (!empty($grid_fields['subject'])): ?>
            <div class="kmaps">
                 <div class="subject"><span class="icon shanticon-subjects"></span> <?php print $grid_fields['subject']; ?></div>
            </div>
        <?php endif; ?>
        <div class="description">
          <?php if (!empty($grid_fields['desc'])) { print $grid_fields['desc']; }  else { print t('No description available.') ; }?>
        </div>
        <div class="links">
            <a href="#" class="btn btn-default btn-sm view-btn">Details</a>
            <!--button class="btn btn-default btn-sm details-btn">Details</button-->
        </div>
    </div> <!-- END details inner -->
</div> <!-- END details --> 