<?php

// Get items for use in the Carousel
// We make a direct query to the db to grab items that have been promoted
// to the front page, taking advantage of this legacy field for our own
// purposes.
// THIS SHOULD BE PUT INTO templates.php
$items = array();
$sql = "
  SELECT nid FROM {node}  n
  JOIN {field_data_body}  b
  ON (n.nid = b.entity_id)
  WHERE n.type = 'collection'
    AND n.promote = 1
    AND n.status = 1
    AND b.body_value NOT RLIKE '^\s*$'
  LIMIT 3";
$rs = db_query($sql);
while ($r = $rs->fetchObject()) {
  $this_node = node_load($r->nid);
  if (sizeof($this_node->body) > 0) {
    $lang = $this_node->language;
    $desc = $this_node->body[$lang][0]['value'];
    $img_url = image_style_url('front_carousel', $this_node->field_general_featured_image[$lang][0]['uri']);
    $items[] = array(
      'node_url'  => url("node/".$r->nid),
      'title'   => $this_node->title,
      'desc'    => $desc,
      'img_url'   => $img_url,
    );
  }
}
?>
<div class="container-fluid carouseldiv">
  <div class="carousel-header show-more" data-ride="carousel"><span>Featured Collections</span><a href="/collections">View All Collections</a></div>
  <div class="row">
    <div class="col-xs-12">
      <div class="carousel carousel-fade slide row" id="collection-carousel">
        <div class="carousel-inner">
        <?php foreach($items as $i => $item): ?>
          <div class="item <?php if ($i == 0) { print 'active'; } ?>">
            <div class="carousel-main-content col-xs-12 col-sm-7 col-md-8">
              <div>
                <h3 class="carousel-title">
                  <a href="<?php echo $item['node_url'] ?>">
                    <span class="icon shanticon-stack"></span>
                    <?php echo $item['title'] ?>
                  </a>
                </h3>
              </div>
              <div class="carousel-description">
                <div class="field field-name-body field-type-text-with-summary field-label-hidden">
                  <?php echo $item['desc'] ?>
                </div>
              </div>
              <p class="go-to-link"><a href="<?php echo $item['node_url']; ?>">View Collection </a></p>
            </div>
            <div class="carousel-main-image col-xs-12 col-sm-5 col-md-4">
              <a href="<?php echo $item['node_url'] ?>">
                <img src="<?php echo $item['img_url'] ?>" alt="">
              </a>
            </div>
          </div>
        <?php endforeach; ?>
        </div>
              <div class="control-box">
                  <a data-slide="prev" href="#collection-carousel" class="carousel-control left"><span class="icon"></span></a>
                  <a data-slide="next" href="#collection-carousel" class="carousel-control right"><span class="icon"></span></a>
              </div>

              <!-- <div class="control-box-2">
                  <button class="btn btn-default btn-sm carousel-pause"><span class="glyphicon glyphicon-pause"></span></button>
              </div>-->

              <ol class="control-box-3 carousel-indicators">
                  <li data-target="#collection-carousel" data-slide-to="0" class="active"></li>
                  <li data-target="#collection-carousel" data-slide-to="1"></li>
                  <li data-target="#collection-carousel" data-slide-to="2"></li>
              </ol>
      </div>
    </div>
  </div>
</div>

<div class="front-overview">
  <p>SHANTI Texts is a published repository of texts that can be used for a variety of content types, from remediated
  primary sources to long-form scholarly blog posts to be shared via social media. It is designed to allow you create
  content on-site or to upload long texts.</p>
</div>

<div>
  <?php print views_embed_view('all_texts_open','panel_pane_1'); ?>
</div>
