(function($) {
  /* TODO samchrisinger: Not needed for now, evaluate for removal. If in the future
   * we use template partials this seems like a decent way to register all of the
   * templates with Handlebars.
  Drupal.behaviors.shantiKmapsSolrRegisterPartials = {
    attach: function(context, settings) {
      $('script[type="text/x-handlebars-template"]').each(function(i, tpl) {
        if (/^shantiKmapsSolr/.test($(tpl).attr('id'))) {
          Handlebars.registerPartial($(tpl).attr('id'), tpl.innerHTML);
        }
      });
    }
  };
  */

  Drupal.behaviors.shantiKmapsSolrRegisterHelpers = {
    attach: function(context, settings) {
      Handlebars.registerHelper('eq', function(a, b) {
        return a === b;
      });
      Handlebars.registerHelper('gt', function(a, b) {
        return a > b;
      });
      Handlebars.registerHelper('not', function(a) {
        return !a;
      });
      Handlebars.registerHelper('and', function(a, b) {
        return a && b;
      });
      Handlebars.registerHelper('len', function(a) {
        return (a && a.length) ? a.length : 0;
      });
      Handlebars.registerHelper('plus', function(a, b) {
        return parseFloat(a) + parseFloat(b);
      });
      Handlebars.registerHelper('concat', function() {
        var acc = '';
        $.each(arguments, function(i) {
          acc += arguments[i];
        });
        return acc;
      });

      Handlebars.registerHelper("extractId", function (str) {
        if ($.type(str) === "string" && str.includes("-")) {
          return str.split("-").pop();
        } else {
          return "UNKNOWN";
        }
      });

      Handlebars.registerHelper("ancestorId", function(doc,index) {
        if ($.isArray(doc.ancestor_ids_is)) {
          return doc.ancestor_ids_is[index];
        } else {
          return 0;
        }
      });

      Handlebars.registerHelper("ifCond", function (v1, operator, v2, options) {
        switch (operator) {
          case "==":
            return v1 == v2 ? options.fn(this) : options.inverse(this)
          case "!=":
            return v1 != v2 ? options.fn(this) : options.inverse(this)
          case "===":
            return v1 === v2 ? options.fn(this) : options.inverse(this)
          case "!==":
            return v1 !== v2 ? options.fn(this) : options.inverse(this)
          case "<":
            return v1 < v2 ? options.fn(this) : options.inverse(this)
          case "<=":
            return v1 <= v2 ? options.fn(this) : options.inverse(this)
          case ">":
            return v1 > v2 ? options.fn(this) : options.inverse(this)
          case ">=":
            return v1 >= v2 ? options.fn(this) : options.inverse(this)
          case "&&":
            return v1 && v2 ? options.fn(this) : options.inverse(this)
          case "||":
            return v1 || v2 ? options.fn(this) : options.inverse(this)
          default:
            return options.inverse(this)
        }
      });


    }
  };

  Drupal.behaviors.shantiKmapsFacetsSolr = {
    attach: function(context, settings) {

      // console.log("Drupal.behaviors.shanti_kmaps_facets_solr::attach");
      // console.error("NEED CONFIGURE KMAPSSOLR.   RIGHT NOW WE ARE JUST USING THE INTERNAL DEFAULTS");
    }
  };

})(jQuery);
