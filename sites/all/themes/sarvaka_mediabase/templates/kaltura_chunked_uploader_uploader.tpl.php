<?php
$inputAcceptFileTypes = implode(',', array_map(function ($fileType) {
  return '.' . $fileType;
}, $fileTypes));
?>

<div id="uploadHook<?php print $uploaderId; ?>"></div>
<div id="uploadbox<?php print $uploaderId; ?>">
  <div class="relative">
    <div id="uploadbutton">
      <form id="fileupload" action="">
        <div class="description">
            <?php print t('First, choose the AV file you wish to add to your collection. Then, press the upload button.'); ?>
        </div>
        <div class="form-managed-file">
          <input
            id="fileinput"
            class="form-file"
            data-uploadboxid="<?php print $uploaderId; ?>"
            type="file"
            name="fileData"
            accept="<?php print $inputAcceptFileTypes; ?>"
          >
          <input
            class="form-submit btn btn-primary"
            type="submit"
            value="<?php print t('Upload'); ?>"
          >
        </div>
      </form>
    </div>

    <span id="upload-file-info" class="label"></span>

    <a
      id="cancelBtn"
      class="cancelBtn file-upload-cancel-btn button btn btn-default hidden"
      role="button"
      tabindex="0"
    >
      <?php print t('Cancel'); ?>
    </a>
  </div>

  <div id="progress" class="progress hidden">
    <div class="bar">
      <div id="progressBar" class="filled"></div>
    </div>
    <div class="anchor">
      <div class="message"></div>
    </div>
  </div>

  <div id="successmsg" class="messages status hidden alert alert-success">
    <span class="large">
      <strong><?php print t('Upload Completed!'); ?></strong>
    </span>
  </div>

  <div>
    <a
      id="submitBtn<?php print $uploaderId; ?>"
      class="button btn btn-primary hidden"
      role="button"
      tabindex="0"
    >
      <?php print t('Submit'); ?>
    </a>
  </div>
</div>
