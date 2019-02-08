<?php
    //Get the definition number;
    $len = count(explode('/', $definition->related_definitions_path_s));
    $len -= 1;
    if ($len === 0) {
        $label = $def_num[$len + 1] . '.';
    } else {
        $label = kmaps_explorer_roman($len) . $def_num[$len + 1];
    }

    //Setup branches which gives us a count of the number of Resources for this definition.
    $branches = preg_grep("/(\d+)_subjects_headers_t$/", array_keys((array)$definition))
?>
<div class="terms-definition-node terms-def-child-<?php echo $definition->related_definitions_level_i ?>">
    <ul id="terms-def-tabs-<?php echo str_replace('/', '-', $definition->related_definitions_path_s) ?>"
        class="nav nav-tabs terms-def-tabs-<?php echo str_replace('/', '-', $definition->related_definitions_path_s) ?>"
        role="tablist">
        <li class="active">
            <a href="#terms-def-<?php echo str_replace('/', '-', $definition->related_definitions_path_s) ?>"
               role="tab" data-toggle="tab"
               aria-expanded="true"><?php echo $label . ' ' ?>Definition</a>
        </li>
        <?php if (count($branches) > 0): ?>
        <li class="">
            <a href="#terms-resources-<?php echo str_replace('/', '-', $definition->related_definitions_path_s) ?>"
               role="tab" data-toggle="tab"
               aria-expanded="false">
                Resources
                <span>(<?php echo count($branches) ?>)</span>
            </a>
        </li>
        <?php endif; ?>
    </ul>
    <div class="tab-content">
        <div role="tabpane" class="tab-pane active"
             id="terms-def-<?php echo str_replace('/', '-', $definition->related_definitions_path_s) ?>">
            <p></p>
            <?php echo $definition->related_definitions_content_s ?>
            <p></p>
            <p>
                <a data-toggle="collapse"
                   href="#definition-details-<?php echo str_replace('/', '-', $definition->related_definitions_path_s) ?>"
                   role="button" aria-expanded="false" aria-controls="definition-details"
                   class="definition-details-control collapsed">
                    <span class="glyphicon"></span>Further Details
                </a>
            </p>
            <div id="definition-details-<?php echo str_replace('/', '-', $definition->related_definitions_path_s) ?>"
                 class="definition-details-wrapper collapse" aria-expanded="false" style="height: 0px">
                <dl>
                  <?php if (isset($definition->related_definitions_language_s) && !empty($definition->related_definitions_language_s)): ?>
                      <dt>Language:</dt>
                      <dd><?php echo $definition->related_definitions_language_s ?></dd>
                  <?php endif; ?>
                  <?php if (isset($definition->related_definitions_tense_s) && !empty($definition->related_definitions_tense_s)): ?>
                      <dt>Tense:</dt>
                      <dd><?php echo $definition->related_definitions_tense_s ?></dd>
                  <?php endif; ?>
                  <?php if (isset($definition->related_definitions_author_s) && !empty($definition->related_definitions_author_s)): ?>
                      <dt>Author:</dt>
                      <dd><?php echo $definition->related_definitions_author_s ?></dd>
                  <?php endif; ?>
                </dl>
            </div>
        </div>
      <?php
      $numbers = [];
      foreach ($branches as $branch) {
        preg_match('(\d+)', $branch, $matches);
        array_push($numbers, $matches[0]);
      }
      ?>
        <div role="tabpanel" class="tab-pane"
             id="terms-resources-<?php echo str_replace('/', '-', $definition->related_definitions_path_s) ?>">
            <h4>Subjects</h4>
            <dl>
              <?php foreach ($numbers as $num): ?>
                  <dt><?php echo $definition->{"related_definitions_branch_subjects-" . $num . "_header_s"} ?>:</dt>
                  <dd class="related_subject">
                    <?php $app_array = explode("-", $definition->{"related_definitions_branch_subjects-" . $num . "_subjects_uids_t"}[0]) ?>
                      <a href="<?php echo $base_url . '/' . $app_array[0] . '/' . $app_array[1] . '/overview/nojs' ?>">
                        <?php echo $definition->{"related_definitions_branch_subjects-" . $num . "_subjects_headers_t"}[0] ?>
                      </a>
                      <span class="popover-kmaps" data-app="<?php echo $app_array[0] ?>"
                            data-id="<?php echo $app_array[1] ?>">
                          <span class="popover-kmaps-tip"></span>
                          <span class="icon shanticon-menu3"></span>
                      </span>
                  </dd>
              <?php endforeach; ?>
            </dl>
        </div>
    </div> <!-- END tab-content -->
</div>
