#include <stdio.h>
#include <math.h>
#include <time.h>

/*#define double long double*/

long int count;

time_t now,then;
int printout=0;

main(int argc, char * argv[])
{
  int i;

  printf("Astrophysical Speed test V 2.01 : Ten second sample...\n");
  printf("Paul Salanitri (c) 1996 Futex\n");
  if (argc>1) {
	if (argv[1][0]=='/' || argv[1][0]=='-') {
	  if (tolower(argv[1][1])=='h') {
		printf("%s [-s|-h]\n",argv[0]);
		printf("  -s : print solution\n");
		exit(1);
	  } else if (tolower(argv[1][1])=='s') {
		printout=1;
		calc_moon(2450000.0);
		exit(0);
	  }
	} else {
	}
  }
  count=0L;
  then=clock();

  while (1) {
/*	calc_moon(2415020.0);*/
/*	calc_moon(2450000.0); */
/*	calc_moon(2450000.0 + (double)count);*/
	calc_moon((long double)((double)2450000.0 + (double)count));
	count++;
	now=clock();
	if (now-then>=CLK_TCK*10) break;
  }


  printf("Calculations per second : %16.4f\n",count/10.0);
  printf("Calculations time       : %10.6f usec\n",10.0/count*1000000.0);
  exit(0);
}

const double dtor=180.0/M_PI;
const double AU=1.0;

