<html>
    <head>
        <title>�û�XXX�ϴ�����Ƭ</title>

		<style type="text/css">
			*{ margin:0; padding:0;}
			#imgList{ list-style:none;}
			.li_css{ float:left; margin:10px;}
			.img_css{ border:1px solid #CC9900; width:200px; height:200px;}
		</style>
		
		<?php
            function upload_multi($dir_name, $photo, $i) {
                $tp = array("image/gif", "image/pjpeg", "image/jpeg", "image/bmp", "image/jpg");

                $path = $dir_name."/".$photo["name"][$i];
                $upfile = $photo["tmp_name"][$i];

                //����ϴ��ļ��Ƿ��������ϴ�������
                if($photo["name"][$i]){
                	if(in_array($photo["type"][$i], $tp)){
                		move_uploaded_file($upfile, iconv("UTF-8", "gb2312", $path));
                	}else{
                		echo "<script>alert('���ļ����Ͳ���ͼƬ��');</script>";
                	}
                }		
            }

            $user_name = $_COOKIE['username'];
            $dir_name = $_COOKIE['dir_name'];

            if($_POST['tijiao']) {
                extract($_POST);
                $photo = $_FILES["pictures"];

                if(!file_exists($dir_name)) {
                    mkdir($dir_name, 0777, true);
                }

                $index=0;
                foreach ($photo["error"] as $key => $error) {
                    if ($error == UPLOAD_ERR_OK){
                        upload_multi($dir_name, $photo, $index);
                    } else {
                        echo "<script>alert('�ϴ�������!');<script/>";
                        break;
                    }
                    $index++;
                }
            }
		?>

		<?php
            $user_name = $_COOKIE['username'];
            $dir_name = $_COOKIE['dir_name'];

            $img = array('gif','GIF','png','PNG','jpg','JPG','pjpeg','PJPEG','jpeg','JPEG','bmp','BMP'); //����ͼƬ�ĺ�׺��
            $dir = $dir_Name.'/'; //�ļ�������
            $pic = array();

            foreach($img as $k=>$v) {
                $pattern = $dir.'*.'.$v;
                $all = glob($pattern);  //�ú�������һ��������ƥ���ļ� / Ŀ¼�����顣��������� false��
                $pic = array_merge($pic,$all);
            }
		?>
	</head>
	
	<body>
        <div style=" margin:10px auto; width:1300px; height:200px;" align="center"><img src="9.jpg" /></div>
        <div style="width:1300px; text-align:center;"><a href="../index.php">������ҳ</a>||<a href="add_img.php">�ϴ���Ƭ</a><span style="float:right;"><h3>��ǰ�û�Ϊ��<?php echo $user_name; ?></h3></span></div>

        <div>
            <ul id="imgList">
                <?php
                    // echo $dir;
                    foreach($pic as $p){		
                        // $str = '<li class="li_css"><a href="deal_photo.php?imgUrl='.$p.'"><img class="img_css" src="'.$p.'" onclick="setCookie(this)"/></a></li>';
                        // echo $str;
                        // document.getElementById('imgList').innerHTML+=$str;
                    }
                ?>
            </ul>
        </div>
	</body>
</html>
