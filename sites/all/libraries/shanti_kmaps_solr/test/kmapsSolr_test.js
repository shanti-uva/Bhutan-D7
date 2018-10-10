(function ($) {

    // Utility functions

    var chosenFacetId = "";

    var objector = function (key, value) {

        if (value === undefined ) {
            return ">>>> undefined <<<<";
        }

        if ($.type(value) === "object" && $.type(value.value) == "string") {
            return "{ " + value.count + ": " + value.id + " }";
        }

        if ($.type(value.handlebarsTemplate) !== "undefined") {
            return "{ FacetConfig " + value.name + " }";

        }

        if ($.type(value.header) !== "undefined") {
            return "{ " + value.uid +": "+  value.header + " }";
        }


        return value;
    }

    QUnit.test('search sequence using update handler', function (assert) {
        //  Documented functions
        // // allow the HANDLER to do all the work
        // kmaps.search($('#searchfield').text());

        assert.expect(11);

        var done = assert.async(10);
        var kmaps = $.kmapsSolr('predev', {
            updateHandler: function (blob) {

                console.log("UPDATEHANDLER");
                // console.log(JSON.stringify(blob, objector,2 ));
                // console.log("updateHandler returned BLOB = " + JSON.stringify(blob,undefined,3));
                assert.equal($.type(blob), "object", 'returned should be an object');

                console.log("...availableFacets = " + JSON.stringify(blob.facets, objector, 2));
                console.log("...chosenFacets = " + JSON.stringify(blob.chosenFacets));
                console.log("...filters = " + JSON.stringify(blob.filters));
                console.log("...results = " + JSON.stringify(blob.results, objector, 2));

                done();

            }

        });

        // execute search

        kmaps.search('*').then(function (kmaps) {
            console.log("============= RESOLVED PROMISE ==============");
            console.log("returned " + JSON.stringify(kmaps, objector, 3));

            var facet = kmaps.getState().facets.related_places.buckets[0];
            console.log("A FACET: " + JSON.stringify(facet));

            chosenFacetId = facet.id;
            return kmaps.selectFacet(facet);
        }).then(function (xxx) {
            console.log("ZINGO! " + JSON.stringify(xxx,objector,2));

            var facet = xxx.getState().facets.feature_types.buckets[1];
            console.log("ANOTHER FACET: " + JSON.stringify(facet));

            return kmaps.selectFacet(facet);
        }).then(function(kmmm) {

            console.log("BINGO!" + JSON.stringify(kmmm,objector,2));

            console.log("Trying to remove: " + JSON.stringify(chosenFacetId));
            return kmmm.removeFacet(chosenFacetId);

        }). then (function(kfff) {
            console.log("RINGO!" + JSON.stringify(kfff,objector,2));

            return kfff.selectKmapId('places-637');
        }).then (function(kppp) {
            console.log("SINGO!" + JSON.stringify(kppp,objector,2));
            return kppp.selectKmapId('places-2');
        }).then (function(kppp) {
            console.log("SINGO!" + JSON.stringify(kppp,objector,2));

            return kppp.removeKmapId('places-637');
        }).then (function(kzzz) {
            console.log("GINGO!" + JSON.stringify(kzzz,objector,2));

            return kzzz.pagePrev();
        }).then (function(knnn) {
            console.log("KINGO!" + JSON.stringify(knnn,objector,2));
            assert.ok(true, "phew");
            done();
        });

        assert.ok(true, "ok");
    });

}(jQuery));
