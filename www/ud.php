<header>
    <?php

    $cid = strval($_GET['c']);
    $status = strval($_GET['s']);
    $u1 = strval($_GET['u1']);
    $u2 = strval($_GET['u2']);
    $u3 = strval($_GET['u3']);
    $rfidtag = strval($_GET['r']);

    $db = new mysqli('localhost', 'clientt', 'clientt', 'clientt');


    if (!$db) {
    } else {

        mysqli_select_db($db, 'clientt');
        // echo ' DB連線成功 ';

        $sqlsearch = "SELECT `id_counter`, `sta`, `u_pos_1`, `u_pos_2`, `u_pos_3`, `rid_pos` FROM `clientt` WHERE `id_counter`  =$cid";
        $hadid = $db->query($sqlsearch);
        if ($hadid->num_rows > 0) {
            //修改
            $sqlfix = "UPDATE `clientt` SET `sta`=$status,`u_pos_1`=$u1,`u_pos_2`=$u2,`u_pos_3`=$u3,`rid_pos`=$rfidtag WHERE`id_counter`= $cid";
            $fixgood = $db->query($sqlfix);
            if ($fixgood) {
                echo "fix";
            } else
                echo "fix fail";
        } else {
            //新增
            $sqladd = "INSERT INTO `clientt` (`id_counter`, `sta`, `u_pos_1`, `u_pos_2`, `u_pos_3`, `rid_pos`) VALUES (' $cid ', '$status', '$u1', '$u2', '$u3', '$rfidtag')";
            $add = $db->query($sqladd);
            if ($add) {
                /*echo "sent c :";
                echo $cid;
                echo "<br> sent s :";
                echo $status;
                echo " <br>  sent u1:";
                echo $u1;
                echo " <br> sent u2:";
                echo $u2;
                echo " <br> sent u3 :";
                echo $u3;
                echo "<br> sent r :";
                echo $rfidtag;*/
                echo "new";
            } else {
                echo $db->error;
            }
        }
    }
    $db->close();


    #SELECT `id_counter`, `sta`, `u_pos_1`, `u_pos_2`, `u_pos_3`, `rid_pos` FROM `clientt` WHERE `id_counter`  =122
    ?>
</header>

<body>

</body>