<?php
include "variables.php";
if (!isset($_POST["admin"]) || $_POST["admin"] != $admin_code) {
    http_response_code(400);
    die("You are not authorized to refresh the connections");
}
if (!isset($_POST["ip"])) {
    http_response_code(400);
    die("Error: Missing parameters");
}

$connections = json_decode(file_get_contents("connected.json"), true);
if (!isset($connections[$_POST["ip"]])) {
    http_response_code(400);
    die("Error: Connection not found");
}
unset($connections[$_POST["ip"]]);
file_put_contents("connected.json", json_encode($connections));