/**
 * @file
 * Custom javascript functionalities for CSC custom views custom sort.
 */
(function ($) {
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
    // Update sort fields
    function update_sort_field(sort_type, sort_value) {
      if ($('#edit-sort-by').val() != sort_type || $('#edit-sort-order').val() != sort_value) {
        var is_front = ($('body').hasClass('front') || $("body").hasClass('page-home')) ? true : false;
        var sort_path = window.location.href;
        var new_sort_string = '&sort_by=' + sort_type + '&sort_order=' +  sort_value;
        if (is_front) { new_sort_string = '?' + new_sort_string.substr(1); }
        if ($.get_query_string_val('sort_by') && $.get_query_string_val('sort_order')) {
          var old_sort_string = '&sort_by=' + $.get_query_string_val('sort_by') + '&sort_order=' + $.get_query_string_val('sort_order');
          if (is_front) { old_sort_string = '?' + old_sort_string.substring(1); }
          var new_sort_path = sort_path.replace(old_sort_string, new_sort_string);
        }
        else {
          var new_sort_path = sort_path + new_sort_string;
        }
        console.log(new_sort_path);
        window.location.replace(new_sort_path);
      }
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
    
  }
};
})(jQuery);
