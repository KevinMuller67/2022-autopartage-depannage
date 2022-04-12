package com.example.loginsqlite;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    EditText Email, Password, Repassword;
    Button signup, signin;
    DBHelper DB;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Email = (EditText) findViewById(R.id.Email);
        Password = (EditText) findViewById(R.id.password);
        Repassword = (EditText) findViewById(R.id.repassword);
        signin = (Button) findViewById(R.id.btnsignin);
        signup = (Button) findViewById(R.id.btnsignup);
        DB = new DBHelper(this);

        signup.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String Mail = Email.getText().toString();
                String MotDePasse = Password.getText().toString();
                String ReMotDePasse = Repassword.getText().toString();

                if (Mail.equals("")||MotDePasse.equals("")||ReMotDePasse.equals(""))
                    Toast.makeText(MainActivity.this, "Veuillez entrez les informations suivantes ", Toast.LENGTH_SHORT).show();
                else {
                    if (MotDePasse.equals(ReMotDePasse)){
                        Boolean checkuser = DB.checkEmail(Mail);
                        if (checkuser == false){
                            Boolean insert = DB.insertData(Mail,MotDePasse);
                            if (insert == true){
                                Toast.makeText(MainActivity.this, "Vous êtes bien inscrit", Toast.LENGTH_SHORT).show();
                                Intent intent = new Intent (getApplicationContext(), HomeActivity.class);
                                startActivity(intent);
                            } else {
                                Toast.makeText(MainActivity.this, "Echec de la création du compte", Toast.LENGTH_SHORT).show();
                            }
                        }
                        else {
                            Toast.makeText(MainActivity.this, "L'utilisateur existe déja ! Veuillez vous connecter", Toast.LENGTH_SHORT).show();
                        }
                    }else {
                        Toast.makeText(MainActivity.this, "Les mots de passe ne sont pas identiques !", Toast.LENGTH_SHORT).show();
                    }
                }
            }
        });

        signin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                Intent intent = new Intent(getApplicationContext(), LoginActivity.class);
                startActivity(intent);
            }
        });
    }
}