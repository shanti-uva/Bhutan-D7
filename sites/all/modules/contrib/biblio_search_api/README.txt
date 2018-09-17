    biblio_search_api.module

Author:  Jacob Sanford (jsanford@unb.ca)
Released under the GPL


Description:
============
This module provides functionality for exposing the fields in biblio to
search_api for indexing.

It has been tested using search_api_solr, but presumably other backend
interface modules will also support this.

Although most fields are exposed verbatim, It exposes the 'biblio_authors',
'biblio_secondary_authors', 'biblio_tertiary_authors',
'biblio_subsidiary_authors' and 'biblio_corp_authors' as comma separated author
lists.

Development of this module was supported by the University of New Brunswick
Libraries.


Requirements:
=============
biblio 7.x-1.x (https://drupal.org/project/biblio)
search_api 7.x-1.x (https://drupal.org/project/search_api)


Installation:
=============
Enable the module.


Settings:
=============
Once enabled, no configuration is needed. Any biblio fields you wish to index
can be selected from the 'admin/config/search/search_api/index/INDEX/fields'
page.
