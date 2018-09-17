(function ($) {
    "use strict";

    Drupal.behaviors.shanti_footnotes = {
        attach: function (context, settings) {

            // javascript is enabled. (just to be sure)
            $('html').addClass('js');

						$('sup[data-footnote-id]').each(function (index,element) {
							var n 			= index + 1;
							var dfid 		= $(element).attr('data-footnote-id');

							var fnm_id 	= 'footnote-marker-' + n + '-1';
							var fn_id 	= 'footnote-' + n;

							var $fnm_a 	= $('sup[data-footnote-id="'+dfid+'"] > a');							
							$fnm_a.attr('id',fnm_id);
							$fnm_a.attr('href', '#'+fn_id);
							$fnm_a.text(n);
							
							var $fn_a		= $('li[data-footnote-id="'+dfid+'"] > a');
							$fn_a.attr('id',fn_id);
							$fn_a.attr('href','#'+fnm_id);
							$fn_a.text(n);

						});						 
            
        }
    };
})(jQuery)