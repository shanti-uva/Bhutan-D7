var skEditor;

$ = jQuery;

/*CKEDITOR.on('dialogDefinition', function (ev) {
    var dialogName = ev.data.name;
    var dialogDefinition = ev.data.definition;

    dialogDefinition.onShow = function() {
        var x_pos = (this.getPosition().x * 1);
        var y_pos = (this.getPosition().y * 1) + 200;
        this.move(x_pos, y_pos); // Top center
    };
});*/

CKEDITOR.dialog.add( 'ksolrdialog', function( editor ) {
	return {
		title: 'Add Mandala resource',
		minWidth: 960,
		contents: [{
			id: 'dialogContent',
			elements: [	{
                    type: 'html',
                    html: '<iframe src="/sites/all/libraries/ckeditor/plugins/ksolr/ksolr-modal.html" style="width:100%;height:640px;margin-top:-90px"></iframe>'
                	}],
			}],
		onLoad: function() {
			if (window.addEventListener) 											// If supported this way
				window.addEventListener("message",kSolrHandler,false);				// Add event handler
			else																	// Use other method
			window.attachEvent("message",kSolrHandler);								// Add handler
			skEditor=editor;
			currdia = CKEDITOR.dialog.getCurrent();
		},
		onOk: function() {}
		};
	});


	function trace(msg)
	{
		console.log(msg);
	}

	function kSolrHandler(e)													// ON KSOLR EVENT
	{
		if (e.data && e.data.match(/kSolrMsg/)) {									// Message from kmap
			var src="";
			var o=$.parseJSON(e.data.substr(9));									// Objectify
			//console.log(o);
			//console.log(o.asset_type);
			if (o.asset_type == "audio-video") {
                 if (o.url_ajax)   {
                   var host = window.location.host;
                    var title = (typeof(o.title) != 'undefined') ? o.title : '';
                   skEditor.insertHtml('<h2>' + title + '</h2><iframe frameborder="0" scrolling="no" src="'+o.url_ajax+'/player" width="560" height="395" allowfullscreen webkitallowfullscreen mozAllowFullScreen frameborder="0"></iframe>');   // Add iframe to text
                  }
            }
			else if (o.asset_type == "picture" || o.asset_type == "images") {										// Picture asset 
				if (o.url_large) 		src=o.url_large;							// Large
				else if (o.url_normal) 	src=o.url_normal;							// Normal
				else if (o.url_thumb) 	src=o.url_thumb;							// Thumb

				if (src) {				              									// If something
				    if (src.indexOf('iiif') > -1) { src = src.replace('!200,200', '!400,400'); }
				    var caption = (typeof(o.caption) != 'undefined') ? o.caption : '';
				    //console.log("src is: " + src);
				    src = src.replace('http://', '//');
					skEditor.insertHtml('<div><img src="'+src+'" width="400" /><p><em>' + caption + '</em></p></div>');			// Add image to text
				} else {
				    console.log('no src for image input');
				}
			}
			else if (o.asset_type == "sources") {									// Sources asset
			    var ajax_url = o.url_ajax;
			    var cite_url = ajax_url.replace('/ajax/', '/embed/') + '/cite';
			    var host = window.location.host;
			    if (host.indexOf('.dd') > -1 ) {
        			    cite_url = cite_url.replace('sources-dev.shanti.virginia.edu', 'sources.dd:8443');
        			}
			    $.ajax({
			        url: cite_url,
			        dataType:  "jsonp",
			        jsonpCallback: "cite",
			        success: function(data) {
                        skEditor.insertHtml(data);   
			        }
			    });
	        } 
	        else if (o.asset_type == "texts") {
                    var title = (typeof(o.title) != 'undefined') ? o.title : '';
	             skEditor.insertHtml('<h2>' + title + '</h2><iframe frameborder="0" scrolling="no" src="'+o.url_ajax+'" width="700" height="600" allowfullscreen webkitallowfullscreen mozAllowFullScreen frameborder="0"></iframe>');   // Add iframe to text
	        } 
            else if (o.asset_type == "visuals") {
                 var ajax_url = o.url_ajax;
                 var cite_url = ajax_url + '/jsonp';
                 var host = window.location.host;
                 if (host.indexOf('.dd') > -1 ) {
                        cite_url = cite_url.replace('-dev.shanti.virginia.edu', '.dd:8443');
                 }
                 $.ajax({
                    url: cite_url,
                    dataType:  "jsonp",
                    jsonpCallback: "cite",
                    success: function(data) {
                        skEditor.insertHtml( data);   
                    }
                 });
           }
			else{																	// Anthing else (IIIF IMages?)
				if (o.url_thumb) 	{												// Use thumb 
					skEditor.insertHtml('<iframe frameborder="0 scrolling="no" src="'+o.url_thumb+'" width="300"></iframe>');	// Add iframe to text
				}
			}
            currdia = CKEDITOR.dialog.getCurrent();
            currdia.hide();
		}
	}