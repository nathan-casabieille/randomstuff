<?php
        $host = 'host';
        $username = 'username';
        $password = 'password';
        $database = 'database';

        try {
            $dsn = 'mysql:host=' . $host . ';dbname=' . $database;
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