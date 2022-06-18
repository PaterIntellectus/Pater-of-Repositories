<?php
    function redirect_to_index()
    {
        header('Location: /');
        die();
    }
    function add_strArray_into_file($request, $filename)
    {
        $file = fopen($filename, 'a');
        if ($file)
        {
            fwrite($file, trim($request)."\n");
        }
        fclose($file);
    }
    function make_list_from_file($filename)
    {
        $file = fopen($filename, 'r') or die('Unable to open file!');
        while (!feof($file))
        {
            $str = fgets($file);
            if ($str) echo ('<li>'.$str.'</li>');
        }
        fclose($file);
    }
    function get_first_line_of_file($filename)
    {
        $file = file($filename);
        $line = $file[0];
        $file[0] = '';
        echo $file;
        file_put_contents($filename, $file);
        return $line;
    }

    $msg = !empty($_GET['msg']) ? $_GET['msg'] : '';
    $cmd = !empty($_GET['cmd']) ? $_GET['cmd'] : '';

    // getting request from an application
    if ($msg || $cmd)
    {
        if ($msg)
        {
            add_strArray_into_file($msg, 'input.txt');
            echo (get_first_line_of_file('output.txt'));
        }
        if ($cmd)
        {
            add_strArray_into_file($cmd, 'output.txt');
        }
        redirect_to_index();
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
            <?php make_list_from_file('input.txt'); ?>
        </ul>

        <form class="cmd_form" action="index.php">
            <label>
                Введите команду: <input type="text" name="cmd" autofocus><br>
            </label>
            <input class="btn_submit" type="Submit" value="Отправить">
        </form>

        <ul class="list">
            <h3>Список строк файла output.txt:</h3>
            <?php make_list_from_file('output.txt'); ?>
        </ul>
    </div>
</body>
</html>