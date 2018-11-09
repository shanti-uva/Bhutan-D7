<div class="wrap-all">
    <span class="sr-only"><a href=".main-content">Skip to main content</a> <a
                href="#kmaps-search">Skip to search</a></span>

    <?php print render($page['header']); ?>

    <!-- include shanti-explore-menu if it exists -->
    <?php if (module_exists('explore_menu')) {
        print render($variables['explore_menu']);
    } ?>

    <!-- Action Links: Edit, View, etc. -->
    <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>

    <!-- Message Area -->
    <?php if (!empty($messages)) {
        print "<div class=\"messages\">$messages</div>";
    } ?>
    <main class="main-wrapper container-fluid">
        <!-- Search Flyout -->
        <?php if (!empty($page['search_flyout'])): ?>
            <div id="search-flyout" class="region extruder right" role="search" style="display: none;">
                <?php print render($page['search_flyout']); ?>
            </div>

            <!-- BEGIN faceted search results -->
            <section id="faceted-search-results"
                     class="faceted-search-results mandala-sliding-panel right-panel search-flyout-collapsed off"
                     style="display:none;" aria-expanded="false" aria-label="Search Results Sliding Panel">
                <!-- INSERT RESULTS TEMPLATE DATA -->
            </section>
        <?php endif; ?>

        <?php print render($page['banner']); ?>

        <div class="home-teaser-wrapper clearfix">
            <main class="container-fixed">
                <!-- Render Content -->
                <?php print render($page['content']); ?>
            </main>
        </div>

        <section id="menu" class="menu-main" style="display:none;">
            <nav id="menu-drill" role="navigation">
                <?php print $variables['user_menu_links']; ?>
            </nav>
        </section><!-- END menu -->
    </main>
</div> <!-- End wrap-all -->

<?php print render($page['footer']); ?>

<!-- Admin Footer -->
<div id="admin-footer">
    <?php print render($page['admin_footer']); ?>
</div>




