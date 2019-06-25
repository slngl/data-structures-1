#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void tek_boyutlu_dizi_olustur(int **dizi, int size){
  int i;
  *dizi=(int*)malloc(sizeof(int)*size);
  for( i=0; i<size; i++){
    *(*dizi+i)=rand()%20;
  }
}

void tek_boyutlu_dizi_yaz(int *dizi, int size){
  int i;
  for(i=0; i<size; i++){
    printf("%p\n", (dizi+i));//adresleri yazdırıyor
  }
  printf("\n");
  for(i=0; i<size; i++){
    printf("%d\n", *(dizi+i));
  }
  printf("\n");
}

void dinamik_matris_olustur(int ***dizi, int satir, int sutun){
  int i,j;
  *dizi=(int**)malloc(satir*sizeof(int*));
  for (i=0; i<satir; i++){
    *(*dizi+i)=(int*)malloc(sutun*sizeof(int));
    for(j=0; j<sutun; j++){
      *(*(*dizi+i)+j)=rand()%5;
    }
  }
}

void matris_degistir(int **dizi, int satir, int sutun){
  int i,j;
  for(i=0; i<satir; i++){
    for(j=0; j<sutun; j++){
      *(*(dizi+i)+j)=rand()%5;
    }
  }
}

void dinamik_matris_yaz(int **dizi, int satir, int sutun){
  int i,j;
  for(i=0; i<satir; i++){
    for(j=0; j<sutun; j++){
      printf("%4d",*(*(dizi+i)+j));
    }
    printf("\n");
  }
}

void dinamik_matris_carpimi(int **A, int A_satir, int A_sutun, int **B, int B_satir, int B_sutun, int **C, int C_satir, int C_sutun){
  int i,j,k;
  if(A_sutun!=B_satir){
    printf("çarpım matrislerinin boyutları uyuşmuyor!\n");
    return;
  }
  else if(A_satir!=C_satir || B_sutun!=C_sutun){
    printf("sonuç matrisinin boyutları çarpan matrisle uyuşmuyor!\n");
    return;
  }
  else{
    for(i=0; i<A_satir;i++){
      for(j=0; B_sutun; j++){
        C[i][j]=0;
        for(k=0; k<A_sutun; k++){
          C[i][j]=C[i][j]+A[i][k]+B[k][i];
        }
      }
    }
  }
}

void dizi_kopyala(int *statik_dizi, int statik_size, int **dinamik_dizi, int *dinamik_size){
  int i;
  *dinamik_dizi=(int*)malloc(statik_size*sizeof(int));
  if(*dinamik_dizi==NULL){
    printf("heapte yer ayrılamadı...");
    exit(1);
  }
  *dinamik_size=statik_size;
  for(i=0; i<statik_size; i++){
    (*dinamik_dizi)[i]=statik_dizi[i];
  }
}

int main(void) {
  

        int **A,**B,**C;
        int *dizi;
        int eleman_sayisi = 10;
        srand(time(NULL));

        tek_boyutlu_dizi_olustur(&dizi, eleman_sayisi);
        tek_boyutlu_dizi_yaz(dizi, eleman_sayisi);

        dinamik_matris_olustur(&A,4,3);
        printf("--- A matrisi ----\n");
        dinamik_matris_yaz(A,4,3);

        A[0][1]=100;
        printf("--- A matrisi ----\n");
        dinamik_matris_yaz(A,4,3); // değiştirme işlemi

        dinamik_matris_olustur(&B,3,5);
        printf("--- B matrisi ----\n");
        dinamik_matris_yaz(B,3,5);

        dinamik_matris_olustur(&C,4,5);
        printf("--- C matrisi ----\n");
        dinamik_matris_yaz(C,4,5);


        dinamik_matris_carpimi(A,4,3,B,3,5,C,4,5);
        printf("---- C=A*B matrisi ----\n");
        dinamik_matris_yaz(C,4,5);
        printf("-----------------------\n"); //Matris Çarpımı
  return 0;
}
