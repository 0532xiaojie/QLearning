#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <math.h>


int main()
{
    FILE *dosya;
    char ch;

    int okunan=0,satirSayisi=0;
    int rMatrisi[100][100];
    int i,j,giris,cikis,iterasyon;

    printf("\n\n   ---Q-LEARNING ile LABIRENTTE YOL BULMA---\n\n");
    printf("Baslangic odacik numarasini giriniz = ");
    scanf("%d",&giris);
    printf("\n");
    printf("Hedef odacik numarasini giriniz = ");
    scanf("%d",&cikis);
    printf("\n");
    printf("Iterasyon sayisini giriniz = ");
    scanf("%d",&iterasyon);
    printf("\n");

    dosya=fopen("input44.txt" , "r");

    while(!feof(dosya))
    {
        ch=getc(dosya);
        if(ch=='\n')
        {
            satirSayisi++;
        }

    }

    fclose(dosya);

    for(i=0; i<satirSayisi; i++)
    {
        for(j=0; j<satirSayisi; j++)
        {
            rMatrisi[i][j]=-1;
            printf("%d ",rMatrisi[i][j]);
        }
        printf("\n");
    }

    dosya=fopen("input44.txt" , "r");
    int cevirme=0;
    int cevirsayac=0;
    int rEski=0;
    while(!feof(dosya))
    {
        ch=getc(dosya);
        if(ch!=',' && ch!='\n')
        {
            cevirsayac++;

            if(cevirsayac==2)
            {
                //okunan=okunan-1
                rMatrisi[okunan-1][cevirme]=rEski;
                cevirme=cevirme*10+ch-'0';
            }
            else
            {
               cevirme = ch - '0';
            }

            if(cevirme==cikis)
            {
                rEski= rMatrisi[okunan][cevirme];
                rMatrisi[okunan][cevirme]=100;
            }
            else
            {
                rEski= rMatrisi[okunan][cevirme];
                rMatrisi[okunan][cevirme]=0;
            }
        }
        else
        {
            cevirsayac=0;
        }

        if(ch=='\n')
        {
            okunan++;
        }

    }
    rMatrisi[cikis][cikis]=100;
    fclose(dosya);
    dosya=fopen("outR.txt","w");

    for(i=0; i<okunan; i++)
    {
        for(j=0; j<okunan; j++)
        {
            printf("%d   ",rMatrisi[i][j]);
            fprintf(dosya,"%d    ",rMatrisi[i][j]);
        }
        printf("\n");
        fprintf(dosya,"\n");
    }
    fclose(dosya);


    float qMatrisi[satirSayisi][satirSayisi];

    for(i=0; i<satirSayisi; i++)
    {
        for(j=0; j<satirSayisi; j++)
        {
            qMatrisi[i][j]=0;
        }
    }


    int enBuyuk=0;
    int enBuyukindis=0;
    int durum=giris;
    int aksiyon=0;
    int komsu=0;
    int itrSayac;
    int eskioda=giris;

    for(itrSayac=0; itrSayac<iterasyon; itrSayac++)
    {
        while(1)
        {
            aksiyon=rand()%satirSayisi;
            if(rMatrisi[giris][aksiyon]!=-1)
                break;
        }
        durum=giris;

        while(durum!=cikis)
        {

            eskioda=durum;
            komsu=0;
            enBuyuk=0;
            enBuyukindis=0;
            while(komsu<satirSayisi)
            {

                if(rMatrisi[aksiyon][komsu]!=-1)
                {
                    if(qMatrisi[aksiyon][komsu]>=enBuyuk && aksiyon!=komsu && komsu!=eskioda )
                    {
                        enBuyuk=qMatrisi[aksiyon][komsu];
                        enBuyukindis=komsu;
                    }

                }
                komsu++;
            }

            qMatrisi[durum][aksiyon]=rMatrisi[durum][aksiyon] + 0.8* qMatrisi[aksiyon][enBuyukindis];
            durum=aksiyon;
            aksiyon=enBuyukindis;

        }

    }
    int cikisYolu[satirSayisi];
    int sayac=0;
    cikisYolu[0]=giris;

    printf("\n");
    printf("\n");
    printf("\n");

    dosya=fopen("outQ.txt","w");
    for(i=0; i<okunan; i++)
    {
        for(j=0; j<okunan; j++)
        {
            printf("%f   ",qMatrisi[i][j]);
            fprintf(dosya,"%f   ",qMatrisi[i][j]);
        }
        printf("\n");
        fprintf(dosya,"\n");
    }
    fclose(dosya);
    int enBuyuk2=0;
    int yol;
    int eklenecek=0;
    int s;

    for(s=0; s<satirSayisi; s++)
    {
        for(yol=0; yol<satirSayisi; yol++)
        {
            if(qMatrisi[giris][yol]>enBuyuk2)
            {
                eklenecek=yol;
                enBuyuk2=qMatrisi[giris][eklenecek];
            }
        }
        cikisYolu[s+1]=eklenecek;
        sayac++;
        giris=eklenecek;
        enBuyuk2=0;
        if(eklenecek==cikis)
        {
            break;
        }
    }

    dosya=fopen("outPath.txt","w");
    int a;
    for(a=0; a<sayac+1; a++)
    {
        printf("  %d ",cikisYolu[a]);
        fprintf(dosya,"%d ",cikisYolu[a]);
    }
    fclose(dosya);

    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 600, 600, 0, 0);
    clear_to_color(screen,makecol(170,170,170) );
    int odacik=sqrt(satirSayisi);
    int yatay=100,dikey=100,b;

    for(a=0; a<odacik; a++)
    {
        yatay=100;
        for(b=0; b<odacik; b++)
        {
            rect(screen,yatay,dikey,yatay+75,dikey+75,makecol(0,0,0));
            yatay+=75;
        }
        dikey+=75;
    }

    int v,y,satir,sutun,yatay1,dikey1;
    for(v=0; v<satirSayisi; v++)
    {
        for(y=0; y<satirSayisi; y++)
        {
            yatay1=100,dikey1=100,satir=0,sutun=0;
            if( rMatrisi[v][y]!=-1)
            {
                if(((v<y)) && abs(v-y)<2 )
                {
                    satir+=(y/odacik);
                    sutun+=(y%odacik);

                    yatay1+=(sutun*75);
                    dikey1+=(satir*75);

                    vline(screen,yatay1,dikey1,dikey1+75,makecol(170,170,170));
                }


                else if(((v<y)) && (!abs(v-y)<2) )
                {
                    satir+=(y/odacik);
                    sutun+=(y%odacik);
                    yatay1+=(sutun*75);
                    dikey1+=(satir*75);

                    hline(screen,yatay1,dikey1,yatay1+75,makecol(170,170,170));

                }

            }


        }



    }
