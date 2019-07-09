<?php
$book_title = $variables['book']['link_title'];
$bid = $variables['book']['bid'];
$langcode = shanti_texts_get_lang_code($variables['nid']);
$coll_id = shanti_collections_admin_get_collection_id_of_node($variables['nid']);
$edit_widget = shanti_sarvaka_texts_get_edit_widget($variables['nid'],$coll_id);
?>
<div id="shanti-texts-container" class="row">
    <div id="shanti-texts-body" class="col-xs-12 col-md-8">
        <?php print views_embed_view('single_text_body','panel_pane_default',$bid); ?>
    </div>
    <div id="shanti-texts-sidebar" role="tabpanel" class="col-xs-12 col-md-4">
        <button class="fullview icon shanticon-expand" href="#"></button>
        <ul id="shanti-texts-sidebar-tabs" class="nav nav-tabs nav-justified" role="tablist">
            <li class="first" role="presentation">
                <a aria-expanded="true" data-toggle="tab" href="#shanti-texts-toc" role="tab">Contents</a>
            </li>
            <li class="" role="presentation">
                <a data-toggle="tab" href="#shanti-texts-meta" role="tab">Description</a>
            </li>
            <li class="" role="presentation">
                <a data-toggle="tab" href="#shanti-texts-links" role="tab">Views</a>
            </li>
        </ul>
        <div class="tab-content">
            <div id="shanti-texts-toc" class="tab-pane" role="tabpanel">

                <div class="shanti-texts-record-title" lang="<?php print $langcode; ?>">
                   <?php print $pdf_link; ?>
                    <a href="#shanti-texts-<?php print $bid; ?>"><?php print $book_title; ?></a>
                    <?php print render($edit_widget); ?>
                </div>
                <?php print views_embed_view('single_text_toc', 'panel_pane_default',$bid); ?>
            </div>
            <div id="shanti-texts-meta" class="tab-pane" role="tabpanel">
                <div class="shanti-texts-record-title"><?php print $book_title; ?></div>
                <?php print views_embed_view('single_text_meta', 'panel_pane_default',$bid); ?>
            </div>
            <div id="shanti-texts-links" class="links tab-pane" role="tabpanel">
                <div class="shanti-texts-record-title"><?php print $book_title; ?></div>                

                <h6>Alternative Formats</h6>
                <?php print views_embed_view('single_text_views', 'panel_pane_default',$bid); ?>

            </div>
        </div>
    </div>
</div>
