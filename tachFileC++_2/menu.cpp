#include "menu.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

// Dinh nghia lop MonAn
MonAn::MonAn(string name, float gia, vector<NguyenLieu> nguyenLieu)
    : tenMon(name), gia(gia), dsNguyenLieu(nguyenLieu) {}

void MonAn::setName(const string name) {
    tenMon = name;
}

string MonAn::getName() const {
    return tenMon;
}

void MonAn::setPrice(const float price) {
    gia = price;
}

float MonAn::getPrice() const {
    return gia;
}

vector<NguyenLieu> MonAn::getIngredient() const {
    return dsNguyenLieu;
}

int MonAn::doiTuongCoNhuNhau(const DoiTuongLamViec& other) const {
    const MonAn* otherMonAn = dynamic_cast<const MonAn*>(&other);

    if(dsNguyenLieu.size() != otherMonAn->dsNguyenLieu.size()) {
        return 0;
    }

    for(int i = 0; i < dsNguyenLieu.size(); i++) {
        if(dsNguyenLieu[i].doiTuongCoNhuNhau(otherMonAn->dsNguyenLieu[i]) == 0) {
            return 0;
        }
    }

    return (
        tenMon == otherMonAn->tenMon &&
        gia == otherMonAn->gia
    );
}

int MonAn::coLaMotDoiTuong(const DoiTuongLamViec& other) const {
    const MonAn* otherMonAn = dynamic_cast<const MonAn*>(&other);
    return tenMon == otherMonAn->tenMon;
}

void MonAn::nhapThongTinNhanDang() {
    cout << "Nhap ten mon an: ";
    getline(cin, tenMon);
}

void MonAn::nhapThongTin() {
    cout << "Nhap ten mon an: ";
    getline(cin, tenMon);
    cout << "Nhap gia: ";
    saferScanf("%f", &gia);

    int soNL;
    cout << "Nhap so luong nguyen lieu: ";
    saferScanf("%d", &soNL);

    //dsNguyenLieu.clear();
    cout << "So nguyen lieu: " << soNL << "\n";
    for (int i = 0; i < soNL; i++) {
        cout << "Iter: " << i+1 << "\n";
        NguyenLieu nl;
        cout << "\nNhap thong tin nguyen lieu\n";
        nl.nhapThongTin();
        dsNguyenLieu.push_back(nl);
    }
}

void MonAn::saoChepThongTin(const DoiTuongLamViec& other) {
    const MonAn* otherMonAn = dynamic_cast<const MonAn*>(&other);
    tenMon = otherMonAn->tenMon;
    gia = otherMonAn->gia;
    dsNguyenLieu = otherMonAn->dsNguyenLieu;
}


// Dinh nghia lop quan li mon an

QuanLiMenu::QuanLiMenu(int maxMang, int maxFile, int luaChon, string dauDan) 
            : QuanLiDanhSach(maxMang, maxFile, luaChon, dauDan) {}

string QuanLiMenu::layXauDoiTuong(const MonAn& doiTuong) const {
    stringstream ss;
    ss << doiTuong.getName() << NGAN_PHAN_TU_CSV
       << doiTuong.getPrice() << NGAN_PHAN_TU_CSV;

    string info;
    vector<NguyenLieu> ingr = doiTuong.getIngredient();
    QuanLiNguyenLieu qlnl(0, 0, 0, "");
    for(int i = 0; i < ingr.size(); i++) {
        info = qlnl.layXauDoiTuong(ingr[i]);
        info.erase(info.find_last_not_of('\n') + 1);
        info[info.length()] = '\0';
        ss << info;
    }

    // Tao truong rong cho cac thanh phan con thieu
    for(int i = 0; i < MAX_MON - ingr.size(); i++) {
        info = qlnl.layXauDoiTuong(NguyenLieu());
        info.erase(info.find_last_not_of('\n') + 1);
        info[info.length()] = '\0';
        ss << info;
    }

    ss << "\n";
    
    return ss.str();
}

MonAn QuanLiMenu::taoDoiTuongTuXau(string xauThongTin) const {
    xauThongTin.erase(xauThongTin.find_last_not_of('\n') + 1);
    stringstream ss(xauThongTin);

    string tenMon;
    float giaMon;
    getline(ss, tenMon, NGAN_PHAN_TU_CSV);
    ss >> giaMon;
    ss.ignore();

    NguyenLieu nguyenLieuRong;
    NguyenLieu nguyenLieuDoc;
    QuanLiNguyenLieu qlnl(0, 0, 0, "");
    string xauNguyenLieu;
    vector<NguyenLieu> nguyenLieuMon;
    // Luot qua tung section cua xau tuong ung voi mot nguyen lieu va kiem tra xem nguyen lieu do co la nguyen lieu rong
    for(int i = 0; i < MAX_MON; i++) {
        for(int j = 0; j < 4; j++) { // 4: so luong thuoc tinh nguyen lieu obj
            getline(ss, xauNguyenLieu, NGAN_PHAN_TU_CSV);
        }
        xauNguyenLieu[xauNguyenLieu.length()] = '\n';
        xauNguyenLieu[xauNguyenLieu.length()] = '\0';

        nguyenLieuDoc.saoChepThongTin(qlnl.taoDoiTuongTuXau(xauNguyenLieu));
        if(nguyenLieuDoc.doiTuongCoNhuNhau(nguyenLieuRong) == 0) {
            nguyenLieuMon.push_back(nguyenLieuDoc);
        }
    }

    return MonAn(tenMon, giaMon, nguyenLieuMon);
}

void QuanLiMenu::hienThi(const vector<MonAn>& danhSach) const {
    ostringstream oss;

    oss << "\nMENU:\n";
    oss << left << setw(5) << "STT"
         << setw(25) << "Ten Mon An"
         << setw(10) << "Gia\n";

    for (int i = 0; i < danhSach.size(); i++) {
        oss << left << setw(5) << i + 1
            << setw(25) << danhSach[i].getName()
            << setw(10) << fixed << setprecision(2) << danhSach[i].getPrice()
            << "\n";
    }

    cout << oss.str();
}

void QuanLiMenu::timKiem(const vector<MonAn>& danhSach) const {}

