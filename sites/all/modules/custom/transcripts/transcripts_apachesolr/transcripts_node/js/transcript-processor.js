(function ($) {
  Drupal.behaviors.transcriptProcessor = {
    attach: function (context, settings) {
      $('#edit-field-transcript').once('transcript-settings', function() {
        var $field = $(this);

        function setMonolingual(monolingual) {
          if (monolingual) {
            $('#transcript-settings, #transcript-results').removeClass('multilingual').addClass('monolingual');
            $('#transcript-results .nav > li').removeClass('active').first().addClass('active');
            $('#transcript-results .tab-content > .tab-pane').removeClass('active').first().addClass('active');
          }
          else { //multlingual
            $('#transcript-settings, #transcript-results').removeClass('monolingual').addClass('multilingual');
            $('#transcript-results .nav > li').removeClass('active').eq(1).addClass('active');
            $('#transcript-results .tab-content > .tab-pane').removeClass('active').eq(1).addClass('active');
          }
        }
        $field.on('change', 'input[type=radio][name=howmany]', function(e) {
          setMonolingual($(this).val() == 'monolingual');
          var delim = $('input[type=radio][name=lang-delim]:checked').val() == 'newline' ? "\n" : $('#custom-lang-delim').val();
          delimitTranscript(delim, false);
        });

        function asSeconds(timecode) {
          var m = timecode.match(/^([0-9]{2}):([0-9]{2}):([0-9]{2})\.([0-9]{3})$/);
          if (m == null) {
            return 0;
          }
          else {
            return Number(m[1])*3600 + Number(m[2])*60 + Number(m[3]) + Number(m[4])/1000;
          }
        }

        function delimitTranscript(delim, fresh) {
          if (fresh && $('#unit-delimiter').length == 1) {
            var source = Drupal.settings.transcripts_node['source'].replace(/>>\s*([^>:]+):/g, '&lt;v $1&gt;');
            var checked = $('input[type=radio][name=unit-delim]:checked').val();
            var unitdel = checked == 'blankline' ? "\n\n" : checked == 'newline' ? "\n" : $('#custom-unit-delim').val();
            var tcus = source.split(unitdel).filter(val => {return val.length > 0; });
            for (var i=0; i<tcus.length; i++) {
              tcus[i] = (i+1).toString() + "\n" + "00:00.000 --> 00:00.000\n" + tcus[i].trim().replace(/\n\s*\n/g, '\n');
            }
            $('#transcript-results .tab-pane:eq(0) > pre').html("WEBVTT\n\n" + tcus.join("\n\n"));
          }

          var multilingual = $('input[type=radio][name=howmany]:checked').val() == 'multilingual';
          var langtags = Array(9);
          var spkrtags = Array(9);
          var tierSet = new Set();
          $('select.language', $field).each(function() {
            var $sel = $(this);
            var id = $sel.attr('id');
            var n = Number(id.substring(id.indexOf('-')+1));
            langtags[n] = $sel.val();
            if (langtags[n] == 'dzo_bod') {
              spkrtags[n] = 'ss_speaker_dzo'; //hack
            }
            else {
              spkrtags[n] = langtags[n].replace("ts_", "").replace("content_", "ss_speaker_"); //FIXME TO CONFIGURATION
            }
          });

          var transcript = $('#transcript-results .tab-pane:eq(0) > pre').html();
          var units = transcript.split("\n\n");
          units.shift();
          var results = Array(8).fill("WEBVTT\n\n");
          var numlangs = 0;
          var xml = "<tcus>\n";
          var regex = /^&lt;v (.*)&gt;([\s\S]*)$/;
          for (var i=0; i<units.length; i++) {
            if (units[i].replace(/\s/g, '').length > 0) {
              var tiers = Array();
              var speakers = Array();
              var lines = units[i].split("\n");
              var langs = lines.slice(2).join("\n").split(delim);
              for (var k=0; k<8; k++) {
                if (k < langs.length) {
                  var tier = langs[k].trim();
                  if (multilingual) {
                    var matches = tier.match(regex);
                    var opentag = "<" + langtags[k+1] + ">";
                    var closetag = "</" + langtags[k+1] + ">";
                    if (matches == null) {
                      tiers.push(opentag + tier + closetag);
                    }
                    else {
                      speakers.push("<" + spkrtags[k+1] + ">" + matches[1] + "</" + spkrtags[k+1] + ">");
                      tiers.push(opentag + matches[2].trim() + closetag);
                    }
                    tierSet.add(langtags[k+1]);
                  }
                  results[k] += lines[0] + "\n" + lines[1] + "\n" + tier + "\n\n";
                }
                else {
                  results[k] += lines[0] + "\n" + lines[1] + "\n\n";
                }
              }
              if (langs.length > numlangs) numlangs = langs.length;
              var times = lines[1].split(" --&gt; ");
              var start = asSeconds(times[0]).toFixed(3);
              var end = asSeconds(times[1]).toFixed(3);
              if (!multilingual) {
                var tier = langs.join(delim);
                var matches = tier.match(regex);
                var opentag = "<" + langtags[0] + ">";
                var closetag = "</" + langtags[0] + ">";
                if (matches == null) {
                  tiers.push(opentag + tier + closetag);
                }
                else {
                  speakers.push("<" + spkrtags[0] + ">" + matches[1] + "</" + spkrtags[0] + ">");
                  tiers.push(opentag + matches[2].trim() + closetag);
                }
                tierSet.add(langtags[0]);
              }
              xml += "<tcu>\n<start>" + start + "</start>\n<end>" + end + "</end>\n<speakers>" + speakers.join("\n") + "</speakers>\n<tiers>" + tiers.join("\n") + "</tiers>\n</tcu>\n";
            }
          }
          var $tabs = $('#transcript-results .tab-content > .tab-pane');
          for (var i=0; i<numlangs; i++) {
            $tabs.eq(i+1).html('<pre>' + results[i] + '</pre>');
          }
          if (multilingual) {
            $('#transcript-results ul.nav').find('li').removeClass('hide').end().find('li:gt(' + numlangs.toString() + ')').addClass('hide');
            $('#languages-which').find('label.multilingual').removeClass('hide').end().find('label.multilingual:gt(' + (numlangs - 1).toString() + ')').addClass('hide');
            if (tierSet.size == numlangs) {
              $('.accept-button > button').removeAttr('disabled');
              $('.accept-message').hide();
            }
            else {
              $('.accept-button > button').attr('disabled', 'disabled');
              $('.accept-message').show();
            }
          } else {
            $('.accept-button > button').removeAttr('disabled');
            $('.accept-message').hide();
          }
          xml += "</tcus>";
          $('.transcript-processor-xml > input').val(xml);
          $('.transcript-processor-tiers > input').val(Array.from(tierSet).join(" "));
        }

        $field.on('change', 'select.language', function(e) {
          var $sel = $(this);
          var id = $sel.attr('id');
          var n = id.substring(id.indexOf('-')+1);
          $('a[href=#language-' + n + ']').html(Drupal.settings.transcriptTiers[$sel.val()]);
          var delim = $('input[type=radio][name=lang-delim]:checked').val() == 'newline' ? "\n" : $('#custom-lang-delim').val();
          delimitTranscript(delim, false);
        });

        $field.on('change', '#custom-lang-delim', function(e) {
          if ($('input[type=radio][name=lang-delim]:checked').val() == 'custom') {
            delimitTranscript($('#custom-lang-delim').val(), false);
          }
        });
        $field.on('change', 'input[type=radio][name=lang-delim]', function(e) {
          delimitTranscript($(this).val() == 'newline' ? "\n" : $('#custom-lang-delim').val(), false);
        });

        $field.on('change', '#custom-unit-delim', function(e) {
          if ($('input[type=radio][name=unit-delim]:checked').val() == 'custom') {
            var delim = $('input[type=radio][name=lang-delim]:checked').val() == 'newline' ? "\n" : $('#custom-lang-delim').val();
            delimitTranscript(delim, true);
          }
        });
        $field.on('change', 'input[type=radio][name=unit-delim]', function(e) {
          var delim = $('input[type=radio][name=lang-delim]:checked').val() == 'newline' ? "\n" : $('#custom-lang-delim').val();
          delimitTranscript(delim, true);
        });

      });
    }
  };
})(jQuery);
