Shanti Images Module 
====================
Description
-----------------------
Shanti Images module is a comprehensive module to catalog and display images using 
a IIIF server. It provide an extensive list of metadata fields along with a number 
of content types and an image formatter that makes use of the IIIF standard's flexibility.

The module assumes that the IIIF server converts images into JPEG-2000 (.jp2) and stores those, while the original is stored on the Drupal site.

Content Types
-----------------------
The module defines three main content types and three subsidiary content types that are used to store information about the images. The three main content types are the Shanti Image, Shanti Image Series, and External Classification Scheme types. The three subsidiary content types are Agents, Image Descriptions, and External Classification. These are subsidiary in that they are fields associated with Shanti Images and Shanti Image Series. They are never created alone but always within the context of creating or editing another node, either a Shanti Image or Shanti Image Series. These content types were all created through Features and are foudn defined in the modules/custom/shanti_images/features folder. 
    
### Shanti Image Content Type
This is the main node content type that keeps track of images. All the other content types depend on this one. Its machine name is `shanti_image`. A Shanti Image can have one or more image uploaded to it. The difference between a Shanti Image with multiple images and an Image Series is an issue of metadata. In situations where the images share much or all of the metadata one should post multiple images to a single Shanti Image node. This would be the case, for instance, with scans of a text. A Shanti Image Series is used when each image has unique metadata, such as a digital exhibition of paintings. The Shanti Image content type defines a large variety of metadata fields. 

This content type also defines a IIIF field formatter in modules/custom/shanti_images/features/shanti_images_type/shanti_image_type.module file. The name of the field formatter is "Shanti Image". It displays a IIIF image according to its settings parameters, which allow the admin to choose the image format (currently restricted to only .jpg), the height, width, and rotation. The formatter can be used in either a view or a node display mode.

### Shanti Image Series
This content type describes a series of images in a specific, fixed order. This is different from a collection in which the images are not inherently ordered. The image series enforces a particular viewing order of the images. Its machine name is `shanti_image_series`. It has less metadata fields, mainly including Title, Date, Description, and Agents.

### External Classification Scheme
Shanti Images include Knowledge Map classification fields for Subjects and Places. However, we also realize the need to use classification schemes outside of the Shanti Mandala system which is built on Knowledge Maps. Its machine name is `external_classification_scheme`. The External Classification Scheme content type enables users to also tag their items (nodes) with tags from schemes external to Mandala, such as Library of Congress Subject Headings, the Getty Thesaurus of Names, etc. To do so, one must first create a record of the external classification scheme using this content type, which records the name of the scheme, an abbreviation for the scheme, urls for viewing HTML and JSON/XML/RDF versions of the records, along with attribution data. The list of schemes is then used to populate the External Scheme field associated with Shanti Images and Shant Image Series.

Settings
-----------------------
Under Configuration > Media > Shanti Image (/admin/config/media/shanti_images) there 
are three settings fields:

* **IIIF Upload URL** : This is the base URL for uploading images to (or deleting them from) the IIIF Server. The variable's name is `shanti_images_upload_url`. This url uses a CURL POST mechanism to which the file itself is put.
* **IIIF Delete URL** : The URL for deleting an image from the IIIF server. This url must contain the place holder "\_\_FILE\_\_" to indicate where the filename belongs in the URL. This is a simple GET call. Its machine name is `shanti_images_delete_url`.
* **IIIF View URL** : This is the *base* domain which is called to view the IIIF images not including the path. This is required. Its machine name is `shanti_images_view_url`.
* **IIIF View Path** : This is the optional *path* appended to the previous domain. Its machine name is `shanti_images_view_path`.

 