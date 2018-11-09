<h4><?php print t('Members'); ?></h4>
<div class="item-list collection-members">
  <ul>
    <?php foreach($group_members as $n => $member): ?>
      <li>
        <?php
            if (strstr($member['user_link'], '</a>')) {
                print $member['user_link'];
            } else {
                // There needs to be some kind of anchor tag around member for styling.
                print '<a name="member-' . $n . '">' . $member['user_link'] . '</a>';
            }
        ?>
      </li>
    <?php endforeach; ?>
  </ul>
</div>
<?php if ($has_inherited_group_members): ?>
  <p><i> * denotes that this member is inherited from a parent collection </i></p>
<?php endif; ?>
