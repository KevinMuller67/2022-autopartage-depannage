<?php 
 
 //on obtient les informations pour se connecter a la bdd
 require_once 'DbConnect.php';
 
 //un tableau pour afficher la réponse
 $response = array();
 
 //si c’est un appel api, cela signifie qu’un paramètre get 
 //nommé api call est défini dans l’URL et avec ce paramètre 
 //nous concluons qu’il s’agit d’un appel api
 if(isset($_GET['apicall'])){
 
 switch($_GET['apicall']){
 
 // partie creation compte
 
 case 'signup':
 
 //verifie si les parametres requises sont disponibles ou non
 if(isTheseParametersAvailable(array('username','email','password','gender'))){
	 //on obtient les valeurs
 $username = $_POST['username']; 
 $email = $_POST['email']; 
 $password = md5($_POST['password']);
 $gender = $_POST['gender']; 
 
 //on verifie si l'utilisateur existe deja avec ce nom ou email
 $stmt = $conn->prepare("SELECT id FROM users WHERE username = ? OR email = ?");
 $stmt->bind_param("ss", $username, $email);
 
 //si l'utilisateur est bien ajouté a la base de donees
 $stmt->execute();
 $stmt->store_result();
 
 //on verifie si le utilisateur existe deja dans la bdd
 if($stmt->num_rows > 0){
 $response['error'] = true;
 $response['message'] = 'User already registered';
 $stmt->close();
 }else{
	 //si l'utilisateur est nouveau, on creer une requete
 $stmt = $conn->prepare("INSERT INTO users (username, email, password, gender) VALUES (?, ?, ?, ?)");
 $stmt->bind_param("ssss", $username, $email, $password, $gender);
 
 //on recupere les informations de l'utilisateur
 if($stmt->execute()){
 $stmt = $conn->prepare("SELECT id, id, username, email, gender FROM users WHERE username = ?"); 
 $stmt->bind_param("s",$username);
 $stmt->execute();
 $stmt->bind_result($userid, $id, $username, $email, $gender);
 $stmt->fetch();
 
 //parametres de user
 $user = array(
 'id'=>$id, 
 'username'=>$username, 
 'email'=>$email,
 'gender'=>$gender
 );
 
 $stmt->close();
 
 // on ajoute les donnees de l'utilisateur dans la reponse
 //et affiche le message suivant
 $response['error'] = false; 
 $response['message'] = 'User registered successfully'; 
 $response['user'] = $user; 
 }
 }
  // ou non
 }else{
 $response['error'] = true; 
 $response['message'] = 'required parameters are not available'; 
 }
 
 break;
 
 //partie connexion
 
 case 'login':
 
 //verifie si les parametres requises sont disponibles ou non
 if(isTheseParametersAvailable(array('username', 'password'))){
 
 //on obtient les valeurs suivantes
 $username = $_POST['username'];
 $password = md5($_POST['password']); 
 
 //on cree la requete
 $stmt = $conn->prepare("SELECT id, username, email, gender FROM users WHERE username = ? AND password = ?");
 $stmt->bind_param("ss",$username, $password);
 
 $stmt->execute();
 
 $stmt->store_result();
 
 // si l'utilisateur existe dans la bdd
 if($stmt->num_rows > 0){
 
 $stmt->bind_result($id, $username, $email, $gender);
 $stmt->fetch();
 
 //parametres de user
 $user = array(
 'id'=>$id, 
 'username'=>$username, 
 'email'=>$email,
 'gender'=>$gender
 );
 
 //affiche sur l'appli que l'utilisateur a bien reussi a se connecter
 $response['error'] = false; 
 $response['message'] = 'Login successfull'; 
 $response['user'] = $user; 
 }else{
	 //affiche sur l'application que le nom ou le mot de passe est incorecte
 $response['error'] = false; 
 $response['message'] = 'Invalid username or password';
 }
 }
 break; 
 
 //si il y a un probleme avec le script
 default: 
 $response['error'] = true; 
 $response['message'] = 'Invalid Operation Called';
 }
  //si ce n'est pas un appel api
  //on affiche le message suivant
 }else{
 $response['error'] = true; 
 $response['message'] = 'Invalid API Call';
 }
 
 //affixhe la reponse en json
 echo json_encode($response);
 
 //C'est une fonction qui valide les parametre disponibles
 //on donne les informations requises a cette fonction
 function isTheseParametersAvailable($params){
 
 //on parcourt tous les paramètres
 foreach($params as $param){
	 //si les parametre ne sont pas disponibles
 if(!isset($_POST[$param])){
 //on retourne un false ou un true si les parametres 
 //sont disponibles
 return false; 
 }
 }
 return true; 
 }