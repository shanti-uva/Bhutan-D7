<?php

/**
 * @file
 * Default theme implementation to display a file.
 *
 * Available variables:
 * - $label: the (sanitized) file name of the file.
 * - $content: An array of file items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The file owner's picture from user-picture.tpl.php.
 * - $date: Formatted added date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $timestamp
 *   variable.
 * - $name: Themed username of file owner output from theme_username().
 * - $file_url: Direct URL of the current file.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_file().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - file-entity: The current template type, i.e., "theming hook".
 *   - file-[type]: The current file type. For example, if the file is a
 *     "Image" file it would result in "file-image". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - file-[mimetype]: The current file's MIME type. For exampe, if the file
 *     is a PNG image, it would result in "file-image-png"
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $file: Full file object. Contains data that may not be safe.
 * - $type: File type, i.e. image, audio, video, etc.
 * - $uid: User ID of the file owner.
 * - $timestamp: Time the file was added formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   listings.
 * - $id: Position of the file. Increments each time it's output.
 *
 * File status variables:
 * - $view_mode: View mode, e.g. 'default', 'full', etc.
 * - $page: Flag for the full page state.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the file a corresponding
 * variable is defined, e.g. $file->caption becomes $caption. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language, e.g. $file->caption['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_file_entity()
 * @see template_process()
 *
 * @ingroup themeable
 */

?>
<div id="<?php print $id; ?>" class="<?php print $classes ?>"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $file_url; ?>"><?php print $label; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($display_submitted): ?>
    <div class="submitted">
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>

  <div class="file-content"<?php print $content_attributes; ?>>
      
      <section class="content-section">
	  <!-- Nav tabs -->
	  <!--<ul class="nav nav-tabs" role="tablist">--></ul>
      <ul class="nav nav-tabs" role="tablist">
	    <li role="presentation" class="active"><a href="#pdf" aria-controls="pdf" role="tab" data-toggle="tab">PDF</a></li>
	    <li role="presentation"><a href="#metadata" aria-controls="info" role="tab" data-toggle="tab">Metadata</a></li>
	    <li role="presentation"><a href="#info" aria-controls="info" role="tab" data-toggle="tab">Info</a></li>
	  </ul>
	
  
	  <!-- Tab panes -->
		  <div class="tab-content">
		    <div role="tabpanel" class="tab-pane iframe active" id="pdf">
		    	<div class="pdfextlink"><a href="<?php print $iframe_url; ?>" target="_blank"> <?php print t('View in Separate Window') ?></a></div>
	  			<iframe class="pdf-frame" title="PDF in IFrame" src="<?php print $iframe_url; ?>" width="100%" height="800"></iframe>
		    </div>
		    <div role="tabpanel" class="tab-pane" id="metadata">
		    	<div class="file-ss-div file-ss-info">
				    <?php
				      print $ssmetadata;
				    ?>
			    </div>
				</div>
		    <div role="tabpanel" class="tab-pane" id="info">
		    	<div class="file-ss-div file-ss-info">
				    <?php
				      // We hide the links now so that we can render them later.
				      hide($content['links']);
							hide($content['file']);
				      //print render($content);
							print $ssfields;
				    ?>
				  </div>
				</div>
		  </div>
		</section>
  </div>

  <?php print render($content['links']); ?>

</div>
