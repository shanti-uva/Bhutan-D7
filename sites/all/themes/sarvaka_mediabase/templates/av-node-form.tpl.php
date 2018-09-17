<?php
  /**
	 * av-node-form.tpl.php: a template for audio and video node edit forms
	 * 
	 * called from sarvaka_mediabase_theme for both audio and video nodes
	 * 
	 * variables adjusted by the following functions:
	 *     sarvaka_mediabase_preprocess_video_node_form()
	 *     sarvaka_mediabase_preprocess_audio_node_form()
	 * 
	 * Variables:
	 *    $form: The form itself
	 * 
	 * 
	 */
?>
<div class="mb-av-form">
	<?php
		echo drupal_render_children($form); 
	?>
</div>