(function ($) {

  Drupal.behaviors.shantiKmapsSubjectsHomepage = {
    attach: function (context, settings) {

        if ($(".main-col .carousel-header").length > 0 ) {
              $(".breadcrumb").css('display', 'none');
              $(".btn.view-offcanvas-sidebar").addClass('hidden');
              $("body").addClass('home-carousel');

        } else {
              $(".breadcrumb").css('display', 'block');
              $(".btn.view-offcanvas-sidebar").removeClass('hidden');
              $("body").removeClass('home-carousel');
        }
    }
  };

})(jQuery);
