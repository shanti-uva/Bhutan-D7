<div id="<?php print $ajax ? $type . '-ajax' : $type . '-main' ?>">
  <!-- Column Resources  -->

  <!-- Column Main  -->
  <section  class="content-section col-xs-12">
    <div class="tab-content">

      <article class="active" id="tab-main">
        <?php if($active_content): ?>
          <?php print $active_content; ?>
        <?php endif; ?>
      </article>

    </div><!-- END tab-content -->
  </section><!-- END content-section -->

</div>

<!-- Template for popovers -->
<script id="popover-general" type="text/x-handlebars-template">
  <div class="popover-body">
    <div class="desc">
      {{{node.caption_eng.[0]}}}
    </div>
    <div class="parents clearfix">
      <p>
        <strong>
          {{capitalizeFirstLetter node.tree}}
        </strong>
        {{#each node.ancestors}}
          <a href="/{{../node.tree}}/{{lookup ../node.ancestor_ids_generic @index}}/overview/nojs">{{this}}</a>
        {{/each}}
      </p>
    </div>
  </div>
  <div class="popover-footer">
    <div class="popover-footer-button">
      <a href="/{{node.tree}}/{{extractId node.id}}/overview/nojs" class="icon shanticon-link-external" target="_blank">Full Entry</a>
    </div>
    {{#each related_info}}
      {{#ifCond this.groupValue '===' "feature_types"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/subjects/nojs" class="icon shanticon-subjects" target="_blank">
            Related Subjects ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
      {{#ifCond this.groupValue '===' "related_subjects"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/subjects/nojs" class="icon shanticon-subjects" target="_blank">
            Related Subjects ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
      {{#ifCond this.groupValue '===' "related_places"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/places/nojs" class="icon shanticon-places" target="_blank">
            Related Places ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
      {{#ifCond this.groupValue '===' "texts"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/texts/nojs" class="icon shanticon-texts" target="_blank">
            Related Texts ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
      {{#ifCond this.groupValue '===' "picture"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/photos/nojs" class="icon shanticon-images" target="_blank">
            Related Images ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
      {{#ifCond this.groupValue '===' "audio-video"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/audio-video/nojs" class="icon shanticon-audio-video" target="_blank">
            Related Audio/Video ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
      {{#ifCond this.groupValue '===' "sources"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/sources/nojs" class="icon shanticon-sources" target="_blank">
            Related Sources ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
      {{#ifCond this.groupValue '===' "visuals"}}
        <div class="popover-footer-button">
          <a href="/{{../node.tree}}/{{extractId ../node.id}}/visuals/nojs" class="icon shanticon-visuals" target="_blank">
            Related Visuals ({{this.doclist.numFound}})
          </a>
        </div>
      {{/ifCond}}
    {{/each}}
  </div>
</script>
