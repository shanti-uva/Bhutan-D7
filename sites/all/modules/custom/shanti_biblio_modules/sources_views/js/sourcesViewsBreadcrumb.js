var globalElement;
(function ($) {
  //Display the correct dropdown when user clicks a breadcrumb
  Drupal.behaviors.sourcesViewsDisplayBreadcrumbDropdowns = {
    attach: function (context, settings) {
      $('ol.breadcrumb a[href=#]').click(function(e) {
        e.preventDefault();
        e.stopPropagation();

        var term_id = $(this).attr('term_id');
        var clicked_dropdown_is_visible = sourcesDropDownIsVisible(term_id);
        sourcesHideAllDropDowns();

        if (!clicked_dropdown_is_visible) {
          sourcesDisplayBreadCrumbDropDown(term_id);
        }
      });
    }
  };
  //make sure the pointer cursor is displayed on hover if breadcrumb has a dropdown
  Drupal.behaviors.sourcesViewsSetBreadcumbCursor = {
    attach: function (context, settings) {
      $('ol.breadcrumb a').each(function(key, element) {
        var term_id = $(this).attr('term_id');
        var dropdownElement = sourcesGetDropdownElement(term_id);
        if (dropdownElement) {
          $(this).css({cursor: 'pointer'});  
        }
      });
    }
  };
  // Toggle breadcrumb dropdown collection children when a user clicks the expander button 
  // on a top parent collection item within the breadcrumb dropdown
  Drupal.behaviors.sourcesViewsToggleBreadcumbDropdownCollectionChildren = {
    attach: function (context, settings) {
      $('.breadcrumb-child-sub-top .fancytree-expander').click(function(e) {
        e.stopPropagation();
        e.preventDefault();

        var breadcrumb_children_container = $(this).parent().parent().parent().parent().next('div.breadcrumb-child');
        breadcrumb_children_container.slideToggle('fast');
        $(this).toggleClass('glyphicon-minus-sign');
        $(this).toggleClass('glyphicon-plus-sign');
      });
    }
  };
  // Close shown breadcrumb dropdown if a user clicks anywhere on the page
  Drupal.behaviors.sourcesViewsHideBreadcumbDropdown = {
    attach: function (context, settings) {
      $('body').click(function(e) {
        $('#collection-library, a.breadcrumb-dropdown-cta').removeClass('active');
        if ($('div.breadcrumb-child-container').is(':visible')) $('div.breadcrumb-child-container').hide();
        if ($('div.library-dropdown').is(':visible')) $('div.library-dropdown').hide();
      });
    }
  };
})(jQuery);

$ = jQuery;

  function sourcesHideAllDropDowns() {
    $('.breadcrumb-dropdown').css({opacity: 0, 'pointer-events': 'none'}).hide();
  }

  function sourcesDisplayBreadCrumbDropDown(term_id) {
    var breadcrumbElement = sourcesGetBreadcrumbElement(term_id);
    var dropdownElement   = sourcesGetDropdownElement(term_id);

    sourcesCenterFirstElementWithSecondHorizontally(dropdownElement, breadcrumbElement);
    sourcesPositionFirstElementBelowSecondPlusOffset(dropdownElement, breadcrumbElement, 5);
    $(dropdownElement).css({opacity: 1, 'pointer-events': 'all'}).show();
    globalElement = dropdownElement;
  }

  function sourcesDropDownIsVisible(term_id) {
    var dropdownElement = sourcesGetDropdownElement(term_id);
    var el = $(dropdownElement).get()[0];
    return $(dropdownElement).is(':visible');

  }

  function sourcesGetDropdownElement(term_id) {
    var dropdownElement = $('.breadcrumb-dropdown[term_id="' + term_id + '"]');
    if (dropdownElement.length) {
      return dropdownElement;
    }
  }

  function sourcesGetBreadcrumbElement(term_id) {
    var breadcrumbElement = $('ol.breadcrumb a[term_id="' + term_id + '"]');
    if (breadcrumbElement.length) {
      return breadcrumbElement;
    }
  }

  function sourcesPositionFirstElementBelowSecondPlusOffset(firstElement, secondElement, offsetPixels) {
    if (firstElement && secondElement) {
        var top = $(secondElement).offset().top + offsetPixels;
        $(firstElement).offset({top: top + 'px'});
    }
  }

  /*
   *  Align the horizontal center of two elements, moving the first to align with the second
   */
  function sourcesCenterFirstElementWithSecondHorizontally(firstElement, secondElement) {
    var secondElementCenter = sourcesFindElementHorizontalCenter(secondElement);
    //sourcesSetElementHorizontalCenter(firstElement, secondElementCenter);
  }

  function sourcesFindElementHorizontalCenter(element) {
    if (element) {
        element = $(element);
        var width = $(element).width();
        var position = $(element).offset();
        var center = (width / 2) + position.left;
        return center;
    }
  }

  function sourcesFindElementBottom(element) {
    element = $(element);
    var position = $(element).offset();
    var height = $(element).height();
    var bottom = (height / 2) + position.top;
    return bottom;
  }

  function sourcesSetElementHorizontalCenter(element, centerPosition) {
    var width = $(element).width();
    var leftEdgePosition = centerPosition - (width / 2);
    leftEdgePosition = leftEdgePosition > 0 ? leftEdgePosition : 0;
    $(element).offset({left: leftEdgePosition});
  }

