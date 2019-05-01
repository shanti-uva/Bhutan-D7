(function ($) {
  /** Overlay Mask extension: adds ability to call .overlayMask("show"|"hide") on any jQuery element **/
  $.fn.overlayMask = function (action) {
    var mask = this.find('.overlay-mask');

    // Create the required mask
    if (!mask.length) {
      mask = $('<div class="overlay-mask"><div class="loading-container"><div class="loading"></div><div id="loading-text">Searching&#133;</div></div></div>');
      mask.css({
        position: 'absolute',
        width: '100%',
        height: '100%',
        top: '0px',
        left: '0px',
        zIndex: 100,
        opacity: 9,
        backgroundColor: 'white'
      }).appendTo(this).fadeTo(0, 0.5).find('div').position({
        my: 'center center',
        at: 'center center',
        of: mask, //'.overlay-mask'
      });
    }

    // Act based on params

    if (!action || action === 'show') {
      mask.show();
    } else if (action === 'hide') {
      mask.hide();
  }
    return this;
  };

  // mixture of http://stackoverflow.com/questions/5802467/prevent-scrolling-of-parent-element
  // and https://gist.github.com/theftprevention/5959411#file-jquery-scrolllock-js
  $.fn.scrollLock = function () {
    return $(this).on("DOMMouseScroll mousewheel", function (ev) {
      var $this = $(this),
        scrollTop = this.scrollTop,
        scrollHeight = this.scrollHeight,
        height = $this.innerHeight(),
        delta = (ev.type == 'DOMMouseScroll' ?
          ev.originalEvent.detail * -40 :
          ev.originalEvent.wheelDelta),
        up = delta > 0;

      var prevent = function () {
        ev.stopPropagation();
        ev.preventDefault();
        ev.returnValue = false;
        return false;
      };

      if (!up && -delta > scrollHeight - height - scrollTop) {
        // Scrolling down, but this will take us past the bottom.
        $this.scrollTop(scrollHeight);
        return prevent();
      } else if (up && delta > scrollTop) {
        // Scrolling up, but this will take us past the top.
        $this.scrollTop(0);
        return prevent();
      }
    });
  };
  $.fn.scrollRelease = function () {
    return $(this).off("DOMMouseScroll mousewheel")
  };


  $.fn.openFlyout = function() {
    return this.each( function() {
      var fly = $(this);
      if (fly.hasClass('extruder')) {
        fly.openMbExtruder();
      } else if (fly.hasClass('faceted-search-results') || fly.attr('id') === 'faceted-search-results') {
        fly.addClass("on").removeClass("off");
      }
    });
  };

  $.fn.closeFlyout = function() {
    return this.each( function() {
      var fly = $(this);
      if (fly.hasClass('extruder')) {
        fly.closeMbExtruder();
      } else if (fly.hasClass('faceted-search-results') || fly.attr('id') === 'faceted-search-results') {
        fly.addClass("off").removeClass("on");
      }
    });
  };

  $.fn.toggleFlyout = function() {
    return this.each( function() {
      var fly = $(this);
      if (fly.hasClass('extruder')) {
        if (fly.hasClass('isOpened')) {
          fly.closeMbExtruder();
        } else {
          fly.openMbExtruder();
        }
      } else if (fly.hasClass('faceted-search-results')) {
        fly.toggleClass('on off');
      }
    });
  };


  // *** Common Functions for Shanti Sarvaka ***
  Drupal.ShantiSarvaka = {};

  //** Function to check width of Extruder and resize content accordingly */
  Drupal.ShantiSarvaka.checkWidth = function () {
    var panelWidth = $(".text").width();
    if (panelWidth > 325) {
      $(".extruder-content").css("width", "100%");
    } else if (panelWidth <= 325) {
      $(".extruder-content").css("width", "100% !important");
  }
  };


  // *** SEARCH *** adapt search panel height to viewport
  Drupal.ShantiSarvaka.searchTabHeight = function () {
    var height = $(window).height();
    var srchtab = (height) - 68;
    var srchtabAdmin = (height) - 103; // subtract 35px height of Drupal admin navbar
    var viewheight = (height) - 260;
//    var viewheightSources = (height) - 150;
//    var viewheightPlaces = (height) - 402;

    srchtab = parseInt(srchtab) + 'px';
    $("#search-flyout").find(".text").css('height', srchtab);

    srchtabAdmin = parseInt(srchtabAdmin) + 'px';
    $(".admin-menu #search-flyout").find(".text").css('height', srchtabAdmin);

    viewheight = parseInt(viewheight) + 'px';
    $(".view-wrap").css('height', viewheight);

    //    viewheightSources = parseInt(viewheightSources) + 'px';
    //    $(".sources .view-wrap").css('height', viewheightSources);

    //   viewheightPlaces = parseInt(viewheightPlaces) + 'px';
    //   $(".page-places .view-wrap").css('height', viewheightPlaces);

  };

  /* Convenience functions for open/closing flyouts */
  Drupal.ShantiSarvaka.openFlyout = function(flyout) {
    $(flyout).openFlyout();
    return flyout;
  };

  Drupal.ShantiSarvaka.closeFlyout = function(flyout) {
    $(flyout).closeFlyout();
    return flyout;
  };


  /**
   *  Settings for the theme
   */
  Drupal.behaviors.shantiSarvaka = {
    attach: function (context, settings) {
      if (context == document) {
        // Initialize settings.
        settings.shanti_sarvaka = $.extend({
            kmapsUrl: "http://subjects.kmaps.virginia.edu",
            mmsUrl: "http://mms.thlib.org",
            placesUrl: "http://places.kmaps.virginia.edu",
            ftListSelector: "ul.facetapi-mb-solr-facet-tree, ul.fancy-tree", // should change "mb-solr" to "fancy" for universality
            fancytrees: [],
            flyoutWidth: 360,
            topLinkOffset: 1500,
          topLinkDuration: 500,
        }, settings.shanti_sarvaka || {});

        if (typeof($.fn.popover) != "undefined") {
            $.fn.popover.Constructor.DEFAULTS.trigger = 'hover click';
            $.fn.popover.Constructor.DEFAULTS.placement = 'bottom auto';
            $.fn.popover.Constructor.DEFAULTS.html = true;
            $.fn.popover.Constructor.DEFAULTS.delay = {"show": 100, "hide": 80000}; // hiding with long timeout
            $.fn.popover.Constructor.DEFAULTS.template = '<div class="popover related-resources-popover" role="tooltip" data-container="body" data-toggle="popover" data-placement="bottom auto"><div class="arrow"></div><h5 class="popover-title"></h5><div class="popover-content"></div></div>';
            $.fn.popover.Constructor.DEFAULTS.container = 'body';
      }
    }
  }
  };

  /**
   * Back to Top Link functionality
   */
  Drupal.behaviors.shantiSarvakaToplink = {
    attach: function (context, settings) {
      if (context == document) {
        var offset = settings.shanti_sarvaka.topLinkOffset;
        var duration = settings.shanti_sarvaka.topLinkDuration;
        jQuery(window).scroll(function () {
          if (jQuery(this).scrollTop() > offset) {
            jQuery('.back-to-top').fadeIn(duration);
          } else {
            jQuery('.back-to-top').fadeOut(duration);
      }
        });
        jQuery('.back-to-top').click(function (event) {
          event.preventDefault();
          jQuery('html, body').animate({scrollTop: 0}, duration);
          return false;
        });
    }
  }
  };

  /**
   * ICheck init
   */
  Drupal.behaviors.shantiSarvakaIcheck = {
    attach: function (context, settings) {
      $("input[type='checkbox'], input[type='radio']", context).not($('.jstree input')).once('icheck').each(function () {
          var self = $(this),
          label = self.next('label');
          if (label.length == 1) {
          self = $(this).detach();
          label.prepend(self);
          }
        if (typeof(self.icheck) != "undefined") {
            self.icheck({
              checkboxClass: "icheckbox_minimal-red",
              radioClass: "iradio_minimal-red",
              insert: "<div class='icheck_line-icon'></div>",
            checkedClass: 'checked',
          });
            // In MB /my-content/collections/ Icheck is not show check when clicked fixing this here
            /*$('div.icheck-item').once('icheckfix').on('mousedown', function() {
           if($(this).hasClass('checked')) {
           $(this).addClass('rm-icheck');
           setTimeout(function() { $('.rm-icheck').removeClass('checked rm-icheck'); }, 500);
           } else {
           $(this).addClass('checked');
           }
           });*/
          }
      });
  }
  };

  /**
   * Select Picker
   */
  Drupal.behaviors.shantiSarvakaSelect = {
    attach: function (context, settings) {
      $(".selectpicker:not(#search-flyout .selectpicker)", context).selectpicker({
        dropupAuto: false,
        //liveSearch: true
      }); // initiates jq-bootstrap-select

  }
  };

  /**
   * Multi Level Push Menu
   */
  Drupal.behaviors.shantiSarvakaMlpMenu = {
    attach: function (context, settings) {
      if (context == document) {
        // Rearrange the button divs so that they are in the order blocks are added with a float-right css
        var buttons = $('div.navbar-buttons ul.navbar-right', context).detach();
        buttons.each(function () {
          $('div.navbar-buttons').prepend($(this));
        });
        // Initialize the multilevel main menu
        $('#menu').multilevelpushmenu({
          menuWidth: 270,
          menuHeight: '32em', // this height is determined by tallest menu
          mode: 'cover',
          direction: 'rtl',
          backItemIcon: 'fa fa-angle-left',
          groupIcon: 'fa fa-angle-right',
          collapsed: false,
          preventItemClick: false,
        });

        // --- align the text
        $('#menu ul>li, #menu h2').css('text-align', 'left');
        $('#menu ul>li.levelHolderClass.rtl').css('text-align', 'right');

        // --- close the menu on outside click except button
        $('.menu-toggle').click(function (event) {
          event.stopPropagation();
          $('#menu').slideToggle(200);
          $('.menu-toggle').toggleClass('show-topmenu');
          $('.main-wrapper').toggleClass('disabled-by-top-menu-open');
          $('#tree').toggleClass('disabled-by-top-menu-open');
          $('.collections').slideUp(200);
          $('.menu-exploretoggle').removeClass('show-topmenu');
        });

        $('.menu-exploretoggle').click(function (event) {
          event.stopPropagation();
          $('.collections').slideToggle(200);
        });

        $('.explore a').click( function(event){
             event.stopPropagation();
             $('.collections').slideToggle(200);
         });

        $('.collections .close').click( function(event){
            $('.collections').slideUp(200);
        });

        $(document).click(function () {
          $('.menu-toggle').removeClass('show-topmenu');
          $('.main-wrapper').removeClass('disabled-by-top-menu-open');
          $('#tree').removeClass('disabled-by-top-menu-open');
          $('#menu').hide(100);
        });


        if($('.menu-exploretoggle').hasClass('show-topmenu')) {
          $(this).addClass('active');
        } else {
          $(this).removeClass('active');
        };


        /* Initialize Language Buttons */

        // Language menu drop down init
        if (typeof($('#block-locale-language .dropdown-toggle').dropdown) == "function") {
            $('#block-locale-language .dropdown-toggle').dropdown();
        }

        // Language Chooser Functionality with ICheck
        $('body').on('ifChecked', 'input.optionlang', function () {
          var newLang = $(this).val().replace('lang:', '');
          var oldLang = Drupal.settings.pathPrefix;
          var currentPage = window.location.pathname;
          if (oldLang.length > 0) {
            // remove any current lang in url (format = "zh/")
            var currentPage = currentPage.replace(RegExp(oldLang + "?$"), ''); // Take care of home page (no slash at end of line)
            currentPage = currentPage.replace(oldLang, ''); // All other pages
          }
          // Create New URL with new Lang Prefix
          var newUrl = (Drupal.settings.basePath + newLang + currentPage).replace(/\/\//g, '/');
          window.location.pathname = newUrl;
        });
    }
  }
  };

  /**
   * Responsive Menus with MbExtruder
   */
  Drupal.behaviors.shantiSarvakaRespMenu = {
    attach: function (context, settings) {
      $(".menu-exploretoggle", context).click(function () {
        if ($("#menu-collections.extruder").hasClass("isOpened")) {
          $(".menu-exploretoggle").removeClass("show-topmenu");
        } else {
          $(".menu-collections").css('display', 'block');
          $(".menu-collections").addClass("active");
          $(".menu-collections > ul").addClass("in");
          $("#search-flyout").closeMbExtruder();
          $(".menu-exploretoggle").addClass("show-topmenu");
          return false;
    }
      });
  }
  };

  /**
   * Popovers Init
   */
  Drupal.behaviors.shantiSarvakaPopovers = {
    attach: function (context, settings) {

      $('.popover-link', context).each(function () {
        // adding .parent() because needed to wrap term and popover icon in span.kmap-tag-group
        // to prevent line break between term and popover icon
        var content = $(this).parent().next('div.popover').html();
        var title = $(this).parent().next('div.popover').attr('data-title');
        // to account for other/older instances where there is no kmap-tag-group
        if ($(this).parent().next('div.popover').length === 0 && $(this).next('div.popover').length > 0) {
          content = $(this).next('div.popover').html();
          title = $(this).next('div.popover').attr('data-title');
        }
        $(this).popover({'title': title, 'content': content});
      });
      $('div.popover', context).remove(); // remove hidden popover content once they have all been initialized
      // show.bs called immediately upon click. Hide all other popovers.
      $('.popover-link', context).on('show.bs.popover', function () {
        $('div.popover').hide();
      });
      // Once shown then
      $('.popover-link', context).on('shown.bs.popover', function () {
        // move the hidden span with kmid into the header when showing a popover
        var idspan = $('div.popover .popover-content span.kmid').detach();
        //console.log(idspan);
        $('div.popover h5').append(idspan);
        $('div.popover span.kmid').show();
      });
      // shown.bs is after popup is rendered. Move footer outside of content
      /*
       $('.popover-link').on('shown.bs.popover', function(){
       var pophtml = $(this).next('div.popover');
       var popfooter = pophtml.find('.popover-footer').detach();
       pophtml.find('.popover-content').after(popfooter);
       popfooter.show();
       });*/
      if (context == document) {
        // Hide popovers if anything but a popover is clicked
        $('body').click(function (e) {
          var target = $(e.target);
          if (target.parents('div.popover').length == 0 && !target.hasClass('popover')) {
            $('div.popover').hide();
      }
        });
    }
  }
  };

  /**
   * Miscellaneous Init
   */
  Drupal.behaviors.shantiSarvakaMiscinit = {
    attach: function (context, settings) {
      if (context == document) {

        // Shanti-filters title keyword search field: use description for placeholder text
        $('.shanti-filters .views-exposed-form .form-item input.form-text').each(function () {
          var desc = $(this).parent().parent().next('.description');
          $(this).attr({'placeholder': $.trim(desc.text()), 'size': '15'});
          desc.remove();
        });

        // conditional Internet Explorer message, see markup immediately after the body tag
        $(".ie-progressive").delay(2000).slideDown(400).delay(5000).slideUp(400);

        // Turn dev menu in admin footer into select
        if ($('#admin-footer #block-menu-devel ul.menu').length > 0) {
          var devmenu = $('#admin-footer #block-menu-devel ul.menu').clone();
          $('#admin-footer #block-menu-devel ul.menu').replaceWith('<select class="devmenu"></select>');
          var sel = $('#block-menu-devel select.devmenu');
          sel.append('<option>Choose an option...</option>');
          $.each(devmenu.children('li'), function () {
            var opt = $('<option>' + $(this).text() + '</option>').attr('value', $(this).find('a').attr('href'));
            sel.append(opt);
          });
          sel.change(function () {
            window.location.pathname = $(this).val();
          });
        }
        // Adjust height of blocks in admin footer
        $('#admin-footer div.block').each(function () {
          $(this).height($(this).parent().height());
        });

        // Collapse/Expand All Buttons For Bootstrap Collapsible Divs
        // Assumes Buttons are in a child div that is a sibling of the collapsible divs.
        $('div.expcoll-btns button').click(function () {
          var divs = $(this).parent().parent().find('div.collapse');
          if ($(this).hasClass('expand')) {
            $(divs).addClass('in');
          } else {
            $(divs).removeClass('in');
          }
        });

        // call Check Width
        Drupal.ShantiSarvaka.checkWidth();

        // Carousel Init and controls
        // Gets speed from setting associated with block so that admins can customize speed.
        $('.carousel').each(function () {
          var speed = $(this).data('speed') * 1000;
          $(this).carousel({
            interval: speed,
            pause: false
          });
        });


        $('.carousel .control-box-2 .carousel-pause').click(function () {
          var carousel = $(this).parents('.carousel');
          if ($(this).hasClass('paused')) {
            carousel.carousel('next');
            carousel.carousel('cycle');
          } else {
            carousel.carousel('pause');
      }
          $(this).toggleClass('paused');
          $(this).find('span').toggleClass('glyphicon-pause glyphicon-play');
        });

    }
  }
  };

  /**
   * Gallery: Initialize a gallery of images
   */
  Drupal.behaviors.shantiSarvakaGalleryInit = {
    attach: function (context, settings) {
      //console.log(context, settings);
      $('.shanti-gallery', context).imagesLoaded(function () {
        // Prepare layout options.
        var options = {
          align: 'left',
          itemWidth: 185, // Optional min width of a grid item
          autoResize: true, // This will auto-update the layout when the browser window is resized.
          container: $('.shanti-gallery'), // Optional, used for some extra CSS styling
          offset: 16, // Optional, the distance between grid items
          outerOffset: 0, // Optional the distance from grid to parent
          flexibleWidth: '35%', // Optional, the maximum width of a grid item
          ignoreInactiveItems: false,
        };
        // Get a reference to your grid items.
        var handler = $('.shanti-gallery');  // for wookmark 2.1.2 removed the ' > li ' as initialiazation now requires just the parent.

        var $window = $(window);
        $window.resize(function () {
          var windowWidth = $window.width(),
            newOptions = {flexibleWidth: '30%'};

          // Breakpoint
          if (windowWidth < 1024) {
            newOptions.flexibleWidth = '100%';
          }

          handler.wookmark(newOptions);
        });

        // Call the layout function.
        handler.wookmark(options);
      });
      /* set active class for displaying loading spinner */
      $('.shanti-thumbnail-link').click(function() {
        $(this).parents('.shanti-thumbnail').addClass('active');
      }); 
  }
  };

  /**
   * Accordion Init: only called on document load
   */
  Drupal.behaviors.shantiSarvakaAccordion = {
    attach: function (context, settings) {

      // Open first accordion if none opened
      //  $("#av-details .field-accordion").each(function(index, element){
      //	  $(element).addClass(index == 0 ? "in" : "").once();
      //	  $(element).has(".in").find(".glyphicon").toggleClass('glyphicon-plus glyphicon-minus');
      //	});
      $('.node-type-video .panel-group .collapsible:eq(0)').each(function (index, element) {
        $(element).find('.panel-collapse').once().addClass('in');
        $(element).has(".in").find('.accordion-toggle').once().removeClass('collapsed');
      });

      // Shiva site gets doubly glypicons. So need to be removed
      $(".glyphicon-plus + .glyphicon-plus, .glyphicon-minus + .glyphicon-minus").remove();

      // If it is an edit form, show any collapsed divs containing errors
      $('.page-node-edit .collapsible.collapsed input.error').parents('.collapsible').find('.collapse').not('.in').eq(0).collapse('show');
  }
  };

  /**
   * Other:
   */
  Drupal.behaviors.shantiSarvakaOtherInit = {
    attach: function (context, settings) {
      if (context == document) {
        $('.shanti-field-group-audience > div').find('a:eq(1)').addClass('icon-link');

        $('.shanti-field-title a').hover(function () {
            $(this).closest('.shanti-thumbnail').addClass('title-hover');
          },
          function () {
            $(this).closest('.shanti-thumbnail').removeClass('title-hover');
          }
        );

        // $('table.sticky-header').css('width','100%');

        // IE10 viewport hack for Surface/desktop Windows 8 bug http://getbootstrap.com/getting-started/#support-ie10-width
        (function () {
          'use strict';
          if (navigator.userAgent.match(/IEMobile\/10\.0/)) {
            var msViewportStyle = document.createElement('style');
            msViewportStyle.appendChild(
              document.createTextNode(
                '@-ms-viewport{width:auto!important}'
            )
            );
            document.querySelector('head').appendChild(msViewportStyle);
          }
        })();


        var myElement = document.getElementById('.carousel.slide');
        if (myElement) {
          // create a simple instance
          // by default, it only adds horizontal recognizers
          var mc = new Hammer(myElement);

          // let the pan gesture support all directions.
          // this will block the vertical scrolling on a touch-device while on the element
          mc.get('pan').set({direction: Hammer.DIRECTION_ALL});

          // listen to events...
          mc.on("panleft panright panup pandown tap press", function (ev) {
            myElement.textContent = ev.type + " gesture detected.";
          });
      }
    }
  }
  };

  /**
   * Format numbers with ssfmtnum class
   */
  Drupal.behaviors.shantiSarvakaFormatNumbers = {
    attach: function (context, settings) {
      $('.ssfmtnum', context).each(function () {
        if ($(this).text().indexOf(',') == -1) {
          var txt = $(this).text(),
            len = txt.length,
            i = len - 1,
            fmtnum = '';
          while (i >= 0) {
            fmtnum = txt.charAt(i) + fmtnum;
            if ((len - i) % 3 === 0 && i > 0) {
              fmtnum = "," + fmtnum;
            }
            --i;
          }
          $(this).text(fmtnum);
    }
      });
  }
  };

  /*
   Drupal.behaviors.kmapsExplorer = {
   attach: function (context, settings) {
   var $selected_li = $('#carousel-feature-slides > li');
   $selected_li.children('a').bind('click', function (e) {
   e.preventDefault();
   $selected_li.removeClass('active');
   $(this).parent().addClass('active');
   });

   $('#carousel-feature-slides.bx-large-slides').bxSlider({
   slideMargin:10,
   pager:true,
   controls:true,
   autoReload: true,
   moveSlides: 1,
   infiniteLoop: false,
   hideControlOnEnd: true,
   breaks: [{screen:0, slides:1, pager:false},{screen:380, slides:1},{screen:450, slides:2},{screen:768, slides:3},{screen:1200, slides:4}]
   });

   $('#carousel-feature-slides.bx-small-slides').bxSlider({
   slideMargin:10,
   pager:true,
   controls:true,
   autoReload: true,
   moveSlides: 1,
   infiniteLoop: false,
   hideControlOnEnd: true,
   breaks: [{screen:0, slides:1, pager:false},{screen:400, slides:2},{screen:550, slides:3},{screen:768, slides:4},{screen:1050, slides:5}]
   });

   }
   };
   */

  Drupal.behaviors.shantiSarvakaKalturaLoading = {
    attach: function (context, settings) {
      if (context == document) {
        // The player on the node edit form cannot be made responsive thru this script.
        // Because it causes the player not to appear until resize happens (ndg, 2015-01-30)
        /* No longer necessary see shanti-main-mediabase.js Drupal.behaviors.shantiAVVideoFix ()
         if (typeof kWidget != 'undefined' && !$('body').hasClass('page-node-edit')) {
         kWidget.addReadyCallback(function(playerId) {
         function calcPlayerSize() {
         var elm = document.getElementById(playerId);
         $(elm).css({width: "auto", height: (elm.clientWidth/16.0)*9+"px"});
         }
         window.addEventListener("resize", calcPlayerSize, false);
         calcPlayerSize();
         });
         }*/
      }
    }
  };


  Drupal.behaviors.shantiSarvakaMbTranscriptLanguageDropdownIcon = {
    attach: function (context, settings) {
      if (context == window.document) {
        $('.transcript-options button.selectpicker span:first-child').replaceWith('<span class="icon shanticon-comments-o"></span>');
        //$('.transcript-options .filter-option').replaceWith('<span class="fa fa-comments-o"></span>');
      }
    }
  };


  // Drupal.behaviors.shantiSarvakaMbTrimDesc moved to shanti-main-mediabase.js

  // Applies wookmark js to related videos tab div by calling Drupal behaviors
  Drupal.behaviors.shantiSarvakaMbRelatedTab = {
    attach: function (context, settings) {
      if (context == window.document) {
        $('a#related-tab').on('shown.bs.tab', function (e) {
          Drupal.attachBehaviors('#related');
        });
    }
  }
  };

  Drupal.behaviors.sidebarOffCanvasToggle = {
    attach: function (context, settings) {
      if (context == document) {

        // Initiate & hide sidebar when active/visible
        $('[data-toggle=offcanvas]').click(function () {
          $('.row-offcanvas').toggleClass('active');
        });

        /* hiding the feature box data icon - w/no data */
        $('.texts .views-row > .views-field > span.field-content:empty').parent('.views-field').addClass('empty');

        // Toggle sidebar
        // $('button.view-offcanvas-sidebar').click( function() {
        //  $(this).toggleClass( 'show', 200 );
        // });

        // Hide sidebar button for homepage
        // if($("body.front").length ) {
        // 	$("button.view-offcanvas-sidebar").remove();
        // }

      }
    }
  };


  // --- unhiding breadcrumbs: inline styles keeps the breadcrumbs markup from flash on load when at homepages where we do not want them
  Drupal.behaviors.breadcrumbsFlickrControl = {
    attach: function (context, settings) {
      $('.breadwrap:not(".front.page-subjects .breadwrap")').show("fast");
  }
  };

  /*
   Drupal.behaviors.advancedToggleClassHeightChange = {
   attach: function (context, settings) {
   --- sets class for height change in flyout, see comboheight below in ShantiSarvaka.searchTabHeight
   $('.advanced-link').on('click', function () {
   $('.view-wrap').toggleClass('short-wrap');
   $('.advanced-view').toggleClass('show-options');
   $('.advanced-view').slideToggle('fast');
   });
   }
   };
   */

  Drupal.behaviors.googleMapsButtonActiveArrow = {
    attach: function (context, settings) {
      if (context == window.document) {
        $('.btn-group-gmaps.btn-group > .btn.btn-default.active').one().prepend('<span class="icon"></span>');
        $('.btn-group-gmaps.btn-group > .btn.btn-default').click(function () {
          $(this).prepend('<span class="icon"></span>');
        });
    }
  }
  };


  Drupal.behaviors.hasTabs = {
    attach: function (context, settings) {
      // --- sets class for height change in flyout, see comboheight below in ShantiSarvaka.searchTabHeight
      if ($(".tabs.secondary").length) {
        $(".titlearea").addClass('has-tabs-secondary');
      }

      if ($(".tabs.primary").length) {
        $("body").addClass('has-tabs');
    }
  }
  };


  // handles ordinary search flyout inputs (not typeahead inputs)
  Drupal.behaviors.shantiSarvakaSearchFlyoutCancel = {
    attach: function (context, settings) {
      if (context == window.document) {
        $('.search-group .input-group').once().each(function () { // ----- testing broader target on oct. 20, 2016
            // $('.extruder').once().each(function() {
          var $xbtn = $("button.searchreset", this);
          var $srch = $(".form-control", this);  // the main search input
          $srch.data("holder", $srch.attr("placeholder"));

            // --- focusin - focusout
          $srch.focusin(function () {
            $srch.attr("placeholder", "");
            $xbtn.show("fast");
          });
          $srch.focusout(function () {
            $srch.attr("placeholder", $srch.data("holder"));
            $xbtn.hide();

            var str = $srch.data("holder"); //"Enter Search...";
            var txt = $srch.val();

            if (str.indexOf(txt) > -1) {
	      $xbtn.hide();
	      return true;
            } else {
	      $xbtn.show(100);
	      return false;
            }
          });
        });
      }
    }
  };

  // Trim Description text for projects in carousel and add ellipsis
  Drupal.behaviors.shantiSarvakaCarousel = {
    attach: function (context, settings) {
      if (context == window.document) {
        // Trim description text to 460 characters.
        $('.carousel-description').each(function () {
          var txt = $(this).text();
          if (txt.length > 500) {
            txt = txt.substr(0, 500);
            txt = txt.substr(0, txt.lastIndexOf(' ')) + "...";
            $(this).text(txt);
          }
        });
        // Activate carousels that are data-status=on see template.php shanti_sarvaka_carousel() function
        $('div.carousel').each(function() {
            if ($(this).data('status') == 'on') {
                $(this).carousel('cycle');
          } else {
                $(this).carousel('pause');
          }
          // Adjust the View Resource link to go to current slide resource
            var href = $(this).find('.carousel-inner .item.active .carousel-slide-path').eq(0).attr('href');
            $('#carousel-slide-link').attr('href', href);
            $(this).on('slid.bs.carousel', function () {
                var href = $(this).find('.carousel-inner .item.active .carousel-slide-path').eq(0).attr('href');
                $('#carousel-slide-link').attr('href', href);
            });
        });
        // Activate pause/play buttons for carousel
        $('#pause-play-btn').click(function () {
          $('#homeCarousel').carousel('cycle');
          var carousel = $(this).parents(".carousel").eq(0);
          var status = carousel.data('status');
          var span = $(this).children("span.glyphicon").eq(0);
          if (status == "off") {
            carousel.carousel('next');
            carousel.carousel('cycle');
            carousel.data('status', 'on');
            span.removeClass("glyphicon-play").addClass("glyphicon-pause");
          } else {
            carousel.carousel('pause');
            carousel.data('status', 'off');
            span.removeClass("glyphicon-pause").addClass("glyphicon-play");
      }
        });
    }
  }
  };

  Drupal.behaviors.shantiDeleteButtonDisable = {
    attach: function (context, settings) {
      if (context == document) {
        // Prevent the backspace key from navigating back.
        $(document).bind('keydown', function (event) {
          var doPrevent = false;
          if (event.keyCode === 8) {
            var d = event.srcElement || event.target;
            if ((d.tagName.toUpperCase() === 'INPUT' &&
                (
                d.type.toUpperCase() === 'TEXT' ||
                d.type.toUpperCase() === 'PASSWORD' ||
                d.type.toUpperCase() === 'FILE' ||
                d.type.toUpperCase() === 'SEARCH' ||
                d.type.toUpperCase() === 'EMAIL' ||
                d.type.toUpperCase() === 'NUMBER' ||
                d.type.toUpperCase() === 'DATE' )
              ) ||
              d.tagName.toUpperCase() === 'TEXTAREA') {
              doPrevent = d.readOnly || d.disabled;
            }
            else {
              doPrevent = true;
            }
          }

          if (doPrevent) {
            event.preventDefault();
            //console.log("Delete Button Navigation has been disabled.");
          }
        });
    }
  }
  };

//	Drupal.behaviors.kmapsOpenlayersMenuFlickrControl = {
//	  attach: function (context, settings) {
//			if($(".openlayermap").length ) {
//				$(".openlayermap #sidebar_wrapper").css('display','block !important');
//			}
//	  }
//	};

//	Drupal.behaviors.kmapsPageNotFound = {
//	  attach: function (context, settings) {
//			if($('.page-title-text:contains("Page not found")').length ) {
//				$('button.view-resources').css('display','none');
//			}
//	  }
//	};


// Sidebar and footer coordinate heights
  Drupal.behaviors.shantiSidebarFooterGravity = {
    attach: function (context, settings) {

      Drupal.ShantiSarvaka.sidebarFooterGravity = function () {

        var height = $(window).height();
        var mainwrapper_minimum = (height) - 150;
        var mainwrapper_minimum_hastabs = (height) - 190;
        var mainwrapper_minimum_hasadminmenu = (height) - 180;
        var mainwrapper_minimum_hasadminfooter = (height) - 212;
        mainwrapper_minimum = parseInt(mainwrapper_minimum) + 'px';
        mainwrapper_minimum_hastabs = parseInt(mainwrapper_minimum_hastabs) + 'px';
        mainwrapper_minimum_hasadminmenu = parseInt(mainwrapper_minimum_hasadminmenu) + 'px';
        mainwrapper_minimum_hasadminfooter = parseInt(mainwrapper_minimum_hasadminfooter) + 'px';
        $("body:not(.bhutan) .main-col").css('min-height', mainwrapper_minimum);
        $("body.has-tabs:not(.bhutan) .main-col").css('min-height', mainwrapper_minimum_hastabs);
        $("body.admin-menu:not(.bhutan) .main-col").css('min-height', mainwrapper_minimum_hasadminmenu);
        $("body.admin-menu.has-tabs:not(.bhutan) .main-col").css('min-height', mainwrapper_minimum_hasadminfooter);

        var sidebarsecond = $(".main-col").height() + 50;  // for sidebar height (only AV has this sidebar) - adds 20px to sidebar-second in AV height for top-margin/padding
        sidebarsecond = parseInt(sidebarsecond) + 'px';
        $(".region-sidebar-second").css('height', sidebarsecond);

        var sidebarsecondeditcollection = $(".page-node-edit.node-type-collection .main-col").height() + 550;
        sidebarsecondeditcollection = parseInt(sidebarsecondeditcollection) + 'px';
        $(".page-node-edit.node-type-collection .region-sidebar-second").css('height', sidebarsecondeditcollection);
      };

      $(window).bind('load resize orientationchange', function () {
        clearTimeout(this.id);
        this.id = setTimeout(Drupal.ShantiSarvaka.sidebarFooterGravity, 300);
      });
  }
  };

// Function to replace broken images
Drupal.behaviors.shantiSarvakaBrokenImages = {
    attach: function (context, settings) {
      if (context == document) {
          // Deal with Broken images if theme setting is on
          if (Drupal.settings.shanti_sarvaka && Drupal.settings.shanti_sarvaka.replace_broken_images) {
              var url = Drupal.settings.shanti_sarvaka.broken_image_icon_url;
              if (Drupal.settings.broken_image_url_override) {
                  if (Drupal.settings.broken_image_url_override.length > 0) {
                    url = Drupal.settings.broken_image_url_override;
                  }
              }

              var collimgurl = '/sites/all/themes/shanti_sarvaka/images/default/collections-generic.png';
              var audioimgurl = '/sites/all/themes/shanti_sarvaka/images/default/generic-audio-thumb.jpg';
              var videoimgurl = '/sites/all/themes/shanti_sarvaka/images/default/generic-video-thumb.jpg';

              // For image tags not yet added to DOM or added later by AJAX, add an event listener
              $('img').on('error', function () {
                  var repurl = url;
                  if ($(this).parents('.shanti-thumbnail.collection').length > 0) {
                    repurl = collimgurl;
                    if ($(this).parents('.shanti-thumbnail.collection').length > 0) {
                        repurl = collimgurl;
                    } else if ($(this).parents('.shanti-thumbnail.audio').length > 0) {
                        repurl = audioimgurl;
                    } else if ($(this).parents('.shanti-thumbnail.video').length > 0) {
                        repurl = videoimgurl;
                    }
                  }
                  var oldsrc = $(this).attr('src');
                  $(this).attr('data-origimg', oldsrc);
                  $(this).attr('src', repurl);
              });
            }
        }
      }
    };

}(jQuery));
