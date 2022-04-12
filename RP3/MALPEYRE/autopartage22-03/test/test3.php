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
  // récupérer les valeurs 
  $Latitude = $_POST['Latitude'];
  $Longitude = $_POST['Longitude'];
  // Requête mysql pour insérer des données
  $sql = "INSERT INTO `gps`(`Latitude`, `Longitude`) VALUES (:Latitude,:Longitude)";
  $res = $pdo->prepare($sql);
  $exec = $res->execute(array(":Latitude" => $Latitude, ":Longitude" => $Longitude));
  // vérifier si la requête d'insertion a réussi
  if ($exec) {
    echo 'Données insérées';
  } else {
    echo "Échec de l'opération d'insertion";
  }
}
