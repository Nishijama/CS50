#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Ensure proper usage

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    // Open input file
    FILE *card = fopen(argv[1], "r");

    if (!card)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    // initialize a buffer array to store the values from the file
    unsigned char buffer[512];

    // initialize a char array to store the name of new JPEG files
    char JPEGname [10];

    // initialize a variable to store the number of new JPEG files
    int JPEGno = -1;

    FILE *img;
    // Loop through the whole file and read 512 bytes into buffer array
    while (fread(buffer, sizeof(BYTE), 512, card) == 512)
    {
        // if a JPEG header is found
        if (buffer [0] == 0xff &&
            buffer [1] == 0xd8 &&
            buffer [2] == 0xff &&
            (buffer [3] & 0xf0) == 0xe0)
        {
            //Update the number of found JPEGs
            JPEGno++;

            if (JPEGno == 0)
            {
                sprintf(JPEGname, "%03i.jpg", JPEGno);
                printf("%s", JPEGname);
                img = fopen(JPEGname, "w");

                if (img == NULL)
                {
                    fprintf(stderr, "Can't open output file!\n");
                    exit(1);
                }

                fwrite(buffer, sizeof(BYTE), 512, img);
            }
            //If this is not the first found JPEG, close the previous one
            if (JPEGno != 0)
            {
                fclose(img);
                if (img == NULL)
                {
                    fprintf(stderr, "Can't close output file!\n");
                    exit(1);
                }
                sprintf(JPEGname, "%03i.jpg", JPEGno);
                printf("%s", JPEGname);
                img = fopen(JPEGname, "w");

                if (img == NULL)
                {
                    fprintf(stderr, "Can't open output file!\n");
                    exit(1);
                }

                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        }

        // if already found a header, keep writing all data to the currently open file
        else
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    // Close the last JPEG file

    fclose(img);
    if (img == NULL)
    {
        fprintf(stderr, "Can't close output file!\n");
        exit(1);
    }
}