<?php

// ��ȡ���е��û���������
$username = $_POST['phone_num'];
$pwd = $_POST['password'];

// �û���Ƭ�洢��ַ
$dir_name = $_SERVER['DOCUMENT_ROOT']."/postcard/upload/".$username;

// �������ݿ�
$connection = mysql_connect("localhost", "postcard", "postcard");
echo mysql_error();
if ($connection) {
    mysql_select_db("postcard_db", $connection);
    $result = mysql_query("select * from user");

    while($row = mysql_fetch_array($result)) {
        // ����û���������ƥ�䣬����add_imgҳ��
        if($row[0] == $username && $row[1] == $pwd) {
            // TODO ��Ҫ��
            if($username != $_COOKIE['username']){
                setcookie('username', $username, time()+600,'/');
                setcookie('dir_name', $dir_name, time()+600,'/');
            }
            echo "<script>location.href='add_img.php';</script>";
        } else {
            echo "<script>alert('�û������������');</script>";
            // echo "<script>location.href='../index.php';</script>";
        }
    }

    // �ر����ݿ�����
    // TODO finally��ʽ��
    mysql_close($connection);
} else {
        die('�������ݿ�ʧ��'. mysql_error());
}

?>