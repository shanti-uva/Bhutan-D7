<div class="overview-top-collection clearfix">
    <?php
    if (count($node_data->illustration_mms_url) > 0) {
        $str = $node_data->illustration_mms_url[0];
        $imgObj = json_decode(file_get_contents('https://mms.thlib.org/media_objects/' . explode("_", end(explode("/", $str)))[0] . '.json'));
        print theme('kmaps_explorer_subjects_overview_image', array('data' => $imgObj));
    }
    ?>

    <h4><?php print $node_data->header; ?></h4>

    <?php
    if (count($node_data->summary_eng) > 0) {
        print $node_data->summary_eng[0];
    }
    ?>
</div>

<div class="panel-group" id="accordion" style="margin-top:1em; clear:both;">
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
                <ul style="margin:0; margin-top: 5px;">
                    <?php foreach ($namesData->names as $name1): ?>
                        <li style="margin-left:1em; list-style:none;">
                            <?php if ($name1->writing_system->name === 'Tibetan script'): ?>
                                <span lang="bo" xml:lang="bo" class="bo"><?php echo $name1->name ?></span>
                            <?php else: ?>
                                <span><?php echo $name1->name ?></span>
                            <?php endif; ?>
                            (<?php echo !empty($name1->language) ? $name1->language->name : '' ?>,
                            <?php echo !empty($name1->writing_system) ? $name1->writing_system->name : '' ?>,
                            <?php echo !empty($name1->relationship) ? $name1->relationship->name : '' ?>)
                            <?php echo kmaps_explorer_print_subjects_names($name1) ?>
                        </li>
                    <?php endforeach; ?>
                </ul>
            </div>
        </div>
    </section>
    <section class="panel panel-default">
        <div class="panel-heading">
            <h6>
                <a href="#collapseTwo" data-toggle="collapse" data-parent="#accordion"
                   class="accordion-toggle collapsed">
                    <span class="glyphicon glyphicon-plus"></span>IDs
                </a>
            </h6>
        </div>
        <div id="collapseTwo" class="panel-collapse collapse">
            <div class="panel-body">
                <div>
                    Subject ID: S<?php print end(explode("-", $node_data->id)); ?>
                </div>
            </div>
        </div>
    </section>
</div>
