
//#define DEBUG
#define PRINT_ETK_STATUS 0

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>

#include "machdep.h"
#include "ETkIfc.h"
#include "ETk.h"
#include "Util.h"
#include "DevError.h"

char *ETkIfc::_etkServer = NULL;
Boolean ETkIfc::_etkQuit = false;

static int MyWrite(int fd, unsigned char *buff, int num);
static int newlinefd(char *s, int fd, int maxc);
static DevStatus SendCommand(const char *etkServer, char *commandBuf,
			     int argc, const char **argv,
			     char *replyBuf, double timeout);
static DevStatus WaitForReply(char *buf, int fd, int bufSize, double timeout);

//
// Static global variables.
//
#if !defined(lint) && defined(RCSID)
static char		rcsid[] = "$RCSfile$ $Revision$ $State$";
#endif
static char *	srcFile = __FILE__;

//
// ETkIfc::CreateWindow()
//
// Show an embedded Tk window. filename is the name of a Tcl/Tk script
// to be executed in the new window. argc and argv carry the command-line
// arguments that will be passed to the Tcl/Tk script.
//
//
DevStatus
ETkIfc::CreateWindow(const char *etkServer, Window win,
		     int centerX, int centerY,
		     int width, int height,
		     const char *filename,
		     int argc, const char **argv,
		     int &handle)
{
    int i;
    char command[ETK_MAX_STR_LENGTH];
    char reply[ETK_MAX_STR_LENGTH];

    DOASSERT(etkServer != NULL, "No ETk server specified");
    
#ifdef DEBUG
    printf("ETkIfc::CreateWindow(%s,0x%lx,%d,%d,%d,%d,%s)\n",
	   etkServer, (long) win, centerX, centerY,
	   width, height, filename);
    printf("    argc: %d\n", argc);
    for (i = 0; i < argc; i++)
	printf("    arg: %s\n", argv[i] ? argv[i] : "(NULL)");
#endif
    
    DevStatus result = StatusOk;
    
    int topLeftX = centerX - (width / 2);
    int topLeftY = centerY - (height / 2);
    int botRightX = centerX + (width / 2) - 1;
    int botRightY = centerY + (height / 2) - 1;
    
    sprintf(command, "show %s 0x%lx %d %d %d %d %d",
	    filename, (long) win,
	    topLeftX, topLeftY, botRightX, botRightY, argc);
    
    double timeout = 5.0;
    
    //
    // SendCommand() will connect to server, send command, send args,
    // wait for reply, and close connection
    //
    DevStatus temp = SendCommand(etkServer, command,
				 argc, argv, reply, timeout);
    result += temp;

    if (result.IsComplete())
    {
	sscanf(reply, "%*s %d", &handle);
    }
    
#if PRINT_ETK_STATUS
    SendCommand(etkServer, "status", 0, NULL, reply, 5.0);
    printf("ETk status: %s\n", replyBuf);
#endif
    
    return result;

}

//
// ETkIfc::SendSimpleCommand()
//
// Sends a command to the EmbeddedTk server. The handle will be appended 
// to the command if handle != ETK_INVALID_HANDLE.
//
//
DevStatus
ETkIfc::SendSimpleCommand(const char *etkServer, const char *command,
			  int handle)
{
    DO_DEBUG(printf("ETkIfc::SendSimpleCommand(%s,%s,%d)\n",
		    etkServer, command, handle));
    
    DevStatus result = StatusOk;
    
    char commandBuf[ETK_MAX_STR_LENGTH];
    char replyBuf[ETK_MAX_STR_LENGTH];
    
    if (handle != ETK_INVALID_HANDLE)
	sprintf(commandBuf, "%s %d", command, handle);
    else
	sprintf(commandBuf, "%s", command);
    
    DevStatus temp = SendCommand(etkServer, commandBuf,
				 0, NULL, replyBuf, 0.0);
    result += temp;
    
#if PRINT_ETK_STATUS
    SendCommand(etkServer, "status", 0, NULL, replyBuf, 5.0);
    printf("ETk status: %s\n", replyBuf);
#endif
    
    return result;
}

//
// ETkIfc::MoveWindow()
//
// Moves an embedded Tk window
//
//
DevStatus
ETkIfc::MoveWindow(const char *etkServer, int handle,
		   int centerX, int centerY)
{
    DO_DEBUG(printf("ETkIfc::MoveWindow(%s,%d,%d,%d)\n",
		    etkServer, handle, centerX, centerY));
    
    DevStatus result = StatusOk;
    
    char commandBuf[ETK_MAX_STR_LENGTH];
    char replyBuf[ETK_MAX_STR_LENGTH];
    
    sprintf(commandBuf, "move %d %d %d", handle, centerX, centerY);
    
    DevStatus temp = SendCommand(etkServer, commandBuf,
				 0, NULL, replyBuf, 0.0);
    result += temp;
    
#if PRINT_ETK_STATUS
    SendCommand(etkServer, "status", 0, NULL, replyBuf, 5.0);
    printf("ETk status: %s\n", replyBuf);
#endif
    
    return result;
}

