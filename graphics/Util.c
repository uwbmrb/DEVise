/*
  ========================================================================
  DEVise Data Visualization Software
  (c) Copyright 1992-2013
  By the DEVise Development Group
  Madison, Wisconsin
  All Rights Reserved.
  ========================================================================

  Under no circumstances is this software to be copied, distributed,
  or altered in any way without prior permission from the DEVise
  Development Group.
*/

/*
  $Id$

  $Log$
  Revision 1.48  2013/01/25 22:13:16  wenger
  Fixed DEVise/JS bugs 1027 and 1028 -- we now re-make DEVise tmp and
  work dirs before we try to use them, in case /tmp cleaner has
  removed them.

  Revision 1.47  2012/04/30 22:21:10  wenger
  Merged js_data_save_br_0 thru js_data_save_br_1 to trunk.

  Revision 1.46.10.1  2012/04/27 15:36:15  wenger
  We now escape any commas in the actual data strings for data download.

  Revision 1.46  2009/05/13 22:41:23  wenger
  Merged x86_64_centos5_br_0 thru x86_64_centos5_br_1/dist_1_9_1x2 to
  the trunk.

  Revision 1.45.2.2  2009/05/06 20:19:13  wenger
  Got rid of extra debug output, cleaned up a few things.

  Revision 1.45.2.1  2009/05/04 19:16:54  wenger
  Fixed some memory problems found by valgrind (looking for the problems
  that are causing core dumps on swordfish@bmrb).

  Revision 1.45  2008/09/11 19:57:06  wenger
  Committed the most important fixes to warnings generated by gcc 4.3.0
  on moray at BMRB (ones that look like they indicate actual bugs).

  Revision 1.44  2005/12/06 20:03:09  wenger
  Merged V1_7b0_br_4 thru V1_7b0_br_5 to trunk.  (This should
  be the end of the V1_7b0_br branch.)

  Revision 1.43.10.8  2005/09/28 17:14:42  wenger
  Fixed a bunch of possible buffer overflows (sprintfs and
  strcats) in DeviseCommand.C and Dispatcher.c; changed a bunch
  of fprintfs() to reportErr*() so the messages go into the
  debug log; various const-ifying of function arguments.

  Revision 1.43.10.7  2005/04/12 18:24:12  wenger
  Better error messages in CheckAndMakeDirectory(); provision
  in Exit::DoExit() to avoid recursion.

  Revision 1.43.10.6  2005/01/03 21:08:22  wenger
  Fixed bug 911 (DEVise can't open DOS-format session files).

  Revision 1.43.10.5  2004/08/25 17:30:18  wenger
  We now print TCL_LIBRARY and TK_LIBRARY environment variable
  values when Tcl or Tk initialization fails.

  Revision 1.43.10.4  2003/12/19 18:07:29  wenger
  Merged redhat9_br_0 thru redhat9_br_1 to V1_7b0_br.

  Revision 1.43.10.3.2.2  2003/12/17 17:13:00  wenger
  Got things to compile and run RH 7.2 and Solaris 2.8 (using gcc 2.95.3
  for Solaris because of dynamic library problems).

  Revision 1.43.10.3.2.1  2003/12/17 00:17:59  wenger
  Merged gcc3_br_1 thru gcc3_br_2 to redhat9_br (just fixed conflicts,
  didn't actually get it to work).

  Revision 1.43.10.3  2003/11/05 19:09:10  wenger
  Changed all sprintfs in Session.c to snprintfs.

  Revision 1.43.10.2  2003/04/24 17:31:08  wenger
  Fixed bug in drill-down code; axis date formats now also apply to
  drill-down coordinates; we now check for buffer overruns in
  DateString().

  Revision 1.43.10.1.2.1  2003/12/16 16:08:16  wenger
  Got DEVise to compile with gcc 3.2.3 (with lots of deprecated-header
  warnings).  It runs on RedHat 7.2, but not on Solaris 2.8 (some kind
  of dynamic library problem).

  Revision 1.43.10.1  2003/04/17 17:59:18  wenger
  Now compiles with no warnings with gcc 2.95, except for warnings about
  tempname and tmpnam on Linux; updated Linux and Solaris dependencies.

  Revision 1.43  2001/05/27 18:51:08  wenger
  Improved buffer checking with snprintfs.

  Revision 1.42  2001/05/18 19:25:22  wenger
  Implemented the DEVise end of 3D drill-down; changed DEVise version to
  1.7.3.

  Revision 1.41  2001/04/12 20:14:59  wenger
  First phase of external process dynamic data generation is in place
  for RectX symbols (needs GUI and some cleanup); added the ability to
  specify format for dates and ints in GData; various improvements to
  diagnostic output.

  Revision 1.40  2000/06/20 22:16:55  wenger
  Added floating-point format for axes and mouse location display.

  Revision 1.39  2000/04/26 19:38:50  wenger
  JavaScreen caching code is largely implemented except for checking
  the validity of the cache files; committing with caching disabled
  to work on cursor draw command ordering (includes improvements to
  DevFileHeader class).

  Revision 1.38  2000/04/20 16:10:12  wenger
  Improved RemoveEnvFromPath() function.

  Revision 1.37  2000/04/18 16:13:27  wenger
  Environment variables can now be used in data source definitions;
  $DEVISE_DAT and $DEVISE_SCHEMA are added to new definitions as appropriate.

  Revision 1.36  2000/04/07 17:36:01  wenger
  String file path in session file is specified with $DEVISE_SESSION.

  Revision 1.35  2000/03/14 17:05:10  wenger
  Fixed bug 569 (group/ungroup causes crash); added more memory checking,
  including new FreeString() function.

  Revision 1.34  1999/11/30 22:28:05  wenger
  Temporarily added extra debug logging to figure out Omer's problems;
  other debug logging improvements; better error checking in setViewGeometry
  command and related code; added setOpeningSession command so Omer can add
  data sources to the temporary catalog; added removeViewFromPile (the start
  of allowing piling of only some views in a window).

  Revision 1.33  1999/07/16 21:35:52  wenger
  Changes to try to reduce the chance of devised hanging, and help diagnose
  the problem if it does: select() in Server::ReadCmd() now has a timeout;
  DEVise stops trying to connect to Tasvir after a certain number of failures,
  and Tasvir commands are logged; errors are now logged to debug log file;
  other debug log improvements.  Changed a number of 'char *' declarations
  to 'const char *'.

  Revision 1.32  1999/07/12 19:02:03  wenger
  Got DEVise to compile and run again on Linux (including Tcl/Tk 8.0).

  Revision 1.31  1999/03/01 23:08:58  wenger
  Fixed a number of memory leaks and removed unused code.

  Revision 1.30  1998/12/22 19:39:09  wenger
  User can now change date format for axis labels; fixed bug 041 (axis
  type not being changed between float and date when attribute is changed);
  got dates to work semi-decently as Y axis labels; view highlight is now
  always drawn by outlining the view; fixed some bugs in drawing the highight.

  Revision 1.29  1998/11/19 21:13:27  wenger
  Implemented non-DTE version of DEVise (new code handles data source catalog
  functions; Tables, SQLViews, etc., are not implemented); changed version to
  1.6.0.

  Revision 1.28  1998/07/29 14:20:19  wenger
  Mods to compile DEVise on Alpha/OSF again (partially successful); mods to
  allow static linking on Linux.

  Revision 1.27  1998/06/17 17:20:33  wenger
  Devised now sends "real" session file list to JavaScreen.

  Revision 1.26  1998/05/14 18:21:10  wenger
  New protocol for JavaScreen opening sessions works (sending "real" GIF)
  except for the problem of spaces in view and window names.

  Revision 1.25  1998/03/09 15:13:58  wenger
  Fixed compile warning.

  Revision 1.24  1998/02/23 23:22:30  wenger
  Merged cleanup_1_4_7_br_8 thru cleanup_1_4_7_br_9.

  Revision 1.23.2.1  1998/02/23 19:51:21  wenger
  Got DEVise 1.4.7 to compile and link on haha; fixed bug 268.

  Revision 1.23  1997/09/23 19:57:28  wenger
  Opening and saving of sessions now working with new scheme of mapping
  automatically creating the appropriate TData.

  Revision 1.22  1997/05/05 16:53:46  wenger
  Devise now automatically launches Tasvir and/or EmbeddedTk servers if
  necessary.

  Revision 1.21  1997/04/29 17:35:02  wenger
  Minor fixes to new text labels; added fixed text label shape;
  CheckDirSpace() no longer prints an error message if it can't get disk
  status.

  Revision 1.20  1996/12/03 20:24:22  jussi
  Added readn() and writen().

  Revision 1.19  1996/12/02 18:44:35  wenger
  Fixed problems dealing with DST in dates (including all date composite
  parsers); added more error checking to date composite parsers.

  Revision 1.18  1996/11/19 15:23:28  wenger
  Minor changes to fix compiles on HP, etc.

  Revision 1.17  1996/11/05 18:23:11  wenger
  Minor mods to get things to compile on SGI systems.

  Revision 1.16  1996/10/18 20:34:08  wenger
  Transforms and clip masks now work for PostScript output; changed
  WindowRep::Text() member functions to ScaledText() to make things
  more clear; added WindowRep::SetDaliServer() member functions to make
  Dali stuff more compatible with client/server library.

  Revision 1.15  1996/10/09 14:33:45  wenger
  Had to make changes to get my new code to compile on HP and Sun.

  Revision 1.14  1996/10/07 22:53:50  wenger
  Added more error checking and better error messages in response to
  some of the problems uncovered by CS 737 students.

  Revision 1.13  1996/08/23 16:55:44  wenger
  First version that allows the use of Dali to display images (more work
  needs to be done on this); changed DevStatus to a class to make it work
  better; various minor bug fixes.

  Revision 1.12  1996/07/14 20:04:47  jussi
  Made code to compile in OSF/1.

  Revision 1.11  1996/07/05 14:39:47  jussi
  Fixed minor problem with null-termination in DateString().

  Revision 1.10  1996/05/20 18:44:42  jussi
  Replaced PENTIUM flag with SOLARIS.

  Revision 1.9  1996/03/27 17:54:56  wenger
  Changes to get DEVise to compile and run on Linux.

  Revision 1.8  1996/02/13 16:20:16  jussi
  Fixed for AIX.

  Revision 1.7  1996/01/10 19:11:17  jussi
  Added error checking to CopyString.

  Revision 1.6  1995/12/28 18:48:14  jussi
  Small fixes to remove compiler warnings.

  Revision 1.5  1995/12/14 17:12:38  jussi
  Small fixes.

  Revision 1.4  1995/10/18 14:55:32  jussi
  Changed mask of created directory to 0777 from 0755.

  Revision 1.3  1995/10/15 18:36:40  jussi
  Added HPUX-specific code.

  Revision 1.2  1995/09/05 21:13:13  jussi
  Added/updated CVS header.
*/

