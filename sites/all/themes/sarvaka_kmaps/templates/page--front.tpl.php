<div class="wrap-all">
   <span class="sr-only"><a href=".main-content">Skip to main content</a> <a href="#search-flyout">Skip to search</a></span>
    <!-- Header Region -->
   <div class="site-banner">
    <div class="navbar navbar-default">

	      <nav class="navbar-buttons">
	        <span class="menu-icon menu-toggle" role="button" aria-label="Main Menu"><a href="#"><span class="sr-only">Main Menu</span><span class="icon shanticon-menu"></span></a></span><!-- desktop > 768 drilldown menu : main-menu -->
	        <span class="menu-explore menu-exploretoggle" role="button" aria-label="Explore Collections"><a href="#"><span>Explore</span><span class="icon shanticon-directions"></span></a></span><!-- mobile < 768 : collections -->
	      </nav>

	      <h1 class="navbar-header<?php if(!$variables['shanti_site']) { print " default"; } ?>">

	          <?php if($variables['shanti_site']): ?>
              <a href="<?php echo $front_page; ?>" class="logo-brand navbar-brand">
                <span class="icon shanticon-logo"></span>
                <span class="mandala">Mandala <em></em></span>
                <?php if($variables['use_admin_site_title']) {
                    print "<span class=\"site-title\">{$site_name}</span>";
                }
                ?>
              </a>

            <?php else: ?>

              <a href="<?php print $variables['home_url']; ?>" class="navbar-brand" title="<?php print $site_name; ?> Homepage">
	            <img src="<?php print $logo; ?>" class="site-logo" />
                <span class="site-title"><?php print $site_name; ?></span>
              </a>

	          <?php endif; ?>

            <a href="<?php print $variables['home_url']; ?>" class="navbar-brand" title="<?php print $site_name; ?> Homepage">
	            <?php if ($site_slogan) {
                    print '<span class="site-slogan">';
                    print $site_slogan;
                    print '</span>';
                    print '<span class="site-slogan development">' . $site_env_context . '</span>';
              }?>
	          </a>
	      </h1>

	      <!-- HEADER REGION -->
	      <nav id="sarvaka-header" class="region navbar-collapse collapse navtop"> <!-- desktop display > 768 -->
	         <form class="form">
	         <fieldset>
	          <ul class="nav navbar-nav navbar-right">
		            <!-- If admin puts blocks in  header, render here -->
		            <?php print render($page['header']);  ?>
	          </ul>
	         </fieldset>
	         </form>
	       </nav>
	       <!-- End of HEADER region -->
     </div>
     <!-- include shanti-explore-menu if it exists -->
     <?php if(module_exists('explore_menu')) { print render($variables['explore_menu']); } ?>
    </div>


    <!-- Begin Content Region -->
    <main class="main-wrapper container-fluid">
      <article class="main-content" role="main">
        <section class="row" role="banner">

          <!-- Banner Region -->
          <div class="titlearea banner<?php print $variables['banner_class']; ?>">
           <div>
             <header role="banner">
                <h1 class="page-title"><span class="icon shanticon-stack"></span><span class="page-title-text">
                <?php
                	if(!empty($variables['default_title']) && !empty($variables['prefix_default_title'])) {
                		print ($title == '')? $variables['default_title'] : $variables['default_title'] . ': ' . $title;
                	} else {
                		print ($title == '')? $variables['default_title']:$title;
                	}
                  ?></span>
                </h1>
              </header>
              <nav class="breadwrap" style="display:none;">
                <?php print theme('breadcrumb', array('breadcrumb' => $breadcrumb)); ?>
              </nav>
              <div class="banner-content">
                <?php print render($page['banner']); ?>
              </div>
              <div class="banner-tabs">
                <?php
                  // For view/edit tabs
                  print render($tabs);
                ?>
              </div>
            </div>
          </div>

        </section> <!-- End of Banner Row -->


        <!-- Begin Content Row -->
        <section class="row row-offcanvas<?php print " $offcanvas_trigger_sb"; ?>" role="main">

          <!-- Sidebar First Region -->
          <?php if ($page['sidebar_first']): ?>
            <section id="sidebar-first" class="region sidebar sidebar-first sidebar-offcanvas<?php print " $bsclass_sb1"; ?> ">
              <?php print render($page['sidebar_first']); ?>
            </section>
          <?php endif; ?>

          <!-- Begin Page Content -->
          <section class="content-section <?php if (!empty($bsclass_main)) { print " $bsclass_main"; } ?> ">

		        <button type="button" class="btn btn-default view-offcanvas-sidebar" data-toggle="offcanvas" style="display:none;">
	            <span class="icon"></span>
	          </button>

          	<!-- Message Area -->
          	<?php if (!empty($messages)) { print "<div class=\"messages\">$messages</div>"; } ?>

          	<!-- Main Content -->
            <div class="tab-content container-fluid">
              <article class="tab-pane main-col active" id="tab-overview">
              	 <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
                 <?php print render($page['content']); ?>
                 <div class="block block-system">
                     <div class="content">
                         <div class="node node-page clearfix">

                             <!-- BEGIN NAVBAR -->
								<div class="btn-group btn-group-justified" role="group" aria-label="...">

								  <div class="btn-group" role="group">
								     <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Search Kmaps <span class="caret"></span>
								  </button>
								  <ul class="dropdown-menu">
								    <li><a href="https://mandala.shanti.virginia.edu/places">Knowledge Maps - Places</a></li>
								    <li><a href="https://mandala.shanti.virginia.edu/subjects">Knowledge Maps - Subjects</a></li>
								    <li role="separator" class="divider"></li>
								    <li><a href="https://wiki.shanti.virginia.edu/display/KB/Mandala+Suite+of+Tools" target="_blank">Help Documentation</a></li>
								  </ul>
								  </div>

								  <div class="btn-group" role="group">
								     <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Audio-Video <span class="caret"></span>
								  </button>
								  <ul class="dropdown-menu">
								    <li><a href="https://audio-video.shanti.virginia.edu/">Home Audio-Video</a></li>
								    <li><a href="https://audio-video.shanti.virginia.edu/collections/all">View Collections</a></li>
								    <li><a href="https://audio-video.shanti.virginia.edu/">Search Audio-Video</a></li>
								    <li role="separator" class="divider"></li>
								    <li><a href="https://wiki.shanti.virginia.edu/display/KB/Audio-Video+in+Mandala" target="_blank">Help Documentation</a></li>
								  </ul>
								  </div>

								  <div class="btn-group" role="group">
								     <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Texts <span class="caret"></span>
								  </button>
								  <ul class="dropdown-menu">
								    <li><a href="https://texts.shanti.virginia.edu/">Home Texts</a></li>
								    <li><a href="https://texts.shanti.virginia.edu/collections/all">View Collections</a></li>
								    <li><a href="https://texts.shanti.virginia.edu/">Search Texts</a></li>
								    <li role="separator" class="divider"></li>
								    <li><a href="https://wiki.shanti.virginia.edu/display/KB/Texts+in+Mandala" target="_blank">Help Documentation</a></li>
								  </ul>
								  </div>

								  <div class="btn-group" role="group">
								     <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Visuals <span class="caret"></span>
								  </button>
								  <ul class="dropdown-menu">
								    <li><a href="https://visuals.shanti.virginia.edu/">Home Visuals</a></li>
								    <li><a href="https://visuals.shanti.virginia.edu/collections/all">View Collections</a></li>
								    <li><a href="https://visuals.shanti.virginia.edu/">Search Visuals</a></li>
								    <li role="separator" class="divider"></li>
								    <li><a href="https://wiki.shanti.virginia.edu/display/KB/Visuals+in+Mandala" target="_blank">Help Documentation</a></li>
								  </ul>
								  </div>

								  <div class="btn-group" role="group">
								     <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Sources <span class="caret"></span>
								  </button>
								  <ul class="dropdown-menu">
								    <li><a href="https://sources.shanti.virginia.edu/">Home Sources</a></li>
								    <li><a href="https://sources.shanti.virginia.edu/">Search Sources</a></li>
								    <li role="separator" class="divider"></li>
								    <li><a href="https://wiki.shanti.virginia.edu/display/KB/Sources+in+Mandala" target="_blank">Help Documentation</a></li>
								  </ul>
								  </div>

								<!--
								  <div class="btn-group" role="group">
								     <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Images <span class="caret"></span>
								  </button>
								  <ul class="dropdown-menu">
								    <li><a href="#">Home Images</a></li>
								    <li><a href="#">View Collections</a></li>
								    <li><a href="#">Search Images</a></li>
								    <li role="separator" class="divider"></li>
								    <li><a href="https://wiki.shanti.virginia.edu/display/KB/Images+in+Mandala" target="_blank">Help Documentation</a></li>
								  </ul>
								  </div>
								-->
						        </div><!-- close button group justified -->
						<!-- END NAVBAR -->



			<div class="homepage-main-content">
			    <!-- BEGIN CARDS -->
			    <div class="wrap">

			        <div class="flip center">
			            <div class="card">
			                <div class="face front">
			                    <span class="icon shanticon-magnify"></span>
			                    <span class="name">Knowledge Maps</span>
			                </div>
			                <div class="face back">
			                    <span class="icon shanticon-magnify"></span>
			                    <div>
			                        <div class="back-wrap-top">
			                            <a href="https://mandala.shanti.virginia.edu/places">
			                                <span class="icon shanticon-places"></span>
			                                <span class="apptitle">Places</span>
			                            </a>
			                        </div>

			                        <div class="back-wrap-bottom">
			                            <a href="https://mandala.shanti.virginia.edu/subjects">
			                                <span class="icon shanticon-subjects"></span>
			                                <span class="apptitle">Subjects</span>
			                            </a>
			                        </div>
			                    </div>
			                </div>
			            </div>
			        </div>

			         <div class="flip deg45">
			            <div class="card">
			                <div class="face front">
			                    <span class="icon shanticon-sources"></span>
			                    <span class="name">Sources</span>
			                </div>
			                <div class="face back">
			                    <div>
			                       <span class="icon shanticon-sources"></span>
			                        <ul>
			                            <li><a href="https://sources.shanti.virginia.edu/">Sources Home</a></li>
			                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Sources+in+Mandala" target="_blank">Contribute</a></li>
			                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Mandala+Suite+of+Tools" target="_blank">FAQ</a></li>
			                        </ul>
			                    </div>
			                </div>
			            </div>
			        </div>

			         <div class="flip deg135">
			            <div class="card">
			                <div class="face front">
			                    <span class="icon shanticon-visuals"></span>
			                    <span class="name">Visuals</span>
			                </div>
			                <div class="face back">
			                    <div>
			                       <span class="icon shanticon-visuals"></span>
			                        <ul>
			                            <li><a href="https://visuals.shanti.virginia.edu/">Visuals Home</a></li>
			                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Create+a+Visualization" target="_blank">Contribute</a></li>
			                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Mandala+Suite+of+Tools" target="_blank">FAQ</a></li>
			                        </ul>
			                    </div>
			                </div>
			            </div>
			        </div>

			        <div class="flip deg225">
			            <div class="card">
			                <div class="face front">
			                    <span class="icon shanticon-texts"></span>
			                    <span class="name">Texts</span>
			                </div>
			                <div class="face back">
			                    <div>
			                      <span class="icon shanticon-texts"></span>
			                        <ul>
			                            <li><a href="https://texts.shanti.virginia.edu/">Texts Home</a></li>
			                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Create+Texts " target="_blank">Contribute</a></li>
			                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Mandala+Suite+of+Tools" target="_blank">FAQ</a></li>
			                        </ul>
			                    </div>
			                </div>
			            </div>
			        </div>

			        <div class="flip deg315">
			            <div class="card">
			                <div class="face front">
			                    <span class="icon shanticon-audio-video"></span>
			                    <span class="name">Audio-Video</span>
			                </div>
			                <div class="face back">
			                    <div>
			                      <span class="icon shanticon-audio-video"></span>
			                        <ul>
			                            <li><a href="https://audio-video.shanti.virginia.edu/">AV Home</a></li>
			                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Start+in+Audio-Video" target="_blank">Contribute</a></li>
			                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Mandala+Suite+of+Tools" target="_blank">FAQ</a></li>
			                        </ul>
			                    </div>
			                </div>
			            </div>
			        </div>

			    </div> <!-- END Cards -->



			    <div class="homepage-intro-text">

			        <h1>Explore the Mandala Collections</h1>

			        <p class="bullet">Mandala Collections are scholarly repositories of <a href="https://texts.shanti.virginia.edu">Texts</a>, <a href="https://audio-video.shanti.virginia.edu">Audio-video</a>, <a href="https://images.shanti.virginia.edu">Images</a>, <a href="https://sources.shanti.virginia.edu">Bibliographies</a> (Sources), and <a href="https://visuals.shanti.virginia.edu">Visualizations</a> (Visuals), all of which are interlinked by the “Knowledge Maps” terms that reference <a href="https://mandala.shanti.virginia.edu/places">Places</a> and <a href="https://mandala.shanti.virginia.edu/subjects">Subjects.</a></p>

			        <p class="bullet">Hosted at the University of Virginia, these resources and scholarship support research, teaching, collaboration, and publication. Explore the collections through searching and browsing with keywords, subjects, and places. </p>

			        <p class="bullet">Special features include multilingual, time-coded, and searchable transcripts for audio-video, interactive videos interwoven with other resources, diverse visualizations such as charts, maps, timelines, and network visualizations, and the ability to easily view information about any place or subject cited in an asset’s description, or see all the other assets associated with that place or subject. </p>

			        <p class="bullet">The underlying management system allows any UVA faculty, student, or staff  to easily upload or create new Mandala assets and collections, including new places and subjects. Mandala technology aims to be accessible to beginners, but offer easy ways to scale up to very advanced features and functionality. </p>



					    <!-- BEGIN CARDS -->
					    <div class="wrap mobile">

					        <div class="flip center">
					            <div class="card">
					                <div class="face front">
					                    <span class="icon shanticon-magnify"></span>
					                    <span class="name">Knowledge Maps</span>
					                </div>
					                <div class="face back">
					                    <span class="icon shanticon-magnify"></span>
					                    <div>
					                        <div class="back-wrap-top">
					                            <a href="https://mandala.shanti.virginia.edu/places">
					                                <span class="icon shanticon-places"></span>
					                                <span class="apptitle">Places</span>
					                            </a>
					                        </div>

					                        <div class="back-wrap-bottom">
					                            <a href="https://mandala.shanti.virginia.edu/subjects">
					                                <span class="icon shanticon-subjects"></span>
					                                <span class="apptitle">Subjects</span>
					                            </a>
					                        </div>
					                    </div>
					                </div>
					            </div>
					        </div>

					         <div class="flip deg45">
					            <div class="card">
					                <div class="face front">
					                    <span class="icon shanticon-sources"></span>
					                    <span class="name">Sources</span>
					                </div>
					                <div class="face back">
					                    <div>
					                       <span class="icon shanticon-sources"></span>
					                        <ul>
					                            <li><a href="https://sources.shanti.virginia.edu/">Sources Home</a></li>
					                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Sources+in+Mandala" target="_blank">Contribute</a></li>
					                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Mandala+Suite+of+Tools" target="_blank">FAQ</a></li>
					                        </ul>
					                    </div>
					                </div>
					            </div>
					        </div>

					         <div class="flip deg135">
					            <div class="card">
					                <div class="face front">
					                    <span class="icon shanticon-visuals"></span>
					                    <span class="name">Visuals</span>
					                </div>
					                <div class="face back">
					                    <div>
					                       <span class="icon shanticon-visuals"></span>
					                        <ul>
					                            <li><a href="https://visuals.shanti.virginia.edu/">Visuals Home</a></li>
					                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Create+a+Visualization" target="_blank">Contribute</a></li>
					                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Mandala+Suite+of+Tools" target="_blank">FAQ</a></li>
					                        </ul>
					                    </div>
					                </div>
					            </div>
					        </div>

					        <div class="flip deg225">
					            <div class="card">
					                <div class="face front">
					                    <span class="icon shanticon-texts"></span>
					                    <span class="name">Texts</span>
					                </div>
					                <div class="face back">
					                    <div>
					                      <span class="icon shanticon-texts"></span>
					                        <ul>
					                            <li><a href="https://texts.shanti.virginia.edu/">Texts Home</a></li>
					                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Create+Texts " target="_blank">Contribute</a></li>
					                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Mandala+Suite+of+Tools" target="_blank">FAQ</a></li>
					                        </ul>
					                    </div>
					                </div>
					            </div>
					        </div>

					        <div class="flip deg315">
					            <div class="card">
					                <div class="face front">
					                    <span class="icon shanticon-audio-video"></span>
					                    <span class="name">Audio-Video</span>
					                </div>
					                <div class="face back">
					                    <div>
					                      <span class="icon shanticon-audio-video"></span>
					                        <ul>
					                            <li><a href="https://audio-video.shanti.virginia.edu/">AV Home</a></li>
					                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Start+in+Audio-Video" target="_blank">Contribute</a></li>
					                            <li><a href="https://wiki.shanti.virginia.edu/display/KB/Mandala+Suite+of+Tools" target="_blank">FAQ</a></li>
					                        </ul>
					                    </div>
					                </div>
					            </div>
					        </div>

					    </div> <!-- END Cards -->



					        <div class="panel panel-default">
					          <div class="panel-heading">
					            <h3 class="panel-title">To Get Started</h3><!-- TO GET STARTED -->
					          </div>
					          <div class="panel-body">
					            <ul>
					                <li>First, create a collection and add content to it using one of the Mandala applications, such as  <a href="https://audio-video.shanti.virginia.edu/">Audio-Video</a>, <a href="https://images.shanti.virginia.edu">Images</a>, <a href="https://visuals.shanti.virginia.edu/">Visuals</a>, <a href="https://sources.shanti.virginia.edu/">Sources</a>, or <a href="https://texts.shanti.virginia.edu/">Texts</a>, all of which can be accessed with your UVA computing credentials.</li>
					                <li>Next, catalog and connect content together by creating keyword relationships from the Knowledge Maps glossary of terms from <a href="https://mandala.shanti.virginia.edu/subjects">Subjects</a> and <a href="https://mandala.shanti.virginia.edu/places">Places</a>.</li>
					                <li>Finally, explore your collections in portals that show all of your content, as well as the content of others, and focus your exploration by searching for the Knowledge Map terms that interest you.</li>
					                <li>Mandala's online help & tutorials are in the <a href="https://wiki.shanti.virginia.edu/display/KB/Mandala+Suite+of+Tools" target="_blank">UVA Knowledge Base.</a></li>
					                <li>If you feel intrigued and would like personal guidance to get started, don’t hesitate to contact <a href="http://shanti.virginia.edu/wordpress/?page_id=560">SHANTI</a> to get a free consultation.</li>
					            </ul>
					          </div><!-- END panel body -->
					        </div><!-- END panel -->

								    </div><!-- End home intro text -->

								</div><!-- End homepage-main-content -->

		                 </div>
		             </div>
		         </div>

		      </article>
		    </div>
		  </section>
		  <!-- END Content -->

          <!-- Sidebar Second Region -->
          <?php if ($page['sidebar_second']): ?>
            <section id="sidebar-second" class="region sidebar sidebar-second sidebar-offcanvas<?php print " $bsclass_sb2"; ?> ">
              <?php print render($page['sidebar_second']); ?>
            </section>
          <?php endif; ?>
        </section>

        <a href="#" class="back-to-top" role="button" aria-label="Back to Top of Page"><span class="icon fa"></span></a>
      </article>

		  <!-- Search Flyout -->
		  <?php if(!empty($page['search_flyout'])): ?>
				<div id="search-flyout" class="region extruder right" role="search" style="display: none;">
				   <?php print render($page['search_flyout']); ?>
				</div>
      <!-- BEGIN faceted search results -->
      <section id="faceted-search-results" class="faceted-search-results mandala-sliding-panel right-panel search-flyout-collapsed off" style="display:none;" aria-expanded="false" aria-label="Search Results Sliding Panel">
        <!-- INSERT RESULTS TEMPLATE DATA -->
        <div class="ui-resizable-handle ui-resizable-w"></div>
      </section>
      <!-- END faceted search results -->
	  <?php endif; ?>


    </main> <!-- End Main Content -->

  <!-- LOAD menus -->
  <section id="menu" class="menu-main" style="display:none;">
    <nav id="menu-drill">
     <?php print $variables['user_menu_links']; ?>
    </nav>
  </section><!-- END menu -->

</div> <!-- End wrap-all -->

<!-- Footer -->
<footer class="footer">
  <div>
    <?php print render($page['footer']); ?>
    <p class="rights">&copy; <?php print date("Y"); ?> All Rights Reserved</p>
  </div>
</footer>

<!-- Admin Footer -->
<div id="admin-footer">
  <?php print render($page['admin_footer']); ?>
</div>

<div id="mandala-veil-bg"></div>

<div id="results-media-viewer-modal" class="modal fade" tabindex="-1" role="dialog">
  <div class="modal-dialog modal-dialog-centered modal-full" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
        <h4 class="modal-title" id="myModalLabel">Media Viewer</h4>
      </div>
      <div id="results-media-viewer-body" class="modal-body">

        <h1>View Media</h1>

      </div> <!-- .model-header -->
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
      </div><!-- .modal-footer -->
    </div> <!-- .modal-content -->
  </div> <!-- .modal-dialog -->
</div> <!-- .modal -->
