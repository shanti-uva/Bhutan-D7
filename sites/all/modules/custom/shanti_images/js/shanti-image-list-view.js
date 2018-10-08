(function($) {
    $(document).ready(function() {
        $('#shanti-image-filters legend').click(function() {
            var sif = $('#shanti-image-filters');
            if (sif.hasClass('collapsed')) {
                sif.removeClass('collapsed').addClass('expanded');
                $('.view-filters').slideDown();
            } else {
                sif.removeClass('expanded').addClass('collapsed');
                $('.view-filters').slideUp();
            }
        });
    })
})(jQuery);