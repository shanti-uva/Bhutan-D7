(function ($) {
	
	//  ndg8f 2013-11-14: Updated (2016-02-19) to load only when tab is first clicked to speed up page load.
	Drupal.behaviors.mbSolrRelatedTab={ 
		attach: function(context) {
			//console.log('mb solr js context:', $(context).attr('id'));
			if(context == document) { 
                // Load more related when tab is clicked
               $('#related-tab').on('show.bs.tab', function() {
                    // Ajax Service Call for More Like This Related videos
                    var data = $('div#related').data();
                    if(data != null && typeof(data.nid) != 'undefined') { 
                        if ($('#related-av-nodes .loading-img').length > 0) {
                            var nid = data.nid;
                            var ct = (typeof(data.count) != "undefined") ? '/' + data.count : '';
                            var url = Drupal.settings.basePath + 'services/mlt/' + nid + ct;
                            $('#related-av-nodes').load(url, function() { 
                                $("#related.mlt .dev-query").remove();
                                $("#related.mlt .shanti-gallery").addClass('clearfix');
                                Drupal.attachBehaviors('#related.mlt');
                            });
                        }
                    }
                    // Set height of facet block to match height of flyout
                    setTimeout(function() {
                        $('.block-facetapi').each(function() { 
                                var hgt = $(this).parent().height(); 
                                $(this).height(hgt); 
                                $(this).children('.content').height(hgt); 
                        });
                    }, 1000);
                });
		    }
	 	}
	};
	
	Drupal.behaviors.mbSolrHomeBlockFilter={ 
        attach: function(context) {
            if($(context).attr('id') == 'views-exposed-form-browse-media-home-block') {
                // Home block views ajax sort/filter request
                if ($('#no-views-filter-results').length > 0) {
                    var p = jQuery('#no-views-filter-results').parents('.shanti-gallery');
                    var cl = p.attr('class');
                    var mtch = cl.match(/view-dom-id-([^\s]+)/); // mtch[0] is full string, mtch[1] is just alphanumeric id
                    if(mtch && mtch.length > 1) {
                        var vdid = 'views_dom_id:' + mtch[1];
                        setTimeout( function() {
                            Drupal.views.instances[vdid].$view.trigger('RefreshView');
                        }, 1000);
                    }
                }
            }
        }
    };
	
} (jQuery));