#pragma once
#include "general.hpp"
using namespace std;

class NguyenLieu : public DoiTuongLamViec {
    private:
        string tenNguyenLieu;
        string donVi;
        float soLuong;
        float gia;
    public:
        NguyenLieu(string name="", string unit="", float soLuong=0, float gia=0);
        void setName(string name);
        string getName() const;
        string getUnit() const;
        void setUnit(const string unit);
        float getQuantity() const;
        void setQuantity(const float quantity);
        float getPrice() const;
        void setPrice(const float price);
        int doiTuongCoNhuNhau(const DoiTuongLamViec& other) const;
        int coLaMotDoiTuong(const DoiTuongLamViec& other) const;
        void nhapThongTinNhanDang();
        void nhapThongTin();
        void saoChepThongTin(const DoiTuongLamViec& other);
};

class QuanLiNguyenLieu : public QuanLiDanhSach<NguyenLieu> {
    private:
    public:
        QuanLiNguyenLieu(int maxMang, int maxFile, int luaChon, string dauDan);
        string layXauDoiTuong(const NguyenLieu& doiTuong) const;
        NguyenLieu taoDoiTuongTuXau(string xauThongTin) const;
        void hienThi(const vector<NguyenLieu>& danhSach) const;
        void timKiem(const vector<NguyenLieu>& danhSach) const;
        void truNguyenLieu(vector<NguyenLieu>& danhSach, const NguyenLieu& nguyenLieuLay, const float soLuongLay);
        void truNguyenLieuMang(const NguyenLieu& nguyenLieuLay, const float soLuongLay);
};