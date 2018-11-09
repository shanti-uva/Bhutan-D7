<?php
   /**
    * Template for the details section of the grid view popdown.
    */
    //dpm($variables);
    //print implode(", ", array_keys($variables));
?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <div class="ppd-details-inner">
        <h2><?php print $title; ?></h2>
        <div class="specs">
            <div class="author"></div>
            <?php print drupal_render($content); ?>
        </div>
        <div class="links">
            <a href="\node\<?php print $node->nid; ?>" class="btn btn-default btn-sm view-btn">Details</a>
        </div>
        <!--div class="description">
             </div-->
    </div> <!-- END details inner -->
</div> <!-- END details --> 