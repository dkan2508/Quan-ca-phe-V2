#pragma once
#include "general.hpp"
#include "customer.hpp"
#include "menu.hpp"

class HoaDon : public DoiTuongLamViec {
    private:
        KhachHang khach;
        Ngay ngayNhapDon;
        vector<int> soMoiMon;
        vector<string> tenMonGoi;
        vector<float> giaMonGoi;
        int soMonGoi;
        float tongTien;
        float tienThua;
        float tienNguyenLieu;
    public:
        HoaDon(KhachHang khach=KhachHang(), Ngay ngay=Ngay(), vector<int> soMoiMon={}, vector<string> tenMonGoi={},
                vector<float> giaMonGoi={}, int soMonGoi=0, float tongTien=0, float tienThua=0, float tienNguyenLieu=0);
        KhachHang getKhach() const;
        void setKhach(const KhachHang& khach);
        Ngay getNgay() const;
        void setNgay(const Ngay& ngay);
        vector<int> getSoMoiMon() const;
        vector<int>& getRefSoMoiMon();
        void setSoMoiMon(const vector<int>& soLuong);
        vector<string> getTenMon() const;
        vector<string>& getRefTenMon();
        void setTenMon(const vector<string>& dsTen);
        vector<float> getGiaMoiMon() const;
        void setGiaMoiMon(const vector<float>& giaMon);
        vector<float>& getRefGiaMoiMon();
        int getSoMonGoi() const;
        void setSoMonGoi(const int soMon);
        float getTongTien() const;
        void setTongTien(const float tongTien);
        float& getRefTongTien();
        float getTienThua() const;
        void setTienThua(const float tienThua);
        float& getRefTienThua();
        float getTienNguyenLieu() const;
        void setTienNguyenLieu(const float tienNguyenLieu);
        float& getRefTienNguyenLieu();

        int doiTuongCoNhuNhau(const DoiTuongLamViec& other) const;
        int coLaMotDoiTuong(const DoiTuongLamViec& other) const;
        void nhapThongTinNhanDang(const QuanLiMenu& menu);
        void nhapThongTin(const QuanLiMenu& menu);
        void saoChepThongTin(const DoiTuongLamViec& other);

        // Hai ham duoi chi xuat hien de dam bao yeu cau ke thua tu class ao
        void nhapThongTinNhanDang() {}
        void nhapThongTin() {}

};   

class QuanLiHoaDon : public QuanLiDanhSach<HoaDon> {
    private:
    public: 
        QuanLiHoaDon(int maxMang, int maxFile, int luaChon, string dauDan);
        string layXauDoiTuong(const HoaDon& hoaDon) const;
        HoaDon taoDoiTuongTuXau(string xauThongTin) const;
        void hienThi(const vector<HoaDon>& danhSach) const;
        void timKiem(const vector<HoaDon>& danhSach) const;
};

void thanhToan(const QuanLiMenu& menu, QuanLiNguyenLieu& kho, QuanLiKhachHang& dsKhach, QuanLiHoaDon& dsHoaDon);
