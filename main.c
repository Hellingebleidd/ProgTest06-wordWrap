#ifndef __PROGTEST__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#endif /* __PROGTEST__ */

char *wordWrap(int width, const char *src) {
    char *vystup, *tmpVystup, *slovo, *tmpSlovo;
    char *tmpSrc;
    int odsek = 0, moznoOdsek = 0;  /*default FALSE*/
    int dlzkaRiadku = 0, dlzkaSlova, i;

    if (strlen(src) == 0)   /*prazdny retazec*/
        return calloc(1, sizeof(char));
    /*init*/
    tmpSrc = (char *) src;
    vystup = (char *) calloc(strlen(src) + 1, sizeof(char)); /*pre istotu +1, ak by vstup nemal \n*/
    tmpVystup = vystup;
    slovo = (char *) calloc((size_t) width + 1, sizeof(char)); /*jedno slovo nemoze byt dlhsie ako riadok*/
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

        } else if (*tmpSrc != ' ' && *tmpSrc != '\t' && *tmpSrc != '\n') {
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

            if (1 + dlzkaSlova + dlzkaRiadku > width) {
                *tmpVystup++ = '\n'; /*treba zariadkovat vystup*/
                dlzkaRiadku = 0;
            }

        } else if (moznoOdsek && *tmpSrc == '\n') {
            odsek = 1;  /*odsek*/

        } else {
            if (*tmpSrc == '\n') moznoOdsek = 1; else moznoOdsek = 0;
        }

    } while (*tmpSrc++ != 0);    /*kym nieje koniec*/
    if (dlzkaRiadku > 0)
        *tmpVystup++ = '\n'; /*treba zariadkovat vystup*/

    free(slovo);
    return vystup;
}

