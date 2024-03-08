/* System-dependent communications i/o routines for embedded Kermit. */

/*
  Author: Frank da Cruz.
  Copyright (C) 1995, 2011.
  Trustees of Columbia University in the City of New York.
  All rights reserved.
  See kermit.c for license.
*/

/*
  The i/o routines for AVR that provide packet i/o
  functions on the console (login) device.

  Device i/o:

    int devopen()    Communications device - open
    int pktmode()    Communications device - enter/exit packet mode
    int readpkt()    Communications device - read a packet
    int tx_data()    Communications device - send data
    int devclose()   Communications device - close
    int inchk()      Communications device - check if bytes are ready to read

  File i/o:

    int openfile()   File - open for input or output
    ULONG fileinfo() Get input file modtime and size
    int readfile()   Input file - read data
    int writefile()  Output file - write data
    int closefile()  Input or output file - close

  Full definitions below, prototypes in platform.h.

  These routines must handle speed setting, parity, flow control, file i/o,
  and similar items without the kermit() routine knowing anything about it.
  If parity is in effect, these routines must add it to outbound characters
  and strip it from inbound characters.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#ifndef O_WRONLY
#ifdef X_OK
#undef X_OK
#endif /* X_OK */
#endif /* O_WRONLY */

#include "cdefs.h"
#include "debug.h"
#include "kermit.h"
#include "platform.h"

UCHAR o_buf[OBUFLEN+8];			/* File output buffer */
UCHAR i_buf[IBUFLEN+8];			/* File input buffer */
int errno;

/*
  In this example, the output file is unbuffered to ensure that every
  output byte is committed.  The input file, however, is buffered for speed.
  This is just one of many possible implementation choices, invisible to the
  Kermit protocol module.
*/

extern xComPortHandle xSerial1Port; /* Create a handle for the serial port. tty file device */
static FIL * ofile = (FIL *)0;	/* File descriptors */
static FIL * ifile = (FIL *)0;	/* and pointers */

/*
 * File System, assuming we're only using one file system.
 */

static FATFS fat_fs;			// defining the structure for the filesystem
static FIL file;				// this will be the file structure. only need one,
								// as we'll either be reading or writing data to file, but not simultaneously.

/* Debugging */

#ifdef DEBUG

static FIL debug_file;			// this will be the debug write file structure, separate from the read or write file.
static FIL * dp = (FIL *)0;		/* Debug log file structure pointer */
static int xdebug = 0;			/* Debugging on/off */

void
dodebug(int fc, UCHAR * label, UCHAR * sval, long nval) {

	FRESULT fr;					// result from fatfs file activities

    if (fc != DB_OPN && !xdebug)
      return;
    if (!label)
      label = (UCHAR *)"";

    switch (fc) {			/* Function code */
	case DB_OPN:			/* Open debug log */
		if (!*label) label = (UCHAR *)"debug.txt";

	    /* Open or create a log file and ready to append */
	    f_mount(&fat_fs, (UCHAR *)"", 1);

	    /* Opens an existing file. If not existing, creates a new file. */
	    fr = f_open(&debug_file, label, FA_WRITE | FA_OPEN_ALWAYS);
	    if (fr == FR_OK) {
	        /* Seek to end of the file to append data */
	    	dp = &debug_file;
	        fr = f_lseek(dp, f_size(dp));
	        if (fr != FR_OK)
	            f_close(dp);
	    }
	    if (fr != FR_OK) return;

		xdebug = 1;
		f_printf(dp,(UCHAR *)"DEBUG LOG OPEN\n");
		return;

	case DB_MSG:			/* Write a message */
		if (dp) f_printf(dp,(UCHAR *)"%s\n",label);
		return;

	case DB_CHR:			/* Write label and character */
		if (dp) f_printf(dp,(UCHAR *)"%s=[%c]\n",label,(char)nval);
		return;

	case DB_PKT:			/* Log a packet */
		/* (fill in later, fall thru for now...) */
	case DB_LOG:			/* Write label and string or number */
		if (sval && dp)
		  f_printf(dp,(UCHAR *)"%s[%s]\n",label,sval);
		else
		  f_printf(dp,(UCHAR *)"%s=%ld\n",label,nval);
		return;

	case DB_CLS:			/* Close debug log */
		if (dp) {
			f_close(dp);
			dp = (FIL *)0;
		}
		xdebug = 0;
		return;
    }
}
#endif /* DEBUG */

