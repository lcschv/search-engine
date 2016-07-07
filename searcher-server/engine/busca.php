<?php 

$val = $_GET['val'];

$content = file_get_contents("http://localhost:8080/".$val); 

echo json_encode(json_decode($content));

?>
