<?php
if($_SERVER["REQUEST_METHOD"] == "POST"){
    $username =$_POST["username"];
    $pwd =$_POST["pwd"];
    $email =$_POST["email"];

    try {
        require_once "dbh.inc.php";
        $qu ="UPDATE users set username = ?, pwd =? , email=? where id =4;";
        $stmt =$pdo->prepare($qu);
        $stmt->execute([$username,$pwd,$email ]);
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