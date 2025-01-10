#pragma once
#include "general.h"

typedef struct {
    char tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU];
    char donVi[MAX_DO_DAI_CHUOI_DON_VI];  //kg, hộp, trái, gói
    float soLuong; 
    float gia; // Tinh tren mot don vi 
} NguyenLieu;

void chuanHoaKho(NguyenLieu* kho, int soNguyenLieu); // Khoi tao du lieu mac dinh
void saoChepNguyenLieu(NguyenLieu* nguyenLieuNhan, NguyenLieu* nguyenLieuNguon); // Deep-copy doi tuong nguyen lieu
void themNhieuNguyenLieuVaoFile(NguyenLieu danhSachNguyenLieu[], int soNguyenLieu, char duongDan[]); // Toi uu de them nhieu doi tuong vao file
int kiemTraSoNguyenLieu(char duongDan[]); // Kiem tra so doi tuong trong file kho
int coNhuNhauNguyenLieu(NguyenLieu h1, NguyenLieu h2); // Kiem tra xem hai nguyen lieu co hoan toan giong nhau (chua dung toi)
void docFileKho(char duongDan[], int soNguyenLieu, NguyenLieu kho[]); // Doc du lieu tu file kho ra mot mang
void xoaNguyenLieuKhoiFile(char duongDan[], NguyenLieu* nguyenLieuXoa); // Xoa mot nguyen lieu khoi file
void themNguyenLieuVaoFile(char duongDan[], NguyenLieu* nguyenLieu); // Them mot nguyen lieu vao file
void hienThiKho(NguyenLieu kho[], int soLuong); // Hien thi danh sach kho
void themNguyenLieu(NguyenLieu kho[], int* soLuong, NguyenLieu* nguyenLieuMoi); // Them mot nguyen lieu vao mang
void xoaNguyenLieu(NguyenLieu kho[], int* soLuong, NguyenLieu* nguyenLieuXoa); // Xoa mot nguyen lieu khoi mang
void layNguyenLieu(NguyenLieu kho[], int soNguyenLieuKho, NguyenLieu nguyenLieuSuDung, int soMon); // 
void nhapThongTinNguyenLieu(NguyenLieu* nguyenLieu, int placeHolderArr[], int* placeHolderVal); // Nhap thong tin cho mot doi tuong nguyen lieu
void nhapTenNguyenLieu(NguyenLieu* nguyenLieu, int placeHolderArr[], int* placeHolderVal); // Nhap ten nguyen lieu de nhanh chong dinh vi doi tuong
void timKiemNguyenLieu(NguyenLieu kho[], int soNguyenLieu); // Tim kiem thong tin nguyen lieu
void capNhatKhoTuFile(NguyenLieu kho[], int* soLuongKho, char duongDan[], int* soLuongFile); 
void capNhatKhoTuMang(NguyenLieu kho[], int* soLuongKho, char duongDan[], int* soLuongFile);
