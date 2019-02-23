#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void){
    srand(time(NULL)); //ayni degerler uretilmesin

    int no = rand()%3; //satir veya sutun indeksi
    int satOrSut = rand()%2; //satir mi sutun mu oldugu
    char returnValue[6]; //Sat 1 veya Sut 3 olarak dondurulecek deger

    switch(satOrSut){
        case 0 : 
            strcpy(returnValue, "Sat "); //returnValue'ya "Sat " atama
            char *c = no+'0'; //integer degiskeni char'a cast etme
            strcat(returnValue, &c); //returnValue'ya cast edilen char'ı ekleme
            break;
        case 1 : 
            strcpy(returnValue, "Sut ");
            char *ch = no+'0';
            strcat(returnValue, &ch);
            break;
    }
    //pipe'a yazma
    write(4, &returnValue, 6*sizeof(char));
}