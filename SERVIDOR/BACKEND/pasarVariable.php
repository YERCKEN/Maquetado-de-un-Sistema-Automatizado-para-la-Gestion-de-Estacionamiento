<?php
$host = 'localhost';
$user = 'id21336352_admin';
$pass = '62692435Jeison@';
$db = 'id21336352_phpbd';

// Crear conexión
$conn = new mysqli($host, $user, $pass, $db);

// Verificar conexión
if ($conn->connect_error) {
    die("Conexión fallida: " . $conn->connect_error);
}

echo "¡Conectado exitosamente!";
?>