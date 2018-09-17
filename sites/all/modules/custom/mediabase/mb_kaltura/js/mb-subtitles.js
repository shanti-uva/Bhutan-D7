(function ($) {
  Drupal.behaviors.mbSubtitles = {
    attach: function (context, settings) {
      $('[data-transcripts-role=transcript-controls]', context)
        .addBack('[data-transcripts-role=transcript-controls]')
        .once('subtitles')
        .each(function () {
          $('section.content-section > .tab-content').before('<div id="mb-messages" class="messages"></div>');
          var $transcriptControls = $(this);
          var trid = $transcriptControls.attr('data-transcripts-id');
          var offset = Drupal.settings.mediabase.prefix.length;
          var $transcriptOptions = $transcriptControls.find('select.transcript-options');
          $transcriptOptions.find('optgroup[data-type=subtitles] option').each(function() {
            this.selected = this.hasAttribute('data-selected');
          });
          $transcriptOptions.selectpicker('refresh');
          $transcriptControls.one('click', 'button.selectpicker', function() {
            var $ul = $('.kaltura-embed iframe').first().contents().find('div.mwPlayerContainer div.closedCaptions > ul');
            // If user clicks on dropdown button before kaltura has loaded the CCs, or if there are no CCs to load,
            // then this code won't apply and no hourglass icons will appear. This isn't ideal, but it's not the end
            // of the world.
            if ($ul.length == 1) {
              $transcriptOptions.find('optgroup[data-type=subtitles] option').each(function() {
                var option = this;
                // if production, then subtitle track names have empty prefix
                var prefix = Drupal.settings.mediabase.site_env == 'prod' ? '' : Drupal.settings.mediabase.site_env + '/';
                var $caption = $ul.find('li a[title="' + prefix + $(option).text() + '"]');
                if ((option.hasAttribute('data-selected') && $caption.length == 0) || (!option.hasAttribute('data-selected') && $caption.length == 1)) {
                    $(option).prop('disabled', true).addClass('pending');
                }
              });
              $transcriptOptions.selectpicker('refresh');
            }
          });
          $transcriptOptions.change(function (e) {
            /* add subtitle track */
            $('optgroup[data-type=subtitles] option:selected', this).not('[data-selected]').each(function () {
              var $option = $(this);
              var $anchor = $transcriptOptions.next('.bootstrap-select').find('a.opt-subtitles').eq($option.index());
              if (!$anchor.hasClass('processing') && !$anchor.hasClass('pending')) {
                $anchor.addClass('processing');
                $.ajax({
                  type: "POST",
                  url: Drupal.settings.basePath + 'mb_kaltura/subtitles/add',
                  data: {
                    'nid': Drupal.settings.mediabase.nid,
                    'trid': trid.split('-').pop(),
                    'tier_id': $option.attr('value').substring(offset)
                  },
                  success: function (response) {
                    $('#mb-messages').append(response.message);
                    switch (response.status) {
                      case 'success':
                        $option.attr('selected', 'selected')
                          .attr('data-selected', response.data.caption_ids[0])
                          .prop('disabled', true)
                          .addClass('pending');
                        $transcriptOptions.selectpicker('refresh'); //refresh also removes 'processing' class
                        break;
                      case 'error':
                        break;
                    }
                  }
                });
              }
            });

            /* remove subtitle track */
            $('optgroup[data-type=subtitles] option:not(:selected)', this).filter('[data-selected]').each(function () {
              var $option = $(this);
              var $anchor = $transcriptOptions.next('.bootstrap-select').find('a.opt-subtitles').eq($option.index());
              if (!$anchor.hasClass('processing') && !$anchor.hasClass('pending')) {
                $anchor.addClass('processing');
                $.ajax({
                  type: "POST",
                  url: Drupal.settings.basePath + 'mb_kaltura/subtitles/delete',
                  data: {
                    'nid': Drupal.settings.mediabase.nid,
                    'caption_id': $option.attr('data-selected'),
                    'tier_id': $option.attr('value').substring(offset)
                  },
                  success: function (response) {
                    $('#mb-messages').append(response.message);
                    switch (response.status) {
                      case 'success':
                        $option.removeAttr('selected data-selected')
                          .prop('disabled', true)
                          .addClass('pending');
                        $transcriptOptions.selectpicker('refresh'); //refresh also removes 'processing' class
                        break;
                      case 'error':
                        break;
                    }
                  }
                });
              }
            });
          });
        });
    }
  }
})(jQuery);
