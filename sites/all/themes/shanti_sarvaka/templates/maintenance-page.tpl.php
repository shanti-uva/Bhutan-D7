<?php
/**
 * @file
 * Implementation to display a single Drupal page while offline.
 *
 * All the available variables are mirrored in page.tpl.php.
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 * @see bartik_process_maintenance_page()
 */
 
    $cl = theme_get_setting('shanti_sarvaka_icon_class');
    $fld = 'sarvaka_';
    switch ($cl) {
        case 'visuals':
            $cl = 'shiva';
            $fld .= 'shiva';
            break;
        case 'audio-video':
            $cl = 'mediabase';
            $fld .= 'mediabase';
            break;
        case 'texts':
            $fld = 'shanti_' . $fld . $cl;
            break;
        case 'sources':
            $fld = 'sources_theme';
            break;
        case 'mandala':
        case 'subjects':
        case 'places':
            $cl = 'kmaps';
            $fld .= $cl;
            break;
        default:
            $fld .= $cl;
    }
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">
    <head>
        <?php print $head; ?>
        <title><?php print $site_name; ?></title>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
    <style type="text/css" media="all">
@import url("/sites/all/themes/shanti_sarvaka/css/utils.css");
@import url("/sites/all/themes/shanti_sarvaka/fonts/font-awesome-4.0.3/css/font-awesome.min.css");
@import url("/sites/all/themes/shanti_sarvaka/fonts/shanticon/css/style.css");
@import url("/sites/all/themes/shanti_sarvaka/css/shanti-main.css");
@import url("/sites/all/themes/<?php print $fld; ?>/css/shanti-main-<?php print $cl; ?>.css");
</style>
<style>
    /** Maintenance Page Styles **/
    .html.front.maintenance {
        width: 100%;
        margin-left: 0;
    }
    .maintenance .navbar-header {
        font-size: 1.4em;
        padding-bottom: 0.5em;
    }
    .maintenance header .page-title {
        padding-left: 1em;
        padding-top: 0.2em;
    }
    .maintenance .site-slogan {
        font-size: 1.2em;
    }
    .maintenance .content-section article.main-col {
        text-align: center;
        top: -1em;
        position: relative;
    }
    .maintenance pre {
        color: darkgreen;
    }
</style>
<body class="html front maintenance" >
  <!--[if lte IE 8]><p class="progressive"><?php print t('It appears you are using an older browser. Please consider a upgrading to a modern version of your browser to best enjoy this website.'); ?></p><![endif]-->
    <div class="wrap-all">
    <!-- Header Region -->
   <div class="site-banner">
    <div class="navbar navbar-default">

        <h1 class="navbar-header">
                           <a href="/" class="logo-brand navbar-brand">
                <span class="icon shanticon-logo"></span>
                <span class="mandala">Mandala <em>Collections</em></span>
                              </a>

            
            <a href="/" class="navbar-brand" title="SHANTI Audio &amp; Video Collections Homepage">
              <span class="site-slogan"><?php echo $site_slogan; ?></span>        </a>
        </h1>

    <!-- Begin Content Region -->
    <main class="main-wrapper container-fluid">
      <article class="main-content" role="main">
        <section class="row" role="banner">

          <!-- Banner Region -->
          <div class="titlearea banner has-tabs">
           <div>
             <header role="banner">
                <h1 class="page-title"><?php 
                echo $site_slogan . ": " . $title; ?> <span class="icon shanticon-gear"></span></span>
                </h1>
              </header>
              
            </div>
          </div>

        </section> <!-- End of Banner Row -->


        <!-- Begin Content Row -->
        <section class="row row-offcanvas row-offcanvas-right" role="main">

          <!-- Begin Page Content -->
          <section class="content-section  col-xs-12 col-md-9 ">
    
                <!-- Main Content -->
                <div class="tab-content container-fluid">
                  <article class="tab-pane main-col active" id="tab-overview">
                        <?php print $content; ?>
                        <?php 
                            /*  For debugging:
                             * print "<div>{var: $cl}</div>";
                            print '<pre>';
                          //var_dump(get_defined_vars()); 
                          print '</pre>';*/
                      ?>
                  </article>
                </div>
              </section>
              <!-- END Content -->
    
              <!-- Sidebar Second Region -->
              <?php if (!empty($page['sidebar_second'])): ?>
                <section id="sidebar-second" class="region sidebar sidebar-second sidebar-offcanvas<?php print " $bsclass_sb2"; ?> ">
                  <?php print render($page['sidebar_second']); ?>
                </section>
              <?php endif; ?>
            </section>
    
          </article>
    
    </div> <!-- End wrap-all -->
    
    <!-- Footer -->
    <footer class="footer">
      <div>
        <?php print render($page['footer']); ?>
        <p class="rights">&copy; <?php print date("Y"); ?> <?php print t('All Rights Reserved'); ?></p>
      </div>
    </footer>
    </body>
</html>
