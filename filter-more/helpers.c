#include "helpers.h"
#include <stdio.h>
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int averageRgb = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = averageRgb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; //temporary
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][width - j - 1].rgbtRed; // -1 is needed otherwise we will get an out of bound error
            image[i][j].rgbtGreen = temp[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][width - j - 1].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; //temporary
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            float pixels = 0.0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int newHeight = i + k; //get height of all the surrounding pixels
                    int newWidth = j + l; //same for width
                    if (newHeight >= 0 && newHeight < height && newWidth >= 0 && newWidth < width) //check if these pixels actually exist
                    {
                        red += temp[newHeight][newWidth].rgbtRed;
                        green += temp[newHeight][newWidth].rgbtGreen;
                        blue += temp[newHeight][newWidth].rgbtBlue;
                        pixels++;
                    }
                }
            }
            if (pixels != 0.0)
            {
                image[i][j].rgbtRed = round(red / pixels);
                image[i][j].rgbtGreen = round(green / pixels);
                image[i][j].rgbtBlue = round(blue / pixels);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; //temporary
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    int listGx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int listGy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            int Gxred = 0;
            int Gyred = 0;
            int Gxgreen = 0;
            int Gygreen = 0;
            int Gxblue = 0;
            int Gyblue = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int newHeight = i + k; //get height of all the surrounding pixels
                    int newWidth = j + l; //same for width
                    if (newHeight >= 0 && newHeight < height && newWidth >= 0 && newWidth < width) //check if these pixels actually exist
                    {
                        Gxred += (temp[newHeight][newWidth].rgbtRed) * listGx[k + 1][l + 1];
                        Gyred += (temp[newHeight][newWidth].rgbtRed) * listGy[k + 1][l + 1];

                        red = round(sqrt((pow(Gxred, 2)) + (pow(Gyred, 2))));

                        if (red > 255) //valid check
                        {
                            red = 255;
                        }

                        Gxgreen += (temp[newHeight][newWidth].rgbtGreen) * listGx[k + 1][l + 1];
                        Gygreen += (temp[newHeight][newWidth].rgbtGreen) * listGy[k + 1][l + 1];

                        green = round(sqrt((pow(Gxgreen, 2)) + (pow(Gygreen, 2))));

                        if (green > 255) //valid check
                        {
                            green = 255;
                        }

                        Gxblue += (temp[newHeight][newWidth].rgbtBlue) * listGx[k + 1][l + 1];
                        Gyblue += (temp[newHeight][newWidth].rgbtBlue) * listGy[k + 1][l + 1];

                        blue = round(sqrt((pow(Gxblue, 2)) + (pow(Gyblue, 2))));

                        if (blue > 255) //valid check
                        {
                            blue = 255;
                        }
                    }
                }
            }
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}
