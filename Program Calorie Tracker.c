#include <stdio.h>
#include <unistd.h>

float hitungkaloriharian(char kelamin, float usia, float tinggi, float berat, int aktivitas) {
    float pengali = 0;
    float TDEE;
    float BMR = 0;
    switch (aktivitas) {
        case 1:
            pengali = 1.2;
            break;
        case 2:
            pengali = 1.375;
            break;
        case 3:
            pengali = 1.55;
            break;
        case 4:
            pengali = 1.725;
            break;
        case 5:
            pengali = 1.9;
            break;
        default:
            printf("Maaf, pilihan tingkat aktivitas tidak tersedia");
            return 0;
    }
    // PERHITUNGAN KEBUTUHAN KALORI BERDASARKAN RUMUS HARRIS-BENEDICT
    // INFO: BMR (BASAL METABOLIC RATE) adalah kebutuhan kalori dasar yang dibutuhkan tubuh untuk menjalankan fungsi-fungsi dasar tubuh
    if (kelamin == 'L' || kelamin == 'l') {
        BMR = (88.362 + (13.397 * berat)) + (4.799 * tinggi) - (5.677 * usia);
    } else if (kelamin == 'P' || kelamin == 'p') {
        BMR = (447.593 + (9.247 * berat)) + (3.098 * tinggi) - (4.33 * usia);
    } else {
        printf("Maaf, pilihan jenis kelamin tidak tersedia\n");
        return 0;
    }
    // INFO: TDEE (ACTIVITY METABOLIC RATE) adalah kebutuhan kalori yang dibutuhkan tubuh berdasarkan tingkat aktivitas
    TDEE = BMR * pengali;
    return TDEE;
}

float hitungkalorimakanan(float karbohidrat, float protein, float lemak, float alkohol) {
    float kaloriKarbohidrat = karbohidrat * 4; // 4 kalori per gram karbohidrat
    float kaloriProtein = protein * 4;         // 4 kalori per gram protein
    float kaloriLemak = lemak * 9;             // 9 kalori per gram lemak
    float kaloriAlkohol = alkohol * 7;         // 7 kalori per gram alkohol
    return kaloriKarbohidrat + kaloriProtein + kaloriLemak + kaloriAlkohol;
}

void hitungBMI() {
    float berat, tinggi, BMI;
    printf("Berat badan (kg): ");
    while (scanf("%f", &berat) != 1 || berat <= 0) {
        printf("Maaf, input tidak valid. Silahkan input berat badan (kg): ");
        while (getchar() != '\n');
    }
    printf("Tinggi badan (cm): ");
    while (scanf("%f", &tinggi) != 1 || tinggi <= 0) {
        printf("Maaf, input tidak valid. Silahkan input tinggi badan (cm): ");
        while (getchar() != '\n');
    }
    tinggi = tinggi / 100; /*Ubah cm ke m*/
    BMI = berat / (tinggi * tinggi);
    if (BMI < 18.5) {
        printf("Peringatan: Anda kekurangan berat badan\n");
    } else if (BMI >= 18.5 && BMI <= 25) {
        printf("Berat badan Anda ideal\n");
    } else if (BMI > 25) {
        printf("Peringatan: Anda kelebihan berat badan\n");
    }
    
    if (BMI < 18.5 || BMI > 25) {
        float beratmin, beratmax;
        beratmin = 18.5 * (tinggi * tinggi);
        beratmax = 25 * (tinggi * tinggi);
        printf("Range berat badan yang ideal untuk Anda : %.1f - %.1f kg\n", beratmin, beratmax);
    }
}

void informasilatihanfisik() {
    char latihanfisik[15][30] = {
        "Berjalan kaki", "Berenang", "Bersepeda", "Burpees", "High Knees",
        "Jumping Jack", "Jogging", "Lari", "Lunges", "Plank",
        "Pull-up", "Push-up", "Sit-up", "Squat", "Yoga"
    };
    char kalori[15][30] = {
        "200-300", "400-700", "400-600", "500-700", "400-600",
        "300-500", "400-600", "600-900", "300-500", "200-300",
        "300-500", "300-500", "200-300", "300-500", "200-400"
    };
    char manfaat[15][50] = {
        "Meningkatkan kebugaran kardiovaskular", "Melatih seluruh otot tubuh", "Meningkatkan kekuatan otot kaki", "Meningkatkan kekuatan dan daya tahan", "Meningkatkan kekuatan kaki",
        "Meningkatkan kebugaran jantung", "Meningkatkan daya tahan kardiovaskular", "Meningkatkan kekuatan otot kaki dan daya tahan", "Meningkatkan keseimbangan dan stabilitas", "Memperkuat otot inti (core)",
        "Menguatkan otot punggung, lengan, dan bahu", "Menguatkan otot dada, bahu, dan triceps", "Menguatkan otot perut", "Menguatkan otot kaki dan bokong", "Meningkatkan fleksibilitas dan kesehatan mental"
    };
    printf("\n                                      Tabel Informasi Latihan Fisik                                      \n");
    printf("=========================================================================================================\n");
    printf("| No. | Latihan Fisik  | Kalori yang Dibakar per Jam |                      Manfaat                     |\n");
    printf("|-----|----------------|-----------------------------|--------------------------------------------------|\n");
    for (int i = 0; i < 15; i++) {
        printf("| %-3d | %-14s |           %-7s           | %-48s |\n", i+1, latihanfisik[i], kalori[i], manfaat[i]);
    }
    printf("=========================================================================================================\n");
}

