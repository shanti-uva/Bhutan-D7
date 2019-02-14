<?php global $base_url ?>
<div class="terms-node-wrapper">
    <div class="terms-introduction-tabs">
        <ul id="terms-intro-tabs" class="nav nav-tabs nav-justified terms-intro-tabs" role="tablist">
            <li class="active" role="presentation">
                <a href="#terms-intro" role="tab" data-toggle="tab" aria-expanded="true">
                    Term Definition
                </a>
            </li>
            <li class="">
                <a href="#terms-intro-details" role="tab" data-toggle="tab" aria-expanded="false">
                    Term details
                </a>
            </li>
        </ul>
        <div class="tab-content">
            <div role="tabpanel" class="tab-pane terms-intro active" id="terms-intro">
                <div class="row">
                    <div class="col-xs-12">
                        <dl>
                            <div class="term-definition-title">
                                <dt class="sr-only">
                                    <dfn><?php echo isset($term_data->header) ? $term_data->header : $term_data->{'name_roman.scholar'} ?></dfn>
                                </dt>
                            </div>
                            <div class="terms-kmaps-id">
                                <dt>ID:</dt>
                                <dd>T<?php echo explode('-', $term_data->id)[1] ?></dd>
                            </div>
                            <ul style="margin:0; margin-top: 5px;">
                              <?php foreach ($names_data as $name): ?>
                                <?php if ($name->related_names_level_i === 1): ?>
                                      <li style="margin-left:1em; list-style:none;">
                                    <span class="<?php echo $name->related_names_writing_system_code_s === 'tibt' ? 'bo' : ''; ?>">
                                      <?php echo $name->related_names_header_s ?>
                                    </span>
                                        <?php echo term_names($name) ?>
                                          <ul style="margin:0; margin-top: 5px;">
                                            <?php foreach ($names_data as $name2): ?>
                                              <?php if ($name2->related_names_level_i === 2 && in_array($name->related_names_path_s, explode('/', $name2->related_names_path_s))): ?>
                                                    <li style="margin-left:1em; list-style:none;">
                                                        <b>></b>&nbsp;
                                                      <?php echo $name2->related_names_header_s ?> <?php echo term_names($name2) ?>
                                                    </li>
                                              <?php endif; ?>
                                            <?php endforeach; ?>
                                          </ul>
                                      </li>
                                <?php endif; ?>
                              <?php endforeach; ?>
                            </ul>
                        </dl>
                      <?php if (!empty($definitions)): ?>
                          <div class="terms-definition-list-wrapper">
                              <!-- BEGIN terms-definitions -->
                              <div class="terms-definition-list-wrapper row">
                                  <div class="col-xs-12"> <!-- Column 1 -->
                                    <?php
                                        $level = 1;
                                        $def_num = [];
                                    ?>
                                    <?php foreach ($definitions as $definition): ?>
                                        <?php
                                            $len = count(explode('/', $definition->related_definitions_path_s));
                                            $def_num[$len] += 1;
                                        ?>
                                        <?php if ($definition->related_definitions_level_i === ($level + 1)): ?>
                                          <div class="terms-definition-list-wrapper row">
                                              <div class="col-xs-12"> <!-- Column 1 -->
                                                <?php include(drupal_get_path('module', 'kmaps_explorer') . '/templates/kmaps-explorer-terms-node-partial.tpl.php') ?>
                                              </div>
                                          </div>
                                          <?php $level += 1 ?>
                                        <?php else: ?>
                                            <?php include(drupal_get_path('module', 'kmaps_explorer') . '/templates/kmaps-explorer-terms-node-partial.tpl.php') ?>
                                        <?php endif; ?>
                                    <?php endforeach; ?>
                                  </div> <!-- END Column 1 -->
                              </div> <!-- END terms-definition-list-wrapper -->
                          </div>
                      <?php endif; ?>
                        <div class="terms-dictionaries-other row">
                            <div class="col-xs-12">
                                <header class="sr-only">Other Dictionaries</header>
                                <h3>Other Dictionaries</h3>
                              <?php $count = 1; ?>
                              <?php foreach ($dict_data as $key => $dict): ?>
                                  <div class="terms-dictionaries-other-node">
                                      <h4><?php echo $count ?>. <cite><a href="#"> <?php echo $key ?></a></cite></h4>
                                    <?php if (count($dict) > 1): ?>
                                        <ul>
                                          <?php foreach ($dict as $subdict): ?>
                                              <li>
                                                  <p><?php echo str_replace(['<p>', '</p>'], '', $subdict->related_definitions_content_s) ?></p>
                                                  <p><a data-toggle="collapse" href="#<?php echo $subdict->id ?>"
                                                        role="button"
                                                        aria-expanded="false" aria-controls="definition-details"
                                                        class="definition-details-control collapsed">
                                                          <span class="glyphicon"></span>Further Details
                                                      </a>
                                                  </p>
                                                  <div id="<?php echo $subdict->id ?>"
                                                       class="definition-details-wrapper collapse" aria-expanded="false"
                                                       style="height: 0px;">
                                                      <dl>
                                                          <dt>language:</dt>
                                                          <dd><?php echo $subdict->related_definitions_language_s ?></dd>
                                                      </dl>
                                                  </div>
                                              </li>
                                          <?php endforeach; ?>
                                        </ul>
                                    <?php else: ?>
                                        <p><?php echo str_replace(['<p>', '</p>'], '', $dict[0]->related_definitions_content_s) ?></p>
                                        <p><a data-toggle="collapse" href="#<?php echo $dict[0]->id ?>" role="button"
                                              aria-expanded="false" aria-controls="definition-details"
                                              class="definition-details-control collapsed">
                                                <span class="glyphicon"></span>Further Details
                                            </a>
                                        </p>
                                        <div id="<?php echo $dict[0]->id ?>"
                                             class="definition-details-wrapper collapse" aria-expanded="false"
                                             style="height: 0px;">
                                            <dl>
                                                <dt>language:</dt>
                                                <dd><?php echo $dict[0]->related_definitions_language_s ?></dd>
                                            </dl>
                                        </div>
                                    <?php endif; ?>
                                  </div>
                                <?php $count++; ?>
                              <?php endforeach; ?>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div role="tabpanel" class="tab-pane terms-intro-details" id="terms-intro-details">
                <div class="row">
                    <div class="col-xs-12">
                        <dl>
                            <?php foreach($assoc_subjects as $id => $subject): ?>
                                <dt><?php echo $subject['header']; ?>:</dt>
                                <dd class="related_subject">
                                    <a href="<?php echo $base_url ?>/subjects/<?php echo $id ?>/overview/nojs"><?php echo $subject['subject'] ?></a>
                                    <span class="popover-kmaps" data-app="subjects"
                                          data-id="<?php echo $id ?>" rel="popover"
                                          data-original-title="" title="">
                                        <span class="popover-kmaps-tip"></span>
                                        <span class="icon shanticon-menu3"></span>
                                    </span>
                                </dd>
                            <?php endforeach; ?>
                        </dl>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
