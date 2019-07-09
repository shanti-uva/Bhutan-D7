(function ($) {

    Drupal.behaviors.shantiSourcesMisc = {
        attach: function (context) {
            if (context === document) {
                if ($('body').hasClass('page-collections-all')) {
                    $('td.views-field-group-access').each(function () {
                        var val = $.trim($(this).text());
                        if (val == '0') {
                            $(this).text(Drupal.t("Public"));
                        } else {
                            $(this).text(Drupal.t("Private"));
                        }
                    });
                }
            }
        }
    };
}(jQuery));