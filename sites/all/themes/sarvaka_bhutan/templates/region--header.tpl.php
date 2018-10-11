<!-- Header Region from region--header.tpl.php -->
<div class="site-banner">
	<div class="navbar navbar-default">
		
    <nav class="navbar-buttons">
      <span class="menu-icon menu-toggle"><a href="#"><span class="sr-only">Main Menu</span><span class="icon shanticon-menu"></span></a></span><!-- desktop > 768 drilldown menu : main-menu -->
    </nav>

    <h1 class="navbar-header<?php if(!$variables['shanti_site']) { print " default"; } ?>">
      <a href="<?php print $variables['home_url']; ?>" class="navbar-brand" title="<?php print $site_name; ?> Homepage">
        <span class="logo"><img src="<?php print $logo; ?>" class="site-logo" /></span> 
        <span class="site-title"><?php print $site_name; ?></span>
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
