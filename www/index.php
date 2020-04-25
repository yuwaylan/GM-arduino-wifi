<header>

</header>

<body>

    <?php
    $db = new mysqli('localhost', 'clientt', 'clientt', 'clientt');
    $clear = 'AAA';
    $clear = $_GET['c'];
    if ($db) {

        mysqli_select_db($db, 'clientt');
        #echo ' DB連線成功 ';
        echo "<h2>目前狀態:</h2>";
        $sqlcurrent = "SELECT * FROM `clientt` WHERE `sta`=1";
        $current = $db->query($sqlcurrent);
        $row = mysqli_num_rows($current); //取得資料表資料列數
        $colums = mysqli_num_fields($current); //取得資料表欄位數

        $drow = mysqli_fetch_array($current);
        echo "id:";
        echo "<id value=" . $drow['id_counter'] . ">" . $drow['id_counter'] . "</id>";
        echo " , status:";
<<<<<<< HEAD
        echo "<status value=" . $drow['sta'] . ">" . $drow['sta'] . "</status>";
        echo " , U1:";
        echo $drow['u_pos_1']; //u_pos_1 為馬達狀態
        echo " , U2:";
        echo $drow['u_pos_2'];
        echo " , U3:";
        echo $drow['u_pos_3'];
=======
        echo $drow['sta'];
        echo " , motor satte:";
        echo $drow['motor_state'];
        echo " , listen state:";
        echo $drow['listen_state'];
        echo " , shoot state:";
        echo $drow['shoot_state'];
>>>>>>> 0d45c8713a7d8b2a50297caae04bd46df0ca7c77
        echo " , rfid:";
        echo $drow['rid_pos'];
    } else {
        echo "LINK FAIL!!";
    }

    if ($clear == "chyu126") {
        $sqldelet = "DELETE FROM `clientt` WHERE `id_counter`=99";
        if ($db->query($sqldelet)) {
            echo "test erased";
        }
    }
    $db->close();
    header('refresh:1');
    ?>

    <h2>要看哪個?</h2>
    <h1><a href="./ud.php?mode=all">console page</a></h1>
    <h1><a href="./bk.php?mode=all">Booking queue</a></h1>

    <?php
    $myfile = fopen("C:\Users\user\Documents\GitHub\GM-arduino-wifi\Unity part\status.txt", "w") or die("Unable to open file!");
    $txt = $drow['id_counter'] . "," . $drow['sta'] . "," . $drow['rid_pos'] . "," . $drow['u_pos_1'];
    fwrite($myfile, $txt);
    fclose($myfile);
    ?>

</body>