//
// static function: SendCommand()
//
// Send a command to the ETk server.
//
// - Connects to server
// - Sends: commandBuf newline
//          argv[0] newline
//          argv[1] newline
//          ...
//          argv[argc-1] newline
// - Waits for a reply
// - Closes the connection
//
// IMPORTANT: The command and arg strings should NOT already have
// newlines embedded in them. This function takes care of sending
// the trailing newline after each string.
//
//
static DevStatus
SendCommand(const char *etkServer, char *commandBuf,
	    int argc, const char **argv,
	    char *replyBuf, double timeout)
{
    DevStatus result = StatusOk;
    int i;
    int length;
    
    if (argc < 0)
	argc = 0;
    
    DO_DEBUG(printf("Sending ETk command: %s\n", commandBuf));
    for (i = 0; i < argc; i++)
    {
	if (argv[i] == NULL)
	    argv[i] = "";
	DO_DEBUG(printf("    arg: %s\n", argv[i]));
    }
    
    
    //
    // Establish connection with ETk server.
    //
    char errBuf[ETK_MAX_STR_LENGTH];
    int fd = ETkClient(etkServer, errBuf);
    if (fd < 0)
    {
	reportError(errBuf, errno);
	result = StatusFailed;
    }
    
    //
    // Send the command.
    //
    if (result.IsComplete())
    {
	length = strlen(commandBuf);
	if (MyWrite(fd, (unsigned char *) commandBuf, length) != length)
	{
	    reportError("Unable to send command to ETk server", errno);
	    result = StatusFailed;
	}
	if (MyWrite(fd, (unsigned char *) "\n", 1) != 1)
	{
	    reportError("Unable to send command to ETk server", errno);
	    result = StatusFailed;
	}
    }
    
    //
    // Send the arguments
    //
    if (result.IsComplete())
    {
	for (i = 0; i < argc && result.IsComplete(); i++)
	{
	    length = strlen(argv[i]);
	    if (MyWrite(fd, (unsigned char *) argv[i], length) != length)
	    {
		reportError("Unable to send command to ETk server", errno);
		result = StatusFailed;
	    }
	    if (MyWrite(fd, (unsigned char *) "\n", 1) != 1)
	    {
		reportError("Unable to send command to ETk server", errno);
		result = StatusFailed;
	    }
	}
    }
    
    //
    // Now wait for and decode the reply.
    //
    if (result.IsComplete())
    {
	result += WaitForReply(replyBuf, fd, ETK_MAX_STR_LENGTH, timeout);
    }
    
    if (result.IsComplete())
    {
	DO_DEBUG(printf("ETk server reply: %s\n", replyBuf));
	
	const char *okStr = "OK";
	const char *errStr = "ERROR";
	char errBuf[ETK_MAX_STR_LENGTH+100];
	if (!strncmp(replyBuf, okStr, strlen(okStr)))
	{
	    // Do nothing...
	}
	else if (!strncmp(replyBuf, errStr, strlen(errStr)))
	{
	    sprintf(errBuf, "Error from ETk server: %s",
		    &replyBuf[strlen(errStr)]);
	    reportError(errBuf, devNoSyserr);
	    result = StatusFailed;
	}
	else
	{
	    sprintf(errBuf,
		    "Can't understand reply from ETk server(%s)", replyBuf);
	    reportError(errBuf, devNoSyserr);
	    result = StatusFailed;
	}
    }
    
    if (fd >= 0)
    {
	if (close(fd) < 0)
	{
	    reportError("Error closing socket", errno);
	    result += StatusWarn;
	}
    }
    
    return result;

}

//
// static function: WaitForReply()
//
// Wait for a reply from the ETk server, and store the reply in buf.
// Returns an error if no reply is received in timeout seconds.
//
//
static DevStatus
WaitForReply(char *buf, int fd, int bufSize, double timeout)
{
    DevStatus result = StatusOk;
    double currentTime;
    
    struct timeval time;
    if (gettimeofday(&time, NULL) == -1)
    {
	reportError("gettimeofday failed", errno);
	result = StatusFailed;
    }
    else
    {
	double timeLimit = (double) time.tv_sec +
	    ((double) time.tv_usec) * 1.0e-6 + timeout;
	
	Boolean done = false;
	while (!done)
	{
	    if (newlinefd(buf, fd, bufSize) > 0)
	    {
		done = true;
	    }
	    
	    else if (gettimeofday(&time, NULL) == -1)
	    {
		reportError("gettimeofday failed", errno);
		result = StatusFailed;
		done = true;
	    }
	    else
	    {
		currentTime = (double) time.tv_sec +
		    ((double) time.tv_usec) * 1.0e-6;
		if (currentTime > timeLimit)
		{
		    reportError("Timed out waiting for ETk server's reply",
				devNoSyserr);
		    result = StatusFailed;
		    done = true;
		}
	    }
	}
    }
    
    return result;
}

//
// static function: newlinefd()
//
// Read a \n-terminated line from fd into s, replacing
// \n by \0. do not read more than maxc-1 characters.
// Returns the number of characters read (excluding \n). 
//
//
static int
newlinefd(char *s, int fd, int maxc)
{
  int i, lim = maxc-1; 
  char c;
  i = 0;
  while ((i < lim) && (read(fd,&c,1) == 1)) {
    if (c == '\n') {
      s[i] = '\0';
      return (i);
    }
    s[i++] = c;
  }
  s[i] = '\0';
  return(i); 
}

//
// static function: MyWrite()
//
// Write num bytes into fd from buff. Return the number of bytes
// actually written, which may be less than num only when
// write(fd,..,..) returns <=0 at some point.
//
//
static int
MyWrite(int fd, unsigned char *buff, int num)
{
    unsigned char *temp;
    int tocome = num;
    int thistime;
    
    temp = buff;
    
    while (tocome > 0) {
	thistime = write(fd,temp,tocome);
	if (thistime <= 0) return(num-tocome);
	tocome -= thistime;
	temp = temp + thistime;
    }
    
    return(num);
}

