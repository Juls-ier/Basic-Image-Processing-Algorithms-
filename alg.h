#pragma once

#include <opencv2/core.hpp>
#include <vector>


void grayscaleRed(cv::Mat& obraz);     // usun 2 z 3 val z jedneego

void grayscaleWeighted( cv::Mat& image);    //Œrednia wa¿ona    

void  darker_lighter(cv::Mat& image, int value);  // przyciemnij obraz o value

void binarization(cv::Mat& image, int value = 50);  // binaryzacja obrazu


// lab 2
 
void dylate(cv::Mat& image, int value); 

void erode(cv::Mat& image, int value );  

void opening(cv::Mat& image, int value);
void closing(cv::Mat& image, int value);

void convolution( cv::Mat& image,  std::vector<double>& filter, int value);