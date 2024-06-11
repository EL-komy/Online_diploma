<?php
declare(strict_types=1);

function check_signup_error(){
    if(isset($_SESSION["errors-signup"]))
    {
        $errors = $_SESSION["errors-signup"];
        echo "<br>";
        foreach($errors as $error)
        {
            echo '<p> '. $error . '</p>';
        }
        //unset($_SESSION["errors-signup"]);
    }
    else{
        echo"error in view";
    }

}