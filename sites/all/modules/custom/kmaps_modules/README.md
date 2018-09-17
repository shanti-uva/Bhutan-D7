Drupal KMaps Modules
====================

The following modules that are required by various KMaps Modules (e.g. drupal_kmaps_navigator) can be found here.

1. ajaxsolr: A totally rad library loader for [Ajax Solr](https://github.com/evolvingweb/ajax-solr).
2. fancytree: A Drupal module that integrates the excellent Fancytree library.
3. typeahead: A Drupal module that makes Twitter's [typeahead.js](https://twitter.github.io/typeahead.js/)
available as a library.

When installing one of these modules, its corresponding library directory (found in the libraries folder) 
must be copied to sites/all/libraries.

In addition, this repository contains further modules which depend on the above modules:

4. SHANTI KMaps Tree: A wrapper for the corresponding [JQuery plugin](https://github.com/shanti-uva/shanti_kmaps_tree).
5. SHANTI KMaps Typeahead: A wrapper for the corresponding [JQuery plugin](https://github.com/shanti-uva/shanti_kmaps_typeahead).

If installing one of these modules, copy the corresponding JQuery plugin to your sites/all/libraries directory. 
When you are done, that directory will have stuff like this in it:

```
$ ls sites/all/libraries/shanti_kmaps*
sites/all/libraries/shanti_kmaps_tree:
css	fonts	html	js

sites/all/libraries/shanti_kmaps_typeahead:
README.md	css		html		js
```
