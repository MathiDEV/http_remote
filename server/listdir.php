<?php
include "variables.php";
header("Content-Type: application/json");
if (!isset($_POST["admin"]) || $_POST["admin"] != $admin_code) {
    http_response_code(400);
    die("Error: You are not authorized to list this directory");
    exit;
}
if (!isset($_POST["ip"]) || !isset($_POST["dir"])) {
    http_response_code(400);
    die("Error: Missing parameters");
    exit;
}

$connections = json_decode(file_get_contents("connected.json"), true);
if (!isset($connections[$_POST["ip"]]) || !$connections[$_POST["ip"]]["active"]) {
    http_response_code(400);
    die("Error: Connection not found");
    exit;
}
$ip = $_POST["ip"];
$port = $connections[$_POST["ip"]]["port"];
$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, "http://$ip:$port/ls");
curl_setopt($ch, CURLOPT_POST, 1);
curl_setopt($ch,CURLOPT_RETURNTRANSFER,1);
curl_setopt($ch, CURLOPT_POSTFIELDS, "dir=".$_POST["dir"]);
$server_output = curl_exec($ch);
$server_output = str_replace("\\", "/" , $server_output);
$server_output = str_replace("//", "/" , $server_output);
$server_output = str_replace("./", "" , $server_output);
$status = curl_getinfo($ch, CURLINFO_HTTP_CODE);
if ($status != 200) {
    http_response_code(400);
    die("Error: Connection not found");
}
echo $server_output;
curl_close($ch);
