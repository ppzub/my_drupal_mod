<?php
/**
* Implements hook_drush_command().
*/
function my_drushcom_drush_command() {
  $items = array();
  $items['create-node'] = array(
    'description' => 'Create custom node with some type and random title',
    //'drupal dependencies' => array('example_drush'),
    'aliases' => array('cn'),
    'arguments' => array(
    'type' => 'Node of this type will be created',
    ),
  );
  return $items;
}

/**
* Create node of specific type.
*/
function drush_my_drushcom_create_node($type){
  global $user;
  if ($type) {
    $values = array(
      'type' => $type,
      'uid' => $user->uid,
      'status' => 1,
      'comment' => 1,
      'promote' => 0,
    );
    $entity = entity_create('node', $values);
    $ewrapper = entity_metadata_wrapper('node', $entity);
    $title = _generateRandomString(15);
    $ewrapper->title->set($title);
    $my_body_content = _generateRandomString(200);
    $ewrapper->body->set(array('value' => $my_body_content));
    $ewrapper->body->summary->set(substr($my_body_content, 0, 50));
    $ewrapper->save();
    
    // Cheking if node was created
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node');
    $query->propertyCondition('type', $type);
    $query->propertyCondition('status', 1);
    $query->fieldCondition('body', 'value', $my_body_content);
    $result = $query->execute();
    if (isset($result['node']))
      $message = t('Node "@title" of "@type" type was created!!!', array('@title' => $title, '@type' => $type));
    else
      $message = t('ERROR: Something go wrong, node wasn\'t created');
    drush_print($message);
  }
  else
    drush_print(t('Specify your content type'));
}

function _generateRandomString($length = 10) {
  $characters = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
  $charactersLength = strlen($characters);
  $randomString = '';
  for ($i = 0; $i < $length; $i++) {
      $randomString .= $characters[mt_rand(0, $charactersLength - 1)];
  }
  return $randomString;
}

/**
* Validate handler for create node command.
*/
function drush_my_drushcom_create_node_validate($type) {
  $types = node_type_get_types();
  if ($type && !in_array($type, array_keys($types))) {
    return drush_set_error('error', t('Content type "@type" is not exists', array('@type' => $type)));
  }
}