/*  D E V O P E N  --  Open communications device  */
/*

  Call with: string pointer to device name.  This routine should get the
  current device settings and save them so devclose() can restore them.
  It should open the device.  If the device is a serial port, devopen()
  set the speed, stop bits, flow control, etc.
  Returns: 0 on failure, 1 on success.
*/
int
devopen(char *device) {
	// turn on the Serial 1 port to connect to the HP-48.
	xSerial1Port = xSerialPortInitMinimal( USART1, 9600, IBUFLEN+8, OBUFLEN+8);
	//  (serial port number, WantedBaud, TxQueueLength, RxQueueLength (8n1))
    return(1);
}

/*  P K T M O D E  --  Put communications device into or out of packet mode  */
/*
  Call with: 0 to put in normal (cooked) mode, 1 to put in packet (raw) mode.
  For a "dumb i/o device" like an i/o port that does not have a login attached
  to it, this routine can usually be a no-op.
  Returns: 0 on failure, 1 on success.
*/
int
pktmode(int on) {
    xSerialTxFlush( &xSerial1Port ); // flush the USART Tx port to allow packets to depart with a clean start.
    xSerialRxFlush( &xSerial1Port ); // flush the USART Rx port to allow packets to arrive with a clean start.
//    system(on ? "stty raw -echo" : "stty sane"); /* Crude but effective */
    return(1);
}


/*  D E V S E T T I N G S  */

int
devsettings(char * s) {
    /* Get current device settings, save them for devrestore() */
    /* Parse string s, do whatever it says, e.g. "9600;8N1" */
    if (!pktmode(ON))			/* And put device in packet mode */
      return(0);
    return(1);
}

/*  D E V R E S T O R E  */

int
devrestore(void) {
    /* Put device back as we found it */
    xSerialTxFlush( &xSerial1Port ); // flush the USART Tx port to allow packets to depart with a clean start.
    xSerialRxFlush( &xSerial1Port ); // flush the USART Rx port to allow packets to arrive with a clean start.
    return(1);
}


/*  D E V C L O S E  --  Closes the current open communications device  */
/*
  Call with: nothing
  Closes the device and puts it back the way it was found by devopen().
  Returns: 0 on failure, 1 on success.
*/
int
devclose(void) {
    vSerialClose( &xSerial1Port );
    return(1);
}

/* I N C H K  --  Check if input waiting */

/*
  Check if input is waiting to be read, needed for sliding windows.  This
  sample version simply looks in the stdin buffer (which is not portable
  even among different Unixes).  If your platform does not provide a way to
  look at the device input buffer without blocking and without actually
  reading from it, make this routine return -1.  On success, returns the
  numbers of characters waiting to be read, i.e. that can be safely read
  without blocking.
*/
int
inchk(struct k_data * k) {
	return( xSerialAvailableChar( &xSerial1Port ) );
}

/*  R E A D P K T  --  Read a Kermit packet from the communications device  */
/*
  Call with:
    k   - Kermit struct pointer
    p   - pointer to read buffer
    len - length of read buffer

  When reading a packet, this function looks for start of Kermit packet
  (k->r_soh), then reads everything between it and the end of the packet
  (k->r_eom) into the indicated buffer.  Returns the number of bytes read, or:
     0   - timeout or other possibly correctable error;
    -1   - fatal error, such as loss of connection, or no buffer to read into.
*/

