#include "globalvar.h"

// ------------------------------------------------------------------
SetupData m_setup;
// ------------------------------------------------------------------

#define fPI 3.1415926535
#define fGRAD_TO_RAD (fPI/180.)
#define fRAD_TO_GRAD (180./fPI)
#define fRAD_TO_MIN (60./fGRAD_TO_RAD)

// ------------------------------------------------------------------
void NormalToGeo(double dNormal, int *pnGr, int *pnMin, float *pfSec)
{
	int nN = (int)(dNormal * fRAD_TO_MIN * 6000.);
	*pfSec = (float(nN % 6000)) / 100.f;
	nN /= 6000;
	*pnMin = nN % 60;
	*pnGr = nN / 60;
}

// ------------------------------------------------------------------
