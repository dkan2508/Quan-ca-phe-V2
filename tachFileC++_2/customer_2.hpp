#pragma once
#include "general.hpp"
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class KhachHang {
    private:
        string tenKhachHang;
        string soDienThoai;
        float diemTichLuy;
    public:
        KhachHang(string, string, float);
        KhachHang(const KhachHang&);
        string getName() const;
        void setName(string);
        string getPhoneNum() const;
        void setPhoneNum(string);
        float getPoint() const;
        void setPoint(float);
        int khachCoNhuNhau(const KhachHang&) const; // Kiem tra xem hai khach hang co hoan toan giong nhau
        int khachCoLaMoi(const KhachHang&) const; // Kiem tra xem hai khach hang co cung so dien thoai
        void saoChepKhach(const KhachHang&);
};

class QuanLiKhach {
    const int gioiHanMang = MAX_KHACH_HANG;
    const int gioiHanFile = INT16_MAX;

    private:
        vector<KhachHang> danhSachMang;
    public:
        QuanLiKhach();
        int soLuongMang() const;
        int soLuongFile() const;
        vector<KhachHang> layDanhSachMang() const;
        vector<KhachHang> layDanhSachFile() const;
        int layGioiHanMang() const;
        int layGioiHanFile() const;

        void hienThiMang() const;
        void hienThiFile() const;

        void resetMang();
        void resetFile() const;

        void xoaPhanTuMang();
        void xoaPhanTuFile() const;

        void themPhanTuMang();
        void themPhanTuFile() const;

        void capNhatMangTuFile();
        void capNhatFileTuMang() const;

        void timKiemMang() const;
        void timKiemFile() const;

        void themNhieuDoiTuongVaoFile(vector<KhachHang> mangThem) const;  
};
