(function ($) { // jQuery wrapper function
	var bto;
	Drupal.behaviors.bhutan_search_deafultOpen = {
		attach: function (context, settings) {
				if($(".flyout-open").length ) { 
					$("#search-flyout").once('openflyout', function() {
						$(this).openMbExtruder();
						$('#kmaps-search .treeview a').click();
						bto = setInterval(function() {
							if($('#ajax-id-8260').length > 0) {
								var topPos = document.getElementById('ajax-id-8260').offsetTop;
								document.getElementById('tree').scrollTop = topPos;
								window.clearInterval(bto);
							}
							if($('#ajax-id-427').length > 0) {
								var topPos = document.getElementById('ajax-id-427').offsetTop;
								document.getElementById('tree').scrollTop = topPos;
								window.clearInterval(bto);
							}  
						}, 1000);
						setTimeout(function() { window.clearInterval(bto); }, 15000);
					});
				}
				
    }
  };	
  			
} (jQuery));