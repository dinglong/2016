<?php

// 获取表单中的用户名和密码
$username = $_POST['phone_num'];
$pwd = $_POST['password'];

// 用户照片存储地址
$dir_name = $_SERVER['DOCUMENT_ROOT']."/postcard/upload/".$username;

// 链接数据库
$connection = mysql_connect("localhost", "postcard", "postcard");
echo mysql_error();
if ($connection) {
    mysql_select_db("postcard_db", $connection);
    $result = mysql_query("select * from user");

    while($row = mysql_fetch_array($result)) {
        // 如果用户名和密码匹配，弹出add_img页面
        if($row[0] == $username && $row[1] == $pwd) {
            // TODO 需要？
            if($username != $_COOKIE['username']){
                setcookie('username', $username, time()+600,'/');
                setcookie('dir_name', $dir_name, time()+600,'/');
            }
            echo "<script>location.href='add_img.php';</script>";
        } else {
            echo "<script>alert('用户名或密码错误');</script>";
            // echo "<script>location.href='../index.php';</script>";
        }
    }

    // 关闭数据库链接
    // TODO finally方式？
    mysql_close($connection);
} else {
        die('连接数据库失败'. mysql_error());
}

?>