<?php
        $host = 'host';
        $db_name = 'database';
        $username = 'username';
        $password = 'password';

        try {
            $dsn = 'mysql:host=' . $host . ';dbname=' . $db_name;
            $db = new PDO($dns, $username, $password);
            $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        }
        catch (Exception $exception){
            die ('Error : ' . $exception->getMessage());
        }

        $id = $_GET['id'];
        $data = $_GET['data'];

        $query = $db->prepare('INSERT INTO Table (id, data) VALUES (?, ?)');
        $query->execute(array($id, $data));
?>
