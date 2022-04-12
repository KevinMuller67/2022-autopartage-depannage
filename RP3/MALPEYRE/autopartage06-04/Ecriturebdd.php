<?php

$host = 'localhost';
$dbname = 'autopartage';
$username = 'root';
$password = 'root';

//connexion a la Bdd
if (isset($_POST['insert'])) {
    try {
        $pdo = new PDO("mysql:host=$host;dbname=$dbname", "$username", "$password");
    } catch (PDOException $exc) {
        echo $exc->getMessage();
        return $pdo;
        exit();
    }
}

$Nom = $_POST['Nom'];
$Adressemail = $_POST['Adressemail'];
$MoyenDePaiement = $_POST['MoyenDePaiement'];
$PapierDesVehicules = $_POST['PapierDesVehicules'];
$MdpProprietaire = $_POST['MdpProprietaire'];
$sql = "INSERT INTO `proprietaire`(`Nom`, `Adressemail`,`MoyenDePaiement`,`PapierDesVehicules`,`MdpProprietaire`) VALUES (:Nom,:Adressemail,:MoyenDePaiement,:PapierDesVehicules,:MdpProprietaire)";
$res = $pdo->prepare($sql);
$exec = $res->execute(array(":Nom" => $Nom, ":Adressemail" => $Adressemail, ":MoyenDePaiement" => $MoyenDePaiement, ":PapierDesVehicules" => $PapierDesVehicules, ":MdpProprietaire" => $MdpProprietaire,));
if ($exec) {
    echo 'Données insérées';
} else {
    echo "Échec de l'opération d'insertion";
}
