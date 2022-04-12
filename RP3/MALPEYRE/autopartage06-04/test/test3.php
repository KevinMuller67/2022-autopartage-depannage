<?php
////////////////// lorsque des choix sont fait et que la page se recharge ///////////////////////////
if (isset($_POST['region'])) { // si une region à été choisie
  $region = $_POST['region'];
};

if (isset($_POST['producteur'])) { // si un producteur à été choisie
  $producteur = $_POST['producteur'];
};

if (isset($_GET['a'])) { // envoi de la region lorsque le producteur est selectionne
  $region = $_GET['a'];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "autopartage";
try {
  $conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
  $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);



  //afficher les regions
?>
  <form name="region1" method="POST" action="rechercher.php">
    <select name="region" onChange="submit()">';
      <?php
      $res1 = $bdd->query("SELECT DEPARTEMENT,DESIGNATION FROM departement");
      while ($result1 = $res1->fetch()) {
      ?>
        <option value="<?php echo $result1['DEPARTEMENT']; ?>"><?php echo $result1['DESIGNATION']; ?></option>
      <?php
      }
      ?>
    </select>
  </form>
<?php
  // Choisir d'après la region

  if (isset($_POST['region'])) {
    echo '<form name="producteur1" method="POST" action="rechercher.php?a=' . $region . '">';
    echo '<select name="producteur" onChange="submit()">
                 <option>Selectioner un producteur </option>';

    $res3 = $bdd->query("SELECT * FROM famille WHERE FAM_DEPARTEMENT='$region'");
    while ($result3 = $res3->fetch()) {
      echo '<option value="' . $result3['FAMILLE'] . '">' . $result3['FAM_DESIGNATION'] . '</option>';
    };
    echo '</select></form>';
  } else {
    echo '<form name="producteur1" method="POST" action="rechercher.php">';
    echo '<select name="producteur"><option>Selectioner un producteur </option>';
    $res3 = $bdd->query("SELECT * FROM famille");
    while ($result3 = $res3->fetch()) {
      echo '<option value="' . $result3['FAMILLE'] . '">' . $result3['FAM_DESIGNATION'] . '"</option>';
    };
    echo '</select></form>';
  };


  // Choisir d'après le producteur

  if (isset($_POST['producteur']) and isset($_GET['a'])) {

    echo '<form name="vin1" method="POST" action="rechercher.php">';
    echo '<select name="Vin" onChange="submit()">';
    $res2 = $bdd->query("SELECT * FROM article WHERE DEPARTEMENT='$region' AND FAMILLE='$producteur'");
    while ($result2 = $res2->fetch()) {
      echo '<option value="' . $result2['ARTICLE'] . '">' . $result2['DESIGNATION'] . '</option>';
    };
    echo '</select></form>';
  } else {
    echo '<form name="vin1" method="POST" action="rechercher.php">';
    echo '<select name="Vin">';
    $res2 = $bdd->query("SELECT ARTICLE,DESIGNATION,FAMILLE,DEPARTEMENT,PRIX_VENTES_STD FROM article");
    while ($result2 = $res2->fetch()) {
      echo '<option value="' . $result2['ARTICLE'] . '">' . $result2['DESIGNATION'] . '</option>';
    };
    echo '</select></form>';
  };
} catch (Exception $e) {
  die('Erreur : ' . $e->getMessage());
}
?>