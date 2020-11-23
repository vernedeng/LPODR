#include "van-convert.h"


using namespace ns3;



void VelToPolar(double vx, double vy, uint64_t & vel, uint64_t & dirc)
{
    double v = sqrt(vx*vx + vy*vy);
    double di = atan(vy/vx);
    di = di*180/3.1415;
    if(vx >0 && vy<0) di+=360;
    else if(vx<0) di+=180;

    vel = (uint64_t)v;
    dirc = (uint64_t)di;

}

void PolarToVel(uint64_t vel, uint64_t dirc, Vector & ret)
{
    double di = (double)dirc/180*3.1415;
  
    ret.x = vel*cos(di);
    ret.y = vel*sin(di);

}


double CalD(Vector mypos, Vector itspos)
{
    double R = 250.0;
    double dx = mypos.x - itspos.x;
    double dy = mypos.y - itspos.y;
    double dij = sqrt(dx*dx + dy*dy);

    //if  ij out of the communication range, return -1;
    if(dij >  R) return -1.0;
    
    //else return 1- dij/R
    return (1-dij/R);
}

double CalY(Vector myvel, Vector itsvel)
{
    double scaleFactor = 0.01;
    double dx = myvel.x - itsvel.x;
    double dy = myvel.y - itsvel.y;
    double vre = sqrt(dx*dx + dy*dy);
    //return exp(-a*vre)
    return exp(-1 * scaleFactor * vre);

}

double CalN(Vector mypos, Vector itspos,Vector myvel, Vector itsvel)
{
    double D = CalD(mypos, itspos);
    if(D<0) return -1.0;
    
    double Y = CalY(myvel,itsvel);
    std::cout<<"D*Y is "<<D*Y<<std::endl;
    return D*Y;
}

double CalT(Vector mypos, Vector itspos,Vector myvel, Vector itsvel)
{
    double a = myvel.x - itsvel.x;
    double b = mypos.x - itspos.x;
    double c = myvel.y - itsvel.y;
    double d = mypos.y - itspos.y;
    double r = 250;
    std::cout<<"abcdr are "<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<r<<std::endl;

    //cal tij
    double tij = -1*( a*b+c*d) + sqrt((a*a+c*c)*r*r - (a*d-b*c)*(a*d-b*c));
    tij = tij / (a*a+c*c);
    
    std::cout<<"tij is "<<tij<<std::endl;
    std::cout<<"1- exp(-1*tij) is "<<1- exp(-1*tij)<<std::endl;
    return 1- exp(-1*tij);
}


double CalMetric( Vector u, double lastMetric, Vector mypos, Vector myvel, Vector itspos, Vector itsvel)
{
    double N = CalN(mypos,itspos,myvel,itsvel);
    std::cout<<"N is "<<N<<std::endl;
    //out of communication range
    if(N < 0) return -1.0; 

    double T = CalT(mypos,itspos,myvel,itsvel);
    std::cout<<"T is "<<T<<std::endl;
    
    return u.x*lastMetric + u.y*N + u.z*T;
}
