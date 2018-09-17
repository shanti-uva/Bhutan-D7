drupal_shanti_user_prefs
==========================

Creates a user preferences module to insert in the Shanti Sarvaka "main menu" drop down
User preferences determine how user wants to see the site and are stored in a table as a json object
and are accessible via Javascript or Drupal PHP.

Preference definitions are read from the js/data folder with each .json file there being a preference set to be chosed by the admin.
A preference definition will have the following JSON structure (minus the comments):

{
	"id":"default", // name/unique id of preference set
	"prefix": "shanti" // prefix to prepend to a preferences machine name with intervening underscore, e.g. "shanti_perspective"
	"langs": {      // An object with a field for each language 
		"eng": [      // Each language contains an array of preference groups
			{           // A preference group is an object with 3 fields: title, machinename, type, and options
				"title": "Perspective",        // the title to be displayed above this group of preferences
				"machine_name": "perspective", // 
				"type": "radio"                // the type of form element: radio, check, select
				"options": [                   // defines options for the element. These are a value:label pair separated by a colon
					"gen:General",
					"tib:Tibetan"
				]
			},
			
		]
	}
}