int
readpkt(struct k_data * k, UCHAR *p, int len) {
    uint8_t flag;
    int n;

    UCHAR x;
    UCHAR c;
/*
  Timeout not implemented in this sample.
  It should not be needed.  All non-embedded Kermits that are capable of
  making connections are also capable of timing out, and only one Kermit
  needs to time out.  NOTE: This simple example waits for SOH and then
  reads everything up to the negotiated packet terminator.  A more robust
  version might be driven by the value of the packet-length field.
*/
#ifdef DEBUG
    char * p2;
#endif	/* DEBUG */

#ifdef F_CTRLC
    short ccn;
    ccn = 0;
#endif /* F_CTRLC */

    if (!p) {		/* Device not open or no buffer */
	debug(DB_MSG,"readpkt FAIL",0,0);
	return(-1);
    }
    flag = n = 0;                       /* Init local variables */

#ifdef DEBUG
    p2 = (char *)p;
#endif	/* DEBUG */

    while (1) {
        //x = getchar();                  /* Replace this with real i/o */
        xSerialGetChar( &xSerial1Port, &x );
        c = (k->parity) ? x & 0x7f : x & 0xff; /* Strip parity */

#ifdef F_CTRLC
	/* In remote mode only: three consecutive ^C's to quit */
        if (k->remote && c == (UCHAR) 3) {
            if (++ccn > 2) {
		debug(DB_MSG,"readpkt ^C^C^C",0,0);
		return(-1);
	    }
        } else {
	    ccn = 0;
	}
#endif /* F_CTRLC */

        if (!flag && c != k->r_soh)	/* No start of packet yet */
          continue;                     /* so discard these bytes. */
        if (c == k->r_soh) {		/* Start of packet */
            flag = 1;                   /* Remember */
            continue;                   /* But discard. */
        } else if (c == k->r_eom	/* Packet terminator */
		   || c == '\012'	/* 1.3: For HyperTerminal */
		   ) {
#ifdef DEBUG
            *p = NUL;                   /* Terminate for printing */
	    debug(DB_PKT,"RPKT",p2,n);
#endif /* DEBUG */
            return(n);
        } else {                        /* Contents of packet */
            if (n++ > k->r_maxlen)	/* Check length */
              return(0);
            else
              *p++ = x & 0xff;
        }
    }
    debug(DB_MSG,"READPKT FAIL (end)",0,0);
    return(-1);
}

/*  T X _ D A T A  --  Writes n bytes of data to communication device.  */
/*
  Call with:
    k = pointer to Kermit struct.
    p = pointer to data to transmit.
    n = length.
  Returns:
    X_OK on success.
    X_ERROR on failure to write - i/o error.
*/
int
tx_data(struct k_data * k, UCHAR *p, int n) {

    uint16_t i = 0;
	while(i < n)
		if( !xSerialPutChar( &xSerial1Port, p[i++]) )
				return(X_ERROR);        /* Failure */
    debug(DB_MSG,"tx_data write",0,n);
    return(X_OK);                       /* Success */
}

/*  O P E N F I L E  --  Open output file  */
/*
  Call with:
    Pointer to filename.
    Size in bytes.
    Creation date in format yyyymmdd hh:mm:ss, e.g. 19950208 14:00:00
    Mode: 1 = read, 2 = create, 3 = append.
  Returns:
    X_OK on success.
    X_ERROR on failure, including rejection based on name, size, or date.
*/
int
openfile(struct k_data * k, UCHAR * s, int mode) {

    switch (mode) {
      case 1:					/* Read */
    	ifile = &file;
		if (! f_open(ifile, s, FA_READ)) {
			debug(DB_LOG,"openfile read error",s,0);
			return(X_ERROR);
		}
		k->s_first   = 1;			/* Set up for getkpt */
		k->zinbuf[0] = '\0';		/* Initialize buffer */
		k->zinptr    = k->zinbuf;	/* Set up buffer pointer */
		k->zincnt    = 0;			/* and count */
		debug(DB_LOG,"openfile read ok",s,0);
		return(X_OK);

      case 2:					/* Write (create) */
      	ofile = &file;
		if (! f_open(ofile, s, FA_WRITE | FA_OPEN_ALWAYS)) {
			debug(DB_LOG,"openfile write error",s,0);
			return(X_ERROR);
		}
		debug(DB_LOG,"openfile write ok",s,0);
		return(X_OK);

#ifdef COMMENT
      case 3:					/* Append (not used) */
        ofile = &file;
  		if (! f_open(ofile, s, FA_WRITE | FA_OPEN_ALWAYS)) {
			debug(DB_LOG,"openfile append error",s,0);
			return(X_ERROR);
  		}

		if( !f_lseek(ofile, f_size(ofile)) ) {
				f_close(ofile);
				debug(DB_LOG,"openfile append seek error",s,0);
				return(X_ERROR);
		}
	    debug(DB_LOG,"openfile append ok",s,0);
	return(X_OK);
#endif /* COMMENT */

      default:
        return(X_ERROR);
    }
}

