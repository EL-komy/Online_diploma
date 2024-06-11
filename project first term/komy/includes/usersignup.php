<?php
echo "error in sinup";
if($_SERVER["REQUEST_METHOD"] == "POST"){
    $username =$_POST["username"];
    $pwd =$_POST["pwd"];
    $email =$_POST["email"];

    try {
        echo "hhh";
        require_once "dbh.inc.php";
        require_once "singup_model.inc.php";
        require_once "singup_contr.inc.php";

        $errors = [];

        if (is_input_empty($username , $pwd , $email)) {
            $errors["empty_input"]="fill in all fields"; 
        }
        if (is_email_invalid( $email)) {
            $errors["invalid_email"]="invalid email used"; 
        }
        if (is_username_taken ( $pdo, $username)) {
            $errors["username_taken"]="username is taken"; 
        }
        if(is_email_registered (  $pdo,  $email))
        {
            $errors["email_registered"]="email is registered"; 
        }

        echo $errors;
        

        require_once "config_session.inc.php";

        if($errors)
        {
            $_SESSION["errors_signup"] =$errors;
            header("Location:../index.php");
        }



    
        
    } catch(PDOException $e)
    {
        echo"ggg";
       die("failedd in db ". $e->getMessage());
        
    }

}else{
    header("Location:../index.php");
    echo"ggg";
    die();
}