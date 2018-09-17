/**
 * @file
 * Fancytree javascript integration for sources collection.
 */
(function ($) {
Drupal.behaviors.sourcesViewsInitializeCollectionListFancyTree = {
  attach: function (context, settings) {
  	if ($('.taxonomy-list-tree').length == 0) { return; }
    $('.taxonomy-list-tree').fancytree({
      source: {
        url: sources_views_get_collection_source_path(),
        cache: false
      },
      extensions: ['filter', 'glyph'],
      glyph: sources_views_get_glyphicon_class(),
      icons: false,
      init: function (event, data) {
        // Set a collection item as active if there is collection filter applied.
        var collection_id = $.get_query_string_val('field_zotero_collections');
        if (collection_id) {
          var collection_item_id = 'collection-item-' + collection_id;
          if ($('.taxonomy-list-tree').fancytree('getTree').getNodeByKey(collection_item_id)) { 
              $('.taxonomy-list-tree').fancytree('getTree').getNodeByKey(collection_item_id).setActive();
          }
        }
      },
      renderNode: function (event, data) {
        sources_views_set_custom_class_names();
      },
      click: function (event, data) {
        // Prevent breadcrumb list container from closing if one of the fancytree item is being expanded/closed.
        event.stopPropagation();
        // Redirect to sources search result page filtered by the selected collection.
        sources_views_redirect_to_filtered_collection_page(event, data);
      }
    });
  }
};

Drupal.behaviors.sourcesViewsInitializeBreadcrumbCollectionListFancyTree = {
  attach: function (context, settings) {
    $('.breadcrumb-tree').each(function(index) {
      var collection_data_url = sources_views_get_collection_source_path($(this).attr('data-collection-parent-id'));
      var fancytree_breadcrumb_container_id = '#' + $(this).attr('id');
      sources_views_build_fancytree_breadcrumb_taxonomy(fancytree_breadcrumb_container_id, collection_data_url)
    });

    // Build each breadcrumb child collection items into fancytree
    function sources_views_build_fancytree_breadcrumb_taxonomy(fancytree_breadcrumb_container_id, collection_data_url) {
    	  if ($(fancytree_breadcrumb_container_id).length == 0 ) { return; }
      $(fancytree_breadcrumb_container_id).fancytree({
        source: {
          url: collection_data_url,
          cache: false
        },
        extensions: ['filter', 'glyph'],
        glyph: sources_views_get_glyphicon_class(),
        icons: false,
        renderNode: function (event, data) {
          sources_views_set_custom_class_names();
        },
        click: function (event, data) {
          // Prevent breadcrumb list container from closing if one of the fancytree item is being expanded/closed.
          event.stopPropagation();
          // Redirect to sources search result page filtered by the selected collection.
          sources_views_redirect_to_filtered_collection_page(event, data);
        }
      });
    }
  }
};

function sources_views_get_collection_source_path(collection_parent_id) {
  if (collection_parent_id) {
    collection_json_data_url = Drupal.settings.basePath + 'json/collection-list/' + collection_parent_id;
  }
  else {
    collection_json_data_url = Drupal.settings.basePath + 'json/collection-list';
  }
  return collection_json_data_url;
}

function sources_views_get_glyphicon_class() {
  var glyphicon_class = {
    map: {
      checkbox: "glyphicon glyphicon-unchecked",
      checkboxSelected: "glyphicon glyphicon-check",
      expanderClosed: "glyphicon glyphicon-plus-sign",
      expanderOpen: "glyphicon glyphicon-minus-sign",
    }
  };
  return glyphicon_class;
}

function sources_views_set_custom_class_names() {
  // Set class name to a collection item on mouse hover.
  $('.fancytree-node').hover(function() {
    $(this).addClass('on-hover');
  }, function() {
    $(this).removeClass('on-hover');
  });
}

function sources_views_redirect_to_filtered_collection_page(event, data) {
  var node = data.node;
  var click_item = $.ui.fancytree.getEventTargetType(event.originalEvent);
  if (click_item == 'title') {
    var term_id = node.key;
    var collection_id = term_id.replace(/\D/g,'');
    var url = '/sources-search?field_zotero_collections=' + collection_id + '&view_mode=collection';
    window.location = url;
  }
}

})(jQuery);
