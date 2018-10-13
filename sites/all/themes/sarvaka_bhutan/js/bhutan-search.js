(function ($) { // jQuery wrapper function
	var bto;
	Drupal.behaviors.bhutan_search_deafultOpen = {
		attach: function(context, settings) {
			if($(".flyout-open").length ) {
				$("#search-flyout").once('openflyout', function() {
					$(this).openMbExtruder();
					$('#kmaps-search .treeview a').click();
					bto = setInterval(function() {
						if($('#ajax-id-8260').length > 0) {
							var topPos = document.getElementById('ajax-id-8260').offsetTop;
							//The 'tree' element is not being found
							//document.getElementById('tree').scrollTop = topPos;
							window.clearInterval(bto);
						}
						if($('#ajax-id-427').length > 0) {
							var topPos = document.getElementById('ajax-id-427').offsetTop;
							//The 'tree' element is not being found
							//document.getElementById('tree').scrollTop = topPos;
							window.clearInterval(bto);
						}
					}, 1000);
					setTimeout(function() { window.clearInterval(bto); }, 15000);
				});
			}
		}
    }

    // Sidebar and footer coordinate heights
    Drupal.behaviors.bhutanSidebarFooterGravity = {
        attach: function (context, settings) {
            Drupal.ShantiSarvaka.bhutanSidebarFooterGravity = function () {
                console.log("Here we go again");
                var height = $(window).height();
                var mainwrapper_minimum = (height) - 190;
                var mainwrapper_minimum_hastabs = (height) - 230;
                var mainwrapper_minimum_hasadminmenu = (height) - 220;
                var mainwrapper_minimum_hasadminfooter = (height) - 252;

                mainwrapper_minimum = parseInt(mainwrapper_minimum) + 'px';
                mainwrapper_minimum_hastabs = parseInt(mainwrapper_minimum_hastabs) + 'px';
                mainwrapper_minimum_hasadminmenu = parseInt(mainwrapper_minimum_hasadminmenu) + 'px';
                mainwrapper_minimum_hasadminfooter = parseInt(mainwrapper_minimum_hasadminfooter) + 'px';

                $(".main-col").css('min-height', mainwrapper_minimum);
                $(".has-tabs .main-col").css('min-height', mainwrapper_minimum_hastabs);
                $(".admin-menu .main-col").css('min-height', mainwrapper_minimum_hasadminmenu);
                $(".admin-menu.has-tabs .main-col").css('min-height', mainwrapper_minimum_hasadminfooter);
            };

            $(window).bind('load resize orientationchange', function () {
                clearTimeout(this.id);
                this.id = setTimeout(Drupal.ShantiSarvaka.bhutanSidebarFooterGravity, 300);
            });
        }
    };
} (jQuery));