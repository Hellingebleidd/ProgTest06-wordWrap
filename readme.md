**Termín odevzdání:** **16.12.2018 23:59:59**

**Pozdní odevzdání s penalizací:  06.01.2019 23:59:59**  (Penále za pozdní odevzdání: 100.0000 %)

Úkolem je realizovat funkci  wordWrap, která dokáže zformátovat text podle zadané šířky.

Rozhraní funkce je následující:

char * wordWrap ( int width, const char * src );

**width** je šířka formátu (max. počet znaků na řádku),
**src** je ASCIIZ (binární nulou ukončený) řetězec ke zformátování, funkce jej pouze čte (nesmí jej modifikovat),

**návratová hodnota** je zformátovaný řetězec tak, aby délky řádek nepřesahovaly zadanou šířku. Text bude zformátován "vlevo". Funkce alokuje prostor pro návratovou hodnotu dynamicky pomocí  malloc(), (nepoužívejte C++ operátor  new). Volající text po zpracování uvolní voláním  free().

**Vstupní řetězec** obsahuje slova oddělená bílými znaky (mezery a tabulátory, mezi slovy může být i více než jeden bílý znak). Odstavce jsou oddělené dvěma (či více) po sobě jdoucími znaky odřádkování.

**Pravidla formátování:**  

-   výstupní řetězec je ve formátu ASCIIZ (binární nulou ukončený),
-   zformátovaný text obsahuje slova oddělená vždy pouze jednou mezerou a odstavce oddělené vždy pouze jedním prázdným řádkem (tedy dvojicí znaků odřádkování).
-   Pokud na vstupu není žádné slovo, bude výstupem prázdný řetězec (alokovaná paměť, ale obsahuje pouze ukončující binární nulu).
-   Před prvním slovem na řádku nejsou mezery.
-   Za posledním slovem na řádku nejsou žádné mezery, pouze odřádkování. Odřádkování je i za posledním řádkem textu.
-   Slova jsou zarovnaná vlevo. Pokud se další slovo na danou řádku nevejde, řádka se ukončí a slovo bude umístěno jako první na následující řádce.
-   Funkce vrací návratovou hodnotu  NULL, pokud je během formátování nalezeno slovo, které se nevejde na řádku.

Realizovaná funkce nesmí používat C++ datový typ string, datové typy z STL (vector,  list, ...) ani regulární výrazy ze standardní knihovny. Použití těchto prostředků povede k chybě při kompilaci. Na vstupu mohou být dlouhé řetězce (např. tisíce znaků).

Odevzdávejte soubor, který obsahuje pouze realizovanou funkci  wordWrap  a případně další Vámi realizované funkce, které jsou z funkce  wordWrap  volané. Naopak, v odevzdávaném souboru nesmí být vkládání hlavičkových souborů a funkce  main  (pokud vkládání hlavičkových souborů a funkci main zabalíte do bloku podmíněného překladu, mohou zůstat). Za základ řešení použijte ukázku z přiloženého archivu. Ukázku si zkopírujte a doplňte implementaci požadované funkce (případně dalších Vašich funkcí). Pokud zachováte bloky podmíněného překladu, můžete takový soubor odevzdávat Progtestu.