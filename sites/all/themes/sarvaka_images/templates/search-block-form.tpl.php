<?php

/**
 * @file
 * Displays the search form block.
 *
 * Available variables:
 * - $search_form: The complete search form ready for print.
 * - $search: Associative array of search elements. Can be used to print each
 *   form element separately.
 *
 * Default elements within $search:
 * - $search['search_block_form']: Text input area wrapped in a div.
 * - $search['actions']: Rendered form buttons.
 * - $search['hidden']: Hidden form elements. Used to validate forms when
 *   submitted.
 *
 * Modules can add to the search form, so it is recommended to check for their
 * existence before printing. The default keys will always exist. To check for
 * a module-provided field, use code like this:
 * @code
 *   <?php if (isset($search['extra_field'])): ?>
 *     <div class="extra-field">
 *       <?php print $search['extra_field']; ?>
 *     </div>
 *   <?php endif; ?>
 * @endcode
 *
 * @see template_preprocess_search_block_form()
 */
/*
<div class="container-inline">
  <?php if (empty($variables['form']['#block']->subject)): ?>
    <h2 class="element-invisible"><?php print t('Search form'); ?></h2>
  <?php endif; ?>
  <?php print $search_form; ?>
</div>
 *
 */
?>
<div class="search-group">
    <?php foreach ($widgets as $id => $widget): ?>
        <div id="<?php print $widget->id; ?>-wrapper" class="views-exposed-widget views-widget-<?php print $id; ?>">
            <div class="input-group">
                <?php print str_replace('<label class="element-invisible" for="edit-search-block-form--2">Search </label>', '<label class="flyout-search-label"><span>Search:</span>Audio-Video</label>', $search['search_block_form']); ?>
                <span class="icon shanticon-magnify"></span>
                <?php print $widget->widget; ?>
            </div>
            
            <!-- search scope -->
            <?php if (!empty($widget->operator)): ?>
                <div class="form-group">
                    <?php print $widget->operator; ?>
                    <a href="#" class="advanced-link toggle-link"><span class="icon"></span>Advanced</a>
                </div>
            <?php endif; ?>
        </div>
    <?php endforeach; ?>
</div>

<div id="notification-wrapper"></div>
<section class="advanced-view"></section>