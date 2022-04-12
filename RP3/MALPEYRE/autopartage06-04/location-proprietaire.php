<html>

<head>
    <title>Auto partage</title>
    <link rel="stylesheet" href="style9.css" type="text/css">
    <?php include 'footer.html'; ?>
    <?php include 'fonction.php'; ?>
</head>

<body>
    <div id="nav">
        <div id="cadre">
            <h1>Autopartage
                <logolycee>
                    <a href="https://lycee-heinrich-nessel.fr/enseignement-superieurs/l-enseignement-superieur/73-bts/215-bts-sn-informations" title="Site du lyc&eacute;e-heinrich-nessel">
                        <img src="image/logolycee.png" alt="logo" style="float:left;width:120px;height:120px;">
                    </a>
                </logolycee>
                <logoconnexion>
                    <a href="connexion.php" title="Connexion">
                        <img src="image/login-button.jpg" alt="connexion" style="float:right;width:120px;height:120px;">
                    </a>
                </logoconnexion>
                <ul id="menu-demo2">
                    <li><a href="index.html">Accueil</a>
                    </li>
                    <li><a href="#">Autopartage</a>
                        <ul>
                            <li><a href="location-client.php">Loueur</a></li>
                            <li><a href="location-proprietaire.php">Propri&eacute;taire</a></li>
                        </ul>
                    </li>
                    <li><a href="#">Question ?</a>
                        <ul>
                            <li><a href="presentation.php">A propos de nous</a></li>
                            <li><a href="Question.php">Foire aux questions</a></li>
                        </ul>
                    </li>
                </ul>
            </h1>
        </div>
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

</html>