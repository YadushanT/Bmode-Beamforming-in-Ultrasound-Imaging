#include "imageParam.h"

using namespace std;

imageParam::imageParam()
{
    numElement = 128;
    numSample = 3338;
    numScanline = 127;

    elementPosition = genElementPosition();
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition);
}

imageParam::~imageParam()
{
    deletePositionArray();
}

float *imageParam::genElementPosition()
{
    //new float array elePosition of numElement size (x-direction)
    float *elePosition = new float[numElement]; // Defines elePosition array with 128 elements
    //for loop to store element location into each array elemen
    for (int i = 0; i < numElement + 1; i++)
        elePosition[i] = (i - ((float(numElement) - 1.0) / 2.0)) * PITCH; // Solves for eleLocation at each element
    return elePosition;
}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float *elementLocation)
{
    float depth;

    //user inputs for depth and numPixel
    cout << "Scanline Depth: ";
    cin >> depth;

    cout << "Number of Pixels: ";
    cin >> numPixel;

    float2 **scanlinePosition = new float2 *[numScanline];
    float depthstepsize = depth / numPixel;

    for (int i = 0; i < numScanline; i++)
    {
        scanlinePosition[i] = new float2[numPixel];
        for (int k = 0; k < numPixel; k++)
        {
            // Stores values at the x and y scanlinePosition
            scanlinePosition[i][k].x = (i - ((numScanline - 1.0) / 2.0)) * PITCH;
            scanlinePosition[i][k].y = depthstepsize * k;
        }
    }
    return scanlinePosition;
}

float imageParam::getXPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].x;
}

float imageParam::getYPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].y;
}

float imageParam::getElementPosition(int element)
{
    return elementPosition[element];
}

int imageParam::getNumElement()
{
    return numElement;
}

int imageParam::getNumSample()
{
    return numSample;
}

int imageParam::getNumScanline()
{
    return numScanline;
}

int imageParam::getNumPixel()
{
    return numPixel;
}

void imageParam::deletePositionArray()
{
    for (int i = 0; i < numPixel; i++)
        delete scanlinePosition[i]; // Releases the memory of each element
    // Releases the memory allocated to both variables below
    delete elementPosition;
    delete scanlinePosition;
}