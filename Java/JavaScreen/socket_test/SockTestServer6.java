import javax.net.ssl.SSLSocket;
import javax.net.ssl.SSLServerSocket;
//TEMPTEMP? import java.net.SocketFactory;
import javax.net.ServerSocketFactory;
import javax.net.ssl.SSLServerSocketFactory;
import java.net.InetAddress;
import java.io.*;

public class SockTestServer6
{
	public static void main(String args[]) {
		int port = 6667;

		for (int anum = 0; anum < args.length; ++anum) {
			if (args[anum].equals("-usage")) {
				myPrint("Usage: java SockTestClient [-port <port>]");
				System.exit(0);
			} else if (args[anum].equals("-port")) {
				port = Integer.parseInt(args[++anum]);
			}
		}
		DoTest(port);
	}

	public static void DoTest(int port) {
		myPrint("Creating socket to <" + port + ">");

	    try {
			ServerSocketFactory factory = SSLServerSocketFactory.getDefault();
			SSLServerSocket sSock =
			  (SSLServerSocket)factory.createServerSocket(port);
			myPrint("Starting to listen on server socket");
			while (true) {
				SSLSocket sock = (SSLSocket)sSock.accept();
				myPrint("Got connection on server socket");
				processCmd(sock);
				sock.close();
			}
	    } catch (Exception ex) {
	        myPrint("Exception (" + ex.toString() +
			  ") creating socket");
	    }
	}

	private static void processCmd(SSLSocket sock) {
		try {
			BufferedInputStream sockIn = new BufferedInputStream(sock.getInputStream());

			int bIn = 0;
			while (bIn != -1) {
				bIn = sockIn.read();
				myPrint("  Read byte: " + bIn);
			}

		} catch (IOException ex) {
			myPrint("IOException (" + ex.toString() + ") processing command");
		}
	}

	private static void myPrint(String msg) {
		System.out.println(msg);
	}
}
