<section id="kmaps-search" role="search">
  <!-- BEGIN Input section -->
  <section class="input-section" style="display:none;">
    <form class="form">
      <fieldset>
        <div class="search-group">
          <?php print render($search); ?>
          <div class="form-group">
            <a class="advanced-link toggle-link show-advanced" href="#">
              <span class="icon"></span>
              Advanced
            </a>
          </div>
        </div>
        <?php if (count($filters) > 0): ?>
          <section class="advanced-view">
            <div class="search-filters">
              <?php print render($filters); ?>
            </div>
          </section>
        <?php endif; ?>
      </fieldset>
    </form>
  </section> <!-- END input section -->
  <!-- BEGIN view section -->
  <section class="view-section">
    <ul class="nav nav-tabs">
      <li class="treeview active">
        <a href=".treeview" data-toggle="tab"><span class="icon shanticon-tree"></span>Browse <?php print ucfirst($domain); ?></a>
      </li>
      <li class="listview">
        <a href=".listview" data-toggle="tab"><span class="icon shanticon-list"></span>Results</a>
      </li>
    </ul>
    <div class="tab-content">
      <!-- TAB - tree view -->
      <div class="treeview tab-pane active">
        <div id="tree" class="view-wrap"><!-- view-wrap controls tree container height --></div>
      </div>
      <!-- TAB - list view -->
      <div class="listview tab-pane">
        <div class="view-wrap"> <!-- view-wrap controls container height -->
        </div>
      </div>
    </div>
  </section><!-- END view section -->
</section><!-- END kmaps-search -->
