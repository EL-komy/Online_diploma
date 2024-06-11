<?php
if($_SERVER["REQUEST_METHOD"] == "POST"){
    $username =$_POST["username"];
    $pwd =$_POST["pwd"];

    try {
        require_once "dbh.inc.php";
        $qu ="DELETE from users where username =? and pwd=?;";
        $stmt =$pdo->prepare($qu);
        $stmt->execute([$username,$pwd]);
        $pdo =null;
        $stmt = null;
        header("Location:../index.php");
        exit();
    } catch(PDOException $e)
    {
       die("failedd in db ". $e->getMessage());
        
    }

}else{
    header("Location:../index.php");

}