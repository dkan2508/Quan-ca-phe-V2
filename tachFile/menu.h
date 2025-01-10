#pragma once

#include "kho.h"
#include "general.h"

// Cấu trúc món ăn
typedef struct {
    char tenMon[DO_DAI_TEN_MON];
    float gia;
    NguyenLieu nguyenLieu[MAX_NGUYEN_LIEU];
    int soNguyenLieu;
} MonAn;

int kiemTraSoMonAn(char duongDan[]); // Kiem tra so mon an trong mang
void saoChepMonAn(MonAn* monAnNhan, MonAn* monAnNguon); // Deep-copy doi tuong mon an
void chuanHoaMonAn(MonAn* monAn, int soMonAn); // Khoi tao gia tri mac dinh
int coNhuNhauMonAn(MonAn h1, MonAn h2); // Kiem tra xem hai mon an co hoan toan giong nhau chua duoc dung)
void themNhieuMonAnVaoFile(MonAn danhSachMonAn[], int soMonAn, char duongDan[]); // Toi uu de them nhieu doi tuong vao file
void docFileMenu(char duongDan[], int soMonAnDoc, MonAn* danhSachMonAn); // Doc du lieu trong file menu ra mot mang
void themMonAnVaoFile(char duongDan[], MonAn* monAn); // Them mot mon an vao file
void xoaMonAnKhoiFile(char duongDan[], MonAn* monXoa); // Xoa mot mon an khoi file
void hienThiMenu(MonAn menu[], int soMon); 
void nhapThongTinMonAn(MonAn* monAn, NguyenLieu kho[], int soNguyenLieuKho); // Nhap thong tin cho mot doi tuong mon an
void nhapTenMonAn(MonAn* monAn, NguyenLieu kho[], int soNguyenLieuKho); // Nhap ten mon an de dinh vi nhanh chong doi tuong
void themMonAnVaoMang(MonAn menu[], int* soMon, MonAn* monThem); // Them mot mon an vao mang
void xoaMonAnTrongMang(MonAn menu[], int* soMonAn, MonAn* monXoa); // Xoa mot mon an khoi mang
void capNhatMonAnTuFile(MonAn menu[], int* soMonMang, char duongDan[], int* soMonFile);
void capNhatMonAnTuMang(MonAn menu[], int* soMonMang, char duongDan[], int* soMonFile);
