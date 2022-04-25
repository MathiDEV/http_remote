<?php
include "variables.php";
header("Content-Type: text/; charset=utf-8");
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
curl_setopt($ch, CURLOPT_URL, "http://$ip:$port/cat");
curl_setopt($ch, CURLOPT_POST, 1);
curl_setopt($ch,CURLOPT_RETURNTRANSFER,1);
curl_setopt($ch, CURLOPT_POSTFIELDS, "dir=".$_POST["dir"]);
$server_output = curl_exec($ch);
$status = curl_getinfo($ch, CURLINFO_HTTP_CODE);
if ($status != 200) {
    http_response_code(400);
    die("Error: Connection not found");
}
echo (utf8_decode($server_output));
curl_close($ch);
