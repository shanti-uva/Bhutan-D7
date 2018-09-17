<div id="transcript-processor" class="panel">
  <div class="panel-body">
    <div class="well well-sm">
      Mandala AV has analyzed and processed your transcript.
      Set the transcript languages, and if necessary reprocess the transcript by changing the settings below.
      Click <strong>Accept</strong> when the analysis is correct and you are ready to generate
      subtitle tracks and an interactive transcript.
    </div>
    <div id="transcript-settings"
         class="col-md-4 <?php print ($numlangs == 1 ? "monolingual" : "multilingual"); ?>">
      <h2>Timecodes</h2>
      <?php if ($timed): ?>
        <div id="timecode-units">
          We see your transcript has timecodes.
        </div>
      <?php else: ?>
        <div id="unit-delimiter">
          <label>Unit delimiter</label>
          <label><input type="radio" name="unit-delim" value="blankline" checked> Empty line</label>
          <label><input type="radio" name="unit-delim" value="newline"> End of line</label>
          <label><input type="radio" name="unit-delim" value="custom"> Custom <input id="custom-unit-delim"
                                                                                     type="text"
                                                                                     value="//"></label>
        </div>
      <?php endif; ?>
      <h2>Languages</h2>
      <div id="languages-howmany">
        <label>Your transcript has...</label>
        <label>
          <input type="radio" name="howmany" value="multilingual" <?php if ($numlangs > 1) print "checked"; ?>>
          Multiple languages
        </label>
        <label>
          <input type="radio" name="howmany" value="monolingual" <?php if ($numlangs == 1) print "checked"; ?>>
          One language only
        </label>
      </div>
      <div id="languages-delimiter">
        <label>Language delimiter</label>
        <label><input type="radio" name="lang-delim" value="newline" checked> End of line</label>
        <label><input type="radio" name="lang-delim" value="custom"> Custom <input id="custom-lang-delim" type="text"
                                                                                   value="/"></label>
      </div>
      <div id="languages-which">
        <?php for ($n = 0; $n < count($languages); $n++): ?>
          <?php $classes = array(); ?>
          <?php if ($n > $numlangs) $classes[] = 'hide'; ?>
          <?php if ($n == 1) $classes[] = 'active'; ?>
          <?php $classes[] = $n == 0 ? 'monolingual' : 'multilingual'; ?>
          <label class="<?php print implode(" ", $classes); ?>">Language <?php print $n; ?>:
            <select id="selectlanguage-<?php print $n; ?>" class="language selectpicker">
              <?php foreach ($tiers as $key => $val): ?>
                <?php $selected = $key == $languages[$n] ? ' selected ' : ''; ?>
                <option value="<?php print $key; ?>"<?php print $selected; ?>>
                  <?php print $val; ?>
                </option>
              <?php endforeach; ?>
            </select>
          </label>
        <?php endfor; ?>
      </div>
    </div>
    <div class="col-md-8">
      <div id="transcript-results" class="<?php print ($numlangs == 1 ? "monolingual" : "multilingual"); ?>">
        <ul class="nav nav-pills">
          <?php for ($n = 0; $n < count($languages); $n++): ?>
            <?php $classes = array(); ?>
            <?php if ($n > $numlangs) $classes[] = 'hide'; ?>
            <?php if (($n == 0 && $numlangs == 1) || ($n == 1 && $numlangs > 1)) $classes[] = 'active'; ?>
            <?php $classes[] = $n == 0 ? 'monolingual' : 'multilingual'; ?>
            <li class="<?php print implode(" ", $classes); ?>" role="presentation">
              <a href="#language-<?php print $n; ?>" role="tab" data-toggle="tab">
                <?php print $tiers[$languages[$n]]; ?>
              </a>
            </li>
          <?php endfor; ?>
        </ul>
        <div class="tab-content">
          <?php for ($n = 0; $n < count($languages); $n++): ?>
            <?php $class = ($n == 0 && $numlangs == 1) || ($n == 1 && $numlangs > 1) ? 'active' : ''; ?>
            <div role="tabpanel" class="tab-pane <?php print $class; ?>" id="language-<?php print $n; ?>">
              <pre><?php print $results[$n]; ?></pre>
            </div>
          <?php endfor; ?>
        </div>
      </div>
    </div>
  </div>
</div>
