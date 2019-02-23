#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
	char *cevap; //program bir kere calisinca yeniden calismasi icin sorulan sorunun cevabi
	do{
		int totalSonuc; //kofaktor sonucu
		int fd[2];
		if(pipe(fd) < 0){
			puts("Pipe Error !");
		}
		int matrix[3][3];
		char sayilar[20]; //girilen sayi
		int elemanlar[9]; //matrisin elemanlari
		int n = 0; //matrisin eleman indeksi
		
		do{	
			printf("Eleman girin : ");
			gets(sayilar);
			elemanlar[n] = atoi(strtok(sayilar, " ")); //girilen sayiyi integer'a donusturerek elemanlar dizisine atar
			n++;
		}while(n<9); //3x3 luk matris oldugundan 9 sayi gelmesi gerekir
		n = 0;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				matrix[i][j] = elemanlar[n]; //matrisi olusturma
				n++;
			}
		}
		int f,i;

		f = fork();
		if(f == 0){
			i = execv("SatSutSec", NULL);
			exit(0);
		}else {
			wait(&i);
		}
		char value[5];
		read(fd[0], &value, 6*sizeof(char)); //SatSutSec programindan gelen degeri value adli degiskene atar
		printf("SatSutSec Value : %s\n"); //SatSutSec programindan gelen deger
		
		//KofakHesap2x2 programına gonderilmek uzere tanimlanmis matrisler
		int kofakMatrix1[2][2];
		int kofakMatrix2[2][2];
		int kofakMatrix3[2][2];

		int sonuc1, sonuc2, sonuc3; //kofakMatrislerin sonuclari

		char *satSut = (char*)malloc(5*sizeof(char));

		char *dizi[2];
		dizi[0] = (char*)malloc(5*sizeof(char));
		dizi[1] = (char*)malloc(5*sizeof(char));
		char* pch = strtok(value, " "); //SatSutSec programindan gelen degeri ikiye bolme
		n = 0;
		//SatSutSec programindan gelen degerleri bosluklara gore ayirip diziye atama
		while(pch != NULL){
			strcpy(dizi[n], pch);
			pch = strtok(NULL, " ");
			n++;
		}

		strcpy(satSut, strtok(value, " ")); //Sat 1 veya Sut 3 olarak gelen stringi iki parcaya bolme
		int no = atoi(dizi[1]);
		int satSutIndeksToplam;
		if(strcmp(satSut, "Sat") == 0){
			switch(no){
				case 0 :
					kofakMatrix1[0][0] = matrix[1][1];
					kofakMatrix1[0][1] = matrix[1][2];
					kofakMatrix1[1][0] = matrix[2][1];
					kofakMatrix1[1][1] = matrix[2][2];

					kofakMatrix2[0][0] = matrix[1][0];
					kofakMatrix2[0][1] = matrix[1][2];
					kofakMatrix2[1][0] = matrix[2][0];
					kofakMatrix2[1][1] = matrix[2][2];

					kofakMatrix3[0][0] = matrix[1][0];
					kofakMatrix3[0][1] = matrix[1][0];
					kofakMatrix3[1][0] = matrix[1][1];
					kofakMatrix3[1][1] = matrix[2][1];

					//pipe'a matrisleri yazma ve KofakHesap2x2 programı calistirilarak sonuclar elde etme
					write(fd[1], &kofakMatrix1, 4*sizeof(int));
					write(fd[1], &matrix[0][0], sizeof(int));
					satSutIndeksToplam = 0;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc1, sizeof(int));

					write(fd[1], &kofakMatrix2, 4*sizeof(int));
					write(fd[1], &matrix[0][1], sizeof(int));
					satSutIndeksToplam = 1;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc2, sizeof(int));

					write(fd[1], &kofakMatrix3, 4*sizeof(int));
					write(fd[1], &matrix[0][2], sizeof(int));
					satSutIndeksToplam = 2;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc3, sizeof(int));

					totalSonuc = sonuc1 + sonuc2 + sonuc3;
				
				case 1 :
					kofakMatrix1[0][0] = matrix[0][1];
					kofakMatrix1[0][1] = matrix[2][1];
					kofakMatrix1[1][0] = matrix[0][2];
					kofakMatrix1[1][1] = matrix[2][2];

					kofakMatrix2[0][0] = matrix[0][0];
					kofakMatrix2[0][1] = matrix[2][0];
					kofakMatrix2[1][0] = matrix[0][2];
					kofakMatrix2[1][1] = matrix[2][2];

					kofakMatrix3[0][0] = matrix[0][0];
					kofakMatrix3[0][1] = matrix[2][0];
					kofakMatrix3[1][0] = matrix[0][1];
					kofakMatrix3[1][1] = matrix[2][1];

					write(fd[1], &kofakMatrix1, 4*sizeof(int));
					write(fd[1], &matrix[1][0], sizeof(int));
					satSutIndeksToplam = 1;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc1, sizeof(int));

					write(fd[1], &kofakMatrix2, 4*sizeof(int));
					write(fd[1], &matrix[1][1], sizeof(int));
					satSutIndeksToplam = 2;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc2, sizeof(int));

					write(fd[1], &kofakMatrix3, 4*sizeof(int));
					write(fd[1], &matrix[1][2], sizeof(int));
					satSutIndeksToplam = 3;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc3, sizeof(int));

					totalSonuc = sonuc1 + sonuc2 + sonuc3;

				case 2 :
					kofakMatrix1[0][0] = matrix[0][1];
					kofakMatrix1[0][1] = matrix[1][1];
					kofakMatrix1[1][0] = matrix[0][2];
					kofakMatrix1[1][1] = matrix[1][2];

					kofakMatrix2[0][0] = matrix[0][0];
					kofakMatrix2[0][1] = matrix[1][0];
					kofakMatrix2[1][0] = matrix[0][2];
					kofakMatrix2[1][1] = matrix[1][2];

					kofakMatrix3[0][0] = matrix[0][0];
					kofakMatrix3[0][1] = matrix[1][0];
					kofakMatrix3[1][0] = matrix[0][1];
					kofakMatrix3[1][1] = matrix[1][1];

					write(fd[1], &kofakMatrix1, 4*sizeof(int));
					write(fd[1], &matrix[2][0], sizeof(int));
					satSutIndeksToplam = 2;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc1, sizeof(int));

					write(fd[1], &kofakMatrix2, 4*sizeof(int));
					write(fd[1], &matrix[2][1], sizeof(int));
					satSutIndeksToplam = 3;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc2, sizeof(int));

					write(fd[1], &kofakMatrix3, 4*sizeof(int));
					write(fd[1], &matrix[2][2], sizeof(int));
					satSutIndeksToplam = 4;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc3, sizeof(int));

					totalSonuc = sonuc1 + sonuc2 + sonuc3;
			}
		}

		if(strcmp(satSut, "Sut") == 0){
			switch(no){
				case 0 :
					kofakMatrix1[0][0] = matrix[1][1];
					kofakMatrix1[0][1] = matrix[2][1];
					kofakMatrix1[1][0] = matrix[1][2];
					kofakMatrix1[1][1] = matrix[2][2];

					kofakMatrix2[0][0] = matrix[0][1];
					kofakMatrix2[0][1] = matrix[2][1];
					kofakMatrix2[1][0] = matrix[0][2];
					kofakMatrix2[1][1] = matrix[2][2];

					kofakMatrix3[0][0] = matrix[0][1];
					kofakMatrix3[0][1] = matrix[1][1];
					kofakMatrix3[1][0] = matrix[0][2];
					kofakMatrix3[1][1] = matrix[1][2];

					write(fd[1], &kofakMatrix1, 4*sizeof(int));
					write(fd[1], &matrix[0][0], sizeof(int));
					satSutIndeksToplam = 0;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc1, sizeof(int));

					write(fd[1], &kofakMatrix2, 4*sizeof(int));
					write(fd[1], &matrix[1][0], sizeof(int));
					satSutIndeksToplam = 1;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc2, sizeof(int));

					write(fd[1], &kofakMatrix3, 4*sizeof(int));
					write(fd[1], &matrix[2][0], sizeof(int));
					satSutIndeksToplam = 2;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc3, sizeof(int));
				
					totalSonuc = sonuc1 + sonuc2 + sonuc3;

				case 1 :
					kofakMatrix1[0][0] = matrix[1][0];
					kofakMatrix1[0][1] = matrix[1][2];
					kofakMatrix1[1][0] = matrix[2][0];
					kofakMatrix1[1][1] = matrix[2][2];

					kofakMatrix2[0][0] = matrix[0][0];
					kofakMatrix2[0][1] = matrix[2][0];
					kofakMatrix2[1][0] = matrix[0][2];
					kofakMatrix2[1][1] = matrix[2][2];

					kofakMatrix3[0][0] = matrix[0][0];
					kofakMatrix3[0][1] = matrix[1][0];
					kofakMatrix3[1][0] = matrix[0][2];
					kofakMatrix3[1][1] = matrix[1][2];

					write(fd[1], &kofakMatrix1, 4*sizeof(int));
					write(fd[1], &matrix[0][1], sizeof(int));
					satSutIndeksToplam = 1;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc1, sizeof(int));

					write(fd[1], &kofakMatrix2, 4*sizeof(int));
					write(fd[1], &matrix[1][1], sizeof(int));
					satSutIndeksToplam = 2;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc2, sizeof(int));

					write(fd[1], &kofakMatrix3, 4*sizeof(int));
					write(fd[1], &matrix[2][2], sizeof(int));
					satSutIndeksToplam = 4;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc3, sizeof(int));

					totalSonuc = sonuc1 + sonuc2 + sonuc3;

				case 2 :
					kofakMatrix1[0][0] = matrix[1][0];
					kofakMatrix1[0][1] = matrix[2][0];
					kofakMatrix1[1][0] = matrix[1][1];
					kofakMatrix1[1][1] = matrix[2][1];

					kofakMatrix2[0][0] = matrix[0][0];
					kofakMatrix2[0][1] = matrix[2][0];
					kofakMatrix2[1][0] = matrix[0][1];
					kofakMatrix2[1][1] = matrix[2][1];

					kofakMatrix3[0][0] = matrix[0][0];
					kofakMatrix3[0][1] = matrix[1][0];
					kofakMatrix3[1][0] = matrix[0][1];
					kofakMatrix3[1][1] = matrix[1][1];

					write(fd[1], &kofakMatrix1, 4*sizeof(int));
					write(fd[1], &matrix[0][2], sizeof(int));
					satSutIndeksToplam = 2;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc1, sizeof(int));

					write(fd[1], &kofakMatrix2, 4*sizeof(int));
					write(fd[1], &matrix[1][2], sizeof(int));
					satSutIndeksToplam = 3;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc2, sizeof(int));

					write(fd[1], &kofakMatrix3, 4*sizeof(int));
					write(fd[1], &matrix[2][2], sizeof(int));
					satSutIndeksToplam = 4;
					write(fd[1], &satSutIndeksToplam, sizeof(int));
					f = fork();
					if(f == 0){
						execv("KofakHesap2x2", NULL);
						exit(0);
					}else{
						wait(&i);
					}
					read(fd[0], &sonuc3, sizeof(int));
					
					totalSonuc = sonuc1 + sonuc2 + sonuc3;
			}
		}
		//pipe'ı kapayarak kofaktor hesabının sonucunu ekrana basma
		close(fd[0]);
		close(fd[1]);
		printf("Kofaktor Sonuc : %d\n", totalSonuc);
		puts("Yeni islem yapmak istiyor musunuz E/H ?");
		gets(cevap);
	}while(strcmp(cevap, "E") == 0); //cevap 'E' oldugu surece program calisir
}