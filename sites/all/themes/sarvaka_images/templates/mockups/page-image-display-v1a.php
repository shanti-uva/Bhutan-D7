<div class="wrap-all">
   <span class="sr-only"><a href=".main-content">Skip to main content</a> <a href="#search-flyout">Skip to search</a></span>
    <!-- Header Region -->
   <div class="site-banner">
    <div class="navbar navbar-default">

        <nav class="navbar-buttons">
          <span class="menu-icon menu-toggle" role="button" aria-label="Main Menu"><a href="#"><span class="sr-only">Main Menu</span><span class="icon shanticon-menu"></span></a></span><!-- desktop > 768 drilldown menu : main-menu -->
          <span class="menu-explore menu-exploretoggle" role="button" aria-label="Explore Collections"><a href="#"><span>Explore</span><span class="icon shanticon-directions"></span></a></span><!-- mobile < 768 : collections -->
        </nav>

        <h1 class="navbar-header<?php if(!$variables['shanti_site']) { print " default"; } ?>">
             <?php if($variables['shanti_site']): ?>
              <a href="<?php echo $mandala_home; ?>" class="logo-brand navbar-brand">
                <span class="icon shanticon-logo"></span>
                <span class="mandala">Mandala <em>Collections</em></span>
                <?php if($variables['use_admin_site_title']) {
                    print "<span class=\"site-title\">{$site_name}</span>";
                }
                ?>
              </a>

            <?php else: ?>
              
              <a href="<?php print $variables['home_url']; ?>" class="navbar-brand" title="<?php print $site_name; ?> Homepage">
              <img src="<?php print $logo; ?>" class="site-logo" />
                <span class="site-title"><?php print $site_name; ?></span>
              </a>
              
            <?php endif; ?>

            <a href="<?php print $variables['home_url']; ?>" class="navbar-brand" title="<?php print $site_name; ?> Homepage">
              <?php if ($site_slogan) {
                    print '<span class="site-slogan">';
                    print $site_slogan;
                    print '</span>';
                    print '<span class="site-slogan development">' . $site_env_context . '</span>';
              }?>
            </a>
        </h1>

        <!-- HEADER REGION -->
        <nav id="sarvaka-header" class="region navbar-collapse collapse navtop"> <!-- desktop display > 768 -->
           <form class="form">
           <fieldset>
            <ul class="nav navbar-nav navbar-right">
                <!-- If admin puts blocks in  header, render here -->
                <?php print render($page['header']);  ?>
            </ul>
           </fieldset>
           </form>
         </nav>
        
     </div><!-- END Navbar -->
     <?php if(module_exists('explore_menu')) { print render($variables['explore_menu']); } ?>

    </div> <!-- End Site-Banner & Header region -->

    <!-- Begin Content Region -->
    <main class="main-wrapper container-fluid">
      <article class="main-content" role="main">

        <!-- BEGIN Image Display Row -->
        <section class="row slider image-display">
            <div class="col-xs-12">

              ADD IMAGE FLEX-SLIDER 

            </div>
        </section>
          
        <!-- BEGIN Details Row -->
        <section class="row image-details"> 
            <div class="col-xs-12">
              <!-- BEGIN Header -->
              <header role="banner">
                <h1> IMAGE TITLE </h1>

                <div class="row">
                    <div class="col-xs-12 col-md-6">
                      <ul>
                        <li> AUTHOR </li>
                        <li> LOCATION </li>
                        <li> COLLECTIONS </li>
                      </ul>
                    </div>

                    <div class="col-xs-12 col-md-6">
                        <P>  DESCRIPTION </P>
                    </div>
                </div> 
              </header><!-- END Header -->


              <section class="row image-details-more">
                <div class="col-xs-12 col-sm-4">
                    <ul>
                      <li> MISC-DATA </li>
                      <li> MISC-DATA </li>
                      <li> MISC-DATA </li>
                    </ul>
                </div>

                <div class="col-xs-12 col-sm-4">
                    <ul>
                      <li> MISC-DATA </li>
                      <li> MISC-DATA </li>
                      <li> MISC-DATA </li>
                    </ul>                  
                </div>

                <div class="col-xs-12 col-sm-4">
                    <ul>
                      <li> MISC-DATA </li>
                      <li> MISC-DATA </li>
                      <li> MISC-DATA </li>
                    </ul>                  
                </div>
              </section>


            </div>
        </section> <!-- END Details Row -->

      </article>











      <!-- Search Flyout -->
      <?php if(!empty($page['search_flyout'])): ?>
        <div id="search-flyout" class="region extruder right" role="search" style="display: none;">
           <?php print render($page['search_flyout']); ?>
        </div>
      <?php endif; ?>

    </main> <!-- End Main Content -->


  <!-- LOAD menus -->
  <section id="menu" class="menu-main" style="display:none;">
    <nav id="menu-drill">
     <?php print $variables['user_menu_links']; ?>
    </nav>
  </section><!-- END menu -->

</div> <!-- End wrap-all -->

<!-- Footer -->
<footer class="footer">
  <div>
    <?php print render($page['footer']); ?>
    <p class="rights">&copy; <?php print date("Y"); ?> All Rights Reserved</p>
  </div>
</footer>

<!-- Admin Footer -->
<div id="admin-footer">
  <?php print render($page['admin_footer']); ?>
</div>