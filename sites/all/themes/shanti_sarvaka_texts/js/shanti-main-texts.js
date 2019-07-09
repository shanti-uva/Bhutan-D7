(function ($) {

	// targets click-hover on whole teaser box not just title text anchor
	/* Drupal.behaviors.shantiTextsTeaserTargetAll = {
		attach: function (context, settings) {
		  if(context == window.document) {

		    $('.view-all-texts .views-row').on('click', function(){
		      window.location=$(this).find('a').attr('href');
		      return false;
		    });

		    $('.view-all-texts .views-row').hover(function() {
		    	$(this).toggleClass('views-row-hover');
		    });	

		    $('.view-all-texts .views-row').on('click', function(){
		      $(this).addClass('views-row-active');
		    });

		  }
		} 
	};
	*/
	
	Drupal.behaviors.shantiAutocompleteSearchAutosubmit = {
        attach: function (context, settings) {
          if(context == window.document) {
            $(document).on('click', '#autocomplete', function(){
                setTimeout(function() {
                    $('#edit-submit-text-search').click();
                }, 100);
            });

          }
        } 
    };

  /**
   * Add summaries to the tabs in the book edit/add form
   *
   * @type {{attach: Drupal.behaviors.shantiTextsSplitterSummary.attach}}
   */
  Drupal.behaviors.shantiTextsBookEditSummaries = {
    attach: function (context) {
        if ($('fieldset#edit-group_text_splitter').length > 0) {
            $('fieldset#edit-group_text_splitter', context).drupalSetSummary(function (context) {
                return Drupal.t('Split text by headers into pages');
            });
            $('fieldset#edit-group_kmap_terms', context).drupalSetSummary(function (context) {
                return Drupal.t('Langs, Subjects, Places, Terms');
            });
            $('fieldset#edit-group_book_metadata', context).drupalSetSummary(function (context) {
                return Drupal.t('Metadata about the text');
            });
            $('fieldset#edit-group_collection', context).drupalSetSummary(function (context) {
                return Drupal.t('Where to put Text and privacy');
            });
            $('#edit-field-dc-lang-code').hide(); // hide old language field
        }
    }
  };

  Drupal.behaviors.shantiTextsTextSplitter = {
    attach: function (context) {
      if (context === document) {
        var bval = $('#edit-book-bid').val();
        //console.log("Bval is: " + bval);
        if ($('body').hasClass('page-node-edit node-type-book') || bval > 0) {
          $('.text-splitter-group input').icheck("disabled");
          if ($('#tsp-diabled').length == 0) {
            var url = '/' + $('#parent-page-alias').val();
            $('.text-splitter-group').prepend('<div id="tsp-diabled">The text splitter can only be used on new “books”. ' +
                'Use the (+) icons in the <a href="' + url + '">books’s Table of Contents</a> to add pages to existing books. ' +
                '<br/>Or use the <a href="/node/' + bval + '/reorder">Sort Text Sections Tab</a> to reorder, promote, or demote sections.' +
                '<br/>If you clicked the (+) icon to get this form, the text you enter under the content tab will be added as the last child of the section you clicked.');
          }
          $('fieldset#edit-group_text_splitter', context).drupalSetSummary(function (context) {
            return Drupal.t('Disabled');
          });
        }
      }
    }
  };

    Drupal.behaviors.shantiTextsUserProfile = {
        attach: function (context) {
            if (context === document) {
                if ($('body').hasClass('page-user')) {
                    $('.profile .field-label').each(function() {
                        $(this).text($(this).text().replace(':', ''));
                    });
                }
            }
        }
    };

 }(jQuery));