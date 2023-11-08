<?php

    error_reporting(0);
    //Establece la conexión con la base de datos
    header('Content-Type: application/json');
    header('Access-Control-Allow-Origin: *'); // Esto permite el acceso CORS, modifica según tus necesidades
    
    $servername = 'localhost';
    $username = 'id21336352_admin';
    $password = '62692435Jeison@';
    $dbname = 'id21336352_phpbd';
    
    $conn = new mysqli($servername, $username, $password, $dbname);

    if (!$conn) {
        $respuestaServer = array(
            'estado' => 'serverInactivo',
            'error' => 'No se pudo conectar a la base de datos.'
        );
    } else {
        $respuestaServer = array(
            'estado' => 'serverActivo'
        );
    }
    
    // Convierte la respuesta en JSON y envíala al cliente
    header('Content-Type: application/json');
    echo json_encode($respuestaServer);

?>