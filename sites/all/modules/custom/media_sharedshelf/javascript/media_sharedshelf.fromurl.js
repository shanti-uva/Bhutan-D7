/**
 * @file
 * Create the 'SharedShelf' tab for the WYSIWYG plugins.
 */

(function ($) {
  namespace('Drupal.media.browser.plugin');

  Drupal.media.browser.plugin.media_sharedshelf = function(mediaBrowser, options) {
    return {
      init: function() {
        tabset = mediaBrowser.getTabset();
        tabset.tabs('add', '#media_sharedshelf', 'SharedShelf');
        mediaBrowser.listen('tabs.show', function (e, id) {
          if (id == 'media_sharedshelf') {
            // We only need to set this once.
            // We probably could set it upon load.
            if (mediaBrowser.getActivePanel().html() == '') {
              mediaBrowser.getActivePanel().html(options.media_sharedshelf);
            }
          }
        });
      }
    }
  };

  // For now, I guess self registration makes sense.
  // Really though, we should be doing it via drupal_add_js and some settings
  // from the drupal variable.
  // @todo: needs a review.
  Drupal.media.browser.register('media_sharedshelf', Drupal.media.browser.plugin.media_sharedshelf);
})(jQuery);
