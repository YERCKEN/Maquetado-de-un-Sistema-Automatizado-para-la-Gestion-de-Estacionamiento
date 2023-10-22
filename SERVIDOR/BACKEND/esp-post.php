<?php

include 'pasarVariable.php';

if (isset($_POST['park1'], $_POST['park2'], $_POST['park3'], $_POST['park4'], $_POST['park5'], $_POST['park6'], $_POST['park7'], $_POST['park8'], $_POST['park9'], $_POST['park10'], $_POST['park11'])) 
{
    $parking1 = $_POST['park1'];
    $parking2 = $_POST['park2'];
    $parking3 = $_POST['park3'];
    $parking4 = $_POST['park4'];
    $parking5 = $_POST['park5'];
    $parking6 = $_POST['park6'];
    $parking7 = $_POST['park7'];
    $parking8 = $_POST['park8'];
    $parking9 = $_POST['park9'];
    $parking10 = $_POST['park10'];
    $parking11 = $_POST['park11'];

    // Declaración preparada
    $stmt = $conn->prepare("UPDATE Parking SET park1=?, park2=?, park3=?, park4=?, park5=?, park6=?, park7=?, park8=?, park9=?, park10=?, park11=? WHERE id=1");
    $stmt->bind_param("sssssssssss", $parking1, $parking2, $parking3, $parking4, $parking5, $parking6, $parking7, $parking8, $parking9, $parking10, $parking11);

    if ($stmt->execute()) {
        echo "\n Registro en base de datos exitoso! Valor insertado: " . $parking1;
    } else {
        echo "\n Error al registrar en BD: " . $stmt->error;
    }
}

?>




