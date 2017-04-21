<html>
    <head>
        <title>邮政明信片制作及邮寄平台</title>

        <style type="text/css">
            .txt{ime-mode:disabled; padding:0px; width:300; height:40; background:#66CC00; text-align:center; border:2px solid #FF0099; font-size:30px; font-weight:bold; vertical-align:middle;}
            p.word{ font-weight:bold; font-size:20px; height:auto;}
            .btn{ width:70px; height:35px; background:#9966CC; border:3px solid #FF99CC;}
        </style>

        <script type="text/javascript">
            function getfocus(obj){
                //var spanElement = document.getElementById(obj);
                obj.style.cssText = "padding:0px; width:300; height:40;  background:#FFCC00; border:2px solid #660066; text-align:center; font-size:30px; font-weight:bold; vertical-align:middle;";
            }

            function lostfocus(obj){
                //var spanElement = document.getElementById("txt1");
　　            obj.style.cssText = "padding:0px; width:300; height:40;  background:#66CC00; text-align:center; border:2px solid #FF0099; font-size:30px; font-weight:bold; vertical-align:middle;";
            }
        </script>

        <script language = javascript>
            var curIndex = 0;
            var timeInterval = 1000;
            var arr = new Array();
            for(var i=0; i<12; i++){
                arr[i] = "image/head/" + i + ".jpg";
            }
            setInterval(changeImg, timeInterval);
            function changeImg() {
                var obj=document.getElementById("obj");
                if (curIndex == arr.length-1){
                    curIndex = 0;
                }
                else{
                    curIndex+=1;
                }
                obj.src=arr[curIndex];
            }
        </script>

        <script type="text/javascript">
                function checkMobile(){
                    var str = document.login_form.phone_num.value;

                    var reges_admin = "admin";
                    var regex_user = /^1[3|5|7|8|][0-9]{9}$/;
                    if (reges_admin.test(str) || regex_user.test(str)){
                        return true;
                    }else{
                        alert("请输入正确的手机号码！");
                        return false;
                    }
                }
        </script>
    </head>

    <body bgcolor="#FF9933">
        <table align="center" border="0"><tr><td><img width="1000" height="200" src="image/top.jpg"/></td></tr></table>

        <form name="login_form" action="src/login_check.php" method="post" onSubmit="return checkMobile();">
            <table align="center" style="border:2px solid #FF0099;">
                <tr>
                    <td rowspan="4"><img id=obj src="image/head/1.jpg" width="290" height="200" /></td>
                    <td colspan="2" width="400" align="center"><h1>邮政明信片制作</h1></td>
                </tr>

                <tr>
                    <td><p class="word">手机号码：</p></td>
                    <td><input type="text" name="phone_num" class="txt" onFocus="getfocus(this)" onBlur="lostfocus(this)" value="<?php echo $_COOKIE['username'];?>" maxlength="11"/></td>
                </tr>

                <tr>
                    <td><p class="word">密    码：</p></td>
                    <td><input type="password" name="password" class="txt" onFocus="getfocus(this)" onBlur="lostfocus(this)"/>
                </tr>

                <tr>
                    <td align="right"><input type="submit" class="btn" value="提交"/></td>
                    <td align="center"><input type="reset" class="btn" value="重置"/></td>
                </tr>
            </table>
        </form>

        <table cellspacing="0" cellpadding="0" width="1000" align="center" border="0">
            <tbody>
                <tr>
                    <td class="bai12" valign="center" background="imgbsy/bg10.jpg" height="96">
                        <div align="center" style="padding-top:15px;">友情链接：&nbsp;&nbsp;
                            <br/>
                            <A class=menu1 href="index.asp">网站首页</A> |
                            <A class=menu1 href="#">关于我们</A> |
                            <A class=menu1 href="#">新闻中心</A> |
                            <A class=menu1 href="#">企业荣誉</A> |
                            <A class=menu1 href="#">下载中心</A> |
                            <A class=menu1 href="Feedback.asp">在线留言</A> |
                            <A class=menu1 href="Aboutus.asp?Title=联系我们">联系我们</A> |
                            <span>&copy 2003-2014 www.chinapostcard.com 版权所有</span>
                            <br/>
                        </div>
                    </td>
                </tr>
            </tbody>
        </table>
    </body>
</html>
