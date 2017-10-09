#ifndef __CONSTANTS_H_
#define __CONSTANTS_H_


double getusec_();

#define START_COUNT_TIME stamp=getusec_();
#define STOP_COUNT_TIME(_m) stamp=getusec_()-stamp;\
                        stamp=stamp/1e6;\
                        printf ("%s:%0.6fs\n",(_m), stamp);

#define  ERROR(_s) {printf("%s\n",(_s)); return 1;}

// Extrae Constants
#define  PROGRAM 		1000
#define  END 			0
#define  PI_COMPUTATION 	1
#define  REST_MAIN		2
#define  TIMING			3



#endif
