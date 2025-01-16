#pragma once
#include "general.hpp"
#include "kho.hpp"
using namespace std;

class MonAn : public DoiTuongLamViec {
    private:
        string tenMon;
        float gia;
        vector<NguyenLieu> dsNguyenLieu;
    public:
        MonAn(string name="", float gia=0, vector<NguyenLieu> nguyenLieu={});
        void setName(const string name);
        string getName() const;
        void setPrice(const float price);
        float getPrice() const;
        vector<NguyenLieu> getIngredient() const;
        int doiTuongCoNhuNhau(const DoiTuongLamViec& other) const;
        int coLaMotDoiTuong(const DoiTuongLamViec& other) const;
        void nhapThongTinNhanDang();
        void nhapThongTin();
        void saoChepThongTin(const DoiTuongLamViec& other);
};

class QuanLiMenu : public QuanLiDanhSach<MonAn> {
    private:
    public:
        QuanLiMenu(int maxMang, int maxFile, int luaChon, string dauDan);
        string layXauDoiTuong(const MonAn& doiTuong) const;
        MonAn taoDoiTuongTuXau(string xauThongTin) const;
        void hienThi(const vector<MonAn>& danhSach) const;
        void timKiem(const vector<MonAn>& danhSach) const;
};
