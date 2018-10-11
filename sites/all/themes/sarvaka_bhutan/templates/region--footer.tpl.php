<!-- Footer Region from region--footer.tpl.php -->

<footer class="footer">
  <div class="sponsors">
  	<p class="tagline">Sponsored by:</p>
  	<?php print render($variables['elements']['views_sponsor_logos-block']); ?>
  </div>
  <div class="general">
    <p>&copy; Copyright <?php echo date('Y') ?></p>
    <?php print render($variables['elements']['system_powered-by']); ?>
  </div>
</footer>

<!-- End of Footer Region -->
