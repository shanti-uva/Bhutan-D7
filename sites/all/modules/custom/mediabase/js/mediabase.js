(function ($) {
	Drupal.behaviors.mediabaseImages={
		attach: function(context) {

		   fixAudioImages();
		   replaceBrokenImages(); 
		   
			function fixAudioImages() {
				$('.shanti-thumbnail.audio img').each(function() { 
					$this = jQuery(this); 
					var src = $this.attr('src'); 
					if (src.indexOf('/width/') > -1) { 
						var pts = src.split("/width/"); 
						$this.attr('src', pts[0]+"/version/0"); 
					} 
				});
			}
		   
		   // On image error in thumbnail div, use the default blank thumbnail image
		   function replaceBrokenImages() {
		      jQuery('.kaltura-thumb img, .shanti-thumbnail.video .shanti-thumbnail-image img').error(function() {
        		       var mysrc = jQuery(this).attr('src');
        		       var url = window.location.protocol + "//" + window.location.host;
        		       url += Drupal.settings.basePath + Drupal.settings.mediabase.path;
        		       url += '/images/generic-video-thumb.jpg';
        		       if(url != mysrc) { 
        		          jQuery(this).attr('src', url);
        		       }
		     });
		     jQuery('.shanti-thumbnail.audio .shanti-thumbnail-image img').error(function() {               var mysrc = jQuery(this).attr('src');
                var url = window.location.protocol + "//" + window.location.host;
                url += Drupal.settings.basePath + Drupal.settings.mediabase.path;
                url += '/images/generic-audio-thumb.jpg';
                if(url != mysrc) { 
                    jQuery(this).attr('src', url);
                }
              });
		   }
		}
	};
	
	Drupal.behaviors.mediabaseSearch={
        attach: function(context){
           
            // Code to add transcript and description radiobuttons to search form
           var transcriptSearch = jQuery('#block-transcripts-transcript-search');
           var siteSearch = jQuery('#block-search-form');
           siteSearch.addClass('active');
           addToggleToSearchForm( transcriptSearch);
           addToggleToSearchForm( siteSearch);
           
           function addToggleToSearchForm( searchForm ) {
            return; // This should be done in Drupal with the Form API and possibly a submit function. Disabling for now.
              var toggleBlock = jQuery('<p class="search-toggle-box"/>');
              searchForm.find('form').append(toggleBlock);
              
              // site search button
              var radioId = 'site-radio-' + searchForm.attr('id');
              toggleBlock.append( jQuery('<input/>').attr({
                    type: 'radio',
                    name: 'search-type',
                    value: 'site',
                    checked: true,
                    id: radioId,
              }).change( function (event) {
                 toggleSearchForm(this);
              }
              ));
              toggleBlock.append( jQuery('<label/>').text(Drupal.t('Site Search')).attr('for', radioId ));
              toggleBlock.append( jQuery('<br/>'));
              
              // transcript search button
              radioId = 'transcript-radio-' + searchForm.attr('id');
              toggleBlock.append( jQuery('<input/>').attr({
                    type: 'radio',
                    name: 'search-type',
                    value: 'transcript',
                    id: radioId,
              }).change( function (event) {
                 toggleSearchForm(this);
              }
              ));
              toggleBlock.append( jQuery('<label/>').text(Drupal.t('Transcript Search')).attr('for', radioId ));
              
              // add the close link
              toggleBlock.prepend( jQuery('<a title="close"><img/></a>').attr({
                    href: '#',
                    class: 'close-toggle-box',
              }).css({
                    float: 'right',
                    width: '20px',
              }).click(function(event) {
                 toggleBlock.removeClass('visible');
                 event.preventDefault();
              }));
              
              // add the close button
              var closeButtonPath = Drupal.settings.basePath +  Drupal.settings.mediabase.path + '/images/close.png';
              jQuery('.close-toggle-box img').attr( {
                    src: closeButtonPath,
              }).css('width', '20px');
              
              searchForm.find('input[type=text]').hover( function(event) {
                    toggleBlock.addClass('visible');
              });
           }
           
           function toggleSearchForm(input) {
              var transcriptSearch = jQuery('#block-transcripts-transcript-search');
              var siteSearch = jQuery('#block-search-form');
              var termValue = jQuery(input).parents('form').find('input[type=text]').val();
              if (input.value == 'transcript' ) {
                 transcriptSearch.addClass('active');
                 transcriptSearch.find('input[value=transcript]').attr('checked',true);
                 transcriptSearch.find('input[type=text]').val( termValue );
                 transcriptSearch.find('.search-toggle-box').addClass('visible');
                 siteSearch.removeClass('active');
                 siteSearch.find('input[value=site]').attr('checked',true);
                 siteSearch.find('.search-toggle-box').removeClass('visible');
              } else {
                 siteSearch.addClass('active');
                 siteSearch.find('input[value=site]').attr('checked',true);
                 siteSearch.find('input[type=text]').val( termValue );
                 siteSearch.find('.search-toggle-box').addClass('visible');
                 transcriptSearch.removeClass('active');
                 transcriptSearch.find('input[value=transcript]').attr('checked',true);
                 transcriptSearch.find('.search-toggle-box').removeClass('visible');
              }
           }
           
           
        }
    };
    
    Drupal.behaviors.mediabaseViews={
        attach: function(context){
             
           fixVBOCheckBoxes();
           if ($('body').hasClass('page-mycontent-workflow')) { 
               // Commenting this out in hotfix 7.x-1.0-beta3.1 as it hides all filters.
               //cleanupWorkflowSelects(context);  
           }
           
           function fixVBOCheckBoxes() {
                // vbo click anywhere in the row to enable messes up the ICheck function so disabling on view-my-content forms
                $('.view-my-content .views-table tbody tr').unbind('click');
               }
           
           // Arrange the 19 selects on the workflow page into organized divs for formatting
            function cleanupWorkflowSelects() {
                // Remove all the select widgets into groups
                var grp3 = $('#views-exposed-form-my-workflow-workflow-all .views-exposed-widget').detach();
                var genfilters = grp3.splice(-3, 3);
                var grp1 = grp3.splice(0,9);
                var grp2 = grp3.splice(0,5);
                if ($('#grp1').length > 0) {
                    $('#grp1').find(".panel-body").eq(0).append(grp1);
                    $('#grp2').find(".panel-body").eq(0).append(grp2);
                    $('#grp3').find(".panel-body").eq(0).append(grp3);
                    $('#grp3').parent().after(genfilters);
                    return;
                }
                // Set up Accordion code
                var formrow = $('#views-exposed-form-my-workflow-workflow-all .views-exposed-widgets.clear-block.row');
                var accordionGrp = $('<div class="panel-group" id="workflow-accordion" role="tablist" aria-multiselectable="true"></div>');
                formrow.append(accordionGrp);
                // Add bootstrap accordion to each row with their group of selects
                // Row 1: Media Workflow
              var row1 = $( '<div class="panel panel-default">' +
                        '<div class="panel-heading" role="tab" id="headingOne">' +
                          '<h6>' +
                            '<a class="accordion-toggle" data-toggle="collapse" data-parent="#workflow-accordion" href="#grp1" aria-expanded="true" aria-controls="grp1">' +
                              '<span class="glyphicon glyphicon-minus"></span>Media Workfow' +
                            '</a>' +
                          '</h6>' +
                        '</div>' +
                        '<div id="grp1" class="panel-collapse collapse in" role="tabpanel" aria-labelledby="headingOne">' +
                          '<div class="panel-body"></div></div></div>');
                          
                row1.find(".panel-body").eq(0).append(grp1);
                accordionGrp.append(row1);
                // Row 2: Catalog Record Workflow
                var row2 = $('<div class="panel panel-default">' +
                        '<div class="panel-heading" role="tab" id="headingTwo">' +
                          '<h6>' +
                            '<a class="accordion-toggle collapsed" data-toggle="collapse" data-parent="#workflow-accordion" href="#grp2" aria-expanded="false" aria-controls="grp2">' +
                              '<span class="glyphicon glyphicon-plus"></span>Catalog Record Workfow' +
                            '</a>' +
                          '</h6>' +
                        '</div>' +
                        '<div id="grp2" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingTwo">' +
                          '<div class="panel-body"></div></div></div>');
                row2.find(".panel-body").eq(0).append(grp2);
                accordionGrp.append(row2);
                // Row 3: Transcript Workflow
                var row3 = $('<div class="panel panel-default">' +
                        '<div class="panel-heading" role="tab" id="headingThree">' +
                          '<h6>' +
                            '<a class="accordion-toggle collapsed" data-toggle="collapse" data-parent="#workflow-accordion" href="#grp3" aria-expanded="false" aria-controls="grp3">' +
                              '<span class="glyphicon glyphicon-plus"></span>Transcript Workfow' +
                            '</a>' +
                          '</h6>' +
                        '</div>' +
                        '<div id="grp3" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingThree">' +
                          '<div class="panel-body"></div></div></div>');
                row3.find(".panel-body").eq(0).append(grp3);
                accordionGrp.append(row3);
                accordionGrp.after(genfilters);
            }
        }
    };
    
     Drupal.behaviors.mediabaseForms={
        attach: function(context){

            var spinner = '<span class="glyphicon glyphicon-refresh glyphicon-refresh-animate"></span>';

            // Hide Add Media Button after audio or video is added for MANU-4900
            var thumbimg = $('.page-node-add-audio .field-name-field-audio .kaltura_field_thumb img,' +
                '.page-node-add-video .field-name-field-video .kaltura_field_thumb img');
            var thumbsrc = thumbimg.attr('src');
            if (thumbsrc) {
                $('.page-node-add-audio .field-name-field-audio #edit-field-audio-und-0-button,' +
                    '.page-node-add-audio .field-name-field-audio .media-field-description.audio, ' +
                    '.page-node-add-video .field-name-field-video #edit-field-video-und-0-button,' +
                    ' .page-node-add-video .field-name-field-video .media-field-description.video').hide();
            }

            // Disable submit forms once something is submitted
           $('#video-node-form, #audio-node-form').submit(function()  { $('#edit-submit').prop('disabled',true);});
           
           $('.field-name-field-pbcore-description .field-name-field-description-type .selectpicker').change(function() {
               var dtype = $(this).val(); 
               var par = $(this).parent('div').parent('div');
               par.find(".lenlim").remove();
               if (dtype == 'Caption') {
                           par.append('<p class="lenlim small">A caption can be a maximum of 140 characters long.</p>');
                 } else if (dtype == 'Summary') {
                           par.append('<p class="lenlim small">A summary can be a maximum of 750 characters long.</p>');
                 }
            });

            // Add confirmation to field collection delete buttons
            // Trick here is that the button use ajax to perform the action.
            // Using bootbox plugin to provide a dialog box and button classes to register confirmation
            if ($('body').hasClass('page-node-edit')) {
                $('.btn-delete.ajax-processed').each(function () {
                    var btnid = $(this).attr('id');  // Get the button id
                    var inputval = $(this).prevAll('.field-type-text').find('input').val();
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

            // Context Not Document
            if (context !== document) {
                // When uploader is used to add media, change body class to av-has-media
                if ($("body.page-node").hasClass('av-no-media')) {
                    if (typeof(context[0]) == 'object' && 'id' in context[0] && context[0]['id'] =="kaltura-uploader-form") {
                        $("body.page-node").removeClass('av-no-media');
                        $("body.page-node").addClass('av-has-media');
                    }
                }

                // Change submit button message when clicked
                $('a[id^=submitBtn]').on('click', function () {
                    $(this).append(spinner);
                });

            }

            // context document
            if (context === document) {
                $('#edit-actions .form-submit').on('mousedown', function () {
                    if ($(this).data('spinner') !== 'true') {
                        $(this).append(spinner);
                        $(this).data('spinner', 'true');
                    }
                });
            }

            // All contexts
            // Add spinner to add more submit in edit form
            $('.mb-av-form button.field-add-more-submit').on('mousedown', function(e) {
                var span = $(this).children('span').eq(0);
                if (span.data('spinner') !== 'true') {
                    span.append(spinner);
                    span.data('spinner', 'true');
                }
            });


        }
     };
     
     Drupal.behaviors.workflowFormFix={
        attach: function(context) {
            /**
             * This snippet is a bug workaround. on the /mycontent/workflow/ page when the reset button is pressed
             * It goes to a URL like .../mycontent/workflow/3665%2C4703%2C4881%2C4965%2C4835%2C3%2C5361%2C5561%2C5867%2C6221
             * This breaks the Media Present and Transcript Present select alters in the feature
             * So the solution is when there is this kind of URL to reload the page with the clean url which loads the 
             * correct code for those drop down selects. This doesn't seem to happen on the /workflow/all page
             */
            var path = window.location.pathname;
            if (path.match(/mycontent\/workflow\/[\s\S]+/)) { 
                window.location.pathname = "/mycontent/workflow/";
            }
            
            // In Workflow pages replace transcript file names with abbreviate name since names are often too long
            if (path.match(/mycontent\/workflow/) || path.match(/workflow\/all/)) {
                $('.views-field.views-field-field-transcript a').each(function() {
                    var mytxt = $(this).text().replace('.Xml', '').replace('.xml', '');
                    if (mytxt.length > 15) {
                        mytxt = mytxt.substring(0,15) + "....";
                        $(this).text(mytxt);
                    }
                    $(this).attr('target', '_blank');
                });
            }
         }
     };

} (jQuery));