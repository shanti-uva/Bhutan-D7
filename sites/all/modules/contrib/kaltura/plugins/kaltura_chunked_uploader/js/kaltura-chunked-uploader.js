(function (Drupal) {
  'use strict';

  var lastUploaderId;

  Drupal.behaviors.kaltura_chunked_uploader = {
    attach: function (ctx, settings) {
      if (!window.jQueryFileUpload) {
        return;
      }

      var $ = window.jQueryFileUpload;
      var moduleSettings = settings.kaltura_chunked_uploader || {};
      var fileTypes = moduleSettings.fileTypes || [];
      var ks = moduleSettings.ks || '';
      var serviceUrl = moduleSettings.serviceUrl || '';
      var uploaderId = moduleSettings.uploaderId || 1;

      var $hook = $('#uploadHook' + uploaderId);

      if (!$hook.length || lastUploaderId === uploaderId) {
        return;
      }

      lastUploaderId = uploaderId;

      var context = $('#uploadbox' + uploaderId);
      // Init the media upload widget
      var widget = $hook.fileupload({
        // need to pass these parameters to trigger chunk upload
        maxChunkSize: 3000000,
        dynamicChunkSizeInitialChunkSize: 1000000,
        dynamicChunkSizeThreshold: 50000000,
        dynamixChunkSizeMaxTime: 30,
        uploadBoxId: uploaderId,
        ks: ks,
        host: serviceUrl,
        apiURL: serviceUrl + '/api_v3/',
        url: serviceUrl + '/api_v3/?service=uploadToken&action=upload&format=1',
        fileTypes: $.map(fileTypes, function (fileType) { return '*.' + fileType; }).join(';'),
        messages: {
          acceptFileTypes: 'File type not allowed',
          maxFileSize: 'File is too large',
          minFileSize: 'File is too small'
        }
      })
        // triggered after upload has finished
        .bind('fileuploaddone', function onUploadDone(event, data) {
          var file = data.files[0];
          var name = (file && file.name) || new Date().toString();

          var $submitButton = $('#submitBtn' + uploaderId, context).removeClass('hidden');
          var base = $submitButton.attr('id');

          Drupal.ajax[base] = new Drupal.ajax(base, $submitButton[0], {
            url: window.location.protocol + '//' + window.location.hostname +
              (window.location.port ? ':' + window.location.port : '') +
              settings.basePath + settings.pathPrefix + 'kaltura-chunked-uploader/ajax/add-media/' +
              encodeURIComponent(data.uploadTokenId) + '/' +
              encodeURIComponent(name),
            event: 'click',
            progress: {
              type: 'throbber'
            }
          });
        });

      // Wait for the user to select a file
      $('#fileupload', context).bind('submit', function onFileSelected(event) {
        event.preventDefault();
        event.stopImmediatePropagation();

        // Initiate actual file uploading
        widget.fileupload('add', { fileInput: $(this).find('#fileinput') });
      });
    }
  };
}(window.Drupal));
