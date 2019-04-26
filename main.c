#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct
{
    char isim[50];
    long int TCKlimlikNo;
    long int telefon;
    char eposta[50];
    char adres[50];
} personel;
  personel per={0};
int main()
{
    setlocale(LC_ALL, "Turkish");
    anaMenu();
    return 0;
}
void anaMenu()
{
    int secim;
    while(secim>6)
    {
        printf("\n\t\t\t\tPERSONEL BILGI SISTEMI\n\n");
        printf("\tISLEMLER\n\n");
        printf("\t*1.Kayit Ekle\n\t*2.Personel Listele\n\t*3.Kaydi Duzenle\n\t*4.TC Kimlik No ile Kayit Bul\n");
        printf("\t*5.Isim ile Kayit Bul\n\t*6.Kayit Sil\n\t*0.Cikis\n\n");
        printf("\tYapmak istediginiz islemi seciniz:");
        scanf("%d", &secim);
    }
    system("cls");
    if(secim==1)
    {
        KayitEkle();
    }
    if(secim==2)
    {
        PersonelListele();
    }
    if(secim==3)
    {
        KaydiDuzenle();
    }
    if(secim==4)
    {
        TCileBul();
    }
    if(secim==5)
    {
        IsimleBul();
    }
    if(secim==6)
    {
        KayitSil();
    }
    if(secim==0)
    {
        Cikis();
    }
}
void KayitEkle()
{
    personel per;
    FILE *fp;
    if((fp=fopen("Personel.txt","a+"))==NULL)
    {
        printf("Dosya bulunmadi.\n");
        exit(1);
    }
    printf("\n\n\n\t\tPERSONEL BILGI GIRISI\n\n");
    while(1)
    {
        printf("\tPersonel Adi:");
        scanf("%s",per.isim);
        printf("\tPersonel TC Kimlik No:");
        scanf("%ld",&per.TCKlimlikNo);
        printf("\tPersonel Telefon No:");
        scanf("%ld",&per.telefon);
        printf("\tPersonel eposta:");
        scanf("%s",per.eposta);
        printf("\tPersonel Adres:");
        scanf("%s",per.adres);

        fwrite(&per,sizeof(per),1,fp);
        break;
    }
    fclose(fp);
    system("cls");
    char tercih;
        while(1)
        {
        printf("\n\tYeni Kayit Eklemek Ister Misinz?[E/e - H/h]:");
        scanf("%s",&tercih);
        printf("\n\n");
        if(tercih=='e' || tercih=='E')
        {
            KayitEkle();
        }
        else if(tercih=='h' || tercih=='H')
        {
            anaMenu();
        }
        }

}
void PersonelListele()
{
    personel per;
    FILE *fp;
    if((fp=fopen("Personel.txt","rb+"))==NULL)
    {
        printf("Dosya bulunmadi.\n");
        exit(1);
    }
    printf("\t\t\tPERSONEL LISTESI\n\n");
    while(fread(&per,sizeof(per),1,fp)==1)
    {
        if(per.TCKlimlikNo !=0 && per.telefon != 0)
        {
            printf("\tPersonel Adi:%s\n", per.isim);
            printf("\tPersonel TC Kimlik No:%ld\n", per.TCKlimlikNo);
            printf("\tPersonel Telefon No:%ld\n", per.telefon);
            printf("\tPersonel Eposta:%s\n", per.eposta);
            printf("\tPersonel Adres:%s\n\n", per.adres);
        }
    }
    fclose(fp);
    anaMenu();

}
void KaydiDuzenle()
{
    personel per;
    char durum[10]="bulunamadi";
    char ad[50];
    FILE *fp;
    system("cls");
    while(1)
    {
        printf("\n\n\tKaydi Duzenlemek Istediginiz Personelin Adini Giriniz:");
        scanf("%s", ad);
        if((fp=fopen("Personel.txt","rb+"))==NULL)
          {
        printf("Dosya bulunmadi.\n");
        exit(1);
          }
        while(fread(&per,sizeof(per),1,fp)==1)
        {
         if(strcmp(per.isim,ad)==0)
         {
             printf("\n\tYeni Personel Adi:");
             scanf("%s",per.isim);
             printf("\tYeni Personel TC Kimlik No:");
             scanf("%ld",&per.TCKlimlikNo);
             printf("\tYeni Personel Telefon No:");
             scanf("%ld",&per.telefon);
             printf("\tYeni Personel Eposta:");
             scanf("%s",per.eposta);
             printf("\tYeni Personel Adres:");
             scanf("%s",per.adres);
             int a;
             a=ftell(fp);
             fseek(fp,(a-sizeof(per)),SEEK_SET);
             fwrite(&per,sizeof(per),1,fp);
             printf("\n\n\tISLEM TAMAMLANDI\n\n");
             printf("\n\tGUNCELLENMIS LISTE\n\n");
             rewind(fp);

             while(fread(&per,sizeof(per),1,fp)==1)
             {
                  if(per.TCKlimlikNo !=0 || per.telefon != 0)
                   {
            printf("\tPersonel Adi:%s\n", per.isim);
            printf("\tPersonel TC Kimlik No:%ld\n", per.TCKlimlikNo);
            printf("\tPersonel Telefon No:%ld\n", per.telefon);
            printf("\tPersonel Eposta:%s\n", per.eposta);
            printf("\tPersonel Adres:%s\n\n", per.adres);
                  }
             }
             anaMenu();
         }
         else strcpy(durum,"bulunamadi");
        }
        fclose(fp);
        if(strcmp(durum,"bulunamadi")== 0)
        {
            printf("Kayit Bulunamdi.\n");
            char secimm;
            printf("\n\tTekrar Arama Yapmak Ister Misiniz?[E/e - H/h]:");
            scanf("%s",&secimm);
            if(secimm=='E' || secimm=='e') continue;
        }
    }
}
void TCileBul()
{
    personel per;
    FILE *fp;
    long int tc;
    int k=0;

    printf("\tAradiginiz kisinin TC sini giriniz:");
    scanf("%ld",&tc);

    if((fp=fopen("Personel.txt","r"))==NULL)
          {
        printf("Dosya bulunmadi.\n");
        exit(1);
          }
    while(1)
    {
        while(!feof(fp))
        {
            fread(&per,sizeof(per),1,fp);
            if(tc==per.TCKlimlikNo)
            {
            printf("\n\tKayit Bulundu\n\n");
            printf("\tPersonel Adi:%s\n", per.isim);
            printf("\tPersonel TC Kimlik No:%ld\n", per.TCKlimlikNo);
            printf("\tPersonel Telefon No:%ld\n", per.telefon);
            printf("\tPersonel Eposta:%s\n", per.eposta);
            printf("\tPersonel Adres:%s\n\n", per.adres);
            k++;
            break;
            }
        }
        if(k==0) printf("\n\tKayit Bulunamadi\n");
        anaMenu();
    }
    fclose(fp);
}
void IsimleBul()
{
    personel per;
    FILE *fp;
    char ad[30];
    int k=0;

    printf("\tAradiginiz kisinin Adini giriniz:");
    scanf("%s",ad);

    if((fp=fopen("Personel.txt","r"))==NULL)
          {
        printf("Dosya bulunmadi.\n");
        exit(1);
          }
    while(1)
    {
        while(!feof(fp))
        {
            fread(&per,sizeof(per),1,fp);
            if(strcmp(ad,per.isim)==0)
            {
            printf("\n\tKayit Bulundu\n\n");
            printf("\tPersonel Adi:%s\n", per.isim);
            printf("\tPersonel TC Kimlik No:%ld\n", per.TCKlimlikNo);
            printf("\tPersonel Telefon No:%ld\n", per.telefon);
            printf("\tPersonel Eposta:%s\n", per.eposta);
            printf("\tPersonel Adres:%s\n\n", per.adres);
            k++;
            break;
            }
        }
        if(k==0) printf("\n\tKayit Bulunamadi\n");
        anaMenu();
    }
    fclose(fp);
}
void KayitSil()
{
    FILE *fp;
    personel per;
    long int TCno;
    int i=0;
    while(1)
    {
        printf("\n\n\tKaydi Silmek Istediginiz Personelin TC sini giriniz: ");
        scanf("%ld",&TCno);

     if((fp=fopen("Personel.txt","rb+"))==NULL)
          {
        printf("Dosya bulunmadi.\n");
        exit(1);
          }
    while(!feof(fp))
    {
        fread(&per,sizeof(per),1,fp);
        if(TCno==per.TCKlimlikNo)
        {
            strcpy(per.isim,"\0");
            per.TCKlimlikNo=0;
            per.telefon=0;
            strcpy(per.eposta,"\0");
            strcpy(per.adres,"\0");

            int a;
            a=ftell(fp);
            fseek(fp,(a-sizeof(per)),SEEK_SET);
            fwrite(&per,sizeof(per),1,fp);
            printf("\n\n\tISLEM TAMAMLANDI\n\n");
            i++;
            break;
        }
    }
    fclose(fp);
    if(i==0)
    {
     printf("\n\tAradiginiz Kayit Bulunamadi\n");
     break;
    }
    break;
    }
    while(1)
    {
        char tercih;
        printf("\n\n\tTekrar Islem Yapmak Ister Misinz?[E/e - H/h]:");
        scanf("%s",&tercih);
        printf("\n\n");
        if(tercih=='e' || tercih=='E')
        {
            KayitSil();
        }
        else if (tercih=='h' || tercih=='H')
        {
            anaMenu();
        }
    }
}
void Cikis()
{
        char tercih;
        printf("\n\n\tCikis Yapmak Ister Misinz?[E/e - H/h]:");
        scanf("%s",&tercih);
        printf("\n\n");
        if(tercih =='e' || tercih=='E')
        {
            exit(1);
        }
        else anaMenu();
}
