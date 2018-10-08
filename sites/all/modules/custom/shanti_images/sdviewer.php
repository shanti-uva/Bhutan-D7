<html>
    <head>
        <title>Test of SeaDragon</title>
        <script type="text/javascript" src="https://images.dd:8443/sites/all/modules/contrib/jquery_update/replace/jquery/1.10/jquery.min.js?v=1.10.2"></script>
        <script type="text/javascript" src="https://images.dd:8443/sites/all/modules/custom/shanti_images/js/openseadragon.js"></script>
        <script type="text/javascript">
        (function ($) {
                $(document).ready(function() {
                    console.log("Starting seadragon. Using .json url");
                    var jsonurl = window.location.search.replace('?json=','');
                    console.log(jsonurl);
                       var sdviewer = OpenSeadragon({
                            id: "sd-div",
                            prefixUrl: "/sites/all/modules/custom/shanti_images/images/openseadragon/",
                            preserveViewport: true,
                            visibilityRatio:    1,
                            minZoomLevel:       1,
                            defaultZoomLevel:   1,
                            sequenceMode:       true,
                            tileSources:  [ 
                                jsonurl
                            ]
                     });
                });
            })(jQuery);
        </script>
    </head>
    <body>
        <p>This is iT!:</p>
        <div id="sd-div">
        </div>
    </body><!-- "https://images.dd:8443/sites/all/modules/custom/shanti_images/js/iiif-image-info.json" -->
</html>
