/*
* debouncedresize: special jQuery event that happens once after a window resize
*
* latest version and complete README available on Github:
* https://github.com/louisremi/jquery-smartresize/blob/master/jquery.debouncedresize.js
*
* Copyright 2011 @louis_remi
* Licensed under the MIT license.
*/

(function ($) {
	Drupal.behaviors.kmaps_exlorer_grid2 = {
		attach: function(context, settings) {
			var $event = $.event,
			$special,
			resizeTimeout;

			$special = $event.special.debouncedresize = {
				setup: function() {
					$( this ).on( "resize", $special.handler );
				},
				teardown: function() {
					$( this ).off( "resize", $special.handler );
				},
				handler: function( event, execAsap ) {
					// Save the context
					var context = this,
						args = arguments,
						dispatch = function() {
							// set correct event type
							event.type = "debouncedresize";
							$event.dispatch.apply( context, args );
						};

					if ( resizeTimeout ) {
						clearTimeout( resizeTimeout );
					}

					execAsap ?
						dispatch() :
						resizeTimeout = setTimeout( dispatch, $special.threshold );
				},
				threshold: 250
			};
		}//End of attach
	};
}) (jQuery);

var Grid = (function($) {

		// list of items
	var $grid = $( '#og-grid' ),
		// the items
		$items = $grid.children( '.item' ),
		// current expanded item's index
		current = -1,
		// position (top) of the expanded item
		// used to know if the preview will expand in a different row
		previewPos = -1,
		// extra amount of pixels to scroll the window
		scrollExtra = 0,
		// extra margin when expanded (between preview overlay and the next items)
		marginExpanded = 10,
		$window = $( window ), winsize,
		$body = $( 'html, body' ),
		// transitionend events
		transEndEventNames = {
			'WebkitTransition' : 'webkitTransitionEnd',
			'MozTransition' : 'transitionend',
			'OTransition' : 'oTransitionEnd',
			'msTransition' : 'MSTransitionEnd',
			'transition' : 'transitionend'
		},
		transEndEventName = transEndEventNames[ Modernizr.prefixed( 'transition' ) ],
		// support for csstransitions
		support = Modernizr.csstransitions,
		// default settings
		settings = {
			minHeight : 500,
			speed : 350,
			easing : 'ease'
		};

	function init( config ) {

		// the settings..
		settings = $.extend( true, {}, settings, config );

		imagesLoaded($grid, $.proxy(function() {
			initGridLayout();
			initLightbox();
			// save item´s size and offset
			saveItemInfo( true );
			// get window´s size
			getWinSize();
			// initialize some events
			initEvents();
		}, this));

	}

	// Initialize the row Grid layout called from init and on window resize
	function initGridLayout() {
		var res = $("#og-grid").rowGrid({itemSelector: ".item", minMargin: 10, maxMargin: 10, firstItemClass: "first-item"});
		// iterate through grid children (= div.item) and set their <a> heights
        res.children('.item').each(function(key, value) {
						var mya = $(this).children('a').eq(0);
						mya.css( {"height" : $(this).height(), "display" : "block" } );
        });
	}

	// Initialization of lightbox by creating list of items.
	function initLightbox() {
		var items = [];
		$("#og-grid .item a").each(function() {
			var data = $(this).attr('data-hugesrc');
			data = data.split("::");
			var item = {
				'src': data[0],
				'w': data[1],
				'h': data[2],
				'title': $(this).attr('data-title'),
			};
			items.push(item);
		});

		Drupal.settings.media_sharedshelf = {'lbitems' : items};

	}

	// add more items to the grid.
	// the new items need to appended to the grid.
	// after that call Grid.addItems(theItems);
	function addItems( $newitems ) {

		$items = $items.add( $newitems );

		$newitems.each( function() {
			var $item = $( this );
			$item.data( {
				offsetTop : $item.offset().top,
				height : $item.height()
			} );
		} );

		initItemsEvents( $newitems );

	}

	// saves the item´s offset top and height (if saveheight is true)
	function saveItemInfo( saveheight ) {
		$('#og-grid > .item').each( function() {
			var $item = $( this );
			$item.data( 'offsetTop', $item.offset().top );
			if( saveheight ) {
				$item.data( 'height', $item.height() );
			}
		} );
	}

	function initEvents() {

		// when clicking an item, show the preview with the item´s info and large image.
		// close the item if already expanded.
		// also close if clicking on the item´s cross
		initItemsEvents( $('#og-grid > .item') );

		// on window resize get the window´s size again
		// reset some values..
		$window.on( 'debouncedresize', function() {
			scrollExtra = 0;
			previewPos = -1;
			// save item´s offset
			saveItemInfo();
			getWinSize();
			var preview = $.data( this, 'preview' );
			if( typeof preview != 'undefined' ) {
				hidePreview();
			}
			initGridLayout();
		} );

	}

	function initItemsEvents( $items ) {
        $('#og-grid > .item').on( 'click', 'span.og-close', function() {
			hidePreview();
			return false;
		} ).children( 'a' ).on( 'click', function(e) {

			var $item = $( this ).parent();
			// check if item already opened
			current === $item.index() ? hidePreview() : showPreview( $item );
			return false;

		} );
	}

	function getWinSize() {

			if ($(window).width() > 767){

				winsize = { width : $window.width(), height : $window.height() - 30 };

			} else {

				winsize = { width : $window.width(), height : $window.height() };

			}
	}

	function showPreview( $item ) {

		var preview = $.data( this, 'preview' ),
			// item´s offset top
			position = $item.data( 'offsetTop' );

		scrollExtra = 0;

		// if a preview exists and previewPos is different (different row) from item´s top then close it
		if( typeof preview != 'undefined' ) {

			// not in the same row
			if( previewPos !== position ) {
				// if position > previewPos then we need to take te current preview´s height in consideration when scrolling the window
				if( position > previewPos ) {
					scrollExtra = preview.height;
				}
				hidePreview();
			}
			// same row
			else {
				preview.update( $item );
				prevNextButtons($item);
				return false;
			}
		}

		// update previewPos
		previewPos = position;
		// initialize new preview for the clicked item
		preview = $.data( this, 'preview', new Preview( $item ) );
		// expand preview overlay
		preview.open();
		prevNextButtons($item);
	}

	function hidePreview() {
		current = -1;
		var preview = $.data( this, 'preview' );
		preview.close();
		$.removeData( this, 'preview' );
	}

	// the preview obj / overlay
	function Preview( $item ) {
		this.$item = $item;
		this.expandedIdx = this.$item.index();
		this.create();
		this.update();
	}

	// Enable the previews previous and next buttons
	function prevNextButtons($item) {
		var prevItem = $item.prev();
		if (prevItem.length == 0) {
			prevItem = $item.nextAll().last();
		}
		$('.og-expander .prev').unbind('click').click(function() {
			showPreview(prevItem);
		});
		var nextItem = $item.next();
		if (nextItem.length == 0) {
			nextItem = $('.og-grid .item').eq(0);
		}
		$('.og-expander .next').unbind('click').click(function() {
			showPreview(nextItem);
		});
	}

	Preview.prototype = {
		create : function() {
			// create Preview structure:
			this.$title = $( '<h3></h3>' );
			this.$description = $( '<p></p>' );
			//this.$href = $( '<a href="#" class="og-details-more og-view-more images-show-more-modal"><span class="icon shanticon-list2">Read More</span></a>' );
			this.$copyurl = $('<button class="btn btn-default btn-sm copyurl"><span><span class="fa fa-clipboard" aria-hidden="true"></span> Copy URL</span></button>');
			this.$lightboxLink = $( '<a href="#" class="lightbox-link btn-lightbox og-view-more"><span class="icon fa-expand">View Full Screen</span></a>' );

			this.$tabs = $('<ul class="nav nav-tabs" role="tablist">' +
	   			'<li role="presentation" class="active"><a href="#desc" aria-controls="desc" role="tab" data-toggle="tab">Description</a></li>' +
					'<li role="presentation"><a href="#info" aria-controls="info" role="tab" data-toggle="tab">Details</a></li>' +
	   			'<li role="presentation"><a href="#download" aria-controls="info" role="tab" data-toggle="tab">Downloads</a></li></ul>');
	   	this.$desctab = $('<div role="tabpanel" class="tab-pane active" id="desc"></div>').append( this.$title, this.$description, this.$lightboxLink);
   		//this.$photographer = $('<li class="photographer">Photographer</li>');
   		this.$place = $('<li class="place">Places: Not available</li>');
			this.$subject = $('<li class="date">Subjects: Not available</li>');
   		this.$creator = $('<li class="creator">Photographer</li>');
   		this.$dtype = $('<li class="dtype">Type</li>');
   		this.$ssid = $('<li class="dtype">Shared Shelf ID</li>');
   		this.$infolist = $('<ul></ul>').append(this.$creator, this.$place, this.$subject, this.$dtype, this.$ssid);
   		this.$infotab = $('<div role="tabpanel" class="tab-pane" id="info"></div>').append(this.$infolist, this.$href, this.$copyurl);
			//Download tab information
			this.$hugeDownloadImg = $('<li>Original Image</li>');
			this.$largeDownloadImg = $('<li>Large Image</li>');
			this.$dlInfo = $('<ul></ul>').append(this.$hugeDownloadImg, this.$largeDownloadImg);
			this.$downloadtab = $('<div role="tabpanel" class="tab-pane" id="download"></div>').append(this.$dlInfo);
   		this.$tabcontent = $('<div class="tab-content"></div>').append(this.$desctab, this.$infotab, this.$downloadtab);
			this.$details = $( '<div class="og-details"></div>' ).append(this.$tabs, this.$tabcontent);

			this.$loading = $( '<div class="og-loading"></div>' );
			this.$fullimage = $( '<div class="og-fullimg"></div>' ).append( this.$loading );
			this.$closePreview = $( '<span class="og-close"></span>' );

			this.$nextPreview = $( '<span class="next og-nav-arrow"><span class="icon"></span></span>' );
			this.$prevPreview = $( '<span class="prev og-nav-arrow"><span class="icon"></span></span>' );

			this.$previewInner = $( '<div class="og-expander-inner"></div>' ).append( this.$closePreview, this.$nextPreview, this.$prevPreview, this.$fullimage, this.$details );
			this.$previewEl = $( '<div class="og-expander"></div>' ).append( this.$previewInner );
			// append preview element to the item
			this.$item.append( this.getEl() );
			// set the transitions for the preview and the item
			if( support ) {
				this.setTransition();
			}
		},
		update : function( $item ) {
			if( $item ) {
				this.$item = $item;
			}

			// if already expanded remove class "og-expanded" from current item and add it to new item
			if( current !== -1 ) {
				var $currentItem = $('#og-grid > .item').eq( current );
				$currentItem.removeClass( 'og-expanded' );
				this.$item.addClass( 'og-expanded' );
				// position the preview correctly
				this.positionPreview();
			}

			// update current value
			current = this.$item.index();

			// update preview´s content
			var $itemEl = this.$item.children( 'a' ),
					eldata = {
						href : $itemEl.attr( 'href' ),
						largesrc : $itemEl.data( 'largesrc' ).toString().split('::')[0],
						hugesrc : $itemEl.data( 'hugesrc' ).toString().split('::')[0],
						title : $itemEl.data( 'title' ),
						description : $itemEl.data( 'description' ),
						creator : $itemEl.data( 'creator' ),
						date : $itemEl.data( 'date' ),
						place : $itemEl.data( 'place' ),
						dtype: $itemEl.data('type'),
						ssid: $itemEl.data('ssid'),
						placesIds: $itemEl.data('places').toString(),
						subjectsIds: $itemEl.data('subjects').toString()
					};

			this.$title.html( eldata.title );
			this.$description.html( eldata.description );

			var lnktxt = (eldata.dtype == 'pdf') ? "View PDF" : "Read more";
			// this.$href.html('<span>' + lnktxt + '</span>').attr({
			// 	"href": "#imagesModal",
			// 	"data-toggle": "modal",
			// 	"data-places": eldata.placesIds,
			// 	"data-subjects": eldata.subjectsIds
			// });

			//Get the related data for related places and subjects
			var placesArray = eldata.placesIds.split('::');
			var subjectsArray = eldata.subjectsIds.split('::');
			var entities = '';
			placesArray.forEach(function(el, ind, arry) {
				entities += 'id:places-' + el + '%20OR%20';
			});
			subjectsArray.forEach(function(el, ind, arry) {
				entities += 'id:subjects-' + el + '%20OR%20';
			});
			entities = entities.substring(0, entities.length - '%20OR%20'.length);
			var url = Drupal.settings.shanti_kmaps_admin.shanti_kmaps_admin_server_solr_terms + '/select?q=' + entities + '&wt=json&json.wrf=?';
			$.get(url, function(data) {
				var docs = data.response.docs;
				var relatedObjects = groupBy(docs, 'tree');
				console.log(relatedObjects);
				var placesMarkup = '<label>Places: </label>';
				relatedObjects.places.forEach(function(el, ind, arry) {
					placesMarkup += '<span>' + el.header + '</span>';
					placesMarkup += '<span id="' + el.id + '-common' + '" class="popover-kmaps" data-app="' + el.id.split("-")[0] + '" data-id="' + el.id.split("-")[1] + '">';
					placesMarkup += '<span class="popover-kmaps-tip"></span>';
					placesMarkup += '<span class="icon shanticon-menu3"></span>';
					placesMarkup += '</span> ' + '&nbsp;';
				});
				this.$place.html(placesMarkup);

				var subjectsMarkup = '<label>Subjects: </label>';
				relatedObjects.subjects.forEach(function(el, ind, arry) {
					subjectsMarkup += '<span>' + el.header + '</span>';
					subjectsMarkup += '<span id="' + el.id + '-common' + '" class="popover-kmaps" data-app="' + el.id.split("-")[0] + '" data-id="' + el.id.split("-")[1] + '">';
					subjectsMarkup += '<span class="popover-kmaps-tip"></span>';
					subjectsMarkup += '<span class="icon shanticon-menu3"></span>';
					subjectsMarkup += '</span> ' + '&nbsp;';
				});
				this.$subject.html(subjectsMarkup);

				//Functionality for popovers
	      $('.popover-kmaps').each(function() {
	        var $that = $(this);
	        var app = $that.data("app");
	        var kid = $that.data("id");
	        $that.popover({
	          html: true,
						placement: 'auto',
	          title: '<span id="pop-title-' + kid + '">Loading ...</span>',
	          content: '<span id="pop-content-' + kid + '">Please wait while captions and related assets load. Loading ...</span>'
	        });
	        $that.on('show.bs.popover', function() {
	          $('#pop-title-' + kid).html('');
	          $('#pop-content-' + kid).html('');
	          $('div.popover').hide();
	          $.get('/mandala/popover/populate/' + app + '/' + kid, function(data) {
            	//data = $.parseJSON(data);
							if (data.node) {
								if (data.node && data.node.header) {
									$('#pop-title-' + kid).html(data.node.header);
								}
								$('#pop-content-' + kid).html(populateSolrPopover(data));
							}
	          });
	        });
	      });
			}.bind(this), 'jsonp');

			this.$creator.html( "<label>Photographer:</label> " + eldata.creator );
			this.$dtype.html("<label>Type:</label> " + eldata.dtype);
			this.$ssid.html("<label>Shared Shelf ID:</label> " + eldata.ssid);
			this.$largeDownloadImg.html('<label>Large Image:</label> ' + '<a href="' + eldata.largesrc +
			'" download><span class="glyphicon glyphicon-download-alt" aria-hidden="true"></span>&nbsp; Download</a>');
			this.$hugeDownloadImg.html('<label>Original Image:</label> ' + '<a href="' + eldata.hugesrc +
			'" download><span class="glyphicon glyphicon-download-alt" aria-hidden="true"></span>&nbsp; Download</a>');

			var self = this;

			// remove the current image in the preview
			if( typeof self.$largeImg != 'undefined' ) {
				self.$largeImg.remove();
			}

			// preload large image and add it to the preview
			// for smaller screens we don´t display the large image (the media query will hide the fullimage wrapper)
			if( self.$fullimage.is( ':visible' ) ) {
				this.$loading.show();
				$( '<img/>' ).load( function() {
					var $img = $( this );
					if( $img.attr( 'src' ) === self.$item.children('a').data( 'largesrc' ) ) {
						//self.$loading.hide();
						self.$fullimage.find( 'img' ).remove();
						self.$fullimage.find('.og-img-wrapper').remove();
						self.$largeImgDiv = $('<div class="og-img-wrapper"></div>');
						self.$largeImg = $( '<a href="#" class="lightbox-img-link"></a>' );

						self.$largeImgDiv.append(self.$largeImg);
						self.$largeImg.append( $img.fadeIn( 100 ));
						self.$fullimage.append( self.$largeImgDiv );
						// Find the lightbox icon and enable click to initiate gallery
						$("a.lightbox-link, a.lightbox-img-link").unbind('click').click(function(event) {
							event.preventDefault();
       						var pswpElement = document.querySelectorAll('.pswp')[0];
       						var iind = self.$item.prevAll().length;
							var options = {
								index: iind,
								getNumItemsFn: function() { return Drupal.settings.sarvaka_image_gallery.total_items; }};
							Drupal.settings.media_sharedshelf.gallery = new PhotoSwipe( pswpElement, PhotoSwipeUI_Default, Drupal.settings.media_sharedshelf.lbitems, options);
							Drupal.settings.media_sharedshelf.gallery.init();
							Drupal.settings.media_sharedshelf.gallery.goTo(iind);
							var iteminfo = Drupal.settings.sarvaka_image_gallery,
									  incr = parseInt(iteminfo.items_per_page) * parseInt(iteminfo.page_number),
								 	  pts = $('.pswp__counter').text().split(' / ');
							pts[0] = iind + incr + 1;
							$('.pswp__counter').text(pts.join(' / '));

							// Adjust current item number based on pagination after markup change
							Drupal.settings.media_sharedshelf.gallery.listen('afterChange', function() {
								var iteminfo = Drupal.settings.sarvaka_image_gallery,
									  incr = parseInt(iteminfo.items_per_page) * parseInt(iteminfo.page_number),
								 	  pts = $('.pswp__counter').text().split(' / '),
									  index = this.items.indexOf(this.currItem) + 1;
								pts[0] = index + incr;
								$('.pswp__counter').text(pts.join(' / '));

							});
						});
						setTimeout(function() {
							 jQuery(".og-img-wrapper img").popupImageCentering();
						}, 300);
					}
				}).attr( 'src', eldata.largesrc );
			}

			//Functionality for images to show modal for more information
			$('#imagesModal').off();
			$('#imagesModal').on('show.bs.modal', function(e) {
				var placesArray = eldata.placesIds.split('::');
				var subjectsArray = eldata.subjectsIds.split('::');
				var entities = '';
				placesArray.forEach(function(el, ind, arry) {
					entities += 'id:places-' + el + '%20OR%20';
				});
				subjectsArray.forEach(function(el, ind, arry) {
					entities += 'id:subjects-' + el + '%20OR%20';
				});
				entities = entities.substring(0, entities.length - '%20OR%20'.length);
				var url = 'http://kidx.shanti.virginia.edu/solr/termindex-dev-update/select?q=' + entities + '&wt=json';
				$.get(url, function(data) {
					data = $.parseJSON(data);
					$('#imagesModal .images-modal-title').html(eldata.title);
					$('#imagesModal .images-modal-body').html(relatedPlacesSubjects(data));
				});
			});

			//Clipboard copy Functionality
			$('button.copyurl').click(function() {
				clipboard.copy(window.location.href);
			});

		},
		open : function() {

			setTimeout( $.proxy( function() {
				// set the height for the preview and the item
				this.setHeights();
				// scroll to position the preview in the right place
				this.positionPreview();
			}, this ), 25 );



		},
		close : function() {
			$('#imagesModal').off();

			var self = this,
				onEndFn = function() {
					if( support ) {
						$( this ).off( transEndEventName );
					}
					self.$item.removeClass( 'og-expanded' );
					self.$previewEl.remove();
				};

			setTimeout( $.proxy( function() {

				if( typeof this.$largeImg !== 'undefined' ) {
					this.$largeImg.fadeOut( 'fast' );
				}
				this.$previewEl.css( 'height', 0 );
				// the current expanded item (might be different from this.$item)
				var $expandedItem = $('#og-grid > .item').eq( this.expandedIdx );
				$expandedItem.css( 'height', $expandedItem.data( 'height' ) ).on( transEndEventName, onEndFn );

				if( !support ) {
					onEndFn.call();
				}

			}, this ), 25 );

			return false;

		},
		calcHeight : function() {

			var heightPreview = winsize.height - this.$item.data( 'height' ) - marginExpanded,
				itemHeight = winsize.height - this.$item.data('height');
                itemHeight = settings.minHeight + this.$item.data( 'height' ) + marginExpanded;

			if( heightPreview < settings.minHeight ) {
				heightPreview = settings.minHeight;
				itemHeight = settings.minHeight + this.$item.data( 'height' ) + marginExpanded;
			}

			this.height = settings.minHeight;
			this.itemHeight = itemHeight;
		},
		setHeights : function() {

			var self = this,
				onEndFn = function() {
					if( support ) {
						self.$item.off( transEndEventName );
					}
					self.$item.addClass( 'og-expanded' );
				};

			this.calcHeight();
			this.$previewEl.css( 'height', this.height );
			this.$item.css( 'height', this.itemHeight ).on( transEndEventName, onEndFn );

			if( !support ) {
				onEndFn.call();
			}

		},
		positionPreview : function() {

			// scroll page
			// case 1 : preview height + item height fits in window´s height
			// case 2 : preview height + item height does not fit in window´s height and preview height is smaller than window´s height
			// case 3 : preview height + item height does not fit in window´s height and preview height is bigger than window´s height
			var position = this.$item.data( 'offsetTop' ),
				previewOffsetT = this.$previewEl.offset().top - scrollExtra,
				scrollVal = this.height + this.$item.data( 'height' ) + marginExpanded <= winsize.height ? position : this.height < winsize.height ? previewOffsetT - ( winsize.height - this.height ) : previewOffsetT;

			$body.animate( { scrollTop : scrollVal }, settings.speed );

		},
		setTransition  : function() {
			this.$previewEl.css( 'transition', 'height ' + settings.speed + 'ms ' + settings.easing );
			this.$item.css( 'transition', 'height ' + settings.speed + 'ms ' + settings.easing );
		},
		getEl : function() {
			return this.$previewEl;
		}
	};

	return {
		init : init,
		addItems : addItems
	};

	//Utility groupBy function to split items into places and subjects;
	function groupBy(arr, property) {
	  return arr.reduce(function(memo, x) {
	    if (!memo[x[property]]) { memo[x[property]] = []; }
	    memo[x[property]].push(x);
	    return memo;
	  }, {});
	}

	//Create markup to return for the related images places and subjects.
	function relatedPlacesSubjects(data) {
		var docs = data.response.docs;
		var relatedObjects = groupBy(docs, 'tree');
		var template = $('#imagesInfo').html();
		var templateScript = Handlebars.compile(template);
		var html = templateScript(relatedObjects);
		return html;
	}

	//Create markup for related subjects in images.
	function imagessubjects(data) {
		var template = $('#imagessubjectspopover').html();
		var templateScript = Handlebars.compile(template);
		var html = templateScript(data);
		return html;
	}

	//Create markup for related places in images.
	function imagesplaces(data) {
		var template = $('#imagesplacespopover').html();
		var templateScript = Handlebars.compile(template);
		var html = templateScript(data);
		return html;
	}

	function populateSolrPopover(data) {
		//Create markup for related places in images.
		var template = $('#popover-general').html();
		var templateScript = Handlebars.compile(template);
		var html = templateScript(data);
		return html;
	}

})(jQuery);