/*  F I L E I N F O  --  Get info about existing file  */
/*
  Call with:
    Pointer to filename
    Pointer to buffer for date-time string
    Length of date-time string buffer (must be at least 18 bytes)
    Pointer to int file type:
       0: Prevailing type is text.
       1: Prevailing type is binary.
    Transfer mode (0 = auto, 1 = manual):
       0: Figure out whether file is text or binary and return type.
       1: (nonzero) Don't try to figure out file type.
  Returns:
    X_ERROR on failure.
    0L or greater on success == file length.
    Date-time string set to yyyymmdd hh:mm:ss modtime of file.
    If date can't be determined, first byte of buffer is set to NUL.
    Type set to 0 (text) or 1 (binary) if mode == 0.
*/
#ifdef F_SCAN
#define SCANBUF 1024
#define SCANSIZ 49152
#endif /* F_SCAN */

ULONG
fileinfo(struct k_data * k,
	UCHAR * filename, UCHAR * buf, int buflen, short * type, short mode) {
    FILINFO statbuf;
    tm timestamp;

#ifdef F_SCAN
    FIL * fp;				/* File scan pointer */
    char inbuf[SCANBUF];		/* and buffer */
#endif /* F_SCAN */

    if (!buf)
      return(X_ERROR);
    buf[0] = '\0';
    if (buflen < 18)
      return(X_ERROR);
    if ( !f_stat(filename, &statbuf) )
      return(X_ERROR);
    fatfs_system(statbuf.ftime, statbuf.ftime, &timestamp);
    snprintf((char *)buf, buflen, "%04d%02d%02d %02d:%02d:%02d",
	    timestamp.tm_year + 2000,
            timestamp.tm_mon,
            timestamp.tm_mday,
            timestamp.tm_hour,
            timestamp.tm_min,
            timestamp.tm_sec
	    );
#ifdef F_SCAN // haven't adjusted this to work for the avr freertos tools.
/*
  Here we determine if the file is text or binary if the transfer mode is
  not forced.  This is an extremely crude sample, which diagnoses any file
  that contains a control character other than HT, LF, FF, or CR as binary.
  A more thorough content analysis can be done that accounts for various
  character sets as well as various forms of Unicode (UTF-8, UTF-16, etc).
  Or the diagnosis could be based wholly or in part on the filename.
  etc etc.  Or the implementation could skip this entirely by not defining
  F_SCAN and/or by always calling this routine with type set to -1.
*/
    if (!mode) {			/* File type determination requested */
	int isbinary = 1;

	fp = &file;
	if (! f_open(fp, filename, FA_READ)) {/* Open the file for scanning */
		debug(DB_LOG,"fileinfo read error", filename ,0 );
		return(X_ERROR);
	}
	if (fp) {
	    int n = 0, count = 0;
	    char c, * p;

	    debug(DB_LOG,"fileinfo scan ", filename, 0);

	    isbinary = 0;
	    while (count < SCANSIZ && !isbinary) { /* Scan this much */
		f_read(fp, &n,1 ,SCANBUF);
		if (n == EOF || n == 0)
		  break;
		count += n;
		p = inbuf;
		while (n--) {
		    c = *p++;
		    if (c < 32 || c == 127) {
			if (c !=  9 &&	/* Tab */
			    c != 10 &&	/* LF */
			    c != 12 &&	/* FF */
			    c != 13) {	/* CR */
			    isbinary = 1;
			    debug(DB_MSG,"fileinfo BINARY",0,0);
			    break;
			}
		    }
		}
	    }
	    f_close(fp);
	    *type = isbinary;
	}
    }
#endif /* F_SCAN */

    return(statbuf.fsize);
}


/*  R E A D F I L E  --  Read data from a file  */

