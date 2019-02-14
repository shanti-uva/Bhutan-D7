;(function($) {
  Drupal.behaviors.kmaps_views_solr = {
    attach: function(context, settings) {
      //Dom-id replacement for Better expose filters
      var domid = $(".shanti-view-dom-id").attr("data-dom-id");
      $("div.view-dom-id-" + domid).removeClass("view-dom-id-" + domid);
      $(".shanti-view-dom-id").addClass("view-dom-id-" + domid);
    }
  };

  Drupal.behaviors.kmaps_views_solr_images = {
    attach: function(context, settings) {
      if (context != document) {
        // for ajax calls in kmaps photos need to reset the pig gallery.
        if ($('body').hasClass('kmaps-photos') && typeof(context) == 'object' && context[0].localName == 'div') {
            if (typeof(settings.shanti_grid_view) != 'undefined') {
              settings.shanti_grid_view.resetpig = true;
            }
        }

      }

      if ($('.shanti-filters .pager a[href*="/ajax"]').length > 0) {
        window.location.reload();
      }
    }
  };


})(jQuery);

//Keep focus after autosubmit of solr view filters.
function SetCaretAtEnd(elem) {
    var elemLen = elem.value.length;
    // For IE Only
    if (document.selection) {
        // Set focus
        elem.focus();
        // Use IE Ranges
        var oSel = document.selection.createRange();
        // Reset position to 0 & then set at end
        oSel.moveStart('character', -elemLen);
        oSel.moveStart('character', elemLen);
        oSel.moveEnd('character', 0);
        oSel.select();
    }
    else if (elem.selectionStart || elem.selectionStart == '0') {
        // Firefox/Chrome
        elem.selectionStart = elemLen;
        elem.selectionEnd = elemLen;
        elem.focus();
    } // if
} // SetCaretAtEnd()

var textboxToFocus = {};

jQuery(function($) {
    var addFocusReminder = function(textbox) {
        textbox.bind('keypress keyup', function(e) {
            textboxToFocus.formid = $(this).closest('form').attr('id');
            textboxToFocus.name = $(this).attr('name');

            if(e.type == 'keypress') {
                if(e.keyCode != 8) { // everything except return
                    textboxToFocus.value = $(this).val() + String.fromCharCode(e.charCode);
                } else {
                    textboxToFocus.value = $(this).val().substr(0, $(this).val().length-1)
                }
            }
            else { // keyup
                textboxToFocus.value = $(this).val();
            }

            //Prevent enter key from triggering submit
            var charCode = e.charCode || e.keyCode;
            if (charCode === 13) {
                return false;
            }
        });
    };

    addFocusReminder($('.view-filters-mb input:text.ctools-auto-submit-processed'));
    $(document).ajaxComplete(function(event,request, settings) {
        if(typeof textboxToFocus.formid !== 'undefined') {
            var textBox = $('#' + textboxToFocus.formid + ' input:text[name="' + textboxToFocus.name + '"]');
            textBox.val(textboxToFocus.value);
            if (textBox[0]) {
                SetCaretAtEnd(textBox[0]);
                addFocusReminder(textBox);
                //textboxToFocus = {}; // if you have other auto-submitted inputs as well
            }
        }
    });
});