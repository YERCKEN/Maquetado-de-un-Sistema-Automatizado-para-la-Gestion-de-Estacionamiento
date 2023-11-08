<?php
    header('Content-Type: application/json');
    header('Access-Control-Allow-Origin: *'); // Esto permite el acceso CORS, modifica según tus necesidades
    //importar la configuración de conexión...
    include('conex.php');
        
    
    if(isset($_POST['nombreUsuario']) && !empty($_POST['nombreUsuario']) && isset($_POST['accesoClave']) && !empty($_POST['accesoClave'])){

        // Recibe los datos del formulario
        $usuario = $_POST["nombreUsuario"];

        $contrasena = $_POST["accesoClave"];
    
        // Consulta SQL para verificar las credenciales del usuario
        $sql = "SELECT * FROM usua WHERE nombre = '$usuario' && contrasena = '$contrasena'";
        $resultado = mysqli_query($conn, $sql);
    
        if (mysqli_num_rows($resultado) > 0) {

            echo json_encode(array('success'=>1));
            // Inicio de sesión exitoso

        } else {
            // Inicio de sesión fallido
            echo json_encode(array('success'=>0));
        }
        
    }
?>
