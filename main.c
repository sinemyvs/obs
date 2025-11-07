//Saliha Yilmaz[200201056]
//Sinem Yavas[200201066]
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
FILE * yedek;
FILE * dosya;
FILE * index;
struct ogrenci{
    long int ogrNo;
    int dersKodu;
    int puan;
    int * ogrNoAdres;
};
int main()
{
    int secim;
    while(1)
    {
        printf("\n1. Veri dosyasini goster\n");
        printf("2. Kayit Ekle\n");
        printf("3. Kayit Bul\n");
        printf("4. Kayit Sil\n");
        printf("5. Kayit Guncelle\n");
        printf("6. Index Dosyasini Olustur\n");
        printf("7. Index Dosyasini Sil\n");
        printf("8. Index Dosyasini Goster\n");
        printf("0. Cikis\n");
        printf("\nSecim: ");
        scanf("%d",&secim);
        switch(secim)
        {
        case 0:
            exit(0);
        case 1:
        {
            veriDosyasiniGoster();
            break;
        }
        case 2:
            {
                kayit_ekle();
                break;
            }
        case 3:
            {
                kayit_bul();
                break;
            }
        case 4:
            {
                kayit_sil();
                break;
            }
        case 5:
            {
                kayit_guncelle();
                break;
            }
        case 6:
            {
                indexDosyasiniOlustur("kayit.bin","test.txt");
                break;
            }
        case 7:
            {
               indexDosyasiniSil();
                break;
            }
        case 8:
            {
                indexDosyasiniGoster();
                break;
            }
        default:
            printf("\nYanlis secim...\n");
        }
    }
    return 0;
}
int indexDosyasiniOlustur(char* rafname,char* txtname)
{
    FILE *dosya, *indeks;
    int n;
    printf("\nKac Adet Veri Girdiniz ?: ");
    scanf("%d",&n);
    struct ogrenci p,s[n],t;
    int i,j;
    if ((dosya = fopen("kayit.bin","rb")) == NULL)
        return 0;
    if ((indeks = fopen("test.txt","wt")) == NULL)
    {
        fclose(dosya);
        return 0;
    }
    for(i=0; i<n; i++)
    {
        fread(&s[i],sizeof(s),1,dosya);
    }
    int x,y;
    for(x=0;x<(n-1);x++)
    {
        for(y=0;y<n-x-1;y++)
        {
            if(s[y].ogrNo>s[y+1].ogrNo)
            {
                t= s[y];
                s[y]= s[y+1];
                s[y+1]=t;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        fprintf(indeks,"%d\t%d\t%d\n",s[i].ogrNo,s[i].dersKodu,s[i].puan);
    }
    fclose(indeks);
    fclose(dosya);
    return 1;
}
void kayit_ekle(void)
{
    struct ogrenci * ogr = (struct ogrenci * ) malloc( sizeof(struct ogrenci ));
    dosya = fopen("kayit.bin" , "a+b");
    if(dosya != NULL)
    {
        printf("Ogrenci No: ");
        scanf("%d", &ogr->ogrNo);
        ogr->ogrNoAdres = &ogr->ogrNo;
        printf("Ders Kodu: ");
        scanf("%d", &ogr->dersKodu);
        printf("Puan: ");
        scanf("%d", &ogr->puan);
        fwrite(ogr,sizeof(struct ogrenci),1,dosya);
        printf("\nKayit islemi tamamlandi...\n");
        fclose(dosya);
    }
}
void veriDosyasiniGoster(void)
{
    struct ogrenci ogr;
    dosya = fopen("kayit.bin", "rb");
    if(dosya!=NULL)
    {
        fread(&ogr,sizeof(struct ogrenci),1,dosya);
        while(!feof(dosya))
        {
            printf("\n%d\t%d\t%d",ogr.ogrNo,ogr.dersKodu,ogr.puan);
            fread(&ogr,sizeof(struct ogrenci),1,dosya);
        }
        fclose(dosya);
        printf("\nKayitlar listelendi...\n");
    }
}
void kayit_sil(void)
{
    int durum=0;
    struct ogrenci ogr;
    FILE *dosya, *yedek;
    long int ogrNo;
    printf("\nSilmek istediginiz ogrencinin numarasini giriniz: ");
    scanf("%d",&ogrNo);
    dosya = fopen("kayit.bin","rb");
    yedek = fopen("yedek.bin","wb");
    while(fread(&ogr,sizeof(struct ogrenci),1,dosya))
        {
            if(ogr.ogrNo == ogrNo)
            {
                durum = 1;
            }

            else
                fwrite(&ogr,sizeof(struct ogrenci),1,yedek);
        }
    fclose(dosya);
    fclose(yedek);
    if(durum)
        {
            dosya = fopen("kayit.bin","wb");
            yedek = fopen("yedek.bin","rb");
            while(fread(&ogr,sizeof(struct ogrenci),1,yedek))
            {
                fwrite(&ogr,sizeof(struct ogrenci),1,dosya);
            }
            fclose(dosya);
            fclose(yedek);
        }
    else
        printf("\nOgrenci bulunamadi...\n");
}
void kayit_guncelle(void)
{
    int durum=0;
    struct ogrenci ogr;
    FILE *dosya, *yedek;
    long int ogrNo;
    int puan;
    printf("\nGuncellemek istediginiz ogrencinin numarasini giriniz: ");
    scanf("%d",&ogrNo);
    dosya = fopen("kayit.bin","rb");
    yedek = fopen("yedek.bin","wb");
    while(fread(&ogr,sizeof(struct ogrenci),1,dosya))
        {
            if(ogr.ogrNo == ogrNo)
            {
                durum = 1;
                printf("Yeni puani giriniz: ");
                scanf("%d",&ogr.puan);
            }
            fwrite(&ogr,sizeof(struct ogrenci),1,yedek);
        }
    fclose(dosya);
    fclose(yedek);
    if(durum)
    {
            dosya = fopen("kayit.bin","wb");
            yedek = fopen("yedek.bin","rb");
            while(fread(&ogr,sizeof(struct ogrenci),1,yedek))
            {
                fwrite(&ogr,sizeof(struct ogrenci),1,dosya);
            }
            fclose(dosya);
            fclose(yedek);
    }
    else
        printf("\nOgrenci bulunamadi...\n");
}
void kayit_bul(void)
{
    int durum=0;
    struct ogrenci ogr;
    FILE *dosya;
    long int ogrNo;
    printf("\nAramak istediginiz ogrencinin numarasini giriniz: ");
    scanf("%d",&ogrNo);
    dosya = fopen("kayit.bin","rb");
    while(fread(&ogr,sizeof(struct ogrenci),1,dosya))
        {
            if(ogr.ogrNo == ogrNo)
            {
                durum = 1;
                printf("%d\t%d\t%d\n",ogr.ogrNo,ogr.dersKodu,ogr.puan);
            }
        }
    if(!durum)
        {
            printf("\nOgrenci bulunamadi...\n");
        }
    fclose(dosya);
}
void indexDosyasiniSil()
{
    if (remove("test.txt") == 0)
        printf("\nDosya silme islemi basarili!\n");
    else
        printf("\nDosya silme islemi basarisiz!\n");
    return 0;
}
void indexDosyasiniGoster()
{
    struct ogrenci ogr;
    index=fopen("test.txt","r");
    if(index == NULL)
        printf("\nDosyaya ulasilamadi...\n");
    else
    {
        while(fscanf(index,"%d\t%d\t%d\n",&ogr.ogrNo,&ogr.dersKodu,&ogr.puan)!=EOF)
        {
            printf("%d\t%d\t%d\n",ogr.ogrNo,ogr.dersKodu,ogr.puan);
        }
    }
}
