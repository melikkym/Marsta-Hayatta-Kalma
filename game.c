#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    
    srand(time(NULL));

#pragma region Degiskenler
    int saglik = 100;
    int enerji = 100;
    int oksijen = 100;
    int su = 0;
    int yedekParca = 0;
    int modulHasari = 0;
    int kilitMuhurlu = 0;
    int gun = 1;
    int tur = 0;
    char zorluk;
    char komut;
    int secimGecerli;
    int turGecerliMi;
    int firtinaTurSayisi = 3;
    int zorlukEsikFarki = 0;
    int zar, esik;
    int harcanacakSu, kullanilanSu, uretilenOksijen;
    int i, carpan, anlikHasar, hasarliTur, kayipSaglik, kayipOksijen;
    char dogruSifre, girilenSifre;
    int denemeHakki;
    int puan;
#pragma endregion
#pragma region Baslangic Yazisi   
    printf("==================================================\n");
    printf("   MARS KOLONISI YASAM DESTEK SIMULATORU BASLADI  \n");
    printf("==================================================\n");
#pragma endregion
#pragma region Zorluk Secimi
    do {
        secimGecerli = 1;
        printf("\nZorluk seviyesi seciniz (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &zorluk);

        switch (zorluk) {
            case 'k':
            case 'K':
                su = 16;
                yedekParca = 4;
                modulHasari = 10;
                firtinaTurSayisi = 3;
                zorlukEsikFarki = 0;
                printf(">> Kolay seviye secildi. (Su: %d, Yedek Parca: %d, Hasar: %d)\n", su, yedekParca, modulHasari);
                break;

            case 'n':
            case 'N':
                su = 12;
                yedekParca = 3;
                modulHasari = 25;
                firtinaTurSayisi = 5;
                zorlukEsikFarki = 10;
                printf(">> Normal seviye secildi. (Su: %d, Yedek Parca: %d, Hasar: %d)\n", su, yedekParca, modulHasari);
                break;

            case 'z':
            case 'Z':
                su = 8;
                yedekParca = 2;
                modulHasari = 45;
                firtinaTurSayisi = 7;
                zorlukEsikFarki = 20;
                printf(">> Zor seviye secildi. (Su: %d, Yedek Parca: %d, Hasar: %d)\n", su, yedekParca, modulHasari);
                break;

            default:
                printf("[UYARI] Gecersiz zorluk seviyesi! Lutfen K, N veya Z giriniz.\n");
                secimGecerli = 0;
                break;
        }
    } while (secimGecerli == 0);
#pragma endregion
#pragma region Ana Dongu
    do {
        turGecerliMi = 1;

        printf("\n--------------------------------------------------\n");
        printf("[GUN: %d | TUR: %d] Saglik: %d | Enerji: %d | Oksijen: %d | Su: %d | Parca: %d | Hasar: %d | Kilit: %d\n",
               gun, tur, saglik, enerji, oksijen, su, yedekParca, modulHasari, kilitMuhurlu);
        printf("Komutlar -> [G]Kesif [O]Oksijen [T]Tamir [D]Durum [U]Uyu [K]Firtina [H]Hava Kilidi [Q]Cikis\n");
        printf("Komutunuz: ");
        scanf(" %c", &komut);

        switch (komut) {
           
            case 'g':
            case 'G':
                if (enerji < 15) {
                    printf("[IPTAL] Kesif icin yeterli enerjiniz yok! (Gereken: 15, Mevcut: %d)\n", enerji);
                    turGecerliMi = 0;
                } else {
                   
                    if (enerji > 40 && oksijen > 30) {
                        esik = 65 - zorlukEsikFarki;
                    } else {
                        esik = 40 - zorlukEsikFarki;
                    }

                    enerji = enerji - 15;
                    oksijen = oksijen - 10;
                    printf(">> Kesfe cikildi (-15 Enerji, -10 Oksijen).\n");

                    zar = rand() % 100;
                    if (zar < esik) {
                        printf("Zar: %d / Esik: %d -> BASARILI (Su Bulundu!)\n", zar, esik);
                        su = su + 4;
                        printf(">> Kesif sonucu 4 birim su buldunuz!\n");
                    } else if (zar < esik + 25) {
                        printf("Zar: %d / Esik: %d -> KISMI BASARI (Yedek Parca Bulundu!)\n", zar, esik + 25);
                        yedekParca = yedekParca + 1;
                        printf(">> Kesif sonucu 1 adet yedek parca buldunuz!\n");
                    } else {
                        printf("Zar: %d / Esik: %d -> BASARISIZ (Eli Bos Donuldu)\n", zar, esik + 25);
                        printf(">> Kesiften eliniz bos dondunuz.\n");
                    }

                    zar = rand() % 100;
                    esik = 10;
                    if (zar < esik || modulHasari > 70) {
                        printf("Yaralanma Kontrolu -> Zar: %d / Esik: %d (Modul Hasari: %d) -> YARALANDINIZ!\n", zar, esik, modulHasari);
                        saglik = saglik - 15;
                        printf(">> Kesif sirasinda kaza gecirdiniz! (-15 Saglik)\n");
                    } else {
                        printf("Yaralanma Kontrolu -> Zar: %d / Esik: %d -> GUVENLI DONUS\n", zar, esik);
                    }
                }
                break;

            case 'o':
            case 'O':
                if (enerji < 10) {
                    printf("[IPTAL] Oksijen uretimi icin yeterli enerjiniz yok! (Gereken: 10, Mevcut: %d)\n", enerji);
                    turGecerliMi = 0;
                } else if (su < 2) {
                    printf("[IPTAL] Oksijen uretimi icin en az 2 birim su gereklidir! (Mevcut Su: %d)\n", su);
                    turGecerliMi = 0;
                } else {
                    printf("Oksijen uretimi icin kac birim su harcamak istiyorsunuz? (Mevcut Su: %d): ", su);
                    scanf("%d", &harcanacakSu);

                    if (harcanacakSu > su || harcanacakSu < 2) {
                        printf("[IPTAL] Gecersiz su miktari! En az 2, en fazla mevcut suyunuz (%d) kadar girebilirsiniz.\n", su);
                        turGecerliMi = 0;
                    } else {
                        enerji = enerji - 10;

                        if (harcanacakSu % 2 == 0) {
                            kullanilanSu = harcanacakSu;
                        } else {
                            kullanilanSu = harcanacakSu - 1;
                            printf(">> Girilen su miktari tek sayi oldugu icin 1 birim su depoda artik olarak kaldi.\n");
                        }

                        su = su - kullanilanSu;
                        uretilenOksijen = (kullanilanSu / 2) * 3;
                        oksijen = oksijen + uretilenOksijen;

                        printf(">> %d birim su kullanilarak %d birim oksijen uretildi (-10 Enerji).\n", kullanilanSu, uretilenOksijen);
                    }
                }
                break;

            case 't':
            case 'T':
                if (enerji < 10) {
                    printf("[IPTAL] Tamir icin yeterli enerjiniz yok! (Gereken: 10, Mevcut: %d)\n", enerji);
                    turGecerliMi = 0;
                } else if (yedekParca <= 0) {
                    printf("[IPTAL] Yedek parcaniz olmadigi icin tamir yapilamaz!\n");
                    turGecerliMi = 0;
                } else if (modulHasari == 0) {
                    printf("[IPTAL] Modulde herhangi bir hasar yok!\n");
                    turGecerliMi = 0;
                } else {
                    enerji = enerji - 10;

                    if (modulHasari <= 30) {
                        yedekParca = yedekParca - 1;
                        modulHasari = modulHasari - 15;
                        printf(">> [Hafif Hasar] 1 yedek parca harcandi, 15 birim hasar onarildi (-10 Enerji).\n");
                    } else if (modulHasari <= 70) {
                        if (yedekParca >= 2) {
                            yedekParca = yedekParca - 2;
                            modulHasari = modulHasari - 30;
                            printf(">> [Orta Hasar] 2 yedek parca harcandi, 30 birim hasar onarildi (-10 Enerji).\n");
                        } else {
                            yedekParca = yedekParca - 1;
                            modulHasari = modulHasari - 15;
                            printf(">> [Orta Hasar - Kisitli Parca] 1 yedek parca harcandi, 15 birim hasar onarildi (-10 Enerji).\n");
                        }
                    } else {
                        if (yedekParca >= 3) {
                            yedekParca = yedekParca - 3;
                            modulHasari = modulHasari - 45;
                            printf(">> [Agir Hasar] 3 yedek parca harcandi, 45 birim hasar onarildi (-10 Enerji).\n");
                        } else {
                            modulHasari = modulHasari - (yedekParca * 15);
                            printf(">> [Agir Hasar - Kisitli Parca] %d yedek parca harcandi, %d birim hasar onarildi (-10 Enerji).\n", yedekParca, yedekParca * 15);
                            yedekParca = 0;
                        }
                    }
                }
                break;

            case 'd':
            case 'D':
                turGecerliMi = 0;
                printf("\n================ DURUM RAPORU ================\n");
                printf("Gun           : %d / 15\n", gun);
                printf("Toplam Tur    : %d\n", tur);
                printf("Saglik        : %d / 100\n", saglik);
                printf("Enerji        : %d / 100\n", enerji);
                printf("Oksijen       : %d / 100\n", oksijen);
                printf("Su Miktari    : %d birim\n", su);
                printf("Yedek Parca   : %d adet\n", yedekParca);
                printf("Modul Hasari  : %d / 100\n", modulHasari);
                printf("Hava Kilidi   : %s\n", (kilitMuhurlu == 1) ? "Muhurlu (1)" : "Acik (0)");
                printf("----------------------------------------------\n");

                if (oksijen < 25) {
                    printf("[KRITIK UYARI] Oksijen seviyesi kritik duzeyde (< 25)!\n");
                }
                if (saglik < 30) {
                    printf("[KRITIK UYARI] Saglik seviyesi kritik duzeyde (< 30)!\n");
                }
                if (modulHasari > 70) {
                    printf("[KRITIK UYARI] Modul hasari tehlikeli boyutta (> 70)!\n");
                }

                if (oksijen >= 25 && saglik >= 30 && modulHasari <= 70) {
                    printf("[DURUM] TUM SISTEMLER NORMAL\n");
                }
                printf("==============================================\n");
                break;

            case 'u':
            case 'U':
                enerji = enerji + 30;
                oksijen = oksijen - 8;
                printf(">> Dinlenmeye gecildi (+30 Enerji, -8 Oksijen).\n");

                if (enerji > 0) {
                    if (oksijen < 20) {
                        saglik = saglik - 10;
                        printf("[TEHLIKE] Oksijen 20'nin altinda oldugu icin uyurken sagliginiz azaldi! (-10 Saglik)\n");
                    } else {
                        saglik = saglik + 15;
                        printf(">> Kaliteli uyku sayesinde sagliginiz artti (+15 Saglik).\n");
                    }
                }
                break;

            case 'k':
            case 'K':
                if (enerji < 10) {
                    printf("[IPTAL] Kum firtinasina karsi koymak icin yeterli enerjiniz yok! (Gereken: 10)\n");
                    turGecerliMi = 0;
                } else {
                    enerji = enerji - 10;
                    hasarliTur = 0;
                    kayipSaglik = 0;
                    kayipOksijen = 0;
                    esik = 70 - zorlukEsikFarki;

                    printf("\n>> Kum Firtinasi Basladi! Toplam %d tur surecek (-10 Enerji).\n", firtinaTurSayisi);

                    for (i = 1; i <= firtinaTurSayisi; i++) {
                        zar = rand() % 100;

                        if (i % 2 == 0) {
                            carpan = 2;
                            printf("[Firtina Tur %d - Siddetli Ruzgar (2x Hasar)] ", i);
                        } else {
                            carpan = 1;
                            printf("[Firtina Tur %d] ", i);
                        }

                        if (zar < 25) {
        
                            printf("Zar: %d / Esik: 25 -> OKSIJEN SIZINTISI TEHLIKESI!\n", zar);
                            if (kilitMuhurlu == 1) {
                                printf("   -> Hava kilidi muhurlu oldugu icin oksijen sizintisi engellendi.\n");
                                continue;
                            }
                            anlikHasar = 6 * carpan;
                            oksijen = oksijen - anlikHasar;
                            kayipOksijen = kayipOksijen + anlikHasar;
                            hasarliTur = hasarliTur + 1;
                            printf("   -> Oksijen sizintisi yasandi! (-%d Oksijen)\n", anlikHasar);
                        } else if (zar < 50) {
                            printf("Zar: %d / Esik: 50 -> FIZIKSEL SARSTINTI!\n", zar);
                            anlikHasar = 5 * carpan;
                            saglik = saglik - anlikHasar;
                            kayipSaglik = kayipSaglik + anlikHasar;
                            hasarliTur = hasarliTur + 1;
                            printf("   -> Firtina nedeniyle yaralandiniz! (-%d Saglik)\n", anlikHasar);
                        } else if (zar < esik) {
                            printf("Zar: %d / Esik: %d -> DIS GOVDE DARBESI!\n", zar, esik);
                            anlikHasar = 7 * carpan;
                            modulHasari = modulHasari + anlikHasar;
                            hasarliTur = hasarliTur + 1;
                            printf("   -> Istasyon modulu hasar aldi! (+%d Modul Hasari)\n", anlikHasar);
                        } else {
                            printf("Zar: %d / Esik: %d -> BASARILI KORUNMA (Hasar Alinmadi)\n", zar, esik);
                        }

                        if (saglik <= 0 || oksijen <= 0) {
                            if (saglik < 0) saglik = 0;
                            if (oksijen < 0) oksijen = 0;
                            printf("[KRITIK] Firtina sirasinda hayati degerleriniz tukendi! Firtina dongusu sonlandiriliyor (BREAK)...\n");
                            break;
                        }
                    }

                    printf("\n--- KUM FIRTINASI OZETI ---\n");
                    printf("Hasar Alinan Tur Sayisi : %d\n", hasarliTur);
                    printf("Toplam Kaybedilen Saglik: %d\n", kayipSaglik);
                    printf("Toplam Kaybedilen Oksijen: %d\n", kayipOksijen);
                    printf("---------------------------\n");
                }
                break;

            
            case 'h':
            case 'H':
                if (enerji < 5) {
                    printf("[IPTAL] Hava kilidi panelini kullanmak icin en az 5 enerjiniz olmali!\n");
                    turGecerliMi = 0;
                } else if (kilitMuhurlu == 1) {
                    printf("[BILGI] Hava kilidi zaten muhurlu durumda!\n");
                    turGecerliMi = 0;
                } else {
                    dogruSifre = 'A' + (gun % 26);
                    denemeHakki = 3;

                    printf("\n--- HAVA KILIDI GUVENLIK PANELI ---\n");
                    printf("Ipucu: Sifre, alfabede 'A' harfinden bugunun gun sayisi (%d) kadar ilerideki harftir.\n", gun % 26);

                    do {
                        printf("Sifreyi giriniz (Kalan Hak: %d): ", denemeHakki);
                        scanf(" %c", &girilenSifre);

                        if (girilenSifre >= 'a' && girilenSifre <= 'z') {
                            girilenSifre = girilenSifre - 32;
                        }

                        if (girilenSifre != dogruSifre) {
                            denemeHakki = denemeHakki - 1;
                            enerji = enerji - 5;
                            if (enerji < 0) enerji = 0;

                            printf("[HATALI SIFRE] Enerjiniz 5 azaldi. ");
                            if (girilenSifre < dogruSifre) {
                                printf("Ipucu: Ileri git (Alfabede daha sonraki bir harf).\n");
                            } else {
                                printf("Ipucu: Geri git (Alfabede daha onceki bir harf).\n");
                            }
                        }
                    } while (girilenSifre != dogruSifre && denemeHakki > 0);

                    if (girilenSifre == dogruSifre) {
                        kilitMuhurlu = 1;
                        printf("[BASARILI] Dogru sifre! Hava kilidi basariyla muhurlendi (kilitMuhurlu = 1).\n");
                    } else {
                        modulHasari = modulHasari + 20;
                        printf("[BASARISIZ] 3 deneme hakkiniz da bitti! Basinc dalgasi nedeniyle modul hasari 20 artti.\n");
                    }
                }
                break;

            case 'q':
            case 'Q':
                turGecerliMi = 0;
                printf("\n>> Simulasyondan cikis komutu verildi...\n");
                break;

            default:
                turGecerliMi = 0;
                printf("[UYARI] Tanimsiz bir komut girdiniz! Bu islem tur harcamadi.\n");
                break;
        }

        if (saglik > 100) saglik = 100;
        if (saglik < 0) saglik = 0;

        if (enerji > 100) enerji = 100;
        if (enerji < 0) enerji = 0;

        if (oksijen > 100) oksijen = 100;
        if (oksijen < 0) oksijen = 0;

        if (modulHasari > 100) modulHasari = 100;
        if (modulHasari < 0) modulHasari = 0;

        if (turGecerliMi == 1 && saglik > 0 && oksijen > 0) {
            tur = tur + 1;

            if (tur % 3 == 0) {
                gun = gun + 1;
                if (gun <= 15) {
                    oksijen = oksijen - 8;
                    printf("\n*** YENI GUN BASLADI (GUN %d) ***\n", gun);
                    printf(">> Gunluk yasam destek tuketimi: -8 Oksijen.\n");

                    if (modulHasari > 70) {
                        saglik = saglik - 5;
                        printf(">> [KRITIK HASAR ETKISI] Modul hasari 70'in uzerinde oldugu icin -5 Saglik kaybettiniz!\n");
                    }

                    if (oksijen < 0) oksijen = 0;
                    if (saglik < 0) saglik = 0;
                }
            }
        }

    } while (komut != 'q' && komut != 'Q' && saglik > 0 && oksijen > 0 && gun <= 15);
#pragma endregion
#pragma region Oyun Sonu
    printf("\n==================================================\n");
    if (saglik <= 0 || oksijen <= 0) {
        printf("   OYUN BITTI: HAYATI DEGERLERINIZ TUKENDI!       \n");
    } else if (gun > 15) {
        gun = 15; 
        printf("   TEBRIKLER! 15 GUN HAYATTA KALDINIZ VE KURTARILDINIZ!\n");
    } else {
        printf("   OYUN BITTI: SIMULASYONDAN CIKIS YAPILDI.       \n");
    }
    printf("==================================================\n");

    puan = (gun * 100) + saglik + oksijen - modulHasari;
#pragma endregion
#pragma region Sonuc Raporu
    printf("Hayatta Kalinan Gun : %d\n", gun);
    printf("Toplam Gecen Tur    : %d\n", tur);
    printf("Son Saglik          : %d\n", saglik);
    printf("Son Enerji          : %d\n", enerji);
    printf("Son Oksijen         : %d\n", oksijen);
    printf("Kalan Su            : %d\n", su);
    printf("Kalan Yedek Parca   : %d\n", yedekParca);
    printf("Son Modul Hasari    : %d\n", modulHasari);
    printf("Hava Kilidi Durumu  : %d\n", kilitMuhurlu);
    printf("--------------------------------------------------\n");
    printf("TOPLAM PUANINIZ     : %d\n", puan);
    printf("==================================================\n");
#pragma endregion
system("pause");
return 0;
}
