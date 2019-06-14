//Function to process kmaps places
function processPlacesData(data) {
  //Global variable to hold all the related resources count
  shantiPlaces = {
    places_id: data.feature.id,
    places_header: data.feature.header,
    shanti_places_data: data
  };

  //Remove all content from show related pages
  $('.show-related-pages').empty();
  $('.content-section article.tab-pane').empty();

  //Removes previous binds for the show related tabs.
  $('a[href="#tab-overview"]').unbind('show.bs.tab');

  //Removes previous binds for the show related places tab.
  $('a[href="#tab-places"]').unbind('show.bs.tab');

  //Removes previous binds for the show related audio-video tab.
  $('a[href="#tab-audio-video"]').unbind('show.bs.tab');

  //Remove previous binds for the related essays tab.
  $('a[href="#tab-essays"]').unbind('show.bs.tab');

  //Remove previous binds for related subjects
  $('a[href="#tab-subjects"]').unbind('show.bs.tab');

  //Remove previous binds for related photos
  $('a[href="#tab-photos"]').unbind('show.bs.tab');

  //Remove previous binds for related texts
  $('a[href="#tab-texts"]').unbind('show.bs.tab');

  //Remove previous binds for the accordion
  $("#collapseOne").unbind('show.bs.collapse');  // note: perhaps this needs expansion options for more than 2 accordions 
  $("#collapseTwo").unbind('show.bs.collapse');

  //Change the page title to that of the new page being loaded
  $(".page-title span").html(data.feature.header);

  //Remove all the active classes from the pills so that their bind functions can trigger
  $("#sidebar-first ul.nav-pills li").removeClass("active");

  //Make the overview tab the default tab on URL Change.
  //$("a[href='#tab-overview']").click();

  //Remove all elements from Breadcrumbs and start adding them again.
  $("ol.breadcrumb li").remove();
  $("ol.breadcrumb").append('<li><a href="">Places:</a></li>');
  $.each(data.feature.parents, populatePlacesBreadcrumbs);
  $("ol.breadcrumb").append('<li>' + data.feature.header + '</li>');

  //First Hide all the elements from the left hand navigation and then show relevant ones
  $("#sidebar-first ul.nav-pills li").hide();

  //Proces the solr index for more left hand content
  var solrURL = 'http://kidx.shanti.virginia.edu/solr/kmindex/select?q=kmapid:places-' + Settings.hash_obj.id + '&fq=&start=0&facets=on&group=true&group.field=service&group.facet=true&group.ngroups=true&group.limit=0&wt=json';
  $.get(solrURL, processSubjectsSolr);

  //Get the element that we want and display to overview.
  //Show overview tab on the left hand column
  
  if (data.feature) {
    $("#sidebar-first ul.nav-pills li.overview").show();
    $('a[href="#tab-overview"]').one('show.bs.tab', function(e) {
      $.bbq.pushState({que: $(e.target).attr('href').substr(1)});
      $.bbq.removeState('nid');

      var $tabOverview = $("#tab-overview");
      $tabOverview.empty();
      if (data.feature.summaries.length > 0) {
        $tabOverview.append('<div class="summary-overview">' + data.feature.summaries[0].content + '</div>');
      }
      if (data.feature.feature_types.length > 0) {
        var featureTitle = '<h6 class="custom-inline">FEATURE TYPE:</h6>';
        $.each(data.feature.feature_types, function(ind, val) {
          featureTitle += '<a href="' + Settings.subjectsPath + "#id=" + val.id + '&que=overview-tab">';
          featureTitle += val.title;
          featureTitle += '</a>';
          if (ind < (data.feature.feature_types.length - 1)) {
            featureTitle += '; ';  
          }
        });
        featureTitle += '';
        $tabOverview.append(featureTitle);
      }

      var overviewContent = '';

      if (data.feature.illustrations.length > 0 && data.feature.illustrations[0].type =='mms') {
        overviewContent += '<div class="resource-overview-image">';
        overviewContent += '</div>';
        $.get(data.feature.illustrations[0].url, function(data) {
          var imgcontent = '<img src="' + data.picture.images[3].url + '">';
          $(".resource-overview-image").append(imgcontent);
        });
      } else if (data.feature.illustrations.length > 0 && data.feature.illustrations[0].type =='external') {
        overviewContent += '<div class="resource-overview-image">';
        overviewContent += '<img src="' + data.feature.illustrations[0].url + '">';
        overviewContent += '</div>';
      }

      if (data.feature.closest_fid_with_shapes) {
        shantiPlaces.fid = data.feature.closest_fid_with_shapes;
        overviewContent += '<div class="google-maps">';
        overviewContent += '<iframe frameborder="0" scrolling="no" marginheight="0" marginwidth="0" src="https://maps.google.com/maps?q=http:%2F%2Fplaces.thlib.org%2Ffeatures%2Fgis_resources%2F' + data.feature.closest_fid_with_shapes + '.kmz&amp;ie=UTF8&amp;t=p&amp;output=embed"></iframe>';
        overviewContent += '</div>';
        overviewContent += '<div class="btn-group btn-group-gmaps">';
        overviewContent += '<button class="btn btn-default renderGmaps active">Google Map</button>';
        overviewContent += '<button class="btn btn-default renderOpenLayerMaps">Custom Map</button>'
        overviewContent += '</div>';
      }
      overviewContent += '<div class="panel-group" id="accordion">';
      overviewContent += '<section class="panel panel-default">';
      overviewContent += '<div class="panel-heading">';
      overviewContent += '<h6>';
      overviewContent += '<a href="#collapseOne" data-toggle="collapse" data-parent="#accordion" class="accordion-toggle collapsed">';
      overviewContent += '<span class="glyphicon glyphicon-plus"></span>Names';
      overviewContent += '</a>';
      overviewContent += '</h6>';
      overviewContent += '</div>';
      overviewContent += '<div id="collapseOne" class="panel-collapse collapse">';
      overviewContent += '<div class="panel-body">';
      overviewContent += '</div>';
      overviewContent += '</div>';
      overviewContent += '</section>';

      if (data.feature.associated_resources.etymology_count > 0) {
        overviewContent += '<section class="panel panel-default">';
        overviewContent += '<div class="panel-heading">';
        overviewContent += '<h6>';
        overviewContent += '<a href="#collapseTwo" data-toggle="collapse" data-parent="#accordion" class="accordion-toggle collapsed">';
        overviewContent += '<span class="glyphicon glyphicon-plus"></span>ETYMOLOGY';
        overviewContent += '</a>';
        overviewContent += '</h6>';
        overviewContent += '</div>';
        overviewContent += '<div id="collapseTwo" class="panel-collapse collapse">';
        overviewContent += '<div class="panel-body">';
        overviewContent += '</div>';
        overviewContent += '</div>';
        overviewContent += '</section>';
      }

      overviewContent += '</div>';
      $tabOverview.append(overviewContent);

      //Render the maps based on what is clicked.
      $(".renderGmaps").click(function() {
        var googleMapsRender = '<iframe frameborder="0" scrolling="no" marginheight="0" marginwidth="0" src="https://maps.google.com/maps?q=http:%2F%2Fplaces.thlib.org%2Ffeatures%2Fgis_resources%2F' + shantiPlaces.fid + '.kmz&amp;ie=UTF8&amp;t=p&amp;output=embed"></iframe>';
        $(".google-maps").html(googleMapsRender);
        $(this).addClass('active');
        $('.renderOpenLayerMaps').removeClass('active');
      });

      $(".renderOpenLayerMaps").click(function() {
        var openLayerMapsRender = '<div id="inset_map" class="fid-' + shantiPlaces.fid + ' language-roman.popular olMap" style="width:100%; height:550px"></div>';
        $(".google-maps").html(openLayerMapsRender);
        InsetMap.init();
        $(this).addClass('active');
        $('.renderGmaps').removeClass('active');
      });

      //Trigger remote call for overview accordion Names
      $("#collapseOne").one('show.bs.collapse', function() {
        var namesURL = Settings.baseUrl + "/features/" + data.feature.id + "/names.json";
        $.get(namesURL, function(data) {
          var namesContent = '<ul>';
          $.each(data.names, function(ind1, val1) {
            namesContent += '<li>';
            namesContent += val1.name + ' (' + val1.language + ', ' + val1.writing_system + ', ' + val1.relationship + ')';
            if(val1.names.length > 0) {
              namesContent += '<ul>';
              $.each (val1.names, function(ind2, val2) {
                namesContent += '<li>';
                namesContent += val2.name + ' (' + val2.language + ', ' + val2.writing_system + ', ' + val2.relationship + ')';
                if(val2.names.length > 0) {
                  namesContent += '<ul>';
                  $.each (val2.names, function(ind3, val3) {
                    namesContent += '<li>';
                    namesContent += val3.name + ' (' + val3.language + ', ' + val3.writing_system + ', ' + val3.relationship + ')';

                    namesContent += '</li>';
                  });
                  namesContent += '</ul>';
                }
                namesContent += '</li>';
              });
              namesContent += '</ul>';
            }
            namesContent += '</li>';
          });
          namesContent += '</ul>';
          $("#collapseOne .panel-body").append(namesContent);
        });
      });

      //Trigger remote call for overview accordion Etymology
      $("#collapseTwo").one('show.bs.collapse', function() {
        var namesURL = Settings.baseUrl + "/features/" + data.feature.id + "/names.json";
        $.get(namesURL, function(data) {
          var etycontent = '';
          if(data.names[0].etymology) {
            etycontent += '<strong class="custom-inline">Etymology for ' + data.names[0].name + ': </strong>';
            etycontent += data.names[0].etymology;
          } else {
            etycontent += '';
          }
          $("#collapseTwo .panel-body").append(etycontent);
        });
      });
    });//end of show.bs.tab

  }//end of data.feature

  //Related places within places.
  if (data.feature.associated_resources.related_feature_count > 0) {
    $("ul.nav li a[href='#tab-places'] .badge").text(data.feature.associated_resources.related_feature_count);
    $("#sidebar-first ul.nav-pills li.places").show();
    $('a[href="#tab-places"]').unbind('show.bs.tab').one('show.bs.tab', function(e) {
      //Push a state to the url hash so we can bookmark it
      $.bbq.pushState({que: $(e.target).attr('href').substr(1)});
      $.bbq.removeState('nid');

      var $tabPlaces = $("#tab-places");
      $tabPlaces.empty();
      var placesURL = Settings.baseUrl + "/features/" + data.feature.id + "/related.json";
      $.get(placesURL, placesWithinPlaces);
    });
  }

  //Related essays (descriptions) section
  if (data.feature.associated_resources.description_count > 0) {
    $("ul.nav li a[href='#tab-essays'] .badge").text(data.feature.associated_resources.description_count);
    $("#sidebar-first ul.nav-pills li.essays").show();
    $('a[href="#tab-essays"]').unbind('show.bs.tab').one('show.bs.tab', function(e) {
      //Push a state to the url hash so we can bookmark it
      $.bbq.pushState({que: $(e.target).attr('href').substr(1)});
      $.bbq.removeState('nid');

      var $tabEssays = $("#tab-essays");
      $tabEssays.empty();
      var essaysURL = Settings.baseUrl + '/features/' + data.feature.id + '/descriptions/' + data.feature.descriptions[0].id + '.json';
      $.get(essaysURL, relatedPlacesEssays);
    });
  }

  //Related subjects (descriptions) section
  if (data.feature.associated_resources.subject_count > 0) {
    $("ul.nav li a[href='#tab-subjects'] .badge").text(data.feature.associated_resources.subject_count);
    $("#sidebar-first ul.nav-pills li.subjects").show();
    $('a[href="#tab-subjects"]').unbind('show.bs.tab').one('show.bs.tab', function(e) {
      //Push a state to the url hash so we can bookmark it
      $.bbq.pushState({que: $(e.target).attr('href').substr(1)});
      $.bbq.removeState('nid');

      $("#tab-subjects").empty();
      var subjectsURL = Settings.baseUrl + '/features/' + data.feature.id + '/topics.json';
      $.get(subjectsURL, relatedPlacesSubjects);
    });
  }

  //Related photos in places section
  if (data.feature.associated_resources.picture_count > 0) {
    $("ul.nav li a[href='#tab-photos'] .badge").text(data.feature.associated_resources.picture_count);
    $("#sidebar-first ul.nav-pills li.photos").show();
    $('a[href="#tab-photos"]').unbind('show.bs.tab').one('show.bs.tab', function(e) {
      //Push a state to the url hash so we can bookmark it
      $.bbq.pushState({que: $(e.target).attr('href').substr(1)});
      $.bbq.removeState('nid');

      var $tabPhotos = $("#tab-photos");
      $tabPhotos.empty();
      var photosURL = Settings.mmsUrl + "/places/" + data.feature.id + "/pictures.json?per_page=30";
      shantiPlaces.photosURL = photosURL;
      shantiPlaces.feature_id = data.feature.id;
      shantiPlaces.total_pages = parseInt(data.feature.associated_resources.picture_count / 32);
      //$.get(photosURL, relatedPhotos);

      $.ajax({
        url: photosURL,
        beforeSend: function(xhr) {
          $('li.photos i').removeClass('icon shanticon-images').addClass('icon shanticon-spinner');
        }
      })
      .done(relatedPlacesPhotos)
      .always(function() {
        $('li.photos i').removeClass('icon shanticon-spinner').addClass('icon shanticon-images');
      });
    });
  }

  //Related Texts section
  if (data.feature.associated_resources.document_count > 0) {
    $("ul.nav li a[href='#tab-texts'] .badge").text(data.feature.associated_resources.document_count);
    $("#sidebar-first ul.nav-pills li.texts").show();
    $('a[href="#tab-texts"]').unbind('show.bs.tab').one('show.bs.tab', function(e) {
      //Push a state to the url hash so we can bookmark it
      $.bbq.pushState({que: $(e.target).attr('href').substr(1)});
      $.bbq.removeState('nid');

      var $tabTexts = $("#tab-texts");
      $tabTexts.empty();
      $tabTexts.append('<h6>Texts in ' + data.feature.header + '</h6>');
      var textsURL = Settings.mmsUrl + "/places/" + data.feature.id + "/documents.json";
      $.get(textsURL, relatedPlacesTexts);
    });
  }
}

