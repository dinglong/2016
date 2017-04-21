package conn;

import java.io.File;
import java.net.URL;
import java.net.URLClassLoader;
import java.security.Security;

public class Test {

    public static void main(String[] args) throws Exception {
        File f1 = new File("conn.factory.jar");
        File f2 = new File("conn.impl.jar");
        File f3 = new File("socket.factory.jar");
        File f4 = new File("socket.factory.proxy.jar");

        URL[] urls = new URL[] { f1.toURI().toURL(), f2.toURI().toURL(), f3.toURI().toURL(), f4.toURI().toURL() };

        Security.setProperty("ssl.SocketFactory.provider", "socket.factory.proxy.MySocketFactoryProxy");

        // 创建自己的classloader
        URLClassLoader cl = new URLClassLoader(urls, ClassLoader.getSystemClassLoader());

        // 有自己的classloader加载指定的类
        Connector connector = (Connector) cl.loadClass("conn.impl.ConnectorImpl").newInstance();
        connector.createConnector();
    }

}
