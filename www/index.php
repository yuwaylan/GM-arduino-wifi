<header>
    <?php
    $db = new mysqli('localhost', 'clientt', 'clientt', 'clientt');
    $clear = 'AAA';
    $clear = $_GET['c'];
    if ($db) {

        mysqli_select_db($db, 'clientt');
        #echo ' DB連線成功 ';
        echo "<h2>目前狀態:</h2>";
        $sqlcurrent = "SELECT * FROM `clientt` WHERE `sta`=99";
        $current = $db->query($sqlcurrent);
        $row = mysqli_num_rows($current); //取得資料表資料列數
        $colums = mysqli_num_fields($current); //取得資料表欄位數

        $drow = mysqli_fetch_array($current);
        echo "id:";
        echo $drow['id_counter'];
        echo " , status:";
        echo $drow['sta'];
        echo " , U1:";
        echo $drow['u_pos_1'];
        echo " , U2:";
        echo $drow['u_pos_2'];
        echo " , U3:";
        echo $drow['u_pos_3'];
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

</header>

<body>


    <h2>要看哪個?</h2>
    <h1><a href="./ud.php?mode=all">console page</a></h1>
    <h1><a href="./bk.php?mode=all">Booking queue</a></h1>

</body>