//Populate Breadcrumbs
function populatePlacesBreadcrumbs(bInd, bVal) {
  $breadcrumbOl = $("ol.breadcrumb");
  $breadcrumbOl.append('<li><a href="#id=' + bVal.id + '&que=overview-tab">' + bVal.header + '</a><span class="icon shanticon-angle-right"></span></li>');
}

//Function to show related photos in places
function relatedPlacesPhotos(data) {
  var $tabPhotos = $("#tab-photos");
  $tabPhotos.empty();
  $tabPhotos.append('<h6>Photographs in ' + shantiPlaces.shanti_places_data.feature.header + '</h6>');
  
  var contentPh = '<div class="related-photos">';

  //First get and show photos from sharedshelf
  // var sharedShelfURL = location.href.substr(0, location.href.lastIndexOf('subjects')) + 'sharedshelf/api/projects/534/assets/filter/fd_24809_lookup.links.source_id/' + shantiPlaces.feature_id + '.json';
  // $.get(sharedShelfURL, function(ssData) {
  //   console.log(ssData);
  // });

  $.each(data.place.media, function(rInd, rElm) {
    contentPh += '<div class="each-photo">';
    contentPh += '<a href="#pid' + rElm.id + '" data-toggle="modal">';
    contentPh += '<img src="' + rElm.images[0].url + '"  alt="' + (rElm.captions.length > 0 ? rElm.captions[0].title : "") + '">';
    contentPh += '</a>';
    contentPh += '</div>';

    //Modal for each photo
    contentPh += '<div class="modal fade" tabindex="-1" role="dialog" id="pid' + rElm.id + '">';
    contentPh += '<div class="modal-dialog">';
    contentPh += '<div class="modal-content">';
    contentPh += '<div class="modal-header">';
    contentPh += '<button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>';
    contentPh += '<p class="modal-title" id="myModalLabel">' + (rElm.captions.length > 0 ? rElm.captions[0].title : "") + '</p>';
    contentPh += '</div>';
    contentPh += '<div class="modal-body">';
    contentPh += '<img src="' + rElm.images[4].url + '" alt="' + (rElm.captions.length > 0 ? rElm.captions[0].title : "") + '">';
    contentPh += '<p><strong>Resource #:</strong> ' + rElm.id + '</p>';
    contentPh += '<p><strong>Description:</strong></p>';
    contentPh += (rElm.descriptions.length > 0 ? rElm.descriptions[0].title : "");
    contentPh += '<p><strong>Copyright holder:</strong> ' + (rElm.copyrights.length > 0 ? rElm.copyrights[0].copyright_holder.title : "") + '</p>';
    contentPh += '<p><strong>Photographer:</strong> ' + (rElm.photographer.hasOwnProperty('fullname') ? rElm.photographer.fullname : "") + '</p>';
    contentPh += '</div>';
    contentPh += '</div>';
    contentPh += '</div>';
    contentPh += '</div>';
  });

  contentPh += '</div>';

  contentPh += '<table class="pagerer">';
  contentPh += '<tbody>';
  contentPh += '<tr>';
  contentPh += '<td class="pagerer pagerer-right">';
  contentPh += '<div class="pagerer-pager">';
  contentPh += '<ul id="photo-pagination" class="pager">';
  contentPh += '<li class="pager-first first"><a href="' + shantiPlaces.photosURL + '&page=1' + '"><span class="icon"></span></a></li>';
  contentPh += '<li class="pager-previous"><a href="' + shantiPlaces.photosURL + '&page=1' + '"><span class="icon"></span></a></li>';
  contentPh += '<li class="pager-item">Page</li>';
  contentPh += '<li class="pager-item widget active"><input type="text" value="1" class="pagerer-page"></li>';
  contentPh += '<li class="pager-item">Of ' + shantiPlaces.total_pages + '</li>';
  contentPh += '<li class="pager-next active"><a href="' + shantiPlaces.photosURL + '&page=2' + '"><span class="icon"></span></a></li>';
  contentPh += '<li class="pager-last active last"><a href="' + shantiPlaces.photosURL + '&page=' + shantiPlaces.total_pages + '"><span class="icon"></span></a></li>';
  contentPh += '</ul>';
  contentPh += '</div>';
  contentPh += '</td>';
  contentPh += '</tr>';
  contentPh += '</tbody>';
  contentPh += '</table>';

  // contentPh += '<div class="paginated-spin"><span class="fa fa-spinner"></span></div>';
  
    $("#tab-photos").append(contentPh);

  //Add the event listener for the first-page element
  $("li.pager-first a").click(function(e) {
    e.preventDefault();
    var currentTarget = $(e.currentTarget).attr('href');
    $.ajax({
      url: currentTarget,
      beforeSend: function(xhr) {
        // $('.paginated-spin i.fa').addClass('fa-spin');
        // $('.paginated-spin').show();
      }
    })
    .done(paginatedPlacesPhotos)
    .always(function() {
      // $('.paginated-spin span').removeClass('fa-spin');
      // $('.paginated-spin').hide();
      $('li input.page-input pagerer-page').val('1');
      $('li.pager-previous a').attr('href', currentTarget);
      var nextTarget = currentTarget.substr(0, currentTarget.lastIndexOf('=') + 1) + 2;
      $('li.pager-next a').attr('href', nextTarget);
    });
  });

  //Add the listener for the previous-page element
  $("li.pager-previous a").click(function(e) {
    e.preventDefault();
    var currentTarget = $(e.currentTarget).attr('href');
    currentTarget = currentTarget.substr(0, currentTarget.lastIndexOf('=') + 1);
    var newpage = parseInt($('li input.page-input pagerer-page').val()) - 1;
    if (newpage < 1) { newpage = 1; }
    var currentURL = currentTarget + newpage;
    var previousTarget = currentTarget + ((newpage - 1) < 1 ? 1 : (newpage - 1));
    var nextTarget = currentTarget + ((newpage + 1) > parseInt(shantiPlaces.total_pages) ? shantiPlaces.total_pages : (newpage + 1));
    $.ajax({
      url: currentURL,
      beforeSend: function(xhr) {
        // $('.paginated-spin span.fa').addClass('fa-spin');
        // $('.paginated-spin').show();
      }
    })
    .done(paginatedPlacesPhotos)
    .always(function() {
      // $('.paginated-spin span').removeClass('fa-spin');
      // $('.paginated-spin').hide();
      $('li input.page-input pagerer-page').val(newpage);
      $(e.currentTarget).attr('href', previousTarget);
      $('li.pager-next a').attr('href', nextTarget);
    });
  });

  //Add the listener for the next-page element
  $("li.pager-next a").click(function(e) {
    e.preventDefault();
    var currentTarget = $(e.currentTarget).attr('href');
    currentTarget = currentTarget.substr(0, currentTarget.lastIndexOf('=') + 1);
    var newpage = parseInt($('li input.page-input pagerer-page').val()) + 1;
    if (newpage > parseInt(shantiPlaces.total_pages)) { newpage = parseInt(shantiPlaces.total_pages); }
    var currentURL = currentTarget + newpage;
    var previousTarget = currentTarget + ((newpage - 1) < 1 ? 1 : (newpage - 1));
    var nextTarget = currentTarget + ((newpage + 1) > parseInt(shantiPlaces.total_pages) ? shantiPlaces.total_pages : (newpage + 1));
    $.ajax({
      url: currentURL,
      beforeSend: function(xhr) {
        // $('.paginated-spin span.fa').addClass('fa-spin');
        // $('.paginated-spin').show();
      }
    })
    .done(paginatedPlacesPhotos)
    .always(function() {
      // $('.paginated-spin span').removeClass('fa-spin');
      // $('.paginated-spin').hide();
      $('li input.page-input pagerer-page').val(newpage);
      $('li.pager-previous a').attr('href', previousTarget);
      $(e.currentTarget).attr('href', nextTarget);
    });
  });

  //Add the listener for the pager text input element
  $("li input.page-input pagerer-page").change(function(e) {
    e.preventDefault();
    var currentTarget = shantiPlaces.photosURL + '&page=';
    var newpage = parseInt($(this).val());
    if (newpage > parseInt(shantiPlaces.total_pages)) { newpage = parseInt(shantiPlaces.total_pages); }
    if (newpage < 1) { newpage = 1; }
    var currentURL = currentTarget + newpage;
    var previousTarget = currentTarget + ((newpage - 1) < 1 ? 1 : (newpage - 1));
    var nextTarget = currentTarget + ((newpage + 1) > parseInt(shantiPlaces.total_pages) ? shantiPlaces.total_pages : (newpage + 1));
    $.ajax({
      url: currentURL,
      beforeSend: function(xhr) {
        // $('.paginated-spin i.fa').addClass('fa-spin');
        // $('.paginated-spin').show();
      }
    })
    .done(paginatedPlacesPhotos)
    .always(function() {
      // $('.paginated-spin span').removeClass('fa-spin');
      // $('.paginated-spin').hide();
      $('li input.page-input pagerer-page').val(newpage);
      $('li.pager-previous a').attr('href', previousTarget);
      $('li.pager-next a').attr('href', nextTarget);
    });
  });

  //Add the event listener for the last-page element
  $("li.pager-last a").click(function(e) {
    e.preventDefault();
    var currentTarget = $(e.currentTarget).attr('href');
    var newpage = parseInt(shantiPlaces.total_pages);
    var previousTarget = shantiPlaces.photosURL + (newpage - 1);
    $.ajax({
      url: currentTarget,
      beforeSend: function(xhr) {
        // $('.paginated-spin i.fa').addClass('fa-spin');
        // $('.paginated-spin').show();
      }
    })
    .done(paginatedPlacesPhotos)
    .always(function() {
      // $('.paginated-spin span').removeClass('fa-spin');
      // $('.paginated-spin').hide();
      $('li input.page-input pagerer-page').val(newpage);
      $('li.pager-previous a').attr('href', previousTarget);
      $('li.pager-next a').attr('href', currentTarget);
    });
  });
}

