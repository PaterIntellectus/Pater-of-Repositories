<?php
    function redirect_to($header = '/')
    {
        header('Location: ' . $header);
        die();
    }
    function file_add($request, $filename)
    {
        $file = fopen($filename, 'a');
        if ($file)
        {
            fwrite($file, trim($request)."\n");
        }
        fclose($file);
    }
    function file_make_list($filename)
    {
        $file = fopen($filename, 'r') or die('Unable to open file!');
        while (!feof($file))
        {
            $str = fgets($file);
            if ($str) echo ('<li>'.$str.'</li>');
        }
        fclose($file);
    }
    function file_get_first_line($filename)
    {
        $file = file($filename);
        if ($file)
        {
            $line = strval($file[0]);
            unset($file[0]);
            file_put_contents($filename, $file);
        }
        else
        {
            $line = 'NO';
        }
        return trim($line);
    }

    $msg = !empty($_GET['msg']) ? $_GET['msg'] : '';
    if ($msg)
    {
        file_add($msg, 'input.txt');
        die(file_get_first_line('output.txt'));
    }

    $cmd = !empty($_GET['cmd']) ? $_GET['cmd'] : '';
    if ($cmd)
    {
        file_add($cmd, 'output.txt');
        redirect_to();
    }
?>
<!DOCTYPE html>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <title>Enter Form</title>
</head>
<body>
    <div class="container">
        <ul class="list">
            <h3>Список строк файла input.txt:</h3>
            <?php file_make_list('input.txt'); ?>
        </ul>

        <form class="cmd_form" action="/">
            <label>
                Введите команду: <input type="text" name="cmd" autofocus><br>
            </label>
            <input class="btn_submit" type="submit" value="Отправить">
        </form>

        <ul class="list">
            <h3>Список строк файла output.txt:</h3>
            <?php file_make_list('output.txt'); ?>
        </ul>
    </div>
</body>
</html>