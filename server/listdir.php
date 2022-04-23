<?php
include "variables.php";

header("Content-Type: application/json");
if (!isset($_POST["admin"]) || $_POST["admin"] != $admin_code) {
    http_response_code(400);
    die("You are not authorized to refresh the connections");
}
if (!isset($_POST["ip"]) || !isset($_POST["dir"])) {
    http_response_code(400);
    die("Error: Missing parameters");
}

$connections = json_decode(file_get_contents("connected.json"), true);
if (!isset($connections[$_POST["ip"]])) {
    http_response_code(400);
    die("Error: Connection not found");
}
$ip = $_POST["ip"];
$port = $connections[$_POST["ip"]]["port"];
$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, "http://$ip:$port/ls");
curl_setopt($ch, CURLOPT_POST, 1);
curl_setopt($ch, CURLOPT_POSTFIELDS, "dir=".$_POST["dir"]);
$server_output = curl_exec($ch);
curl_close($ch);
