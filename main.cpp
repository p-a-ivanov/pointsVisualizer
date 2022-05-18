#include "headers/func.h"

int main(int, char**) {

    std::cout << "Please enter file name to input points: ";
    std::string pointFileName;
    std::cin >> pointFileName;
    std::string strippedFileName = pointFileName.substr(0, pointFileName.find_last_of('.'));
    std::cout << '\n';

    std::vector<Point> pointsContainer = func::getPoints(pointFileName, false)[0];
    std::cout << "Please enter file name to input planes: ";
    std::string planeFileName;
    std::cin >> planeFileName;
    std::cout << '\n';

    std::vector<std::vector<Point>> planes = func::getPoints(planeFileName, true);
    try{
        func::checkPoints(planes, pointsContainer, strippedFileName);
    }catch(...){
        std::cout << '\n' << "Some kind of error occured. Validate the data and try again";
        return 1;
    }
    std::cout << '\n' << "All points have been processed. Do you want to launch a visualisation script? (Y/n)" << '\n';
    char scr;
    std::cin >> scr;
    while(!((scr != 'n'|| scr != 'N') || (scr != 'Y' || scr!= 'y'))){
        std::cout << "Command was not recognized. Do you want to launch a visualisation script? (Y/n)" << '\n';
        std::cin >> scr;
    }
    if(scr == 'n' || scr == 'N'){
        std::cout << "Closing the program..." << '\n';
        //sleep(3);
        return 1;
    }
    std::cout << "Launching visualisation script..." << '\n';
    //Py_Initialize();


     int res = system(("python3 ./../pointsVisualizer.py " + 
                     strippedFileName + "_good.txt " + 
                     strippedFileName + "_wrong.txt " + planeFileName).c_str());
    //int res = system("python3 ./../pointsVisualizer.py --str1 --str2 --str3");
    if(res != 0){
        std::cout << "Exit code was: " << res << '\n';
    }
    
    return 1;
}