//Function to process and show the paginated photos in places
function paginatedPlacesPhotos(data) {
  var paginatedContent = $("#tab-photos .related-photos");

  var contentPh = '';
  $.each(data.place.media, function(rInd, rElm) {
    contentPh += '<div class="each-photo">';
    contentPh += '<a href="#pid' + rElm.id + '" data-toggle="modal">';
    contentPh += '<img src="' + rElm.images[0].url + '" alt="' + (rElm.captions.length > 0 ? rElm.captions[0].title : "") + '">';
    contentPh += '</a>';
    contentPh += '</div>';

    //Modal for each photo
    contentPh += '<div class="modal fade" tabindex="-1" role="dialog" id="pid' + rElm.id + '">';
    contentPh += '<div class="modal-dialog">';
    contentPh += '<div class="modal-content">';
    contentPh += '<div class="modal-header">';
    contentPh += '<button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>';
    contentPh += '<p class="modal-title" id="myModalLabel">' + (rElm.captions.length > 0 ? rElm.captions[0].title : "") + '</p>';
    contentPh += '</div>';
    contentPh += '<div class="modal-body">';
    contentPh += '<img src="' + rElm.images[4].url + '" alt="' + (rElm.captions.length > 0 ? rElm.captions[0].title : "") + '">';
    contentPh += '<p><strong>Resource #:</strong> ' + rElm.id + '</p>';
    contentPh += '<p><strong>Description:</strong></p>';
    contentPh += (rElm.descriptions.length > 0 ? rElm.descriptions[0].title : "");
    contentPh += '<p><strong>Copyright holder:</strong> ' + (rElm.copyrights.length > 0 ? rElm.copyrights[0].copyright_holder.title : "") + '</p>';
    contentPh += '<p><strong>Photographer:</strong> ' + (rElm.hasOwnProperty('photographer') ? rElm.photographer.fullname : "") + '</p>';
    contentPh += '</div>';
    contentPh += '</div>';
    contentPh += '</div>';
    contentPh += '</div>';
  });
  paginatedContent.empty().html(contentPh);
}

