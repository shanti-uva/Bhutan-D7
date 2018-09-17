(function ($) {
	Drupal.behaviors.shantiUserPrefs = {
	  attach: function (context, settings) {
		// If whole document is loading get user settings loaded from DB to Drupal settings object and make form match
	  	if(context == document) { 
		  	var pobj = settings.shantiUserPrefs;  
		  	// Put Each value in settings
		  	if(typeof(pobj.fields) == "object" && pobj.fields.length != undefined) {
			  	$.each(pobj.fields, function(n, ft) {
			  		var pts = ft.split(':');
			  		if(pts.length > 0) {
				  		var f = pts[0];
				  		var type = (pts.legnth > 1) ? pts[1] : '';
				  		if( pobj.preferences.hasOwnProperty(f)) {
				  			var inputs = $('#user-prefs input[name=' + f + '][value=' + pobj.preferences[f] + ']');
				  			if(inputs.length > 0) {
				  				inputs.iCheck('check');
				  			}
				  		}
				    }
			    }); // end of each 
		    }
		    // On change event: Register that settings have changed
		    // Just for checkboxes and radio buttons TODO: Implement for select and textareas (anything else?)
		    $('#user-prefs').on("ifChecked", "input[type=radio], input[type=checkbox]", 
		    	function(e) { 
		    		Drupal.settings.shantiUserPrefs.isChanged = true; 
		    		var nm = $(this).attr('name');
		    		$('input[name=' + nm + ']').removeAttr('checked');
		    		$(this).attr('checked','checked');
		    	}
		    );
		    
		    // Determine when main menu is closed and if changed, save settings.
		    $('nav.menu-buttons span').click(function() { Drupal.settings.shantiUserPrefs.menuOpen = true; });
		    // When main menu check if main menu is being closed
				$(document).click(function() {
					// If main menu is open then it's being closed
					if( Drupal.settings.shantiUserPrefs.menuOpen) {
						Drupal.settings.shantiUserPrefs.menuOpen = false;
						// If settings have changed save them
						if(Drupal.settings.shantiUserPrefs.isChanged) {
						 	// Get new settings from "form"
						 	var mysettings = {};
						 	var pobj = settings.shantiUserPrefs;  
					  	// Get the value of each field in the settings
					  	$.each(pobj.fields, function(n, ft) {
					  		var pts = ft.split(':');
					  		if(pts.length > 0) {
						  		var f = pts[0];
						  		mysettings[f] = $('#user-prefs .checked input[name=' + f + ']').val();
						    }
					    }); // end of each 
					    // Serialize and place in save form field and send Ajax save command
					    Drupal.settings.shantiUserPrefs.preferences = mysettings;
					    mysettings = JSON.stringify(mysettings);
						 	Drupal.settings.shantiUserPrefs.isChanged = false;
					    // Put json in json field of save form and submit the ajax save
					    $('#user-prefs-field').val(mysettings);
					    $('#user-prefs-form button[type=submit]').mousedown();
						 	Drupal.settings.shantiUserPrefs.isChanged = false;
						} 
					}
				});
			}
	  }
	};
}(jQuery));