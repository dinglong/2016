1. ���ڽ����SSLSocketFactory��ʵ�����Լ���classloader�в��ܳɹ����ص�����

2. ��������ʱ��ͬ�İ���ɶ�Ӧ����jar�ļ�

3. �������������£�

	java -Djavax.net.debug=ssl -cp conn.jar conn.Test
	java -Djavax.net.debug=ssl -cp socket.factory.proxy.jar;conn.jar conn.Test

	��һ������ʧ�ܣ��ڶ����ɹ