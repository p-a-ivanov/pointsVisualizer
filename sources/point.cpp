#include "../headers/func.h"

Point::Point(std::string pointStr){
    
    
    std::istringstream value(pointStr);
    std::vector<std::string> points((std::istream_iterator<std::string>(value)), std::istream_iterator<std::string>());

    cX = std::stod(points[0], NULL);
    cY = std::stod(points[1], NULL);
    cZ = std::stod(points[2], NULL);
}


