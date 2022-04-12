<?php
function connexion()
{
    $host = 'localhost';
    $dbname = 'autopartage';
    $username = 'root';
    $password = 'root';

    if (isset($_POST['insert'])) {
        try {
            $pdo = new PDO("mysql:host=$host;dbname=$dbname", "$username", "$password");
        } catch (PDOException $exc) {
            echo $exc->getMessage();
            exit();
        }
    }
}
