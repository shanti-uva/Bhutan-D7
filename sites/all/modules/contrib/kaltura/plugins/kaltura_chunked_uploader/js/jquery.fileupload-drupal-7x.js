/**
 * jquery.fileupload Drupal UI helper
 */
(function (factory) {
  'use strict';
  if (typeof define === 'function' && define.amd) {
    // Register as an anonymous AMD module:
    define([
      'jquery',
      './jquery.fileupload'
    ], factory);
  } else {
    // Browser globals:
    factory(
      window.jQueryFileUpload
    );
  }
}(function ($) {
  'use strict';

  var originalDone = $.blueimp.fileupload.prototype.options.done;
  var originalOnCancel = $.blueimp.fileupload.prototype.onCancel;

  $.widget('blueimp.fileupload', $.blueimp.fileupload, {
    options: {
      done: function (e, data) {
        originalDone.call(this, e, data);

        if (data.textStatus === 'success') {
          var widget = $(e.target);
          var uploadBoxId = widget.fileupload('getUploadBoxId', e, data);
          var uploadBox = widget.fileupload('getUploadBox', uploadBoxId);
          $('#progress .anchor .message', uploadBox).css('color', '');
        }
      }
    },

    onCancel: function (uploadBoxId) {
      originalOnCancel.call(this, uploadBoxId);

      var $widget = $('#uploadbox' + uploadBoxId);
      $('#progress', $widget).addClass('hidden');
      $('#successmsg', $widget)
        .removeClass('hidden status error')
        .addClass('warning');
    },

    onError: function (error, uploadBoxId) {
      displayError(error, uploadBoxId);
      this._trigger('error', null, { error: error, uploadBoxId: uploadBoxId });
    }
  });

  function displayError(error, uploadBoxId) {
    var $widget = $('#uploadbox' + uploadBoxId);
    $('#fileupload', $widget).addClass('hidden');
    $('#progress', $widget).addClass('hidden');
    $('#cancelBtn', $widget).addClass('hidden');
    $('#successmsg', $widget)
      .text(error)
      .removeClass('hidden status warning')
      .addClass('error');
  }
}));
