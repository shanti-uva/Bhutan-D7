(function ($) {
    Drupal.behaviors.shantiImagesTextFieldPlaceholders = {
        attach: function (context, settings) {
            
            // Search for Title fields
            $('.views-widget-filter-title .form-item input.form-text').attr({
                'placeholder': 'Search Title',
                'size':'13'
            });
            $('.views-widget-filter-title_1 .form-item-agent input.form-text').attr({
                'placeholder':'Search Agent',
                'size':'13'
            });
        }
    };
}) (jQuery);