#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string>

#if defined (SGI)
  #define STAT_BAVAIL f_bfree
#else
  #define STAT_BAVAIL f_bavail
#endif

#if defined(SOLARIS) || defined(OSF)
  #include <sys/statvfs.h>
  #define STAT_STRUCT statvfs
  #define STAT_FUNC statvfs
  #define STAT_FRSIZE f_frsize
#elif defined(AIX)
  #define _KERNEL
  #define _VOPS
  #include <sys/vfs.h>
  #include <sys/statfs.h>
  #define STAT_STRUCT statfs
  #define STAT_FUNC VFS_STATFS
  #define STAT_FRSIZE f_bsize
#else
  #include <sys/vfs.h>
  #define STAT_STRUCT statfs
  #define STAT_FUNC statfs
  #define STAT_FRSIZE f_bsize

  #if defined(SUN)
    extern "C" int statfs(const char *, struct statfs *);
  #else
    #if defined(SGI)
      #include <sys/statfs.h>
    #endif
  #endif
#endif

#if defined(SOLARIS) || defined(HPUX) || defined(AIX)
#include <dirent.h>
#else
#include <sys/dir.h>
#endif

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <libgen.h>

#include "Util.h"
#include "Exit.h"
#include "DevError.h"

long ModTime(char *fname)
{
  struct stat sbuf;
  if (stat(fname, &sbuf) < 0) {
    fprintf(stderr, "Cannot get modtime of %s\n", fname);
    reportErrNosys("Fatal error");//TEMP -- replace with better message
    Exit::DoExit(2);
  }
  return (long)sbuf.st_mtime;
}

