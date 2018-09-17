<div class="overview-top-collection clearfix">
    <?php print $places_overview_image; ?>

    <?php if (count($node_data->feature_types) > 0): ?>
      <div class="feature-type-wrapper">
        <h6 class="custom-inline">Feature Type:</h6>
        <?php foreach($node_data->feature_types as $key => $name): ?>
          <span><?php print $name; ?></span>
          <span class="popover-kmaps" data-app="subjects" data-id="<?php print $node_data->feature_type_ids[$key]; ?>">
            <span class="popover-kmaps-tip"></span>
            <span class="icon shanticon-menu3"></span>
          </span>
        <?php endforeach; ?>
      </div>
    <?php endif; ?>

    <?php if (count($node_data->summary_eng) > 0): ?>
        <div class="summary-overview"><?php print $node_data->summary_eng[0]; ?></div>
    <?php endif; ?>
</div>

<?php if(isset($node_data->closest_fid_with_shapes)): ?>
  <div class="map-renditions">
    <div id="map-canvas">
    </div>
    <div class="openlayermap">
      <iframe sandbox="allow-forms allow-scripts allow-same-origin" width="100%" height="600" frameborder="0" data-src="https://www.thlib.org/places/maps/interactive_ajax/#fid:<?php print $node_data->closest_fid_with_shapes; ?>" src="about:blank">
      </iframe>
    </div>
    <div class="btn-group btn-group-gmaps">
      <button class="btn btn-default renderGmaps active">Google Map</button>
      <button class="btn btn-default renderOpenLayerMaps">Custom Map</button>
    </div>
  </div>
<?php endif; ?>

<div class="panel-group" id="accordion">
  <section class="panel panel-default">
    <div class="panel-heading">
      <h6>
        <a href="#collapseOne" data-toggle="collapse" data-parent="#accordion" class="accordion-toggle">
          <span class="glyphicon glyphicon-plus"></span>Names
        </a>
      </h6>
    </div>
    <div id="collapseOne" class="panel-collapse collapse in">
      <div class="panel-body">
        <?php print $accordionName; ?>
      </div>
    </div>
  </section>
  <?php if(!empty($accordionEtymology)): ?>
  <section class="panel panel-default">
    <div class="panel-heading">
      <h6>
        <a href="#collapseTwo" data-toggle="collapse" data-parent="#accordion" class="accordion-toggle collapsed">
          <span class="glyphicon glyphicon-plus"></span>ETYMOLOGY
        </a>
      </h6>
    </div>
    <div id="collapseTwo" class="panel-collapse collapse">
      <div class="panel-body">
        <?php print $accordionEtymology; ?>
      </div>
    </div>
  </section>
  <?php endif; ?>
  <?php if(!empty($accordionIdContent)): ?>
  <section class="panel panel-default">
    <div class="panel-heading">
      <h6>
        <a href="#collapseThree" data-toggle="collapse" data-parent="#accordion" class="accordion-toggle collapsed">
          <span class="glyphicon glyphicon-plus"></span>IDs
        </a>
      </h6>
    </div>
    <div id="collapseThree" class="panel-collapse collapse">
      <div class="panel-body">
        <?php print $accordionIdContent; ?>
      </div>
    </div>
  </section>
  <?php endif; ?>
  <?php if(!empty($accordionLocationContent)): ?>
  <section class="panel panel-default">
    <div class="panel-heading">
      <h6>
        <a href="#collapseFour" data-toggle="collapse" data-parent="#accordion" class="accordion-toggle collapsed">
          <span class="glyphicon glyphicon-plus"></span>Location
        </a>
      </h6>
    </div>
    <div id="collapseFour" class="panel-collapse collapse">
      <div class="panel-body">
        <?php print $accordionLocationContent; ?>
      </div>
    </div>
  </section>
  <?php endif; ?>
  <?php if(!empty($accordionGisContent)): ?>
  <section class="panel panel-default">
    <div class="panel-heading">
      <h6>
        <a href="#collapseFive" data-toggle="collapse" data-parent="#accordion" class="accordion-toggle collapsed">
          <span class="glyphicon glyphicon-plus"></span>GIS Resources
        </a>
      </h6>
    </div>
    <div id="collapseFive" class="panel-collapse collapse">
      <div class="panel-body">
        <?php print $accordionGisContent; ?>
      </div>
    </div>
  </section>
  <?php endif; ?>
</div>
