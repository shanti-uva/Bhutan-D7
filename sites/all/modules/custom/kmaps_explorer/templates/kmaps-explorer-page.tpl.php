<div id="<?php print $ajax ? $type . '-ajax' : $type . '-main' ?>">
  <!-- Column Resources  -->
  <section id="sidebar-first" class="region sidebar sidebar-first col-xs-6 col-md-3 sidebar-offcanvas ">
    <ul class="nav nav-pills nav-stacked">
      <li class="overview <?php print isset($overview) ? 'active' : ''; ?>"><a href="<?php print base_path() . $type . '/' . $kid; ?>/overview/nojs" class="use-ajax">
        <span class="icon shanticon-overview"></span>Overview</a>
      </li>

      <?php if($places_count > 0): ?>
        <li class="places <?php print isset($place) ? 'active' : ''; ?>">
          <a href="<?php print base_path() . $type . '/' . $kid; ?>/places/nojs" class="use-ajax">
            <span class="icon shanticon-places"></span>
            Places
            <span class="badge"><?php print $places_count; ?></span>
          </a>
        </li>
      <?php endif; ?>

      <?php if($subjects_count > 0): ?>
        <li class="subjects <?php print isset($subject) ? 'active' : ''; ?>">
          <a href="<?php print base_path() . $type . '/' . $kid; ?>/subjects/nojs" class="use-ajax">
            <span class="icon shanticon-subjects"></span>
            Subjects
            <span class="badge"><?php print $subjects_count; ?></span>
          </a>
        </li>
      <?php endif; ?>

      <?php if($solr_text_count > 0): ?>
        <li class="essays <?php print isset($text) ? 'active' : ''; ?>">
          <a href="<?php print base_path() . $type . '/' . $kid; ?>/texts/nojs" class="use-ajax">
            <span class="icon shanticon-texts"></span>
            Texts
            <span class="badge"><?php print $solr_text_count; ?></span>
          </a>
        </li>
      <?php endif; ?>

      <?php if(false): ?>
        <li class="agents"><a href="<?php print base_path() . $type . '/' . $kid; ?>/agents">
          <span class="icon shanticon-agents"></span>Agents<span class="badge"></span></a>
        </li>
      <?php endif; ?>

      <?php if(false): ?>
        <li class="events"><a href="<?php print base_path() . $type . '/' . $kid; ?>/events">
          <span class="icon shanticon-events"></span>Events<span class="badge"></span></a>
        </li>
      <?php endif; ?>

      <?php if($images_count > 0): ?>
        <li class="photos <?php print isset($photo) ? 'active' : ''; ?>">
          <a href="<?php print base_path() . $type . '/' . $kid; ?>/photos/nojs" class="use-ajax">
            <span class="icon shanticon-photos"></span>
            Images
            <span class="badge"><?php print $images_count; ?></span>
          </a>
        </li>
      <?php endif; ?>

      <?php if($video_count > 0): ?>
        <li class="audio-video <?php print isset($audio_video) ? 'active' : ''; ?>">
          <a href="<?php print base_path() . $type . '/' . $kid; ?>/audio-video/nojs" class="use-ajax">
            <span class="icon shanticon-audio-video"></span>
            Audio-Video
            <span class="badge"><?php print $video_count; ?></span>
          </a>
        </li>
      <?php endif; ?>

      <?php if($visuals_count > 0): ?>
        <li class="visuals <?php print isset($visuals) ? 'active' : ''; ?>">
          <a href="<?php print base_path() . $type . '/' . $kid; ?>/visuals/nojs" class="use-ajax">
            <span class="icon shanticon-visuals"></span>
            Visuals
            <span class="badge"><?php print $visuals_count; ?></span>
          </a>
        </li>
      <?php endif; ?>

      <?php if(false): ?>
        <li class="maps"><a href="<?php print base_path() . $type . '/' . $kid; ?>/maps">
          <span class="icon shanticon-maps"></span>Maps<span class="badge"></span></a>
        </li>
      <?php endif; ?>

      <?php if(false): ?>
        <li class="community"><a href="<?php print base_path() . $type . '/' . $kid; ?>/community">
          <span class="icon shanticon-community"></span>Community<span class="badge"></span></a>
        </li>
      <?php endif; ?>

      <?php if(false): ?>
        <li class="terms"><a href="<?php print base_path() . $type . '/' . $kid; ?>/terms">
          <span class="icon shanticon-terms"></span>Terms<span class="badge"></span></a>
        </li>
      <?php endif; ?>

      <?php if($sources_count > 0): ?>
        <li class="sources <?php print isset($sources) ? 'active' : ''; ?>">
          <a href="<?php print base_path() . $type . '/' . $kid; ?>/sources/nojs" class="use-ajax">
            <span class="icon shanticon-sources"></span>
            Sources
            <span class="badge"><?php print $sources_count; ?></span>
          </a>
        </li>
      <?php endif; ?>
    </ul>
  </section>

  <!-- Column Main  -->
  <section  class="content-section col-xs-12 col-md-9 ">
    <div class="tab-content">

      <article class="active" id="tab-main">
        <?php if($active_content): ?>
          <?php print $active_content; ?>
        <?php endif; ?>
      </article>

    </div><!-- END tab-content -->
  </section><!-- END content-section -->

  <!-- Edit button for Rails App -->
  <div class="fixed-action-button">
    <a href="<?php print $edit_url; ?>" class="round-btn-fixed">
      <span class="glyphicon glyphicon-pencil" aria-hidden="true"></span>
    </a>
  </div>
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
