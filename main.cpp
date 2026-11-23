#include <opencv2/opencv.hpp>
#include <iostream>
#include "alg.h"

int main()
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_WARNING); //logi off

   // cv::Mat original = cv::imread("Pan_zywiec_zdroj_wynalazca_wody.png");
    //cv::Mat original = cv::imread("kot.jpg");
   // cv::Mat original = cv::imread("open.png");
    cv::Mat original = cv::imread("frog.png");

    if (original.empty())
    {
        std::cout << "Nie udalo sie wczytac obrazu.\n";
        return 1;
    }
     cv::Mat wynik = original.clone();



     

	 std::string command;





     std::vector<double> blur = {  //srednia daje blur
    1.0 / 9, 1.0 / 9, 1.0 / 9,
    1.0 / 9, 1.0 / 9, 1.0 / 9,
    1.0 / 9, 1.0 / 9, 1.0 / 9
     };


     std::vector<double> sharpenFilter = {
     0, -1,  0,
    -1,  5, -1,
     0, -1,  0
     };

     std::vector<double> highPassFilter = {
    -1, -1, -1,
    -1,  8, -1,
    -1, -1, -1
     };

     std::vector<double> lowPassFilter = {
    1.0 / 10, 1.0 / 10, 1.0 / 10,
    1.0 / 10, 2.0 / 10, 1.0 / 10,
    1.0 / 10, 1.0 / 10, 1.0 / 10
     };

     std::vector<double> gauss = {  
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16
     };


     std::vector<double> gauss2 = {
    1.0 / 25, 3.0 / 25, 1.0 / 25,
    3.0 / 25, 9.0 / 25, 3.0 / 25,
    1.0 / 25, 3.0 / 25, 1.0 / 25
     };

     std::vector<double> gauss3 = {
    1.0 / 49, 5.0 / 49, 1.0 / 49,
    5.0 / 49, 27.0 / 49, 5.0 / 49,
    1.0 / 49, 5.0 / 49, 1.0 / 49
     };



     while (true) {

		 std::cout << " q - quit, o - original, rc - grayscaleRedChannel, rw - grayscaleweighted, dl - darker/lighter , b - binarization\n";
         std::cout << " d - dilatation ; e - erosion; op - opening; c - closing, co - convultion \n";

         std::cin >> command;

         if(command == "q") {
             break;
         }
         else if (command == "o") {

             wynik = original.clone();

         }
         else if(command == "rc") {

			 grayscaleRed(wynik);

         }
         else if (command == "rw") {

			 grayscaleWeighted(wynik);

         }
         else if (command == "dl") {

             int val;
             std::cin >> val;

             darker_lighter(wynik, val);

         }
         else if(command == "b") {
             int val;
             std::cin >> val;
		  binarization(wynik, val);

         }
         else if (command == "s") {
             std::string filename;
             std::cin >> filename;
             cv::imwrite(filename, wynik);
         }
         else if (command == "d") {
             int x;
			 std::cin >> x;
			 dylate(wynik,x);
         }
         else if (command == "e") {
             int x;
             std::cin >> x;
             erode(wynik, x);
         }
         else if (command == "op") {
             int x;
             std::cin >> x;
             opening(wynik, x);
         }
         else if (command == "c") {
             int x;
             std::cin >> x;
             closing(wynik, x);
         }
         else if (command == "co") {
           

             std::cout << " co - gaussian, bl - blur, sh - sharpen, hp - high-pass, lp - low-pass\n";
             std::cout << " g1 - gauss sigma1, g2 - gauss sigma2, g3 - gauss sigma3\n";

             std::cin >> command;
            if (command == "co") {
                 convolution(wynik, gauss, 1);
            }
            else if (command == "bl") {
             convolution(wynik, blur, 1);
            }
            else if (command == "sh") {
             convolution(wynik, sharpenFilter, 1);
            }
            else if (command == "hp") {
                convolution(wynik, highPassFilter, 1);
            }
            else if (command == "lp") {
                 convolution(wynik, lowPassFilter, 1);
            }
            else if (command == "g1") {
              convolution(wynik, gauss, 1);
             }
            else if (command == "g2") {
                 convolution(wynik, gauss2, 1);
            }
            else if (command == "g3") {
              convolution(wynik, gauss3, 1);
            }else if(command == "q") {
                continue;
			}
            
			 
         }
         else {

             std::cout << " ???\n";
         }




        cv::imshow("Moj obraz", wynik);
        cv::moveWindow("Moj obraz", 50, 50);
        cv::waitKey(1);





     }









    return 0;
}