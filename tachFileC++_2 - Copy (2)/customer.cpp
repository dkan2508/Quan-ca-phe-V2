#include "customer.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// Dinh nghia lop khach hang

KhachHang::KhachHang(string name, string sdt, float diem)
    : tenKhach(name), soDienThoai(sdt), diemTichLuy(diem) {}

void KhachHang::setName(string name) {
    tenKhach = name;
}

string KhachHang::getName() const {
    return tenKhach;
}

string KhachHang::getPhoneNum() const {
    return soDienThoai;
}

void KhachHang::setPhoneNum(const string sdt) {
    soDienThoai = sdt;
}

float KhachHang::getPoint() const {
    return diemTichLuy;
}

void KhachHang::setPoint(const float point) {
    diemTichLuy = point;
}

int KhachHang::doiTuongCoNhuNhau(const DoiTuongLamViec& other) const {
    const KhachHang* otherKhachHang = dynamic_cast<const KhachHang*>(&other);
    return (
        tenKhach == otherKhachHang->tenKhach &&
        soDienThoai == otherKhachHang->soDienThoai &&
        diemTichLuy == otherKhachHang->diemTichLuy
    );
}

int KhachHang::coLaMotDoiTuong(const DoiTuongLamViec& other) const {
    const KhachHang* otherKhachHang = dynamic_cast<const KhachHang*>(&other);
    return soDienThoai == otherKhachHang->soDienThoai;
}

void KhachHang::nhapThongTinNhanDang() {
    cout << "Nhap so dien thoai: ";
    getline(cin, soDienThoai);
}

void KhachHang::nhapThongTin() {
    cout << "Nhap ten khach hang: ";
    getline(cin, tenKhach);
    cout << "Nhap so dien thoai: ";
    getline(cin, soDienThoai);
    cout << "Nhap diem tich luy: ";
    saferScanf("%f", &diemTichLuy);
}

void KhachHang::saoChepThongTin(const DoiTuongLamViec& other) {
    const KhachHang* otherKhachHang = dynamic_cast<const KhachHang*>(&other);
    tenKhach = otherKhachHang->tenKhach;
    soDienThoai = otherKhachHang->soDienThoai;
    diemTichLuy = otherKhachHang->diemTichLuy;
}

// Dinh nghia lop quan li khach hang

QuanLiKhachHang::QuanLiKhachHang(int maxMang, int maxFile, int luaChon, string dauDan) 
                : QuanLiDanhSach(maxMang, maxFile, luaChon, dauDan) {}

string QuanLiKhachHang::layXauDoiTuong(const KhachHang& doiTuong) const {
    stringstream ss;
    ss << doiTuong.getName() << NGAN_PHAN_TU_CSV
       << doiTuong.getPhoneNum() << NGAN_PHAN_TU_CSV
       << doiTuong.getPoint()
       << "\n";
    return ss.str();
}

KhachHang QuanLiKhachHang::taoDoiTuongTuXau(string xauThongTin) const {
    string name, sdt;
    float point;
    
    // Chuyen thanh mot stream de su dung getline()
    stringstream ss(xauThongTin);
    
    getline(ss, name, ','); // Lay thong tin toi dau phay dau tien
    getline(ss, sdt, ',');
    ss >> point; // Input thong tin vao truong tiep theo nhu cin >>

    return KhachHang(name, sdt, point);
}

void QuanLiKhachHang::hienThi(const vector<KhachHang>& danhSach) const {
    ostringstream oss;

    oss << "DANH SACH KHACH HANG:\n";
    oss << left << setw(5) << "STT" 
              << setw(25) << "Ten Khach Hang" 
              << setw(25) << "So Dien Thoai" 
              << setw(10) << "Diem Tich Luy\n";

    for(int i = 0; i < danhSach.size(); i++) {
        oss << left << setw(5) << i + 1
            << setw(25) << danhSach[i].getName()
            << setw(25) << danhSach[i].getPhoneNum()
            << setw(10) << fixed << left << setprecision(2) << danhSach[i].getPoint()
            << "\n";
    }

    cout << oss.str();
}

void QuanLiKhachHang::timKiem(const vector<KhachHang>& danhSach) const {
    int soLuong = danhSach.size();
    ostringstream oss;
    int luaChon;
    string keyword;

    cout << "\nChon phuong thuc tim kiem:\n";
    cout << "1. Tim theo ten\n";
    cout << "2. Tim theo so dien thoai\n";
    cout << "Nhap lua chon: ";
    saferScanf("%d", &luaChon);

    if (luaChon != 1 && luaChon != 2) {
        cout << "Lua chon khong hop le\n";
        return;
    } else if (luaChon == 1) {
        cout << "Nhap ten khach hang: ";
        getline(cin, keyword);
        oss << "\nDanh sach khach hang tim duoc theo ten '" << keyword << "':\n";
        oss << left << setw(5) << "STT" << setw(20) << "Ten khach hang"
            << setw(20) << "So dien thoai" << setw(15) << "Diem tich luy" << "\n";

        int stt = 1;
        for (int i = 0; i < soLuong; i++) {
            if (danhSachMang[i].getName().find(keyword) != string::npos) {
                oss << left << setw(5) << stt++
                    << setw(20) << danhSachMang[i].getName()
                    << setw(20) << danhSachMang[i].getPhoneNum()
                    << fixed << setprecision(2) << setw(15) << danhSachMang[i].getPoint() << "\n";
            }
        }
        cout << oss.str();

    } else if (luaChon == 2) {
        cout << "Nhap so dien thoai khach hang: ";
        getline(cin, keyword);

        oss << "\nDanh sach khach hang tim duoc theo so dien thoai '" << keyword << "':\n";
        oss << left << setw(5) << "STT" << setw(20) << "Ten khach hang"
            << setw(20) << "So dien thoai" << setw(15) << "Diem tich luy" << "\n";

        int stt = 1;
        for (int i = 0; i < soLuong; i++) {
            if (danhSachMang[i].getPhoneNum().find(keyword) != string::npos) {
                oss << left << setw(5) << stt++
                    << setw(20) << danhSachMang[i].getName()
                    << setw(20) << danhSachMang[i].getPhoneNum()
                    << fixed << setprecision(2) << setw(15) << danhSachMang[i].getPoint() << "\n";
            }
        }
        cout << oss.str();
    }
}

int QuanLiKhachHang::layDiemTichLuy(const vector<KhachHang>& danhSach, const KhachHang& khachLayDiem) const {
    int status = timPhanTu(danhSach, khachLayDiem);
    if(status == -1) {
        return status;
    }
    return danhSach[status].getPoint();
}

int QuanLiKhachHang::layDiemTichLuyMang(const KhachHang& khachLayDiem) const {
    return layDiemTichLuy(danhSachMang, khachLayDiem);
}

int QuanLiKhachHang::layDiemTichLuyFile(const KhachHang& khachLayDiem) const {
    string duongDan = docFileQuanLi(luaChonDoiTuong);
    return layDiemTichLuy(layDanhSachFile(duongDan), khachLayDiem);
}