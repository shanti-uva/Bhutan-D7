<!-- Header Region from region--header.tpl.php -->
<div class="site-banner">
	<div class="navbar navbar-default">
		
    <nav class="navbar-buttons">
      <span class="menu-icon menu-toggle"><a href="#"><span class="sr-only">Main Menu</span><span class="icon shanticon-menu"></span></a></span><!-- desktop > 768 drilldown menu : main-menu -->
      <span class="menu-explore menu-exploretoggle" role="button" aria-label="Explore Collections"><a href="#"><span>Explore</span><span class="icon shanticon-directions"></span></a></span><!-- mobile < 768 : collections -->
    </nav>

    <h1 class="navbar-header<?php if(!$variables['shanti_site']) { print " default"; } ?>">
      <a href="<?php print $variables['home_url']; ?>" class="navbar-brand" title="<?php print $site_name; ?> Homepage">
        <span class="logo"><img src="<?php print $logo; ?>" class="site-logo" rel="<?php print $site_name; ?>"/></span> 
        <span class="site-title sr-only"><?php print $site_name; ?></span>
      </a>
    </h1>

    <nav id="sarvaka-header" class="region navbar-collapse collapse navtop"> <!-- desktop display > 768 -->
       <form class="form">
	       <fieldset>
	        <ul class="nav navbar-nav navbar-right">
	            <!-- If admin puts blocks in  header, render here -->
							<?php if ($content) { print $content; } ?>
	        </ul>
	       </fieldset>
       </form>
     </nav>
      <!-- include shanti-explore-menu if it exists this is hidden until explore button clicked -->
     <?php if(module_exists('explore_menu')) { print render($variables['explore_menu']); } ?>    
 </div>
</div>
<!-- End of Header Region -->
