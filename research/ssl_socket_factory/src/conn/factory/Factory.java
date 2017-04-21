package conn.factory;

import javax.net.ssl.SSLSocketFactory;

public class Factory {

    public static void initialSSLSocketFactory() {
        System.out.println("in initialSSLSocketFactory.");
        SSLSocketFactory.getDefault();
        System.out.println("out initialSSLSocketFactory.");
    }

}
