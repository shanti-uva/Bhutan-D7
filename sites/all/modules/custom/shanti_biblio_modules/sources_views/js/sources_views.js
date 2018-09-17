/**
 * @file
 * Custom javascript functionalities for CSC custom views module.
 */
(function ($) {
  Drupal.behaviors.sourcesViews = {
    attach: function (context, settings) {
      // Load option settings by default
      if ($.isFunction($.cookie)){
        if ($.cookie('detail-level-value') != undefined) $.set_detail_level($.cookie('detail-level-value'));
      }
      $('.detail-level-option a').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        var option = $(this).attr('id');
        $.set_detail_level(option);
        $.cookie('detail-level-value', option);
      });
      $('#block-sources-views-custom-sort-filter').show();
    }
  };

  Drupal.behaviors.sourcesViewsAlterNodeBiblioFieldLabel = {
    attach: function (context, settings) {
      // Override secondary title field label text on node biblio edit form.
      $('.form-item-biblio-secondary-title label').text('Published In');
    }
  };

  // Returns query string value.
  $.get_query_string_val = function (variable) {
    var query = window.location.search.substring(1);
    var vars = query.split('&');
      for (var i = 0; i < vars.length; i++) {
        var pair = vars[i].split('=');
        if (pair[0] == variable){return pair[1];}
      }
    return(false);
  };
  
  $.set_detail_level = function (option_value) {
    $('.detail-level-option a').removeClass('active');
    $('.view-biblio-search-api.view-display-id-page .views-field, .view-biblio-search-api.view-display-id-allpage .views-field').hide();
    var option_id = '#' + option_value;
    $(option_id).addClass('active');
    switch (option_value) {
      case 'short-detail':
        $('.view-biblio-search-api.view-display-id-page .views-field-title').show();
        // for -allpage (home page) title is not in a .view-field so it doesn't get hidden
        break;
      case 'medium-detail':
        $('.view-biblio-search-api.view-display-id-page .views-field-title, .view-biblio-search-api.view-display-id-page .views-field-biblio-authors').show();
        $('.view-biblio-search-api.view-display-id-allpage .views-field-biblio-authors').show();
        break;
      case 'long-detail':
        $('.view-biblio-search-api.view-display-id-page .views-field, .view-biblio-search-api.view-display-id-allpage .views-field').show();
        break;
    }
  };
})(jQuery);
