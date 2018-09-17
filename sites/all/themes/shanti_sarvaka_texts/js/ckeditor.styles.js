/*
Copyright (c) 2003-2013, CKSource - Frederico Knabben. All rights reserved.
For licensing, see LICENSE.html or http://ckeditor.com/license
*/

/*
 * This file is used/requested by the 'Styles' button.
 * The 'Styles' button is not enabled by default in DrupalFull and DrupalFiltered toolbars.
 */
if(typeof(CKEDITOR) !== 'undefined') {
    CKEDITOR.addStylesSet( 'drupal',
    [
            /* Block Styles */

            { name : 'Bourdieu'	, 	element : 'div', attributes : { 'class' : 'bourdieu' } },
            { name : 'Pull Quote Right'	, element : 'div', attributes : { 'class' : 'pull-quote-right' } },
            { name : 'Pull Quote Left'	, element : 'div', attributes : { 'class' : 'pull-quote-left' } },

            /* Inline Styles */

            { name : 'Marker: Yellow'	, element : 'span', attributes : { 'class' : 'marker-yellow' } },
            { name : 'Marker: Green'	, element : 'span', attributes : { 'class' : 'marker-green' } },
            { name : 'Marker: Blue'	, element : 'span', attributes : { 'class' : 'marker-blue' } },
            { name : 'Marker: Red'	, element : 'span', attributes : { 'class' : 'marker-red' } },

						/*
            { name : 'Big'				, element : 'big' },
            { name : 'Small'			, element : 'small' },
            { name : 'Typewriter'		, element : 'tt' },

            { name : 'Computer Code'	, element : 'code' },
            { name : 'Keyboard Phrase'	, element : 'kbd' },
            { name : 'Sample Text'		, element : 'samp' },
            { name : 'Variable'			, element : 'var' },

            { name : 'Deleted Text'		, element : 'del' },
            { name : 'Inserted Text'	, element : 'ins' },

            { name : 'Cited Work'		, element : 'cite' },
            { name : 'Inline Quotation'	, element : 'q' },
						*/

            /* Object Styles */

            {
                    name : 'Image on Left',
                    element : 'img',
                    attributes :
                    {
                            'class' : 'image-left'
                    }
            },

            {
                    name : 'Image on Right',
                    element : 'img',
                    attributes :
                    {
                            'class' : 'image-right',
                    }
            }
    ]);
}