#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    const int BLOCK_SIZE = 512;
    //Check usage
    if (argc  != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //Open file
    FILE *raw_file = fopen(argv[1], "r");
    if (!raw_file)
    {
        printf("Cannot find that file\n");
        return 1;
    }

    //buffer for file's name

    char *new_img = malloc(8 * sizeof(char)); //###.jpg 8 char including Nul
    while (new_img == NULL)
    {
        new_img = malloc(8 * sizeof(char)); //###.jpg 8 char including Nul
    }

    BYTE buffer[512];
    int count = 0;
    //Create new file
    FILE *recovered_img;
    while (fread(&buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xff) == 0xe0)
        {
            if (count == 0)
            {
                sprintf(new_img, "%03i.jpg", count);

                //Open recovered_file
                recovered_img = fopen(new_img, "w");
                fwrite(&buffer, 1, BLOCK_SIZE, recovered_img);
                count++;
            }
            else
            {
                fclose(recovered_img);
                sprintf(new_img, "%03i.jpg", count);
                //Open recovered_file
                recovered_img = fopen(new_img, "w");
                fwrite(&buffer, 1, BLOCK_SIZE, recovered_img);
                count++;
            }
        }
        else
        {
            if (count > 0)
            {
                fwrite(&buffer, 1, BLOCK_SIZE, recovered_img);
            }
        }
    }
    fclose(raw_file);
    fclose(recovered_img);
    free(new_img);
    return 0;
}