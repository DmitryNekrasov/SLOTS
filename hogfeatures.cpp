#include "hogfeatures.h"

#include <QDebug>

#define NUM_SECTOR 9
#define PI 3.1415926535

void allocHogFeatures(HogFeatures** obj, const int size_x,
                      const int size_y, const int features_number) {
    (*obj) = (HogFeatures*) malloc(sizeof(HogFeatures));
    (*obj)->size_x = size_x;
    (*obj)->size_y = size_y;
    (*obj)->features_number = features_number;
    (*obj)->map = (float*) malloc(sizeof (float) * (size_x * size_y  * features_number));
    for (int i = 0; i < size_x * size_y * features_number; i++) {
        (*obj)->map[i] = 0.0f;
    }
}

void freeHogFeatures(HogFeatures** obj) {
    if(*obj == NULL) {
        return;
    }
    free((*obj)->map);
    free(*obj);
    (*obj) = NULL;
}

void getHogFeatures(const IplImage* image, int k, HogFeatures** hogFeatures) {
    int sizeX, sizeY;
    int p, px, stringSize;
    int height, width, numChannels;
    int i, j, kk, c, ii, jj, d;
    float  * datadx, * datady;

    int   ch;
    float magnitude, x, y, tx, ty;

    IplImage * dx, * dy;
    int *nearest;
    float *w, a_x, b_x;

    float kernel[3] = {-1.f, 0.f, 1.f};
    CvMat kernel_dx = cvMat(1, 3, CV_32F, kernel);
    CvMat kernel_dy = cvMat(3, 1, CV_32F, kernel);

    float * r;
    int   * alfa;

    float boundary_x[NUM_SECTOR + 1];
    float boundary_y[NUM_SECTOR + 1];
    float max, dotProd;
    int   maxi;

    height = image->height;
    width  = image->width ;

    numChannels = image->nChannels;

    dx    = cvCreateImage(cvSize(image->width, image->height),
                          IPL_DEPTH_32F, 3);
    dy    = cvCreateImage(cvSize(image->width, image->height),
                          IPL_DEPTH_32F, 3);

    sizeX = width  / k;
    sizeY = height / k;
    px    = 3 * NUM_SECTOR;
    p     = px;
    stringSize = sizeX * p;
    allocHogFeatures(hogFeatures, sizeX, sizeY, p);

    cvFilter2D(image, dx, &kernel_dx, cvPoint(-1, 0));
    cvFilter2D(image, dy, &kernel_dy, cvPoint(0, -1));

    float arg_vector;
    for(i = 0; i <= NUM_SECTOR; i++)
    {
        arg_vector    = ( (float) i ) * ( (float)(PI) / (float)(NUM_SECTOR) );
        boundary_x[i] = cosf(arg_vector);
        boundary_y[i] = sinf(arg_vector);
    }/*for(i = 0; i <= NUM_SECTOR; i++) */

    r    = (float *)malloc( sizeof(float) * (width * height));
    alfa = (int   *)malloc( sizeof(int  ) * (width * height * 2));

    for(j = 1; j < height - 1; j++)
    {
        datadx = (float*)(dx->imageData + dx->widthStep * j);
        datady = (float*)(dy->imageData + dy->widthStep * j);
        for(i = 1; i < width - 1; i++)
        {
            c = 0;
            x = (datadx[i * numChannels + c]);
            y = (datady[i * numChannels + c]);

            r[j * width + i] =sqrtf(x * x + y * y);
            for(ch = 1; ch < numChannels; ch++)
            {
                tx = (datadx[i * numChannels + ch]);
                ty = (datady[i * numChannels + ch]);
                magnitude = sqrtf(tx * tx + ty * ty);
                if(magnitude > r[j * width + i])
                {
                    r[j * width + i] = magnitude;
                    c = ch;
                    x = tx;
                    y = ty;
                }
            }/*for(ch = 1; ch < numChannels; ch++)*/

            max  = boundary_x[0] * x + boundary_y[0] * y;
            maxi = 0;
            for (kk = 0; kk < NUM_SECTOR; kk++)
            {
                dotProd = boundary_x[kk] * x + boundary_y[kk] * y;
                if (dotProd > max)
                {
                    max  = dotProd;
                    maxi = kk;
                }
                else
                {
                    if (-dotProd > max)
                    {
                        max  = -dotProd;
                        maxi = kk + NUM_SECTOR;
                    }
                }
            }
            alfa[j * width * 2 + i * 2    ] = maxi % NUM_SECTOR;
            alfa[j * width * 2 + i * 2 + 1] = maxi;
        }/*for(i = 0; i < width; i++)*/
    }/*for(j = 0; j < height; j++)*/

    nearest = (int  *)malloc(sizeof(int  ) *  k);
    w       = (float*)malloc(sizeof(float) * (k * 2));

    for(i = 0; i < k / 2; i++)
    {
        nearest[i] = -1;
    }/*for(i = 0; i < k / 2; i++)*/
    for(i = k / 2; i < k; i++)
    {
        nearest[i] = 1;
    }/*for(i = k / 2; i < k; i++)*/

    for(j = 0; j < k / 2; j++)
    {
        b_x = k / 2 + j + 0.5f;
        a_x = k / 2 - j - 0.5f;
        w[j * 2    ] = 1.0f/a_x * ((a_x * b_x) / ( a_x + b_x));
        w[j * 2 + 1] = 1.0f/b_x * ((a_x * b_x) / ( a_x + b_x));
    }/*for(j = 0; j < k / 2; j++)*/
    for(j = k / 2; j < k; j++)
    {
        a_x = j - k / 2 + 0.5f;
        b_x =-j + k / 2 - 0.5f + k;
        w[j * 2    ] = 1.0f/a_x * ((a_x * b_x) / ( a_x + b_x));
        w[j * 2 + 1] = 1.0f/b_x * ((a_x * b_x) / ( a_x + b_x));
    }/*for(j = k / 2; j < k; j++)*/

    for(i = 0; i < sizeY; i++)
    {
      for(j = 0; j < sizeX; j++)
      {
        for(ii = 0; ii < k; ii++)
        {
          for(jj = 0; jj < k; jj++)
          {
            if ((i * k + ii > 0) &&
                (i * k + ii < height - 1) &&
                (j * k + jj > 0) &&
                (j * k + jj < width  - 1))
            {
              d = (k * i + ii) * width + (j * k + jj);
              (*hogFeatures)->map[ i * stringSize + j * (*hogFeatures)->features_number + alfa[d * 2    ]] +=
                  r[d] * w[ii * 2] * w[jj * 2];
              (*hogFeatures)->map[ i * stringSize + j * (*hogFeatures)->features_number + alfa[d * 2 + 1] + NUM_SECTOR] +=
                  r[d] * w[ii * 2] * w[jj * 2];
              if ((i + nearest[ii] >= 0) &&
                  (i + nearest[ii] <= sizeY - 1))
              {
                (*hogFeatures)->map[(i + nearest[ii]) * stringSize + j * (*hogFeatures)->features_number + alfa[d * 2    ]             ] +=
                  r[d] * w[ii * 2 + 1] * w[jj * 2 ];
                (*hogFeatures)->map[(i + nearest[ii]) * stringSize + j * (*hogFeatures)->features_number + alfa[d * 2 + 1] + NUM_SECTOR] +=
                  r[d] * w[ii * 2 + 1] * w[jj * 2 ];
              }
              if ((j + nearest[jj] >= 0) &&
                  (j + nearest[jj] <= sizeX - 1))
              {
                (*hogFeatures)->map[i * stringSize + (j + nearest[jj]) * (*hogFeatures)->features_number + alfa[d * 2    ]             ] +=
                  r[d] * w[ii * 2] * w[jj * 2 + 1];
                (*hogFeatures)->map[i * stringSize + (j + nearest[jj]) * (*hogFeatures)->features_number + alfa[d * 2 + 1] + NUM_SECTOR] +=
                  r[d] * w[ii * 2] * w[jj * 2 + 1];
              }
              if ((i + nearest[ii] >= 0) &&
                  (i + nearest[ii] <= sizeY - 1) &&
                  (j + nearest[jj] >= 0) &&
                  (j + nearest[jj] <= sizeX - 1))
              {
                (*hogFeatures)->map[(i + nearest[ii]) * stringSize + (j + nearest[jj]) * (*hogFeatures)->features_number + alfa[d * 2    ]             ] +=
                  r[d] * w[ii * 2 + 1] * w[jj * 2 + 1];
                (*hogFeatures)->map[(i + nearest[ii]) * stringSize + (j + nearest[jj]) * (*hogFeatures)->features_number + alfa[d * 2 + 1] + NUM_SECTOR] +=
                  r[d] * w[ii * 2 + 1] * w[jj * 2 + 1];
              }
            }
          }/*for(jj = 0; jj < k; jj++)*/
        }/*for(ii = 0; ii < k; ii++)*/
      }/*for(j = 1; j < sizeX - 1; j++)*/
    }/*for(i = 1; i < sizeY - 1; i++)*/

    cvReleaseImage(&dx);
    cvReleaseImage(&dy);


    free(w);
    free(nearest);

    free(r);
    free(alfa);

    qDebug() << "Correct!" << "\n";
}
