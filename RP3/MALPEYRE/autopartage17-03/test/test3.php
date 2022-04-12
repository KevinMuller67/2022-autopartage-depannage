<?php
$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "autopartage";

$Nom = $_POST["Nom"];
$Adressemail = $_POST["Adressemail"];
$MoyenDePaiement = $_POST["MoyenDePaiement"];
$PapierDesVehicules = $_POST["PapierDesVehicules"];
$MdpProprietaire = $_POST["MdpProprietaire"];

try {
    $conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
    // set the PDO error mode to exception
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    $sql = "INSERT INTO proprietaire(Nom, Adressemail, MoyenDePaiement, PapierDesVehicules, MdpProprietaire)
  VALUES(Nom, AdresseMail, MoyenDePaiement, PapierDesVehicules, MdpProprietaire)";
    // use exec() because no results are returned
    $conn->exec($sql);
    echo "New record created successfully";
} catch (PDOException $e) {
    echo $sql . "<br>" . $e->getMessage();
}

$conn = null;
