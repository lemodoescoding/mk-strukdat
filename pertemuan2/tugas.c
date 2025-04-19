#include <stdio.h>
#include <string.h>

struct KTP {
  int id;
  char tanggal_lahir[100];
  char alamat[100];
  char nama[50];
};

int jumlah = 0;

struct KTP ktp_array[50];

void tambahData() {
  char nama[50], alamat[100], tgl_lahir[100];
  printf("Input NIK: ");
  scanf("%d", &ktp_array[jumlah].id);

  printf("Input Nama: ");
  scanf(" %[^\n]", nama);

  strncpy(ktp_array[jumlah].nama, nama, 50);

  printf("Input Alamat: ");
  scanf(" %[^\n]", alamat);

  strncpy(ktp_array[jumlah].alamat, alamat, 100);

  printf("Input Tanggal Lahir: ");
  scanf(" %[^\n]", tgl_lahir);

  strncpy(ktp_array[jumlah].tanggal_lahir, tgl_lahir, 100);

  jumlah++;

  printf("Berhasil menambahkan data!\n");
}

void cariData() {
  int id, i;
  printf("Input ID KTP yang ingin dicari: ");
  scanf("%d", &id);

  printf(
      "\n---------------------------------------------------------------------"
      "------------------------------\n");
  printf("No\tNIK\t\tNama\t\t\t\tTanggal Lahir\t\t\tAlamat\n");
  printf("--------------------------------------------------------------------"
         "-------------------------------\n");

  for (i = 0; i < jumlah; i++) {
    if (ktp_array[i].id == id) {
      printf("%d\t%10d\t%-25s\t%-20s\t%s\n", i + 1, ktp_array[i].id,
             ktp_array[i].nama, ktp_array[i].tanggal_lahir,
             ktp_array[i].alamat);

      return;
    }
  }

  printf("Data dengan ID tersebut tidak ditemukan!\n");
  return;
}

void tampilData() {
  if (jumlah == 0) {
    printf("Tidak ada data yang tersimpan!\n");
    return;
  }

  int i;
  printf(
      "\n---------------------------------------------------------------------"
      "------------------------------\n");
  printf("No\tNIK\t\tNama\t\t\t\tTanggal Lahir\t\t\tAlamat\n");
  printf("--------------------------------------------------------------------"
         "-------------------------------\n");

  for (i = 0; i < jumlah; i++) {

    printf("%d\t%10d\t%-25s\t%-20s\t%s\n", i + 1, ktp_array[i].id,
           ktp_array[i].nama, ktp_array[i].tanggal_lahir, ktp_array[i].alamat);
  }
}

void hapusData() {
  int id, i;
  if (jumlah == 0) {
    printf("Tidak ada data yang disimpan!");
    return;
  }

  printf("Masukkan ID data yang ingin dihapus: ");
  scanf("%d", &id);

  for (i = 0; i < jumlah; i++) {
    if (ktp_array[i].id == id) {

      for (int j = i; j < jumlah; j++) {
        ktp_array[j] = ktp_array[j + 1];
      }

      printf("Data berhasil dihapus!\n");

      jumlah--;

      return;
    }
  }

  printf("Data tidak ditemukan!");
  return;
}

int main() {
  int choice;
  do {
    printf("\n");
    printf("1. Tambah Data\n");
    printf("2. Cari Data\n");
    printf("3. Tampilkan Data\n");
    printf("4. Hapus Data\n");
    printf("0. Keluar Program\n");

    printf("Pilih: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      tambahData();
      break;
    case 2:
      cariData();
      break;
    case 3:
      tampilData();
      break;
    case 4:
      hapusData();
      break;
    }
  } while (choice != 0);

  printf("Keluar Program!");
  return 0;
}