DevStatus
ReadFile(const char *filename, int &size, char *&buffer)
{
  DevStatus result = StatusOk;

  struct stat sbuf;
  if (stat(filename, &sbuf) < 0)
  {
    reportError("Can't get size of file", errno);
    result = StatusFailed;
  }
  else
  {
    size = sbuf.st_size;
    buffer = new char[size];
    if (buffer == NULL)
    {
      reportError("Out of memory", errno);
      result = StatusFailed;
    }
    else
    {
      int fd = open(filename, O_RDONLY);
      if (fd < 0)
      {
        reportError("Can't open file", errno);
        result = StatusFailed;
      }
      else
      {
        if (read(fd, buffer, size) != size)
	{
          reportError("Error reading file", errno);
          result = StatusFailed;
	}

	if (close(fd) < 0)
	{
          reportError("Error closing file", errno);
          result = StatusWarn;
	}
      }

      if (!result.IsComplete()) delete [] buffer;
    }
  }

  return result;
}

char *CopyString(const char *str)
{
  if (str == NULL) return NULL;
  // Changed from new to malloc here so the stack doesn't get too deep
  // for Purify to show.  RKW 1999-03-01.
  int bufSize = strlen(str) + 1;
  char *result = (char *)malloc(bufSize);
  if (!result) {
    reportErrNosys("Fatal error: out of memory");
    Exit::DoExit(2);
  }
  strncpy(result, str, bufSize);
  return result;
}