///////////////////////////////////////////////   GIRIS-CIKIS    //////////////////////////////////////////////////
    satir=cikisYolu[0]/odacik;
    sutun=cikisYolu[0]%odacik;
    yatay1+=sutun*75;
    dikey1+=satir*75;
    if(cikisYolu[0]%odacik==0 || cikisYolu[0]%odacik==2)
    {
        vline(screen,yatay1,dikey1,dikey1+75,makecol(170,170,170));

    }else
    {
        hline(screen,yatay1,dikey1,yatay1+75,makecol(170,170,170));
    }

//////////////////////////////////////////////////////////////////////////////////////
    int cikisSatir,cikisSutun,cikisYatay=100,cikisDikey=100;
    cikisSatir=giris/odacik;
    cikisSutun=giris%odacik;
    cikisYatay+=cikisSutun*75;
    cikisDikey+=cikisSatir*75;
    if(giris%odacik==odacik-1)
    {
        vline(screen,cikisYatay+75,cikisDikey,cikisDikey+75,makecol(170,170,170));
        hline(screen,cikisYatay+33,cikisDikey+33,cikisYatay+75,makecol(183,2,34));
    }
    else if(giris%odacik==0)
    {
        vline(screen,cikisYatay,cikisDikey,cikisDikey+75,makecol(170,170,170));
        hline(screen,cikisYatay+33,cikisDikey+33,cikisYatay,makecol(183,2,34));

    }
    else
    {
        hline(screen,cikisYatay,cikisDikey+75,cikisYatay+75,makecol(170,170,170));
        vline(screen,cikisYatay+33,cikisDikey+33,cikisDikey+75,makecol(183,2,34));
    }


///////////////////////////////////////////////   YOL    //////////////////////////////////////////////////

   int yoll=0,yolYatay=100,yolDikey=100,yollYatay=100,yollDikey=100,yolSatir,yolSutun,yolSatirr,yolSutunn;
    while(cikisYolu[yoll]!=cikis)
    {
        yolSatir=cikisYolu[yoll]/odacik;
        yolSutun=cikisYolu[yoll]%odacik;
        yolYatay=yolSutun*75+133;
        yolDikey=yolSatir*75+133;

        yolSatirr=cikisYolu[yoll+1]/odacik;
        yolSutunn=cikisYolu[yoll+1]%odacik;
        yollYatay=yolSutunn*75+133;
        yollDikey=yolSatirr*75+133;
        yoll++;
        line(screen,yolYatay,yolDikey,yollYatay,yollDikey,makecol(183,2,34));

    }
    while(!key[KEY_ESC]) {}

    return 0;
}
END_OF_MAIN();
