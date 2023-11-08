<?php
    include("conex.php");
    header('Access-Control-Allow-Origin: *'); // Esto permite el acceso CORS, modifica según tus necesidades
    

    if(isset($_POST["closeOpen"]) && !empty($_POST["closeOpen"])){

        // Recibe los datos del formulario

        $abrirCerrar = $_POST["closeOpen"];

    
        // Consulta SQL para verificar las credenciales del usuario
        $sql = "UPDATE abrecierra SET valor = '$abrirCerrar' WHERE id = '1'";

        $resultado = mysqli_query($conn, $sql);


        if ($resultado) {
            // Si la actualización fue exitosa, devuelve una respuesta JSON
            $response = array("ok" => true, "message" => "Datos actualizados en la base de datos.");
        } else {
        // Si hubo un error en la actualización, devuelve una respuesta JSON con un mensaje de error
        $response = array("ok" => false, "message" => "Error al actualizar la base de datos.");
        }

        header('Content-Type: application/json');
         echo json_encode($response);
    }
?>