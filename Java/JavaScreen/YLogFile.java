import java.io.*;

public final class YLogFile
{
    private static BufferedWriter logFile = null;
    private static String logFileName = null;
    private static boolean isLog = false;
    
    public YLogFile(boolean arg1, String arg2) throws YException
    {   
        isLog = arg1;
        logFileName = arg2;
                
        if (isLog) {
            if (logFileName == null)
                logFileName = new String("defaults.log");
                            
            try {
                logFile = new BufferedWriter(new FileWriter(logFileName));
            } catch (IOException e) {
                logFile = null;
                throw new YException("Can not open log file " + logFileName);
            }
        }
    }        
   
    public static void println(String msg)
    {           
        if (logFile != null) {
            try {
                logFile.write(msg, 0, msg.length());
                logFile.newLine(); 
            } catch (IOException e) {
                // do nothing
            }    
        } 
    }
    
    public static void print(String msg)
    {
        if (logFile != null) {
            try {
                logFile.write(msg, 0, msg.length());
            }  catch (IOException e) {
                // do nothing
            }    
        }
    }
        
    protected void finalize()
    {    
        if (logFile != null) {
            try {
                logFile.close();
            }  catch (IOException e) {
                // do nothing
            }
                
            logFile = null;
        }
    }    
}
