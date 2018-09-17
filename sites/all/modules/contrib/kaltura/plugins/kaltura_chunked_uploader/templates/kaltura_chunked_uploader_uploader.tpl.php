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
            class="form-submit"
            type="submit"
            value="Upload"
          >
        </div>
        <div class="description">

        </div>
      </form>
    </div>

    <span id="upload-file-info" class="label"></span>

    <a
      id="cancelBtn"
      class="cancelBtn button hidden"
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
      class="button hidden"
      role="button"
      tabindex="0"
    >
      <?php print t('Submit'); ?>
    </a>
  </div>
</div>
