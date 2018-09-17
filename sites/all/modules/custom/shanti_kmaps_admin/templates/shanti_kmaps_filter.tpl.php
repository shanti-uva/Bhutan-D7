<!--
 Available variables:
   $namespace - used by the javascript to coordinate related filters and typeahead inputs
   $type - the type of filter, feature_type or associated_subject
   $display - the user-facing unpluralized filter name, Feature Type or Associated Subject
-->

<div id="<?php print $namespace; ?>-filter-<?php print $type; ?>"
     class="kmap-filter"
     data-search-filter="<?php print $type; ?>">
    <label><span>Filter:</span> Select <?php print $display; ?>s</label>
    <input id="<?php print $namespace; ?>-search-filter-<?php print $type; ?>"
           class="kmap-search-filter form-control form-text" type="text"
           data-search-filter="<?php print $type; ?>"
           placeholder="Filter by <?php print $display; ?>">
    <div id="<?php print $namespace; ?>-filter-box-<?php print $type; ?>"
         class="kmap-filter-box"
         data-search-filter="<?php print $type; ?>"> </div>
</div>