#include <iostream>
using namespace std;

struct nodeQueue {
  int kode;
  string nama;
  nodeQueue* next;
};

struct nodeStack {
  int kode;
  string nama;
  nodeStack* next;
};

struct nodeTree {
  int kode;
  string nama;
  nodeTree* kiri;
  nodeTree* kanan;
};

nodeQueue* front = NULL;
nodeQueue* last = NULL;
nodeStack* top = NULL;
nodeTree* root = NULL;

// menambahkan node baru ke tree berdasarkan kode
nodeTree* tambah_tree(nodeTree* akar, int kode, string nama) {
  if (akar == NULL) {
    return new nodeTree{kode, nama, NULL, NULL};
  }
  if (kode < akar->kode) {
    akar->kiri = tambah_tree(akar->kiri, kode, nama);
  } else {
    akar->kanan = tambah_tree(akar->kanan, kode, nama);
  }
  return akar;
}

// mencari node di tree berdaarkan kode
nodeTree* cari_tree(nodeTree* akar, int kode) {
  if (akar == NULL || akar->kode == kode) {
    return akar;
  }
  if (kode < akar->kode) {
    return cari_tree(akar->kiri, kode);
  }
  return cari_tree(akar->kanan, kode);
}

// menghapus node di tree berdasarkan kode
nodeTree* hapus_tree(nodeTree* akar, int kode) {
  if (akar == NULL) {
    return NULL;
  }
  if (kode < akar->kode) {
    akar->kiri = hapus_tree(akar->kiri, kode);
  } else if (kode > akar->kode) {
    akar->kanan = hapus_tree(akar->kanan, kode);
  } else if (akar->kiri == NULL) {
    nodeTree* sisa = akar->kanan;
    delete akar;
    return sisa;
  } else if (akar->kanan == NULL) {
    nodeTree* sisa = akar->kiri;
    delete akar;
    return sisa;
  } else {
    nodeTree* pengganti = akar->kanan;
    while (pengganti->kiri != NULL) {
      pengganti = pengganti->kiri;
    }
    akar->kode = pengganti->kode;
    akar->nama = pengganti->nama;
    akar->kanan = hapus_tree(akar->kanan, pengganti->kode);
  }
  return akar;
}
// menampilkan isi tree

void preorder(nodeTree* akar, int& no) {
  if (akar == NULL) {
    return;
  }
  cout << no << ". [" << akar->kode << "] " << akar->nama << endl;
  no++;
  preorder(akar->kiri, no);
  preorder(akar->kanan, no);
}

void inorder(nodeTree* akar, int& no) {
  if (akar == NULL) {
    return;
  }
  inorder(akar->kiri, no);
  cout << no << ". [" << akar->kode << "] " << akar->nama << endl;
  no++;
  inorder(akar->kanan, no);
}

void postorder(nodeTree* akar, int& no) {
  if (akar == NULL) {
    return;
  }
  postorder(akar->kiri, no);
  postorder(akar->kanan, no);

  cout << no << ". [" << akar->kode << "] " << akar->nama << endl;
  no++;
}

// input nomor kode dan nama tapi memaukan di paling belakang
void tambah_energi() {
  int kode;
  string nama;
  cout << "Masukan kode energi: ";
  cin >> kode;

  if (cin.fail() || kode <= 0) {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Kode energi harus berupa angka lebih dari 0!" << endl << endl;
    return;
  }
  nodeQueue* q = front;
  while (q != NULL) {
    if (q->kode == kode) {
      cout << "Kode energi sudah digunakan!" << endl << endl;
    }
    q = q->next;
  }
  nodeStack* s = top;
  while (s != NULL) {
    if (s->kode == kode) {
      cout << "Kode energi sudah digunakan!" << endl << endl;
    }
    s = s->next;
  }
  cout << "Masukan nama energi: ";
  cin.ignore();
  getline(cin, nama);
  if (nama.empty()) {
    cout << "Nama energi tidak boleh kosong!" << endl << endl;
    return;
  }
  nodeQueue* nb = new nodeQueue{kode, nama, NULL};
  if (front == NULL) {
    front = last = nb;
  } else {
    last->next = nb;
    last = nb;
  }
  cout << "Berhasil memasukan energi!" << endl << endl;
}

// menampilkan seluruh energi
void lihat_antrean() {
  if (front == NULL) {
    cout << "Antrean energi kosong!" << endl << endl;
    return;
  }
  cout << "\n=== Energi Dalam Antrean ==\n";
  nodeQueue* nb = front;
  int no = 1;
  while (nb != NULL) {
    cout << no << ". [" << nb->kode << "] " << nb->nama << endl;
    nb = nb->next;
    no++;
  }
  cout << endl;
}

