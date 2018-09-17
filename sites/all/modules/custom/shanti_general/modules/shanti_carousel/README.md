Shanti Sarvaka Carousel
====================================

This module creates a block for displaying a carousel. Usually only implemented on the front page, but any number of carousels
can be defined for the site by going to /admin/config/user-interface/shanti_carousel and entering the number of carousels you want.
On this settings page you can also determine the speed with which ALL carousels automatically revolve in seconds.

**Description And Image Fields**
If you want to use nodes from the site in the carousel, on the general module settings page you can choose which fields to
use for the description and which for the images from the two collapsible divs on that page. If none are selected, it will
search for any of the fields of that type (in the lists on that page) and use the first valid value it comes across.

Each carousel is then defined as a block and is found in the block settings "Shanti Carousel Block {n}".
Place each block in the desired region and set the pages it appears on for your theme on your site.

Each block also has specific settings:

**Block Title:** This is the standard block title for Drupal. It is not recommended you use this field.

**Carousel Block Name:** This is the adminstrative name for the block that appears on the Drupal block page. This allows you
    to give custom names to your block for easily differentiating them.
    
**Node IDs to Include in Carousel {N}:** This text area is used to determine the information for each slide, one slide per line. 
    
    The slide definitions can have any of the following 3 syntaxes:
    
    1. Solr Asset UID
    
    This is uid for any asset in the kmasset index, optionally followed by a pipe and the url to an image to use.
    If no image is supplied and there is a mms url in the record, that will be used. For example,
    
        texts-dev_shanti_virginia_edu-16230
    
    or
    
        texts-dev_shanti_virginia_edu-16202|https://texts-dev.shanti.virginia.edu/sites/texts/files/styles/large/public/gling-bu-dgon.png
    
    2. Kmap Term UID
    
    This is the uid for any term in the kmterms index, also optionally followed by an image URL For example:
    
        place-1234
    
    or
    
        subjects-5678|https://mandala.shanti.virginia.edu/sites/texts/files/styles/large/public/drepung-gomang_group2.jpg
        
    3. Node Path
    
    This is the path to a node on the current site. The node (usually a basic page) must have a regular body with the text for the slide and 
    a "field_image" field which contains the image for the slide. It can optionally have a "field_resource_link" for the another page
    to which the slide links. Otherwise, the slide will link to the node itself. A second option for linking the slide to another resource is
    to follow the node path with a pipe and the desired URL. For example:
    
        content/test-page
    
    or
    
        content/thl|http://www.thlib.org/
        
    These syntaxes for slides can be mixed and matched. A made-up example for the slide links settings is:
    
        texts-dev_shanti_virginia_edu-16230|https://texts-dev.shanti.virginia.edu/sites/texts/files/styles/large/public/drepung-gomang_group2.jpg
        places-5
        content/thl|http://www.thlib.org/
        subjects-20
        content/about
    
    
    Each resource from SOLR must have a description in their solr record for the carousel to render properly. 

**Text for Link above Carousel {N}:** If you want a link above the carousel on the right, enter the text for the link here.

**URL for Link above Carousel {N}:** If you want a link above the carousel on the right, enter the url for the link here.

**Auto start Carousel {N}:** Check this box if you want the carousel to automatically start cycling at the speed in the global settings.

**Carousel Image Style:** The module creates a default "Carousel" style that defines the optimal size for a carousel image. 
Whenever an image is added or updated, the module will create the "Carousel" derrivative in "public://styles/carousel/public/" 
There is also a general use function "get_carousel_image_url($file)" that only works for image files and returns the url for
that files carousel image, since the carousel image url removes any custom folder that the original image may be housed in.
