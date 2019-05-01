(function($){

Drupal.behaviors.shantiTexts = {
    attach: function (context, settings) {

        $('.shanti-texts-section-title').on('inview', function(event, isInView) {
            nid = $(this).parent().attr('id');
            toc_id = nid.replace('shanti-texts','shanti-texts-toc');
            if (isInView) {
                $('.solo').removeClass('toc-selected solo');
                $('#'+toc_id).addClass('toc-selected');
                $("#shanti-texts-sidebar .tab-content").scrollTo('#'+toc_id,10,{easing:'swing',margin:true,offset:-130}); /* speed was 500, testing now 10 */
            } else {
                if ($('.toc-selected').length == 1) {
                    $('#'+toc_id).addClass('solo');
                } else {
                    $('#' + toc_id).removeClass('toc-selected');
                }
            }
            $(window).trigger('checkInView');
        });

        var kwic_n = Drupal.settings.shantiTexts.kwic_n;
        if (kwic_n) {
            // If there is a kwic number ...
            location.href = '#' + 'shanti-texts-search-hit-' + kwic_n;
        } else {
            // This handles scrolling to anchors which doesn't otherwise work
            location.href = '#' + window.location.hash.substr(1);
        }

        $('#shanti-texts-sidebar-tabs li.first a').tab('show'); // Bootstrap

        // No longer being used ...
        /*
        $('.toc-item-node', context).localScroll({
            target:'#shanti-texts-body',
            duration: 10,
        });
        */
    },

    detach: function (context, settings) {

    },

};

Drupal.behaviors.shantiTextsReaderSidebar = {
    attach: function (context, settings) {

        /* overflow scrolling for sidebar - the setting */
        $( "#shanti-texts-sidebar-tabs li" ).on('shown.bs.tab', function (e) { 
            var element = document.querySelector('#shanti-texts-sidebar .tab-content');
            if( (element.offsetHeight < element.scrollHeight) || (element.offsetWidth < element.scrollWidth)){
               // element w/ overflow
              element.style.overflow = "scroll";
            }
            else{
              element.style.overflow = "visible";
            }
        });   

        /* Editing buttons in sidebar TOC */
        $('.node-type-book .shanti-texts-section-controls > a').hover(function () { 
            $(this).closest('li').addClass('active'); 
        },
          function () {
            $(this).closest('li').removeClass('active');
          }
        );

        /* removing banners and footer */
        $( ".fullview" ).on( "click", function( event ) {
            $('.main-content>.row:first-of-type,.footer,.site-banner,.flap').toggle();
            $('.main-col').once().height( $(".main-col").height() + 140 );
            $('.admin-menu .main-col').once().height( $(".admin-menu .main-col").height() + 140 );
            $(this).toggleClass('expanded-view');

//            if ($(this).text() == "[exit] Full-Screen")
//                $(this).text("[enter] Full-Screen")
//                 else
//                $(this).text("[exit] Full-Screen");

        });    

        /* same functions - targets are different - keeping the colored banner 
        $( ".banner-view a" ).on( "click", function( event ) {
            $('.footer,.site-banner,.flap').toggle();
            $('.main-col').once().height( $(".main-col").height() - 80 );
            $('body.admin-menu .main-col').once().height( $("body.admin-menu .main-col").height() - 80 );

            if ($(this).text() == "[hide] Text w/Banner")
                $(this).text("[show] Text w/Banner")
                 else
                $(this).text("[hide] Text w/Banner");
        }); 
         */

    }
};



})(jQuery);
