#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float mean = (float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            image[i][j].rgbtRed = round(mean);
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

    //calulate sepia values for each color
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((float)(.393 * original[i][j].rgbtRed + .769 * original[i][j].rgbtGreen + .189 * original[i][j].rgbtBlue) > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(.393 * original[i][j].rgbtRed + .769 * original[i][j].rgbtGreen + .189 * original[i][j].rgbtBlue);
            }

            if ((float)(.349 * original[i][j].rgbtRed + .686 * original[i][j].rgbtGreen + .168 * original[i][j].rgbtBlue) > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(.349 * original[i][j].rgbtRed + .686 * original[i][j].rgbtGreen + .168 * original[i][j].rgbtBlue);
            }

            if ((float)(.272 * original[i][j].rgbtRed + .534 * original[i][j].rgbtGreen + .131 * original[i][j].rgbtBlue) > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(.272 * original[i][j].rgbtRed + .534 * original[i][j].rgbtGreen + .131 * original[i][j].rgbtBlue);
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //create a temporary struct
    RGBTRIPLE temp[height][width];

    //copy the image into the temporary struct
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //copyt the RHS to the LHS
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {

            image[i][j].rgbtRed = image[i][(width - 1) - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][(width - 1) - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][(width - 1) - j].rgbtBlue;
        }
    }

    //copy the LHS provided there is an odd number of pixels
    if (width % 2 != 0)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = width / 2, k = width / 2; j < width; j++, k--)
            {

                image[i][j].rgbtRed = temp[i][k].rgbtRed;
                image[i][j].rgbtGreen = temp[i][k].rgbtGreen;
                image[i][j].rgbtBlue = temp[i][k].rgbtBlue;

            }
        }
    }

    //copy the LHS provided there is an even number of pixels
    else
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = width / 2, k = (width / 2) - 1; j < width; j++, k--)
            {

                image[i][j].rgbtRed = temp[i][k].rgbtRed;
                image[i][j].rgbtGreen = temp[i][k].rgbtGreen;
                image[i][j].rgbtBlue = temp[i][k].rgbtBlue;

            }
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
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


    //No ile tych komentarzy!
    //Na prawde, ten program nie jest az tak skomplikowany
    //wiec juz na prawde dajcie spokoj
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //top row

            if (i == 0)
            {
                if (j == 0)
                {
                    image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j].rgbtRed +
                                                        original[i + 1][j + 1].rgbtRed) / 4);
                    image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j].rgbtGreen +
                                                          original[i + 1][j + 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j].rgbtBlue +
                                                         original[i + 1][j + 1].rgbtBlue) / 4);
                }
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i + 1][j].rgbtRed +
                                                        original[i + 1][j - 1].rgbtRed) / 4);
                    image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i + 1][j].rgbtGreen +
                                                          original[i + 1][j - 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i + 1][j].rgbtBlue +
                                                         original[i + 1][j - 1].rgbtBlue) / 4);
                }
                else
                {
                    image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i + 1][j].rgbtRed +
                                                        original[i + 1][j - 1].rgbtRed + original[i + 1][j + 1].rgbtRed + original[i][j + 1].rgbtRed) / 6);
                    image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i + 1][j].rgbtGreen +
                                                          original[i + 1][j - 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen + original[i][j + 1].rgbtGreen) / 6);
                    image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i + 1][j].rgbtBlue +
                                                         original[i + 1][j - 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue + original[i][j + 1].rgbtBlue) / 6);
                }
            }

            //bottom row

            else if (i == height - 1)
            {
                if (j == 0)
                {
                    image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i][j + 1].rgbtRed + original[i - 1][j].rgbtRed +
                                                        original[i - 1][j + 1].rgbtRed) / 4);
                    image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i - 1][j].rgbtGreen +
                                                          original[i - 1][j + 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i - 1][j].rgbtBlue +
                                                         original[i - 1][j + 1].rgbtBlue) / 4);
                }
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i - 1][j].rgbtRed +
                                                        original[i - 1][j - 1].rgbtRed) / 4);
                    image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen +
                                                          original[i - 1][j - 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue +
                                                         original[i - 1][j - 1].rgbtBlue) / 4);
                }
                else
                {
                    image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i - 1][j].rgbtRed +
                                                        original[i - 1][j - 1].rgbtRed + original[i - 1][j + 1].rgbtRed + original[i][j + 1].rgbtRed) / 6);
                    image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen +
                                                          original[i - 1][j - 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen + original[i][j + 1].rgbtGreen) / 6);
                    image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue +
                                                         original[i - 1][j - 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue + original[i][j + 1].rgbtBlue) / 6);
                }
            }

            // first column

            else if (j == 0)
            {
                if (i == 0)
                {
                    continue;
                }
                else if (i == height - 1)
                {
                    continue;
                }
                else
                {
                    image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j].rgbtRed +
                                                        original[i + 1][j + 1].rgbtRed + original[i - 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed) / 6);
                    image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j].rgbtGreen +
                                                          original[i + 1][j + 1].rgbtGreen + original[i - 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen) / 6);
                    image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j].rgbtBlue +
                                                         original[i + 1][j + 1].rgbtBlue + original[i - 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue) / 6);
                }
            }

            // last column

            else if (j == width - 1)
            {
                if (i == 0)
                {
                    continue;
                }
                else if (i == height - 1)
                {
                    continue;
                }
                else
                {
                    image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i + 1][j].rgbtRed +
                                                        original[i + 1][j - 1].rgbtRed + original[i - 1][j].rgbtRed + original[i - 1][j - 1].rgbtRed) / 6);
                    image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i + 1][j].rgbtGreen +
                                                          original[i + 1][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen + original[i - 1][j - 1].rgbtGreen) / 6);
                    image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i + 1][j].rgbtBlue +
                                                         original[i + 1][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue + original[i - 1][j - 1].rgbtBlue) / 6);
                }
            }

            //For everything else

            else
            {
                image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i][j + 1].rgbtRed +
                                                    original[i - 1][j - 1].rgbtRed + original[i - 1][j + 1].rgbtRed + original[i - 1][j].rgbtRed + original[i + 1][j - 1].rgbtRed +
                                                    original[i + 1][j + 1].rgbtRed + original[i + 1][j].rgbtRed) / 9);
                image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i][j + 1].rgbtGreen +
                                                      original[i - 1][j - 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen + original[i - 1][j].rgbtGreen +
                                                      original[i + 1][j - 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen + original[i + 1][j].rgbtGreen) / 9);
                image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i][j + 1].rgbtBlue +
                                                     original[i - 1][j - 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue + original[i - 1][j].rgbtBlue +
                                                     original[i + 1][j - 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue + original[i + 1][j].rgbtBlue) / 9);
            }
        }
    }
    return;
}

