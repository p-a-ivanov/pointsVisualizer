#include "point.h"

namespace func
{

    struct planeEquation
    {
        double A, B, C, D;
        planeEquation(double a, double b, double c, double d);
    };
    
    std::vector<std::vector<Point>> getPoints(std::string file_name, bool isPlns);

    void checkPoints(std::vector<std::vector<Point>> plnVectors, std::vector<Point> ptVector, std::string file_name);



}