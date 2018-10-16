<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print $user_picture; ?>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <div class="content"<?php print $content_attributes; ?>>
      <?php
          // We hide the comments and links now so that we can render them later.
          hide($content['comments']);
          hide($content['links']);
          hide($content['field_image']);
        ?>
      <!-- BEGIN Image Display Row -->
        <!-- <div id="preloading-horizontal" style="display:none;" role="progressbar" aria-valuemin="0" aria-valuetext="Loading image..." aria-valuemax="100"></div> -->
        <section class="image-display">
              <?php //dpm($content, 'content'); //dpm(get_defined_vars(), 'vars in template'); dpm($content, 'content');  ?>
              <?php print $flexslider_markup; ?>
        </section>
        <!-- BEGIN Details Row -->
        <aside class="image-detail-wrapper">
          <!-- position title/info higher below the featured image -->
            <header class="image-title">
                <h2><?php print $title; ?></h2>
                     <ul class="info list-inline">
                      <li><span><?php print $creator; ?></span></li>
                      <li><?php print render($content['field_image_type']); ?></li>
                      <li><span><?php print str_replace('x', ' x ', $pixels); ?> px</span></li>
                    </ul>
            </header>
            <div class="row image-detail-summary">
                  <div class="col-xs-12 col-sm-6">
                  <h5>Mandala Collections</h5>
                  <ul>
                    <li><span class="icon shanticon-stack" title="Collection"></span>
                        <?php if (!empty($content['field_og_collection_ref'])): ?>
                              <?php print render($content['field_og_collection_ref']); ?>
                        <?php endif; ?>
                        <?php print render($content['group_content_access']); ?>
                    </li>
                  </ul>
                  </div>
                  <div class="col-xs-12 col-sm-6">
                      <?php if (!empty($content['field_places']) || !empty($content['field_subjects']) || !empty($content['field_kmap_collections'])): ?>
                          <h5>Classification</h5>
                            <ul class="kmap-items" style="display: none;">
                              <?php if (!empty($content['field_places'])): ?>
                              <li><span class="icon shanticon-places"></span> <?php print render($content['field_places']); ?></li>
                                  <?php endif; ?>
                                  <?php if (!empty($content['field_subjects'])): ?>
                              <li><span class="icon shanticon-subjects"></span> <?php print render($content['field_subjects']); ?></li>
                                  <?php endif; ?>
                                  <?php if (!empty($content['field_kmap_collections'])): ?>
                                    <li><span class="icon shanticon-stack"></span> <?php print render($content['field_kmap_collections']); ?></li>
                                  <?php endif; ?>
                            </ul>
                        <?php endif; ?>
                  </div>
              </div> <!-- END image-detail-summary -->

              <div class="row image-detail-extended">
                  <div class="field detail-columns col-xs-12">
                      <h3 class="image-detail-title"><?php print $title; ?></h3>
                      <ul class="image-summary-info-list">
                          <li><span class="icon shanticon-agents"></span> <?php print $creator; ?></li>
                          <li><span class="fa fa-camera"></span><?php print render($content['field_image_type']); ?></li>
                          <li><span class="fa fa-arrows"></span><?php print str_replace('x', ' x ', $pixels); ?> px</li>
                      </ul>
                      <?php if (!empty($content['field_image_descriptions'])): ?>
                          <h5>Description</h5>
                          <?php print render($content['field_image_descriptions']); ?>
                      <?php endif; ?>
                      <ul>
                          <?php
                          hide($content['field_image_notes']);
                          hide($content['field_technical_notes']);
                          hide($content['field_license_url']);
                          print render($content);
                          ?>
                          <li class="dontsplit">
                              <span class="field-label"><?php print t('Uploaded By:'); ?>&nbsp;</span>
                              <span class="field-items">
                                  <?php
                                    print($username);
                                  ?>
                              </span>
                          </li>
                          <li class="dontsplit">
                              <span class="field-label"><?php print t('Original file:'); ?>&nbsp;</span>
                              <span class="field-items">
                                  <?php
                                      print($original_filename);
                                  ?>
                              </span>
                          </li>
                          <?php
                              print(render($content['field_image_notes']));
                              print(render($content['field_technical_notes']));
                              print(render($content['field_license_url']));
                          ?>
                      </ul>
                  </div>
              </div>
        </aside> <!-- END Details Row -->
  </div>
</div>
