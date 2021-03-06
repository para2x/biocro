/*
 *  /src/c4photo.h by Fernando Ezequiel Miguez  Copyright (C) 2007-2008
 *
 */

#ifndef C4PHOTO_h
#define C4PHOTO_H
int nObs;

struct c4_str {

	double Assim;
	double Gs;
	double Ci;
  double GrossAssim;

};

/* Function needed for ballBerry */
extern double fnpsvp(double Tkelvin);
extern double ballBerry(double Amu, double Cappm, double Temp, double RelH, double beta0, double beta1);
extern struct c4_str c4photoC(double Qp, double Tl, double RH, double vmax, double alpha, 
			      double kparm, double theta, double beta, double Rd, double bb0, double bb1, double StomaWS, double Ca, int ws,double upperT,double lowerT);


/* Declaring the RSS_C4photo */
extern double RSS_C4photo(double oAssim[nObs], double oQp[nObs], double oTemp[nObs], 
		   double oRH[nObs], double vmax, double alpha, double kparm,
			  double theta, double beta,
			  double Rd, double Catm, double b0, double b1, double StomWS, int ws,double upperT,double lowerT);


#endif