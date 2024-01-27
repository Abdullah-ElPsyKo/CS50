#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover [forencic image]\n");
        return 1;
    }

    FILE *fptr = NULL;
    FILE *ptr = NULL;
    fptr = fopen(argv[1], "r");

    if (fptr == NULL)
    {
        printf("Error, could not open the file\n");
        return 1;
    }

    BYTE buffer[512]; //address of the first byte of memory
    char filename[8];
    int count = 0;
    while (fread(buffer, 512, 1, fptr) != 0) //check if end of file is reached
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if (ptr != NULL) //close previous file to prevent memory leak
            {
                fclose(ptr);
            }
            sprintf(filename, "%03d.jpg", count++); //correct string format xxx.jpg
            ptr = fopen(filename, "w");

        }
        if (ptr != NULL)
        {
            fwrite(buffer, 512, 1, ptr);
        }
    }
    //close files
    fclose(ptr);
    fclose(fptr);
}