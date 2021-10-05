#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
       for (int j = 0; j < width; j++)
       {
            image[i][j].rgbtRed = round(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3;
            image[i][j].rgbtGreen = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][j].rgbtRed;
       }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

// declare array or struct (not sure)
RGBTRIPLE original[height][width];

for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
        original[i][j].rgbtRed = image[i][j].rgbtRed;
        original[i][j].rgbtGreen = image[i][j].rgbtGreen;
        original[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }


for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((.393 * original[i][j].rgbtRed + .769 * original[i][j].rgbtGreen + .189 * original[i][j].rgbtBlue) > 255)
                    image[i][j].rgbtRed = 255;
            else
                image[i][j].rgbtRed = round(.393 * original[i][j].rgbtRed + .769 * original[i][j].rgbtGreen + .189 * original[i][j].rgbtBlue);

            if ((.349 * original[i][j].rgbtRed + .686 * original[i][j].rgbtGreen + .168 * original[i][j].rgbtBlue) > 255)
                    image[i][j].rgbtGreen = 255;
            else
                image[i][j].rgbtGreen = round(.349 * original[i][j].rgbtRed + .686 * original[i][j].rgbtGreen + .168 * original[i][j].rgbtBlue);

            if ((.272 * original[i][j].rgbtRed + .534 * original[i][j].rgbtGreen + .131 * original[i][j].rgbtBlue) > 255)
                    image[i][j].rgbtBlue = 255;
            else
                    image[i][j].rgbtBlue = round(.272 * original[i][j].rgbtRed + .534 * original[i][j].rgbtGreen + .131 * original[i][j].rgbtBlue);
       }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width-j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width-j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width-j].rgbtBlue;

            image[i][width-i].rgbtRed = temp[i][j].rgbtRed;
            image[i][width-i].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][width-i].rgbtBlue = temp[i][j].rgbtBlue;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

