import  java.io.*;
import  java.net.*;
import  java.util.*;

public class jsdevises
{   
    public static void main(String[] args)    
    {
        String version = System.getProperty("java.version");
        if (version.compareTo("1.1") < 0)  {
            System.out.println("Error: Java version 1.1 or greater is needed to run this program\n" 
                               + "The version you used is " + version);
            System.exit(1);
        }
        
        String usage = new String("usage: java jsdevises [-CP[port]] [-IP[port]] [-DP[port]]");
        
        if (args.length > 3)  {
            System.out.println(usage);
            System.exit(1);
        }
        
        for (int i = 0; i < args.length; i++)  {
            if (args[i].startsWith("-CP"))  {
                if (!args[i].substring(3).equals(""))  {
                    try  {
                        Globals.CMDPORT = Integer.parseInt(args[i].substring(3));
                        if (Globals.CMDPORT < 1 || Globals.CMDPORT > 65535)
                            throw new NumberFormatException();
                    }  catch (NumberFormatException e)  {
                        System.out.println("Invalid port number " + Globals.CMDPORT + " used in -CP field!\n");
                        System.out.println(usage);
                        System.exit(1);
                    }
                }
            }  else if (args[i].startsWith("-IP"))  {
                if (!args[i].substring(3).equals(""))  {
                    try  {
                        Globals.IMGPORT = Integer.parseInt(args[i].substring(3));
                        if (Globals.IMGPORT < 1 || Globals.IMGPORT > 65535)
                            throw new NumberFormatException();
                    }  catch (NumberFormatException e)  {
                        System.out.println("Invalid port number " + Globals.IMGPORT + " used in -IP field!\n");
                        System.out.println(usage);
                        System.exit(1);
                    }
                }
            }  else if (args[i].startsWith("-DP"))  {        
                if (!args[i].substring(3).equals(""))  {
                    try  {
                        Globals.DATAPORT = Integer.parseInt(args[i].substring(3));
                        if (Globals.DATAPORT < 1 || Globals.DATAPORT > 65535)
                            throw new NumberFormatException();
                    }  catch (NumberFormatException e)  {
                        System.out.println("Invalid port number " + Globals.DATAPORT + " used in -DP field!\n");
                        System.out.println(usage);
                        System.exit(1);
                    }
                }
            }  else  {
                System.out.println(usage);
                System.exit(1);
            }
        }
    
        DEViseCmdServerSocket cmdServerSocket = null;
        DEViseImgServerSocket imgServerSocket = null;
        try  {
            cmdServerSocket = new DEViseCmdServerSocket();
            imgServerSocket = new DEViseImgServerSocket(cmdServerSocket);
        }  catch (IOException e)  {
            System.out.println("Can not open server socket at local host");
            System.exit(1);
        }
        
        Thread cmdServerThread = new Thread(cmdServerSocket);
        cmdServerThread.start();
        Thread imgServerThread = new Thread(imgServerSocket);
        imgServerThread.start();       
    }
}
