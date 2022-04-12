<!DOCTYPE html>
<html>

<head>Afficher la table users</head>

<body>
    <form action="Ecriturebdd.php" method="post">
        <TABLE BORDER=1 style="margin-left: 40%;margin-right: 40%;">
            <TR>
                <TD>Nom</TD>
                <TD>
                    <INPUT type=text name="Nom">
                </TD>
            </TR>
            <TR>
                <TD>Adresse Mail</TD>
                <TD>
                    <INPUT type=text name="Adressemail">
                </TD>
            </TR>
            <TR>
                <TD>Moyen De Paiement</TD>
                <TD>
                    <INPUT type=text name="MoyenDePaiement">
                </TD>
            </TR>
            <TR>
                <TD>Papier Des Vehicules</TD>
                <TD>
                    <INPUT type=text name="PapierDesVehicules">
                </TD>
            </TR>
            <TR>
                <TD>Mot de passe</TD>
                <TD>
                    <INPUT type=text name="MdpProprietaire">
                </TD>
            </TR>
            <TR>
                <TD COLSPAN=2>
                    <input type="submit" name="insert" value="Ins&eacute;rer">
                </TD>
            </TR>
        </TABLE>
    </FORM>
    <?php
    // ce fichier PHP est lancé via le formulaire dans index.HTML
    //les données sont reçues grace à la méthode POST du protocole HTTP utilisée dans index.html
    // les données sont celles saisies dans le formulaire
    $host = 'localhost';
    $dbname = 'autopartage';
    $username = 'root';
    $password = 'root';
    //si on a cliqué sur la zone nommée "insert" dans le formulaire HTML
    //               <p><input type="submit" name="insert" value="Insérer"></p>
    if (isset($_POST['insert'])) {
        try {
            // se connecter à la BDD mysql
            $pdo = new PDO("mysql:host=$host;dbname=$dbname", "$username", "$password");
        } catch (PDOException $exc) {
            echo $exc->getMessage();
            exit();
        }
        $sql = "INSERT INTO `proprietaire`(`Nom`, `Adressemail`,`MoyenDePaiement`,`PapierDesVehicules`,`MdpProprietaire`) VALUES (:Nom,:Adressemail,:MoyenDePaiement,:PapierDesVehicules,:MdpProprietaire)";
        $res = $pdo->prepare($sql);
        $exec = $res->execute(array(":Nom" => $Nom, ":Adressemail" => $Adressemail, ":MoyenDePaiement" => $MoyenDePaiement, ":PapierDesVehicules" => $PapierDesVehicules, ":MdpProprietaire" => $MdpProprietaire,));
        // vérifier si la requête d'insertion a réussi
        if ($exec) {
            echo 'Données insérées';
        } else {
            echo "Échec de l'opération d'insertion";
        }
    }
    ?>
</body>

</html>