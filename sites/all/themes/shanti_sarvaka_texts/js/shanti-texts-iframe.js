(function ($) { // jQuery wrapper function
	// Moved to /shanti_sarvaka/js/sarv-iframe.js for all sites (2018-07-06)
	
	function inMBframe() {
	    try {
	        return window.self !== window.top;
	    } catch (e) {
	        return true;
	    }
	}
	
	/** Check to see whether is in iframe and change class accordingly **/
	Drupal.behaviors.sarvaka_mb_iframe_links = {
		attach: function (context, settings) {
			if(context == window.document) {
				if(inMBframe()) {
					$('body').addClass('in-frame');
				} else {
					$('body').removeClass('in-frame');
				}
			}
		}
	};
}(jQuery));


