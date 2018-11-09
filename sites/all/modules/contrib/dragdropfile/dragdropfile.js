
(function ($) {



  // Browers that don't know File, won't have event.dataTransfer.files.
  if (!window.File || !File.prototype) {
    return;
  }



  Drupal.dragDropFile || (Drupal.dragDropFile = {
    progress: {
      uploading: Drupal.t("Uploaded !done / !total (batch !current_batch / !total_batches)"),
      processing: Drupal.t("Processing batch !current_batch / !total_batches ... Patience..."),
    },
  });



  // Override Drupal.file.progressBar to NOT wait 0.5 sec.
  Drupal.file && (Drupal.file.progressBar = function(e) {
    $(this).closest('div.form-managed-file').find('div.ajax-progress-bar').show();
  });



  function formatKB(bytes) {
    return String(Math.round(bytes / 1024));
  }

  function formatMB(bytes) {
    var num = String(Math.round(bytes / 1024 / 1024 * 10) / 10);
    if (num.indexOf('.') == -1) {
      num += '.0';
    }
    return num;
  }

  function batchProgress(progress, totalSize, doneSize, processingBatch, currentBatch, totalBatches) {
    var message = Drupal.dragDropFile.progress.processing;
    var params = {
      "!current_batch": currentBatch,
      "!total_batches": totalBatches,
    };

    if (!processingBatch) {
      message = Drupal.dragDropFile.progress.uploading;

      var mb = totalSize > 1e6;
      var format = mb ? formatMB : formatKB;
      var sizeLabel = mb ? ' MB' : ' KB';

      params["!done"] = format(doneSize);
      params["!total"] = format(totalSize) + sizeLabel;
    }

    message = Drupal.formatString(message, params);
    progress.object.setProgress(Math.round(doneSize / totalSize * 100), message);
  }



Drupal.behaviors.dragDropFile = {
  attach: function(context, settings) {

    settings.ajax && $.each(settings.ajax, function(base, cfg) {
      if (cfg.element && cfg.element.type === 'submit' && cfg.element.value == Drupal.t('Upload')) {
        cfg.overriddenByDragDropFile = true;
        var
          ajax = Drupal.ajax[base],
          options = ajax.options,
          $submit = $('#' + base);
        options.ajax = ajax;

        if (options.overriddenByDragDropFile || !$submit.length || !$submit.hasClass('i-am-dragdropfile')) return;

        options.onProgress = function(e) {
          batchProgress(this.progress, e.total, e.done, (e.done == e.total), 1, 1);
        };

        options.overriddenByDragDropFile = true;
        var oldBeforeSend = options.beforeSend;
        options.beforeSend = function(xhr, options) {
          // Do Drupal magic here.
          oldBeforeSend.call(this, xhr, options);

          // Do my magic here.
          if (options.files) {
            $.each(options.files, function(i, file) {
              options.data.append(options.inputName, file);
            });
          }
        };

        var $wrapper = $('#' + cfg.wrapper);
        $wrapper.data('ajax-base', base);
        $wrapper.attr('data-ddf-title', $submit.attr('data-ddf-title'));
        $wrapper.bind({
          dragover: function(e) {
            e.preventDefault();
            var $this = $(this);

            $this.addClass('over');
          }, // dragover

          dragleave: function(e) {
            e.preventDefault();
            var $this = $(this);

            $this.removeClass('over');
          }, // dragleave

          drop: function(e) {
            var $this = $(this);
            $this.removeClass('over');
            var $wrapper = $this.parent();

            if ('INPUT' == e.target.nodeName) {
              console.log("DON'T handle drop event");
              return;
            }

            e.preventDefault();

            // @todo
            var
              base = $this.data('ajax-base'),
              $input = $wrapper.find('input.form-file').first(),
              input = $input[0],
              files = Array.prototype.slice.call(e.originalEvent.dataTransfer.files),
              $form = $input.closest('form'),
              inputName = $input.attr('name');

            // Append only as many files as are allowed.
            var max = parseFloat($input.attr('max'));
            if (max) {
              files = files.slice(0, max);
            }

            // Validate files.
            if ($input.data('validate') == 'settings' && Drupal.settings.file && Drupal.settings.file.elements && Drupal.settings.file.elements['#' + input.id]) {
              var
                fakeInput = document.createElement('input'),
                fails = 0;
              for (var i=0, L=files.length; i<L; i++) {
                var
                  fileName = files[i].name,
                  extensions = Drupal.settings.file.elements['#' + input.id];
                fakeInput.value = fileName;
                var valid = Drupal.file.validateExtension.call(fakeInput, {data: {extensions: extensions}}) !== false;
                if (!valid) {
                  fails++;
                  delete files[i];
                  continue;
                }

                if (files[i].size > Drupal.settings.dragDropFile.max_filesize) {
                  fails++;
                  delete files[i];
                  continue;
                }
              }

              if (fails) {
                $('.file-upload-js-error').remove();

                var error = Drupal.t('@fails of @total files invalid.', {
                  "@fails": fails,
                  "@total": L
                });
                $input.closest('div.form-managed-file').prepend('<div class="messages error file-upload-js-error">' + error + '</div>');
              }

              files = files.filter(function(el) { return !!el; });
              if (!files.length) {
                return;
              }
            }

            var totalFiles = files.length;
            var totalSize = files.reduce(function(size, file) {
              return size + file.size;
            }, 0);
            var doneFiles = 0;
            var doneSize = 0;

            var batches = createBatches(files);
            var totalBatches = batches.length;
            var progress;

            function createBatches(files) {
              var batches = [[]];
              var batchSize = 0;
              for (var i=0; i<files.length; i++) {
                var file = files[i];

                if (batchSize && (batchSize + file.size > Drupal.settings.dragDropFile.max_upload_size || batches[batches.length-1].length >= Drupal.settings.dragDropFile.max_files)) {
                  batches.push([]);
                  batchSize = 0;
                }

                batches[batches.length-1].push(file);
                batchSize += file.size;
              }

              return batches;
            }

            function startUpload() {
              // 'Unset' all file inputs.
              $form.find('input[type="file"]').val('').each(function() {
                var $this = $(this);
                $this.data('actualInputName', this.name);
                $this.removeAttr('name');
              });

              // Start uploading
              sendNextBatch();
            }

            function sendNextBatch() {
              // Find next batch
              var batch = batches.pop();
              if (!batch) {
                batchProgress(progress, totalSize, doneSize, true, totalBatches, totalBatches);

                // All done
                return allFilesDone();
              }

              // For every batch
              var
                settings = Drupal.settings.ajax[base],
                ajax = Drupal.ajax[base],
                options = ajax.options,
                $input = $wrapper.find('input.form-file').first(),
                $submit = $input.closest('.form-item').find(Drupal.settings.dragDropFile.submitButtonSelector).first();

              inputName = $input.attr('name') || inputName;

              // Override success callback to add something at the very end.
              var oldSuccess = options.success;
              options.success = function(response, status, xhr) {
                var result = oldSuccess.call(this, response, status);

                // 'base' will most likely have changed.
                var
                  oldBase = base,
                  regex = new RegExp('^' + oldBase.replace(/\-\d+\-/, '-\\\d+-') + '$');
                if (response[0] && response[0].settings && response[0].settings.ajax) {
                  $.each(response[0].settings.ajax, function(potentialBase, _settings) {
                    if (potentialBase.match(regex)) {
                      base = potentialBase;
                    }
                  });
                }

                // Update upload statistics
                doneFiles += batch.length;
                doneSize += batch.reduce(function(size, file) {
                  return size + file.size;
                }, 0);

                // Send next file
                sendNextBatch();

                return result;
              };

              // Prep upload
              options.files = batch;
              options.inputName = inputName;
              options.onProgress = function(e) {
                batchProgress(progress, totalSize, doneSize + e.done, (e.done == e.total), totalBatches-batches.length, totalBatches);
              };

              // Upload!
              $submit.trigger(settings.event);

              // Init local progress bar immediately after submission starts
              progress = ajax.progress;
              batchProgress(progress, totalSize, doneSize, false, totalBatches-batches.length, totalBatches);
            }

            function allFilesDone() {
              // Reset all file inputs.
              $form.find('input[type="file"]').each(function() {
                var $this = $(this);
                $this.attr('name', $this.data('actualInputName'));
                $this.removeData('actualInputName');
              });
            }

            startUpload();

          } // drop
        }).addClass('dragdropfile-processed'); // bind events
      }
    });

  }
};



})(jQuery);
