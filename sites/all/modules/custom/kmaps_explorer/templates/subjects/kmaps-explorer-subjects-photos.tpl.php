<h4><?php print $title; ?></h4>
<div id="og-grid" class="og-grid clearfix">
  <?php foreach($data as $aItem): ?>
    <?php $formats = kmaps_explorer_correct_images($aItem); ?>
    <div class="item">
      <a
        href="<?php print base_path() . $type . '/' . $id . '/photos-node/' . $aItem->id; ?>"
        data-largesrc="<?php print $formats['large']->url; ?>"
        data-hugesrc="<?php print $formats['huge']->url . '::' . $formats['huge']->width . '::' . $formats['huge']->height; ?>"
        data-title="<?php print (count($aItem->captions) > 0 ? check_plain($aItem->captions[0]->title) : ''); ?>"
        data-description="<?php print (count($aItem->descriptions) > 0 ? check_plain(strip_tags($aItem->descriptions[0]->title)) : 'No description currently available.'); ?>"
        data-creator="<?php print (count($aItem->copyrights) > 0 ? check_plain($aItem->copyrights[0]->copyright_holder->title) : 'Not available'); ?>"
        data-photographer="<?php print ((isset($aItem->photographer) && isset($aItem->photographer->fullname)) ? check_plain($aItem->photographer->fullname) : 'Not available'); ?>"
        data-date="Not available"
        data-place="Not available"
        data-type="jpg"
        data-ssid="<?php print $aItem->id; ?>"
        data-places="<?php print implode('::', array_map(function($o) { return $o->fid; }, $aItem->associated_features)); ?>"
        data-subjects="<?php print implode('::', array_map(function($o) { return $o->id; }, $aItem->associated_categories)); ?>"
        data-toggle="modal"
      >
        <img class="shanti-image-thumbnail" src="<?php print $formats['essay']->url; ?>" alt="<?php print (count($aItem->captions) > 0 ? $aItem->captions[0]->title : ''); ?>" height="180">
          <div class="img-footer-overlay" style="display: none;"><?php print (count($aItem->captions) > 0 ? truncate($aItem->captions[0]->title, 80) : ''); ?></div>
      </a>
    </div>
  <?php endforeach; ?>
</div>

<!-- Modal -->
<div class="modal fade" id="imagesModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
  <div class="modal-dialog" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
        <h4 class="modal-title images-modal-title" id="images-modal-label">Modal title</h4>
      </div>
      <div class="modal-body images-modal-body">
        ...
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
      </div>
    </div>
  </div>
</div>

