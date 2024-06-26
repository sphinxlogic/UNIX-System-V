/*	@(#)n2.c	1.2	*/
#include "tdef.h"
#include <sgtty.h>
extern
#include "d.h"
extern
#include "v.h"
#ifdef NROFF
extern
#include "tw.h"
#endif
#include "s.h"
#include <setjmp.h>

/*
troff2.c

output, cleanup
*/

#include "ext.h"
extern jmp_buf	sjbuf;
int	toolate;
int	error;

pchar(i)
tchar i;
{
	int j;
	static int hx = 0;	/* records if have seen HX */

	if (hx) {
		hx = 0;
		j = absmot(i);
		if (isnmot(i)) {
			if (j > dip->blss)
				dip->blss = j;
		} else {
			if (j > dip->alss)
				dip->alss = j;
			ralss = dip->alss;
		}
		return;
	}
	if (ismot(i)) {
		pchar1(i); 
		return;
	}
	switch (j = cbits(i)) {
	case 0:
	case IMP:
	case RIGHT:
	case LEFT:
		return;
	case HX:
		hx = 1;
		return;
	case PRESC:
		if (dip == &d[0])
			j = eschar;	/* fall through */
	default:
		setcbits(i, trtab[j]);
	}
	pchar1(i);
}


pchar1(i)
tchar i;
{
	register j, *k;

	j = cbits(i);
	if (dip != &d[0]) {
		wbf(i);
		dip->op = offset;
		return;
	}
	if (!tflg && !print) {
		if (j == '\n')
			dip->alss = dip->blss = 0;
		return;
	}
	if (no_out || j == FILLER)
		return;
	if (tflg) {	/* transparent mode, undiverted */
		fprintf(ptid, "%c", j);
		return;
	}
#ifndef NROFF
	if (ascii) {
		if (ismot(i)) {
			oput(' ');
			return;
		}
		if (j < 0177 && j != WORDSP) {
			oput(j);
			return;
		}
		if (j == HYPHEN || j == MINUS)
			oput('-');
		else if (j == LIG_FI)
			oputs("fi");
		else if (j == LIG_FL)
			oputs("fl");
		else if (j == LIG_FF)
			oputs("ff");
		else if (j == LIG_FFI)
			oputs("ffi");
		else if (j == LIG_FFL)
			oputs("ffl");
		else if (j == NARSP || j == HNARSP || j == WORDSP)
			;	/* nothing at all */
		else {
			oput('\\');
			oput('(');
			oput(chname[chtab[j-128]]);
			oput(chname[chtab[j-128]+1]);
		}
	} else
#endif
		ptout(i);
}


oput(i)
char	i;
{
	*obufp++ = i;
	if (obufp >= &obuf[OBUFSZ])
		flusho();
}


oputs(i)
register char	*i;
{
	while (*i != 0)
		oput(*i++);
}


flusho()
{
	if (obufp == obuf)
		return;
	if (no_out == 0) {
		if (!toolate) {
			toolate++;
#ifdef NROFF
			if (t.bset || t.breset) {
				if (ttysave == -1) {
					gtty(1, &ttys);
					ttysave = ttys.sg_flags;
				}
				ttys.sg_flags &= ~t.breset;
				ttys.sg_flags |= t.bset;
				stty(1, &ttys);
			}
			 {
				char	*p = t.twinit;
				while (*p++)
					;
				write(ptid, t.twinit, p - t.twinit - 1);
			}
#endif
		}
		toolate += write(ptid, obuf, obufp - obuf);
	}
	obufp = obuf;
}


done(x) 
int	x;
{
	register i;

	error |= x;
	level = 0;
	app = ds = lgf = 0;
	if (i = em) {
		donef = -1;
		em = 0;
		if (control(i, 0))
			longjmp(sjbuf, 1);
	}
	if (!nfo)
		done3(0);
	mflg = 0;
	dip = &d[0];
	if (woff)
		wbt((tchar)0);
	if (pendw)
		getword(1);
	pendnf = 0;
	if (donef == 1)
		done1(0);
	donef = 1;
	ip = 0;
	frame = stk;
	nxf = frame + 1;
	if (!ejf)
		tbreak();
	nflush++;
	eject((struct s *)0);
	longjmp(sjbuf, 1);
}


done1(x) 
int	x; 
{
	error |= x;
	if (v.nl) {
		trap = 0;
		eject((struct s *)0);
		longjmp(sjbuf, 1);
	}
	if (nofeed) {
		ptlead();
		flusho();
		done3(0);
	} else {
		if (!gflag)
			pttrailer();
		done2(0);
	}
}


done2(x) 
int	x; 
{
	ptlead();
#ifndef NROFF
	if (!ascii)
		ptstop();
#endif
	flusho();
	done3(x);
}

done3(x) 
int	x;
{
	error |= x;
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	unlink(unlkp);
#ifdef NROFF
	twdone();
#endif
	if (quiet) {
		ttys.sg_flags |= ECHO;
		stty(0, &ttys);
	}
	if (ascii)
		mesg(1);
	exit(error);
}


edone(x) 
int	x;
{
	frame = stk;
	nxf = frame + 1;
	ip = 0;
	done(x);
}



casepi()
{
	register i;
	int	id[2];

	if (toolate || skip() || !getname() || pipe(id) == -1 || (i = fork()) == -1) {
		fprintf(stderr, "Pipe not created.\n");
		return;
	}
	ptid = id[1];
	if (i > 0) {
		close(id[0]);
		toolate++;
		pipeflg++;
		return;
	}
	close(0);
	dup(id[0]);
	close(id[1]);
	execl(nextf, nextf, 0);
	fprintf(stderr, "Cannot exec %s\n", nextf);
	exit(-4);
}