void FreeString(char *str)
{
  if (str) {
    int length = strlen(str);
    memset(str, 0, length);
    free(str);
  }
}

char *
RemoveEnvFromPath(const char *path)
{
  char *result;

  const char *inP = path;
  char tmpBuf[MAXPATHLEN * 2];
  char *outP = tmpBuf;

  while (*inP) {
    if (*inP == '$') {
      // Starting an environment variable name.
      *inP++; // skip over '$'
      char envVar[256];
      char *envP = envVar;

      // Get the name of the environment variable.
      // Assume var name will end at '/', '"', '.' or white space (added '"',
      // ',', and white space to allow data catalog entries to be passed in).
      while (*inP && *inP != '/' && *inP != '"' && *inP != '.' &&
          !isspace(*inP)) {
        *envP++ = *inP++;
      }
      *envP = '\0'; // terminate the string

      // Now get its value and copy it into the output buffer.
      char *varValue = getenv(envVar);
      if (varValue) {
        envP = varValue;
	while (*envP) {
	  *outP++ = *envP++;
	}
      } else {
	char errBuf[1024];
	int formatted = snprintf(errBuf, sizeof(errBuf)/sizeof(char),
	    "Error getting value for environment variable %s", envVar);
	(void) checkAndTermBuf2(errBuf, formatted);
        reportErrSys(errBuf);
      }
    } else {
      // 'Regular' character -- just copy it.
      *outP++ = *inP++;
    }
  }
  *outP = '\0'; // terminate the string

  result = CopyString(tmpBuf);

  return result;
}

char *
AddEnvToPath(const char *envVar, const char *path)
{
  char *result;

  const char *envVal = getenv(envVar);
  if (!envVal) {
    char errBuf[1024];
    int formatted = snprintf(errBuf, sizeof(errBuf)/sizeof(char),
        "Error getting value for environment variable %s", envVar);
    (void) checkAndTermBuf2(errBuf, formatted);
    reportErrSys(errBuf);
    // Note: if we get here, we still want to continue through the
    // rest of the function and copy the string at the end.
  }

  char *match = NULL;
  if (envVal) {
    match = strstr(path, envVal);
  }

  if (match) {
    char tmpBuf[MAXPATHLEN * 2];
    char *outP = tmpBuf;
    int bufLeft = sizeof(tmpBuf);

    // Copy the stuff before the match.
    int beginLen = match - path;
    DOASSERT(beginLen < bufLeft, "Buffer overflow");
    // We only copy *part* of the path string.
    memcpy(outP, path, beginLen);
    outP += beginLen;
    bufLeft -= beginLen;

    // Copy in the environment variable name.
    DOASSERT(1 < bufLeft, "Buffer overflow");
    *outP++ = '$';
    bufLeft--;

    int varLen = strlen(envVar);
    DOASSERT(varLen < bufLeft, "Buffer overflow");
    // We *don't* want to copy the terminating null.
    memcpy(outP, envVar, varLen);
    outP += varLen;
    bufLeft -= varLen;

    // Copy in the stuff after the match
    int valLen = strlen(envVal);
    int endLen = strlen(path + beginLen + valLen);
    DOASSERT(endLen < bufLeft, "Buffer overflow");
    // Here we *do* want to copy the terminating null.
    strncpy(outP, path + beginLen + valLen, bufLeft);

    result = CopyString(tmpBuf);
  } else {
    result = CopyString(path);
  }

  return result;
}

