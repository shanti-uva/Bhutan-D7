<div id="places-main">

  <?php 
    $block = block_load('shanti_carousel', 'shanti_carousel_block_2');
    print render(_block_get_renderable_array(_block_render_blocks(array($block))));
  ?>

  <!-- Search Bar -->
  <div class="front-search">
    <div class="wrap">
      <?php echo $search; ?>
      <span class="icon shanticon-magnify"></span>
    </div>
  </div>

  <!-- List of Places -->
  <?php echo $list; ?>

</div><!-- End of places-main -->

<!-- Template for popovers -->
<script id="popover-front" type="text/x-handlebars-template">
  <div class="popover-body">
    <div class="desc">
      {{{node.caption_eng.[0]}}}
    </div>
  </div>
   <p class="related-label">Related Resoures:</p>
  <div class="popover-footer">
    <div class="popover-footer-button">
      <a href="/{{node.tree}}/{{extractId node.id}}/overview/nojs" class="icon shanticon-link-external" target="_blank"> Full Entry</a>
    </div>
    {{#each related_info}}
      {{#ifCond this.groupValue '===' "feature_types"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/subjects/nojs" class="icon shanticon-subjects" target="_blank">
             Subjects ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
      {{#ifCond this.groupValue '===' "related_subjects"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/subjects/nojs" class="icon shanticon-subjects" target="_blank">
             Subjects ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
      {{#ifCond this.groupValue '===' "related_places"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/places/nojs" class="icon shanticon-places" target="_blank">
             Places ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
      {{#ifCond this.groupValue '===' "texts"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/texts/nojs" class="icon shanticon-texts" target="_blank">
             Texts ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
      {{#ifCond this.groupValue '===' "picture"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/photos/nojs" class="icon shanticon-images" target="_blank">
             Images ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
      {{#ifCond this.groupValue '===' "audio-video"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/audio-video/nojs" class="icon shanticon-audio-video" target="_blank">
             Audio/Video ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
      {{#ifCond this.groupValue '===' "sources"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/sources/nojs" class="icon shanticon-sources" target="_blank">
             Sources ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
      {{#ifCond this.groupValue '===' "visuals"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/visuals/nojs" class="icon shanticon-visuals" target="_blank">
             Visuals ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
    {{/each}}
  </div>
</script>