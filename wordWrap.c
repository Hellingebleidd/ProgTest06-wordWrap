#ifndef __PROGTEST__
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "wordWrap.h"
#endif /* __PROGTEST__ */

char *wordWrap(int width, const char *src) {
    char *vystup, *tmpVystup, *slovo, *tmpSlovo;
    char *tmpSrc;
    int odsek = 0, moznoOdsek = 0;  /*default FALSE*/
    int dlzkaRiadku = 0, dlzkaSlova, i;

    if (strlen(src) == 0) {
        /*prazdny retazec*/
        vystup= (char *) malloc(sizeof(char));
        *vystup=0;
        return vystup;
    }

    /*init*/
    tmpSrc = (char *) src;
    vystup = (char *) malloc((strlen(src) + 1)* sizeof(char)); /*pre istotu +1, ak by vstup nemal \n*/
    tmpVystup = vystup;
    slovo = (char *) malloc(((size_t) width + 1) * sizeof(char)); /*jedno slovo nemoze byt dlhsie ako riadok*/
    tmpSlovo = slovo;   /*nastavim smernik na zaciatok*/
    dlzkaSlova = 0;

    do {
        if (dlzkaSlova > 0 && (*tmpSrc == ' ' || *tmpSrc == '\t' || *tmpSrc == '\n' || *tmpSrc == 0)) {
            /*koniec slova, pridat na koniec riadku*/
            if (dlzkaRiadku > 0) {
                *tmpVystup++ = ' ';
                dlzkaRiadku++;
            }
            tmpSlovo = slovo;
            for (i = 0; i < dlzkaSlova; ++i)   /*pridam slovo na koniec */
                *tmpVystup++ = *tmpSlovo++;
            dlzkaRiadku += dlzkaSlova;
            dlzkaSlova = 0;
            tmpSlovo = slovo; /*nastavim smernik na zaciatok*/
            if (*tmpSrc == '\n')
                moznoOdsek = 1;

        } else if (*tmpSrc != ' ' && *tmpSrc != '\t' && *tmpSrc != '\n' && *tmpSrc != 0) {
            /*pridavam pismekna slova*/
            if (moznoOdsek) moznoOdsek = 0;
            if (odsek) {
                *tmpVystup++ = '\n'; /*treba zariadkovat vystup 2x */
                *tmpVystup++ = '\n';
                dlzkaRiadku = 0;
                odsek = 0;
            }
            if (++dlzkaSlova > width) {     /*koniec s chybou*/
                free(vystup);
                free(slovo);
                return NULL;
            }
            *tmpSlovo++ = *tmpSrc;

            if (1 + dlzkaSlova + dlzkaRiadku > width && dlzkaRiadku>0) {
                *tmpVystup++ = '\n'; /*treba zariadkovat vystup*/
                dlzkaRiadku = 0;
            }

        } else if (moznoOdsek && *tmpSrc == '\n') {
            odsek = 1;  /*odsek*/

        } else {
            if (*tmpSrc == '\n' && tmpVystup!=vystup)
                /*ignoruj odseky na zaciatku textu*/
                moznoOdsek = 1;
            else
                moznoOdsek = 0;
        }

    } while (*tmpSrc++ != 0);    /*kym nieje koniec*/
    if (*(tmpVystup-1)!='\n')
        *tmpVystup++ = '\n'; /*treba zariadkovat vystup*/
    *tmpVystup=0;
    free(slovo);
    return vystup;
}