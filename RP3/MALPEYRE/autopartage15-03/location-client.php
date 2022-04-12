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
                    <a href="https://lycee-heinrich-nessel.fr/" title="Site du lyc&eacute;e-heinrich-nessel">
                        <img src="image/logolycee.png" alt="logo" style="float:left;width:120px;height:120px;">
                    </a>
                </logolycee>
                <logoconnexion>
                    <a href="connexion.html" title="Connexion">
                        <img src="image/login-button.jpg" alt="connexion" style="float:right;width:120px;height:120px;">
                    </a>
                </logoconnexion>


            </h1>
        </div>
</body>
<?php
$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "autopartage";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT Nom ,AdresseMail FROM loueur";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
    while ($row = $result->fetch_assoc()) {
        echo "Nom: " . $row["Nom"] . " - Name: " . $row["AdresseMail"] . "<br>";
    }
} else {
    echo "0 results";
}
$conn->close();
