<?php
drupal_add_css(drupal_get_path('theme','shanti_sarvaka_texts') . '/css/shanti_texts_page_all_texts.css');
?>

<!-- VIEW AREA -->
<div class="<?php print $classes; ?>">

	<!-- ATTACHMENT BEFORE -->
	<div class="attachment attachment-before">
		<!-- CONTROLS -->
		<div class="view-all-texts-control-box">
			<div class="view-all-texts-control-box-row clearfix">
				<div class="view-all-texts-control-box-cell-header view-all-texts-control-box-cell col-xs-12 col-sm-12 col-md-4"> 
				<?php print $header; ?>
				</div>
				<div class="view-all-texts-control-box-cell-filters view-all-texts-control-box-cell col-xs-6 col-sm-5 col-md-4">
				<?php print $exposed; ?>
				</div>
				<div class="view-all-texts-control-box-cell-pager view-all-texts-control-box-cell col-xs-6 col-sm-7 col-md-4">
				<?php print $pager; ?>
				</div>
			</div>
		</div>
	</div>
  
	<!-- ROWS -->
  <?php if ($rows): ?>
	<div class="view-content">
		<?php print $rows; ?>
	</div>
  <?php elseif ($empty): ?>
	<div class="view-empty">
		<?php print $empty; ?>
	</div>
  <?php endif; ?>

	<!-- ATTACHMENT AFTER -->
	<div class="attachment attachment-after">
		<?php print $pager; ?>
	</div>

</div><?php /* class view */ ?>
