#pragma once
#include "general.h"

typedef struct {
    char tenKhachHang[DO_DAI_TEN_KHACH];
    char soDienThoai[DO_DAI_SO_DIEN_THOAI];
    float diemTichLuy;
} KhachHang;

void themKhachHang(KhachHang danhSachKhachHang[], int *soKhachHang, KhachHang* khachHangMoi); // Them khach hang vao mang
void xemDanhSachKhachHang(KhachHang danhSachKhachHang[], int soKhachHang); // Hien thi danh sach khach hang
void timKiemKhachHang(KhachHang danhSachKhachHang[], int soKhachHang); // Tim kiem thong tin khach hang
void xoaKhachHang(KhachHang danhSachKhach[], int* soLuong, KhachHang* khachXoa); // Xoa mot khach hang khoi mang
void nhapThongTinKhach(KhachHang* khachHang, int placeHolderArr[], int placeHolderVal); // Nhap thong tin cho mot doi tuong khach hang
void nhapTenSDTKhach(KhachHang* khachHang, int placeholderArr[], int placeholderVal); // Nhap ten va so dien thoai khach hang, duoc dung de nhanh chong dinh vi khach hang ma khong can dien diem tich luy
void capNhatKhachTuMang(KhachHang danhSach[], int* soKhach, char duongDan[], int* soKhachFile);  
void capNhatKhachTuFile(KhachHang danhSach[], int* soKhach, char duongDan[], int* soKhachFile);
void layDiemTichLuy(KhachHang danhSachKhachHang[], int soKhachHang, KhachHang* khach); // Lay thong tin diem tich luy tu mang
void chuanHoaKhachHang(KhachHang* khachHang, int soKhachHang); // Cai dat mac dinh cho khach hang, tranh gia tri rac
void saoChepKhachHang(KhachHang* khachNhan, KhachHang* khachNguon); // Deep-copying khach hang
int kiemTraSoKhachHang(char duongDan[]); // Kiem tra so khach trong file
int coNhuNhauKhachHang(KhachHang k1, KhachHang k2); // Kiem tra xem hai khach hang co la nhu nhau
void docFileKhachHang(char duongDan[], int soKhachHangDoc, KhachHang danhSachKhachHang[]); // Doc va ghi du lieu cua file khach hang vao mot mang
void xoaKhachKhoiFile(char duongDan[], KhachHang* khachXoa); // Xoa khach hang cu the khoi file
void themKhachHangVaoFile(char duongDan[], KhachHang* khach); // Them mot khach hang vao file
void themNhieuKhachVaoFile(KhachHang danhSachKhach[], int soKhach, char duongDan[]); // Toi uu hon de them nhieu khach hang vao file

