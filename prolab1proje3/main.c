#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct n
{

    char kelime[100];
    int sayi;
    struct n* next;
} Node;

Node * BasaEkle(Node *d,char  kelimegelen[100],int x)
{
    if(d==NULL)
    {
//bossa ife girer
        d=(Node*)malloc(sizeof(Node));
        d->next=NULL;
        strcpy(d->kelime,kelimegelen);
        d->sayi=x;
        return d;
    }
    else
    {

        //yeni gelen deger var olan deðerden buyukse basa ekleyecek
        Node * gecici=(Node*)malloc(sizeof(Node));
        strcpy(gecici->kelime,kelimegelen);
        gecici->sayi=x;
        gecici->next=d;
        return gecici;


    }
}

Node * ArayaEkle(Node *d, char kelimegelen[100],int x)
{
//araya veya sondan kucukse sona ekler
    Node * gezen=d;
    while(gezen->next!=NULL && gezen->next->sayi > x )
    {
        gezen=gezen->next;
    }

    if(d->sayi<x)
    {
        d=BasaEkle(d,kelimegelen,x);
        return d;

    }
    Node * gecici=(Node*)malloc(sizeof(Node));
    gecici->next=gezen->next;
    gezen->next=gecici;
    strcpy(gecici->kelime,kelimegelen);
    gecici->sayi=x;
    return d;
}


Node * SonaEkle(Node *d, char kelimegelen[100],int x)
{
    Node * gezen=d;
    while(gezen->next!=NULL)
    {
        gezen=gezen->next;
    }
    Node * yeni=(Node*)malloc(sizeof(Node));
    gezen->next=yeni;
    yeni->next=NULL;
    strcpy(yeni->kelime,kelimegelen);
    yeni->sayi=x;
    return d;

}

Node * Ekle(Node *d,char kelimegelen[100],int x)
{

    Node * gezen=d;


    if(d==NULL)
    {
//tamamen bossa
        d=BasaEkle(d,kelimegelen,x);
        return d;
    }

    else
    {
        while(gezen!=NULL)
        {
            if(strcmp(gezen->kelime,kelimegelen)==0)
            {
                //ayni kelime kontrolu
                return d;
            }
            gezen=gezen->next;
        }


        if(d->next==NULL )
        {
//tek eleman varsa
            if(d->sayi<x)
            {
                d=BasaEkle(d,kelimegelen,x);
                return d;
            }
            else
            {
                d=SonaEkle(d,kelimegelen,x);
                return d;
            }
        }
        else
        {
//arayaekle
            d=ArayaEkle(d,kelimegelen,x);
            return d;

        }
    }
}
void EkranaBas(Node *d)
{
    int i=0;
    Node * gezen;
    gezen=d;
    while(gezen!=NULL)
    {
        i++;
        printf("%dinci:   %s  >>>  %d  adet var\n",i,gezen->kelime,gezen->sayi);
        gezen=gezen->next;

    }
}



int kelime_sayici(char kelime[])
{
    FILE*f=fopen("deneme.txt", "r");
    int i=0;
    char c;
    char kelimeler[1000000];
    while((c = fgetc(f)) != EOF) // dosyayayı diziye atma
    {
        kelimeler[i]=c;

        i++;
    }

    char *okunankelime=NULL;
    int sayac=0;


    for(okunankelime = strtok(kelimeler," "); okunankelime != NULL; okunankelime = strtok(NULL," \n"))
    {
        if(strcmp(kelime,okunankelime)==0)
        {
            sayac=sayac+1;
        }
    }

    fclose(f);

    return sayac;

}


int main()
{
    Node* root;
    root=NULL;
    FILE*dosya=fopen("deneme.txt", "r");
    char word[100];

    int sayi;

    while(fscanf(dosya,"%s",word)!=EOF) //tek tek kelimelei tutup bağlılisteye ekleme

    {

        sayi=kelime_sayici(word);
        root=Ekle(root,word,sayi);
    }

    fclose(dosya);

    EkranaBas(root);

    return 0;
}
