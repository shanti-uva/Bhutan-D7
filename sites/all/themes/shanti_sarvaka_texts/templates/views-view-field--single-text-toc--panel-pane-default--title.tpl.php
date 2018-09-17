<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
$textlang = '';
$textlang = shanti_texts_get_lang_code($row->nid);
$output = preg_replace("/<a /", "<a lang=\"$textlang\" ", $output);
$coll_id = shanti_collections_admin_get_collection_id_of_node($row->nid);
$edit_widget = shanti_sarvaka_texts_get_edit_widget($row->nid,$coll_id);
?>
<?php print $output; ?>
<?php print render($edit_widget); ?>
