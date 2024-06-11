<?php
declare(strict_types=1);

function get_username(object $pdo,string $username){
    echo "error in nodf";
    $query ="SELECT username from users where username =:username;";
    $stm = $pdo->prepare($query);
    $stm->bindparam(":username" ,$username );
    $stm->execute();

    $result = $stm->fetch(PDO::FETCH_ASSOC);
    return $result;
    
}

function get_email(object $pdo,string $email){
    $query ="SELECT username from users where username =:email;";
    $stm = $pdo->prepare($query);
    $stm->bindparam(":email" ,$email );
    $stm->execute();

    $result = $stm->fetch(PDO::FETCH_ASSOC);
    return $result;
    
}
