# KMaps Solr

## Basics

This is a JQuery plugin which provides an abstraction for Solr queries for KMaps.

Here are some of the things that it would do:


### Typical Usage:

##### Initalization / Setup:
```
var kmaps = $.kmapsSolr('prod');

// attach an update listener
// should I pass the kmapsSolr object whole or encapsulate the state and pass that?
kmaps.on('update', function(event, ksolr) {
    var response = ksolr.response();
    // ... update the UI according to the reponse
    updateHitList(reponse);
    
    var facetList = kmsolr.listFacets();
    updateFacets(facetList);
    
});

```
##### Execute a search
```
// allow the listeners to do all the work 
kmaps.search($('#searchfield').text());
```


```
// Or you could use chaining to process the response
var specialParams = {
    query: "id:subjects-20",
    facets: facetConfig
}

// Here, I'm doing a one-time query and not saving 
// the changed parameters in the search state.
var facets = kmaps.search( specialParams, false ).listFacets();
processFacets(facets);
```

## Usage
### Get an instance
#### Get a preconfigured kmapsolr instance
```
var kmaps = $.kmapsSolr('prod');
```
There will be a config file that contains these configurations.  The config file will look something like:

```
{
    'prod': {
        baseUrl: 'https://my.production.solr.host',
        basePath: '/path/to/solr',
        termIndex: 'kmterms',
        assetIndex: 'kmassets',
        ...
    },
    'dev': {
        baseUrl: 'https://my.development.solr.host',
        basePath '/path/to/solr',
        termIndex: 'kmterms-dev'
        ...
    }
}
```


#### Get a custom configured kmapsolr instance

```
var kmaps = $.kmapsSolr({
    baseUrl: 'http://localhost:234234',
    basePath: '/solr',
    termIndex: 'kmterms-local',
    assetIndex: 'kmassets-local'
});
```

#### Get and extend a preconfigured solr instance:
```
var kmaps = $.kmapsSolr('dev',{ 
    baseUrl: 'http://localhost:123456',
    assetIndex: 'kmassets-experimental3'
});
```

#### Search:
```
/* update according to the current search state.  Can be useful
 to update facets and to notify listeners */
kmaps.search();

/* search using these params, will update the current state
kmaps.search( 
{
    searchString: 'phlegmatic',
    domain: {
        'kmaps': false,
        'places': false,
        'subjects': false,
        'audio-video': false,
        'images': true
    },
    facets: currentFacets
});

/*  
 Do a "one-time" search

 Note: the second parameter, is false,
 meaning: do not update the stored search state
*/
kmaps.search( 
{
    searchString: 'quicksearch',
    domain: {
        'kmaps': false,
        'places': false,
        'subjects': false,
        'audio-video': false,
        'images': true
    },
    facets: { ... }
},
false);

/* A bare string is assumed to be a searchString parameter);
kmaps.search('some search string');
```

Retrieve the current search state/results:


```
/* returns the raw solr response.  Always returns an object(?). */
var rawResponse = kmaps.response();

/* returns the current search state */
var state = kmaps.getState();

/* returns json blob for the current config */
var config = kmaps.getConfig();

```






Re-initialize and/or configure an existing instance:
```

/* re-initialize with a preconfiguration */
kmaps.init('prod');

/* re-initialize with a preconfiguration and override given parameters */
kmaps.init('development', {
    baseUrl: 'https://my.development.solr.host',
    basePath '/path/to/solr',
    termIndex: 'kmterms-dev'
});

/* override the current configuration */
kmaps.configure({
   termIndex: 'kmterms-manu-9999' 
});
```