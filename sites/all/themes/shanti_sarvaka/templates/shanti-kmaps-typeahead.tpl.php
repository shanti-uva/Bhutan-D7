<!--
 Available variables:
   $namespace - used by the javascript to coordinate related filters and typeahead inputs
   $domain - the user-facing domain name, e.g. Subjects, Places, Subcollections, Memorabilia, etc.
-->

<div id="<?php print $namespace; ?>-typeahead-wrapper"
     class="kmap-typeahead-picker">
  <label class="flyout-search-label"><span><?php print t('Search:'); ?></span><?php print rtrim($domain, 's') . ' Names'; ?></label>
  <input id="<?php print $namespace; ?>-search-term"
         class="kmap-search-term form-control form-text" type="text"
         placeholder="<?php print t('Enter Search...'); ?>">
  <span class="icon shanticon-magnify"></span>
  <button type="button" class="btn searchreset" aria-label="Clear search text" style="display: none;"><span class="icon"></span></button>
</div>
