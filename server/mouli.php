<?php
error_reporting(E_ALL);
ini_set('display_errors', 'On');

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
ob_start();
$ip = $_POST["ip"];
$port = $connections[$_POST["ip"]]["port"];
$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, "http://$ip:$port/getfiles");
curl_setopt($ch, CURLOPT_POST, 1);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
$server_output = curl_exec($ch);
curl_close($ch);
$response = json_decode($server_output, true);

// clear runner directory
$runner = "runner/";

if (is_dir($runner)) {
    exec("rm -rf $runner");
}
mkdir($runner);
chmod($runner, 0777);

$allowed_exts = file_get_contents("mouli/.allowed");
$allowed_exts = explode("\n", $allowed_exts);
foreach ($response as $path => $content) {
    $dirs = explode("/", $path);
    $filename = array_pop($dirs);
    $ext = pathinfo($filename, PATHINFO_EXTENSION);
    if (in_array($ext, $allowed_exts) || $path == "") {
        continue;
    }
    $dir_path = $runner;
    foreach ($dirs as $dir) {
        $dir_path .= $dir . "/";
        if (!file_exists($dir_path)) {
            mkdir($dir_path);
        }
    }
    $file = fopen("$runner$path", "w+");
    $content = base64_decode($content);
    fwrite($file, $content);
    fclose($file);
}
exec("cp -r mouli/* $runner");
chmod("$runner/mouli", 0777);
$id = str_replace(".", "_", $ip);
exec("cd $runner && ./mouli > ../traces/$id.txt && cd ..", $res, $out);
if ($out != 0) {
    http_response_code(400);
    die("Error: Failed to run mouli");
}
die("Success: Mouli ran successfully");
