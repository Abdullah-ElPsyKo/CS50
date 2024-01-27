#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++) //itterate through the height
    {
        for (int j = 0; j < width; j++) //itterate through the width
        {
            if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00)
            {
                //change color to Azure in my case
                image[i][j].rgbtRed = 0xf0;
                image[i][j].rgbtGreen = 0xff;
                image[i][j].rgbtBlue = 0xff;
            }
        }
    }
}
