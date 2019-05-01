/*! Shanti Kmaps Solr - v0.1.0 - 2019-04-29
* Copyright (c) 2019 ys2n; Licensed MIT */
/*! Shanti Kmaps Solr - v0.1.0 - 2018-07-24
* Copyright (c) 2018 ys2n; Licensed MIT */
;(function ($, window, document, undefined) {
  'use strict';
  var DEBUG = false;
  var TEXT_SEARCH_FIELD = 'text';
  var JOINQ_LOGIC = "OR";

  // ys2n:  how do we combine the kmap selection and other searches?
  // are we using filtering (AND) or are we adding to the result set (OR)
  // hmmmm.   Constant for now, but should it vary?  Under what circumstances?
  // var FILTERLOGIC = "OR";  // NOT IN USE CURRENTLY

  // key for storing the state in local storage
  var stateStoreKey = "inpage_search_state_store";

  // These are the named configs.
  // TODO: ys2n: refactor this into a separate config file.
  var presetConfigs = {
    'prod': {
      'preset': 'prod',
      'solrBase': 'ss395824-us-east-1-aws.measuredsearch.com',
      'solrPath': '/solr/',
      'assetIndex': 'kmassets',
      'termIndex': 'kmterms_prod'
    },
    'dev': {
      'preset': 'dev',
      'solrBase': 'ss251856-us-east-1-aws.measuredsearch.com',
      'solrPath': '/solr/',
      'assetIndex': 'kmassets_dev',
      'termIndex': 'kmterms_dev'
    },
    'predev': {
      'preset': 'predev',
      'solrBase': 'ss251856-us-east-1-aws.measuredsearch.com',
      'solrPath': '/solr/',
      'assetIndex': 'kmassets_predev',
      'termIndex': 'kmterms_predev'
    },
    'test': {
      'preset': 'test',
      'solrBase': 'ss251856-us-east-1-aws.measuredsearch.com',
      'solrPath': '/solr/',
      'assetIndex': 'kmassets_test',
      'termIndex': 'kmterms_test'
    },
    'stage': {
      'preset': 'stage',
      'solrBase': 'ss395824-us-east-1-aws.measuredsearch.com',
      'solrPath': '/solr/',
      'assetIndex': 'kmassets_stage',
      'termIndex': 'kmterms_stage'
    }
  };

  // TODO: ys2n: chosenFacets was never used.  Remove this.
  var defaultState = {
    chosenFacets: [],
    page: 0
  };

  // utility function to neaten display of objects
  var objector = function (key, value) {
    if ($.type(value) === "object" && $.type(value.value) === "string") {
      return "[" + value.count + ": " + value.id + " ]";
    }

    if (key === "docs") {
      return "[ ... " + value.length + " docs  ... ]";
    }
    return value;
  };

  // Constructor for KMapsSolr
  function KMapsSolr(config, options) {

    // State will vary depending on the search requests
    this.state = defaultState;

    // Initialize ourselves
    this.init(config, options);

  }

  KMapsSolr.prototype = {
    processConfig: function (config, options) {
      var kmapsSolrConfig = {
        pageSize: 100
      };
      var arg_type = $.type(config);
      if (arg_type === "string") {
        if ($.isPlainObject(presetConfigs[config])) {
          kmapsSolrConfig = $.extend({}, kmapsSolrConfig, presetConfigs[config]);
        } else {
          //  perhaps give list of possible presets here
          throw new Error("Unknown preset: " + config);
        }
      } else if (arg_type === "object") {
        kmapsSolrConfig = $.extend({}, kmapsSolrConfig, config);
      }
      if ($.isPlainObject(options)) {
        kmapsSolrConfig = $.extend({}, kmapsSolrConfig, options);
      }
      // console.log("processConfig returning: " + JSON.stringify(kmapsSolrConfig));
      return kmapsSolrConfig;
    },


    // Returns an array of FacetConfigs used to apply and render facet configs to the current solr search.

    assembleFacetConfigs: function () {

      // Facet Configs
      // The interface for each FacetConfig is the following:
      //
      // Fields:
      //
      //  name:  unique config name
      //
      //  title: A Human Readable label to present to the user when browsing/choosing the available facets.
      //
      //  handlebarsTemplate: a string handlebarsTemplate for rendering the facet interface.
      //
      // Functions:
      //
      //  applies():  a function which is passed a search_params object and returns a boolean stating whether this FacetConfig should be applied.
      //
      //  getSolrFacetJSONString(): a function which returns the appropriate SOLR Json Facet blob suitable for a query.
      //
      //  transform(): a function which transforms a JSON blob from a format returned by SOLR, to a another more convenient format.
      //
      //

      // TODO: ys2n: refactor this so that these can be loaded from separate files.  Right now its just an array of hardcoded blobs
      var facetConfig = [

        // {
        //   name: "asset_type",
        //   title: "Type",
        //   applies: function (search_params) {
        //
        //     // always apply this facetConfig
        //     return true;
        //   },
        //   getSolrFacetJSONString: function () {
        //     return undefined;  // return this as a JSON string blob
        //   },
        //   transform: function (entry) {
        //     var type = entry.val;
        //     var name = entry.val;
        //     var count = entry.count;
        //     var fq = "asset_type:" + entry.val;
        //
        //     var facetentry = {
        //       id: "type-" + type,
        //       type: "Type",
        //       label: name,
        //       full_label: true,
        //       value: type,
        //       count: count,
        //       filterQuery: fq,
        //     };
        //     return facetentry;          },
        //   handlebarsTemplate: ""
        // },


        {
          name: "assetType",
          title: "Asset Type",
          applies: function (search_params) {
            // always apply this facetConfig
            return false;
          },
          getSolrFacetJSONString: function () {
            // I'm constructing this as an object then serializing via JSON.stringify
            var json = {
              assetType: {
                limit: 300,
                type: "terms",
                field: "asset_type",
                facet: {
                  subtype: {
                    limit: 1,
                    type: "terms",
                    field: "asset_subtype"
                  }
                }
                // domain: {blockChildren: "block_type:parent"}
              }
            };
            return JSON.stringify(json);  // return this as a JSON string blob
          },
          transform: function (entry) {

            var value = entry.val;
            var name = value;
            var count = entry.count;
            var fq = "asset_type:\"" + value + "\"";
            var evalue = value.replace(/\s+/g,"_");
            var subtype = (entry.subtype && entry.subtype.buckets && entry.subtype.buckets.length > 0)?entry.subtype.buckets[0].val:"";
            var subtype_label = (subtype.length > 0)?": " + subtype:"";

            var facetentry = {
              id: "asset_type-" + evalue,
              type: "Asset Type",
              label: name + subtype_label,
              full_label: true,
              value: value,
              count: count,
              filterQuery: fq
            };
            // console.log("FACETENTRY id = " + facetentry.id + " evalue = " + evalue);
            return facetentry;
          },
          handlebarsTemplate: ""
        },



        {
          name: "places",
          title: "Related Places",
          applies: function (search_params) {
            // always apply this facetConfig
            return true;
          },
          getSolrFacetJSONString: function () {
            // I'm constructing this as an object then serializing via JSON.stringify
            var json = {
              places: {
                limit: 300,
                type: "terms",
                field: "kmapid",
                prefix: "places",
                // domain: {blockChildren: "block_type:parent"}
              }
            };
            return JSON.stringify(json);  // return this as a JSON string blob
          },
          transform: function (entry) {

            var full_label = false;
            var kcache = Drupal.settings.kmapsSolr.state.kmapsLabelCache;

            var display_name = entry.val;
            if (kcache) {
              var x = kcache[entry.val];
              if (x) {
                display_name = x;
                full_label = true;
              }
            }
            var value = entry.val;
            var name = display_name;
            var count = entry.count;
            var fq = "kmapid:\"" + value + "\"";
            var evalue = value.replace(/\s+/g,"_");

            var facetentry = {
              id: evalue,
              type: "Related Subjects",
              label: name,
              full_label: full_label,
              value: value,
              count: count,
              filterQuery: fq
            };
            // console.log("FACETENTRY id = " + facetentry.id + " evalue = " + evalue);
            return facetentry;
          },
          handlebarsTemplate: ""
        },


        {
          name: "subjects",
          title: "Related Subjects",
          applies: function (search_params) {
            // always apply this facetConfig
            return true;
          },
          getSolrFacetJSONString: function () {
            // I'm constructing this as an object then serializing via JSON.stringify
            var json = {
              subjects: {
                limit: 300,
                type: "terms",
                field: "kmapid",
                prefix: "subjects",
                // domain: {blockChildren: "block_type:parent"}
              }
            };
            return JSON.stringify(json);  // return this as a JSON string blob
          },
          transform: function (entry) {

            var full_label = false;
            var kcache = Drupal.settings.kmapsSolr.state.kmapsLabelCache

            var display_name = entry.val;
            if (kcache) {
              var x = kcache[entry.val];
              if (x) {
                display_name = x;
                full_label = true;
              }
            }
            var value = entry.val;
            var name = display_name;
            var count = entry.count;
            var fq = "kmapid:\"" + value + "\"";
            var evalue = value.replace(/\s+/g,"_");

            var facetentry = {
              id: evalue,
              type: "Related Subjects",
              label: name,
              full_label: full_label,
              value: value,
              count: count,
              filterQuery: fq
            };
            // console.log("FACETENTRY id = " + facetentry.id + " evalue = " + evalue);
            return facetentry;
          },
          handlebarsTemplate: ""
        },


        {
          name: "collection_title",
          title: "Collection",
          applies: function (search_params) {
            // always apply this facetConfig
            return true;
          },
          getSolrFacetJSONString: function () {
            // I'm constructing this as an object then serializing via JSON.stringify
            var json = {
              collection_title: {
                limit: 300,
                type: "terms",
                field: "collection_title"
                // domain: {blockChildren: "block_type:parent"}
              }
            };
            return JSON.stringify(json);  // return this as a JSON string blob
          },
          transform: function (entry) {

            var value = entry.val;
            var name = value;
            var count = entry.count;
            var fq = "collection_title:\"" + value + "\"";
            var evalue = value.replace(/\s+/g,"_");

            var facetentry = {
              id: "collection_title-" + evalue,
              type: "Collection",
              label: name,
              full_label: true,
              value: value,
              count: count,
              filterQuery: fq
            };
            // console.log("FACETENTRY id = " + facetentry.id + " evalue = " + evalue);
            return facetentry;
          },
          handlebarsTemplate: ""
        },


        {
          name: "asset_subtype",
          title: "Asset Type",
          applies: function (search_params) {
            // always apply this facetConfig
            return true;
          },
          getSolrFacetJSONString: function () {
            // I'm constructing this as an object then serializing via JSON.stringify
            var json = {
              asset_subtype: {
                limit: 300,
                type: "terms",
                field: "asset_subtype",
                facet: {
                  parent_type: {
                    limit: 1,
                    type: "terms",
                    field: "asset_type"
                  }
                }
                // domain: {blockChildren: "block_type:parent"}
              }
            };
            return JSON.stringify(json);  // return this as a JSON string blob
          },
          transform: function (entry) {

            var value = entry.val;
            var name = value;
            var count = entry.count;
            var fq = "asset_subtype:\"" + value + "\"";
            var evalue = value.replace(/\s+/g,"_");
            var parent_type = entry.parent_type.buckets[0].val

            var facetentry = {
              id: "asset_subtype-" + evalue,
              type: "Asset Subtype",
              label: parent_type + ": " + name,
              full_label: true,
              value: value,
              count: count,
              filterQuery: fq
            };
            // console.log("FACETENTRY id = " + facetentry.id + " evalue = " + evalue);
            return facetentry;
          },
          handlebarsTemplate: ""
        },

        {
          name: "feature_types_ss",
          title: "Feature Types",
          applies: function (search_params) {
            // always apply this facetConfig
            return true;
          },
          getSolrFacetJSONString: function () {
            // I'm constructing this as an object then serializing via JSON.stringify
            var json = {
              feature_types_ss: {
                limit: 300,
                type: "terms",
                field: "feature_types_ss"
                // domain: {blockChildren: "block_type:parent"}
              }
            };
            return JSON.stringify(json);  // return this as a JSON string blob
          },
          transform: function (entry) {

            var kmapid = entry.val;
            var name = kmapid;
            var count = entry.count;
            var fq = "feature_types_ss:\"" + kmapid + "\"";

            var facetentry = {
              id: "feature_types-" + kmapid,
              type: "Feature Type",
              label: name,
              full_label: true,
              value: kmapid,
              count: count,
              filterQuery: fq
            };
            // console.log("FACETENTRY id = " + facetentry.id);
            return facetentry;
          },
          handlebarsTemplate: ""
        },

        {
          name: "node_user",
          title: "Uploading User",
          applies: function (search_params) {
            // always apply this facetConfig

            // DISABLED
            return true;
          },
          getSolrFacetJSONString: function () {
            // I'm constructing this as an object then serializing via JSON.stringify
            var json = {
              node_user: {
                limit: 300,
                type: "terms",
                field: "user_name_full_s"
                // domain: {blockChildren: "block_type:parent"}
              }
            };
            return JSON.stringify(json);  // return this as a JSON string blob
          },
          transform: function (entry) {

            var value = entry.val;
            var name = value;
            var count = entry.count;
            var fq = "user_name_full_s:\"" + value + "\"";
            var evalue = value.replace(/\s+/g,"_");

            var facetentry = {
              id: "node_user-" + evalue,
              type: "Uploading User",
              label: name,
              full_label: true,
              value: value,
              count: count,
              filterQuery: fq
            };
            // console.log("FACETENTRY id = " + facetentry.id + " evalue = " + evalue);
            return facetentry;
          },
          handlebarsTemplate: ""
        },

        {
          name: "node_lang",
          title: "Asset Language",
          applies: function (search_params) {
            // always apply this facetConfig
            return true;
          },
          getSolrFacetJSONString: function () {
            // I'm constructing this as an object then serializing via JSON.stringify
            var json = {
              node_lang: {
                limit: 300,
                type: "terms",
                field: "node_lang"
                // domain: {blockChildren: "block_type:parent"}
              }
            };
            return JSON.stringify(json);  // return this as a JSON string blob
          },
          transform: function (entry) {

            var value = entry.val;
            var name = value;
            var count = entry.count;
            var fq = "node_lang:\"" + value + "\"";
            var evalue = value.replace(/\s+/g,"_");

            if (name === "") {
              name = "(unknown)";
            } else if (name === "und") {
              name = "(undefined)";
            }

            var facetentry = {
              id: "node_lang-" + evalue,
              type: "Asset Language",
              label: name,
              full_label: true,
              value: value,
              count: count,
              filterQuery: fq
            };
            // console.log("FACETENTRY id = " + facetentry.id + " evalue = " + evalue);
            return facetentry;
          },
          handlebarsTemplate: ""
        },

        /*
                {
                  name: "related_subjects",
                  title: "Related Subjects",
                  applies: function (search_params) {
                    return true;
                  },

                  getSolrFacetJSONString: function () {
                    var json = {
                      related_subjects: {
                        type: "terms",
                        // TODO: ys2n: THIS SHOULD BE CONFIGURABLE!
                        limit: 300,
                        prefix: "subjects-",
                        field: "related_subjects_id_s",
                        facet: {
                          related_subjects_header_s: {
                            field: "related_subjects_header_s"
                          }
                        },
                        domain: {blockChildren: "block_type:parent"}
                      }
                    };
                    return JSON.stringify(json);
                  },

                  transform: function (entry) {
                    if (DEBUG) console.log("transforming: " + JSON.stringify(entry));
                    var kmapid = entry.val;
                    var name = entry.related_subjects_header_s.buckets[0].val;
                    var count = entry.count;
                    var fq = "{!parent which='block_type:parent'}related_subjects_id_s:" + kmapid;
                    var facetentry = {
                      id: "related_subjects-" + kmapid,
                      type: "Related Subject",
                      label: name,
                      full_label: true,
                      value: kmapid,
                      count: count,
                      filterQuery: fq
                    };
                    // console.log("FACETENTRY id = " + facetentry.id + " evalue = " + evalue);
                    return facetentry;
                  },

                  handlebarsTemplate: ""
                },

                {
                  name: "related_places",

                  title: "Related Places",

                  applies: function (search_params) {
                    return true;
                  },

                  getSolrFacetJSONString: function () {
                    var json = {
                      related_places: {
                        type: "terms",
                        // TODO: ys2n: THIS SHOULD BE CONFIGURABLE!
                        limit: 300,
                        prefix: "places-",
                        field: "related_places_id_s",
                        facet: {
                          related_places_header_s: {
                            field: "related_places_header_s"
                          }
                        },
                        domain: {blockChildren: "block_type:parent"}
                      }
                    };
                    return JSON.stringify(json);
                  },

                  transform: function (entry) {
                    // console.log("transforming: " + JSON.stringify(entry));
                    var kmapid = entry.val;

                    // default this value to the kmapid if the related_places_header_s is empty...
                    var name_value = (entry.related_places_header_s.buckets.length !==0 )? entry.related_places_header_s.buckets[0].val : kmapid;
                    var name = name_value;
                    var count = entry.count;
                    var fq = "{!parent which='block_type:parent'}related_places_id_s:" + kmapid;

                    var facetentry = {
                      id: "related_places-" + kmapid,
                      type: "Related Place",
                      label: name,
                      full_label: true,
                      value: kmapid,
                      count: count,
                      filterQuery: fq
                    };
                    // console.log("FACETENTRY id = " + facetentry.id + " evalue = " + evalue);
                    return facetentry;
                  },

                  handlebarsTemplate: ""
                }
                */

      ];
      return facetConfig;
    },

    init: function (config, options) {

      var self = this;

      // Load session storage if available
      if (sessionStorage.getItem(stateStoreKey) !== null) {
        try {
          this.state = JSON.parse(sessionStorage.getItem(stateStoreKey));
        } catch (err) {
          console.log("Error restoring in-page search state. (" + err + ").  Discarding.");
          sessionStorage.setItem(stateStoreKey, JSON.stringify(defaultState));
        }
      }


      // else {
        // Look for defaultFilterState option
        if (options && typeof options.defaultFilterState !== "undefined") {
          if (typeof this.state === "undefined") {
            this.state = {
              kmapsLabelCache: {}
            };
          }
          try {
            this.state.filters = options.defaultFilterState;
            if (options.loadedFromURL) {
              // if loaded from URL then assume the state should be considered "not changed".
              console.log("state loaded from URL: assumed not changed");
              this.state.lastStateJSON = JSON.stringify(options.defaultFilterState);
            }
          } catch (err) {
            console.error("Error restoring filterState. (" + err + "). Ignoring. ");
            console.log("options.defaultFilterState: " + JSON.stringify(options.defaultFilterState));
          }
        }
      // }

      this.settings = this.processConfig(config, options);
      this.settings.facetConfigList = this.assembleFacetConfigs();

      // execute a default query and then any afterInit() functions
      // This is primarily to get a default set of facets
      // Uses JQuery promise.
      this.search().then(
        // pre-fetch then run afterInit();
        function () {
          if (self.settings.afterInit !== null && $.type(self.settings.afterInit) === "function") {
            self.settings.afterInit(self);
          }
        }
      );
    },

    search: function (arg, _persist) {

      if (DEBUG) console.error("SEARCH with arg: " + JSON.stringify(arg));

      var deferred = $.Deferred();

      // default to true
      if ($.type(_persist) === 'undefined') {
        _persist = true;
      }

      // dispatch function

      if (DEBUG) {
        console.log("SEARCH CALLED WITH " + JSON.stringify(arg));
        // console.error("THE STATE = " + JSON.stringify(this.state));
        // console.error("THE SETTINGS = " + JSON.stringify(this.settings));
      }

      var self = this;
      var error = false;

      // process arguments and state
      var current = $.extend({}, this.state, this.processSearchArguments(arg));

      if ($.type(this.settings.beforeSearch) === 'function') {
        this.settings.beforeSearch(current);
      }

      try {
        // self.executeKMapSearch(current, self.settings, function (error, result) {
        //
        //   $.extend(self.state, result);
        //   // self.update();
        //
        //   if (error) {
        //     console.error("There was an error during the executeKMapSearch callback.");
        //     console.dir(error);
        //   }
        //
        //
        //
        // });

        // Do another search, this time, an asset search, based on the kmaps search result or...?
        self.executeAssetSearch(current, self.settings, function(error, asset_result) {

          if (error) {
            console.error("There was an error during the executeAssetSearch callback.");
            console.dir(error);
            console.dir({ state: self.state });
            console.error("rejecting promise...");

            console.dir(deferred);
            console.log("deferred state: " + deferred.state());

            deferred.reject(self);
          }

          if (_persist && !error) {
            $.extend(self.state, asset_result);

            if (DEBUG) {
              console.log("HERE ARE THE ASSET RESULTS");
              console.dir(asset_result);
            }
            self.update();
            deferred.resolve(self);
            sessionStorage.setItem(stateStoreKey, JSON.stringify(self.state));
            // TODO: ys2n: if there is any url state-storing to be done it could be done here.

            if (self.settings.afterSearch !== null && $.type(self.settings.afterSearch) === "function") {
              if (DEBUG) console.error("Calling AfterSearch");
              self.settings.afterSearch(self.state);
              // if (DEBUG) console.error("AFTERSEARCH!");
            }
          }
        });

      } catch (err) {
        console.error("ERROR:" + err);
        deferred.reject(self);
        if (self.settings.afterError !== null && $.type(self.settings.afterError) === "function") {
          console.error("Calling AfterError");
          self.settings.afterError(self.state);
          // if (DEBUG) console.error("AFTERSEARCH!");
        }
      }

      return deferred.promise();
    },

    removeFacet: function (facetspec) {
      if (DEBUG) console.error("removeFacet: " + JSON.stringify(facetspec));
      var facet = null;
      var arg_type = $.type(facetspec);
      if (arg_type === "string") {
        facet = this.state.facetHash[facetspec];
      } else {
        facet = facetspec;
      }

      if ($.type(facet) !== "object") {
         delete this.state.filters[facetspec];
      } else {
        delete this.state.filters[facet.id];
      }
      return this.search();
    },


    selectFacet: function (facet) {

      var arg_type = $.type(facet);

      if (arg_type === "string") {
        facet = this.state.facetHash[facet];
      } else if (arg_type !== "object") {
        throw new Error("selectFacet: Unknown argument type " + arg_type + " or unknown facet name " + facet);
      }
      return this.search({"chooseFacets": [facet]}, true);

    },

    selectKmapId: function (kmapid) {
      return this.search({"chooseKmaps": [kmapid]});
    },

    showAssetTypes: function(asset_types) {
      if ($.isArray(asset_types)) {

        // if ($.inArray("images", asset_types) > -1) { asset_types.push("picture"); }
        // if ($.inArray("texts", asset_types) > -1){ asset_types.push("document"); }
        // if ($.inArray("audio-video", asset_types) > -1 ) { asset_types.push("video"); }
        // if ($.inArray("sources", asset_types) > -1 ) { asset_types.push("onlineresource"); }
        if ($.inArray("all", asset_types) > -1 || asset_types.length === 0 ) { asset_types = [ "all","subjects","terms","places","images","audio-video","texts","sources","visuals" ]; }
        asset_types = asset_types.join(" ");

      }

      return this.search({"showAssetTypes":asset_types});
    },

    selectSort: function(field,direction) {
      return this.search({"chooseSort": [field,direction]});
    },

    removeKmapId: function (kmapid) {
      if (!$.isEmptyObject(this.state.filters.kmaps) && $.type(this.state.filters.kmaps[kmapid]) === "string") {
        delete this.state.filters.kmaps[kmapid];
      } else {
        console.error("tried to delete non-existent " + kmapid);
      }

      // eliminate empty kmaps node
      if ($.isEmptyObject(this.state.filters.kmaps)) {
        delete this.state.filters.kmaps;
      }
      return this.search();
    },

    processSearchArguments: function (arg) {

      // our current search params
      var current_search = {};

      // examine first argument
      var arg_type = $.type(arg);

      if (arg_type === 'string') {
        // if this is a 'plain text' search, use all the current state
        $.extend(current_search, this.state, {searchString: arg});  // We aren't modifying state (yet)
      } else if (arg_type === 'object') {
        // if this is a configured search, extend the current state
        $.extend(current_search, this.state, arg);  // merge the search params
      } else {
        // console.log("FELL THROUGH!!")
      }

      return current_search;
    },

    // executeKMapSearch: function (searchparams, settings, kmsearch_cb) {
    //
    //   // TODO: ys2n: refactor this to simplify logic.
    //   // TODO: ys2n: e.g. "flatten" the _filters_ object, so that the add/remove mechanics are simpler and more predictable.
    //
    //   var self = this;
    //   var titles = {};
    //   var transformers = {};
    //   var merged = {};
    //
    //   var x_start = searchparams.start || 0;
    //   var pageSize = settings.pageSize;
    //
    //   $.each(settings.facetConfigList, function (x, y) {
    //     var facet = JSON.parse(y.getSolrFacetJSONString());
    //     if (y.applies(searchparams)) {
    //       $.extend(true, merged, facet);
    //     }
    //     if ($.type(y.transform) === 'function') {
    //       transformers[y.name] = y.transform;
    //       titles[y.name] = y.title;
    //     }
    //   });
    //
    //   // serialize to JSON
    //   var facetJSON = JSON.stringify(merged);
    //
    //   // add fq's
    //   var fqhash = {};  // hash of filter queries (fq)
    //
    //   if ($.type(self.state.filters) === "object") {
    //     // use the stored ones
    //     fqhash = self.state.filters;
    //   }
    //
    //   // asset type list preprocessing so that the UI is updated in time.
    //   var assetTypeList;
    //   if ($.type(self.state.filters) === "object") {
    //     // use the stored ones
    //     fqhash = self.state.filters;
    //     assetTypeList = (self.state.assetTypeList)?self.state.assetTypeList:[];
    //   }
    //
    //   var showAssetTypes = searchparams.showAssetTypes;
    //
    //   if (true) { console.log(" showAssetTypes = " + JSON.stringify(showAssetTypes)); }
    //
    //   if ($.isArray(showAssetTypes)) {
    //     assetTypeList = showAssetTypes;
    //   } else if ( typeof showAssetTypes === "string" && showAssetTypes.length > 0 ) {
    //     assetTypeList = showAssetTypes.split(/\s+/);
    //   } else if ( showAssetTypes === "" ) {
    //     assetTypeList = [ "all","places", "subjects", "audio-video", "images", "sources", "texts", "visuals" ];
    //   }
    //
    //   if (assetTypeList !== null) {
    //     self.state.assetTypeList = assetTypeList;
    //     if (DEBUG) console.log("setting state.assetTypeList : " + JSON.stringify(assetTypeList) );
    //   }
    //
    //   if (!assetTypeList || assetTypeList === null || assetTypeList.length === 0 ) {
    //     assetTypeList = [ "all","places", "subjects", "audio-video", "images", "sources", "texts", "visuals" ];
    //   }
    //   if (true)  { console.error("assetTypeList = " + JSON.stringify(assetTypeList)); }
    //
    //   // get the current search string and override any
    //   if ($.type(searchparams.searchString) === "string") {
    //     if (searchparams.searchString.length === 0) {
    //       if (fqhash.searchString) {
    //         delete fqhash.searchString;
    //       }
    //     } else {
    //       fqhash.searchString = TEXT_SEARCH_FIELD + ":" + searchparams["searchString"];
    //     }
    //   }
    //
    //   // make sure chooseFacets is an array
    //   var chooseFacets = searchparams["chooseFacets"];
    //   if (chooseFacets === null || $.type(chooseFacets) === "undefined") {
    //     searchparams.chooseFacets = [];
    //   } else if ($.type(chooseFacets) !== "array") {
    //     searchparams.chooseFacets = [chooseFacets];
    //   }
    //
    //   $.each(searchparams.chooseFacets, function (x, y) {
    //     fqhash[y.id] = y.filterQuery;
    //   });
    //
    //   var chooseKmaps = searchparams.chooseKmaps;
    //   if (chooseKmaps === null || $.type(chooseKmaps) === "undefined") {
    //     searchparams.chooseKmaps = [];
    //   } else if ($.type(chooseKmaps) !== "array") {
    //     searchparams.chooseKmaps = [chooseKmaps];
    //   }
    //   $.each(searchparams.chooseKmaps, function (x, y) {
    //     if (!fqhash.kmaps) {
    //       fqhash.kmaps = {};
    //     }
    //
    //     // delete if this kmap pre-exists
    //     if (fqhash["kmaps"][y]) {
    //       delete fqhash["kmaps"][y];
    //     }
    //
    //     // add the kmap clause.   Note that if we do not want the children to match we would use uid instead of ancestor_uids_generic.
    //     fqhash.kmaps[y] = "ancestor_uids_generic:" + y;
    //
    //   });
    //
    //   // we use "OR" logic with kmaps queries. (expanding the hits depending on which kmaps were selected).
    //   var fqlist = $.map(fqhash, function (v, k) {
    //     if ($.isPlainObject(v)) {
    //       var kmaplist = $.map(v, function (kid) {
    //         return kid;
    //       });
    //       if (kmaplist.length !== 0) {
    //         v = "{!tag=kmaps}(" + kmaplist.join(" OR ") + ")";
    //       }
    //     }
    //     return v;
    //   });
    //
    //
    //   // figure out sort specification
    //   function calculateSort(state, params) {
    //
    //     // console.log("calculateSort");
    //     //
    //     // console.log("STATE:");
    //     // console.dir(state);
    //     // console.log("PARAMS:");
    //     // console.dir(params);
    //
    //     var sspecs = [];
    //
    //     sspecs.push("asset_type ASC");
    //     sspecs.push("uid ASC");
    //
    //     var sortspec = sspecs.join(',');
    //
    //     return sortspec;
    //   }
    //
    //   var sortspec = calculateSort(self.state,searchparams);
    //
    //   // okay let's execute the query
    //
    //   if (DEBUG) {
    //     // useful debugging
    //     $('.search-results-facets').html("<pre>DEBUG</pre><pre>" + JSON.stringify({
    //       fqlist: fqlist
    //     }, undefined, 3) + "</pre>");
    //   }
    //
    //   var cf = self.getConfig();
    //
    //   // verify configuration is set.
    //   if (!cf.solrBase) {
    //     throw new Error ("solrBase is not set!");
    //   } else if (!cf.solrPath){
    //     throw new Error ("solrPath is not set!");
    //   } else if (!cf.termIndex) {
    //     throw new Error("solrPath is not set!");
    //   }
    //
    //   var requestUrl = "https://" + cf.solrBase + cf.solrPath + cf.assetIndex + "/select";
    //   // console.log("requestUrl = " + requestUrl);
    //
    //   // console.error("PAGESIZE = " + pageSize);
    //
    //   var fqlist_full = fqlist.slice(); // clone the array
    //
    //   // Add configure fq's to fqlist.
    //
    //   fqlist_full.push("-asset_type:(terms picture document video)");
    //   if(cf.kmapFilterQuery && cf.kmapFilterQuery.length > 0) {
    //     for (var i = 0; i < cf.kmapFilterQuery.length; i++) {
    //       if (DEBUG) { console.log("pushing \"" + cf.kmapFilterQuery[i] + "\" onto fqlist..."); }
    //       fqlist_full.push(cf.kmapFilterQuery[i]);
    //     }
    //   }
    //   // fqlist_full.push ("+(ancestor_uids_generic:places-2 tree:subjects)")
    //
    //   if (true) {
    //     console.log("kmap fqlist:");
    //     console.dir(fqlist_full);
    //   }
    //
    //   var requestParams = {
    //     q: "asset_type:*",
    //     fl: '*',
    //     fq:  fqlist_full,
    //     facet: true,
    //     'json.facet': facetJSON,
    //     start: x_start,
    //     rows: pageSize,
    //     sort: sortspec,
    //     wt:'json',
    //     echoParams: 'explicit'
    //   };
    //
    //   console.error("AJAXING");
    //   console.log("FQ: " + JSON.stringify(requestParams.fq),undefined,2);
    //   console.log("JSON.FACET: " + JSON.stringify(requestParams['json.facet']),undefined,2);
    //
    //   try {
    //     $.ajaxSettings.traditional = true;
    //     $.ajax({
    //       type: "GET",
    //       cache: true,
    //       url: requestUrl,
    //       data: requestParams,
    //       dataType: "jsonp",
    //       jsonp: 'json.wrf',
    //       timeout: 30000,
    //
    //       error: function (x,e) {
    //         console.error("ERRORING: " + JSON.stringify(arguments));
    //         console.log(e);
    //         kmsearch_cb(e);
    //       },
    //       beforeSend: function () {
    //       },
    //       success: function (response) {
    //
    //         // see the raw solr reponse
    //         if (DEBUG) { console.error("THE RESPONSE: " + JSON.stringify(response, undefined, 3)) };
    //
    //         // process the results
    //

    //         if (DEBUG) {
    //           console.dir(current_blob);
    //         }
    //         kmsearch_cb(null,current_blob);
    //
    //       },
    //       complete: function () {
    //         if (DEBUG) {
    //           console.log("COMPLETE");
    //         }
    //       }
    //     });
    //   } catch (err) {
    //     console.error(err);
    //   }
    // },

    executeAssetSearch: function (searchparams, settings,  asset_search_cb) {

      var self = this;
      var titles = {};
      var transformers = {};
      var assetQlist = [];
      var assetTypeList = null;

      var x_start = searchparams.start || 0;
      var pageSize = settings.pageSize;
      var overFetch = (settings.overFetch)?settings.overFetch:0;

      if (DEBUG) console.error("overFetch = " + overFetch);

      var json_facets = {
        // start with the asset counts
        "asset_counts": {
          "limit":100,
          "type":"terms",
          "field":"asset_type",
          "domain": { "excludeTags": "ast"},
        }
      };
      $.each(settings.facetConfigList, function (x, y) {
        if (y.getSolrFacetJSONString()) {
          var facet = JSON.parse(y.getSolrFacetJSONString());
          if (y.applies(searchparams)) {
            $.extend(true, json_facets, facet);
          }
        }
        if ($.type(y.transform) === 'function') {
          transformers[y.name] = y.transform;
          titles[y.name] = y.title;
        }
      });

      // serialize to JSON
      var facetJSON = JSON.stringify(json_facets);


      if (DEBUG) {
        console.log("FACETJSON: ");
        console.dir(facetJSON);
      }

      // add fq's
      var fqhash = {};  // hash of filter queries (fq)

      if ($.type(self.state.filters) === "object") {
        // use the stored ones
        fqhash = self.state.filters;
      }

      // asset type list preprocessing so that the UI is updated in time.
      var assetTypeList;
      if ($.type(self.state.filters) === "object") {
        // use the stored ones
        fqhash = self.state.filters;
        assetTypeList = (self.state.assetTypeList)?self.state.assetTypeList:[];
      }

      var showAssetTypes = searchparams.showAssetTypes;

      if (DEBUG) { console.log(" showAssetTypes = " + JSON.stringify(showAssetTypes)); }

      if ($.isArray(showAssetTypes)) {
        assetTypeList = showAssetTypes;
      } else if ( typeof showAssetTypes === "string" && showAssetTypes.length > 0 ) {
        assetTypeList = showAssetTypes.split(/\s+/);
      } else if ( showAssetTypes === "" ) {
        assetTypeList = [ "all","places", "subjects", "terms", "audio-video", "images", "sources", "texts", "visuals" ];
      }

      if (assetTypeList !== null) {
        self.state.assetTypeList = assetTypeList;
        if (DEBUG) console.log("setting state.assetTypeList : " + JSON.stringify(assetTypeList) );
      }

      if (!assetTypeList || assetTypeList === null || assetTypeList.length === 0 ) {
        assetTypeList = [ "all","places", "subjects", "terms", "audio-video", "images", "sources", "texts", "visuals" ];
      }
      if (DEBUG)  { console.error("assetTypeList = " + JSON.stringify(assetTypeList)); }

      // get the current search string and override any
      if ($.type(searchparams.searchString) === "string") {
        if (searchparams.searchString.length === 0) {
          if (fqhash.searchString) {
            delete fqhash.searchString;
          }
        } else {
          fqhash.searchString = TEXT_SEARCH_FIELD + ":" + searchparams["searchString"];
        }
      }

      // make sure chooseFacets is an array
      var chooseFacets = searchparams["chooseFacets"];
      if ($.type(chooseFacets) === "undefined" || chooseFacets === null) {
        searchparams.chooseFacets = [];
      } else if ($.type(chooseFacets) !== "array") {
        searchparams.chooseFacets = [chooseFacets];
      }

      $.each(searchparams.chooseFacets, function (x, y) {
        fqhash[y.id] = y.filterQuery;
      });

      var chooseKmaps = searchparams.chooseKmaps;
      if (chooseKmaps === null || $.type(chooseKmaps) === "undefined") {
        searchparams.chooseKmaps = [];
      } else if ($.type(chooseKmaps) !== "array") {
        searchparams.chooseKmaps = [chooseKmaps];
      }
      $.each(searchparams.chooseKmaps, function (x, y) {
        if (!fqhash.kmaps) {
          fqhash.kmaps = {};
        }

        // delete if this kmap pre-exists
        if (fqhash["kmaps"][y]) {
          delete fqhash["kmaps"][y];
        }

        // add the kmap clause.   Note that if we do not want the children to match we would use uid instead of ancestor_uids_generic.
        fqhash.kmaps[y] = "kmapid:" + y;

      });

      // we use "OR" logic with kmaps queries. (expanding the hits depending on which kmaps were selected).
      var fqlist = $.map(fqhash, function (v, k) {
        if ($.isPlainObject(v)) {
          var kmaplist = $.map(v, function (kid) {
            return kid;
          });
          if (kmaplist.length !== 0) {
            v = "{!tag=kmaps}(" + kmaplist.join(" OR ") + ")";
          }
        }
        return v;
      });


      // add fq's
      var fqhash = {};  // hash of filter queries (fq)

      // THIS LOGIC IS F'ed UP!
      // NEED TO REFACTOR AND SIMPLIFY!

      if ($.type(self.state.filters) === "object") {
        // use the stored ones
        fqhash = self.state.filters;
        // assetQlist = (self.state.assetQlist)?self.state.assetQlist:[];
        assetTypeList = (self.state.assetTypeList)?self.state.assetTypeList:[];
        if (DEBUG) console.log("STORED assetTypeList: " + JSON.stringify(assetTypeList));
      }

      var showAssetTypes = searchparams.showAssetTypes;
      if (!showAssetTypes && assetTypeList) {
        showAssetTypes = assetTypeList;
      }

      var assetTypeFilter = null;
      if ($.isArray(showAssetTypes) && showAssetTypes.length > 0) {
        assetTypeFilter = "{!tag=ast}asset_type:(" + showAssetTypes.join(" ") + ")";
        assetTypeList = showAssetTypes;
      } else if ( typeof showAssetTypes === "string" ) {
        assetTypeFilter = "{!tag=ast}asset_type:(" + showAssetTypes + ")";

        if (showAssetTypes.length !== 0) {
          assetTypeList = showAssetTypes.split(/\s+/);
        } else {
          assetTypeList = [];
          assetQlist = [];
        }
      }

      if (assetTypeList && assetTypeList.length > 0 && assetTypeList[0].length > 0) {
        if (DEBUG) console.log("assetTypeList = " + JSON.stringify(assetTypeList));
        assetQlist=[ assetTypeFilter ];
      }

      // get the current search string and override any
      if ($.type(searchparams.searchString) === "string") {
        if (searchparams.searchString.length === 0) {
          if (fqhash.searchString) {
            delete fqhash.searchString;
          }
        } else {
          fqhash.searchString = TEXT_SEARCH_FIELD+ ":" + searchparams.searchString;
        }
      }

      // we use "OR" logic with kmaps queries. (expanding the hits depending on which kmaps were selected).
      var facetquery_list = $.map(fqhash, function (v, k) {
        // skip searchString
        if (k === "searchString") {
          return null;
        }
        if ($.isPlainObject(v)) {
          var kmaplist = $.map(v, function (kid) {
            return kid;
          });
          if (kmaplist.length !== 0) {
            v = "(" + kmaplist.join(" OR ") + ")";
          }
        }
        return v;
      });

      // if (facetquery_list.length === 0) {
      //   facetquery_list.push("tree:*"); // need at least one query...
      // }

      if (DEBUG) {
        console.error("FQHASH: " + JSON.stringify(fqhash, undefined, 2));
        console.error("FACETQUERY_LIST:  " + JSON.stringify(facetquery_list, undefined, 2));
        console.error("SEARCHSTRING: " + fqhash.searchString);
        console.error("ASSETQLIST:  " + JSON.stringify(assetQlist, undefined, 2));
      }

      // okay let's execute the query

      // if (DEBUG) {
      //   // useful debugging
      //   $('.search-results-facets').html("<pre>DEBUG</pre><pre>" + JSON.stringify({
      //     fqlist: facetquery_list
      //   }, undefined, 3) + "</pre>");
      // }

      var cf = self.getConfig();

      // verify configuration is set.
      if (!cf.solrBase) {
        throw new Error ("solrBase is not set!");
      } else if (!cf.solrPath){
        throw new Error ("solrPath is not set!");
      } else if (!cf.termIndex) {
        throw new Error("solrPath is not set!");
      }

      var assetMatch = "";
      // var kmapsMatch = "";
      var xact = "";
      // if (xact.search(' ') && xact.charAt(0) != '"') {
      //     xact = '"' + xact + '"';
      // }
      var starts = "";
      var slashy = "";
      var search = "";

      // var kmapsMatchQuery = "";
      if (fqhash.searchString) {
        if (fqhash.searchString !== TEXT_SEARCH_FIELD + ":*")  {
          search = fqhash.searchString.split(':')[1];

          // improve "exact matching" sub-strings
          search = search.replace(/\ /g ,'\\ ');
          xact = search.replace(/\*/g,"");

          // if (xact.search(' ') && xact.charAt(0) != '"') {
          //     xact = '"' + xact + '"';
          // }
          starts = xact+"*";
          slashy = xact+"/";

          // SOLR weighted query
          assetMatch = "title:${xact}^100" +
            "title:${slashy}^100" +
            " names_txt:${xact}^90" +
            " title:${starts}^80" +
            " names_txt:${starts}^70" +
            " title:${search}^10" +
            " caption:${search}" +
            " summary:${search}" +
            " names_txt:${search} " ;
          // kmapsMatch = "{!join from=uid_i to=kmapid_is score=none v=$kmapsMatch}";
          var qSearch = fqhash.searchString;
          if (search.search(' ') > -1 && search.charAt(0) != '"') {
              qSearch = fqhash.searchString.split(':')[0] + ':"' + search + '"';
          }
          // kmapsMatchQuery = qSearch + " OR " + "name_tibt:\"" + fqhash.searchString.split(':')[1] + "\"";
        }
      }


      // // NEED TO ESCAPE SPACES IN THE JOINQ QUERIES WITH "\ ".   BUT ONLY IN THE JOINQ!
      // var joinqlist = $.map(facetquery_list, function(fq) {
      //
      //   if (fq.startsWith(TEXT_SEARCH_FIELD + ':')) {
      //     return fq.replace(" ", "\\ ").replace(":","\\:");
      //   } else {
      //     return fq;
      //   }
      // });
      // var joinquery = (joinqlist.length)?"+" + joinqlist.join(" " +
      //   JOINQ_LOGIC +
      //   " +") : "";
      // if (DEBUG) console.log("JOINQUERY = " + joinquery);

      var requestUrl = "https://" + cf.solrBase + cf.solrPath + cf.assetIndex + "/select";
      var assetQueryClause = (assetMatch)?"( " + assetMatch + " )":"*:*";

      var fqlist_full = [ assetTypeFilter ];
      fqlist_full.push ("-asset_type:(picture document video)");


      fqlist_full.push ("-kmapid_strict:(subjects-9311 subjects-9312 subjects-9313 subjects-9314)");


      if(cf.assetFilterQuery && cf.assetFilterQuery.length > 0) {
        for (var i = 0; i < cf.assetFilterQuery.length; i++) {
          if (DEBUG) { console.log("pushing assset query \"" + cf.assetFilterQuery[i] + "\" onto fqlist..."); }
          fqlist_full.push(cf.assetFilterQuery[i]);
        }
      }

      if (facetquery_list && facetquery_list.length) {
        for (var j=0; j < facetquery_list.length; j++) {
          if (DEBUG) { console.log("pushing facet query \"" + facetquery_list[j] + "\" onto fqlist..."); }
          fqlist_full.push(facetquery_list[j]);
        }
      }

      if (DEBUG) {
        console.log("ASSET QUERY fqlist:");
        console.dir(fqlist_full);
      }

      var requestParams = {
        "q": assetQueryClause,
        "fl": '*',
        "start": x_start,
        "rows": pageSize + overFetch,
        "wt": "json",
        "fq": fqlist_full,
        "facet": "on",
        // "facet.field": "{!ex=ast}asset_type",
        'json.facet': facetJSON,
        "hl":"on",
        "hl.method":"unified",
        "hl.fl":"title,caption,summary,names_txt",
        "hl.fragsize":0,
        "hl.tag.pre":"<mark>",
        "hl.tag.post":"</mark>",
        "echoParams":"explicit",
        "xact":xact,
        "starts":starts,
        "search":search,
        "slashy":slashy
       };

      // if (assetQlist.length > 0) {
      //   requestParams.fq = assetQlist;
      // }



      if (DEBUG) {
        console.log("ASSET QUERY CLAUSE: " + assetQueryClause);
        console.log("FQ LIST: " + JSON.stringify(fqlist_full));
        console.log(JSON.stringify({ "REQUEST PARAMS" : requestParams }, undefined, 2));
      }


      try {
        // traditional is required to properly process multiple fq parameters for SOLR
        $.ajaxSettings.traditional = true;
        $.ajax({
          type: "GET",
          cache: true,
          url: requestUrl,
          data: requestParams,
          dataType: "jsonp",
          jsonp: 'json.wrf',
          timeout: 30000,

          error: function (e) {
            console.error("ERRORING: " + JSON.stringify(e));
            asset_search_cb(e);
          },
          beforeSend: function () {

          },
          success: function (response) {

            // process facets

            var results = response.response; // the main results.
            var facets = response.facets;
            var facetHash = (self.state.facetHash) ? self.state.facetHash : {};

            var filters = self.state.filters || {};

            var fq = response.responseHeader.params.fq;

            // assemble the fqhash from all the information we have at the moment....

            // make sure fq is an array

            var $fq_type = $.type(fq);
            if ($fq_type === "undefined") {
              filters = {};
            } else if ($fq_type !== "array" && $fq_type !== "string") {
              throw new Error("unrecognized filters.  Must be string or array: " + JSON.stringify(fq));
            } else {
              if ($fq_type === "string") {
                fq = [fq];
              }

              // lookup the facet object from the facetHash
              $.each(fq, function (i, filter) {
                var $facet;
                if (self.state && self.state.facetHash) {
                  $facet = self.state.facetHash[filter];
                }
              });
            }

            // apply the transformers
            for (var field in facets) {
              // console.error("MUNGING: " + field);
              if (field === "count" || field === "asset_counts") {
                // ignore count field right now.
                // if (DEBUG) console.log("count = " + facets.count);
              } else {
                facets[field].title = titles[field];
                facets[field].name = field;
                for (var item in facets[field].buckets) {
                  try { // transform each returned facet according to the transform() method of the FacetConfig
                    var term = facets[field].buckets[item];
                    var transformer = transformers[field];

                    if (DEBUG) {
                      console.log("Term = " + JSON.stringify(term));
                      console.log("Field = " + field);
                      console.log("Found transformer = " + transformer);
                    }

                    if ($.type(transformer) === "function") {
                      var entry = transformer(term);
                      if (filters[entry.id]) {
                        entry.selected = true;
                      }
                      facets[field].buckets[item] = entry;
                      facetHash[entry.id] = entry;
                      facetHash[entry.filterQuery] = entry;  // want to look it up by id or query!
                    } else {
                      console.error("transformer not found for field = " + field);
                    }
                  } catch (e) {
                    console.error("Skipping transform of " + facets[field].buckets[item] + ": " + e);
                    throw(e);
                  }
                }

                // sort the buckets with selected items on top
                facets[field].buckets.sort(function (a, b) {
                    if (!a.selected) {
                      a.selected = false;
                    }
                    if (!b.selected) {
                      b.selected = false;
                    }
                    if (a.selected === b.selected) {
                      return (b.count - a.count);
                    } else if (a.selected) {
                      return -1;
                    } else if (b.selected) {
                      return 1;
                    } else {
                      return b.count - a.count;
                    }
                  }
                );
              }
            }

            // let's store this state in self.state
            var current_blob = $.extend(self.state, {
              'facets': facets,
              'facetHash': facetHash,
              'filters': filters,
              'results': results
            });

            // see the raw solr reponse
            if (DEBUG){
              console.error("THE ASSET RESPONSE");
              console.dir(response);
            }

            // process the results
            var asset_results = response.response; // the main results.
            var asset_counts = {};

            // process highlighting!
            if (false) {
              console.log("HIGHLIGHTING:");
              console.dir(response.highlighting);
            }

            var hl = response.highlighting;


            // remap data as needed:
            var newdocs = $.map(asset_results.docs, function(doc, cb) {

              // Insert highlighting
              if (hl[doc.uid]) {
                if (hl[doc.uid].title.length > 0) {
                  if (false) {
                    console.log("highlighting doc.title for " + doc.uid + "...");
                  }
                  doc.title = hl[doc.uid].title;
                }
                if (hl[doc.uid].caption.length > 0) {
                  if (false) {
                    console.log("highlighting doc.caption for " + doc.uid + "...");
                  }
                  doc.caption = hl[doc.uid].caption[0];
                }
                if (hl[doc.uid].summary.length > 0) {
                  if (false) {
                    console.log("highlighting doc.summary for " + doc.uid + "...");
                  }
                  doc.summary = hl[doc.uid].summary[0];
                }

                if (hl[doc.uid].names_txt.length > 0) {
                  if (false) {
                    console.log("highlighting doc.names_txt for " + doc.uid + "...");
                  }

                  var hl_names = hl[doc.uid].names_txt;
                  for (var j = 0; j < doc.names_txt.length; j++) {
                    if (false) { console.log("doc.title = " + $("<i>" + doc.title[0] + "</i>").text()); }
                    if (doc.names_txt[j] === $("<i>" + doc.title[0] + "</i>").text()) { // idiomatic way of removing markup...
                      if (false) { console.log ("REMOVING " + doc.names_txt[j]); }
                      delete doc.names_txt[j];
                    } else {
                      for (var i = 0; i < hl_names.length; i++) {
                        if (doc.names_txt[j] === $("<i>"+ hl_names[i] + "</i>").text()) {
                          if (false) {
                            if (false) { console.log(" ...REPLACING: " + doc.names_txt[j] + " with " + hl_names[i]) };
                          }
                          doc.names_txt[j] = hl_names[i];
                          break;
                        }
                      }
                    }
                  }
                }
              }

              // make kmapid_strict uniq!
              if (doc.kmapid_strict) {
                var kmapid_strict = doc.kmapid_strict;

                var unique = [];
                var places = [];
                var subjects = [];
                $.each(kmapid_strict, function (i, el) {
                  if ($.inArray(el, unique) === -1 && el !== doc.uid) {
                    unique.push(el);
                    if (el.startsWith('subjects')) {
                      subjects.push(el);
                    } else if (el.startsWith('places')) {
                      places.push(el);
                    }
                  }
                });
                doc.kmapid_strict = unique;
                doc.kmapid_strict_places = places;
                doc.kmapid_strict_subjects = subjects;
              }


              // sort and organize kmapid_strict





              // fix title
              if (!doc.title) {
                if (doc.caption) {
                  doc.title = [doc.caption];
                } else {
                  doc.title = [doc.uid];
                }
              }
              doc.header = doc.title[0];

              // fix tree
              if (!doc.tree) {
                if (doc.asset_type) {
                  doc.tree = doc.asset_type;
                }
              }

              if (doc.asset_subtype) {
                doc.asset_subtype = doc.asset_subtype.replace(/\s+/g,"_");
              }

              // fix ancestors
              if (!doc.ancestors) {
                if (doc.ancestors_txt) {
                  doc.ancestors = doc.ancestors_txt;
                }
              }

              if (!doc.feature_types) {
                if (doc.feature_types_ss) {
                  doc.feature_types = doc.feature_types_ss;
                }
              }

              var display = $('<i>' + doc.header + '<\i>').text(); //  + " (" + doc.uid + ")"; // display kmapid
              // console.log( "DOC DOC: " + doc.uid + " = " + display);

              if ($.type(self.state.kmapsLabelCache) === "undefined") {
                self.state.kmapsLabelCache = {};
              }
              self.state.kmapsLabelCache[doc.uid] = display;

              if (DEBUG) console.dir(doc);

              // trip a solr lookup
              // let's not...  Its quite expensive.
              // self.updateKmapLabels(doc.kmapid);

              return doc;
            });

            if (response.facets && response.facets.asset_counts) {
              if (DEBUG) console.error(JSON.stringify(response.facets.asset_counts, undefined, 3));
              var buckets = response.facets.asset_counts.buckets;
              for (var b=0; b < buckets.length; b++) {
                var bucket = buckets[b];
                var value = bucket.val;
                var count = bucket.count;
                asset_counts[value] = count;
              }

              // Now discard the asset_counts from the original facet list so it doesn't appear in the facet list.
              delete response.facets.asset_counts;

            }

            if (DEBUG) {
              console.log("ASSET COUNTS : " + JSON.stringify(asset_counts, undefined, 3));
              console.log("checking state.assetQlist : " + assetQlist);
              console.log("checking state.assetTypeList : " + JSON.stringify(assetTypeList));
            }
            if (assetTypeList !== null) {
              self.state.assetTypeList = assetTypeList;
              if (DEBUG) console.log("setting state.assetTypeList : " + JSON.stringify(assetTypeList) );
            }
            if (assetQlist !== null) {
              self.state.assetQlist = assetQlist;
              if (DEBUG) console.log("setting state.assetQlist : " + assetQlist);
            }

            // let's store this state in self.state
            var current_blob = $.extend(self.state, {
              'asset_results': asset_results,
              'asset_counts' : asset_counts,
            });

            if (DEBUG) {
              console.log("=======================>");
              console.dir(current_blob);
            }

            asset_search_cb(null,current_blob);

          },
          complete: function () {
            // if (DEBUG) {
            //   console.log("COMPLETE");
            // }
          }
        });
      } catch (err) {
        console.error(err);
      }
      // asset_search_cb(null, {});
    },

    clearFacets: function() {
      var searchString = this.state.filters["searchString"];
      this.state.filters = { "searchString": searchString };
      return this.search();
    },

    clearAll: function() {
      this.state.filters = { };
      return this.search();
    },

    // convenience function
    pageNext: function () {
      return this.page('next');
    },

    // convenience function
    pagePrev: function () {
      return this.page('prev');
    },

    // convenience function
    pageLast: function () {
      return this.page('last');
    },

    // convenience function
    pageFirst: function () {
      return this.page(1);
    },

    pageCount: function () {
      var numFound = (this.state.asset_results)?Number(this.state.asset_results.numFound):0;
      var size = this.settings.pageSize;
      var pages = Math.ceil(numFound / size);
      return pages;
    },

    page: function (pg_number) {
      var numFound = (this.state.asset_results)?Number(this.state.asset_results.numFound):0;
      var start = (this.state.asset_results)?Number(this.state.asset_results.start):0;
      var size = this.settings.pageSize;
      var page = Math.ceil((start + 1) / size);
      var pages = Math.ceil(numFound / size);

      // console.groupCollapsed("page " + page + "/" + pages + " results " + start + "/" + numFound);
      // console.log(" numFound = " + numFound);
      // console.log("    start = " + start);
      // console.log("    size = " + size);
      // console.log("     page = " + page);
      // console.log("    pages = " + pages);
      // console.groupEnd();


      if (pg_number === undefined) {
        return page;
      }

      if(DEBUG) {
        console.log("pg_number = " + JSON.stringify(pg_number));
      }
      if (!$.isNumeric(pg_number)) {
        if (pg_number === 'first') {
          pg_number = 0;
        } else if (pg_number === 'last') {
          pg_number = pages;
        } else if (pg_number === 'next') {
          pg_number = page + 1;
        } else if (pg_number === 'prev') {
          pg_number = page - 1;
        } else {
          throw new Error("recognized argument to page(): " + pg_number);
        }
      }

      // console.log("pg_number = " + JSON.stringify(pg_number));

      if (!$.isNumeric(pg_number)) {
        throw new Error("Whoa, we should only be dealing with a number at this point!  Somehow pg_number = " + pg_number);
      }
      // deal with page number only from now on....

      // constrain range
      if (pg_number <= 0) {
        pg_number = 1;
      } else if (pg_number > pages) {
        pg_number = pages;
      }

      // calculate start from page number
      var new_start = (pg_number - 1) * size;

      // console.log("Trying to go to start = " + new_start);
      return this.search({start: new_start});
    },

    getRangeStart: function() {
      if (this.state && this.state.asset_results) {
        return Number(this.state.asset_results.start) + 1;
      } else {
        return 0;
      }
    },

    getRangeEnd: function() {
      if (this.state && this.state.asset_results) {
        return Number(this.state.asset_results.start) + Number(this.state.asset_results.docs.length);
      } else {
        return 0;
      }
    },

    getState: function () {
      return this.state;
    },

    getConfig: function () {
      return this.settings;
    },

    // utility
    updateKmapLabels: function(requested_kids, callback) {

      var DEBUG = false;

      var self = this;
      var cf = self.getConfig();

      // lookup the list of kmaps and cache their name

      if (DEBUG) console.log("updateKmapLabels: " + JSON.stringify(requested_kids));

      var unique = [];
      $.each(requested_kids, function(i, el){
        if($.inArray(el, unique) === -1) unique.push(el);
      });



      if ($.type(callback) !== "function") {
        callback = function() { if (DEBUG) console.log("updateKmapLabels no-op callback: " + JSON.stringify(arguments)); };  // no-op callback
      }

      try {
        if (!Drupal.settings.kmapsSolr.state.kmapsLabelCache) {
          Drupal.settings.kmapsSolr.state.kmapsLabelCache = {};
        }
        if ($.isArray(requested_kids) && requested_kids.length > 0) {
          requested_kids = $.grep(requested_kids, function(x) {
            if (Drupal.settings.kmapsSolr.state.kmapsLabelCache[x]) {
              if (DEBUG) console.error(x + " exists in cache. skipping...");
              // var cached = {
              //   uid: x,
              //   header: Drupal.settings.kmapsSolr.state.kmapsLabelCache[x]
              // }
              // $(Drupal.settings.kmapsSolr).trigger('kmapsLabelCacheUpdate', [cached]);

              return false;
            } else {
              return true;
            }
          });

          if (unique.length > 0) {
              var kmapids = unique.slice(0,100); // truncate
              if (DEBUG) console.log("cacheKmaps: " + JSON.stringify(kmapids));
              var kst = kmapids.join(' ');
              var query = "uid: (" + kst + ")";
              $.ajax({
                "type": "GET",
                "cache": true,
                "url": "https://" + cf.solrBase + cf.solrPath + cf.termIndex + "/query",
                "data": {
                  "q": query,
                  "fl": "uid,header",
                  "rows": 100
                },
                "dataType": "jsonp",
                "jsonp": "json.wrf",
                "error": function (x, etype, message) {
                  console.error(message);
                  callback(message, null);
                },
                "success": function (resp) {
                  var ret = $.map(resp.response.docs, function (mapping, y) {
                    // if (DEBUG) console.error("Caching " + JSON.stringify(mapping));
                    var display_label = mapping.header; // + " (" + mapping.uid + ")"; // display kmapid
                    // console.error( "Label: " + display_label);
                    Drupal.settings.kmapsSolr.state.kmapsLabelCache[mapping.uid] = display_label;
                    $(Drupal.settings.kmapsSolr).trigger('kmapsLabelCacheUpdate', [mapping]);
                    return mapping;
                  });

                  //  COMPARE THE REQUESTED kmapids with the returns
                  //  Deal with those labels that are unavailable...

                  if (DEBUG) {
                    console.log("REQUESTED KMAPIDS: " + JSON.stringify(kmapids));
                    console.log("RETURNED: " + JSON.stringify(ret, undefined, 2));
                  }

                  var kmapid_map = {};

                  for (var i = 0; i < kmapids.length; i++) {
                    kmapid_map[kmapids[i]] = kmapids[i];
                  }

                  for (var j = 0; j < ret.length; j++) {
                    delete kmapid_map[ret[j].uid];
                  }

                  if (ret.length == 0 && !$.isEmptyObject(kmapid_map)) {
                    console.error("We couldn't get the proper labels for these: " + JSON.stringify(kmapid_map, undefined, 2));

                    // give up on these and cache a the uid as the label
                    $.each(kmapid_map, function (x, y) {
                      var mapping = {uid: x, header: "Unknown " + y};
                      Drupal.settings.kmapsSolr.state.kmapsLabelCache[mapping.uid] = mapping.header;
                      $(Drupal.settings.kmapsSolr).trigger('kmapsLabelCacheUpdate', [mapping]);
                    });
                  }


                  callback(null, ret);
                }
              });
          }
        }
      } catch (e) {
        console.error(e);
        callback(e,null);
      }
    }

};

  $.extend(KMapsSolr.prototype, {
    update: function () {

      // This is the internal function that notifies 'update' listeners and passes the internal state
      // $(this).trigger('update',this.state);

      if (DEBUG) {
        console.group("update handler");
      }
      // if (DEBUG) console.log("update() calling updateHandler with state");
      this.updateHandler(this.state);
      if (DEBUG) {
        console.groupEnd("update handler");
      }

    },
    updateHandler: function (state) {
      // if (DEBUG) console.log("updateHandler() called with state" , state);
      // console.groupCollapsed(state);
      // This is a weeny way of doing this.  Why not override this method instead?
      if ($.type(this.settings.updateHandler) === 'function') {
        this.settings.updateHandler(state);
      } else {
        console.error("No update handler specified");
      }
    }

  });

  // Just a simple factory method
  $.fn.kmapsSolr = function (config, options) {
    return new KMapsSolr(config, options);
  };

  $.kmapsSolr = function (config, options) {
    return new KMapsSolr(config, options);
  };

})(jQuery, window, document);
