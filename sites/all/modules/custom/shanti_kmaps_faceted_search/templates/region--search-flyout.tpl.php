<?php
/**
 * Created by PhpStorm.
 * User: ys2n
 * Date: 2/15/18
 * Time: 4:35 PM
 */
?>
<?php if ($content): ?>
  <span id="btn-collapse-flyout" class="icon shanticon-arrow-end-right btn-collapse-flyout" type="button" aria-label="Collapse Search Flyout"></span>
  <div class="<?php print $classes; ?>">
    <?php print $content; ?>
  </div>
<?php endif; ?>
