#include <stdio.h>
#include <stdlib.h>


struct hucre{
  int icerik;
  struct hucre *sonraki;
};
//düğüm yapısı oluşturduk

struct hucre* hucre_olustur(int icerik){
  struct hucre *a;
  a=(struct hucre*)malloc(sizeof(struct hucre));
  if(a==NULL){
    printf("Heap alanında yer ayrılamadı...");
    exit(1);
  }
  a->icerik=icerik;
  a->sonraki=NULL;
  return a;
}

void liste_basina_ekle(int icerik, struct hucre **liste_basi){
  struct hucre *a=hucre_olustur(icerik);
  a->sonraki=*liste_basi;
  *liste_basi=a;
}

void liste_sonuna_ekle(int icerik, struct hucre **liste_basi){
  struct hucre *a=hucre_olustur(icerik);
  if(*liste_basi==NULL){
    a->sonraki=*liste_basi;
    *liste_basi=a;
  }
  else {
    struct hucre* x = *liste_basi;
    while(x->sonraki != NULL) {
     x = x->sonraki;
    }
    x->sonraki = a;
  }
}

void liste_yaz(struct hucre *liste_basi){
  while(liste_basi!=NULL){
    printf("%d\t", liste_basi->icerik);
    liste_basi=liste_basi->sonraki;
  }
  printf("\n");
}

void liste_yaz_recursive(struct hucre *liste_basi){
  if(liste_basi!=NULL){
    printf("%d", liste_basi->icerik);
    liste_yaz_recursive(liste_basi->sonraki);
  }
}

void tersten_liste_yaz_recursive(struct hucre *liste_basi){
  if(liste_basi!=NULL){
    tersten_liste_yaz_recursive(liste_basi->sonraki);
    printf("%d", liste_basi->icerik);
  }
}

void liste_sirali_ekle(int icerik, struct hucre **liste_basi){
  struct hucre *a, *b, *eklenen;
  b=*liste_basi;
  while(b!=NULL && b->icerik <= icerik){
    if(b->icerik==icerik){
      return;
    }//aynı elemanı eklemeyi engeller
    a=b;
    b=b->sonraki;
  }
  eklenen=hucre_olustur(icerik);
  if(b==*liste_basi){
    eklenen->sonraki=*liste_basi;
    *liste_basi=eklenen;
  }//liste boşsa eklenen hucresi liste başı olur
  else{
    a->sonraki=eklenen;
    eklenen->sonraki=b;
  }
}

void liste_eleman_sil(int silinen, struct hucre **liste_basi){
  struct hucre *temp= *liste_basi;//liste başını kaybetmemek için temp'e atadık
  struct hucre *once;
  while((temp!=NULL) && (temp->icerik!=silinen)){
    once=temp;
    temp=temp->sonraki;
  }//silinecek elemanı bulduk
  if(temp==NULL){
    return;
  }
  else if(temp==*liste_basi){
    *liste_basi=(*liste_basi)->sonraki;
  }//silinecek eleman liste başıysa listeye tekrar ulaşabilmek için ikinci elemanı liste başına atadık
  else{
    once->sonraki=temp->sonraki;
  }
  free(temp);
}

void liste_sirala(struct hucre **liste_basi){
  struct hucre *a,*b,*c,*d;
  if(*liste_basi==NULL || (*liste_basi)->sonraki==NULL ){
    return;
  }//listede birden fazla eleman olmalı
  d=(*liste_basi)->sonraki;
  (*liste_basi)->sonraki=NULL;
  while(d!=NULL){
    c=d;
    d=d->sonraki;
    b=*liste_basi;
    while(b!=NULL && b->icerik < c->icerik ){
      a=b;
      b=b->sonraki;
    }
    if(b==*liste_basi){
      c->sonraki=*liste_basi;
      *liste_basi=c;
    }
    else{
      a->sonraki=c;
      c->sonraki=b;
    }
  }
}

void liste_ters_cevir(struct hucre **liste_basi) {
  struct hucre *a, *b;
  a = NULL;
  while(*liste_basi != NULL) {
    b = *liste_basi;
    *liste_basi = (*liste_basi)->sonraki;
    b->sonraki = a;
    a = b;
  }
 *liste_basi = a;
}

struct hucre **liste_ters_cevir_recursive(struct hucre **liste_basi) {
 struct hucre *gecici;
  if (*liste_basi == NULL) {
    return liste_basi;
  }
  else if ((*liste_basi)->sonraki == NULL) {
    return &((*liste_basi)->sonraki);
  }
  else {
    gecici = *liste_basi;
    *liste_basi = (*liste_basi)->sonraki;
    *liste_ters_cevir_recursive(liste_basi) = gecici;
    gecici->sonraki = NULL;
    return &(gecici->sonraki);
  }
}
int main(void) {
  struct hucre *liste1 = NULL;
  liste_basina_ekle(30, &liste1);
  liste_yaz(liste1);
  liste_basina_ekle(550, &liste1);
  liste_sonuna_ekle(40, &liste1);
  liste_yaz(liste1);
  liste_sonuna_ekle(50, &liste1);
  liste_yaz(liste1);
  liste_yaz(liste1);
  liste_ters_cevir_recursive(&liste1);
  liste_yaz(liste1);
  return 0;
}
