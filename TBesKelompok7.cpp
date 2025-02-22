/* KELOMPOK 7
    1. Muhamad 'Abid Fakhri Nabiil  (32602400022)
    2. Muhammad Gigeh Wicaksono     (32602400021)
    3. Rintan Audina                (32602400035)     
    4. Marco Syahin Masyhur         (32602400014)
*/
#include <iostream>

using namespace std;
void DataRoti(string nama[], int JmlProduksiPHr[], int ButuhBahanPr[]);
int totalButuhBahan(int JmlProduksiPHr[], int ButuhBahanPr[], int totalBahanPr[]);
void CekBahanCukup(string nama[], int BahanTersedia[], int totalBahanPr[]);
int SisaBahan(int SisaBhnTersediaPr[], int ButuhBahanPr[], int BahanTersedia[]);
void HasilOutput(string nama[], int JmlProduksiPHr[], int ButuhBahanPr[],int BahanTersedia[]);

int JmlJenisRoti; // Variabel untuk menampung jumlah jenis roti dibuat global karena semua fungsi menggunakannya

int main(){

    cout << "======================================================================" << endl;
    cout << "|                  PROGRAM MENGELOLA PRODUKSI ROTI                   |" << endl;
    cout << "======================================================================" << endl;
    do
    {
        cout << "Masukkan jumlah jenis roti\t: ";
        cin >> JmlJenisRoti; // Memasukkan input jumlah jenis roti
        if (JmlJenisRoti < 1) cout << "Jumlah jenis roti minimal 1 jenis..." << endl;
        // Akan terus mengulang jika Jumlah jenis roti kurang dari 1
    } while (JmlJenisRoti < 1);
    
    cout << "======================================================================" << endl;

    // Menyimpan array
    string nama[JmlJenisRoti];
    int JmlProduksiPHr[JmlJenisRoti], ButuhBahanPr[JmlJenisRoti];

    // Memanggil DataRoti yang berisi meminta input data roti
    DataRoti(nama, JmlProduksiPHr, ButuhBahanPr);

    int BahanTersedia[JmlJenisRoti];
    int totalBahanTersedia = 0;

    // Meminta input bahan yang tersedia di pabrik per roti
    cout << "Masukkan jumlah bahan baku yang tersedia (dalam gram) :\n";
    for (int i = 0; i < JmlJenisRoti; i++)
    {
        do // Meminta intput Bahan yang tersedia per roti
        {
            cout << "- Bahan baku untuk " << nama[i] << "\t: ";
            cin >> BahanTersedia[i];
            if (BahanTersedia[i] < 1) cout << " Bahan baku yang tersedia tidak boleh kurang dari 1 gram...." << endl;
            // Akan mengulang jika bahan tersedia kurang dari 1
        } while (BahanTersedia[i] < 1);
        // Total bahan tersedia untuk semua roti
        totalBahanTersedia = totalBahanTersedia + BahanTersedia[i]; 
    }
    cout << "======================================================================" << endl;
    
    // Memanggi fungsi Output
    HasilOutput(nama, JmlProduksiPHr, ButuhBahanPr, BahanTersedia);

    // Meminta input konfirmasi untuk mengulang program atau tidak
    char konfirmasi;
    cout << "\nApakah Anda ingin mengulang program?[Y/n] : ";
    cin >> konfirmasi;
    if (konfirmasi == 'Y' || konfirmasi == 'y')
    {
        main();
    } else return 0;
}

