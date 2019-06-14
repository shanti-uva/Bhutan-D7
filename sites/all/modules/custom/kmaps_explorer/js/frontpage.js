(function ($) {
  Drupal.behaviors.kmapsExplorerFrontPage = {
    attach: function (context, settings) {

      $('.landing-popover.open-task', context).click(function() {
        $(this).toggleClass('open-task');
        var $that = $(this);
        var app = $(this).data('app');
        var kid = $(this).data('id');
        $('.place-open-' + kid, context).toggle('fast');

        $.ajax({
          url: '/mandala/popover/populate/' + app + '/' + kid,
          beforeSend: function() {
            $that.toggleClass('fa-spin shanticon-spinner');
          },
          success: function(data) {
            if (data.node) {
              // if (data.node && data.node.header) {
              //   $('#pop-title-' + kid, context).html(data.node.header);
              // }
              $('.place-open-' + kid, context).html(populateSolrFrontpage(data));
            }
          },
          complete: function() {
            $that.toggleClass('fa-spin shanticon-spinner');
          }
        });

      });

      function populateSolrFrontpage(data) {
        //Create markup for related places in images.
        var template = $('#popover-front').html();
        var templateScript = Handlebars.compile(template);
        var html = templateScript(data);
        return html;
      }

    }
  };

})(jQuery);
