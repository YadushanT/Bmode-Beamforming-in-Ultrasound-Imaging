#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer()
{
    int numElement, numSample, scanline = 0;
    complex **dataMatrix = NULL;
    dataBuffer *next = NULL;
}

dataBuffer::dataBuffer( std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    inputNumElement = numElement;
    inputNumSample = numSample;
    inputScanline = scanline;
} 

dataBuffer::~dataBuffer()
{

}

complex **dataBuffer::createDataMatrix()
{
 
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) 
{ 

}

float dataBuffer::getRealRFData(int element,int sample)
{

}
float dataBuffer::getImagRFData(int element,int sample)
{

}

void dataBuffer::deleteDataMatrix()
{

}