//Function to show related subjects in places
function relatedPlacesSubjects(data) {
  var subjectsContent = '';
  var $tabSubjects = $('#tab-subjects');
  $tabSubjects.empty();
  if (data.feature.feature_types.length > 0) {
    var subjectsContent = '<h6>FEATURE TYPES:</h6>';
    subjectsContent += '<ul>';
    $.each(data.feature.feature_types, function(ind, val) {
      subjectsContent += '<li><a href="' + Settings.subjectsPath + "#id=" + val.id + '&que=overview-tab">';
      subjectsContent += val.title;
      subjectsContent += '</a></li>';
    });
    subjectsContent += '</ul>';
  }

  if (data.feature.category_features.length > 0) {
    subjectsContent += '<div><h6>SUBJECTS</h6><ul>';
    $.each(data.feature.category_features, function(ind, val) {
      subjectsContent += '<li>';
      subjectsContent += val.root.title + ' > ' + '<a href="' + Settings.subjectsPath + '#id=' + val.category.id + '&que=overview-tab">' + val.category.title + '</a>';
      if (val.numeric_value) {
        subjectsContent += ': ' + val.numeric_value;
      }
      if (val.string_value) {
        subjectsContent += ': ' + val.string_value;
      }
      subjectsContent += '</li>';
    });
    subjectsContent += '</ul></div>';
  }

  $tabSubjects.append(subjectsContent);
}

