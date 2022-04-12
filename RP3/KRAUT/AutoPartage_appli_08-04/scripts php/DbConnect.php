<?php
//information pour se connecter a la bdd
$servername = "90.63.166.160";
$username = "jules";
$password = "autopartage";
$database = "autopartage";
 
 
//creation d'une nouvelle connexion avec mysqli
$conn = new mysqli($servername, $username, $password, $database);
 
//si on arrive pas a se connecter a la bdd 
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
?>