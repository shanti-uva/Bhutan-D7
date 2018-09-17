<?php 

/**
 * Implements hook_feeds_processor_targets_alter().
 */

function shanti_kmaps_fields_feeds_processor_targets_alter(&$targets, $entity_type, $bundle_name) 
{
    foreach (field_info_instances($entity_type, $bundle_name) as $name => $instance) {
        $info = field_info_field($name);
        if ($info['type'] == 'shanti_kmaps_fields_default') {
            foreach ($info['columns'] as $sub_field => $schema_info) {
                $name_label = $instance['label'] . ': ' . drupal_ucfirst(str_replace('_', ' ', $sub_field));
                $targets[$name . ':' . $sub_field] = array(
                    'name' => $name_label, 
                    'callback' => 'shanti_kmaps_fields_set_target',
                    'real_target' => $info['field_name'], 
                    'description' => $schema_info['description'],
                );
            }
        }
    }
}

/**
 * Mapping callback.
 */

function shanti_kmaps_fields_set_target($source, $entity, $target, $value, $mapping) 
{
    $entity->{$target}[$entity->language][0]['value'] = $value;
    if (isset($source->importer->processor->config['input_format'])) {
        $entity->{$target}[$entity->language][0]['format'] = $source->importer->processor->config['input_format'];
    }
}