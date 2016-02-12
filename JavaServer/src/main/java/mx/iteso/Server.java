package mx.iteso;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Properties;

public class Server {
	
	static ServerSocket serverSocket;
	static int serverPort;
	
	static Socket clientSocket;
	
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
			serverSocket = new ServerSocket(serverPort);
			System.out.println("[SERVER] Server listening at port " + serverPort);
			
			clientSocket = serverSocket.accept();
			System.out.println("[SERVER] Connection started. Sending data...");
			
			OutputStream out = clientSocket.getOutputStream();
			out.write(100);
			System.out.println("[SERVER] Done");
			
			serverSocket.close();
			System.out.println("[SERVER] Connection closed");
			System.out.println("[SERVER] Server down");
			
		}
		catch(Exception ex)
		{
			System.out.println("[SERVER] Error: "+ex.getMessage());
		}
	}

}
