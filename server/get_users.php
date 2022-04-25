<?php
include "variables.php";

header("Content-Type: application/json");
if (!isset($_POST["admin"]) || $_POST["admin"] != $admin_code) {
    http_response_code(400);
    die("You are not authorized to refresh the connections");
}

$connections = json_decode(file_get_contents("connected.json"), true);
foreach ($connections as $ip=>$connection) {
    $port = $connection["port"];
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, "http://$ip:$port/ping");
    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 0);
    curl_setopt($ch, CURLOPT_TIMEOUT, 3);
    $server_output = curl_exec($ch);
    curl_close($ch);
    $connections[$ip]["active"] = $server_output == "200";
}
file_put_contents("connected.json", json_encode($connections));
echo json_encode($connections);