<html>

<head>
    <title>Auto partage</title>
    <link rel="stylesheet" href="style/style.css" type="text/css">
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
                    <a href="connexion.html" title="Connexion">
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
                            <li><a href="presentation.html">A propos de nous</a></li>
                            <li><a href="Question.html">Foire aux questions</a></li>
                        </ul>
                    </li>
                </ul>
            </h1>
        </div>
        <?php
        echo "<table style='border: solid 1px black ;'>";
        echo "<tr><th>Id</th><th>Nom</th><th>AdresseMail</th><th>MoyenDePaiement</th><th>PapierDesVehicules</th><th>MdpProprietaire</th><br/></tr>";
        class TableRows extends RecursiveIteratorIterator
        {
            function __construct($it)
            {
                parent::__construct($it, self::LEAVES_ONLY);
            }
            function current()
            {
                return "<td style='width: 150px; border: 1px solid black;'>" . parent::current() . "</td>";
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

            $result = $stmt->setFetchMode(PDO::FETCH_ASSOC);
            foreach (new TableRows(new RecursiveArrayIterator($stmt->fetchAll())) as $k => $v) {
                echo  $v;
            }
        } catch (PDOException $e) {
            echo "Error: " . $e->getMessage();
        }
        $conn = null;
        echo "</table>";
        ?>
    </div>
    <div id="bas">
        <div id="GCV">
            <p><a href="MentionLegal/CGV.html">Mention legal</p>
            <p><a href="MentionLegal/identification.html">identification</p>
            <p><a href="MentionLegal/traitement.html">traitement</p>
        </div>
    </div>
</body>

</html>