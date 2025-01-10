#pragma once
#include "customer.h"

typedef struct {
    KhachHang khachHang;
    Ngay ngayNhapDon;
    int soLuongMon[MAX_MON];
    char tenMonGoi[MAX_MON][DO_DAI_TEN_MON]; 
    float giaMonGoi[MAX_MON];
    int soMonGoi;
    float tongTien;
    float tienThua;
    float tienNguyenLieu;
} HoaDon;

void chuanHoaHoaDon(HoaDon* hoaDon, int soHoaDon); // Khoi tao gia tri mac dinh
void saoChepHoaDon(HoaDon* hoaDonNhan, HoaDon* hoaDonNguon); // Deep-copy hai doi tuong hoa don
int kiemTraSoHoaDon(char duongDan[]); // Doc so hoa don trong file
int coNhuNhauHoaDon(HoaDon h1, HoaDon h2); // Kiem tra xem hai doi tuong hoa don co hoan toan cung thuoc tinh khong
void docFileHoaDon(char duongDan[], int soHoaDon, HoaDon danhSachHoaDon[]); // Lay du lieu trong file hoa don vao mot mang
void xoaHoaDonKhoiFile(char duongDan[], HoaDon* hoaDonXoa); // Xoa mot doi tuong cu the khoi file hoa don
void themHoaDonVaoFile(HoaDon hoaDon, char duongDan[]); // Them mot doi tuong cu the vao file hoa don
void xemHoaDon(HoaDon danhSachHoaDon[], int soHoaDon); // Hien thi danh sach hoa don
void timKiemHoaDon(HoaDon danhSachHoaDon[], int soHoaDon); // Tim kiem thong tin hoa don trong mot mang
void thanhToan(MonAn menu[], int soMon, HoaDon danhSachHoaDon[], int *soHoaDon, KhachHang danhSachKhachHang[], int *soKhachHang,
                NguyenLieu kho[], int soNguyenLieuKho, char duongDanFileKhach[]); // Thuc hien thanh toan
void xoaHoaDon(HoaDon danhSach[], int* soLuong, HoaDon* hoaDonXoa); // Xoa hoa don khoi mot mang nhat dinh
void nhapThongTinHoaDon(HoaDon* hoaDon, MonAn menu[], int soMonMenu); 
void capNhatHoaDonTuFile(HoaDon danhSachHoaDon[], int* soHoaDon, char duongDan[], int* soHoaDonFile);
void capNhatHoaDonTuMang(HoaDon danhSachHoaDon[], int* soHoaDon, char duongDan[], int* soHoaDonFile);
