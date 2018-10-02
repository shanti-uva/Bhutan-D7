<div class="wrap-all">
	<span class="sr-only"><a href=".main-content">Skip to main content</a> <a href="#kmaps-search">Skip to search</a></span>
	
	<?php print render($page['header']); ?>
	
  <!-- include shanti-explore-menu if it exists -->
  <?php if(module_exists('explore_menu')) { print render($variables['explore_menu']); } ?>
  
	<!-- Action Links: Edit, View, etc. -->
	<?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>

  <!-- Message Area -->
  <?php if (!empty($messages)) { print "<div class=\"messages\">$messages</div>"; } ?>

	<?php print render($page['banner']); ?>
	
  <div class="home-teaser-wrapper clearfix">  
	  <main class="container-fixed">
	  		<!-- Render Content -->
      	<?php 
      		print render($page['content']); 
      	?>
	  </main>
  </div>

  <section id="menu" class="menu-main" style="display:none;">
    <nav id="menu-drill" role="navigation">
     <?php print $variables['user_menu_links']; ?>
    </nav>
  </section><!-- END menu -->

</div> <!-- End wrap-all -->

<?php print render($page['footer']); ?>

<!-- Admin Footer -->
<div id="admin-footer">
  <?php print render($page['admin_footer']); ?>
</div>




