#pragma once
#include "general.hpp"
using namespace std;

class KhachHang : public DoiTuongLamViec {
    private:
        string tenKhach;
        string soDienThoai;
        float diemTichLuy;
    public:
        KhachHang(string name="", string sdt="", float diem=0);
        void setName(string name);
        string getName() const;
        string getPhoneNum() const;
        void setPhoneNum(const string sdt);
        float getPoint() const;
        void setPoint(const float point);
        int doiTuongCoNhuNhau(const DoiTuongLamViec& other) const;
        int coLaMotDoiTuong(const DoiTuongLamViec& other) const;
        void nhapThongTinNhanDang();
        void nhapThongTin();
        void saoChepThongTin(const DoiTuongLamViec& other);
};

class QuanLiKhachHang : public QuanLiDanhSach<KhachHang> {
    private:
    public:
        QuanLiKhachHang(int maxMang, int maxFile, int luaChon, string dauDan);
        string layXauDoiTuong(const KhachHang& doiTuong) const;
        KhachHang taoDoiTuongTuXau(string xauThongTin) const;
        void hienThi(const vector<KhachHang>& danhSach) const;
        void timKiem(const vector<KhachHang>& danhSach) const;
        int layDiemTichLuy(const vector<KhachHang>& danhSach, const KhachHang& khachLayDiem) const;
        int layDiemTichLuyMang(const KhachHang& khachLayDiem) const;
        int layDiemTichLuyFile(const KhachHang& khachLayDiem) const;
};