void
PrintEnv(FILE *file, const char *envVar)
{
  const char *value = getenv(envVar);
  if (!value) value = "(NULL)";
  fprintf(file, "Environment variable %s: <%s>\n", envVar, value);
}

// Note: ParseFloatDate() depends on this format.
static const char *_defaultDateFormat = "%b %d %Y %T";

const char *
GetDefaultDateFormat()
{
  return _defaultDateFormat;
}

const char *DateString(time_t tm, const char *format)
{
#if 0
  if (tm < 0) {
    char errBuf[1024];
    int formatted = snprintf(errBuf, sizeof(errBuf)/sizeof(char),
        "Illegal time value %ld\n", tm);
    (void) checkAndTermBuf2(errBuf, formatted);
    reportErrNosys(errBuf);
  }
#endif

  const int bufLen = 32;
  static char dateBuf[bufLen];

  const char *result = dateBuf;

  if (format == NULL || strlen(format) == 0) format = _defaultDateFormat;

  // Note: second arg. of cftime() should be declared const in system header
  // files.
#if defined(LINUX) || defined(SOLARIS)
  int count = strftime(dateBuf, bufLen, format, localtime(&tm));
#else
  int count = cftime(dateBuf, (char *)format, &tm);
#endif

  if (count == 0 || count > bufLen) {
    fprintf(stderr, "Date buffer overflow!!\n");
    result = "buffer overflow";
  }

  return result;
}

DevStatus
EscapeChars(char buf[], int bufSize, const char *toEscape)
{
  char *src = buf;
  std::string tmpStr = "";

  while (*src) {
    // Escape specified characters and '\'.
    if (*src == '\\' || strchr(toEscape, *src) != NULL) {
      tmpStr += '\\';
    }
    tmpStr += *src;
    ++src;
  }

  return nice_strncpy(buf, tmpStr.c_str(), bufSize);
}

void ClearDir(const char *dir)
{
  /* clear directory */

  DIR *dirp = opendir(dir);
  if (dirp != NULL){
#if defined(SOLARIS) || defined(HPUX) || defined(AIX) || defined(LINUX) \
      || defined(OSF)
    struct dirent *dp;
#else
    struct direct *dp;
#endif
    for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp)){
#if defined(SOLARIS) || defined(HPUX) || defined(AIX) || defined(LINUX) \
      || defined(OSF)
      struct dirent *realdp = (struct dirent *)dp;
#else
      struct direct *realdp = dp;
#endif
      if (strcmp(realdp->d_name,".") != 0 &&
	  strcmp(realdp->d_name,"..") != 0 ){
	char buf[MAXPATHLEN];
	int formatted = snprintf(buf, sizeof(buf)/sizeof(char),
	    "%s/%s", dir, realdp->d_name);
	(void) checkAndTermBuf2(buf, formatted);
	/*
	   printf("unlinking %s\n", buf);
	*/
	unlink(buf);
      }
    }
    closedir(dirp);
  }
}

/* Check if directory exists. Make directory if not already exists
   Clear directory if clear == true*/

