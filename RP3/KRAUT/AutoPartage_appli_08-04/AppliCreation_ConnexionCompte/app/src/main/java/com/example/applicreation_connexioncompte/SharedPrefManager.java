package com.example.applicreation_connexioncompte;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;

public class SharedPrefManager {

    //Constantes
    private static final String SHARED_PREF_NAME = "Jordan";
    private static final String KEY_USERNAME = "cléusername";
    private static final String KEY_EMAIL = "cléemail";
    private static final String KEY_GENDER = "clégenre";
    private static final String KEY_ID = "cléid";

    private static SharedPrefManager mInstance;
    private static Context mCtx;

    private SharedPrefManager (Context context) {
        mCtx = context;
    }

    public static synchronized SharedPrefManager getInstance(Context context) {
        if (mInstance == null) {
            mInstance = new SharedPrefManager(context);
        }
        return mInstance;
    }

    //méthode pour laisser l'utilisateur se logger
    //Cette méthode va stocker les données de l'utilisateur dans Shared preferences
    public void UserLogin (User user) {
        SharedPreferences sharedPreferences = mCtx.getSharedPreferences(SHARED_PREF_NAME, Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putInt(KEY_ID, user.getId());
        editor.putString(KEY_USERNAME, user.getUsername());
        editor.putString(KEY_EMAIL, user.getEmail());
        editor.putString(KEY_GENDER, user.getGender());
        editor.apply();
    }

    //Cette méthode va check si l'utilisateur est loggé ou non
    public boolean isLoggedIn() {
        SharedPreferences sharedPreferences = mCtx.getSharedPreferences(SHARED_PREF_NAME, Context.MODE_PRIVATE);
        return sharedPreferences.getString(KEY_USERNAME, null) != null;
    }

    //cette methode va donner les informations à user
        public User getUser() {
            SharedPreferences sharedPreferences = mCtx.getSharedPreferences(SHARED_PREF_NAME, Context.MODE_PRIVATE);
            return new User(
                    sharedPreferences.getInt(KEY_ID, -1),
                    sharedPreferences.getString(KEY_USERNAME, null),
                    sharedPreferences.getString(KEY_EMAIL, null),
                    sharedPreferences.getString(KEY_GENDER, null)
            );
    }

    //cette methode va deconnecter l'utilisateur
    public void logout() {
        SharedPreferences sharedPreferences = mCtx.getSharedPreferences(SHARED_PREF_NAME, Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.clear();
        editor.apply();
        mCtx.startActivity(new Intent(mCtx, LoginActivity.class));
    }
}


