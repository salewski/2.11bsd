/*
 * six-byte packet header for asynch lines.
 * headers for other devices take up the same
 * or less space.  If this changes the header
 * struct will have to become a union.
 */
struct header {
	char	sync;		/* sync byte */
	char	ksize;		/* encoded packet size */
	u_short sum;		/* block check of data packet */
	char	cntl;		/* control byte */
	char	ccntl;		/* block check of header */
};
#define	HDRSIZ	6

/*
 * Control structure for a packet driver connection.
 */
struct pack {
	short	p_state;	/* line state */
	short	p_bits;		/* mask for getepack */
	short	p_rsize;	/* input packet size */
	short	p_xsize;	/* output packet size */
	struct	header p_ihbuf;	/* input header */
	struct	header p_ohbuf; /* output header */
	char	*p_rptr;
	char	p_mode;
	char	**p_ipool;	/* head link to input buffer pool */
	char	**p_io;		/* input buffer given to driver */
	char	p_xcount;	/* # active output buffers */
	char	p_rcount;
	char	p_nout,p_tout;
	char	p_lpsize;	/* log(psize/32) */
	char	p_timer;
	char	p_obusy;
	char	p_srxmit;
	char	p_rwindow;	/* window size */
	char	p_swindow;
	char	p_msg;		/* control msg */
	char	p_rmsg;		/* repeated control msg */
	char	p_ps,p_pr;	/* last packet sent, recv'd */
	char	p_rpr;		/* copy of remote pr */
	char	p_nxtps;	/* next output seq number */
	char	p_imap;		/* bit map of input buffers */
	char	p_pscopy;	/* newest output packet */
	char	*p_ob[8];	/* output buffers */
	char	*p_ib[8];	/* input buffers */
	char	p_os[8];	/* output buffer status */
	char	p_is[8];	/* input buffer status */
	short	p_osum[8];	/* output checksums */
	short	p_isum[8];	/* input checksums */
	DSYSTEM;
};
#define	CHECK	0125252
#define	SYN	020
#define	MOD8	7
#define	NOTCNTL(a)	(a & 0300)
#ifndef MIN
#define	MIN(a,b)	(((a)<(b))? (a):(b))
#endif

char	next[8];
char	mask[8];
short	npbits;
short	pkactive;
short	pkzot;
short	pkdisc;

/*
 * driver state
 */
#define	DEAD	0
#define	INITa	1
#define	INITb	2
#define	INITab	3
#define	LIVE	010
#define	RXMIT	020
#define	RREJ	040
#define PDEBUG	0200
#define	DRAINO	0400
#define	WAITO	01000
#define	DOWN	02000
#define	RCLOSE	04000
#define	BADFRAME 020000

/*
 * modes
 */
#define	SLOWMODE	0100
/*
 * io buffer states
 */
#define	B_NULL	0
#define	B_READY	1
#define	B_SENT	2
#define	B_RESID	010
#define	B_COPY	020
#define	B_MARK	040
#define	B_SHORT	0100

/*
 * control messages
 */
#define	CLOSE	1
#define	RJ	2
#define	SRJ	3
#define	RR	4
#define	INITC	5
#define	INITB	6
#define	INITA	7

#define	M_RJ	4
#define	M_SRJ	010
#define	M_RR	020
#define	M_INITC	040
#define	M_CLOSE	2
#define	M_INITA	0200
#define	M_INITB	0100



#define	PKOPRI	31
#define	PKIPRI	30

#define	NPLINES	8

/*
 * packet ioctl buf
 */
struct	piocb {
	unsigned t;
	short	psize;
	short	mode;
	short	state;
	char	window;
};

short pkdebug;
short pksizes[];

#define	Pwrite	1
#define	Poutput	1
#define	Pxint	1


#define	Print	01
#define	Prend	01
#define	Pacc	01
#define	Pread	01

short	*PTRACE;


#define	ISCNTL(a) ((a & 0300) == 0)