// Fungsi untuk meminta data roti
void DataRoti(string nama[], int JmlProduksiPHr[], int ButuhBahanPr[]){

    for (int i = 0; i < JmlJenisRoti; i++)
    {
        cin.ignore(); // Mengabaikan enter terakhri
        cout << "Masukkan nama jenis roti " << i + 1 << "\t\t\t\t: ";
        getline(cin, nama[i]); // Meminta input nama jenis roti

        do{ // Meminta input jumlah produksi per hari untuk setiap roti
            cout << "Masukkan jumlah produksi roti " << i + 1 << " per hari\t\t: ";
            cin >> JmlProduksiPHr[i];

            // Jika Jumlah produksi per hari kurang dari 0 program tidak akan dilanjut dan mengulang
            // Jika Jumlah produksi per hari sudah lebih dari 0 maka akan bisa lanjut memasukkan bahan yang dibutuhkan
            if (JmlProduksiPHr[i] > 0)
            {
                do // meminta input bahan yang dubituhkan per roti
                {
                    cout << "Masukkan bahan baku yang dibutuhkan roti " << i + 1 << " (dalam gram)\t: ";
                    cin >> ButuhBahanPr[i];
                    if (ButuhBahanPr[i] < 1) {
                        cout << "Bahan yang dibutuhkan tidak boleh kurang dari 1 ..." << endl;
                    }
                } while (ButuhBahanPr[i] < 1); // Cek bahan yang dibutuhkan tidak boleh < 1
            } else{
                // Menampilkan pesan jika jumlah produksi kurang dari 0
                cout << "Jumlah produksi per hari minimal 1 buah" << endl;  
            }
        // Cek jumlah produksi jika < 1 akan mengulang meminta input jumlah produksi per hari
        }while (JmlProduksiPHr[i] < 1);
        cout << "----------------------------------------------------------------------" << endl;
    }
}

// Fungsi untuk menghitung total bahan yang dibutuhkan untuk produksi
int totalButuhBahan(int JmlProduksiPHr[], int ButuhBahanPr[], int totalBahanPr[]){

    // Hitung bahan per roti
    int totalSemuaBahan = 0;
    for (int i = 0; i < JmlJenisRoti; i++)
    {
        totalBahanPr[i] = JmlProduksiPHr[i] * ButuhBahanPr[i]; // Hitung bahan yang dibutuhkan setiap roti
        totalSemuaBahan = totalSemuaBahan + totalBahanPr[i]; // Hitung total keseluruhan bahan yang dibutuhkan
    }
    
    return totalSemuaBahan; // Mengembalikan total seluruh bahan yang dibutuhkan
}

// Fungsi untuk mengecek kecukupan bahan baku
void CekBahanCukup(string nama[], int BahanTersedia[], int totalBahanPr[]){
    
    bool status[JmlJenisRoti]; // Menyimpan status kecukupan bahan baku setiap roti

    for (int i = 0; i < JmlJenisRoti; i++)
    {
        status[i] = BahanTersedia[i] >= totalBahanPr[i]; // Jika bahan tersedia < total bahan per roti maka false
        if (status[i] == false) // Jika false maka akan mengeluarkan pesan roti yang tidak cukup bahan bakunya
        {
            cout << "Bahan baku untuk " << nama[i] << " tidak cukup..." << endl;
        }
    }

}

// Fungsi untuk menghitung sisa bahan baku
int SisaBahan(int SisaBhnTersediaPr[], int totalBahanPr[], int BahanTersedia[]){

    int totalSisaBahan = 0; // Menyimpan sisa bahan
    for (int i = 0; i < JmlJenisRoti; i++)
    {
        SisaBhnTersediaPr[i] = BahanTersedia[i] - totalBahanPr[i]; // Sisa bahan setiap roti
        if (SisaBhnTersediaPr[i] >= 0) // Cek jika sisa bahan tidak < 0 maka akan menotal seluruhnya 
        {
            // Menghitung total sisa bahan
            totalSisaBahan = totalSisaBahan + SisaBhnTersediaPr[i]; 
        }
    }

    return totalSisaBahan; // Mengembalikan nilai total sisa bahan
}

