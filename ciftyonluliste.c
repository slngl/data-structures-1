#include <stdio.h>

struct hucre{
  int icerik;
  struct hucre *ileri;
  struct hucre *geri;
};

struct liste{
  struct hucre *bas;
  struct hucre *son;
 };
 
 struct hucre *hucre_olustur(int icerik){
  struct hucre *yeni;
  yeni=(struct hucre*)malloc(sizeof(struct hucre));
  if(yeni==NULL){
    printf("yeni hücremize yer ayrılamadı maalesef :( ");
    exit(1);
  }
   yeni->icerik=icerik;
   yeni->ileri=yeni->geri=NULL;
   return yeni;
}

void liste_baslat(struct liste **liste){
  *liste=(struct liste*)malloc(sizeof(struct liste));
  if(liste==NULL){
     printf("yeni listemize yer ayrılamadı maalesef :( ");
     exit(1);
  }
  (*liste)->bas=(*liste)->son=NULL;
}

void listeye_sondan_ekle(int icerik, struct liste *liste){
  struct hucre *yeni;
  yeni=hucre_olustur(icerik);
  if(liste->bas==NULL){
    liste->bas=yeni;
  }
  else{
    liste->son->ileri=yeni;
    yeni->geri=liste->son;
  }
  liste->son=yeni;
}

void listeye_bastan_ekle(int icerik, struct liste *liste){
  struct hucre *yeni;
  yeni=hucre_olustur(icerik);
  if(liste->son==NULL){
    liste->son = yeni;
  }
  
  else{
    liste->bas->geri=yeni;
    yeni->ileri = liste->bas;
  }
  liste->bas = yeni;
}

void liste_yazdir(struct liste *liste){
  struct hucre *bas = liste->bas;
  while(bas != NULL){
    printf("%d\t", bas->icerik);
    bas = bas->ileri;
  }
  printf("\n");

}

void yanlis_liste_yazdir(struct liste *liste){
  //struct hucre *bas = liste->bas;
  while(liste->bas != NULL){
    printf("%d\t", liste->bas->icerik);
    liste->bas = liste->bas->ileri;
  }
  printf("\n");

}

void sondan_liste_yazdir(struct liste *liste){
  struct hucre *son = liste->son;
  while(son != NULL){
    printf("%d", son->icerik);
    son = son->geri;
  }
  printf("\n");

}

int main(void) {

  struct liste *liste;

  liste_baslat(&liste);

  listeye_bastan_ekle(24, liste);

  listeye_sondan_ekle(12, liste);
  
  listeye_bastan_ekle(2, liste);

  listeye_sondan_ekle(12, liste);

  liste_yazdir(liste);

  printf("ikinci fonk deneme\n");
  
  yanlis_liste_yazdir(liste);
  
  return 0;
}