void proses_energi() {
  if (front == NULL) {
    cout << "Antrean energi kosong!" << endl;
    return;
  }

  nodeQueue* hapus = front;
  nodeStack* nb = new nodeStack{hapus->kode, hapus->nama, top};
  top = nb;
  root = tambah_tree(root, hapus->kode, hapus->nama);
  cout << "Berhasil memproses energi " << hapus->nama << "!" << endl << endl;
  front = hapus->next;

  if (front == NULL) {
    last = NULL;
  }
  delete hapus;
}

// menampilkan seluruh energi
void lihat_riwayat() {
  if (top == NULL) {
    cout << "Belum ada energi yang selesai" << endl << endl;
    return;
  }
  cout << "=== Energi Yang Sudah Terserap ===" << endl;
  nodeStack* nb = top;
  int no = 1;
  while (nb != NULL) {
    cout << no << ". [" << nb->kode << "] " << nb->nama << endl;
    nb = nb->next;
    no++;
  }
  cout << endl;
}

void cari_energi() {
  if (root == NULL) {
    cout << "Belum ada energi yang terserap!" << endl;
    return;
  }
  int kode;
  cout << "Masukan kode energi: ";
  cin >> kode;
  if (cin.fail() || kode <= 0) {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Kode energi harus berupa angka lebih dari 0!" << endl << endl;
    return;
  }
  nodeTree* hasil = cari_tree(root, kode);
  if (hasil == NULL) {
    cout << "Energi dengan kode " << kode << " tidak ditemukan!" << endl;
    return;
  }
  cout << "Ditemukan: [" << hasil->kode << "] " << hasil->nama << endl << endl;
}

void lihat_energi() {
  if (root == NULL) {
    cout << "Belum ada energi yang terserap!" << endl;
    return;
  }
  char pil;
  int no = 1;
  cout << " === Isi Kristal Organ ===" << endl << endl;
  cout << "1. Pre-Order" << endl;
  cout << "2. In-Order" << endl;
  cout << "3. Post-Order" << endl;
  cout << "Masukan Pilihan: ";
  cin >> pil;
  cout << endl;

  switch (pil) {
    case '1': {
      preorder(root, no);
      break;
    }
    case '2': {
      inorder(root, no);
      break;
    }
    case '3': {
      postorder(root, no);
      break;
    }
    default: {
      cout << "Pilihan yang anda masukan salah!" << endl;
    }
  }
  cout << endl;
}

void gunakan_energi() {
  if (root == NULL) {
    cout << "Belum ada energi yang terserap!" << endl;
    return;
  }
  int kode;
  cout << "Masukan kode energi: ";
  cin >> kode;
  if (cin.fail() || kode <= 0) {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Kode energi harus berupa angka lebih dari 0!" << endl << endl;
    return;
  }
  nodeTree* hasil = cari_tree(root, kode);
  if (hasil == NULL) {
    cout << "Energi dengan kode " << kode << " tidak ditemukan!" << endl;
    return;
  }

  cout << "Energi " << hasil->nama << " telah terserap!" << endl;
  root = hapus_tree(root, kode);
}

void hapus_riwayat() {
  if (top != NULL) {
    nodeTree* hapus_tree();
  }
}

int main() {
  char pil = '0';
  while (pil != 9) {
    cout << "\n=== Sistem Organ Inti Nirwana ===" << endl;
    cout << "1. Tambah Energi " << endl;
    cout << "2. Lihat Energi Dalam Antrean" << endl;
    cout << "3. Proses Energi " << endl;
    cout << "4. lihat energi Yang Sudah Terserap" << endl;
    cout << "5. Hapus Riwayat Energi Teratas" << endl;
    cout << "6. cari energi Di Organ" << endl;
    cout << "7. Lihat Isi Organ" << endl;
    cout << "8. Gunakan Energi" << endl;
    cout << "9. Keluar " << endl;
    cout << "Masukan Pilihan Anda: ";
    cin >> pil;

    switch (pil) {
      case '1': {
        char pil_tambah = 'y';
        while (pil_tambah == 'y' || pil_tambah == 'Y') {
          tambah_energi();
          cout << "Apakah anda ingin menambah energi lagi? (y/n) : ";
          cin >> pil_tambah;
        }
        break;
      }
      case '2': {
        lihat_antrean();
        break;
      }
      case '3': {
        proses_energi();
        break;
      }
      case '4': {
        lihat_riwayat();
        break;
      }
      case '5': {
        hapus_riwayat();
        break;
      }
      case '6': {
        cari_energi();
        break;
      }
      case '7': {
        lihat_energi();
        break;
      }
      case '8': {
        gunakan_energi();
        break;
      }
      case '9': {
        cout << "Program Keluar!";
        exit(0);
      }
      default: {
        cout << "Pilihan yang anda masukan salah!" << endl;
      }
    }
    cout << endl;
  }
}
