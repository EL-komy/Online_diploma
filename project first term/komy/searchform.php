<?php


if($_SERVER["REQUEST_METHOD"] == "POST"){
    $usersearch =$_POST["usersearch"];

    try {
        require_once "includes/dbh.inc.php";
        $qu ="SELECT * from comments where username = ?;";
        $stmt =$pdo->prepare($qu);
        $stmt->execute([$usersearch ]);
        $result=$stmt->fetchAll(PDO::FETCH_ASSOC);
        $pdo =null;
        $stmt = null;
    
    } catch(PDOException $e)
    {
       die("failedd in db ". $e->getMessage());
        
    }

}else{
    header("Location:../index.php");

}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>singup</title>
</head>
<body>
    <h3>RESULT</h3>
    <?php 
    if (empty($result)) {
        echo" NO RESULT";
    }
    else{
        foreach($result as $row)
        {
            echo '<br>';
            echo htmlspecialchars($row["username"]);
            echo htmlspecialchars($row["comment_t"]);
            echo htmlspecialchars($row["create_at"]);
            
        }
    }
    ?>

</body>
</html>