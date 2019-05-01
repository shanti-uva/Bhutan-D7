(function ($) {


  Drupal.behaviors.shanti_images_more_links = {
    attach: function (context, settings) {
        
        // Description more links to modals. Find more links load content via ajax and enable BS modals
        $('.shanti-image-description .desc.morelink').each(function() {
            // Create the modal link from the description more link
            var _this = $(this);
            var nid = $(this).parents('.shanti-image-description').data('nid');
             _this.html('<a href="#" data-toggle="modal" data-target="#sid-' + nid + '">' + _this.html() + '</a>');
             // Define modal ID and Selector
             var modalId = 'sid-' + nid;
             var modalSel = '#' + modalId;
            // Check if modal div has already been added 
            if ($(modalSel).length == 0) {
                // Create image description vault if necessary
                if ($('#img-desc-vault').length == 0) {
                    $('body').append('<div id="img-desc-vault"></div>');
                }
               // Add the modal div shell then load it content by calling Images endpoint for node embed
               // See shanti_images.module function shanti_images_node_embed($nid)
               $('#img-desc-vault').append('<div id="' + modalId + '" class="desc modal fade" role="dialog"></div>');
                $(modalSel).load(Drupal.settings.basePath + 'shanti-images/node-embed/' + nid, function() {
                   var title = $(modalSel).find('.modal-body h2').eq(0).hide().text();
                   $(modalSel).find('.modal-header h4').eq(0).text(title);
                   // Make sure any links in description open new window
                   $(modalSel).find('.modal-body a').each(function() {
                       $(this).attr('target', '_blank');
                   });
                });
            }
        });
        
    }
  };
  
  /**
   * Drupal Behavior for Image Node page
   *        If the array settings.shanti_images.addimages is not empty, uploads listed images
   *        When an image is added to a node this gets set in shanti_images_preprocess_node in shanti_images.module
   */
    Drupal.behaviors.shanti_images_add_images = {
        attach: function (context, settings) {
            var dsetimg = Drupal.settings.shanti_images;
            if (typeof(settings.shanti_images) == 'undefined') { dsetimg = false; }
            if (context == document) {
                var debug = (dsetimg.debug) ? true : false;
                if ($('body').is('.node-type-shanti-image')) {
                    if (dsetimg && typeof(dsetimg.addimages) != 'undefined') {
                        if (dsetimg.addimages) {
                            setTimeout(function() {
                                $('#fsslider .flex-active-slide').prepend('<p class="imgprocessing">Your image is being processed<span>.</span><span>.</span><span>.</span><br/><small style="font-size: 80%;">(Do not close this window until processing is finished)</small></p>');
                                $('#fsslider .flex-active-slide p').css({
                                    'width': '100%',
                                    'text-align':'center'
                                });
                                $('#fsslider .flex-active-slide').css('min-height', '42rem');
                                $('#fsslider .flex-active-slide img').hide();
                               }, 300);
                            var imageshowing = false;
                            dsetimg.warning = function(e) { (e || window.event).returnValue = true; return true;};
                            if (debug) { console.log('addimage array:', JSON.stringify(dsetimg.addimages)); }
                            for(var n in dsetimg.addimages) {

                                window.addEventListener('beforeunload',  dsetimg.warning);
                                var item = dsetimg.addimages[n];
                                var url = Drupal.settings.basePath + 'image/upload/' + item.nid + '/' + item.fid + '/' +
                                        item.siid;
                                if (debug) {
                                    console.log('Add Image item = ' + JSON.stringify(item));
                                    console.log('Add Image url = ' + url)
                                }
                                $.getJSON(url, function() {
                                    if (!imageshowing) {
                                         dsetimg.addimages = false;
                                         imageshowing = true;
                                         window.removeEventListener('beforeunload',  dsetimg.warning);
                                         setTimeout(function() {
                                            window.location.reload();
                                        }, 1500);
                                    }
                                });
                            }
                            
                        }
                    }
                }
            }
        }
    };
    
    /**
     * Behaviors for Shanti Image Edit Form
     */
    Drupal.behaviors.shanti_images_edit_form = {
        attach: function (context, settings) {
            // Confirm before field deletes. Uses Bootbox.
            if ($('body').hasClass('page-node-edit')) {
                var spinner = '<span class="glyphicon glyphicon-refresh glyphicon-refresh-animate"></span>';
                $('.btn-delete.ajax-processed').each(function () {
                    var btnid = $(this).attr('id');  // Get the button id
                    var inputval = $(this).prevAll('.field-type-text').find('input').val();
                    if ($(this).parents('#edit-field-image-agents').length > 0) { return true; } // return false breaks the each loop. return true is like a continue
                    // Add a beforeserialize function to potentially interrupt AJAX call
                    Drupal.ajax[btnid].beforeSerialize = function () {
                        // If the button has the class "confirm-return" it is returning already from confirmation. Do not show dialog
                        if (!$('#' + btnid).hasClass('action-confirmed')) {
                            // Otherwise, use bootbox to show the dialog
                            bootbox.trigid = btnid; // Save current button id with bootbox to access in callback
                            // Get the value of the preceding input box for confirm dialog
                            var btnnm = btnid.replace('edit-field', '').replace('en', '')
                                .replace('und', '').replace('remove-button', '');
                            btnnm = btnnm.replace(/\-/g, ' ');
                            // Create confirm message
                            var btnval = (inputval) ? '= “' + inputval + '”' : '';
                            var msg = "Are you sure you want to remove this item: " + btnnm + btnval + "?";
                            // Call bootbox confirm
                            bootbox.confirm({
                                message: msg,
                                buttons: {
                                    confirm: {
                                        label: 'Yes',
                                        className: 'btn btn-primary btbx-confirm'
                                    },
                                    cancel: {
                                        label: 'No',
                                        className: 'btn btn-primary btbx-cancel'
                                    }
                                },
                                // The callback is the key function. Bootbox returns prior to the answer here.
                                // So use the call back to set a special class on the button and retrigger
                                callback: function (result) {
                                    bootbox.hideAll(); // Hide the dialog box upon any button click
                                    if (result == true) {  // if confirmed ...
                                        // Get the current button ID and reset bootstrap variable
                                        var btnid = '#' + bootbox.trigid;
                                        bootbox.trigid = false;
                                        // Add class to
                                        $(btnid).addClass('action-confirmed');
                                        $(btnid).trigger('mousedown');
                                    }
                                }
                            });
                        }
                        // Only proceed with ajax if the button has the "action-confirmed" class
                        if ($('#' + btnid).hasClass('action-confirmed')) {
                            // Hide the trashcan icon and replace with a spinner
                            $('#' + btnid).find('span.shanticon-trash').hide();
                            $('#' + btnid).prepend(spinner);
                            return true;
                        } else {
                            return false;
                        }
                    };
                });
            }

            // Uncheck "Show end date" in new edit form
            setTimeout(function() {
                $('#edit-field-image-agents-und-form label[for=edit-field-image-agents-und-form-field-agent-dates-und-0-show-todate] > div.checked').each(function() { $(this).parent().click(); });
            }, 400);
        }
    };
    
    /**
     * IIIF admin JS Functions
     */
    Drupal.behaviors.shanti_images_admin = {
        attach: function (context, settings) {
            if (context == document) {
                //Toggle Raw JSON in IIIF admin list
                $('#iiif-filelist-json .toggle').click(function () {
                    $('#iiif-filelist-json .togglediv').toggle();
                });

                // Rearrange Settings form
                if (window.location.pathname == '/admin/config/media/shanti_images/settings') {
                    var el = $('.form-item-shanti-images-cron-unit').remove();
                    $('#edit-shanti-images-cron-age').after(el);
                }

            }
        }
    };

    Drupal.behaviors.shanti_images_image_load_fallback = {
        attach: function (context, settings) {
            if (context == document) {
                $('img').delay(5000)
                    .each(function() {
                        if (!this.complete || typeof this.naturalWidth == "undefined" || this.naturalWidth == 0) {
                                $(this).attr('src', $(this).attr('src') + '?' + new Date().getTime());
                        }
                    });
            }
        }
    };

    Drupal.behaviors.shanti_images_admin_view = {
        attach: function (context, settings) {
            if (context == document) {
                if ($('body').hasClass('page-admin-content') && $('.view-id-administration_nodes_custom_').length > 0) {
                    $('.form-item-mmsid-max, .form-item-nid-max').hide();
                    $('.form-item-mmsid-min').keyup(function() {
                      if ($('.form-item-mmsid-min input').val() != '') {
                        $('.form-item-mmsid-max').show();
                      } else {
                        $('.form-item-mmsid-max').hide();
                      }
                    });
                    $('.form-item-nid-min').keyup(function() {
                      if ($('.form-item-nid-min input').val() != '' ) {
                        $('.form-item-nid-max').show();
                      } else {
                        $('.form-item-nid-max').hide();
                      }
                    });
                    $('.form-item-mmsid-min').focusout(function() {
                        if ($('.form-item-mmsid-max input').val() === '') {
                            $('.form-item-mmsid-max input').val($('.form-item-mmsid-min input').val());
                        }
                    });
                    $('.form-item-nid-min').focusout(function() {
                        if ($('.form-item-nid-max input').val() === '') {
                            $('.form-item-nid-max input').val($('.form-item-nid-min input').val());
                        }
                    });

                    // Set the tab index for the exposed form items
                    $ti = 0;
                    $('.views-exposed-form input, .views-exposed-form select, .views-exposed-form button').each(function() { $ti++; $(this).attr('tabindex', $ti);});
                }
            }
        }
    };


    Drupal.behaviors.shanti_images_mms_list = {
        attach: function (context, settings) {
            if (context == document) {
                $('.shanti-image-rem-mmsid').click(function(e) {
                    e.preventDefault();
                    var mmsid = $(this).data('mmsid');
                    var jsonurl = '/admin/shanti_images/list/removeid/' + mmsid;
                    $.getJSON(jsonurl, function(data) {
                        if (data.success) {
                            var el = $(e.currentTarget);
                            el.after('<span class="mms-removed">' + data.msg + '</span>');
                            el.remove();
                        } else {
                            console.log("Problem in API call to remove images", data);
                        }
                    });
                });
            }
        }
    };

  /**
   * Behavior to adjust image urls on DEV when the image is on prod
   * @type {{attach: Drupal.behaviors.shanti_images_dev_adjust.attach}}
   */
  Drupal.behaviors.shanti_images_dev_adjust = {
    attach: function (context, settings) {
      var hst = window.location.hostname;
      if (hst.indexOf('.dd') > -1 || hst.indexOf('-dev') > -1) {
        $('body').find('img[src*="iiif-test"]').each(function () {
          var src = $(this).attr('src');
          if (src.match(/shanti-image(-stage)?-\d+/)) {
            $(this).attr('src', src.replace('-test', ''));
          }
        });
      }
    }
  };

}(jQuery));