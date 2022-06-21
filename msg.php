<?php 
    if (!empty($_GET['msg']))
        $msg = $_GET['msg'];
    else
    {
        redirect_to();
        die();
    }
?>
<!DOCTYPE html>
<html>
<head>
    <link rel="stylesheet" href="style.css">
</head>
<body style="text-align: center">
    <form class="cmd_form" method='post' action="/">
        <h3>Сообщение: </h3>
        <h2><?= $msg ?></h2>
        <input type="submit" value="Назад">
    </form>
</body>
</html>