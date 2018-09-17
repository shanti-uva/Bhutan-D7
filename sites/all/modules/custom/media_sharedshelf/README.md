# shanti_media_sharedshelf
This is a fork of jlk4p's sandbox module (https://www.drupal.org/sandbox/jlk4p/1808830) version 7.x-2.x to work on potential updates.


### -- SUMMARY --

The Media: SharedShelf module allows editors to choose their SharedShelf images 
within the Media browser, both for fields and within WYSIWYG.

To use it, enable the Media module. You'll also need to have a SharedShelf
account at http://catalog.sharedshelf.artstor.org/login.html.

After that, editors will be able to enter a SharedShelf image ID or full size
image URL. Or an editor may prefer to select a project (and/or image sets within 
it), as well as search project image metadata to choose images to add as media 
items.


### -- REQUIREMENTS --

Apache Solr File module available at http://drupal.org/project/apachesolr_file.
Entity module available at http://drupal.org/project/entity.
Media module available at http://drupal.org/project/media.
Views module available at http://drupal.org/project/views.


### -- INSTALLATION --

Install this module as you would any other Drupal module. This module functions
with the basic Solr configuration installation of the Apache Solr module files 
and has been tested using Solr 3.x.

Make sure the Image structure is configured to display SharedShelf
images. (See the last step documented under the Configuration notes.)

Make sure that you configure Apache Solr and Apaceh Solr File correctly. You 
must use the appropriate Solr config files from the apachesolr/solr-conf/solr-x
folder. In addition, per the Apache Solr File module, make sure you modify the 
solrconfig.xml file such that <lib dir="../../dist/" /> is added to it and the 
other necessary lines are located there. Then restart Solr and delete the 
Solr index from the Drupal admin panel before using this module.


### -- CONFIGURATION --

* Set the SharedShelf user authentication information in 
  Administration >> Configuration >> Media >> SharedShelf API Settings:

  - Select with which SharedShelf server to connect. You may want to use their
    demo server if just evaluating the module. Enter credentials which may be
    used to log into the SharedShelf site.

* Customize form default settings and dynamic content display settings in 
  Administration >> Configuration >> Media >> SharedShelf Media Settings:

  - When accessing the add media form, you can specify a default project to use.

  - You may define the number of images per page for search results and the 
    desired image size to be cached locally.

* Include SharedShelf basic image metadata in Solr indexing:
  Administration >> Configuration >> Search and metadata >> Apache solr search

  - Make sure the image type is selected below the File option at the bottom 
    of the settings.

* Enable the file display for SharedShelf images:
 Administration >> Structure >> File types >> Image

  - Choose the Manage File Display tab and repeat the steps below for each 
    display type: default, teaser, and preview.
  - Enable the display of SharedShelf images by checking the SharedShelf 
    Preview Image option.
  - Adjust the SharedShelf Preview Image display settings by choosing the
    preferred image style for the display type (default, teaser, etc.).
  - Save the configuration changes. 

### -- TROUBLESHOOTING IMAGE DISPLAY ISSUES --

The Media module provides for displaying different file/media types. But you
must indicate how these different file types get displayed. If thumbnail images 
are not appearing, make sure you have enabled the display of SharedShelf Preview
images by going through the last step in the configuration section above.

### -- TROUBLESHOOTING IMAGE EMBED DISPLAY ISSUES --

When using the WYSIWYG embed option to add an image to an article or page, you
may find that the image and metadata fields do not display. If you use Filtered
or Full HTML text formats you MUST make sure that no text fields include an
email address or URL in them as these types of information are transformed into
HTML links. This creation of HTML links will break the JSON data format used
in the WYSIWYG view and prevent the content from displaying.

### -- TROUBLESHOOTING SOLR MEMORY ISSUES --

If you find that Apache Solr File is having memory errors when indexing content,
you may want to reduce the number of items per cron job based on the local cache
image size specified in this module. For example, for image size of 256(px) 
using 10 items per cron job seems to run without causing memory errors.

### -- CONTACT --

Current maintainer:
* Jack Kelly (jlk4p) - http://drupal.org/user/1878962


Sponsored by the University of Virginia Library. The University of Virginia 
hereby disclaims all copyright interest in the 'Media: SharedShelf' Drupal 
module written by Jack Kelly.

October 2012
Rector and Visitors of the University of Virginia

