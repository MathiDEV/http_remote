<style>
    body {
        text-align: center;
        background-color: #141414;
        color: white;
    }
</style>
<?php
if (isset($_GET["userip"])) {
    $ip = $_GET["userip"];
} else {
    $ip = $_SERVER["REMOTE_ADDR"];
}

if ($ip == "::1") {
    $ip = "127.0.0.1";
}
$id = str_replace(".", "_", $ip);
if (!file_exists("../traces/$id.txt")) {
    die("<span style='color:#dc3545'>Erreur: Aucune moulinette n'est passée sur votre machine</span>");
}

$last_modified = filemtime("../traces/$id.txt");

$trace = file_get_contents("../traces/$id.txt");
$trace = str_replace(["[91m", "[92m", "[93m", "[94m", "[0m", "\n"], ["<span style='color:#dc3545'>", "<span style='color:#28a745'>", "<span style='color:#ffc107'>", "<span style='color:#007bff; font-size: 20px'>", "</span>", "<br>"], $trace);
// echo last modified as datetime
echo "Moulinette du " . date("d/m/Y H:i:s", $last_modified) . "<br><br>";
echo $trace;
?>