<!-- Handlebar template to use for images subjects popovers -->
<script id="imagessubjectspopover" type="text/x-handlebars-template">
  <div class="images-subjects-popover">
    <h3 class="images-header-title">{{header}}</h3>
    <div class="">
      <h5>Ancestors</h5>
      <div class="">
        {{#each ancestors}}
          <a
          href="/subjects/{{lookup ../[ancestor_ids_default] @index}}/overview/nojs"
          class="list-group-item {{#ifCond (inc @index) '==' ../ancestors.length}}active{{/ifCond}}"
          target="_blank">
            {{this}}
          </a>
        {{/each}}
      </div>
      {{#if illustration_mms_url}}
        <h5>Illustration Image</h5>
        <img src="{{illustration_mms_url}}" />
      {{/if}}
    </div>
  </div>
</script>

<!-- Handlebar template to use for images places popovers -->
<script id="imagesplacespopover" type="text/x-handlebars-template">
  <div class="images-places-popover">
    <h3 class="images-header-title">{{header}}</h3>
    <div class="">
      <h5>Ancestors</h5>
      <div class="">
        {{#each ancestors}}
          <a
          href="/places/{{lookup ../[ancestor_ids_cult.reg] @index}}/overview/nojs"
          class="list-group-item {{#ifCond (inc @index) '==' ../ancestors.length}}active{{/ifCond}}"
          target="_blank">
            {{this}}
          </a>
        {{/each}}
      </div>
      <h5>Feature Types</h5>
      <ul class="">
        {{#each feature_types}}
          <li class="list-group-item">{{this}}</li>
        {{/each}}
      </ul>
      <h5>Names</h5>
      <ul class="">
        {{#each name}}
          <li class="list-group-item">{{this}}</li>
        {{/each}}
      </ul>
    </div>
  </div>
</script>

<!-- Handlebar template to use for images modal -->
<script id="imagesInfo" type="text/x-handlebars-template">
  <div class="images-info-tabs">
    <!-- Nav tabs -->
    <ul class="nav nav-pills" role="tablist">
      <li role="presentation" class="active"><a href="#places" aria-controls="places" role="tab" data-toggle="pill">Related Places</a></li>
      <li role="presentation"><a href="#subjects" aria-controls="subjects" role="tab" data-toggle="pill">Related Subjects</a></li>
    </ul>
    <!-- Tab panes -->
    <div class="tab-content">
      <div role="tabpanel" class="tab-pane active" id="places">
        <div class="panel-group" id="accordion" role="tablist" aria-multiselectable="true">
          {{#each places}}
            <div class="panel panel-default">
              <div class="panel-heading" role="tab">
                <h4 class="panel-title">
                  <a role="button" class="accordion-toggle" data-toggle="collapse" data-parent="#accordion" href="#{{id}}" aria-expanded="true" aria-controls="{{id}}">
                    {{header}}
                  </a>
                </h4>
              </div>
              <div id="{{id}}" class="panel-collapse collapse" role="tabpanel">
                <div class="panel-body">
                  <h5>Ancestors</h5>
                  <div class="list-group">
                    {{#each ancestors}}
                      <a
                      href="/places/{{lookup ../[ancestor_ids_cult.reg] @index}}/overview/nojs"
                      class="list-group-item {{#ifCond (inc @index) '==' ../ancestors.length}}active{{/ifCond}}"
                      target="_blank">
                        {{this}}
                      </a>
                    {{/each}}
                  </div>
                  <h5>Feature Types</h5>
                  <ul class="list-group">
                    {{#each feature_types}}
                      <li class="list-group-item">{{this}}</li>
                    {{/each}}
                  </ul>
                  <h5>Names</h5>
                  <ul class="list-group">
                    {{#each name}}
                      <li class="list-group-item">{{this}}</li>
                    {{/each}}
                  </ul>
                </div>
              </div>
            </div>
          {{/each}}
        </div>
      </div>
      <div role="tabpanel" class="tab-pane" id="subjects">
        {{#each subjects}}
          <div class="panel panel-default">
            <div class="panel-heading" role="tab">
              <h4 class="panel-title">
                <a role="button" class="accordion-toggle" data-toggle="collapse" data-parent="#accordion" href="#{{id}}" aria-expanded="true" aria-controls="{{id}}">
                  {{header}}
                </a>
              </h4>
            </div>
            <div id="{{id}}" class="panel-collapse collapse" role="tabpanel">
              <div class="panel-body">
                <h5>Ancestors</h5>
                <div class="list-group">
                  {{#each ancestors}}
                    <a
                    href="/subjects/{{lookup ../[ancestor_ids_default] @index}}/overview/nojs"
                    class="list-group-item {{#ifCond (inc @index) '==' ../ancestors.length}}active{{/ifCond}}"
                    target="_blank">
                      {{this}}
                    </a>
                  {{/each}}
                </div>
                {{#if illustration_mms_url}}
                  <h5>Illustration Image</h5>
                  <img src="{{illustration_mms_url}}" />
                {{/if}}
              </div>
            </div>
          </div>
        {{/each}}
      </div>
    </div>
  </div>
</script>

<!-- Root element of PhotoSwipe. Must have class pswp. -->
<div class="pswp" tabindex="-1" role="dialog" aria-hidden="true">

    <!-- Background of PhotoSwipe.
         It's a separate element as animating opacity is faster than rgba(). -->
    <div class="pswp__bg"></div>

    <!-- Slides wrapper with overflow:hidden. -->
    <div class="pswp__scroll-wrap">

        <!-- Container that holds slides.
            PhotoSwipe keeps only 3 of them in the DOM to save memory.
            Don't modify these 3 pswp__item elements, data is added later on. -->
        <div class="pswp__container">
            <div class="pswp__item"></div>
            <div class="pswp__item"></div>
            <div class="pswp__item"></div>
        </div>

        <!-- Default (PhotoSwipeUI_Default) interface on top of sliding area. Can be changed. -->
        <div class="pswp__ui pswp__ui--hidden">

            <div class="pswp__top-bar">

                <!--  Controls are self-explanatory. Order can be changed. -->

                <div class="pswp__counter"></div>

                <button class="pswp__button pswp__button--close" title="Close (Esc)"></button>

                <button class="pswp__button pswp__button--share" title="Share"></button>

                <button class="pswp__button pswp__button--fs" title="Toggle fullscreen"></button>

                <button class="pswp__button pswp__button--zoom" title="Zoom in/out"></button>

                <!-- Preloader demo http://codepen.io/dimsemenov/pen/yyBWoR -->
                <!-- element will get class pswp__preloader active when preloader is running -->
                <div class="pswp__preloader">
                    <div class="pswp__preloader__icn">
                      <div class="pswp__preloader__cut">
                        <div class="pswp__preloader__donut"></div>
                      </div>
                    </div>
                </div>
            </div>

            <div class="pswp__share-modal pswp__share-modal--hidden pswp__single-tap">
                <div class="pswp__share-tooltip"></div>
            </div>

            <button class="pswp__button pswp__button--arrow--left" title="Previous (arrow left)">
            </button>

            <button class="pswp__button pswp__button--arrow--right" title="Next (arrow right)">
            </button>

            <div class="pswp__caption">
                <div class="pswp__caption__center"></div>
            </div>

        </div>

    </div>

</div>
