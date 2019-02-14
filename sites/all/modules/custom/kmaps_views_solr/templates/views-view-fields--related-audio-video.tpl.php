<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<div class="shanti-thumbnail-image shanti-field-<?php print $fields['asset_type']->content ?>">
  <a href="/<?php print $view->args[0] . '/' . $view->args[1] ?>/audio-video-node/<?php print $fields['av_id']->content ?>/nojs"
     class="shanti-thumbnail-link use-ajax">
    <span class="overlay">
      <span class="icon"></span>
    </span><!--use html entities-->
    <img
      src="<?php if(isset($fields['thumb'])) { print $fields['thumb']->content; } ?>"
      typeof="foaf:Image" class="k-no-rotate">
    <span class="icon shanticon-<?php print $fields['asset_type']->content ?>"></span>
  </a>
</div>
<div class="shanti-thumbnail-info">
  <div class="body-wrap">
    <div class="shanti-thumbnail-field shanti-field-title en">
      <span class="field-content">
        <a href="/<?php print $view->args[0] . '/' . $view->args[1] ?>/audio-video-node/<?php print $fields['av_id']->content ?>/nojs"
          class="shanti-thumbnail-link use-ajax" 
          <?php 
            if (!empty($fields['av_title'])) { echo 'title="' . $fields['av_title']->content . '"';}
          ?>
        >
          <?php print $fields['av_title']->content; ?>
        </a>
      </span>
    </div>

    <?php if (!empty($fields['creator'])): ?>
      <div class="shanti-thumbnail-field shanti-field-creator">
        <span class="shanti-field-content"><?php print $fields['creator']->content; ?></span>
      </div>
    <?php endif; ?>
	      
    <?php if(!empty($fields['duration'])): ?>
      <div class="shanti-thumbnail-field shanti-field-duration">
        <span class="shanti-field-content"> <?php print $fields['duration']->content ?></span>
      </div>
    <?php endif; ?>
          
    <?php if(!empty($fields['location'])): ?>
      <div class="shanti-thumbnail-field shanti-field-place">
        <span class="shanti-field-content"><?php print explode('-', $fields['location']->content)[0] ?></span>
      </div>
    <?php endif; ?>

    <?php if(!empty($fields['language'])): ?>
      <div class="shanti-thumbnail-field shanti-field-languages">
        <span class="shanti-field-content"><?php print $fields['language']->content ?></span>
      </div>
    <?php endif; ?>

    <div class="shanti-thumbnail-field shanti-field-created">
      <span class="shanti-field-content">
        <?php
          if(!empty($fields['created_date'])) {
            print date('d M Y', strtotime($fields['created_date']->content));
          }
        ?>
      </span>
    </div>
  </div> <!-- end body-wrap -->

  <div class="footer-wrap">
    <?php if(!empty($fields['collection'])): ?>
      <div class="shanti-field shanti-field-group-audience">
        <div class="shanti-field-content">
          <a href="#" class="shanti-thumbnail-link">
            <?php print $fields['collection']->content ?>
          </a>
        </div>
      </div>
    <?php endif; ?>
  </div> <!-- end footer -->

</div> <!-- end shanti-thumbnail-info -->