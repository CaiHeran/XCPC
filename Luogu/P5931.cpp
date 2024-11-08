
// 这题有力地展现了数学之美。
#include <cstdio>
#include <cmath>

double H, h, D;

double len(double a)
{
/*
// len on floor
    double onfloor = a*h/(H-h);
    if (onfloor + a <= D)
        return onfloor;

    onfloor = D - a;

    double t = (H*a + h*D - H*D) / (H-h);
    double onwall = H*t / (D+t);

    return onfloor + onwall;
*/
    double tanA=(H-h)/a, floor=H/tanA;
    if (floor<=D)
        return floor-a;
    // double onfloor = D - a, onwall = (floor-D)/tanA;
    return D-a + (floor-D)*tanA;
}

int main()
{
    int T;
    scanf("%d", &T);
while (T--)
{
    scanf("%lf%lf%lf", &H, &h, &D);
    /*
    double l=0.0, r=D, m1, m2;
    while (r-l >= 0.001)
    {
        m1 = l+(r-l)/3.0,
        m2 = r-(r-l)/3.0;
        if (len(m1)<len(m2))
            l = m1;
        else
            r = m2;
    }
    printf("%.3lf\n", round(len(l)));
    */
    double t1 = sqrt(D*(H-h)), t2 = D*(H-h)/H;
    if (t1<=t2)
        printf("%.3lf\n", D - (H-h)*D/H);
    else if (t2<=t1 && t1<=D)
        printf("%.3lf\n", D + H - 2.0*sqrt(D*(H-h)));
    else if (t1>=D)
        printf("%.3lf\n", h);
}
}