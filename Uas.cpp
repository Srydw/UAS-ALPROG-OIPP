#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Struktur untuk menyimpan informasi makanan
struct Makanan {
    string nama;
    int harga;
    int stok;
};

// Deklarasi menu makanan
const int MAX_MENU = 5;
Makanan menu[MAX_MENU] = {
    {"Resol mayo", 2500, 20},
    {"Mie Goreng", 5000, 7},
    {"Gorengan 3x", 2000, 33},
    {"Jeroan", 4000, 12},
    {"Aneka ES", 3000, 50}
};

// Fungsi untuk menampilkan menu
void tampilkanMenu() {
    cout << "=== Menu Kantin OIPP ===" << endl;
    for (int i = 0; i < MAX_MENU; i++) {
        cout << i + 1 << ". " << menu[i].nama 
            << " - Rp " << menu[i].harga 
            << " (Stok: " << menu[i].stok << ")" << endl;
    }
}

// Fungsi untuk input makanan
void inputMakanan(vector<int> &pilihan, vector<int> &jumlah) {
    int p, j;
    char lanjut;
    do {
        cout << "Masukkan nomor makanan: ";
        cin >> p;
        cout << "Masukkan jumlah: ";
        cin >> j;
        pilihan.push_back(p);
        jumlah.push_back(j);

        cout << "Apakah Anda ingin menambah menu lain? (y/n): ";
        cin >> lanjut;
    } while (lanjut == 'y' || lanjut == 'Y');
}

// Fungsi untuk validasi stok
bool validasiStok(const vector<int> &pilihan, const vector<int> &jumlah) {
    for (size_t i = 0; i < pilihan.size(); i++) {
        if (menu[pilihan[i] - 1].stok < jumlah[i]) {
            return false;
        }
    }
    return true;
}

// Fungsi untuk menghitung total harga
int hitungTotalHarga(const vector<int> &pilihan, const vector<int> &jumlah) {
    int total = 0;
    for (size_t i = 0; i < pilihan.size(); i++) {
        total += menu[pilihan[i] - 1].harga * jumlah[i];
    }
    return total;
}

// Fungsi untuk menerapkan diskon
double terapkanDiskon(int total) {
    if (total > 50000) {
        return total * 0.9; // Diskon 10%
    } else if (total > 30000) {
        return total * 0.95; // Diskon 5%
    }
    return total; // Tanpa diskon
}

// Fungsi untuk melakukan pembayaran
void pembayaran(double total) {
    cout << "Total Pembayaran: Rp " << fixed << setprecision(2) << total << endl;
    cout << "Pembayaran berhasil!" << endl;
}

// Fungsi untuk mencetak struk pembelian
void strukPembelian(const vector<int> &pilihan, const vector<int> &jumlah, double total) {
    cout << "\n=== Struk Pembelian ===" << endl;
    for (size_t i = 0; i < pilihan.size(); i++) {
        cout << "Makanan: " << menu[pilihan[i] - 1].nama << endl;
        cout << "Jumlah: " << jumlah[i] << endl;
    }
    cout << "Total: Rp " << fixed << setprecision(2) << total << endl;
}

int main() {
    cout << "==================================================\n";
    cout << "  _  __         _   _         ___ ___ ___ ___  \n";
    cout << " | |/ /__ _ _ _| |_(_)_ _    / _ \\_ _| _ \\ _ \\ \n";
    cout << " | ' </ _` | ' \\  _| | ' \\  | (_) | ||  _/  _/ \n";
    cout << " |_|\\_\\__,_|_||_\\__|_|_||_|  \\___/___|_| |_|   \n\n";
    cout << "==================================================\n";

    char lanjut;
    do {
        tampilkanMenu();
        vector<int> pilihan;
        vector<int> jumlah;

        inputMakanan(pilihan, jumlah);

        if (validasiStok(pilihan, jumlah)) {
            for (size_t i = 0; i < pilihan.size(); i++) {
                menu[pilihan[i] - 1].stok -= jumlah[i]; // Kurangi stok
            }
            int total = hitungTotalHarga(pilihan, jumlah);
            double totalDiskon = terapkanDiskon(total);
            strukPembelian(pilihan, jumlah, totalDiskon);
            pembayaran(totalDiskon);
        } else {
            cout << "Stok tidak mencukupi!" << endl;
        }

        cout << "Apakah Anda ingin membeli lagi? (y/n): ";
        cin >> lanjut;

    } while (lanjut == 'y' || lanjut == 'Y');

    return 0;
}
