<?php

/**
 * @file
 * biblio_long_fields.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function biblio_long_fields_defaultconfig_features() {
  return array(
    'biblio_long_fields' => array(
      'field_default_fields' => 'field_default_fields',
    ),
  );
}

/**
 * Implements hook_defaultconfig_field_default_fields().
 */
function biblio_long_fields_defaultconfig_field_default_fields() {
  $fields = array();

  // Exported field: 'node-biblio-field_biblio_long_language'.
  $fields['node-biblio-field_biblio_long_language'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => -1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_biblio_long_language',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => 0,
      'module' => 'list',
      'settings' => array(
        'allowed_values' => array(
          'English' => 'English',
          'German' => 'German',
          'Chinese' => 'Chinese',
          'Tibetan' => 'Tibetan',
          'Sanskrit' => 'Sanskrit',
          'Japanese' => 'Japanese',
          'Sina Bidoyoh' => 'Sina Bidoyoh',
          'Abkhaz' => 'Abkhaz',
          'Adyghe' => 'Adyghe',
          'Afrikaans' => 'Afrikaans',
          'Akan' => 'Akan',
          'Albanian' => 'Albanian',
          'Arabic' => 'Arabic',
          'Aragonese' => 'Aragonese',
          'Amharic' => 'Amharic',
          'Armenian' => 'Armenian',
          'Aymara' => 'Aymara',
          'Balinese' => 'Balinese',
          'Basque' => 'Basque',
          'Betawi' => 'Betawi',
          'Bosnian' => 'Bosnian',
          'Breton' => 'Breton',
          'Bulgarian' => 'Bulgarian',
          'Cantonese' => 'Cantonese',
          'Catalan' => 'Catalan',
          'Cherokee' => 'Cherokee',
          'Chickasaw' => 'Chickasaw',
          'Coptic' => 'Coptic',
          'Cornish' => 'Cornish',
          'Corsican' => 'Corsican',
          'Crimean Tatar' => 'Crimean Tatar',
          'Croatian' => 'Croatian',
          'Czech' => 'Czech',
          'Danish' => 'Danish',
          'Dutch' => 'Dutch',
          'Dawro' => 'Dawro',
          'Esperanto' => 'Esperanto',
          'Estonian' => 'Estonian',
          'Ewe' => 'Ewe',
          'Fiji Hindi' => 'Fiji Hindi',
          'Finnish' => 'Finnish',
          'French' => 'French',
          'Galician' => 'Galician',
          'Georgian' => 'Georgian',
          'Greek, Modern' => 'Greek, Modern',
          'Ancient Greek' => 'Ancient Greek',
          'Greenlandic' => 'Greenlandic',
          'Haitian Creole' => 'Haitian Creole',
          'Hawaiian' => 'Hawaiian',
          'Hebrew' => 'Hebrew',
          'Hindi' => 'Hindi',
          'Hungarian' => 'Hungarian',
          'Icelandic' => 'Icelandic',
          'Indonesian' => 'Indonesian',
          'Inuktitut' => 'Inuktitut',
          'Interlingua' => 'Interlingua',
          'Irish' => 'Irish',
          'Italian' => 'Italian',
          'Kabardian' => 'Kabardian',
          'Kannada' => 'Kannada',
          'Kashubian' => 'Kashubian',
          'Khmer' => 'Khmer',
          'Kinyarwanda' => 'Kinyarwanda',
          'Korean' => 'Korean',
          'Kurdish/Kurdî' => 'Kurdish/Kurdî',
          'Ladin' => 'Ladin',
          'Latgalian' => 'Latgalian',
          'Latin' => 'Latin',
          'Lingala' => 'Lingala',
          'Livonian' => 'Livonian',
          'Lojban' => 'Lojban',
          'Lower Sorbian' => 'Lower Sorbian',
          'Low German' => 'Low German',
          'Macedonian' => 'Macedonian',
          'Malay' => 'Malay',
          'Malayalam' => 'Malayalam',
          'Mandarin' => 'Mandarin',
          'Manx' => 'Manx',
          'Maori' => 'Maori',
          'Mauritian Creole' => 'Mauritian Creole',
          'Min Nan' => 'Min Nan',
          'Mongolian' => 'Mongolian',
          'Norwegian' => 'Norwegian',
          'Old Armenian' => 'Old Armenian',
          'Old English' => 'Old English',
          'Old French' => 'Old French',
          'Old Norse' => 'Old Norse',
          'Old Prussian' => 'Old Prussian',
          'Oriya' => 'Oriya',
          'Pangasinan' => 'Pangasinan',
          'Papiamentu' => 'Papiamentu',
          'Pashto' => 'Pashto',
          'Persian' => 'Persian',
          'Pitjantjatjara' => 'Pitjantjatjara',
          'Polish' => 'Polish',
          'Portuguese' => 'Portuguese',
          'Proto-Slavic' => 'Proto-Slavic',
          'Rapa Nui' => 'Rapa Nui',
          'Romanian' => 'Romanian',
          'Russian' => 'Russian',
          'Scots' => 'Scots',
          'Scottish Gaelic' => 'Scottish Gaelic',
          'Serbian' => 'Serbian',
          'Serbo-Croatian' => 'Serbo-Croatian',
          'Slovak' => 'Slovak',
          'Slovene' => 'Slovene',
          'Spanish' => 'Spanish',
          'Sinhalese' => 'Sinhalese',
          'Swahili' => 'Swahili',
          'Swedish' => 'Swedish',
          'Tagalog' => 'Tagalog',
          'Tajik' => 'Tajik',
          'Tamil' => 'Tamil',
          'Tarantino' => 'Tarantino',
          'Telugu' => 'Telugu',
          'Thai' => 'Thai',
          'Tok Pisin' => 'Tok Pisin',
          'Turkish' => 'Turkish',
          'Twi' => 'Twi',
          'Ukrainian' => 'Ukrainian',
          'Upper Sorbian' => 'Upper Sorbian',
          'Urdu' => 'Urdu',
          'Uzbek' => 'Uzbek',
          'Venetian' => 'Venetian',
          'Vietnamese' => 'Vietnamese',
          'Vilamovian' => 'Vilamovian',
          'Volapük' => 'Volapük',
          'Võro' => 'Võro',
          'Welsh' => 'Welsh',
          'Xhosa' => 'Xhosa',
          'Yiddish' => 'Yiddish',
        ),
        'allowed_values_function' => '',
        'entity_translation_sync' => FALSE,
      ),
      'translatable' => 0,
      'type' => 'list_text',
    ),
    'field_instance' => array(
      'bundle' => 'biblio',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => 16,
        ),
        'full' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_biblio_long_language',
      'label' => 'Long Title Language',
      'required' => 0,
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(
          'apply_chosen' => '',
        ),
        'type' => 'options_select',
        'weight' => 66,
      ),
    ),
  );

  // Exported field: 'node-biblio-field_biblio_long_title'.
  $fields['node-biblio-field_biblio_long_title'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_biblio_long_title',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => 0,
      'module' => 'text',
      'settings' => array(
        'entity_translation_sync' => FALSE,
      ),
      'translatable' => 0,
      'type' => 'text_long',
    ),
    'field_instance' => array(
      'bundle' => 'biblio',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 9,
        ),
        'featured' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'full' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_plain',
          'weight' => -25,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 11,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_biblio_long_title',
      'label' => 'Long Title',
      'required' => 0,
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'linkit' => array(
          'button_text' => 'Search',
          'enable' => 0,
          'profile' => '',
        ),
        'text_processing' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => 5,
        ),
        'type' => 'text_textarea',
        'weight' => 65,
      ),
    ),
  );

  // Exported field: 'node-biblio-field_kmaps_places'.
  $fields['node-biblio-field_kmaps_places'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => -1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_kmaps_places',
      'foreign keys' => array(),
      'indexes' => array(
        'id' => array(
          0 => 'id',
        ),
      ),
      'locked' => 0,
      'module' => 'shanti_kmaps_fields',
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'kmap_domain' => 'places',
      ),
      'translatable' => 0,
      'type' => 'shanti_kmaps_fields_default',
    ),
    'field_instance' => array(
      'bundle' => 'biblio',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'shanti_kmaps_fields',
          'settings' => array(),
          'type' => 'kmap_popover_formatter',
          'weight' => 7,
        ),
        'full' => array(
          'label' => 'above',
          'module' => 'shanti_kmaps_fields',
          'settings' => array(),
          'type' => 'kmap_popover_formatter',
          'weight' => 4,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 1,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_kmaps_places',
      'label' => 'Places',
      'required' => 0,
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'kmap_term_limit' => 100,
        'search_filters' => array(),
        'search_root_kmap_path' => NULL,
        'search_root_kmapid' => '',
        'search_view' => '',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'shanti_kmaps_fields',
        'settings' => array(),
        'type' => 'kmap_typeahead_picker',
        'weight' => 69,
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Long Title');
  t('Long Title Language');
  t('Places');

  return $fields;
}
