/**
 * @file
 * Custom javascript functionalities for search flyout search form
 */

(function ($) {
  Drupal.behaviors.sourcesViewsSearchFlyoutReset = {
    attach: function(context, settings) {
      var $searchInput = $(context).find('#edit-advanced-search-api-views-fulltext');
      var $resetButton= $searchInput.closest('.input-group').find('button.searchreset');
      // Binding to the button's inner <span> prevents clicking the icon but missing the
      // button. Not sure why the click event isn't bubbling up...
      // -samchrisinger
      $resetButton.find('span').on('click', function(event) {
        event.preventDefault();
        $searchInput.val('');
      });
    }
  };

  Drupal.behaviors.sourcesViewsSearchFlyoutInitializeFilterText = {
    attach: function (context, settings) {
      var default_publication_year_option = $('.form-item-advanced-search-publication-year input[type=radio]:checked').val();

      set_search_flyout_publication_year_filter_text_display(default_publication_year_option);
      set_search_flyout_source_type_filter_text();
      set_search_flyout_textfield_filter_text_display();
    }
  };

  Drupal.behaviors.sourcesViewsSearchFlyoutSetPublicationTypeSelectEventHandler = {
    attach: function (context, settings) {
      $('#edit-advanced-biblio-publication-type').change(function() {
        $('#edit-biblio-publication-type').val($(this).val());
        set_search_flyout_source_type_filter_text();
      });
    }
  };

  Drupal.behaviors.sourcesViewsSearchFlyoutSetPublicationYearOptionEventHandler = {
    attach: function (context, settings) {
      $('#edit-advanced-search-publication-year .form-type-radio').click(function(e) {
        var publication_year_option_value = $(this).find('input[type="radio"]').val();
        // Update publication years
        if (publication_year_option_value != 'range') {
          var start_year;
          var end_year;
          if (publication_year_option_value === (new Date()).getFullYear().toString()) {
            start_year = end_year = publication_year_option_value;
          }
          else {
            // Past 12 months
            start_year = publication_year_option_value;
            end_year = (parseInt(publication_year_option_value) + 1).toString();
          }
          $('#edit-advanced-search-start-year').attr('value', start_year);
          $('#edit-advanced-search-end-year').attr('value', end_year);
          update_year_of_publication_range_text_label(start_year, end_year);
        }
        else {
          update_year_of_publication_range_text_label(get_publication_start_year(), get_publication_end_year());
        }

        set_search_flyout_publication_year_filter_text_display(publication_year_option_value);
        set_read_only_publication_year(publication_year_option_value);
        // Update publication year radio button class and markup
        $('#edit-advanced-search-publication-year div.iradio_minimal-red').removeClass('checked');
        $('#edit-advanced-search-publication-year').find('input[name="advanced_search_publication_year"]').prop('checked', false);
        $(this).find('div.iradio_minimal-red').addClass('checked');
        $(this).find('input[type="radio"].form-radio.icheck-input').prop('checked', true);
        e.preventDefault();
      });
    }
  };

  Drupal.behaviors.sourcesViewsSearchFlyoutInitializePublicationYears = {
    attach: function (context, settings) {
      var selected_publication_year_option = $('input[name=advanced_search_publication_year]:checked').val();
      // Set publication year default start year and end year values
      var default_publication_end_year;
      var default_publication_start_year;
      if (selected_publication_year_option != 'range') {
        var publication_year = parseInt(selected_publication_year_option);
        default_publication_start_year = publication_year;
        default_publication_end_year = publication_year;
      }
      else {
        default_publication_start_year = get_publication_start_year();
        default_publication_end_year = get_publication_end_year();
      }

      var setYears = function() {
        set_search_flyout_publication_year_filter_text_display('range');
      };
      var validate = function() {
        $(this).valid();
      };

      $('#edit-advanced-search-start-year')
        .attr('value', default_publication_start_year)
        .keyup(setYears)
        .change(validate);

      $('#edit-advanced-search-end-year')
        .attr('value', default_publication_end_year)
        .keyup(setYears)
        .change(validate);

      $('#edit-advanced-search-end-year').closest('form').validate({
        onkeyup: true,
        rules: {
          advanced_search_start_year: {
            range: [get_default_publication_start_year(), get_default_publication_end_year()],
            max: function(){
              return get_publication_end_year();
            }
          },
          advanced_search_end_year: {
            range: [get_default_publication_start_year(), get_default_publication_end_year()],
            min: function(){
              return get_publication_start_year();
            }
          }
        }
      });
      set_read_only_publication_year(selected_publication_year_option);
    }
  };

  Drupal.behaviors.sourcesViewsSearchFlyoutSetClearButtonHandler = {
    attach: function (context, settings) {
      $('#sources-views-advanced-search-form #edit-clear').click(function(e) {
        // Set filter text display to default
        $('.source-type-selected-filter').text('All');
        $('#sources-views-advanced-search-form .form-text, .field-selected-filter').val('');
        $('.year-selected-filter').text(', ' + get_publication_start_year() + ' - ' + get_publication_end_year());
        // Set input text fields and dropdown fields to default
        $('#edit-advanced-biblio-publication-type').selectpicker('val', 0);
        $('.field-selected-filter').text('');
        $('#edit-condition-option').val('all').change();
        $('#edit-advanced-search-start-year').val(get_default_publication_start_year());
        $('#edit-advanced-search-end-year').val(get_default_publication_end_year());
        // Set publication year option markup and class to default
        $('#edit-advanced-search-publication-year div.iradio_minimal-red').removeClass('checked');
        $('#edit-advanced-search-publication-year-range').parent().addClass('checked');
        $('#edit-advanced-search-publication-year-range').prop('checked', true);
        // Set publication year range text display to default
        $('.publication-year-start').text(get_default_publication_start_year());
        $('.publication-year-end').text(get_default_publication_end_year());
        e.preventDefault();
      });
    }
  };

  Drupal.behaviors.sourcesViewsSearchFlyoutSetFormSubmitHandler = {
    attach: function (context, settings) {
      var submit_widgets = [
        '#views-exposed-form-biblio-search-api-page input[type="text"]',
        '#views-exposed-form-biblio-search-api-page input[type="select"]',
        '#views-exposed-form-biblio-search-api-page input[type="radio"]',
      ];
      var submit_element_selectors = submit_widgets.join(', ');

      $(submit_element_selectors).keypress(function (e) {
        if (e.which == 13) { // Enter key
          $('.sources-custom-search-form').submit();
          return false;
        }
      });
    }
  };

  function set_read_only_publication_year(selected_publication_year_option) {
    if (selected_publication_year_option != 'range') {
      $('#edit-advanced-search-start-year').prop('disabled', true);
      $('#edit-advanced-search-end-year').prop('disabled', true);
    }
    else {
      $('#edit-advanced-search-start-year').prop('disabled', false);
      $('#edit-advanced-search-end-year').prop('disabled', false);
    }
  }

  function set_search_flyout_source_type_filter_text() {
    var source_type_text = 'All';
    if ($('#edit-advanced-biblio-publication-type option:selected').val() != '') {
      source_type_text = $('#edit-advanced-biblio-publication-type option:selected').text();
    } else {
        var params = parse_search_params();
        if (params['advanced_biblio_publication_type']) {
            setTimeout(function() {
                $('#edit-advanced-biblio-publication-type').selectpicker('val', params['advanced_biblio_publication_type']);
            }, 500);
        }
    }
    $('.source-type-selected-filter').text(source_type_text);
  }

  function set_search_flyout_textfield_filter_text_display() {
    var text_fields = [
      $('#edit-title').val(),
      $('#edit-search-text-biblio-author').val(),
      $('#edit-search-text-biblio-publisher').val(),
      $('#edit-search-text-biblio-publish-place').val(),
      $('#edit-search-text-biblio-abstract').val(),
      $('#edit-search-text-zotero-tags').val(),
    ];
    var text_field_values = [];

    for (var i = 0; i < text_fields.length; i++) {
      if (text_fields[i]) {
        text_field_values.push(text_fields[i]);
      }
    }

    if (text_field_values.length == 1) {
      $.each(text_field_values, function( key, value ){
        $('.field-selected-filter').text(', ' + value);
      });
    }
  }

  function set_search_flyout_publication_year_filter_text_display(option_value) {
    var publish_year_text;
    var start_year;
    var end_year;
    if (option_value === (new Date()).getFullYear().toString()) {
      start_year = end_year = option_value;
      publish_year_text = ', ' + option_value;
    }
    else {
      if (option_value != 'range') {
        start_year = option_value;
        end_year = (parseInt(option_value) + 1).toString();
      }
      else {
        start_year = get_publication_start_year();
        end_year = get_publication_end_year();
      }
      publish_year_text = ', ' + start_year + ' - ' + end_year;
    }
    update_year_of_publication_range_text_label(start_year, end_year);
    $('.year-selected-filter').text(publish_year_text);
  }

  function update_year_of_publication_range_text_label(start_year, end_year) {
    $('.publication-year-start').text(start_year);
    $('.publication-year-end').text(end_year);
  }

  function get_default_publication_start_year() {
    var default_publication_start_year = parseInt($('#unfiltered-earliest-published-year').val());
    return default_publication_start_year;
  }

  function get_publication_start_year() {
    var startYear = $('#edit-advanced-search-start-year').val();
    if (startYear) {
      return parseInt(startYear);
    } else {
      return get_default_publication_start_year();
    }
    /*var default_publication_start_year = get_default_publication_start_year();
    var publication_start_year = default_publication_start_year;
    if ($('#earliest-published-year').length) {
      publication_start_year = parseInt($('#earliest-published-year').val());
    } else {
        var params = parse_search_params();
        if (params['advanced_search_start_year']) {
             publication_start_year = params['advanced_search_start_year'];
        }
    }
    return publication_start_year;
    */
  }

  function parse_search_params() {
    var ss = window.location.search.replace("?","");
    var pts = ss.split('&');
    var params = {};
    for (var n in pts) {
        var ppts = pts[n].split('=');
        if (ppts.length == 2) {
            params[ppts[0]] = ppts[1];
        }
    }
    return params;
  }
  function get_default_publication_end_year() {
    var default_publication_end_year = parseInt($('#unfiltered-latest-published-year').val());
    return default_publication_end_year;
  }

  function get_publication_end_year() {
    var endYear = $('#edit-advanced-search-end-year').val();
    if (endYear) {
      return parseInt(endYear);
    } else {
      return get_default_publication_end_year();
    }
    /*
    var default_publication_end_year = get_default_publication_end_year();
    var publication_end_year = default_publication_end_year;
    if ($('#latest-published-year').length) {
      publication_end_year = parseInt($('#latest-published-year').val());
    } else {
        var params = parse_search_params();
        if (params['advanced_search_end_year']) {
             publication_end_year = params['advanced_search_end_year'];
        }
    }
    return publication_end_year;
    */
  }
})(jQuery);
