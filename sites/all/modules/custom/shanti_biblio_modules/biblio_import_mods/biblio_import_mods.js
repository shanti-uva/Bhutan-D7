(function ($) {
    /**
     * Drupal Behavior for Biblio Import form. When file is uploaded, change the format select based on file extension
     */
    Drupal.behaviors.biblio_import_mods = {
        attach: function (context) {
            if (context == document) {
                var file_field = $('#biblio-import-form #edit-biblio-import-file');
                file_field.on('change', function () {
                    var filename = file_field[0].files[0].name;
                    var pts = filename.split('.');
                    if (pts.length > 1) {
                        // To change other select to RIS format do:
                        var format = '';
                        switch(pts[1]) {
                            case 'ris':
                                format = 'biblio_ris';
                                break;

                            case 'xml':
                                format = 'biblio_xml';
                                break;

                            case 'bib':
                                format = 'biblio_bibtex';
                                break;
                        }
                        if (format.length > 0) {
                            $('#biblio-import-form #edit-filetype').selectpicker('val', format);
                        }
                    }
                });
            }
        }
    }
}(jQuery));