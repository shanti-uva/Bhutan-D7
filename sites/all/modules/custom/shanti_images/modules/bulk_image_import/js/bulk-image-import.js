(function ($) {
  Drupal.behaviors.bulk_image_import_review = {
    attach: function(context, settings) {
      var table = $('#bulkImageImportReviewTable');
      if(table) {
        table.find('tr').each(function() {
          $(this).find('td').eq(4).on('click', function() {});
        });
      }
    }
  };
}(jQuery));
