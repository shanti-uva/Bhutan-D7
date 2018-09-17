(function ($) { // jQuery wrapper function
	
	function inIframe() {
	    try {
	        return window.self !== window.top;
	    } catch (e) {
	        return true;
	    }
	}
	
	/** Check to see whether is in iframe and change class accordingly **/
	Drupal.behaviors.shanti_sarvaka_in_iframe = {
		attach: function (context, settings) {
			if(context == window.document) {
				if(inIframe()) {
					$('body').addClass('in-frame');
					//console.log('in iframe');
				} else {
					$('body').removeClass('in-frame');
                    //console.log('not in iframe');
				}
			}
		}
	};
}(jQuery));


