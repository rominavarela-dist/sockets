package mx.iteso;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Properties;

public class Client {
	static Socket clientSocket;
	static int serverPort;
	static InetAddress serverAddr;
	
	static public void main(String argv[])
	{
		try
		{
			//load configuration
			Properties props = new Properties();
			File f = new File("config/connection.config");
			InputStream input = new FileInputStream(f);
			props.load(input);
			input.close();
			
			serverPort = Integer.parseInt(props.getProperty("serverPort"));
			serverAddr = Inet4Address.getByName(props.getProperty("serverAddress"));
			System.out.println("[CLIENT] Connecting to " + serverAddr.getHostAddress() + ":" + serverPort);
			
			clientSocket = new Socket(serverAddr,serverPort);
			System.out.println("[CLIENT] Connection started. Receiving data...");
			
			InputStream in = clientSocket.getInputStream();
			int data = in.read();
			System.out.println(data);
			System.out.println("[Client] Done");
			
			clientSocket.close();
			System.out.println("[CLIENT] Connection closed");
			System.out.println("[CLIENT] Client down");
		}
		catch(Exception ex)
		{
			System.out.println("[CLIENT] Error: "+ex.getMessage());
		}
	}
}
