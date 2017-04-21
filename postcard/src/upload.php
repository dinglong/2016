<html>
    <head>
        <title>用户XXX上传的照片</title>

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

                //检查上传文件是否在允许上传的类型
                if($photo["name"][$i]){
                	if(in_array($photo["type"][$i], $tp)){
                		move_uploaded_file($upfile, iconv("UTF-8", "gb2312", $path));
                	}else{
                		echo "<script>alert('有文件类型不是图片！');</script>";
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
                        echo "<script>alert('上传有问题!');<script/>";
                        break;
                    }
                    $index++;
                }
            }
		?>

		<?php
            $user_name = $_COOKIE['username'];
            $dir_name = $_COOKIE['dir_name'];

            $img = array('gif','GIF','png','PNG','jpg','JPG','pjpeg','PJPEG','jpeg','JPEG','bmp','BMP'); //所有图片的后缀名
            $dir = $dir_Name.'/'; //文件夹名称
            $pic = array();

            foreach($img as $k=>$v) {
                $pattern = $dir.'*.'.$v;
                $all = glob($pattern);  //该函数返回一个包含有匹配文件 / 目录的数组。如果出错返回 false。
                $pic = array_merge($pic,$all);
            }
		?>
	</head>
	
	<body>
        <div style=" margin:10px auto; width:1300px; height:200px;" align="center"><img src="9.jpg" /></div>
        <div style="width:1300px; text-align:center;"><a href="../index.php">返回首页</a>||<a href="add_img.php">上传照片</a><span style="float:right;"><h3>当前用户为：<?php echo $user_name; ?></h3></span></div>

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
