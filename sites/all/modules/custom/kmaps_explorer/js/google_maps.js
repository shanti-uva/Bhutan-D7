;(function ($) {
    Drupal.behaviors.kmapsExplorerMaps = {
        attach: function (context, settings) {
            if ($("#map-canvas").length) {
                var mapOptions = {
                    zoom: 11,
                    scrollwheel: false
                };

                var map = new google.maps.Map(document.getElementById("map-canvas"), mapOptions);

                var ctaLayer = new google.maps.KmlLayer({
                    url:
                    "http://places.thlib.org/features/gis_resources/" +
                    Drupal.settings.kmaps_explorer.closest_fid_with_shapes +
                    ".kml",
                    map: map
                });

                //Hide the openlayer maps
                $(".openlayermap", context).hide();

                //Listener functions for the map switch buttons.
                $(".renderGmaps").click(function () {
                    $(".openlayermap", context).hide();
                    $("#map-canvas", context).show();
                    $(this).addClass("active");
                    $(".renderOpenLayerMaps").removeClass("active");
                });

                $(".renderOpenLayerMaps").click(function () {
                    $("#map-canvas", context).hide();
                    var iframe = $(".openlayermap > iframe", context);
                    iframe.attr("src", iframe.data("src"));
                    $(".openlayermap", context).show();
                    $(this).addClass("active");
                    $(".renderGmaps").removeClass("active");
                });
            }
        }
    }
})(jQuery);
