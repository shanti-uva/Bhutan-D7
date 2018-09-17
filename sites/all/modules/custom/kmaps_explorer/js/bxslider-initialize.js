(function ($) {
  Drupal.behaviors.kmapsExplorerBxslider = {
    attach: function (context, settings) {
      $('#carousel-feature-slides').once('kmaps-explorer').each(function () {
        var $carousel = $(this);

        var $selected_li = $carousel.children('li');
        $selected_li.children('a').bind('click', function (e) {
          e.preventDefault();
          $selected_li.removeClass('active');
          $(this).parent().addClass('active');
        });

        if ($carousel.is('.bx-large-slides')) {
          $carousel.bxSlider({
            slideMargin: 10,
            pager: true,
            controls: true,
            autoReload: true,
            moveSlides: 1,
            infiniteLoop: false,
            hideControlOnEnd: true,
            breaks: [{screen: 0, slides: 1, pager: false}, {screen: 380, slides: 1}, {
              screen: 450,
              slides: 2
            }, {screen: 768, slides: 3}, {screen: 1200, slides: 4}]
          });
        }
        else if ($carousel.is('.bx-small-slides')) {
          $carousel.bxSlider({
            slideMargin: 10,
            pager: true,
            controls: true,
            autoReload: true,
            moveSlides: 1,
            infiniteLoop: false,
            hideControlOnEnd: true,
            breaks: [{screen: 0, slides: 1, pager: false}, {screen: 400, slides: 2}, {
              screen: 550,
              slides: 3
            }, {screen: 768, slides: 4}, {screen: 1050, slides: 5}]
          });
        }

      });
    }
  };

})(jQuery);
