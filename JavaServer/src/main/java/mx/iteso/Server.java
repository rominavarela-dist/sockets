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
			
			// connect
			clientSocket = serverSocket.accept();
			InputStream in = clientSocket.getInputStream();
			OutputStream out = clientSocket.getOutputStream();
			System.out.println("[SERVER] Connection started");
			
			// listen request
			Struct req = new Struct();
			byte[] reqData = new byte[Struct.sizeInBytes()];
			in.read(reqData);
			req.readBytes(reqData);
			System.out.println("[SERVER] Request:");
			System.out.println(req);
			
			// send response
			Struct res = new Struct();
			res.x = -req.x;
			res.y = -req.y;
			res.z = (char) (req.z + 32);
			System.out.println("[SERVER] Response:");
			System.out.println(res);
			
			byte[] resData = res.toByteArray();
			out.write(resData);
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
