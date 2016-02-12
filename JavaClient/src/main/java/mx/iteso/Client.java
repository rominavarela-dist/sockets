package mx.iteso;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.OutputStream;
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
			// load configuration
			Properties props = new Properties();
			File f = new File("config/connection.config");
			InputStream input = new FileInputStream(f);
			props.load(input);
			input.close();
			
			serverPort = Integer.parseInt(props.getProperty("serverPort"));
			serverAddr = Inet4Address.getByName(props.getProperty("serverAddress"));
			System.out.println("[CLIENT] Connecting to " + serverAddr.getHostAddress() + ":" + serverPort);
			
			// connect
			clientSocket = new Socket(serverAddr,serverPort);
			OutputStream out = clientSocket.getOutputStream();
			InputStream in = clientSocket.getInputStream();
			System.out.println("[CLIENT] Connection started");
			
			// send request
			Struct req = new Struct();
			req.x = (int) (Math.random() * 100);
			req.y = (float) (Math.random() * 100);
			req.z = (char) ((Math.random() * 26) + 65);
			System.out.println("[CLIENT] Request:");
			System.out.println(req);
			
			byte[] reqData = req.toByteArray();
			out.write(reqData);
			
			// listen response
			Struct res = new Struct();
			byte[] resData = new byte[Struct.sizeInBytes()];
			in.read(resData);
			res.readBytes(resData);
			System.out.println("[CLIENT] Response:");
			System.out.println(res);
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
