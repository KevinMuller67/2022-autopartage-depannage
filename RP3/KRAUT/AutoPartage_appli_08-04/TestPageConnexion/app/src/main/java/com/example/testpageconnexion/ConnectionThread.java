package com.example.testpageconnexion;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.os.Bundle;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.UUID;



import android.os.Message;


public class ConnectionThread extends Thread{


    private BluetoothSocket bluetoothSocket = null;
    private BluetoothServerSocket bluetoothServerSocket = null;
    private InputStream input;
    private OutputStream output;
    private String bluetoothDevAddress = null;
    private static String myUUID = "00001101-0000-1000-8000-00805F9B34FB";
    private boolean server;
    private boolean running = false;



    // Prépare l'appareil à fonctionner comme un serveur
    ConnectionThread(){
        this.server = true;
    }


    // Prépare l’appareil pour travailler en tant que client
    ConnectionThread(String bluetoothDevAddress){ // → MAC address of device that connection is requested
        this.server = false;
        this.bluetoothDevAddress = bluetoothDevAddress;
    }

    // Processus de connexion
    public void run(){
        this.running = true; // processus qui s'execute
        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        // Selon que le thread fonctionne comme client ou serveur, ses performances seront différentes
        if(this.server){
            // Serveur
            try{
                bluetoothServerSocket = bluetoothAdapter.listenUsingRfcommWithServiceRecord("Bluetooth", UUID.fromString(myUUID));
                bluetoothSocket = bluetoothServerSocket.accept();

                if(bluetoothSocket != null) bluetoothServerSocket.close();

            }catch (IOException e){
                e.printStackTrace();
                toMainActivity("---N".getBytes());
            }
        }else{
            // Client
            Log.d("BluetoothMode", "Client");
            try{
                Log.d("BluetoothAddress", this.bluetoothDevAddress);
                bluetoothAdapter.cancelDiscovery();
                BluetoothDevice bluetoothDevice = bluetoothAdapter.getRemoteDevice(this.bluetoothDevAddress);
                bluetoothSocket = bluetoothDevice.createRfcommSocketToServiceRecord(UUID.fromString(myUUID));

                if(bluetoothSocket != null) {
                    bluetoothSocket.connect();
                    Log.d("BluetoothConnected?", bluetoothSocket.isConnected()+"");
                }
            }catch (IOException e){
                e.printStackTrace();
                toMainActivity("---TO".getBytes());
            }
        }

        if(bluetoothSocket != null){

            toMainActivity("---S".getBytes());
            try{
                input = bluetoothSocket.getInputStream();
                output = bluetoothSocket.getOutputStream();

                byte[] buffer = new byte[1024];
                int bytes;

                while (running){

                    // Lorsque Bluetooth est connecté, lisez les messages à partir de Bluetooth
                    // et les envoyer à Main où ces messages seront traités.
                    bytes = input.read(buffer);
                    toMainActivity(Arrays.copyOfRange(buffer, 0, bytes));
                }

            }catch (IOException e){
                e.printStackTrace();
                toMainActivity("---N".getBytes());
            }
        }
    }

    //methode qui prepare la connexion
    private void toMainActivity(byte[] data) {
        Message message = new Message();
        Bundle bundle = new Bundle();
        bundle.putByteArray("data", data);
        message.setData(bundle);
        MainActivity.handler.sendMessage(message);
    }

    //methode pour envoyer des données
    public void write(byte[] data){

        if(output != null){
            try{
                output.write(data);
            }catch (IOException e){
                e.printStackTrace();
            }
        }else{
            toMainActivity("---N".getBytes());
        }

    }

    //quand on ferme la connexion
    public void cancel(){

        try{
            running = false;
            bluetoothServerSocket.close();
            bluetoothSocket.close();
        }catch (IOException e){
            e.printStackTrace();
        }
        running = false;
    }

}