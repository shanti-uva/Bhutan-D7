<table class="shanti-texts-record-table table">
    <tbody>
        <?php foreach ($fields as $id => $field): ?>
        <tr class='shanti-texts-field <?php print $id; ?>'>
            <?php if ($field->label != ''): ?>
            <td class='shanti-texts-field-label'>
                <?php print $field->label_html; ?>
            </td>
            <td class='shanti-texts-field-content'>
                <?php print $field->content; ?>
            </td>
            <?php else: ?>
            <td colspan="2" class='shanti-texts-field-content'>
			    <?php print $field->content; ?>
	        </td>
            <?php endif; ?>
        </tr>
        <?php endforeach; ?>
    </tbody>
</table>