int main() {
    int opsi;
    float kebutuhankaloriharian = 0, totalkalorisemuamakanan = 0;
    char ulang = 'n';
    printf("===========================================\n");
    printf("          Program Calorie Tracker          \n");
    printf("===========================================\n");
    do {
        printf("1. Hitung kebutuhan kalori harian\n2. Hitung kalori makanan\n3. Hitung berat badan ideal\n4. Informasi latihan fisik\nSilahkan pilih opsi yang tersedia: ");
        while (scanf("%d", &opsi) != 1 || opsi < 1 || opsi > 4) {
            printf("Maaf, Input tidak valid. Silahkan pilih opsi yang tersedia: ");
            while (getchar() != '\n'); /*Bersihkan input buffer*/
        }
        switch (opsi) {
            case 1: {
                char kelamin;
                float usia, tinggi, berat;
                int aktivitas;
                printf("Jenis kelamin (Laki-laki(L)/Perempuan(P)): ");
                while (scanf(" %c", &kelamin) !=1 || kelamin != 'L' && kelamin != 'l' && kelamin != 'P' && kelamin != 'p') {
                    printf("Maaf, Input tidak valid. Silahkan pilih jenis kelamin (Laki-laki(L)/Perempuan(P)): ");
                    while (getchar() != '\n');
                }
                printf("Usia (tahun): ");
                while (scanf("%f", &usia) != 1 || usia <= 0) {
                    printf("Maaf, input tidak valid. Silahkan input usia (tahun): ");
                    while (getchar() != '\n'); 
                }
                printf("Tinggi badan (cm): ");
                while (scanf("%f", &tinggi) != 1 || tinggi <= 0) {
                    printf("Maaf, input tidak valid. Silahkan input tinggi badan (cm): ");
                    while (getchar() != '\n');
                }
                printf("Berat badan (kg): ");
                while (scanf("%f", &berat) != 1 || berat <= 0) {
                    printf("Maaf, input tidak valid. Silahkan input berat badan (kg): ");
                    while (getchar() != '\n');
                }
                printf("1. Tidak aktif (sedikit atau tidak berolahraga)\n2. Aktif ringan (olahraga 1-3 hari/minggu)\n3. Cukup aktif (olahraga 3-5 hari/minggu)\n4. Aktif (olahraga 6-7 hari/minggu)\n5. Sangat aktif (latihan keras 6-7 hari/minggu)\nTingkat aktivitas: ");
                while (scanf("%d", &aktivitas) != 1 || aktivitas < 1 || aktivitas > 5) {
                    printf("Maaf, Input tidak valid. Silahkan input tingkat aktivitas: ");
                    while (getchar() != '\n');
                }
                kebutuhankaloriharian = hitungkaloriharian(kelamin, usia, tinggi, berat, aktivitas);
                printf("Kebutuhan kalori harian Anda: %.2f kalori\n", kebutuhankaloriharian);
                break;
            }
            case 2: {
                int jumlahmakanan=0;
                printf("Input jumlah makanan: ");
                while (scanf("%d", &jumlahmakanan) != 1 || jumlahmakanan <= 0) {
                    printf("Maaf, input tidak valid. Silahkan input jumlah makanan: ");
                    while (getchar() != '\n');
                }
                char namamakanan[jumlahmakanan][30];
                float karbohidrat [jumlahmakanan], protein [jumlahmakanan], lemak [jumlahmakanan], alkohol [jumlahmakanan], kalorikarbohidrat [jumlahmakanan], kaloriprotein [jumlahmakanan], kalorilemak [jumlahmakanan], kalorialkohol [jumlahmakanan], totalkalorimakanan [jumlahmakanan], totalkalorikarbohidrat = 0, totalkaloriprotein = 0, totalkalorilemak = 0, totalkalorialkohol = 0;
                for (int i = 0; i < jumlahmakanan; i++) {
                    printf("Makanan ke-%d: \n", i+1);
                    printf("Nama makanan: ");
                    scanf(" %[^\n]s", namamakanan[i]);
                    printf("Input jumlah karbohidrat (gram): ");
                    while (scanf("%f", &karbohidrat[i]) != 1 || karbohidrat[i] < 0) {
                        printf("Maaf, input tidak valid. Silahkan input jumlah karbohidrat (gram): ");
                        while (getchar() != '\n'); 
                    }
                    printf("Input jumlah protein (gram): ");
                    while (scanf("%f", &protein[i]) != 1 || protein[i] < 0) {
                        printf("Maaf, input tidak valid. Silahkan input jumlah protein (gram): ");
                        while (getchar() != '\n'); 
                    }
                    printf("Input jumlah lemak (gram): ");
                    while (scanf("%f", &lemak[i]) != 1 || lemak[i] < 0) {
                        printf("Maaf, input tidak valid. Silahkan input jumlah lemak (gram): ");
                        while (getchar() != '\n'); 
                    }
                    printf("Input jumlah alkohol (gram): ");
                    while (scanf("%f", &alkohol[i]) != 1 || alkohol[i] < 0) {
                        printf("Maaf, input tidak valid. Silahkan input jumlah alkohol (gram): ");
                        while (getchar() != '\n'); 
                    }
                    kalorikarbohidrat[i] = karbohidrat[i] * 4;
                    kaloriprotein[i] = protein[i] * 4;
                    kalorilemak[i] = lemak[i] * 9;
                    kalorialkohol[i] = alkohol[i] * 7;
                    totalkalorimakanan[i] = hitungkalorimakanan(karbohidrat[i], protein[i], lemak[i], alkohol[i]);
                    totalkalorikarbohidrat += kalorikarbohidrat[i];
                    totalkaloriprotein += kaloriprotein[i];
                    totalkalorilemak += kalorilemak[i];
                    totalkalorialkohol += kalorialkohol[i];
                    totalkalorisemuamakanan += hitungkalorimakanan(karbohidrat[i], protein[i], lemak[i], alkohol[i]);
                }
                printf("\n                                                   Tabel Informasi Makanan                                                   \n");
                printf("=============================================================================================================================\n");
                printf("| No. |          Nama Makanan          | Kalori Karbohidrat | Kalori Protein | Kalori Lemak | Kalori Alkohol | Total Kalori |\n");
                printf("|-----|--------------------------------|--------------------|----------------|--------------|----------------|--------------|\n");
                for (int i = 0; i < jumlahmakanan; i++) {
                    printf("| %-3d | %-30s |      %-7.2f       |    %-7.2f     |   %-7.2f    |    %-7.2f     |   %-7.2f    |\n", i+1, namamakanan[i], kalorikarbohidrat[i], kaloriprotein[i], kalorilemak[i], kalorialkohol[i], totalkalorimakanan[i]);
                }
                printf("=============================================================================================================================\n");
                if (kebutuhankaloriharian > 0) {
                    if (totalkalorikarbohidrat / kebutuhankaloriharian > 0.65) {
                        printf("Peringatan: Anda kelebihan mengonsumsi karbohidrat.\n");
                    } else if (totalkalorikarbohidrat / kebutuhankaloriharian < 0.45) {
                        printf("Peringatan: Anda kekurangan mengonsumsi karbohidrat.\n");
                    }

                    if (totalkalorilemak / kebutuhankaloriharian > 0.35) {
                        printf("Peringatan: Anda kelebihan mengonsumsi lemak.\n");
                    } else if (totalkalorilemak / kebutuhankaloriharian < 0.20) {
                        printf("Peringatan: Anda kekurangan mengonsumsi lemak.\n");
                    }

                    if (totalkaloriprotein / kebutuhankaloriharian > 0.35) {
                        printf("Peringatan: Anda kelebihan mengonsumsi protein.\n");
                    } else if (totalkaloriprotein / kebutuhankaloriharian < 0.15) {
                        printf("Peringatan: Anda kekurangan mengonsumsi protein.\n");
                    }

                    if (totalkalorialkohol / kebutuhankaloriharian > 0.05) {
                        printf("Peringatan: Anda kelebihan mengonsumsi alkohol.\n");
                    }
                }
                printf("Total kalori dari semua makanan yang Anda konsumsi: %.2f kalori\n", totalkalorisemuamakanan);
                break;
            }
            case 3: {
                hitungBMI();
                break;
            }
            case 4: {
                informasilatihanfisik();
                break;
            }
            default:
                printf("Maaf, pilihan tidak tersedia.\n");
                break;
        }
        printf("\nApakah Anda ingin memilih opsi lain (y/n): ");
        scanf(" %c", &ulang);
        printf("\n");
    } while (ulang == 'y' || ulang == 'Y');

    float perubahanberat, selisihkalori;
    char ubahberat[6][10] = {"-1 kg", "-0.5 kg", "-0.25 kg", "+0.25 kg", "+0.5 kg", "+1 kg"};
    float kaloriubahberat[6] = {-1100, -550, -275, 275, 550, 1100};
    if (kebutuhankaloriharian > 0) {
        selisihkalori = kebutuhankaloriharian - totalkalorisemuamakanan;
        // INFO: Kenaikan berat badan 1 kg setara dengan kelebihan sebanyak 7700 kalori, begitupun sebaliknya.
        if (selisihkalori > 0) {
            printf("Sisa kalori harian yang diperlukan : %.2f kalori\n", selisihkalori);
            perubahanberat = (selisihkalori) / 7700;
            printf("Berat badan Anda berpotensi berkurang sebanyak: %.2f kg\n", perubahanberat);
        } else if (selisihkalori < 0) {
            printf("Anda telah mengonsumsi kalori melebihi batas sebanyak: %.2f kalori\n", -selisihkalori);
            perubahanberat = (-selisihkalori) / 7700;
            printf("Berat badan Anda berpotensi bertambah sebanyak: %.2f kg\n", perubahanberat);
        } else if (selisihkalori == 0) {
            printf("Anda telah mengonsumsi kalori sesuai dengan kebutuhan harian Anda.\n");
        } else {
            printf("Maaf, kebutuhan kalori harian tidak valid.\n");
        }
        printf("\n              Tabel Perubahan Berat Badan              \n");
        printf("========================================================\n");
        printf("| Perubahan berat badan/minggu | Kebutuhan kalori/hari |\n");
        printf("|------------------------------|-----------------------|\n");
        for (int i = 0; i < 6; i++) {
            printf("|           %-8s           |        %-7.2f        |\n", ubahberat[i], kebutuhankaloriharian + kaloriubahberat[i]);
        }
        printf("========================================================\n");
    }

    printf("\nApakah Anda ingin menyimpan riwayat kebutuhan kalori harian dan kalori dari semua makanan ke dalam file? (y/n): ");
    scanf(" %c", &ulang);
    if (ulang == 'y' || ulang == 'Y') {
        FILE *file;
        char filename[100];
        printf("Ketik nama file untuk menyimpan riwayat (misalnya, kalori.txt): ");
        scanf(" %[^\n]s", filename);
        file = fopen(filename, "w");
        if (file == NULL) {
            printf("Gagal menulis dan membuka file.\n");
        } else {
            fprintf(file, "Kebutuhan kalori harian Anda: %.2f kalori\n", kebutuhankaloriharian);
            fprintf(file, "Total kalori dari semua makanan yang Anda konsumsi: %.2f kalori\n", totalkalorisemuamakanan);
            if (kebutuhankaloriharian > 0) {
                if (selisihkalori > 0) {
                    fprintf(file, "\nSisa kalori harian yang diperlukan: %.2f kalori\n", selisihkalori);
                    fprintf(file, "Berat badan berpotensi berkurang sebanyak: %.2f kg\n", perubahanberat);
                } else if (selisihkalori < 0) {
                    fprintf(file, "\nKalori melebihi batas sebanyak: %.2f kalori\n", -selisihkalori);
                    fprintf(file, "Berat badan berpotensi bertambah sebanyak: %.2f kg\n", perubahanberat);
                } else {
                    fprintf(file, "\nKalori sesuai dengan kebutuhan harian.\n");
                }
                fprintf(file, "\n              Tabel Perubahan Berat Badan              \n");
                fprintf(file, "========================================================\n");
                fprintf(file, "| Perubahan berat badan/minggu | Kebutuhan kalori/hari |\n");
                fprintf(file, "|------------------------------|-----------------------|\n");
                for (int i = 0; i < 6; i++) {
                    fprintf(file, "|           %-8s           |        %-7.2f        |\n", ubahberat[i], kebutuhankaloriharian + kaloriubahberat[i]);
                }
                fprintf(file, "========================================================\n");
            }
            fclose(file);
            printf("Riwayat berhasil disimpan ke file %s yang terletak di \"%s\"\n", filename, getcwd(NULL, 0));
        }
    }

    printf("\nTekan enter untuk keluar...");
    getchar();
    getchar();
    return 0;
}