package com.example.testpageconnexion;

import android.os.Bundle;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.os.Message;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.bluetooth.BluetoothAdapter;
import android.os.Handler;
import android.util.Log;
import android.content.Intent;
import android.widget.TextView;
import android.widget.EditText;
import android.widget.Toast;
import androidx.annotation.Nullable;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {


    /*Constantes*/
    public final int REQUEST_ENABLE_BT = 1;
    public final int SELECT_PAIRED_DEVICE = 2;


    /*Variables*/
    public static BluetoothAdapter bluetoothAdapter;
    private ArrayList<String> arrayAdapter; //tableau pour afficher les differents appareils disponibles
    private String macConnectedDevice;   //adresse MAC de l'appareil

    //UI
    static TextView tvStatusMessage;
    static TextView tvTextSpace;

    //Threads
    ConnectionThread connect;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // UI
        tvStatusMessage = findViewById(R.id.statusMessage);

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        // Verifie si le Bluetooth est disponible
        if (bluetoothAdapter == null) {
            Toast.makeText(this, "Bluetooth not available", Toast.LENGTH_SHORT).show();
            finish();
            return;
        }


        // Si il existe, authoriser le bluetooth
        if (!bluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }


    }

    //edit
//methode pour appareiller les appareils
    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == REQUEST_ENABLE_BT) {
            if (resultCode == RESULT_OK) {
                Toast.makeText(this, "Bluetooth enabled", Toast.LENGTH_SHORT).show();
            } else {
                Toast.makeText(this, "Bluetooth not available", Toast.LENGTH_SHORT).show();
            }
            finish();
        } else if (requestCode == SELECT_PAIRED_DEVICE) {
            if (resultCode == RESULT_OK) {
                assert data != null;
                tvStatusMessage.setText(String.format("Selected: %s → %s",
                        data.getStringExtra("btDevName"), data.getStringExtra("btDevAddress")));
                macConnectedDevice = data.getStringExtra("btDevAddress");
                connect = new ConnectionThread(data.getStringExtra("btDevAddress"));

            } else {
                tvStatusMessage.setText(R.string.any_connected_devices);
            }
        }


    }

    //methode pour rechercher les appareils a proximite
    public void searchPairedDevices(View view) {
        Intent searchPairedDevicesIntent = new Intent(this, PairedDevices.class);
        startActivityForResult(searchPairedDevicesIntent, SELECT_PAIRED_DEVICE);
    }

    //methode pour se rendre visible des autres appareils
    public void enableVisibility(View view) {
        Intent discoverableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
        discoverableIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 30);
        startActivity(discoverableIntent);
    }

    //methode pour se connecter a l'appareil
    public void connect(View view) {
        Log.d("MAC", macConnectedDevice);
        connect = new ConnectionThread(macConnectedDevice);
        connect.start();
    }

    // Cette partie est pour les messages qui s'affichent comme pour dire si l'app est connecte
    //a l'esp ou non, etc...
    static public Handler handler = new Handler() {

        @Override
        public void handleMessage(Message msg) {

            Bundle bundle = msg.getData();
            byte[] data = bundle.getByteArray("data");
            String dataString = new String(data);

            if (dataString.equals("---N"))
                tvStatusMessage.setText("A connection error has occurred");
            else if (dataString.equals("---S")) tvStatusMessage.setText("Connected");
            else if (dataString.equals("---TO")) tvStatusMessage.setText("Connection Timeout");
            else tvStatusMessage.setText(new String(data)); //BLUETOOTH MESSAGE RECEIPT

        }

    };

    //methode pour envoyer les donnees
    public void sendMessage(View view) {
        EditText messageBox = (EditText) findViewById(R.id.editText_MessageBox);
        String messageString = messageBox.getText().toString();
        byte[] data = messageString.getBytes();
        connect.write(data);
    }


    //Menu
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // "Gonfle" le menu; cela ajoute des éléments à la barre d’action si elle est présente.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        //"Gonfle" le menu; cela ajoute des éléments à la barre d’action si elle est présente.
        // Gére les clics de la barre d’action.
        // La barre d’action gère automatiquement les clics sur le bouton Home/Up,
        // tant qu'on specifie une activité parent dans AndroidManifest.xml.
        int id = item.getItemId();

        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}