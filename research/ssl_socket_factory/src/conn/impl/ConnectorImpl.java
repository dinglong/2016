package conn.impl;

import conn.Connector;
import conn.factory.Factory;

public class ConnectorImpl implements Connector {

    @Override
    public void createConnector() {
        System.out.println("in createConnector.");

        ClassLoader currClassLoader = Thread.currentThread().getContextClassLoader();
        try {
            Thread.currentThread().setContextClassLoader(Factory.class.getClassLoader());
            Factory.initialSSLSocketFactory();
        } finally {
            Thread.currentThread().setContextClassLoader(currClassLoader);
        }

        System.out.println("out createConnector.");
    }

}
