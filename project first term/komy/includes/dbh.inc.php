<?php
$dsn ="mysql:host=localhost;dbname=firstdatabase";
$dbusername= "root";
$dbpassword ="";

try {
    echo "error in db";
    $pdo =new PDO($dsn, $dbusername,$dbpassword );
    $pdo->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);
    } 
catch(PDOException $e)
{
   die("failedd ". $e->getMessage());
    
}
