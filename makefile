all: determinant3x3 KofakHesap2x2 SatSutSec

determinant3x3: determinant3x3.c
	gcc determinant3x3.c -o determinant3x3

KofakHesap2x2: KofakHesap2x2.c
	gcc KofakHesap2x2.c -o KofakHesap2x2

SatSutSec: SatSutSec.c
	gcc SatSutSec.c -o SatSutSec