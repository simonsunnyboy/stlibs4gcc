#include <osbind.h>

int main(int argc, char *argv[]) 
{
    int nr = 0;

    (void)Cconws("\033E");
    (void)Cconws("Test .ttp got parameters:\n\r");

    while(argc > 0)
    {
        (void)Cconws(argv[nr]);
        (void)Cconws("\n\r");
        nr++;
        argc--;
    }

    (void)Cconws("---------------------------------------\n\rpress ENTER\n\r");

    Cconin();

    return 0;
}
