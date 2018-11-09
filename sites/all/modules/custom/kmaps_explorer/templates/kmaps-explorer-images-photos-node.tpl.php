<div class="related-photos">
    <?php if ($photo->response->numFound > 0): ?>
        <?php $imageObj = $photo->response->docs[0]; ?>
        <?php
            $urlArray = explode("/", $imageObj->url_thumb);
            $urlArray[count($urlArray) - 3] = "!600,400";
            $urlArray = implode("/", $urlArray);
        ?>
        <?php if(!empty($imageObj->caption)): ?>
            <p><?php echo $imageObj->caption; ?></p>
        <?php endif; ?>
        <figure>
            <img src="<?php print $urlArray; ?>">
            <?php if(count($imageObj->creator) > 0): ?>
                <figcaption><strong>Photographer:</strong> <?php print $imageObj->creator[0]; ?></figcaption>
            <?php endif; ?>
        </figure><br>
        <?php if(!empty($imageObj->summary)): ?>
            <p><?php print $imageObj->summary ?></p>
        <?php endif; ?>
    <?php endif; ?>
</div>
