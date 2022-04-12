<head>
    <meta charset="utf-8" />
    <title>Insérer des données dans la table Users</title>
    <link rel="stylesheet" type="text/css" href="csstest/style5.css">

</head>

<body>
    <h1>Bienvenue sur notre site</h1>
    <form action="test2.php" method="post">
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
    <br>
    <?php
    echo "<table style='border: solid 1px black ;'>";
    echo "<tr><th>Id</th><th>Nom</th><th>Adresse mail</th><th>Moyen de Paiement</th><th>Papier</th><th>MdpProprietaire</th></tr>";
    class TableRows extends RecursiveIteratorIterator
    {
        function __construct($it)
        {
            parent::__construct($it, self::LEAVES_ONLY);
        }

        function current()
        {
            return "<td style='width:150px;border:1px solid black;'>" . parent::current() . "</td>";
        }

        function beginChildren()
        {
            echo "<tr>";
        }

        function endChildren()
        {
            echo "</tr>" . "\n";
        }
    }

    $servername = "localhost";
    $username = "root";
    $password = "root";
    $dbname = "autopartage";

    try {
        $conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
        $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        $stmt = $conn->prepare("SELECT * FROM proprietaire");
        $stmt->execute();

        // set the resulting array to associative
        $result = $stmt->setFetchMode(PDO::FETCH_ASSOC);
        foreach (new TableRows(new RecursiveArrayIterator($stmt->fetchAll())) as $k => $v) {
            echo $v;
        }
    } catch (PDOException $e) {
        echo "Error: " . $e->getMessage();
    }
    $conn = null;
    echo "</table>";
    ?>
</body>