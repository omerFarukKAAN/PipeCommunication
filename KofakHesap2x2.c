#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int matrix[2][2]; //hesap yapilacak 2x2 lik matris
    int eleman; //kapatilan eleman
    int us; //kapatilan elemanin satir ve sutun indeks toplami

    //pipe'dan okuma
    read(3, &matrix, 4*sizeof(int));
    read(3, &eleman, sizeof(int));
    read(3, &us, sizeof(int));
    
    us = us+2; //indeksler 0'dan basladigindan dogru sonuc vermesi icin satir sutun indekslerinin toplamına 2 eklemek gerekir.

    //kofaktor hesabi yapma
    int kofaktor;
    if(us%2 == 0){
        kofaktor = eleman * ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]));
    }else {
        kofaktor = -1 * (eleman * ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0])));
    }
    //pipe'a yazma
    write(4, &kofaktor, sizeof(int));
}