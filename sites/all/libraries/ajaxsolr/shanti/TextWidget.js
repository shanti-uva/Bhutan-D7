/**
 * Created by ys2n on 8/27/14.
 */

const SEARCH_MIN_LENGTH = 2;

(function ($) {

    AjaxSolr.TextWidget = AjaxSolr.AbstractTextWidget.extend({
        doSearch: function (widget) {

            console.log("doSearch!");

            if (!widget) {
                widget = this;
            }
            var value = $(widget.target).val();
            console.log("search value = " + value);

            if (value.length < SEARCH_MIN_LENGTH) {
                if (widget.notify) {
                    widget.notify.clear();
                    widget.notify.warn('warntooshort', 'Search string must be ' + SEARCH_MIN_LENGTH + ' characters or longer.');
                }
            } else {
                if (widget.notify) {
                    widget.notify.clear();
                }
                //  If the user inserts wildcards, assume they know what they are doing.
                //if (value.indexOf('*') < 0) {

                    // Process advanced search

                    console.log("SEARCH GROUP:" + $('#searchAnchorGroup'));
                    console.log("SEARCH ANCHOR: " + $('#searchAnchorGroup .checked input[name="anchor"]').val());
                    console.log("SEARCH SCOPE: " + $('#searchScopeGroup .checked input[name="scope"]').val());


                    var query = "";
                    var anchor = $('#searchAnchorGroup .checked input[name="anchor"]').val();
                    var scope = $('#searchScopeGroup .checked input[name="scope"]').val();

                   // if (/[\\u0000-\\u00ff]/.test(value)) {
                        switch (anchor) {
                            case 'startsWith':
                                value = value + "*";
                                break;
                            case 'contains':
                                value = "*" + value + "*";
                                break;
                            case 'exact':
                                // fall through
                                break;
                            default:
                                alert("Error: unknown anchor: '" + anchor + "'")
                        }
                    //}

                    switch (scope) {
                        case 'name':
//                                    console.log("name scope");
                            query = "name:" + value + " OR name_zh:" + value + " OR name_bod_tibt:" + value;
                            break;
                        case 'all':
//                                    console.log('all scope');
                            query = "text:" + value + " OR name_zh:" + value+ " OR name_bod_tibt:" + value;
                            break;
                        default:
                            alert("Error: unknown scope: '" + scope + "'");
                    }
                //}

                // alert("search " + value);
                        console.log("TEXTWIDGET: query " + query);

                widget.set(query);
                if (value /* && self.set(value) */) {
                            console.log("TEXTWIDGET: do Request " + value);
                    widget.doRequest();
                }
            }


			// switch to listview
            $('.listview a').tab('show');
        },


        init: function () {
            var self = this;
//            console.log("TEXTWIDGET: " + $(this.target))
//            console.dir($(this.target));

            $(this.target).on('keyup', function (e) {
//                console.log("keyup " + e);
                // alert("blurt");
                if (e.which == 13) {
                    self.doSearch(self);
                }
            });

            $(this.target).on('doSearch', function(e) {
                console.log("doSearch: " + e);
                self.doSearch(self);
            });

            $("button.searchreset").click( function() {
                    if (self.clear()) {
                        self.doRequest();  // OOPS!  DON'T do the request.
                    };
                    return true; // allow other listeners to fire?
                }
            );
        },

        beforeRequest: function() {
//            console.log("TextWidget: beforeRequest()");
        },

        afterRequest: function () {
//            console.log("TextWidget: afterRequest()");
            $(this.target).find('input').val('');
        }
    });

})(jQuery);






