<?php

/**
 * @file
 * Shanti grid view gallery template based on views-view-unformated.tpl.php
 *
 */

?>
<div class="shanti-view-dom-id" <?php if(isset($variables['dom_id'])) print 'data-dom-id="' . $variables['dom_id'] . '"'; ?>>
    <?php if (!empty($view->introtext)): ?>
         <div class="shanti-view-intro">
             <?php print $view->introtext; ?>
         </div>
    <?php endif; ?>
    <div class="shanti-filters clearfix">
        <div class="control-box-cell-header col-xs-12 col-md-3">
            <?php if (!empty($header)) { print $header; }?>
        </div>
        
        <div class="control-box-cell-filters col-xs-12 col-md-5" >
            <?php if (!empty($exposed)): ?>
                <div class="view-filters-mb">
                <?php if (!empty($exposed))  { print $exposed; } ?>
                </div>
            <?php endif;?>
        </div>
        
        <?php if (!empty($rows) && !empty($pager)): ?>
            <div class="control-box-cell-pager col-xs-6 col-md-4">
                <?php if (!empty($pager)) { print $pager; }?>
            </div>        
        <?php endif; ?>
    </div>     
    
    <div class="<?php print $classes; ?> clearfix">
        <?php print render($title_prefix); ?>
        <?php if ($title): ?>
            <?php print $title; ?>
        <?php endif; ?>
        <?php print render($title_suffix); ?>
        
        <?php if (!empty($attachment_before)): ?>
            <div class="attachment attachment-before">
                <?php print $attachment_before; ?>
            </div>
        <?php endif; ?>
        
        <?php if (!empty($rows)): ?>
            <!-- PIG wrapper -->
            <div class="ppg-wrapper">
                <div id="ppg-grid"></div><!-- End of #ppd-grid -->
            </div> <!-- End of PIG wrapper-->
            
            <!-- Photoswipe DIV was here -->
        <?php else: ?>
            <div class="view-empty">
                <?php
                    if (!empty($view->empty['area']->options['content'])) {
                        print $view->empty['area']->options['content'];
                    }
                ?>
            </div>
        <?php endif; ?>
        
        <?php if (!empty($attachment_after)): ?>
            <div class="attachment attachment-after">
                <?php print $attachment_after; ?>
            </div>
        <?php endif; ?>
        
        <?php if (!empty($more)): ?>
            <?php print $more; ?>
        <?php endif; ?>
        
        <?php if (!empty($footer)): ?>
            <div class="view-footer">
                <?php print $footer; ?>
            </div>
        <?php endif; ?>
        
        <?php if (!empty($feed_icon)): ?>
            <div class="feed-icon">
                <?php print $feed_icon; ?>
            </div>
        <?php endif; ?>
    
    </div><?php /* class view */ ?>
    
    <?php if (!empty($rows) && !empty($pager)): ?>
        <div class="shanti-filters bottom">
            <?php print $pager; ?>
        </div>
    <?php endif; ?>
</div>
     
    