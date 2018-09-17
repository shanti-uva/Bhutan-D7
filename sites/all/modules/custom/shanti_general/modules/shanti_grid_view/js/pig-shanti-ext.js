/**
 * This Javascript file extends the Pig (Progressive Image Grid) JS Class written by Dan Schlosser
 * See https://medium.com/@danrschlosser/building-the-image-grid-from-google-photos-6a09e193c74a and
 *        https://github.com/schlosser/pig.js
 *
 * This file needs to be loaded after pig.js
 * Unlike the original library, this extension IS depends on jQuery
 *
 * In order for this extension to work properly. The ProgressiveImage class needs to be made global as well.
 * This is done by copying the code for PIG at the bottom of the library and adapting it
 * to ProgressiveImage so that it can be extended as well. The code is:
 *
  // Export ProgressiveImage into the global scope. Added by ndg8f (if it gets used...)
  if (typeof define === 'function' && define.amd) {
    define(ProgressiveImage);
  } else if (typeof module !== 'undefined' && module.exports) {
    module.exports = ProgressiveImage;
  } else {
    global.ProgressiveImage = ProgressiveImage;
  }
 */

(function($) {
   
    // Extending Pig Object
    Pig.prototype._getOnScroll = function() {  return function() {}; }; // disable infinite scrolling but call initPopdown()
    /**
     *  Settings for the Popdown (ppd) are in the ppdSettings object. They are:
     *    height:       the height of the popodown when it opens = this.ppdSettings.height
     *    imageSize: the size of the image in the popdown as "width,height"
     *    template:   the string to be converted into the HTML template = this.ppdSettings.template
     *    imgSelector: the selector that identifies the img tag in the popdown
     *    infoSelector: the selector identifying the div where the information is to be loaded
     *    infoURL:    the function to use to load the information with __EID__ being the replacement string for the entity id (node id or file id)
     */
    Pig.prototype.ppdSettings = {
        height: 600, // the height of the popdown
        imageSize: '550',
        lightboxSize: '1200',
        // TODO: Convert this to a template in the templates folder
        template:  '<div class="ppd-expander"><div class="ppd-expander-inner"><span class="ppd-close" role="button" aria-label="Close Gallery Previewer"></span>' +
                        '<span class="next ppd-nav-arrow"><span class="icon"></span></span><span class="prev ppd-nav-arrow"><span class="icon"></span></span>' +
                        '<div class="ppd-fullimg"><div class="ppd-img-wrapper"><div class="ppd-loading image"><ul><li></li><li></li><li></li><li></li></ul><div id="ppd-loading-text">Loading&#133;</div></div><img src="#" style="display: none;" /></div></div><div class="ppd-details"><div class="loading-container"><div class="loading"></div></div></div>',
         imgSelector: '.ppd-fullimg img',
         infoSelector: '.ppd-details',
         infoURL:  '/shanti/grid/info/__TYPE__/__NID__',
         speed: 200,
         easing: 'easeOutQuart'
    };
    // The following attributes are not PPD settings but are for internal state tracking
    Pig.prototype.ppdOpen = false;
    Pig.prototype.ppdCloseOnResizeEnabled = false; // not a setting for keeping track of whether this is enabled or not
    Pig.prototype.ppdImage = false;
    Pig.prototype.ppdIndex = false;
    Pig.prototype.ppdClosedHeight = false;
    Pig.prototype.ppdOpenHeight = false;
    Pig.prototype.ppdClicked = false;

    /**
     * Overrides _parseImageData from pig.js
     */
    Pig.prototype._parseImageData = function(imageData) {
        this.imageData = imageData; // keep reference to image data (ndg8f)
        var progressiveImages = [];
        imageData.forEach(function(image, index) {
          var progressiveImage = new ProgressiveImage(image, index, this);
          progressiveImage.title = image.title;  // added by ndg8f
          progressiveImage.nid = image.nid;    // added by ndg8f
          progressiveImage.rotation = image.rotation // added by ndg8f
          progressiveImages.push(progressiveImage);
        }.bind(this));

        return progressiveImages;
      };

    /**
     * Extend pig with function in the following ways:
     *      1. to activate popdown when an image is clicked
     *      2. to install onclick listeners on nav arrows for popdown
     *      3. to install onclick listener on close button for popdown
     *      4. to install onclick listeners on popdown image and details buttons to open the lightbox slideshow
     */
    Pig.prototype.activatePopdown = function() {
        var _this = this;
        
        // Activate image clicking to open popdown
        var images = _this.images;
        for (n in images) {
            var el = images[n].element;
            $(el).attr('id', 'spimg-' + n);  // add an unique ID to figure element
            $(el).attr('data-nid', _this.imageData[n].nid); // add a data attribute to figure elements with nid value
            $(el).attr('data-path', _this.imageData[n].path); // add a data attribute to figure elements with nid value
            //console.log(el, _this.imageData[n]);
            $(el).unbind('click').click(function(e) {
                var pig = Drupal.settings.shanti_grid_view.mypig;
                //console.log($(e.target).get(0).tagName, e);
                if (pig.ppdImage.element != this) {
                    //console.log('opening');
                    pig.openPopdown(this);
                    $(el).addClass('selected');
                } else if ($(e.target).get(0).tagName == 'IMG' && !$(e.target).parents('.ppd-fullimg').length) {
                     pig.closePopdown(true);
                }
            });
        }
        // Use view setting for popdown image size
        _this.ppdSettings.imageSize = Drupal.settings.shanti_grid_view.popdown_image_size;
        // Activate popdown nav arrows and close
        $(document).on('click', '.prev.ppd-nav-arrow', function() {
            _this.gotoImage('prev');
        });
        $(document).on('click', '.next.ppd-nav-arrow', function() {
            _this.gotoImage('next');
        });

        // Activate popdown close button
        $(document).on('click', '.ppd-close', function() {
            _this.closePopdown(true, function() {
                _this.ppdIndex = false;
                _this.ppdImage = false;
                $('figure.select').removeClass('selected');
            });
        });

      // Activate ligthbox link
      // whenever the images is clicked or one of the view buttons
      // Removed ', .ppd-details .links .view-btn' from selector so I could hardcode the link so command click would work
      /* removing code below so that lightbox works on gallery
        $(document).on('click', '.ppd-img-wrapper img:visible', function(e) {
            e.preventDefault();
            var nid = $(this).parents('figure.pig-figure').eq(0).data('nid');
            var path = $(this).parents('figure.pig-figure').eq(0).data('path');
            if (path) {
                window.location.pathname = path;
            }
        });
        */
      /** Disabling Photoswipe Gallery for stand alone node page 
      $(document).on('click', '.ppd-img-wrapper img:visible, .ppd-details .links button', function(event) {
            event.preventDefault();
            var pswpElement = document.querySelectorAll('.pswp')[0];
            var iind = _this.ppdImage.index;
            var options = {
                index: iind,
                getNumItemsFn: function() { return _this.images.length; }
            };
            var imglist = _this.getImageInfo();
            _this.psgallery = new PhotoSwipe( pswpElement,
                                                                 PhotoSwipeUI_Default,
                                                                 imglist,
                                                                 options );
            _this.psgallery.init();
            _this.psgallery.goTo(iind);
        });
        **/
       
        

        // reset open and close heights on resize
        window.addEventListener('resize', function() {
            _this.ppdOpenHeight = _this.ppdClosedHeight = false;
        });
        
        document.addEventListener('keydown', function(e) { _this.interpretKeyEvent(e); });
        return this;
    };

   /**
    * interpretKeyEvent: handler for key events for popdown and else
    */
   Pig.prototype.interpretKeyEvent = function(e) {
       var _this = this;
       if (_this.ppdOpen) {
           switch(e.key) {
               case "ArrowLeft":
                   _this.gotoImage('prev');
                   break;
                   
               case "ArrowRight":
                   _this.gotoImage('next');
                   break;
                   
               case "Escape":
                    _this.closePopdown(true);
                    break;
                    
               default:
                   //console.log(e);
           }
       }
   };
   
   /**
    * getImageInfo: gets info of all images in the present gallery for the lightbox slideshow
    */
   Pig.prototype.getImageInfo = function() {
       var pgobj = Drupal.settings.shanti_grid_view.mypig;
       var imglist = [];
       $(pgobj.images).each(function() {
           var lbsize = pgobj.ppdSettings.lightboxSize;
           var info = {
               'src': pgobj.settings.urlForSize(this.filename, lbsize, this.rotation),
               'w': parseInt(lbsize),
               'h': parseInt(lbsize) / this.aspectRatio,
               'title': this.title
           };
           imglist.push(info);
       });
       return imglist;
   };

    /**
     *  Pig Popdown function called when an image is clicke it opens popdown.
     */
    Pig.prototype.openPopdown = function(el) {
        var _this = this; // The pig object
        $(el).addClass('ppd-expanded').siblings().removeClass('ppd-expanded');
        _this.ppdIndex = $(el).prevAll('figure').length; // Get index of this figure element
        var clickedImage = _this.images[_this.ppdIndex];  // get progressive image object for this figure element
       
        // if the popdown is already open on same row
        if (_this.ppdOpen) {
            _this.popdown.clicked = false; // used to detect if swipe/touch action is in progress
            // If it's in the same row, just load its info into the already open popdown and return
            if (clickedImage.style.translateY == _this.ppdImage.style.translateY) {
                _this.ppdImage = clickedImage;
                $(_this.ppdSettings.imgSelector).attr('src', '');
                $(_this.ppdSettings.infoSelector).html('<div class="ppd-loading details" style="display: block;"></div>');
                
                var ppd = _this.popdown.detach(); // move popdown inside new figure/images
                $(el).append(ppd);
                
                var parenttrans = parseMatrixValue($(el).css('transform')); // adjust the xshift base on new parent
                _this.popdown.css({'transform': 'translate3d(-' + parenttrans.xshift + 'px, 0px, 0)'});
                
                _this.loadPopdown(); // load new content
                return;
            }
        }
        
        
        // If popdown is not open or not on same row
        // Close any open popdown, shifting up (true) and then open a new one (callback)
        _this.closePopdown(true, function() {
            _this.ppdImage = clickedImage;  // set the ppdImage to the currently clicked image
            $('.ppd-expander').remove(); // remove any vestiges
            $('.ppd-expanded').removeClass('ppd-expanded'); // Open the popdown after previous one is closed
            $(el).addClass('ppd-expanded'); // add expanded class
            var myY = _this.ppdImage.style.translateY;   // get its Y translation value
            
            _this.popdown = $(el).append(_this.ppdSettings.template).children().last().css('height', 0); // Add popdown template to element and show it.
           
            var parenttrans = parseMatrixValue($(el).css('transform')); // position and open the popdown
            var gridwidth = $('#' + _this.settings.containerId).width();
            
            _this.popdown.css({
                'transform': 'translate3d(-' + parenttrans.xshift + 'px, 0px, 0)',
			    'width': gridwidth + 'px',
            });
            
            _this.loadPopdown(); // start loading info into popdown
            
            
            _this.popdown.css('transition' , 'height ' + _this.ppdSettings.speed + 'ms ' + _this.ppdSettings.easing);
            _this.popdown.css('height', _this.ppdSettings.height);
           _this.shiftDown(myY); 
           
            _this.ppdOpen = true;
            _this.closePopdownOnResize();
            
           setTimeout(function() {
                _this.scrollToView();
            }, 400);
        });

    };

    /**
     * Function to load the popdown via AJAX using the ppdSetting.infoUrl
     */
    Pig.prototype.loadPopdown = function() {
        var _this = this;

        $('.ppd-loading').show();
        // Load and center the image
        var img = $(_this.ppdSettings.imgSelector).eq(0);
        var imgurl = _this.settings.urlForSize(_this.ppdImage.filename, _this.ppdSettings.imageSize, _this.ppdImage.rotation);
        img.unbind('load').on('load', function() {
            $(this).fadeIn();
            $('.ppd-loading.image').hide();
        }).attr('src', imgurl);
        
        // Get URL for info call and make ajax call to load in infoSelector div
        var url = _this.ppdSettings.infoURL;
        url = url.replace('__TYPE__', _this.settings.entityType).replace('__NID__', _this.ppdImage.nid);
        // Show loading animation for details (.loading.details) because on newly created nodes with lots of kmaps
        // the details can take a while to load the first time
        $(_this.ppdSettings.infoSelector).html('<div class="loading details" style="display: block;"></div>').load(url, function() {
            Drupal.attachBehaviors(_this.ppdSettings.infoSelector);  // Attach behaviors to loaded content for kmaps popovers
            var href = _this.imageData[_this.ppdIndex].path;
            $('.ppd-details .links .view-btn').attr('href', href);
        });
        
        // Add Swipe listener to the popdown inner div to move image previous or next
        var ppdinner = $('.ppd-expander-inner').get(0);
        if (ppdinner) { 
            _this.popdown.hammer = new Hammer(ppdinner);
            _this.popdown.hammer.on("swipe", function(ev) {
                if (!_this.ppdClicked) {
                    if (ev.deltaX < 0) {
                        _this.gotoImage('prev');
                    } else {
                        _this.gotoImage('next');
                    }
                    _this.popdown.hammer.stop(true); // This doesn't seem to stop the listening, so ...
                    _this.ppdClicked = true;
                    setTimeout(function() { _this.ppdClicked = false; }, 500);
                }
            });
        }

        // wraps flexslideshow image w/anchor element, and displays icon for expand in center of image
        $('.ppd-fullimg img').wrap('<a href="#" class="pswp-link" title="Fullscreen Image Viewer"></a>');
        $('.ppd-fullimg a.pswp-link').hover(function () {
            $(this).prepend('<span class="fa fa-arrows-alt"></span>');
            $('.ppd-fullimg .fa-arrows-alt').fadeIn(5000);
          },
          function () {
            $('.ppd-fullimg .fa-arrows-alt').remove();
          }
        );
        
    };

    /**
     * Function to scroll popdown into view if it isn't already
     */
    Pig.prototype.scrollToView = function() {
        //return;
        var _this = this;
        var ppd = $(_this.popdown);
        
        if (typeof(ppd.offset)  === 'function' && typeof(ppd.offset()) != 'undefined' && typeof(ppd.offset()) != 'undefined') {
            var diff = $(window).height() - (ppd.height() + 50);
            var sttop = ppd.offset().top - diff; // This measures from the bottom of the previewer, the goal being about 30px from bottom of browser
            $('html,body').animate({scrollTop:sttop}, 350);

            // if (navigator.userAgent.match('Safari') && !navigator.userAgent.match('Chrome')) {  // For Safari scrollTop must be set on body
            //    $('body').animate({scrollTop:sttop}, 350);
            // } else {
            //    $('html').animate({scrollTop:sttop}, 350);
            // }
        } 
    };

    /**
     * Function to close and open popdown
     * Takes a callback so it can be called by the openPopdown function to close any open popdowns not on the same row
     * Callback is called immediately if no popup is opened, but if one is, then it is only called after the open one is closed.
     */
    Pig.prototype.closePopdown = function(doShift, callback) {
        var _this = this;
        if (typeof(_this.popdown) == "object") {
            if (doShift) {  _this.shiftUp(); } 
            /*_this.popdown.css('transition' , 'height ' + _this.ppdSettings.speed + 'ms ' + _this.ppdSettings.easing);
                        .css('height', 0);*/
            _this.popdown.slideUp(_this.ppdSettings.speed,
                                    function() {
                                        var pig = Drupal.settings.shanti_grid_view.mypig;
                                        if (typeof(pig.popdown && pig.popdown.remove) == 'function') {
                                            pig.popdown.remove();
                                        }
                                        $('.ppd-expanded').removeClass('ppd-expanded');
                                        pig.ppdOpen = false;
                                        pig.popdown = false;
                                        pig.ppdImage = false;
                                        //console.log('pig after close', pig);
                                        if (typeof(callback) === 'function') {
                                            callback();
                                        }
                                     }); 

        } else {
            typeof callback === 'function' && callback();
        }
    };

    /**
     * Function to shift down .ppdHeight all images with Y shift greater than given
     */
    Pig.prototype.shiftDown = function(yshift) {
        var _this = this;  // set  _this variable to current Pig Object
        // Register total height of window when ppd is open or closed and set it to opened height
        if (!_this.ppdClosedHeight) {
            _this.ppdClosedHeight =  _this.container.clientHeight + "px";
            _this.ppdOpenHeight =  (_this.container.clientHeight + _this.ppdSettings.height) + "px";
        }
      $(_this.container).css("height", _this.ppdOpenHeight);
        var shiftimgs = [];
        for (n in _this.images) {
            var img = _this.images[n];
            if (img.style.translateY > yshift) {
                $(img.element).addClass('ppdshifted');
                shiftimgs.push(img.element);
            }
        }
        _this.shiftImages(shiftimgs, 'down');
    };

    /**
     * Function to shift objects back up .ppdHeight
     */
    Pig.prototype.shiftUp = function(callback) {
      var _this = this;
      if($('.ppdshifted').length > 0) {
        var ind = $('.ppdshifted').eq(0).prevAll('figure').length;
        var shiftimgs = [];
        var tmpimgs = _this.images.slice(ind);
        $.each(tmpimgs, function(n, img) { shiftimgs.push(img.element);});
        _this.shiftImages(shiftimgs, 'up');
        $('.ppdshifted').removeClass('ppdshifted');
      }
      $(_this.container).css("height", _this.ppdCloseHeight);
    };

    /**
     * shiftImages: given an array of figure DOM elements and a direction, shifts those elements the height of the popdown in that direction
     *          shiftimgs : an array of figure DOM elements
     *          direction: a string either "up" or "down"
     */
    Pig.prototype.shiftImages = function(shiftimgs, direction) {
        var _this = this;
        var shfdir = (direction == 'up') ? -1 : 1,
              shftamt = _this.ppdSettings.height * shfdir,
               transnm = getSupportedTransformProperty();
         $.each(shiftimgs, function(index, item) {
                var mytpv = item.style[transnm];
                var mtch = mytpv.match(/, (\d+\.?\d*)px,/); // middle value is Y
                if (mtch && mtch.length > 1) {
                    var newY = parseInt(mtch[1]) + shftamt;
                    var newtpv = mytpv.replace(', ' + mtch[1] + 'px,', ', ' + newY + 'px,');
                    $(item).css('transition', transnm + ' ' + _this.ppdSettings.speed + 'ms ' + _this.ppdSettings.easing).css(transnm, newtpv);
                }
            });
    };

    /**
     * The gotoImage function makes the popdown open for a particular image by index or 'prev' and 'next' string
     * The latter are used by the corresponding buttons in the popdown
     */
    Pig.prototype.gotoImage = function(iind) {
        var _this = this;
        if (typeof(iind) == "undefined") { return; }
        if (iind == "prev") {
            iind = _this.ppdIndex - 1;
            if (iind < 0) { iind = _this.images.length - 1; }
        }
        if (iind == "next") {
            iind = _this.ppdIndex + 1;
            if (iind > _this.images.length - 1) { iind = 0; }
        }
        _this.openPopdown(_this.images[iind].element);
    };


    /**
     * On window resize close popdown
     */
    Pig.prototype.closePopdownOnResize = function() {
        if (!this.ppdCloseOnResizeEnabled) {
            var _this = this;
            this.ppdCloseOnResizeEnabled = true;
            window.addEventListener('resize', function() {
                _this.closePopdown(true);
            });
        }
    };

  /**
   * Overriding ProgressiveImage.prototype.load function
   * Mostly the same. Only code added at bottom
   */
  ProgressiveImage.prototype.load = function() {
    // Create a new image element, and insert it into the DOM. It doesn't
    // matter the order of the figure elements, because all positioning
    // is done using transforms.
    this.existsOnPage = true;
    this._updateStyles();
    this.pig.container.appendChild(this.getElement());

    // We run the rest of the function in a 100ms setTimeout so that if the
    // user is scrolling down the page very fast and hide() is called within
    // 100ms of load(), the hide() function will set this.existsOnPage to false
    // and we can exit.
    setTimeout(function() {

      // The image was hidden very quickly after being loaded, so don't bother
      // loading it at all.
      if (!this.existsOnPage) {
        return;
      }

      // Show thumbnail
      if (!this.thumbnail) {
        this.thumbnail = new Image();
        this.thumbnail.src = this.pig.settings.urlForSize(this.filename, this.pig.settings.thumbnailSize, this.rotation);
        this.thumbnail.className = this.classNames.thumbnail;
        this.thumbnail.onload = function() {

          // We have to make sure thumbnail still exists, we may have already been
          // deallocated if the user scrolls too fast.
          if (this.thumbnail) {
            this.thumbnail.className += ' ' + this.classNames.loaded;
          }
        }.bind(this);

        this.getElement().appendChild(this.thumbnail);
      }

      // Show full image
      if (!this.fullImage) {
        this.fullImage = new Image();
        this.fullImage.src = this.pig.settings.urlForSize(this.filename, this.pig.settings.getImageSize(this.pig.lastWindowWidth), this.rotation);
        this.fullImage.onload = function() {

          // We have to make sure fullImage still exists, we may have already been
          // deallocated if the user scrolls too fast.
          if (this.fullImage) {
            this.fullImage.className += ' ' + this.classNames.loaded;
          }
        }.bind(this);

        this.getElement().appendChild(this.fullImage);

        // Add Footer  (code added by ndg8f)
        this.footer = document.createElement('div');
        this.footer.className = 'img-footer-overlay';
        this.footer.style.display = 'none';
        this.footer.innerHTML = this.title;
        this.getElement().appendChild(this.footer);
      }
    }.bind(this), 100);
  }; // End of ProgressiveImage extension

//********** HELPER FUNCTION *****************//
// function to get which transform name
function getSupportedTransformProperty() {
    var properties = ["transform", "msTransform", "webkitTransform", "mozTransform", "oTransform"];
    for (var i = 0; i < properties.length; i++) {
        if (typeof document.body.style[properties[i]] != "undefined") {
            return properties[i];
        }
    }
    return null;
}

/**
 * Function to parse the css matrix value returned by $(el).css('transform')
 * And return just translateX (5th part) and translateY (6th part)
 */
function parseMatrixValue(mv) {
    var m = mv.match(/\(([\d\s\,\.]+)\)/);
    if (m) {
        var mvals = m[1].replace(/\s+/g, '').split(',');
        for (var n in mvals) {
            mvals[n] *= 1;
        }
        return {'xshift': mvals[4], 'yshift': mvals[5]};
    } else {
        return false;
    }
}

// Debugger that shows view port size. Helps when making responsive designs; mf8yk nov 2017
// -----------
/*
function showViewPortSize(display) {
    if(display) { 
      var height = window.innerHeight;
      var width = window.innerWidth;
      jQuery('body').prepend('<div id="viewportsize" style="z-index:9999;position:fixed;bottom:20px;left:0px;color:#fff;background:#000;padding:10px">Height: '+height+'<br>Width: '+width+'</div>');
      jQuery(window).resize(function() {
          height = window.innerHeight;
          width = window.innerWidth;
          jQuery('#viewportsize').html('Height: '+height+'<br>Width: '+width);
      });
    }
}

$(document).ready(function(){
 showViewPortSize(true);
});
*/

})(jQuery);
