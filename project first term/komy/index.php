<?php

require_once "includes/config_session.inc.php";
require_once "includes/singup_view.inc.php";
   
?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>singup</title>
</head>
<body>

    <!-- <h3>login</h3>
     <form action="includes/.php" method="POST" >
        <input type="text" name="username">
        <input type="password" name="pwd">
        <button>login</button>
     </form>  -->

     <h3>singn up</h3>
     <form action="includes/usersignup.php" method="POST" >
        <input type="text" name="username">
        <input type="password" name="pwd">
        <input type="text" name="email">
        <button>singn up</button>
     </form> 

     <?php
     check_signup_error();
     ?>
  
</body>
</html>