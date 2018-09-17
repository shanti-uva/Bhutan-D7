/**
 * Created by edwardjgarrett on 5/22/16.
 */

(function ($) {

    // local "globals"
    var filtered = {};

    // utility functions
    function extractKMapID(line) {
        var kmap_id = null;
        var rgx1 = /\s(\w?\d+)$/;
        var matches = rgx1.exec(line);
        if (matches != null) {
            var kmap_id = matches[1];
        }
        return kmap_id;
    }

    function pickFilter(namespace, type, suggestion) {
        var $box = $('#' + namespace + '-filter-box-' + type);
        var kmap_id = 'F' + suggestion.id;
        var item = {
            domain: 'subjects', // default
            id: suggestion.id,
            header: suggestion.value,
            path: '{{' + suggestion.id + '}}'
        };
        if (!filtered[namespace][type][kmap_id]) {
            filtered[namespace][type][kmap_id] = item;
            var $el = $("<div/>").addClass('selected-kmap ' + kmap_id).appendTo($box);
            $("<span class='icon shanticon-close2'></span>").addClass('delete-me').addClass(kmap_id).appendTo($el);
            $("<span>" + item.header + " " + kmap_id + "</span>").addClass('kmap-label').appendTo($el);
            $el.attr({
                'data-kmap-id-int': item.id,
                'data-kmap-path': item.path,
                'data-kmap-header': item.header
            });
            Drupal.attachBehaviors($el);
        }
    }

    function getNamespace($el, suffix) {
        return $el.attr('id').replace(suffix, '');
    }

    function getFilter(namespace, type) {
        return $('#' + namespace + '-search-filter-' + type);
    }

    function getFilterBox(namespace, type) {
        return $('#' + namespace + '-filter-box-' + type);
    }

    function getTypeahead(namespace) {
        return $('#' + namespace + '-search-term');
    }

    // behaviors
    Drupal.behaviors.shantiKmapsAdminFilter = {

        attach: function (context, settings) {

            var admin = settings.shanti_kmaps_admin;

            $('.kmap-filter-box').once('shanti-kmaps').each(function () {
                var type = $(this).attr('data-search-filter');
                var namespace = getNamespace($(this), '-filter-box-' + type);
                if (!filtered[namespace]) {
                    filtered[namespace] = {};
                }
                filtered[namespace][type] = {}; // Init filters for this field
            });

            $('.kmap-filter-box .delete-me').once('shanti-kmaps').on('click', function (e) {
                var $el = $(this).parent();
                var $box = $(this).closest('.kmap-filter-box');
                var type = $box.attr('data-search-filter'); //feature_type or associated_subject
                var namespace = getNamespace($box, '-filter-box-' + type);
                var $filter = getFilter(namespace, type);
                var $typeahead = getTypeahead(namespace);
                var others = [];
                if (filtered[namespace]) {
                    others = Object.keys(filtered[namespace]);
                    others.splice(others.indexOf(type), 1);
                }
                var kmap_id = extractKMapID($(this).next('span.kmap-label').html());
                var field = type + "_ids";
                var search = $filter.typeahead('val'); //get search term
                KMapsUtil.removeFilters($typeahead, field, filtered[namespace][type]);
                delete filtered[namespace][type][kmap_id];
                KMapsUtil.trackTypeaheadSelected($filter, filtered[namespace][type]);
                $el.remove();
                var fq = KMapsUtil.getFilters(field, filtered[namespace][type], $box.hasClass('kmaps-conjunctive-filters') ? 'AND' : 'OR');
                $typeahead.kmapsTypeahead('addFilters', fq).kmapsTypeahead('setValue', $typeahead.typeahead('val'), false);
                for (var i=0; i<others.length; i++) {
                    getFilter(namespace, others[i]).kmapsTypeahead('refetchPrefetch', fq);
                }
                $filter.kmapsTypeahead('refacetPrefetch', fq);
                $filter.kmapsTypeahead('setValue', search, false); // 'false' prevents dropdown from re-opening
            });

            $('.kmap-search-filter', context).once('shanti-kmaps').each(function () {
                var $filter = $(this);
                var type = $filter.attr('data-search-filter'); //feature_type or associated_subject
                var namespace = getNamespace($filter, '-search-filter-' + type);
                var nsettings = admin.kmaps_filter[namespace];
                // var root_kmap_path = nsettings.root_kmap_path ? nsettings.root_kmap_path : nsettings.domain == 'subjects' ?  admin.shanti_kmaps_admin_root_subjects_path : admin.shanti_kmaps_admin_root_places_path;
                var others = [];
                if (filtered[namespace]) {
                    others = Object.keys(filtered[namespace]);
                    others.splice(others.indexOf(type), 1);
                }
                /*  kmaps navigator domain handling
                 var domain = (settings.kmaps_explorer) ? settings.kmaps_explorer.app : 'places';
                 */
                $filter.kmapsTypeahead({
                    term_index: admin.shanti_kmaps_admin_server_solr_terms,
                    domain: 'subjects', // always Filter by Subject
                    filters: KMapsUtil.getFilterQueryForFilter(type),
                    ancestors: 'off', 
                    min_chars: 0,
                    selected: 'omit',
                    prefetch_facets: 'on',
                    prefetch_field: type + 's', //feature_types or associated_subjects
                    prefetch_filters: nsettings.root_kmap_path ? ['tree:' + nsettings.domain, 'ancestor_id_path:' + nsettings.root_kmap_path] : ['tree:' + nsettings.domain],
                    max_terms: 50
                }).bind('typeahead:select',
                    function (ev, suggestion) {
                        if (suggestion.count > 0) { // should not be able to select zero-result filters
                            var mode = suggestion.refacet ? 'AND' : 'OR';
                            var $typeahead = getTypeahead(namespace);
                            var $box = getFilterBox(namespace, type);
                            var field = type + "_ids";
                            KMapsUtil.removeFilters($typeahead, field, filtered[namespace][type]);
                            pickFilter(namespace, type, suggestion);
                            $box.toggleClass('kmaps-conjunctive-filters', mode == 'AND');
                            KMapsUtil.trackTypeaheadSelected($filter, filtered[namespace][type]);
                            var fq = KMapsUtil.getFilters(field, filtered[namespace][type], mode);
                            $typeahead.kmapsTypeahead('addFilters', fq).kmapsTypeahead('setValue', $typeahead.typeahead('val'), false);
                            for (var i=0; i<others.length; i++) {
                                getFilter(namespace, others[i]).kmapsTypeahead('refetchPrefetch', fq);
                            }
                            $filter.kmapsTypeahead('refacetPrefetch', fq);
                            $filter.kmapsTypeahead('setValue', '', false); // reset filter after selection
                        }
                    }
                );
            });
        },

        detach: function (context, settings) {

        }

    };

})(jQuery);
