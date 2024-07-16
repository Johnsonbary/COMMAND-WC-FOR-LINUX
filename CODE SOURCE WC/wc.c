#include "wc.h"

void option(int argc, char *argv[])
{
    int i = 1;
    nouveau:
        if(argc <= 1)
        {
            printf("Consultez WC --help\n");
            exit(0);
        }
        if(i < argc)
        {
            if(strcmp(argv[i], "--help") == 0)
            {
                option_help();
                exit(0);
            }
            if(strcmp(argv[i], "--version") == 0)
            {
                option_version();
                exit(0);
            }
            if(strcmp(argv[i], "-c" ) == 0 || strcmp(argv[i], "--bytes") == 0)
            {
                option_bytes(argv[argc - 1]);
                printf("%s\n", argv[argc - 1]);
                i++;
                goto nouveau;
            }
            if(strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--chars") == 0)
            {
                option_chars(argv[argc - 1]);
                printf("%s\n", argv[argc - 1]);
                i++;
                goto nouveau;
            }
            if(strcmp(argv[i], "-L" ) == 0 || strcmp(argv[i], "--max-line-length") == 0)
            {
                option_L(argv[argc - 1]);
                printf("%s\n", argv[argc - 1]);
                i++;
                goto nouveau;
            }
            if(strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--word") == 0)
            {
                option_word(argv[argc - 1]);
                printf("%s\n", argv[argc - 1]);
                i++;
                goto nouveau;
            }
            if(strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "-lines") == 0)
            {
                    option_l(argv[argc - 1]);
                printf("%s\n", argv[argc - 1]);
                i++;
                goto nouveau;
            }
            else
            {
                option_sans(argv, i);
                i++;
                goto nouveau;
            }
        }
    }
void detruire(FILE *fichier)
{
    if(fichier != NULL)
    {
        fclose(fichier);
    }
}
void option_help()
{
    system("cat help");
    exit(0);
}
void option_version()
{
    system("cat version");
    exit(0);
}
void option_bytes(char argv[100])
{
    FILE *fichier = NULL;
    char mot;
    int count = 0;
    fichier = ouverture(argv);
    while(!feof(fichier))
    {
        mot = fgetc(fichier);
        if(mot != EOF)
            count++;
    }
    printf("%d ", count);
    detruire(fichier);
}
void option_chars(char argv[100])
{
    FILE *fichier = NULL;
    char mot;
    int count = 0;
    fichier = ouverture(argv);
    while(!feof(fichier))
    {
        mot = fgetc(fichier);
        if((mot & 0xC0) != 0x80 && mot != EOF)
        {
            count++;
        }
    }
    printf("%d ", count);
    detruire(fichier);
}
void option_L(char argv[100])
{
    FILE *fichier = NULL;
    int count = -1;
    int nouveau = 0;
    char mot;
    fichier = ouverture(argv);
    while(!feof(fichier))
    {
        mot = fgetc(fichier);
        if((mot & 0xC0) != 0x80)
        {
            count++;
        }
        if(nouveau <= count)
            nouveau = count;
        if(mot == '\n')
        {
            count = 0;
        }
    }
    printf("%d ", nouveau);
    detruire(fichier);
}
void option_word(char argv[100])
{
    FILE *fichier = NULL;
    int count = 0;
    char mot[200];
    fichier = ouverture(argv);
    while(!feof(fichier))
    {
        fscanf(fichier, "%s", mot);
        count++;
    }    
    printf("%d ", count);
    detruire(fichier);
}
void option_sans(char *argv[], int nombre)
{
    option_l(argv[nombre]);
    option_word(argv[nombre]);
    option_bytes(argv[nombre]);
    printf("%s\n", argv[nombre]);
}
void option_l(char argv[100])
{
    FILE *fichier = NULL;
    int count = -1;
    char mot[200];
    fichier = ouverture(argv);
    while(!feof(fichier))
    {
        fgets(mot, 200, fichier);
        count++;
    }
    printf("%d ", count);
}
FILE *ouverture(char argv[100])
{
    FILE *fichier = NULL;
    fichier = fopen(argv, "r+");
    if(fichier == NULL)
    {
        printf("Consultez WC --help\n");
        exit(0);
    }
    return (fichier);
}