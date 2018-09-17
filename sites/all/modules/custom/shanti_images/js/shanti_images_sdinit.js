(function ($) {
    $(document).ready(function() {
        var sdsel = '#sd-div';
            if ($(sdsel).data('iiifurls')) {
               var imgurls = $(sdsel).data('iiifurls').split("|$|");
               var rotation = $(sdsel).data('rotation');
               if (rotation == NaN) { rotation = 0;}
               var is_series = (imgurls.length > 1) ? true : false;
               var sdviewer = OpenSeadragon({
                    id:                              sdsel.replace('#', ''),
                    prefixUrl:                    "/sites/all/modules/custom/shanti_images/images/openseadragon/",
                    preserveViewport:       false,
                    visibilityRatio:             1,
                    minZoomLevel:            -1,
                    maxZoomLevel:           20,
                    defaultZoomLevel:       1,
                    degrees:                      rotation,
                    showNavigator:           true,
                    showRotationControl:  true,
                    sequenceMode:           is_series,
                    zoomPerScroll:            1.08,
                    zoomPerSecond:         2.0,
                    tileSources:                 imgurls
                });
            }
        });
}(jQuery));