void CheckAndMakeDirectory(const char *dir, Boolean clear, Boolean errorIsFatal)
{
  const char *fatalMsg = "";
  if (errorIsFatal) fatalMsg = "Fatal error: ";

  struct stat sbuf;
  int ret = stat(dir, &sbuf);
  if (ret >=  0) {
	/* path exists... */
    if (!(sbuf.st_mode & S_IFDIR)){
	  /* ...but not a directory. */
	  char errBuf[1024];
	  int formatted = snprintf(errBuf, sizeof(errBuf)/sizeof(char),
	  		"%s%s is not a directory", fatalMsg, dir);
	  (void) checkAndTermBuf2(errBuf, formatted);
	  reportErrNosys(errBuf);
      if (errorIsFatal) Exit::DoExit(1);
    } else {
	  /* ...and is a directory; clear it. */
      if (clear) {
        ClearDir(dir);
      }
	}
  } else {
    /* path does not exist; make new directory */
    /* if necessary we recursively call this function to make higher-
     * level directories */
    char *tmpDir = CopyString(dir);
    char *upOne = dirname(tmpDir);
    if (strcmp(upOne, ".") && strcmp(upOne, "/")) {
      CheckAndMakeDirectory(upOne, false, errorIsFatal);
    }
    FreeString(tmpDir);

    int code = mkdir(dir, 0777);
    if (code < 0 ){
	  char errBuf[1024];
	  int formatted = snprintf(errBuf, sizeof(errBuf),
	  		"%sCan't create directory %s", fatalMsg, dir);
	  (void) checkAndTermBuf2(errBuf, formatted);
	  reportErrSys(errBuf);
      if (errorIsFatal) Exit::DoExit(1);
    }
  }
}

/* Check whether we have enough space in a given directory. */
void CheckDirSpace(const char *dirname, const char *envVar, int warnSize,
  int exitSize)
{
  struct STAT_STRUCT stats;

  if (STAT_FUNC(dirname, &stats
#if defined(SGI)
    , sizeof(stats), 0
#endif
    ) != 0)
  {
#if defined(DEBUG)
    reportErrSys("Can't get status of file system");
#endif
  }
  else
  {
    int minBlocksFree = exitSize / stats.STAT_FRSIZE;
    int warnBlocksFree = warnSize / stats.STAT_FRSIZE;
    if (((int)stats.STAT_BAVAIL) < minBlocksFree)
    {
      char errBuf[1024];
      int formatted = snprintf(errBuf, sizeof(errBuf)/sizeof(char),
          "Fatal error: %s directory (%s) has less than %d bytes free\n",
	  envVar, dirname, exitSize);
      (void) checkAndTermBuf2(errBuf, formatted);
      reportErrNosys(errBuf);
      Exit::DoAbort(errBuf, __FILE__, __LINE__);
    }
    else if (((int)stats.STAT_BAVAIL) < warnBlocksFree)
    {
      fprintf(stderr,
	"Warning: %s directory (%s) has less than %d bytes free\n",
	envVar, dirname, warnSize);
    }
  }

  return;
}

//
// Read specified number of bytes. Recover from interrupted system calls.
//

int readn(int fd, char *buf, int nbytes)
{
    int nleft = nbytes;
    while (nleft > 0) {
        int nread = read(fd, buf, nleft);
        if (nread < 0) {
            if (errno == EINTR)
                continue;
            perror("read");
            return nread;
        }
        if (nread == 0)                 // EOF?
            break;
        nleft -= nread;
        buf   += nread;
    }
    
    return nbytes - nleft;
}
  
//
// Write specified number of bytes. Recover from interrupted system calls.
//

int writen(int fd, char *buf, int nbytes)
{
    int nleft = nbytes;
    while (nleft > 0) {
        int nwritten = write(fd, buf, nleft);
        if (nwritten < 0) {
            if (errno == EINTR)
                continue;
            return nwritten;
        }
        nleft -= nwritten;
        buf   += nwritten;
    }

    return nbytes - nleft;
}

