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
 * Available Fields for Visuals: 
 * 	nid, field_image, title, shivanode_element_type, shivanode_subtype, created, author_field_lname
 * 
 * @ingroup views_templates
 */
 
 //dpm($fields['title'], 'title object');
?>
<li class="shanti-thumbnail visual">
  <div class="shanti-thumbnail-image shanti-field-visuals nid-<?php print $fields['nid']->content; ?>">
    <a href="<?php print url('node/' . $fields['nid']->content); ?>" class="shanti-thumbnail-link">
    	 <span class="overlay"><span class="icon"></span></span>
       <?php print $fields['field_image']->content; ?>
       <span class="icon shanticon-visuals"></span>
    </a>
  </div> <!-- End of shanti-thumbnail-image -->
  
  <div class="shanti-thumbnail-info">
		<div class="body-wrap">
			<div class="shanti-thumbnail-field clearfix shanti-field-title">
				<span class="field-content"><a href="<?php print url('node/' . $fields['nid']->content); ?>" class="shanti-thumbnail-link"><?php print $fields['title']->content; ?></a></span>
			</div>
            
			<div class="shanti-thumbnail-field clearfix shanti-field-creator">
				<span class="shanti-field-content"><?php  print $fields['author_field_lname']->content; ?></span>
			</div>
			<div class="shanti-thumbnail-field clearfix shanti-field-created">
				<span class="shanti-field-content"><?php  print $fields['created']->content; ?></span>
			</div>
			
            <div class="shanti-thumbnail-field clearfix shanti-field-type">
                <span class="shanti-field-content"><?php  print $fields['shivanode_subtype']->content; ?></span>
            </div>
		     
		</div> <!-- end body-wrap -->

		<div class="footer-wrap">
		    <div class="shanti-thumbnail-field clearfix shanti-field-collection">
		        <span class="shanti-field-content"><?php print $fields['coll']; ?></span>
		    </div>
		</div> <!-- end footer -->
	</div> <!-- end shanti-thumbnail-info -->
</li> <!-- end shanti-thumbnail -->

