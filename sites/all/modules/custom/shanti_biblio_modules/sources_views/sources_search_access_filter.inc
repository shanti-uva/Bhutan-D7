<?php

/**
 * @file
 * Contains SearchApiAlterAddUrl.
 */

/**
 * Search API data alteration callback that adds an URL field for all items.
 */
class SourcesSearchAccessFilter extends SearchApiAbstractAlterCallback {

  /**
   *
   */
  public function alterItems(array &$items) {
    $anon = user_load(0);
    foreach ($items as $n => $node) {
      $viewable = node_access('view', $node, $anon);
      if (!$viewable) {
        unset($items[$n]);
      }
    }
  }

}