int
readfile(struct k_data * k) {
	uint16_t cnt = 0;
    if (!k->zinptr) {
#ifdef DEBUG
	f_printf(dp,(UCHAR *)"readfile ZINPTR NOT SET\n");
#endif /* DEBUG */
	return(X_ERROR);
    }
    if (k->zincnt < 1) {		/* Nothing in buffer - must refill */
	if (k->binary) {		/* Binary - just read raw buffers */
	    k->dummy = 0;
	    if(! f_read(ifile, k->zinbuf, k->zinlen, (uint16_t *)&(k->zincnt) ))
	    	debug(DB_LOG,"readfile binary ok zincnt",0,k->zincnt);

	} else {			/* Text mode needs LF/CRLF handling */
	    int c;			/* Current character */
	    for (k->zincnt = 0; (k->zincnt < (k->zinlen - 2)); (k->zincnt)++) {
		f_read(ifile, &c, 1, &cnt);
		if (c  == EOF || cnt == 0)
		  break;
		if (c == '\n')		/* Have newline? */
		  k->zinbuf[(k->zincnt)++] = '\r'; /* Insert CR */
		k->zinbuf[k->zincnt] = c;
	    }
#ifdef DEBUG
	    k->zinbuf[k->zincnt] = '\0';
	    debug(DB_LOG,"readfile text ok zincnt",0,k->zincnt);
#endif /* DEBUG */
	}
	k->zinbuf[k->zincnt] = '\0';	/* Terminate. */
	if (k->zincnt == 0)		/* Check for EOF */
	  return(-1);
	k->zinptr = k->zinbuf;		/* Not EOF - reset pointer */
    }
    (k->zincnt)--;			/* Return first byte. */

    debug(DB_LOG,"readfile exit zincnt",0,k->zincnt);
    debug(DB_LOG,"readfile exit zinptr",0,k->zinptr);
    return(*(k->zinptr)++ & 0xff);
}


/*  W R I T E F I L E  --  Write data to file  */
/*
  Call with:
    Kermit struct
    String pointer
    Length
  Returns:
    X_OK on success
    X_ERROR on failure, such as i/o error, space used up, etc
*/
int
writefile(struct k_data * k, UCHAR * s, int n) {
    uint16_t rc;
    uint16_t cnt;
    rc = X_OK;

    debug(DB_LOG,"writefile binary",0,k->binary);

    if (k->binary) {			/* Binary mode, just write it */
		if (! f_write(ofile, s, n, &cnt))
			debug(DB_LOG,"writefile binary ok zoutcnt", 0, cnt);
		if( cnt != n) rc = X_ERROR;
    } else {				/* Text mode, skip CRs */
		UCHAR * p, * q;
		uint16_t i;
		q = s;

		while (1)
		{
			for (p = q, i = 0; ((*p) && (*p != (UCHAR)13)); p++, i++) ;
			if (i > 0)
				if ( !f_write(ofile, q, i, &cnt))
					debug(DB_LOG,"writefile text ok zoutcnt", 0, cnt);
			if (cnt != i) rc = X_ERROR;
			if (!*p)
				break;
			q = p+1;
		}
    }
    return(rc);
}

/*  C L O S E F I L E  --  Close output file  */
/*
  Mode = 1 for input file, mode = 2 or 3 for output file.

  For output files, the character c is the character (if any) from the Z
  packet data field.  If it is D, it means the file transfer was canceled
  in midstream by the sender, and the file is therefore incomplete.  This
  routine should check for that and decide what to do.  It should be
  harmless to call this routine for a file that that is not open.
*/
int
closefile(struct k_data * k, UCHAR c, int mode) {
    int rc = X_OK;			/* Return code */

    switch (mode) {
      case 1:				/* Closing input file */
		if ( !ifile )		/* If not not open */
		  break;			/* do nothing but succeed */
		debug(DB_LOG,"closefile (input)",k->filename,0);
		if (! f_close(ifile))
		  rc = X_ERROR;
		break;
      case 2:				/* Closing output file */
      case 3:
		if ( !ofile )		/* If not open */
		  break;			/* do nothing but succeed */
		debug(DB_LOG,"closefile (output) name",k->filename,0);
		debug(DB_LOG,"closefile (output) keep",0,k->ikeep);
		if (!f_close(ofile)) {		/* Try to close */
			rc = X_ERROR;
		} else if ((k->ikeep == 0) &&	/* Don't keep incomplete files */
			   (c == 'D')) {	/* This file was incomplete */
			if (k->filename) {
			debug(DB_LOG,"deleting incomplete",k->filename,0);
			f_unlink(k->filename);	/* Delete it. */
			}
		}
		break;
      default:
		rc = X_ERROR;
		break;
    }
    return(rc);
}

#ifdef DEBUG
uint8_t
xerror(void) {
    uint32_t x;
    extern uint8_t errorrate;
    if (errorrate == 0)
      return(0);
    x = random() % 100;
    debug(DB_LOG,"RANDOM",0,x);
    debug(DB_LOG,"ERROR",0,(x < errorrate));
    return(x < errorrate);
}
#endif /* DEBUG */
