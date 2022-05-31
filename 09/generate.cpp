#include <cstdlib>
#include <cstdio>
#include <random>


int main()
{
    FILE * file = fopen64("file.bin", "wb");

    int64_t buffer[1024];

    for (int64_t i = 0; i < 10000000; i++)
    {
        buffer[i % 1024] = random();

        if (i % 1024 == 1023)
        {
            fwrite(buffer, sizeof (int64_t), 1024, file);
            printf("%ld\n", i / 1024);
        }
    }

    fclose(file);
    return 0;
}