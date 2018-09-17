	
(function ($) {

	Drupal.behaviors.shantiTextSearchFlyoutCancel = {
		attach: function (context, settings) {
				if(context == window.document) {
													
					var mbsrch = $(".view-filters input.form-control");  // the main search input
					$(mbsrch).attr("placeholder", "Enter Search...");
				    $(mbsrch).data("holder", $(mbsrch).attr("placeholder"));
				    $(".views-reset-button button").hide();
				
				    // --- focusin - focusout
				    $(mbsrch).focusin(function () {
				        $(mbsrch).attr("placeholder", "");
				        $(".views-reset-button button").show("fast");
				    });

				    $(mbsrch).focusout(function () {
				        $(mbsrch).attr("placeholder", $(mbsrch).data("holder"));
				        $(".views-reset-button button").hide();
				
				        var str = "Enter Search...";
				        var txt = $(mbsrch).val();
				
				        if (str.indexOf(txt) > -1) {
				            $(".views-reset-button button").hide();
				            return true;
				        } else {
				            $(".views-reset-button button").show(100);
				            return false;
				        }
				    });
				
				}
		}
	};	  	


}(jQuery));