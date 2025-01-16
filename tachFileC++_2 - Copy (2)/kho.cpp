#include "kho.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// Dinh nghia lop nguyen lieu
NguyenLieu::NguyenLieu(string name, string unit, float quantity, float price)
            : tenNguyenLieu(name), donVi(unit), soLuong(quantity), gia(price) {};

string NguyenLieu::getName() const {
    return tenNguyenLieu;
}

void NguyenLieu::setName(const string name) {
    tenNguyenLieu = name;
}

string NguyenLieu::getUnit() const {
    return donVi;
}

void NguyenLieu::setUnit(const string unit) {
    donVi = unit;
}

float NguyenLieu::getQuantity() const {
    return soLuong;
}

void NguyenLieu::setQuantity(const float quantity) {
    soLuong = quantity;
}

float NguyenLieu::getPrice() const {
    return gia;
}

void NguyenLieu::setPrice(const float price) {
    gia = price;
}

int NguyenLieu::doiTuongCoNhuNhau(const DoiTuongLamViec& other) const {
    // Cast lop cha ve lop con
    const NguyenLieu* otherNguyenLieu = dynamic_cast<const NguyenLieu*>(&other);

    return (
        tenNguyenLieu == otherNguyenLieu->tenNguyenLieu &&
        donVi == otherNguyenLieu->donVi &&
        soLuong == otherNguyenLieu->soLuong &&
        gia == otherNguyenLieu->gia
    );
}

int NguyenLieu::coLaMotDoiTuong(const DoiTuongLamViec& other) const {
    const NguyenLieu* otherNguyenLieu = dynamic_cast<const NguyenLieu*>(&other);
    return tenNguyenLieu == otherNguyenLieu->tenNguyenLieu;
}

void NguyenLieu::nhapThongTinNhanDang() {
    cout << "Nhap ten nguyen lieu: ";
    getline(cin, tenNguyenLieu);
}

void NguyenLieu::nhapThongTin() {
    cout << "Nhap ten nguyen lieu: ";
    getline(cin, tenNguyenLieu);
    cout << "Nhap don vi: ";
    getline(cin, donVi);
    cout << "Nhap soLuong: ";
    saferScanf("%f", &soLuong);
    cout << "Nhap gia moi don vi: ";
    saferScanf("%f", &gia);
}

void NguyenLieu::saoChepThongTin(const DoiTuongLamViec& other) {
    const NguyenLieu* otherNguyenLieu = dynamic_cast<const NguyenLieu*>(&other);

    tenNguyenLieu = otherNguyenLieu->tenNguyenLieu;
    donVi = otherNguyenLieu->donVi;
    soLuong = otherNguyenLieu->soLuong;
    gia = otherNguyenLieu->gia;
}

// Dinh nghia lop quan li nguyen lieu

QuanLiNguyenLieu::QuanLiNguyenLieu(int maxMang, int maxFile, int luaChon, string dauDan) 
                : QuanLiDanhSach(maxMang, maxFile, luaChon, dauDan) {};

string QuanLiNguyenLieu::layXauDoiTuong(const NguyenLieu& doiTuong) const {
    stringstream ss;
    ss << doiTuong.getName() << ","
       << doiTuong.getUnit() << ","
       << doiTuong.getQuantity() << ","
       << doiTuong.getPrice() << "\n";
    return ss.str();
};

NguyenLieu QuanLiNguyenLieu::taoDoiTuongTuXau(string xauThongTin) const {
    string name, unit;
    float quantity, price;
    
    // Chuyen thanh mot stream de su dung getline()
    stringstream ss(xauThongTin);
    
    getline(ss, name, ','); // Lay thong tin toi dau phay dau tien
    getline(ss, unit, ',');
    ss >> quantity; // Input thong tin vao truong tiep theo nhu cin >>
    ss.ignore(); // Bo qua dau phay sau soLuong
    ss >> price;

    return NguyenLieu(name, unit, quantity, price);
}

void QuanLiNguyenLieu::hienThi(const vector<NguyenLieu>& danhSach) const {
    ostringstream oss;

    oss << "DANH SACH NGUYEN LIEU TRONG KHO:\n";
    oss << left << setw(5) << "STT" 
              << setw(25) << "Ten Nguyen Lieu" 
              << setw(10) << "Don Vi" 
              << setw(10) << "So Luong" 
              << setw(10) << "Gia\n";

    for (int i = 0; i < danhSach.size(); i++) {
        oss << left << setw(5) << i + 1
            << setw(25) << danhSach[i].getName()
            << setw(25) << danhSach[i].getUnit()
            << setw(10) << fixed << setprecision(2) << danhSach[i].getQuantity()
            << setw(10) << fixed << setprecision(2) << danhSach[i].getPrice()
            << "\n";
    }

    cout << oss.str();
}

void QuanLiNguyenLieu::timKiem(const vector<NguyenLieu>& danhSach) const {
    NguyenLieu doiTuong;
    doiTuong.nhapThongTinNhanDang();

    ostringstream oss;

    oss << "\nDanh sach nguyen lieu tim duoc theo ten '" << doiTuong.getName() << "':\n";
    oss << left << setw(3) << "STT" 
              << setw(25) << "Ten Nguyen Lieu" 
              << setw(10) << "Don Vi" 
              << setw(10) << "So Luong" 
              << setw(10) << "Gia\n";

    for (int i = 0; i < danhSach.size(); i++) {
        if(danhSach[i].getName().find(doiTuong.getName()) != string::npos) { // Ten co la substring cua ten nguyen lieu trong danh sach
            oss << left << setw(3) << i + 1
                << setw(25) << danhSach[i].getName()
                << setw(10) << danhSach[i].getUnit()
                << setw(10) << danhSach[i].getQuantity()
                << setw(10) << danhSach[i].getPrice()
                << "\n";
        }
    }

    cout << oss.str();
}

void QuanLiNguyenLieu::truNguyenLieu(vector<NguyenLieu>& danhSach, const NguyenLieu& nguyenLieuLay, const float soLuongLay) {
    int status = timPhanTu(danhSach, nguyenLieuLay);
    if(status != -1) {
        danhSach[status].setQuantity(danhSach[status].getQuantity() - soLuongLay);
    }
}

void QuanLiNguyenLieu::truNguyenLieuMang(const NguyenLieu& nguyenLieuLay, const float soLuongLay) {
    truNguyenLieu(danhSachMang, nguyenLieuLay, soLuongLay);
}
