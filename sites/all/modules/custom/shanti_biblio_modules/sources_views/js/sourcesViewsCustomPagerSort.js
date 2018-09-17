/**
 * @file
 * Custom javascript functionalities for CSC custom views custom pager.
 */
(function ($) {
    
    function parseParams(qs) {
        var params = {};
        var qpts = qs.replace('?','').split('&');
        for(var n in qpts) {
            var prm = qpts[n].split('=');
            if (prm.length == 2) {
                params[prm[0]] = prm[1];
            } else {
                console.log(prm);
            }
        }
        return params;
    }
    
    function rebuildQuery(params) {
        var qry = '?';
        var builtparams = [];
        for (var p in params) {
           builtparams.push( p + '=' + params[p]);
        }
        qry += builtparams.join('&');
        return qry;
    }
    
    Drupal.behaviors.sourcesViewsCustomPager = {
      attach: function (context, settings) {
        // Restrict input to numbers only
        $('#pager-input').keypress(function(e) {
          if (e.charCode < 48 || e.charCode > 57) return false;
        });
        // Redirect on enter key
        $('#pager-input').keydown(function(e) {
              if (e.which == 13) {
                  var pagequery = window.location.search;
                  var params = parseParams(pagequery);
                  var maxpg = $('#max-page-input').val() * 1;
                  var pageval = $('#pager-input').val() * 1;
                  if (pageval < 1) { pageval = 1; }
                  if (pageval > maxpg) { pageval = maxpg; }
                  params.page = pageval - 1;
                  window.location.search = rebuildQuery(params);
              }
          });
       }
    }; // End of sourcesViewsCustomPager
    
    Drupal.behaviors.sourcesViewsCustomSort = {
      attach: function (context, settings) {
        // Default custom sort state
        var default_sort_value = $.get_query_string_val('sort_by');
        var default_sort_order = $.get_query_string_val('sort_order');
    
        var sort_by = (default_sort_value) ? default_sort_value : 'sort_stripped_node_title';
        var sort_order = (default_sort_order) ? default_sort_order : 'ASC';
        switch (sort_by) { 
          case 'sort_stripped_node_title':
            var default_sort_value = (sort_order == 'ASC') ? 'title_asc' : 'title_desc';
            break;
          case 'sort_biblio_author':
            var default_sort_value = (sort_order == 'ASC') ? 'author_asc' : 'author_desc';
            break;
          case 'sort_custom_publication_year':
            var default_sort_value = (sort_order == 'ASC') ? 'year_asc' : 'year_desc';
            break;
        }
        $('#block-sources-views-custom-sort-filter .bootstrap-select.select-wrapper .dropdown-menu li').each(function(index) {
          ($(this).attr('rel') == default_sort_value) ? $(this).addClass('selected') : $(this).removeClass('selected');
        });
        // Update hidden sort field values based on the selected value of custom sort field.
        $('#block-sources-views-custom-sort-filter .bootstrap-select.select-wrapper .dropdown-menu li').click(function() {
            
          switch ($(this).attr('rel')) {
            case 'title_asc':
              update_sort_field('sort_stripped_node_title', 'ASC');
              break;
            case 'title_desc':
              update_sort_field('sort_stripped_node_title', 'DESC');
              break;
            case 'author_asc':
              update_sort_field('sort_biblio_author', 'ASC');
              break;
            case 'author_desc':
              update_sort_field('sort_biblio_author', 'DESC');  
              break;
            case 'year_asc':
              update_sort_field('sort_custom_publication_year', 'ASC');
              break;
            case 'year_desc':
              update_sort_field('sort_custom_publication_year', 'DESC');
              break;
            case 'default':
              update_sort_field('sort_stripped_node_title', 'ASC');  
              break;
          }
        });  
        }
    };  // end of behavior sourcesViewsCustomSort
        
        // Update sort fields
        function update_sort_field(sort_type, sort_value) {
          if ($('#edit-sort-by').val() != sort_type || $('#edit-sort-order').val() != sort_value) {
              var pagequery = window.location.search;
              var params = parseParams(pagequery);
              params.sort_by = sort_type;
              params.sort_order = sort_value;
              delete params.page;
              window.location.search = rebuildQuery(params);
          }
        // Set selected value text display on custom sort dropdown field
        var selected_option_value = $('#custom-sort-form ul.dropdown-menu.selectpicker li.selected span.text').text();
        var select_option_value = $('#custom-sort-form ul.dropdown-menu.selectpicker li.selected').attr('rel');
        if (select_option_value == 'title_asc' || select_option_value == 'title_desc') var option_group_label = 'Title';
        if(select_option_value == 'author_asc' || select_option_value == 'author_desc') var option_group_label = 'Author';
        if(select_option_value == 'year_asc' || select_option_value == 'year_desc') var option_group_label = 'Year';
        if (selected_option_value != '' && select_option_value != '') {
          $('#custom-sort-form span.filter-option').text('Sort By: ' + option_group_label + ' ' + selected_option_value);
        }
        else {
          $('#custom-sort-form span.filter-option').text('Sort By: ');
        }
        
      } // end of update_sort_field function
})(jQuery);
