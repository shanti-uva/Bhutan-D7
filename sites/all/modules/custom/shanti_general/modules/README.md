shanti_general modules
=============================
The submodules within shanti_general are wither for integrating with the Drupal Shanti Sarvaka theme or general use modules for
all Shanti sites. The modules are:

1. explore_menu: a module that creates a block for placing in the top bar that creates the link and drop down explore menu.
2. features: Drupal Features created for Shanti Mandala Sites
    2a: Shanti Admin Features: provides enhanced views for shanti/admin/content and shanti/admin/people with VBO capabilities
    2b: Shanti Pager: a feature the defines the core_pager using the Pagerer module
3. jira_collector: provides a block with a button for submitting a JIRA for bugs.
4. shanti_carousel: Defines a general carousel block to use in any Shanti mandala site
5. shanti_user: This module is for specific functions around shanti's custom user type This includes under "old" the prefious
     "user_prefs" module which was a module for adding the user preference form to the multi-level menu in the top bar. 
     It saves the settings on a user by user basis and makes them available in the Drupal.settings JS object. 
     (Note: Need to add PHP api functions to access the settings via PHP.)

These were taken from Shanti Sarvaka and moved into Shanti General as a way to have them all in same place. 