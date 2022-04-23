<?php
include "variables.php";

if (!isset($_POST["name"]) || !isset($_POST["port"]) || !isset($_POST["os"])) {
    http_response_code(400);
    die("Error: Missing parameters");
}
$ip = $_SERVER["REMOTE_ADDR"];
if ($ip == "::1") {
    $ip = "127.0.0.1";
}
$connected = json_decode(file_get_contents("connected.json"), true);
$connected[$ip] = ["name"=> $_POST["name"], "port" =>$_POST["port"], "os" => $_POST["os"]];
file_put_contents("connected.json", json_encode($connected));
?>