fgets_result
nice_fgets(char *buf, int bufSize, FILE *fp)
{
  fgets_result result = fgets_ok;

  // In case no chars get transferred to buffer.
  buf[0] = '\0';

  char testChar = '\123';
  buf[bufSize - 1] = testChar;

  if (fgets(buf, bufSize, fp) == NULL) {
    if (feof(fp)) {
      result = fgets_eof;
    }
    if (ferror(fp)) {
      reportErrSys("Error in nice_fgets()");
      result = fgets_error;
    }
  }

  if (buf[bufSize - 1] != testChar) {
    // Buffer is too small (or the line had *exactly* bufSize-1 characters).
    reportErrNosys("Buffer overflow");
    result = fgets_bufoverflow;
  }

  // Make absolutely sure the string is terminated.
  buf[bufSize - 1] = '\0';

  StripTrailingNewline(buf);

  return result;
}

DevStatus
nice_strncpy(char *dest, const char *src, size_t destSize)
{
  DevStatus status(StatusOk);

  if (src == NULL) {
    reportErrNosys("NULL src buffer");
    status += StatusFailed;
  } else if (dest == NULL) {
    reportErrNosys("NULL dest buffer");
    status += StatusFailed;
  } else if (destSize == 0) {
    reportErrNosys("Zero-size dest buffer");
    status += StatusFailed;
  } else {
    int index = 0;
    while (src[index] != '\0' && index < (int)destSize - 1) {
      dest[index] = src[index];
      index++;
    }
    dest[index] = '\0';

    if (src[index] != '\0') {
      reportErrNosys("Dest buffer too short");
      status += StatusFailed;
    }
  }

  return status;
}

DevStatus nice_strncat(char *dest, const char *src, size_t destSize)
{
  DevStatus result(StatusOk);

  if (dest == NULL) {
    reportErrNosys("NULL dest buffer");
    result += StatusFailed;
  } else {
    int len = strlen(dest);
    int newSize = destSize - len;
    result += nice_strncpy(&dest[len], src, newSize);
  }

  return result;
}

void
dos2unix(char *buf)
{
  int last = strlen(buf) - 1;
  if (last >= 0 && buf[last] == '\r') {
    buf[last] = '\0';
  }
}

void
PrintArgs(FILE *fp, int argc, const char * const *argv, Boolean printNewline)
{
  int index;
  const char *prefix = "";
  for (index = 0; index < argc; index++) {
    fprintf(fp, "%s<%s>", prefix, argv[index]);
    prefix = ", ";
  }
  if (printNewline) fprintf(fp, "\n");
}

void
CopyArgs(int argc, const char * const * argvOld, char **&argvNew)
{
  argvNew = new char *[argc];
  if (argvNew == NULL) {
    reportErrNosys("Insufficient memory");
    Exit::DoExit(2);
  }

  int index;
  for (index = 0; index < argc; index++) {
    argvNew[index] = CopyString(argvOld[index]);
  }
}

void FreeArgs(int argc, char **argv)
{
  int index;
  for (index = 0; index < argc; index++) {
    FreeString(argv[index]);
  }

  delete [] argv;
}

Boolean
dequal(double d1, double d2, double zeroTol, double relTol)
{
    Boolean result = false;

    if (d1 == d2) {
        result = true;
    } else {
        double absDiff = fabs(d1 - d2);
	if (d1 == 0.0 || d2 == 0.0) {
	    if (absDiff < zeroTol) {
	        result = true;
	    }
	} else {
	    double relDiff = fabs(absDiff / d1);
	    if (relDiff < relTol) {
	        result = true;
	    }
	}
    }

    return result;
}

DevStatus
CheckAndTermBuf(char buf[], int bufSize, int formatted, const char *file,
  int line)
{
#if defined(DEBUG)
    printf("CheckAndTermBuf(0x%p, %d, %d)\n", buf, bufSize, formatted);
#endif

    DevStatus result(StatusOk);

    if (formatted >= bufSize || formatted < 0) {
	DevError::ReportError("Warning: buffer is too short", file, line,
	  devNoSyserr);

	result += StatusFailed;

	if (bufSize > 0) {

	    // Put overflow indicator string at end of buffer.
	    const char *termStr = "*...";
	    const int termLen = strlen(termStr);
	    int startIndex = bufSize - termLen - 1;
	    if (startIndex >= 0) {
	        strncpy(&buf[startIndex], termStr, termLen + 1);
	    }

	    // Be absolutely sure the buffer is correctly terminated.
	    buf[bufSize - 1] = '\0';
	}
    }

    return result;
}
