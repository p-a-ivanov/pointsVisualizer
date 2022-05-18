#include "../headers/func.h"

    func::planeEquation::planeEquation(double a, double b, double c, double d){
        func::planeEquation::A = a; 
        func::planeEquation::B = b; 
        func::planeEquation::C = c; 
        func::planeEquation::D = d;          
    }


    std::vector<std::vector<Point>> func::getPoints(std::string file_name, bool isPlns){

        std::ifstream input_stream("./../inputs/" + file_name, std::ios_base::binary);
        if (input_stream.fail()) {
            throw std::runtime_error("Failed to open file");
        }

        std::string strLine;
        std::vector<Point> vPoints;
        
        while (std::getline(input_stream, strLine)){
                vPoints.push_back(Point(strLine));
        }

        if(!isPlns){
            return std::vector<std::vector<Point>>{vPoints};
        }
        
        std::vector<std::vector<Point>> vvPoints;
        auto itr = vPoints.begin();
        unsigned fullSize = vPoints.size();
        unsigned partsCount = ((vPoints.size() - 1)/3) + 1;
        for(unsigned i = 0; i < partsCount; ++i){
            auto partSize = fullSize / (partsCount - i);
            fullSize -= partSize;

            vvPoints.emplace_back(std::vector<Point>{itr, itr + partSize});
            itr +=partSize;
        }

        return vvPoints;

    }


    void func::checkPoints(std::vector<std::vector<Point>> plnVectors, std::vector<Point> ptVector, std::string fileName){

        std::vector<planeEquation> planeEqs;
        for(std::vector<Point> plane : plnVectors){

            double A, B, C, D;

            //A = y1 (z2 - z3) + y2 (z3 - z1) + y3 (z1 - z2)
            //B = z1 (x2 - x3) + z2 (x3 - x1) + z3 (x1 - x2)
            //C = x1 (y2 - y3) + x2 (y3 - y1) + x3 (y1 - y2)
            //- D = x1 (y2 z3 - y3 z2) + x2 (y3 z1 - y1 z3) + x3 (y1 z2 - y2 z1)

            A = plane[0].cY*(plane[1].cZ-plane[2].cZ)+plane[1].cY*(plane[2].cZ-plane[0].cZ)+plane[2].cY*(plane[0].cZ-plane[1].cZ);
            B = plane[0].cZ*(plane[1].cX-plane[2].cX)+plane[1].cZ*(plane[2].cX-plane[0].cX)+plane[2].cZ*(plane[0].cX-plane[1].cX);
            C = plane[0].cX*(plane[1].cY-plane[2].cY)+plane[1].cX*(plane[2].cY-plane[0].cY)+plane[2].cX*(plane[0].cY-plane[1].cY);
            D = -1 * (  plane[0].cX * ( plane[1].cY * plane[2].cZ - plane[2].cY * plane[1].cZ) + 
                        plane[1].cX * ( plane[2].cY * plane[0].cZ - plane[0].cY * plane[2].cZ) +
                        plane[2].cX * ( plane[0].cY * plane[1].cZ - plane[1].cY * plane[0].cZ) );
            planeEqs.push_back(planeEquation(A, B, C, D));
        }

        std::string goodPointsName = "./../outputs/" + fileName + "_good.txt";
        std::string wrongPointsName = "./../outputs/" + fileName + "_wrong.txt";

        std::ofstream outPtsGood;
        outPtsGood.open(goodPointsName);
        outPtsGood.close();
        std::ofstream outPtsWrong;
        outPtsWrong.open(wrongPointsName);
        outPtsWrong.close();

        int process = 0;
        int finish = ptVector.size();
        int segm = int(finish/100);
        int segmProcess = 0;

        std::cout << "Processing points... " << '\n';
        for(int a = 0; a < 100; a++){
            std::cout << '.';                               
        }
        std::cout << '\r';

        std::string ptsGood;
        std::string ptsWrong;
        for(Point P : ptVector){
            
            process++;

            bool isGood = false;
            for(size_t it = 1; it < planeEqs.size(); it++){

                double posCf1 = planeEqs[it].A*P.cX + planeEqs[it].B*P.cY + planeEqs[it].C*P.cZ + planeEqs[it].D;
                double posCf0 = planeEqs[it-1].A*P.cX + planeEqs[it-1].B*P.cY + planeEqs[it-1].C*P.cZ + planeEqs[it-1].D;

                if( it != 0 && ((posCf1 < 0 && posCf0 > 0) || (posCf1 > 0 && posCf0 < 0) || (posCf1 < 0 && posCf0 < 0)) ) {
                    ptsGood.append(std::to_string(P.cX) + ' ' + std::to_string(P.cY) + ' ' + std::to_string(P.cZ) + '\n');
                    isGood = true;
                    break;
                }
                
            }
            
            if(!isGood){
                ptsWrong.append(std::to_string(P.cX) + ' ' + std::to_string(P.cY) + ' ' + std::to_string(P.cZ) + '\n');
            }

            if(int(process/segm) > segmProcess ){
                segmProcess++;
                std::cout << '|';
                std::cout.flush();
            }

        }
        outPtsGood.open(goodPointsName, std::ios_base::app);
        outPtsGood << ptsGood;
        outPtsGood.close();

        outPtsWrong.open(wrongPointsName, std::ios_base::app);
        outPtsWrong << ptsWrong;
        outPtsWrong.close();

        std::cout << '\n';

        return;
    }
