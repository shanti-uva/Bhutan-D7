Drupal KMaps Facet Module
=============================

A Drupal block module that provides a customizable number of blocks to navigate subject and places in relation to a specific resource type.

Developed for Shanti at UVa (http://shanti.virginia.edu) by Than Grove (ndg8f@virginia.edu)
Based on Kmaps Tree Library written by Yuji Shinozaki (ys2n@virginia.edu) and Shanti Kmaps Field module written by Raf Alvarado

This module creates a variable number of blocks. Each block displays either a place or subject tree from a customizable starting point
where each node of the tree shows the number of a specific type of resource tagged with that kmap. In the block configuration, you choose
the type (places/subjects), the root node, and the type of resource to display counts for (e.g. A/V, texts, etc.). The block then dispalys
that portion of the tree with numbers indicating the number of resources (nodes) of chosen type tagged with that kmap.

Blocks are can be placed in any region, however they were primarily intended for the Shanti Sarvaka theme Search Flyout. 
They can be displayed as individual tabs with some modification to the subtheme. To implement this 
see Mediabase's Sarvaka Mediabase theme, especially the sarvaka_mediabase_preprocess_region() function in the template.php file.

## Dependencies
The Facet Module builds on work already done in the Shanti Mandala package. It uses the 
1. The shanti_kmaps_tree library
2. The shanti_kmaps_fields module
3. The shanti_kmaps_admin module 

## Required Hook Implementation
In order for facet counts to display on tree after a Drupal keyword search is performed, sites must implement:

 hook_node_facet_hits($qstr=FALSE, $kmids=FALSE)
 
 The parameters are:
 
    qstr (string): The current keyword search string
    kmids (array): A list of currently selected kmap ids (e.g., subjects-123)
    
The function must return an associative array with the following keys:

    qids: A list of **all** node ids that are a result of the search 
    facet_data: An associative array of kmap_id => count based on that search and the already selected kmap_ids
    
To achieve this the Drupal site must index all kmap fields. To facilitate this, two functions have been added to shanti_kmaps_fields:

    1. shanti_kmaps_fields_get_all_kmap_fields(): This function returns all kmap fields
    2. shanti_kmaps_fields_get_kmaps_for_node($node = FALSE, $format='array'): This function returns all kmap tags associated with a particular node

Because individual sites use different search modules, it is up to each site to index the kmaps per node 
and return this information in the above mentioned hook.

## Required JS Data for Searches
When a search is performed on the host site, it is encumbent on that site to provide three javascript settings for the
kmaps_integrated_search module (i.e., Drupal.settings.kmaps_integrated_search) based on the kmap facet fields indexed in the sites search database. 
There are:
    
    core_search:            set to "true" to indicate a native search has been performed and facet data is provided 
    search_filter_data:   a JSON-encoded associative array of kmap_id:count pairs
    core_search_query:  a JSON-encoded array of query parameters used in the search. In particular, this must have a "q" key set
                                    to the current query string. This is used to populate the search box when a page is loaded from a URL. 
    
## Usage
This module is intended for use with Shanti sites that have resource nodes of a specific type that contain kmap fields
indexed in the SOLR kmasset index that have some nodes with kmap data. It will then display any number of kmap trees in blocks
and show the number of resources on the site tagged with each kmap. The setup assumes one has installed kmap fields
and made the appropriate settings in kmap admin to index them in the SOLR kmasset index.

### Module Settings
Once the module is installed, you will need to adjust the settings at:

     ../admin/config/user-interface/kmaps_integrated_search 
     
 or from the admin menu: 
 
    Configuration -> User Interface -> Kmaps Facet
 
 These are as follows:
 
1. **Number of Kmap Facet Blocks:** The number of kmap tree blocks you want to have
2. **Use Bootstrap Tabs for SHANTI Flyout:** If multiple blocks are in the shanti flyout, use bootstrap tab markup to display as tabs
3. **Resource Types to Count:** The type of resource you want to show counts for. Currently, you should only pick the type of resource your site natively displays, such as A/V, Text, etc. The present state of the module cannot display non-native types of resources in a site.
4. **Show resource counts next to nodes:** Whether you want to show counts next to treenodes (on by default)
5. **Hide nodes with no resources:** Hide nodes that have a count of zero.
6. **Items per page in gallery:** Number of node teaser tiles to display in gallery.

### Enable Blocks
Next go to the block admin page (/admin/structure/block) and you will see a number of Kmaps Facet blocks as defined in the settings
above. Each block will be named "Kmaps Facets 1 (Kmaps Facet)" and so on. Click the "Configure" link for that block and it will 
take you to the block's configuration page, which has the following fields:

#### Block Title
This is the header for the facet that appears on the page itself. In the search flyout it appears as the tab name.

#### Block Name
This is the administration name for the block that appears on the block admin page. No matter what you enter here, 
it will have "(Kmaps Facet)" appended to it for clarity.

#### KMap Tree Type
This allows you to choose the type of Kmap tree you wish to show in the block: subjects or places. (A TODO for the future 
would be to just get this information from the field itself.)

#### Kmap Root Node
This is the KMap ID for the root node where you want the tree to begin. In other words, if you pick subjects, you do not have 
to show the whole subject tree. By entering a KMap ID for a particular subject, you can show the tree with that subject 
as the root or top node.

Finally, choose the Region Settings as with all Drupal blocks. This module was designed for the blocks to be put in the Shanti 
Sarvaka theme's Search Flyout region without further styling, but it can be used with any theme with some styling adjustments.

Once, set up the kmap tree will display, showing counts of nodes that are tagged with each resource (if that setting is chosen).
When a node is clicked, it will display a gallery of those nodes and if counts are showing, update them.
