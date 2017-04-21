<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <title>照片上传</title>

        <style type="text/css">
        	.file_Url{ margin:10px;padding:10px; width:800; height:30; background:#00FF99; border:1px solid #FF0099; font-size:15px;}
        </style>
        
        <?php
   		    $username = $_COOKIE['username'];
			$dir_name = $_COOKIE['dir_name'];
		?>
	</head>

    <body>
        <span style=" border:2px solid #006633;float:right; background-color:#0099FF;"><a href="../index.php" style=" font-family:'宋体'; color:#FF0000;font-size:18px; font-weight:bold; text-decoration:none;">退 出</a></span>
        <table align="center">
            <tr>
                <td align="center">
                    <a href="../index.php"><img src="shouye.jpg"/></a>
                    <span style="float:left;"><a href="upload.php">查看已有照片</a></span>
                    <span style="float:right;">当前用户为：<?php echo $username;?></span>
                </td>
            </tr>
		    <tr><td>
		
            <div align="center" style="margin:10px auto; width:1000; height:300px; font-size:13px; border:3px solid #FF9900;"><br/>
                <h2>照片上传</h2>
                <hr color="#FF9900"/>

                <form action="upload.php" enctype="multipart/form-data" method="post" name="upform">
                    <font style="letter-spacing:1px" color="#FF0000">选择要上传的文件：</font><br/><br/>
                    <input class="file_Url" type="file" name="pictures[]" /><br>

                    <div id="new_up"></div>

                    <a href="#" onClick="add_img()">选择更多图片</a>

                    <input style="width:109px; height:37px; font-weight:bold;" type="submit" value="上 传" name="tijiao"/><br/>
                    <input type="hidden" name="username" value="<?php echo $username?>">
                    <input type="hidden" name="dir_name" value="<?php echo $dir_name?>">
                </form>

                <script type="text/javascript">
                    function add_img(){
                    document.getElementById('new_up').innerHTML+='<input class="file_Url" type="file" name="pictures[]" /><br>';
                    }
                </script>
            </div>
	        </td></tr>
        </table>
    </body>
</html>