// Fungsi Output
void HasilOutput(string nama[], int JmlProduksiPHr[], int ButuhBahanPr[], int BahanTersedia[]){
    
    // Menampilkan nama jenis roti dan produksi jenis roti per hari
    cout << "\nJumlah produksi per hari untuk setiap roti :\n"; 
    for (int i = 0; i < JmlJenisRoti; i++)
    {
        cout << "- Jumlah produksi per hari untuk " << nama[i] << " : ";
        cout << JmlProduksiPHr[i] << " buah/Hari" << endl; // Menampilkan jumlah produksi setiap rotinya perhari
    }
    cout << "----------------------------------------------------------------------" << endl;

    // Menampilkan bahan baku yang dibutuhkan per jenis roti
    cout << "\nBahan baku yang dibutuhkan per roti :\n";
    for (int i = 0; i < JmlJenisRoti; i++)
    {
        cout << "- Bahan baku yang dibutuhkan untuk satu " << nama[i] << " : ";
        cout << ButuhBahanPr[i] << " gram" << endl; // Menampilkan bahan yang dibutuhkan untuk satu roti
    }
    cout << "----------------------------------------------------------------------" << endl;
    // Menghitung total bahan yang dibutuhkan per roti
    int totalBahanPr[JmlJenisRoti];
    int totalButuhBahanBaku = totalButuhBahan(JmlProduksiPHr, ButuhBahanPr, totalBahanPr); // Memanggil totalButuhBahan

    cout << "\nTotal bahan yang dibutuhkan per roti :\n";
    for (int i = 0; i < JmlJenisRoti; i++)
    {
        cout << "- Bahan yang dibutuhkan untuk produksi " << JmlProduksiPHr[i] << " ";
        cout << nama[i] << " : " << totalBahanPr[i] << " gram" << endl; // Menampilkan total bahan per roti
    }
    cout << "----------------------------------------------------------------------" << endl;
    // Menampilkan jumlah bahan yang tersedia di pabrik per roti
    cout << "\nBahan baku yang tersedia di pabrik :\n";
    for (int i = 0; i < JmlJenisRoti; i++)
    {
        cout << "- Bahan yang tersedia untuk " << nama[i] << "\t: ";
        cout << BahanTersedia[i] << " gram" << endl; // Menampilkan bahan tersedia setiap roti
    }
    cout << "----------------------------------------------------------------------" << endl;


    // Menghitung total bahan yang tersedia di pabrik
    int T_BahanTersedia = 0; // Menyimpan total bahan tersedia
    cout << "\nTotal bahan yang tersedia di pabrik\t: ";
    for (int i = 0; i < JmlJenisRoti; i++)
    {
        T_BahanTersedia = T_BahanTersedia + BahanTersedia[i]; // Menghitung total
    }
    cout << T_BahanTersedia << " gram" << endl; // Menampilkan total

    // Menghitung total keseluruhan bahan yang dibutuhkan
    cout << "Total Keseluruhan bahan yang dibutuhkan\t: ";
    cout << totalButuhBahanBaku << " gram" << endl; // Menampilkan total butuh bahan baku

    cout << "----------------------------------------------------------------------" << endl;

    int SisaBhnTersediaPr[JmlJenisRoti]; // Menyimpan sisa bahan setiap roti
    int sisa = SisaBahan(SisaBhnTersediaPr, totalBahanPr, BahanTersedia); // Memanggil SisaBahan

    // Menampilkan sisa bahan setelah produksi
    cout << "Sisa bahan setelah produksi :\n";
    for (int i = 0; i < JmlJenisRoti; i++)
    {
        if (SisaBhnTersediaPr[i] >= 0)
        {
            cout << "- Sisa bahan baku untuk " << nama[i] << " : ";
            cout << SisaBhnTersediaPr[i] << " gram" << endl;
        }
    }
    cout << "\nTotal sisa bahan baku yang tersedia\t: " << sisa << endl;
    
    CekBahanCukup(nama, BahanTersedia, totalBahanPr); // Memanggil fungsi cek kecukupan bahan baku

}