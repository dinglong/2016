package socket.factory.proxy;

import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

import javax.net.ssl.SSLSocketFactory;

public class MySocketFactoryProxy extends SSLSocketFactory {
    private static final String className = "socket.factory.MySocketFactory";
    private SSLSocketFactory mySSLSocketFactory = null;

    public MySocketFactoryProxy() {
        System.out.println("in MySocketFactoryProxy.");
        try {
            ClassLoader cl = Thread.currentThread().getContextClassLoader();
            mySSLSocketFactory = (SSLSocketFactory) cl.loadClass(className).newInstance();
        } catch (Exception e) {
            e.printStackTrace();
        }
        System.out.println("out MySocketFactoryProxy.");
    }

    @Override
    public Socket createSocket(Socket s, String host, int port, boolean autoClose) throws IOException {
        return mySSLSocketFactory.createSocket(s, host, port, autoClose);
    }

    @Override
    public String[] getDefaultCipherSuites() {
        return getDefaultCipherSuites();
    }

    @Override
    public String[] getSupportedCipherSuites() {
        return getSupportedCipherSuites();
    }

    @Override
    public Socket createSocket(String host, int port) throws IOException, UnknownHostException {
        return createSocket(host, port);
    }

    @Override
    public Socket createSocket(InetAddress host, int port) throws IOException {
        return createSocket(host, port);
    }

    @Override
    public Socket createSocket(String host, int port, InetAddress localHost, int localPort) throws IOException,
            UnknownHostException {
        return createSocket(host, port, localHost, localPort);
    }

    @Override
    public Socket createSocket(InetAddress address, int port, InetAddress localAddress, int localPort)
            throws IOException {
        return createSocket(address, port, localAddress, localPort);
    }

}
