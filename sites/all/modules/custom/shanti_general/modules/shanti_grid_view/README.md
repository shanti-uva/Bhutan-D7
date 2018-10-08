Description
--------------------
The Shanti Grid View module provides a Views format to display an interactive gallery for viewing images similar to the 
images result page when searching in Google. It displays thumbnails of a certain size in a fluid grid, which when clicked 
on open down into a larger version of the image and further description and details of the image. It further provides 
a fullscreen lightbox slideshow view of the gallery. 

The view is field-based and can be display either files or nodes. Two fields are required an image thumbnail field and 
a larger image field to show in the drop down. These can and probably should be the same image displayed with different 
size image styles. For thumbnails a height between 150-200 seems best. For the larger size something between 1000 and 2000+, 
since the large size is also used for the lightbox fullscreen view.

When these fields have been added to the view, one should choose the format "Shanti Grid" and under the settings asign 
the thumbnail image and the larger image.

Uses
--------------------
The Grid view is designed to be used with Shanti IIIF Images, Media image files, Nodes, and custom views data sources.
Create a view of the desired source (images, files, nodes, data source), choose the fields for each row of the view, 
and the under the settings fill in the appropriate details for each one. 
Some of the types need to map fields in the view to types of data in the drop down. So you will 
need to add the fields to the view before filling out the settings.

### Custom Data Source Views
Custom data source view are views that use a custom plugin that adapts an external data sources, such as 
SOLR to views. These require some custom coding to work with the grid views module. The settings such views have are: 

* __Item ID__: a select list of field in the view. Choose the field that contains the item's ID
* __Item Title__: A similar select for the field that has the title
* __Thumbnail Image__: A similar select for the thumbnail image 
* __Image URL Syntax__: Syntax to use to get images of different sizes, uses \_\_ID_\_ for the place where 
the ID number is in the URL and \_\_SIZE\_\_ for the width in pixels. This is optional, but the developer can 
use this to create a custom function to delivery different sized of images in different contexts.
* __Popdown URL Syntax__: This is a required field with the syntax for the URL/endpoint to retrieve the information 
details about an item in the grid based on ID. It has was place holder: \_\_ID_\_ for the place where the ID
of the item goes. The developer will have to implement this endpoint to return the html for the drop down panel, which loads 
via ajax. The template for this detail pane can be loaded with the function `_shanti_grid_view_get_general_template()` 
This returns the string for the markup with the placeholders detailed below.
* __Resource Page ULR Syntax__: This is the url syntax for the item's full page using \_\_ID_\_ as a placeholder for the item's id.

#### Details Markup Template Placeholder

The HTML of the template for the details pane is a string with the following placeholders. These need to be replaced 
or hidden, or you can create your own template based on the one here and use that:

 * GVTYPE : e.g. "node", "file", "data
 * GVID : a unique numeric id, together with type this becomes the id, e.g. "node-1234"
 * GVTITLE : The title/caption of the image
 * GVAUTH : the markup for the author's name/link
 * GVWIDTH : the width of the image
 * GVHEIGHT : the height of the image
 * GVDATE : the date of the image
 * GVCOLLECTION : the name/link for the collection
 * GVPLACES : the markup for the kmaps place tags
 * GVSUBJECTS : the markup for the subjects tags
 * GVDESC : the description for this item


Dependencies
--------------------
* Ctools
* Views
* Media (recommended but not required)

Author
--------------------
Than Grove
Shanti@UVa
July 2017



