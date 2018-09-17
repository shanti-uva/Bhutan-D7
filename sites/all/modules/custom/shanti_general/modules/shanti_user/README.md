Shanti User Module
==========================

A module for customizing and enhancing the Drupal User interface for Shanti 
Initially set up to provide a function for admins to add blocks of users _en masse_ to a site and collection.

In Jan. 2018, added ability to fill in user profile fields for first and last name from ldap. 
For this to work, the user entity must have fields "field_lname" (last name) and "field_fname" (first name)

Future uses could be:

* User Preferences for a site: The old user preferences module is included here in the /old folder
* SSO: Probably more complicated that using this module but could it help? See [https://www.drupal.org/node/2402397]
    * Map Netbadge user attributes to user profile. See [https://www.drupal.org/node/2414567] 
* Pan-Shanti Collections: Maybe a separate module than this one? Allows users to have a collection that spans all Shanti sites?
* Customize the User entity types throughout Shanti
* Any User based functionality that we would want on all sites