calc_moon(JD)
double JD;
{

/* The new harmonic solution to the position of the moon */
  double dummy;
  double t,t2;
  double m1,m2,m3,m4,m5,m6;
  double q,ml,ms,md,me,mf;
  double na;
  double a,s1,s2,b,s3,c,s4,e,e2;
  double l,mm,tp;
  double g,w1,w2,bm;
  double pm,r;

  JD=JD-2415020.0; /* move to Jan 0.5 1900 */
  t=(JD/36525.0); t2=t*t;
  m1=2.732158213e1; m2=3.652596407e2;
  m3=2.755455094e1; m4=2.953058868e1;
  m5=2.721222039e1; m6=6.798363307e3;
  q=JD; m1=q/m1; m2=q/m2;
  m3=q/m3; m4=q/m4; m5=q/m5; m6=q/m6;
  m1=360.0*modf(m1,&dummy);
  m2=360.0*modf(m2,&dummy);
  m3=360.0*modf(m3,&dummy);
  m4=360.0*modf(m4,&dummy);
  m5=360.0*modf(m5,&dummy);
  m6=360.0*modf(m6,&dummy);
  ml=2.70434164e2+m1-(1.133e-3-1.9e-6*t)*t2;
  ms=3.58475833e2+m2-(1.5e-4+3.3e-6*t)*t2;
  md=2.96104608e2+m3+(9.192e-3+1.44e-5*t)*t2;
  me=3.50737486e2+m4-(1.436e-3-1.9e-6*t)*t2;
  mf=11.250889+m5-(3.211e-3+3e-7*t)*t2;

  na=2.59183275e2-m6+(2.078e-3+2.2e-6*t)*t2;


	a=(51.2+20.2*t)/dtor; s1=sin(a); s2=sin(na/dtor);
	b=346.56+(132.87-9.1731e-3*t)*t;
	s3=3.964e-3*sin(b/dtor);
	c=(na+275.05-2.3*t)/dtor;  s4=sin(c);
	ml=ml+2.33e-4*s1+s3+1.964e-3*s2;
	ms=ms-1.778e-3*s1;
	md=md+8.17e-4*s1+s3+2.541e-3*s2;
	mf=mf+s3-2.4691e-2*s2-4.328e-3*s4;
	me=me+2.011e-3*s1+s3+1.964e-3*s2;
	e=1-(2.495e-3+7.52e-6*t)*t; e2=e*e;
	ml=ml/dtor; ms=ms/dtor; na=na/dtor;
	me=me/dtor; mf=mf/dtor; md=md/dtor;

	l=6.28875*sin(md)+1.274018*sin(2.0*me-md);
	l=l+6.58309e-1*sin(2.0*me)+2.13616e-1*sin(2.0*md);
	l=l-e*1.85596e-1*sin(ms)-1.14336e-1*sin(2.0*mf);
	l=l+5.8793e-2*sin(2.0*(me-md));
	l=l+5.7212e-2*e*sin(2.0*me-ms-md)+5.332e-2*sin(2.0*me+md);
	l=l+4.5874e-2*e*sin(2.0*me-ms)+4.1024e-2*e*sin(md-ms);
	l=l-3.4718e-2*sin(me)-e*3.0465e-2*sin(ms+md);
	l=l+1.5326e-2*sin(2.0*(me-mf))-1.2528e-2*sin(2.0*mf+md);
	l=l-1.098e-2*sin(2.0*mf-md)+1.0674e-2*sin(4.0*me-md);
	l=l+1.0034e-2*sin(3.0*md)+8.548e-3*sin(4.0*me-2.0*md);
	l=l-e*7.91e-3*sin(ms-md+2.0*me)-e*6.783e-3*sin(2.0*me+ms);
	l=l+5.162e-3*sin(md-me)+e*5e-3*sin(ms+me);
	l=l+3.862e-3*sin(4.0*me)+e*4.049e-3*sin(md-ms+2.0*me);
	l=l+3.996e-3*sin(2.0*(md+me))+3.665e-3*sin(2.0*me-3.0*md);
	l=l+e*2.695e-3*sin(2.0*md-ms)+2.602e-3*sin(md-2.0*(mf+me));
	l=l+e*2.396e-3*sin(2.0*(me-md)-ms)-2.349e-3*sin(md+me);
	l=l+e2*2.249e-3*sin(2.0*(me-ms))-e*2.125e-3*sin(2.0*md+ms);
	l=l-e2*2.079e-3*sin(2.0*ms)+e2*2.059e-3*sin(2.0*(me-ms)-md);
	l=l-1.773e-3*sin(md+2.0*(me-mf))-1.595e-3*sin(2.0*(mf+me));
	l=l+e*1.22e-3*sin(4.0*me-ms-md)-1.11e-3*sin(2.0*(md+mf));
	l=l+8.92e-4*sin(md-3.0*me)-e*8.11e-4*sin(ms+md+2.0*me);
	l=l+e*7.61e-4*sin(4.0*me-ms-2.0*md);
	l=l+e2*7.04e-4*sin(md-2.0*(ms+me));
	l=l+e*6.93e-4*sin(ms-2.0*(md-me));
	l=l+e*5.98e-4*sin(2.0*(me-mf)-ms);
	l=l+5.5e-4*sin(md+4.0*me)+5.38e-4*sin(4.0*md);
	l=l+e*5.21e-4*sin(4.0*me-ms)+4.86e-4*sin(2.0*md-me);
	l=l+e2*7.17e-4*sin(md-2.0*ms);
	mm=ml+l/dtor; tp=6.283185308;
	while (mm<0.0) mm=mm+tp;
	while (mm>tp) mm=mm-tp;

	g=5.128189*sin(mf)+2.80606e-1*sin(md+mf);
	g=g+2.77693e-1*sin(md-mf)+1.73238e-1*sin(2.0*me-mf);
	g=g+5.5413e-2*sin(2.0*me+mf-md)+4.6272e-2*sin(2.0*me-mf-md);
	g=g+3.2573e-2*sin(2.0*me+mf)+1.7198e-2*sin(2.0*md+mf);
	g=g+9.267e-3*sin(2.0*me+md-mf)+8.823e-3*sin(2.0*md-mf);
	g=g+e*8.247e-3*sin(2.0*me-ms-mf)+4.323e-3*sin(2.0*(me-md)-mf);
	g=g+4.2e-3*sin(2.0*me+mf+md)+e*3.372e-3*sin(mf-ms-2.0*me);
	g=g+e*2.472e-3*sin(2.0*me+mf-ms-md);
	g=g+e*2.222e-3*sin(2.0*me+mf-ms);
	g=g+e*2.072e-3*sin(2.0*me-mf-ms-md);
	g=g+e*1.877e-3*sin(mf-ms+md)+1.828e-3*sin(4.0*me-mf-md);
	g=g-e*1.803e-3*sin(mf+ms)-1.75e-3*sin(3.0*mf);
	g=g+e*1.57e-3*sin(md-ms-mf)-1.487e-3*sin(mf+me);
	g=g-e*1.481e-3*sin(mf+ms+md)+e*1.417e-3*sin(mf-ms-md);
	g=g+e*1.35e-3*sin(mf-ms)+1.33e-3*sin(mf-me);
	g=g+1.106e-3*sin(mf+3.0*md)+1.02e-3*sin(4.0*me-mf);
	g=g+8.33e-4*sin(mf+4.0*me-md)+7.81e-4*sin(md-3.0*mf);
	g=g+6.7e-4*sin(mf+4.0*me-2.0*md)+6.06e-4*sin(2.0*me-3.0*mf);
	g=g+5.97e-4*sin(2.0*(me+md)-mf);
	g=g+e*4.92e-4*sin(2.0*me+md-ms-mf)+4.5e-4*sin(2.0*(md-me)-mf);
	g=g+4.39e-4*sin(3.0*md-mf)+4.23e-4*sin(mf+2.0*(me+md));
	g=g+4.22e-4*sin(2.0*me-mf-3.0*md)-e*3.67e-4*sin(ms+mf+2.0*me-md);
	g=g-e*3.53e-4*sin(ms+mf+2.0*me)+3.31e-4*sin(mf+4.0*me);
	g=g+e*3.17e-4*sin(2.0*me+mf-ms+md);
	g=g+e2*3.06e-4*sin(2.0*(me-ms)-mf)-2.83e-4*sin(md+3.0*mf);
	w1=4.664e-4*cos(na);  w2=7.54e-5*cos(c);
	bm=g/dtor*(1.0-w1-w2);

	pm=9.50724e-1+5.1818e-2*cos(md)+9.531e-3*cos(2.0*me-md);
	pm=pm+7.843e-3*cos(2.0*me)+2.824e-3*cos(2.0*md);
	pm=pm+8.57e-4*cos(2.0*me+md)+e*5.33e-4*cos(2.0*me-ms);
	pm=pm+e*4.01e-4*cos(2.0*me-md-ms);
	pm=pm+e*3.2e-4*cos(md-ms)-2.71e-4*cos(me);
	pm=pm-e*2.64e-4*cos(ms+md)-1.98e-4*cos(2.0*mf-md);
	pm=pm+1.73e-4*cos(3.0*md)+1.67e-4*cos(4.0*me-md);
	pm=pm-e*1.11e-4*cos(ms)+1.03e-4*cos(4.0*me-2.0*md);
	pm=pm-8.4e-5*cos(2.0*md-2.0*me)-e*8.3e-5*cos(2.0*me+ms);
	pm=pm+7.9e-5*cos(2.0*me+2.0*md)+7.2e-5*cos(4.0*me);
	pm=pm+e*6.4e-5*cos(2.0*me-ms+md)-e*6.3e-5*cos(2.0*me+ms-md);
	pm=pm+e*4.1e-5*cos(ms+me)+e*3.5e-5*cos(2.0*md-ms);
	pm=pm-3.3e-5*cos(3.0*md-2.0*me)-3e-5*cos(md+me);
	pm=pm-2.9e-5*cos(2.0*(mf-me))-e*2.9e-5*cos(2.0*md+ms);
	pm=pm+e2*2.6e-5*cos(2.0*(me-ms))-2.3e-5*cos(2.0*(mf-me)+md);
	pm=pm+e*1.9e-5*cos(4.0*me-ms-md);
	pm=pm/dtor;

	r=6378.14/sin(pm)/AU;

	if (printout) {
	  printf("Solution for JD=%lf\n",JD+2415020.0);
	  printf("  mm=%30.25lf\n",mm);
	  printf("  bm=%30.25lf\n",bm);
	  printf("  pm=%30.25lf\n",pm);
	  /*
	  printf("Solution for JD=%Lf\n",JD+2415020.0);
	  printf("  mm=%30.25Lf\n",mm);
	  printf("  bm=%30.25Lf\n",bm);
	  printf("  pm=%30.25Lf\n",pm);
	  */
	}
}


/*
Moon Position numerical
16800 GOTO16830:REMii=-5.145*sin(2*�*(td-181.5833)/27.21222)
16802 ii=-5.1454*SIN(2*�*(td+4336.5382)/27.21222)
16810 REMm=(td-181.5833)/27.321661:m=(m-int(m))*360+230.138851
16812 m=(td-4.903472222)/27.321661:m=(m-INT(m))*360+58.843643
16814 REMm=(td+4336.5382)/27.32158:m=(m-int(m))*360+98.6496618
16820 ha(n)=m:hp(n)=ii:ga(n)=m:gp(n)=ii:GOTO2140
!
16830 nm=dc-2436935+(h0+m0/60)/24:m=nm/27.321582+311.1687/360:m=(m-INT(m))*360:PRINT"m="m"";                         :REM (582)
16835 REMpg=(m-(nm*.111404+255.7433))/360:pg=(pg-int(pg))*360:print"(m-)pg="pg;
16840 m=m+ 6.2886*SIN((m-(nm*.111404+255.7433))/kk)
16850 REMm=m+dr
16860 ii=5.1454*SIN((m-178.699+nm*.052954)/kk)
16861 PRINT"dc=";dc;"m="m;"inc"ii
16862 :   :GOTO16820
*/
