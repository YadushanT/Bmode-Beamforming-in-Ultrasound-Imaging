#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer()
{
    // Initialize variables
    numElement = 0;
    numSample = 0;
    scanline = 0;

    dataMatrix = NULL;
    next = NULL;
}

dataBuffer::dataBuffer(std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    // reinitialze variables
    numElement = inputNumElement;
    numSample = inputNumSample;
    scanline = inputScanline;

    dataMatrix = createDataMatrix();                      // Calls function createDataMatrix
    int num = loadRFData(dataMatrix, imagFile, realFile); // Calls function loadRFData with parameter values
}

dataBuffer::~dataBuffer()
{
    deleteDataMatrix(); // To release the data stored in dataMatrix, the destructor calls the deleteDataMatrix function.
}

complex **dataBuffer::createDataMatrix()
{
    complex **RFData;                   // Create a double pointer RFData 
    RFData = new complex *[numElement]; // Creates a pointer array of type complex with numElement elements

    for (int i = 0; i < numElement; i++)
        RFData[i] = new complex[numSample];//for loop creates new complex array of numSample size for each numElement in RFData
    return RFData;
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile)
{
    const int MAX_SIZE = 100; 
    char line[MAX_SIZE];

    for (int i = 0; i < numElement; i++) {
        for (int j = 0; j < numSample; j++) {
            imagFile->getline(line, MAX_SIZE); // open imag text file
            RFData[i][j].imag = atof(line);     // convert each charcter array to float and store in RFData array

            realFile->getline(line, MAX_SIZE); // open real text file
            RFData[i][j].real = atof(line);     // convert each charcter array to float and store in RFData array
        }
    }

    if (imagFile->fail() || realFile->fail())
        return -1;
    return 0;
}

float dataBuffer::getRealRFData(int element, int sample)
{
    // Returns real component of the stored data in dataMatrix
    return dataMatrix[element][sample].real;
}

float dataBuffer::getImagRFData(int element, int sample)
{
    // Returns imaginary component of the stored data in dataMatrix
    return dataMatrix[element][sample].imag;
}

void dataBuffer::deleteDataMatrix()
{
    // delete dataMatrix and release all memory allocation
    for (int i = 0; i < numElement; i++)
        delete dataMatrix[i];
    delete dataMatrix;
}