//Function to show the related places within kmap places
function placesWithinPlaces(data) {
  $("#tab-places").empty();
  var contentPlaces = '';
  $.each(data.feature_relation_types, function(ind1, val1) {
    contentPlaces += '<h6>' + shantiPlaces.places_header + ' ' + val1.label + ' (' + val1.count + '):</h6>';
    contentPlaces += '<ul>';
    $.each(val1.categories, function(ind2, val2) {
      contentPlaces += '<li>' + val2.header + ' (' + val2.features.length + ')';
      contentPlaces += '<ul>';
      $.each(val2.features, function(ind3, val3) {
        contentPlaces += '<li><a href="' + Settings.placesPath + '#id=' + val3.id + '&que=overview-tab">';
        contentPlaces += val3.header;
        contentPlaces += '</a></li>';
      });
      contentPlaces += '</ul>';
      contentPlaces += '</li>';
    });
    contentPlaces += '</ul>';
  });

  $("#tab-places").append(contentPlaces);
}

//Function to show related places Essays
function relatedPlacesEssays(data) {
  var contentES = '<div class="related-essays">';

  var monthNames = [ "January", "February", "March", "April", "May", "June",
  "July", "August", "September", "October", "November", "December" ];
  var createdDate = new Date(Date.parse(data.description.created_at));
  var showDate = monthNames[createdDate.getMonth()] + ' ' + createdDate.getDate() + ', ' + createdDate.getFullYear();
  if (data.description.title) {
    contentES += '<h6>' + (data.description.title ? data.description.title : "") + ' <small>by ' + (data.description.author ? data.description.author.fullname : "") + ' (' + showDate + ')</small>' + '</h6>';
  }
  if (!data.description.title) {
    contentES += '<div class="summary-overview">' + data.description.content + '</div>';
  } else {
    contentES += data.description.content;
  }

  contentES += '</div>';

  $("#tab-essays").append(contentES);
}

