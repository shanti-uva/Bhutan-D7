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
              <!-- Message Area -->
              <?php if (!empty($messages)) { print "<div class=\"messages\">$messages</div>"; } ?>

              <!-- Begin Page Content -->
              <section class="content-section clearfix image-display-wrapper <?php if (!empty($bsclass_main)) { print " $bsclass_main"; } ?> ">
                    <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
                    <?php print render($page['content']); ?>
                    <!-- Page content (or node--shanti-image.tpl.php) will display sections for Display Row and Details Row -->
              </section><!-- End Page Content Section -->
          </article><!-- End of Main Content article -->

          <?php if(!empty($page['search_flyout'])): ?>
             <!-- Search Flyout -->
            <div id="search-flyout" class="region extruder right" role="search" style="display: none;">
               <?php print render($page['search_flyout']); ?>
            </div> <!-- End of Search Flyout -->

            <!-- BEGIN faceted search results -->
            <section id="faceted-search-results" class="faceted-search-results mandala-sliding-panel right-panel search-flyout-collapsed off" style="display:none;" aria-expanded="false" aria-label="Search Results Sliding Panel">
                <!-- INSERT RESULTS TEMPLATE DATA -->
            </section>
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
