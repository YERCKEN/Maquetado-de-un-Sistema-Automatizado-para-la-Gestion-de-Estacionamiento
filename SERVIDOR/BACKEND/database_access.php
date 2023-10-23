<?php
header('Content-Type: application/json');
header('Access-Control-Allow-Origin: *'); // Esto permite el acceso CORS, modifica según tus necesidades

$servername = 'localhost';
$username = 'id21336352_admin';
$password = '62692435Jeison@';
$dbname = 'id21336352_phpbd';

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Conexión fallida: " . $conn->connect_error);
}

$sql = "SELECT park1, park2, park3, park4, park5, park6, park7, park8, park9, park10, park11 FROM Parking WHERE id = 1";
$result = $conn->query($sql);

$data = [];

if ($result->num_rows > 0) {
    echo json_encode($result->fetch_assoc());
} else {
    echo json_encode([]);
}

$conn->close();
?>