//Function to process and show related texts
function relatedPlacesTexts(data) {
  var contentTX = '<div class="related-texts text-in-places kmaps-list-columns">';

  $.each(data.place.media, function(mInd, mElm) {
    $.get(Settings.mmsUrl + '/media_objects/' + mElm.id + '.json', function(data) {
      if (data.document.images) {
        var contentTX = '<div class="each-text">';
        contentTX += '<a href="#pid' + data.document.id + '" data-toggle="modal">';
        contentTX += '<img src="' + data.document.images[1].url + '" alt="' + (data.document.captions.length > 0 ? data.document.captions[0].title : "") + '">';
        contentTX += '</a>';
        contentTX += '</div>';

        //Modal for each photo
        contentTX += '<div class="modal fade" tabindex="-1" role="dialog" id="pid' + data.document.id + '">';
        contentTX += '<div class="modal-dialog">';
        contentTX += '<div class="modal-content">';
        contentTX += '<div class="modal-header">';
        contentTX += '<button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>';
        contentTX += '<p class="modal-title" id="myModalLabel">' + (data.document.captions.length > 0 ? data.document.captions[0].title : "") + '</p>';
        contentTX += '</div>';
        contentTX += '<div class="modal-body">';
        contentTX += '<img src="' + data.document.images[6].url + '" alt="' + (data.document.captions.length > 0 ? data.document.captions[0].title : "") + '">';
        contentTX += '<p><strong>Resource #:</strong> ' + data.document.id + '</p>';
        contentTX += '</div>';
        contentTX += '</div>';
        contentTX += '</div>';
        contentTX += '</div>';
        $(".related-texts").append(contentTX);
      }
    });
  });

  contentTX += '</div>';

  $("#tab-texts").append(contentTX);
}

//Recursive function to build and return nested names
function buildNames(obj) {
  var retContent = '';
  if(obj.names && obj.names.length > 0) {
    retContent += '<ul>';
    $.each(obj.names, function(ind, val) {
      retContent += '<li>';
      retContent += val.name + ' (' + val.language + ', ' + val.writing_system + ', ' + val.relationship + ')';
      retContent += '</li>';
    });
    retContent += '</ul>';
    return retContent;
  } else {
    return retContent;
  }
}

/*
//Initiate open layer maps
jQuery(function ($) {
  $( document ).ready(function() {
    InsetMap.init();
  });
});

*/












