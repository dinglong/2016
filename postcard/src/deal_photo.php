<html>
	<head>
		<title>��Ƭ����</title>
		<style type="text/css">
			*{ margin:0; padding:0;}
		
		</style>
		
		<?php
			$str = $_GET['imgUrl'];
		?>
	</head>

	<body>
		<table align="center">
			<tr>
				<td>
					<div align="center" style="width:1000px; height:auto; margin:10px auto;"><img style="width:950px; height:auto;" src="<?php echo $str;?>"/></div>
				</td>
				
				<td>
					<span style="float:right;"><a href="upload.php"><h2>������һҳ��</h2></a></span>
				</td>
			</tr>
		</table>
	</body>



</html>