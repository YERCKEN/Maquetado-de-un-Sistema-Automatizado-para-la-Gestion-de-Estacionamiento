<?php

    error_reporting(0);
    //Establece la conexión con la base de datos
    $conn = mysqli_connect('localhost', 'root', '', 'usuarios');

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