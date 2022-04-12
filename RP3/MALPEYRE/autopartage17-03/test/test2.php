<?php
$serveur = "localhost";
$dbname = "autopartage";
$user = "root";
$pass = "root";

$Nom = $_POST["Nom"];
$Adressemail = $_POST["Adressemail"];
$MoyenDePaiement = $_POST["MoyenDePaiement"];
$PapierDesVehicules = $_POST["PapierDesVehicules"];
$MdpProprietaire = $_POST["MdpProprietaire"];

try {
    //On se connecte à la BDD
    $dbco = new PDO("mysql:host=$serveur;dbname=$dbname", $user, $pass);
    $dbco->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    //On insère les données reçues
    $sth = $dbco->prepare("
            INSERT INTO proprietaire(Nom, Adressemail, MoyenDePaiement, PapierDesVehicules, MdpProprietaire)
            VALUES(Nom, AdresseMail, MoyenDePaiement, PapierDesVehicules, MdpProprietaire)");
    $sth->bindParam('Nom', $Nom);
    $sth->bindParam('Adressemail', $Adressemail);
    $sth->bindParam('MoyenDePaiement', $MoyenDePaiement);
    $sth->bindParam('PapierDesVehicules', $PapierDesVehicules);
    $sth->bindParam('MdpProprietaire', $MdpProprietaire);
    $sth->execute();
} catch (PDOException $e) {
    echo 'Impossible de traiter les données. Erreur : ' . $e->getMessage();
}
