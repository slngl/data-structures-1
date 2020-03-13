#include<stdio.h>
#include<conio.h>
#include<process.h>
#include <string.h>
#include<stdlib.h>
void read();
void write();
void del();
static int eleman=0;
struct T_Eser
{
  char eser_ismi[50];
  char eser_turu[50];
  char eser_sahibi[50];
  int eser_ID;
  int tik;
}Eser;

struct hucre {
        int icerik;
        struct hucre *sonraki;
};


struct hucre* hucre_olustur(int icerik) {
        struct hucre *a;
        a = (struct hucre*)malloc(sizeof(struct hucre));
        if (a==NULL) {
                printf("Heap alaninda yer ayrilamadi.\n");
                exit(1);
        }
        a->icerik = icerik;
        a->sonraki = NULL;
        return a;
}
void liste_yaz(struct hucre *liste_basi) {
        while(liste_basi != NULL) {
                printf("%d  ", liste_basi->icerik);
                liste_basi = liste_basi->sonraki;
        }
        printf("\n");
}
int liste_sonuna_ekle(int icerik, struct hucre **liste_basi) {

        struct hucre* a = hucre_olustur(icerik);
        if(*liste_basi == NULL) {
                a->sonraki = *liste_basi;
                *liste_basi = a;
        }
        else {
                struct hucre* x = *liste_basi;

                while(x->sonraki!= NULL  )
                {
                    x = x->sonraki;

                }
        x->sonraki = a;
        }
        return 0;
}
void liste_eleman_sil(int silinen, struct hucre **liste_basi) {
        struct hucre *temp = *liste_basi;
        struct hucre *once;
        while((temp != NULL) && (temp->icerik != silinen)) {
                once = temp;
                temp = temp->sonraki;
        }
        if (temp == NULL) {
                return;
        }
        else if (temp == *liste_basi) {
                *liste_basi =(*liste_basi)->sonraki;
        }
        else {
                once->sonraki = temp->sonraki;
        }
        free(temp);
}
struct hucre *list = NULL;
int main(){
    list=NULL;
    FILE *fp;//Dosya pointeri
    fp=fopen("Galeri.dat","w");
    fclose(fp);
	int secim;
	int s;
    while(1){
        printf("\n1:Yonetici\n2:Kullanici\n3:Cikis\n");
        scanf("%d",&s);
        switch(s){
        case 1:
        {
       		printf("\n1:Kayit Ekleme");
        	printf("\n2:Kayit Okuma");
        	printf("\n3:Kayit Silme");
        	printf("\n4:Kayit Guncelleme");
       		printf("\n5:Cikis");
        	printf("\n\tSeciminizi giriniz:- ");
        	scanf("%d",&secim);
        	switch(secim)
        	{
            case 1:
            write();
            break;
            case 2:
            read();
            break;
            case 3:
            del();
            break;
            case 4:
            update();
            break;
            case 5:
            exit(1);
            default:
            printf("\n\tGecersiz Secim\n");
            break;
        	}
		}
            case 2:
            read();
            break;
            case 3:
            exit(1);
            default:
            printf("\n\tGecersiz Secim\n");
            break;

        }
    }
getch();

}
void write()//Dosyanin içine yazma islemi yapan fonksiyon
{
    int i;
    int temp;
    int isaret=0;		//ayni id eklenmesin diye kontrol ediyor
    if(list != NULL) //erişim listesinde eleman varsa yeni eleman ona göre eklenir
    {
        FILE *fp;//Dosya pointeri
        fp=fopen("Galeri.dat","r");
        FILE *fp2;
        fp2=fopen("eklemeyeni.dat","w");
        
        struct hucre* x= list;
        jump:
        while(fread(&Eser,sizeof(Eser),1,fp)==1){
            if(Eser.eser_ID==x->icerik){					//listenin ilk elemanının olduğu yeri buluyoruz
            	printf("\nEser ID := ");
                scanf("%d",&temp);
                if(Eser.eser_ID==temp){						//daha önce girilmiş olan ID girilmiş mi
                        isaret=1;
                        printf("ayni id ile bir eser tanimli!"); 
                        goto jump;
                        break;
                }
    
                if(isaret==0){
                 Eser.eser_ID=temp;
				 printf("\nEser Adi := ");
                 scanf("%s",Eser.eser_ismi);
                 printf("\nEser Turu := ");
                 scanf("%s",Eser.eser_turu);
                 printf("\nEser Sahibi := ");
                 scanf("%s",Eser.eser_sahibi);
                 Eser.tik=1;
                 printf("\n***\n");
                 fwrite(&Eser,sizeof(Eser),1,fp2);
                 liste_eleman_sil(x->icerik,&list);
                }
            }
            else{
               fwrite(&Eser,sizeof(Eser),1,fp2);
           }
        }
        isaret=0;
        fclose(fp);
        fclose(fp2);
        remove("Galeri.dat");
        rename("eklemeyeni.dat","Galeri.dat");

    }
    else{//erişim listesinde eleman yoksa 
    	
        FILE *fp;//Dosya pointeri
        fp=fopen("Galeri.dat","a+");
        printf("\nEser ID := ");
        scanf("%d",&temp);
        jump0:
		while(fread(&Eser,sizeof(Eser),1,fp)==1){//daha önce girilmiş olan ID girilmiş mi
		
            if(Eser.eser_ID==temp){
                isaret=1;
                printf("dosyada kayitli id girildii!!");
                goto jump0;
                break;
            }
                }
                if(isaret==0)
                {
                 Eser.eser_ID=temp;			
                 printf("\nEser Adi := ");
                 scanf("%s",Eser.eser_ismi);
                 printf("\nEser Turu := ");
                 scanf("%s",Eser.eser_turu);
                 printf("\nEser Sahibi := ");
                 scanf("%s",Eser.eser_sahibi);
                 Eser.tik=1;
                 printf("\n***\n");
                 fwrite(&Eser,sizeof(Eser),1,fp);
				 }
                 isaret=0;
        fclose(fp);//dosyayi kapattik
    }
}

    int gecici;
    int isaret=0;
    if(list != NULL) //erişim listesinde eleman varsa yeni eleman ona göre eklenir
    {
        FILE *fp;//Dosya pointeri
        fp=fopen("Galeri.dat","r");
        FILE *fp2;
        fp2=fopen("eklemeyeni.dat","w");
        while(fread(&Eser,sizeof(Eser),1,fp)==1){
            if(Eser.eser_ID==list->icerik){
                printf("\nEser ID := ");
                scanf("%d",&gecici);
                while(fread(&Eser,sizeof(Eser),1,fp)==1){//daha önce girilmiş olan ID girilmiş mi
                    if(Eser.eser_ID==gecici){
                        isaret=1;
                        break;
                    }
                }
                if(isaret==0){
                 int i=Eser.eser_ID;
                 Eser.eser_ID=gecici;
                 printf("\nEser Adi := ");
                 scanf("%s",Eser.eser_ismi);
                 printf("\nEser Turu := ");
                 scanf("%s",Eser.eser_turu);
                 printf("\nEser Sahibi := ");
                 scanf("%s",Eser.eser_sahibi);
                 Eser.tik=1;
                 printf("\n*******\n");
                 fwrite(&Eser,sizeof(Eser),1,fp2);
                 liste_eleman_sil(i,&list);
                }
            }
            else{
               fwrite(&Eser,sizeof(Eser),1,fp2);
           }
        }
        isaret=0;
        fclose(fp);
        fclose(fp2);
        remove("Galeri.dat");
        rename("eklemeyeni.dat","Galeri.dat");

    }
    else{//erişim listesinde eleman yoksa
    
        FILE *fp;//Dosya pointeri
        fp=fopen("Galeri.dat","a+");
        printf("\nEser ID := ");
        scanf("%d",&gecici);
        while(fread(&Eser,sizeof(Eser),1,fp)==1){//daha önce girilmiş olan ID girilmiş mi
            if(Eser.eser_ID==gecici){
                isaret=1;
                printf("daha once bu ID degerini girdiniz\n");
                break;
            }
        }
        if(isaret==0){
                 Eser.eser_ID=gecici;
                 printf("\nEser Adi := ");
                 scanf("%s",Eser.eser_ismi);
                 printf("\nEser Turu := ");
                 scanf("%s",Eser.eser_turu);
                 printf("\nEser Sahibi := ");
                 scanf("%s",Eser.eser_sahibi);
                 Eser.tik=1;
                 printf("\n*******\n");
                 fwrite(&Eser,sizeof(Eser),1,fp);
        }
        isaret=0;
        eleman++;
        fclose(fp);//dosyayi kapattik
    }
}
void read()//Dosyanin içine okuma işlemi yapan fonksiyon
{
    FILE *fp;
    fp=fopen("Galeri.dat","r");
    while(fread(&Eser,sizeof(Eser),1,fp)==1)
        {
            if(Eser.tik==1){
                printf("\nEser ID := %d",Eser.eser_ID);
                printf("\nEser Adi := %s",Eser.eser_ismi);
                printf("\nEser Turu := %s",Eser.eser_turu);
                printf("\nEser Sahibi := %s",Eser.eser_sahibi);
                printf("\n********\n");
            }

        }
fclose(fp);
liste_yaz(list);
}
void del()
{
    FILE *fp;//Dosya pointeri
    fp=fopen("Galeri.dat","r");
    FILE *fp2;
    fp2=fopen("yeni.dat","w");
    int silinen;
    int temp=0; // Dosyadaki silinicek olan elemana olan uzaklık.

    printf("Silmek istediginiz esere ait ID giriniz: \n");
    scanf("%d",&silinen);
    while (fread(&Eser,sizeof(Eser),1,fp)==1)//dosya okunuyor
    {
       if (silinen==Eser.eser_ID){//silinen id var ise tik 0 yapılır
           Eser.tik=0;
           fwrite(&Eser,sizeof(Eser),1,fp2);
      //  fprintf(fp2,"%d %s %s %s %d",Eser.eser_ID,Eser.eser_ismi,Eser.eser_sahibi,Eser.eser_turu,Eser.tik=0);

        liste_sonuna_ekle(silinen,&list);//silinen eseri erişim listesinin sonuna ekliyoruz
        eleman--;
       }
       else {
               Eser.tik=1;
           fwrite(&Eser,sizeof(Eser),1,fp2);
         //   fprintf(fp2,"%d %s %s %s %d",Eser.eser_ID,Eser.eser_ismi,Eser.eser_sahibi,Eser.eser_turu,Eser.tik);
       }
       temp++;
    }
    if(eleman==temp) printf("\ndosyada bu eleman yok\n");//silinecek eleman dosyada yer almıyor ekrana uyarı yazısı çıkacak
    fclose(fp);
    fclose(fp2);
    remove("Galeri.dat");
    rename("yeni.dat","Galeri.dat");//yeni dosya asıl dosyaya kopyalanır

}
void update(){
    int id;
    FILE *fp;//Dosya pointeri
    fp=fopen("Galeri.dat","r");
    FILE *fp2;
    fp2=fopen("yeni.dat","w");
    printf("\nGüncellemek istediginiz verinin ID değerini girin");
    scanf("%d",&id);
     while (fread(&Eser,sizeof(Eser),1,fp)==1)//dosya okunuyor
    {
       if (id==Eser.eser_ID){
            int secim;
           printf("\nGuncellemek istediginiz değeri seçin\n1-Isim\n2-Tur\n3-Sahip\n");
           scanf("%d",&secim);
    		switch(secim){
       			case 1:
          		 printf("\nYeni ismi girin");
          		 scanf("%s",&Eser.eser_ismi);
          		 fwrite(&Eser,sizeof(Eser),1,fp2);
          		 break;
       			case 2:
         		  printf("\nYeni tur girin");
         		  scanf("%s",&Eser.eser_turu);
        		   fwrite(&Eser,sizeof(Eser),1,fp2);
        		   break;
       			case 3:
        		   printf("\nYeni sahip girin");
        		   scanf("%s",&Eser.eser_sahibi);
       			    fwrite(&Eser,sizeof(Eser),1,fp2);
       			    break;
       		}
       }
       else{
          fwrite(&Eser,sizeof(Eser),1,fp2);
       }
    }
       fclose(fp);
       fclose(fp2);
       remove("Galeri.dat");
       rename("yeni.dat","Galeri.dat");
}
