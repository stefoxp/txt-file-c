/**************************************************************/
/* 
    Scopo:      programma per la copia di un file di testo
                all'interno di un altro file di testo
    Argomenti:  nomi del file di input e del file di output
*/
/**************************************************************/

/*****************************/
/* inclusione delle librerie */
/*****************************/

#include <stdio.h>

/****************************************************/
/* definizione di un tipo per l'esito del programma */
/****************************************************/

typedef enum {esito_positivo,
                errore_argomento,         /* mancanza di argomenti richiesti */
                errore_input,             /* in apertura del file di input */
                errore_output,            /* in apertura del file di output */
                errore_scrittura,         /* in scrittura sul file di output */
                errore_lettura} esito_t;  /* in lettura sul file di input */

/********************************/
/* dichiarazione delle funzioni */
/********************************/

esito_t copia_file(char *, 
                   char *);
void informa_utente(esito_t , 
                    char *, 
                    char *, 
                    char *);

/******************************************************/
/* definizione della funzione copia_file

   Scopo:      copia il contenuto del file di testo
               indicato all'interno del file indicato
    Argomenti: nome del programma,
               nome del file di input,
               nome del file di output
*/
/******************************************************/

esito_t copia_file(char *infile_name, 
                   char *outfile_name)
{
    /* dichiarazione delle variabili locali */
    FILE *infile_p,     /* lavoro: puntatore al file di input */
        *outfile_p;     /* lavoro: puntatore al file di output */
    int c,              /* input: carattere alfanumerico */
        contatore;      /* output: nro progressivo di riga */
    esito_t esito;      /* output: valore da restituire all'esterno */
    
    /* inizializzazione */
    contatore = 1;
    /* se viene restituito questo valore significa che l'esecuzione e'
    terminata con successo */
    esito = esito_positivo;
   
    /* apre il file di input in modalita' di lettura: se non esiste informa l'utente */
    if ((infile_p = fopen(infile_name,
                          "r")) != NULL)
    {
        /* apre il file di output in modalita' di scrittura: se non esiste lo crea */
        if ((outfile_p = fopen(outfile_name,
                               "w")) != NULL)
        {
            /* scrive il nome del file di input */
            fprintf(outfile_p,
                    "**********%s.lis**********\n", 
                    infile_name);
            
            /* verifica che il file di input non sia vuoto */
            if (!feof(infile_p))
                fprintf(outfile_p, 
                        "(%d) ", 
                        contatore); /* scrive il nro per la prima riga */
            
            /* scorre il file di input fino alla fine */
            while ((c = fgetc(infile_p)) != EOF)
            {
                
                /* memorizza il carattere letto dal file di input nel file di output */
                fputc(c, 
                      outfile_p);
                
                /* se si tratta di un carattere newline */
                if (c == '\n')
                {
                    /* incrementa il contatore */
                    contatore = contatore + 1;

                    /* aggiunge il numero di riga */
                    fprintf(outfile_p, 
                            "(%d) ", 
                            contatore);
                }
            }
            /* verifica l'eventuale presenza di errori in scrittura sul file di output */
            if (ferror(outfile_p))
                /* restituisce un codice di errore */
                esito = errore_scrittura;
            
            /* chiude il file di output */
            fclose(outfile_p);
        }
         else
        {
            /* il file di output non puo' essere aperto: restituisce un codice di errore */
            esito = errore_output;
        }
        /* verifica l'eventuale presenza di errori in lettura sul file di input */
        if (ferror(infile_p))
            /* restituisce un codice di errore */
            esito = errore_lettura;

        /* chiude il file di input */
        fclose(infile_p);
    }
    else
    {
        /* il file di input non esiste: restituisce un codice di errore */
        esito = errore_input;
    }
    /* restituisce un intero significativo */
    return(esito);
}

void informa_utente(esito_t esito_finale, 
                    char *prg_name, 
                    char *infile_name, 
                    char *outfile_name)
{
    /* verifica che l'esito sia stato positivo */
    if (esito_finale == esito_positivo)
    {
            /* messaggio di conferma per l'utente */
            printf("*******************************************************************************\n");
            printf("%s:\n\tContenuto del file - %s - copiato nel file - %s -\n\tNessun errore rilevato.\n",
                    prg_name,
                    infile_name,
                    outfile_name);
            printf("*******************************************************************************\n");
    }
    else
    {
        /* visualizza il codice identificativo dell'errore */
        fprintf(stderr, 
            "%s:\n\tSi e' verificato un errore durante l'operazione di copia:\n\tCodice errore: %d.\n",
            prg_name,
            esito_finale);
        
        /* visualizza una descrizione specifica per ogni tipo di errore gestito */
        switch (esito_finale)
        {
            
            case errore_argomento:
                /* mancano 1 o pi� argomenti: informa l'utente circa la corretta sintassi da utilizzare */
                fprintf(stderr,
                        "\tE' necessario utilizzare la seguente sintassi: %s infile outfile\n",
                        prg_name);
                break;
            case errore_input:
                /* il file di input non esiste: informa l'utente */
                fprintf(stderr,
                        "\tIl file di input - %s - non esiste o non puo' essere aperto.\n",
                        infile_name);
                break;
            case errore_output:
                /* il file di output non esiste e non puo' essere creato */
                fprintf(stderr,
                        "\tIl file di output - %s - non puo' essere aperto.\n",
                        outfile_name);
                break;
            case errore_scrittura:
                /* scrittura sul file di oputput */
                fprintf(stderr, 
                        "\tErrore in scrittura sul file %s.\n",
                        outfile_name);
                break;
            case errore_lettura:
                /* lettura dal file di input */
                fprintf(stderr, 
                        "\tErrore in lettura sul file %s.\n",
                        infile_name);
                break;
            default:
                /* esito imprevisto */
                fprintf(stderr, 
                        "\tErrore sconosciuto!\n");
                break;
        }
    }
}

/***********************************/
/* definizione della funzione main */
/***********************************/

int main(int argc,
        char *argv[])
{
    /* dichiarazioni */
    esito_t esito;          /* output: valore restituito */
    
    /* inizializzazione */
    /* se viene restituito questo valore significa che l'esecuzione e' terminata con successo */
    esito = esito_positivo;

    /* verifica la presenza di 2 argomenti */
   if (argc != 3)
        /* la sintassi della riga di comando non e' corretta: restituisce un codice di errore */
        esito = errore_argomento;
    else
        /* chiama la funzione che si occupa della copia */
        esito = copia_file(argv[1],
                           argv[2]);
    
    /* visualizza un messaggio informativo a video */
    informa_utente(esito,
                    argv[0],
                    argv[1],
                    argv[2]);
    
    /* restituisce un codice di esito */
    return(esito);
}