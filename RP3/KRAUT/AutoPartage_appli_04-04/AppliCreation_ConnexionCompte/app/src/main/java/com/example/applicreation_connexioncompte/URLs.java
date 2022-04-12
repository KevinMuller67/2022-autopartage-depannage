package com.example.applicreation_connexioncompte;

public class URLs {
    //url pour appeler le script pour lire et ecrire dans la base de donnee
    private static final String ROOT_URL = "http://192.168.124.111/projettest/Api.php?apicall=" ;

    public static final String URL_REGISTER = ROOT_URL + "signup";
    public static final String URL_LOGIN= ROOT_URL + "login";
}
