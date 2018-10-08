<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */

$nid       = $fields['nid']->content;
$node      = node_load($nid);

$lang      = $node->language;
$bid       = $node->book['bid'];
$mlid      = $node->book['mlid'];

$depth     = $fields['depth']->content;
$weight    = $fields['weight']->content;
$title     = $fields['title']->content;
$content   = $fields['field_book_content']->content;
$places    = $fields['field_kmap_places']->content;
$subjects  = $fields['field_kmap_term']->content;

$coll_id   = shanti_collections_admin_get_collection_id_of_node($nid);
/*
$coll_field = variable_get('shanti_collections_admin_collection_field');
if (isset($node->{$coll_field}[$lang][0]['target_id'])) {
    $coll_id = $node->{$coll_field}[$lang][0]['target_id'];
}
*/

$textlang = shanti_texts_get_lang_code($nid);

$search_str = '';
if (array_key_exists('s',$_GET)) {
    $search_str = $_GET['s'];
}

/*
$node_edit_url = l('<span class="label label-primary">Edit</span>',
    "node/$nid/edit",
    array(
        'html' => TRUE,
        'query' => array('destination' => current_path()),
        'fragment' => "shanti-texts-$nid",
        'attributes' => array('title' => t('Edit this page')),
    )
);

$node_add_url = l('<span class="label label-success">Insert</span>',
    "node/add/book",
    array(
        'html' => TRUE,
        'query' => array(
            'destination' => current_path(),
            'field_og_collection_ref' => $coll_id,
            'parent' => $mlid
        ),
        'fragment' => "node-$nid",
        'attributes' => array('title' => t('Add a new page under this one')),
    )
);
*/


?>
<a name="shanti-texts-<?php print $nid; ?>"></a>
<div id="shanti-texts-<?php print $nid; ?>" class="shanti-texts-section text-level-<?php print $depth; ?>" lang="<?php print $textlang; ?>">
    <div id="shanti-texts-<?php print $nid; ?>">
        <div class="shanti-texts-section-title text-level-<?php print $depth; ?>">
            <?php print $title; ?>
        </div>
    </div>
    <div class="shanti-texts-section-content">
        <?php
        if ($search_str) {
            $content = preg_replace("/($search_str)/i","<span class='search-string-hit' style='background:yellow;'>$1</span>",$content);
        }
        print $content;
        ?>
    </div>
    <?php if($subjects || $places): ?>
    <div class="shanti-texts-section-kmaps">
        <?php print $subjects; ?>
        <?php print $places; ?>
    </div>
    <?php endif; ?>

    <!--
    <?php
    /*
    if(user_access('add content to books') &&
      og_is_member('node',$coll_id,'user') &&
      og_user_access('node',$coll_id,'create book content') &&
      og_user_access('node',$coll_id,'update own book content')):
     */
    ?>
    <div class="shanti-texts-section-controls">
        <?php //print $node_edit_url; ?>
        <?php //print $node_add_url; ?>
    </div>
    <?php //endif; ?>
    -->

</div>
