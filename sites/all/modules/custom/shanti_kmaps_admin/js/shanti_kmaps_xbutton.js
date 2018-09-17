/**
 * Created by edwardjgarrett on 8/2/16.
 */

(function ($) {
    Drupal.behaviors.shantiKmapsXButton = {
        attach: function (context, settings) {
            $('.kmap-typeahead-picker, .kmap-tree-picker').once('shanti-kmaps').each(function () {
                var $xbtn = $('button.searchreset', this);
                var $srch = $(".kmap-search-term:not(.kmaps-tt-hint)", this);  // the main search input
                $srch.data("holder", $srch.attr("placeholder"));

                // click
                $xbtn.click(function () {
                    if ($srch.hasClass('kmaps-tt-input')) { // typeahead picker
                        $xbtn.addClass('resetting');
                        $srch.kmapsTypeahead('setValue', '', false);
                        window.setTimeout(function () {
                            $xbtn.removeClass('resetting');
                            $xbtn.hide();
                        }, 300);
                    }
                    else { // tree picker
                        $srch.val('');
                        $xbtn.hide();
                    }
                });

                // --- focusin - focusout
                $srch.focusin(function () {
                    $srch.attr("placeholder", "");
                    $xbtn.show();
                }).focusout(function () {
                    $srch.attr("placeholder", $srch.data("holder"));

                    // see http://stackoverflow.com/questions/13980448/jquery-focusout-click-conflict
                    // and http://stackoverflow.com/questions/8981463/detect-if-hovering-over-element-with-jquery
                    if (!$xbtn.hasClass('resetting') && $xbtn.parent().find('.searchreset:hover').length > 0) {
                        if ($srch.hasClass('kmaps-tt-input')) { // typeahead picker
                            $xbtn.addClass('resetting');
                            $srch.kmapsTypeahead('setValue', '', false);
                            window.setTimeout(function () {
                                $xbtn.removeClass('resetting');
                                $xbtn.hide();
                            }, 300);
                        }
                        else { // tree picker
                            $srch.val('');
                            $xbtn.hide();
                        }
                    }
                    else {
                        var str = $srch.data("holder");
                        if (str.indexOf($srch.val()) > -1) {
                            $xbtn.hide();
                        }
                    }
                });
            });
        },
        detach: function (context, settings) {
        }
    };
})(jQuery);
