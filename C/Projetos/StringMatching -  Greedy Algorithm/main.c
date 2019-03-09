#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int stringMatching(char *txt,char *palvr);
int search(char *txt, char *plvr);

int main(int argc, char *argv[]) {
	int x;
	char *texto;
	texto = "EBEBEBEB cavalo fdsgh fgfedet ffdt";
	search(texto, "cavalo");
	stringMatching(texto,"cavalo");
	return 0;
}

int stringMatching(char *txt,char *palvr){
	int x,y;
	for(x=0;x<strlen(txt);x++){
		
		if(palvr[0] == txt[x]){
			y = 0;
			while( (y < strlen(palvr)) && (txt[x+y] == palvr[y]) ){
				printf("%c",palvr[y]);
				y++;	
			}
		}
	}
}


int search(char *txt, char *plvr){
	int x,y;
	for(x=0; x<(strlen(txt) );x++){
		for(y=0; y<strlen(plvr); y++){
			if(txt[x] != plvr[y]){
				break;
			}
		}
		if(y == strlen(plvr)){
			printf("Inicio de string: %d \n",x);
		}
	}
}