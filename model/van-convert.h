#ifndef VAN_CONVERT_H
#define VAN_CONVERT_H


#include <algorithm>
#include <string>
#include <cmath>
#include <stdint.h>
#include <iostream>
#include "ns3/vector.h"

using namespace ns3;

void VelToPolar(double vx, double vy, uint64_t & vel, uint64_t & dirc);

void PolarToVel(uint64_t vel, uint64_t dirc, Vector & ret);

double CalD(Vector mypos, Vector itspos);

double CalY(Vector myvel, Vector itsvel);

double CalN(Vector mypos, Vector itspos,Vector myvel, Vector itsvel);

double CalT(Vector mypos, Vector itspos,Vector myvel, Vector itsvel);

double CalMetric( uint16_t u1,  uint16_t u2, uint16_t u3, double lastMetric, Vector mypos, Vector myvel, Vector itspos, Vector itsvel);


#endif