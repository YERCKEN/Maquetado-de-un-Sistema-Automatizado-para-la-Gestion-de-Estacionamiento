<?php
    require_once 'conex.php';
    function obtenerMovimiento() {
        global $conn;
    
        $sql = "SELECT valor FROM abrecierra WHERE id = 1";
        $result = $conn->query($sql);
    
        if ($result->num_rows > 0) {
            $row = $result->fetch_assoc();
            return $row['valor'];
        } else {
            return null;
        }
    }
?>