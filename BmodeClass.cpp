#include "BmodeClass.h"

BmodeClass::BmodeClass()
{
    imparams = NULL;
    RFData = NULL;
    next = NULL;

    line = 0;
}

BmodeClass::BmodeClass(imageParam *params, dataBuffer *data, int numline)
{
    imparams = params;
    RFData = data;
    line = numline; // scanline numer

    scanline = createScanline(imparams->getNumPixel());
    beamform();
}

BmodeClass::~BmodeClass()
{
    deleteScanline();
}

float *BmodeClass::createScanline(int numPixel)
{
    float *mem = new float[numPixel];
    return mem;
}

void BmodeClass::beamform()
{
    float tForward[imparams->getNumPixel()];
    float tBackward[imparams->getNumPixel()][imparams->getNumElement()];
    float tTotal[imparams->getNumPixel()];
    int s[imparams->getNumPixel()][imparams->getNumElement()];
    float pReal;
    float pImag;

    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        tForward[i] = (imparams->getYPosition(line, i)) / imparams->SOS; //calculate time scan travels forward

        for (int k = 0; k < imparams->getNumElement(); k++)
        {
            tBackward[i][k] = sqrt(pow(imparams->getYPosition(line, i), 2) + pow((imparams->getXPosition(line, i)) - imparams->getElementPosition(k), 2)) / imparams->SOS; //calculate time scan travels back to tranducer element
            tTotal[i] = tForward[i] + tBackward[i][k]; //calculate total time of scan to travel                                                                                                                         
            s[i][k] = floor(tTotal[i] * imparams->FS); //sampling frequency of i'th scanline from k'th tranducer

            if (s[i][k] < imparams->getNumSample())
            {
                pReal += RFData->getRealRFData(k, s[i][k]); // calculate pReal
                pImag += RFData->getImagRFData(k, s[i][k]); // calculation for pImag
            }                                                
        }
        scanline[i] = sqrt(pow(pReal, 2) + pow(pImag, 2)); //calculate echo magnitude of scanline at i'th element
        pReal = 0;
        pImag = 0;
    }
}

void BmodeClass::getScanline(float *data)
{
    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        data[i] = scanline[i];
    }
}

void BmodeClass::deleteScanline()
{
    delete scanline;
}
