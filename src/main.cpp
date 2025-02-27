#include <cstdint>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

const long double angle120 = 120 * M_PI / 180;
const long double maxAmplitude = (sin(angle120 / 2) - sin(-angle120 / 2));

ofstream csv("result.csv");
ofstream mapSvmPwm0("result0.c");

void calcForAngle(const long double angle)
{

    const long double
        v[3] = {sin(angle), sin(angle - angle120), sin(angle + angle120)},
        vMin = min(v[0], min(v[1], v[2])),
        vMax = max(v[0], max(v[1], v[2])),
        center = (vMin + vMax) / 2,
        svmPwm0 = (v[0] - vMin) / maxAmplitude,
        svmPwm1 = (vMax - v[0]) / maxAmplitude,
        svmPwmCenter = (v[0] - center) / maxAmplitude + 0.5;

    csv << angle << ',' << v[0] << ',' << vMin << ',' << vMax << ',' << center << ',' << svmPwm0 << ',' << svmPwm1 << ',' << svmPwmCenter << ',' << svmPwm1 << endl;
    mapSvmPwm0 << (unsigned int)(uint8_t)round(svmPwm0 * 255) << "," << endl;
}

int main()
{
    cout << "angle120=" << angle120 << ", maxAmplitude" << maxAmplitude << endl;
    csv << "angle,sin,vMin,vMax,center,svmPwm0,svmPwm1,svmPwmCenter" << endl;
    mapSvmPwm0 << "const uint8_t map[] = {";

    for (int i = 0; i < 256; ++i)
    {
        calcForAngle(i * 2 * M_PI / 256);
    }
    mapSvmPwm0 << "};" << endl;

    return 0;
}
