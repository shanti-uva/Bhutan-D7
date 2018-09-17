drupal_shanti_explore_menu
==========================

Creates the standard explore menu for Shanti projects used by Shanti Sarvaka theme.
Creates a block to place in the Top Bar of the Sarvaka theme that creates a button and the corresponding drop down display of the menu
Link data is taken from the json file at explore_menu/js/shanti-collections.json

Data file contains a links array. Each item in the array is formatted as such:

```
{"class": "overview", "text": "Overview", "href": "http://shanti.virginia.edu/"},
```

The item array subfields are:
	* *class* : the name of the shanticon class used for the icon
	* *text* : the text to display for the link
	* *href* : the absolute url for the link (if relative urls are given here the site's base_url and base_path will be prepended to it)
	* *disabled* : if defined and set to true, the link will not be added to the menu (used to effectively comment out not yet known links as comments cannot be used in JSON)
	* *weight* : (TODO: Need to enable this) The menu weight to give to the item. By default the order of items will correspond to the order of the items in the data array by giving it a weight of ARRAY_INDEX - 50, i.e. ascending from -50.

Block has configuration settings:
	* *Block Title* : Standard block title field
	* *Section Element Class* : The value for the class attribute of the section element containing the content div, defaults to: container opencollect collections
	* *Containing Div Class* : The value for the class attribute of the div containing the links to the collections, defaults to: col-sm-12 col-md-10 col-md-offset-1
	* *Title* : Title to display at the top of the collection links, defaults to: Title to display at the top of the collection links
	* *Link Text* : Text for button in top bar, default to: EXPLORE
	* *Update Menu Links* : When this button is pressed, it reads in the data fil

TODO: Still need final list of links to fill out info in js/shanti-collections.json Right now many are temporary or disabled.