#ifndef __PROGTEST__
int                main                                     ( void )
{
    char * res;
    const char * s0 =
            "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus\n"
            "pede, pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat\n"
            "orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus\n"
            "lectus, vitae feugiat purus orci ultricies turpis. Pellentesque habitant\n"
            "morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nam\n"
            "in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor\n"
            "ultrices neque. Mauris semper, mauris ut feugiat ultricies, augue purus\n"
            "tincidunt  elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
            "pretium, augue non cursus pretium, nibh dolor laoreet leo, sed pharetra pede\n"
            "libero non diam.";
    const char * s1 =
            "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus\n"
            "pede, pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat\n"
            "orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus\n"
            "lectus, vitae feugiat purus orci ultricies turpis. Pellentesque habitant\n"
            "morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nam\n"
            "in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor\n"
            "ultrices neque. Mauris semper, mauris ut feugiat ultricies, augue purus\n"
            "tincidunt  elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
            "pretium, augue non cursus pretium, nibh\tdolor laoreet leo, sed pharetra pede\n"
            "libero non diam.\n"
            "\n"
            "Proin est nisi,                     gravida ac, vulputate id, fringilla sit\n"
            "amet, magna. Nam congue cursus magna. In malesuada, velit a gravida sodales,\n"
            "dolor nisl vestibulum orci, sit amet sagittis mauris tellus nec purus. Nulla\n"
            "eget risus. Quisque nec sapien blandit odio convallis ullamcorper. Lorem\n"
            "ipsum dolor sit amet, consectetuer adipiscing elit. Pellentesque cursus.\n"
            "Aliquam tempus neque vitae libero molestie ut auctor.\n"
            "\n"
            "\n"
            "\n"
            "In nec massa eu tortor vulputate suscipit.\tNam tristique magna nec pede. Sed\n"
            "a nisi. Nulla sed augue ut risus placerat porttitor. Ut aliquam. Nulla\n"
            "facilisi. Nulla vehicula nibh ac sapien. Nunc facilisis dapibus ipsum. Donec\n"
            "sed mauris. Nulla quam nisi, laoreet non, dignissim posuere, lacinia nec,\n"
            "turpis. Mauris malesuada nisi sed enim. In hac habitasse platea dictumst.\n"
            "Fusce    faucibus, turpis nec auctor posuere, nulla tellus scelerisque metus,\n"
            "quis molestie mi dui id quam. Mauris vestibulum. Nam ullamcorper.\n"
            "\n";
    printf("\n glupocina\n");

    res = wordWrap ( 40, s0 );
    assert ( ! strcmp ( res,
                        "Lorem ipsum dolor sit amet, consectetuer\n"
                        "adipiscing elit. Integer metus pede,\n"
                        "pretium vitae, rhoncus et, auctor sit\n"
                        "amet, ligula. Integer volutpat orci et\n"
                        "elit. Nunc tempus, urna at sollicitudin\n"
                        "rutrum, arcu libero rhoncus lectus,\n"
                        "vitae feugiat purus orci ultricies\n"
                        "turpis. Pellentesque habitant morbi\n"
                        "tristique senectus et netus et malesuada\n"
                        "fames ac turpis egestas. Nam in pede.\n"
                        "Etiam eu sem id urna ultricies congue.\n"
                        "Vestibulum porttitor ultrices neque.\n"
                        "Mauris semper, mauris ut feugiat\n"
                        "ultricies, augue purus tincidunt elit,\n"
                        "eu interdum ante nisl ac ante.\n"
                        "Pellentesque dui. Vestibulum pretium,\n"
                        "augue non cursus pretium, nibh dolor\n"
                        "laoreet leo, sed pharetra pede libero\n"
                        "non diam.\n" ) );
    free ( res );

    res = wordWrap ( 120, s0 );
    assert ( ! strcmp ( res,
                        "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus pede, pretium vitae, rhoncus et, auctor sit\n"
                        "amet, ligula. Integer volutpat orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus lectus, vitae\n"
                        "feugiat purus orci ultricies turpis. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac\n"
                        "turpis egestas. Nam in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor ultrices neque. Mauris semper,\n"
                        "mauris ut feugiat ultricies, augue purus tincidunt elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
                        "pretium, augue non cursus pretium, nibh dolor laoreet leo, sed pharetra pede libero non diam.\n" ) );
    free ( res );

    res = wordWrap ( 10, s1 );
    assert ( res == NULL );

    res = wordWrap ( 40, s1 );
    assert ( ! strcmp ( res,
                        "Lorem ipsum dolor sit amet, consectetuer\n"
                        "adipiscing elit. Integer metus pede,\n"
                        "pretium vitae, rhoncus et, auctor sit\n"
                        "amet, ligula. Integer volutpat orci et\n"
                        "elit. Nunc tempus, urna at sollicitudin\n"
                        "rutrum, arcu libero rhoncus lectus,\n"
                        "vitae feugiat purus orci ultricies\n"
                        "turpis. Pellentesque habitant morbi\n"
                        "tristique senectus et netus et malesuada\n"
                        "fames ac turpis egestas. Nam in pede.\n"
                        "Etiam eu sem id urna ultricies congue.\n"
                        "Vestibulum porttitor ultrices neque.\n"
                        "Mauris semper, mauris ut feugiat\n"
                        "ultricies, augue purus tincidunt elit,\n"
                        "eu interdum ante nisl ac ante.\n"
                        "Pellentesque dui. Vestibulum pretium,\n"
                        "augue non cursus pretium, nibh dolor\n"
                        "laoreet leo, sed pharetra pede libero\n"
                        "non diam.\n"
                        "\n"
                        "Proin est nisi, gravida ac, vulputate\n"
                        "id, fringilla sit amet, magna. Nam\n"
                        "congue cursus magna. In malesuada, velit\n"
                        "a gravida sodales, dolor nisl vestibulum\n"
                        "orci, sit amet sagittis mauris tellus\n"
                        "nec purus. Nulla eget risus. Quisque nec\n"
                        "sapien blandit odio convallis\n"
                        "ullamcorper. Lorem ipsum dolor sit amet,\n"
                        "consectetuer adipiscing elit.\n"
                        "Pellentesque cursus. Aliquam tempus\n"
                        "neque vitae libero molestie ut auctor.\n"
                        "\n"
                        "In nec massa eu tortor vulputate\n"
                        "suscipit. Nam tristique magna nec pede.\n"
                        "Sed a nisi. Nulla sed augue ut risus\n"
                        "placerat porttitor. Ut aliquam. Nulla\n"
                        "facilisi. Nulla vehicula nibh ac sapien.\n"
                        "Nunc facilisis dapibus ipsum. Donec sed\n"
                        "mauris. Nulla quam nisi, laoreet non,\n"
                        "dignissim posuere, lacinia nec, turpis.\n"
                        "Mauris malesuada nisi sed enim. In hac\n"
                        "habitasse platea dictumst. Fusce\n"
                        "faucibus, turpis nec auctor posuere,\n"
                        "nulla tellus scelerisque metus, quis\n"
                        "molestie mi dui id quam. Mauris\n"
                        "vestibulum. Nam ullamcorper.\n" ) );
    free ( res );

    res = wordWrap ( 80, s1 );
    assert ( ! strcmp ( res,
                        "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus pede,\n"
                        "pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat orci et\n"
                        "elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus lectus,\n"
                        "vitae feugiat purus orci ultricies turpis. Pellentesque habitant morbi tristique\n"
                        "senectus et netus et malesuada fames ac turpis egestas. Nam in pede. Etiam eu\n"
                        "sem id urna ultricies congue. Vestibulum porttitor ultrices neque. Mauris\n"
                        "semper, mauris ut feugiat ultricies, augue purus tincidunt elit, eu interdum\n"
                        "ante nisl ac ante. Pellentesque dui. Vestibulum pretium, augue non cursus\n"
                        "pretium, nibh dolor laoreet leo, sed pharetra pede libero non diam.\n"
                        "\n"
                        "Proin est nisi, gravida ac, vulputate id, fringilla sit amet, magna. Nam congue\n"
                        "cursus magna. In malesuada, velit a gravida sodales, dolor nisl vestibulum orci,\n"
                        "sit amet sagittis mauris tellus nec purus. Nulla eget risus. Quisque nec sapien\n"
                        "blandit odio convallis ullamcorper. Lorem ipsum dolor sit amet, consectetuer\n"
                        "adipiscing elit. Pellentesque cursus. Aliquam tempus neque vitae libero molestie\n"
                        "ut auctor.\n"
                        "\n"
                        "In nec massa eu tortor vulputate suscipit. Nam tristique magna nec pede. Sed a\n"
                        "nisi. Nulla sed augue ut risus placerat porttitor. Ut aliquam. Nulla facilisi.\n"
                        "Nulla vehicula nibh ac sapien. Nunc facilisis dapibus ipsum. Donec sed mauris.\n"
                        "Nulla quam nisi, laoreet non, dignissim posuere, lacinia nec, turpis. Mauris\n"
                        "malesuada nisi sed enim. In hac habitasse platea dictumst. Fusce faucibus,\n"
                        "turpis nec auctor posuere, nulla tellus scelerisque metus, quis molestie mi dui\n"
                        "id quam. Mauris vestibulum. Nam ullamcorper.\n" ) );
    free ( res );

    return 0;
}
#endif /* __PROGTEST__ */
