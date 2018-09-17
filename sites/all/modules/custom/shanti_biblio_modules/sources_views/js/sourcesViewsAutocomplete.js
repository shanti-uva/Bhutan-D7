/**
 * @file
 * Custom javascript functionalities for CSC custom views autocomplete field.
 */
(function ($) {

//Store all criteria
var search_criteria = {};

//If we are in the process of redirecting
//Used to prevent submit on enter
var redirect_in_progress = false;

/*
 * For the main search box (non-advanced) autocomplete
 * which allows user to select different categories (Title, Author, etc)
 * In the dropdown
 */
Drupal.behaviors.sourcesViewsQuickSearchAutocomplete = {
  attach: function (context, settings) {
    var selector = 'input#edit-advanced-search-api-views-fulltext';

    preventSubmitOnEnter(selector);

    //Add our own handler, after autocompleteSelect fires
    quick_search_submit_on_enter(selector);

    $(selector, context).bind('autocompleteSelect', function() {
      quick_search_autocomplete_select_handler($(this));
    });

    //Simulate a form submit event when clicking custom autocomplete field submit button
    $('#searchbutton').click(function() {
      if ($('#autocomplete').length) {
        $('#autocomplete').remove();
      }
      $("#sources-views-advanced-search-form").submit();
    });
  }
};

/*
 * Do not automatically submit form if user presses the
 * Enter key on the provided input element
 * we will handle this manually on a case-by-case basis
 */
function preventSubmitOnEnter(element) {
  $(element).bind('keydown', function(e) {
    if (e.which == 13) {
      e.preventDefault();
    }
  });
}

/*
 * For the main search box, we submit immediately on autocomplete select
 */
function quick_search_autocomplete_select_handler(autocomplete_element) {
  redirect_in_progress = true;
  var autocomplete_value = $(autocomplete_element).val().split('=');

  //clear node=123 from search input
  $(autocomplete_element).val('');

  var redirect_url;
  var filter_type  = autocomplete_value[0];
  var filter_value = autocomplete_value[1];
  var filter_page  = autocomplete_value[2];

  var query_keys = {
    author: 'search_text_biblio_author',
    publisher: 'biblio_publisher',
    publishplace: 'biblio_place_published',
    tag: 'field_zotero_tags'
  }

  if (filter_type === 'node') {
    redirect_url = location.protocol + '//' + location.host + '/sources-search/biblio/' + filter_value; //?page=' + filter_page + '&current_nid=' + filter_value;
  }
  else {
    var query_key = query_keys[filter_type];
    var redirect_url = location.protocol + '//' + location.host + '/sources-search?' + query_key + '=' + filter_value;
  }
  window.location.assign(redirect_url);
}

/*
 * Bind submit to keyup on enter, so autocompleteSelect has a chance to fire
 */
function quick_search_submit_on_enter(autocomplete_element) {
  $(autocomplete_element).on('keyup', function(e) {
    //We have to set timeout to get around closing autocomplete event
    //which somehow squelches submit
    if (e.which == 13) {
      setTimeout(function() {
        if (!redirect_in_progress) {
          $('#block-sources-views-advanced-search-filter form').submit();
        }
      }, 500)
    }
  });
}

})(jQuery);
