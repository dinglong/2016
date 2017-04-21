1. 用于解决当SSLSocketFactory的实现在自己的classloader中不能成功加载的问题

2. 测试运行时不同的包打成对应报名jar文件

3. 测试命令行如下：

	java -Djavax.net.debug=ssl -cp conn.jar conn.Test
	java -Djavax.net.debug=ssl -cp socket.factory.proxy.jar;conn.jar conn.Test

	第一个加载失败，第二个成功