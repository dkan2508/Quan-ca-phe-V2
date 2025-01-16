#include "general.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

Ngay::Ngay(int ngay, int thang, int nam) {
    this->ngay = ngay;
    this->thang = thang;
    this->nam = nam;
}

int Ngay::getNgay() const {
    return ngay;
}

void Ngay::setNgay(const int ngay) {
    this->ngay = ngay;
}

int Ngay::getThang() const {
    return thang;
}

void Ngay::setThang(const int thang) {
    this->thang = thang;
}

int Ngay::getNam() const {
    return nam;
}

void Ngay::setNam(const int nam) {
    this->nam = nam;
}

int Ngay::coNhuNhauNgay(const Ngay& other) const {
    // Tra ve 1 neu nhu nhau
    return (ngay == other.ngay && thang == other.thang && nam == other.nam) ? 1 : 0;
}

void Ngay::saoChepNgay(const Ngay& other) {
    setNgay(other.ngay);
    setThang(other.thang);
    setNam(other.nam);
}

void Ngay::nhapNgay() {
    cout << "Nhap ngay: ";
    saferScanf("%d", &ngay);
    cout << "Nhap thang: ";
    saferScanf("%d", &thang);
    cout << "Nhap nam: ";
    saferScanf("%d", &nam);
}

void thongBaoLoi(const string thongDiep) {
    cerr << thongDiep << strerror(errno) << "\n";
}

string docFileQuanLi(int luaChon) {
    // 1: file khach hang
    // 2: file hoa don
    // 3: file kho
    // 4: file menu
    string duongDan = "";

    if(luaChon < 1 || luaChon > 4) {
        cout << "Lua chon mo file quan li khong hop le!\n";
        return duongDan;
    }

    ifstream fstr(MANAGING_FILE, ios::in);

    if(!fstr.is_open()) {
        thongBaoLoi("Khong mo duoc file: ");
        return duongDan;
    }

    for(int i = 1; i <= luaChon; i++) {
        if(!getline(fstr, duongDan)) {
            thongBaoLoi("Xay ra loi khi doc file quan ly: ");
            fstr.close();
            return duongDan;
        }
    }
    duongDan.erase(duongDan.find_last_not_of('\n') + 1);
    fstr.close();
    return duongDan;
}

void capNhatFileQuanLi(int luaChon, string duongDanMoi) {
    // 1: file khach hang
    // 2: file hoa don
    // 3: file kho
    // 4: file menu

    if (luaChon < 1 || luaChon > SO_DOI_TUONG_LAM_VIEC) {
        cout << "Lua chon khong hop le!\n";
        return;
    }
    // Loai bo ky tu newline cua dau vao (neu co). Neu dau vao khong co newline, doan code nay khong gay anh huong gi
    if(duongDanMoi.length() != 0) {
        duongDanMoi.erase(duongDanMoi.find_last_not_of('\n') + 1);    
    }

    // Mo file de doc
    string noiDungFile[SO_DOI_TUONG_LAM_VIEC] = {""};
    ifstream ifstr(MANAGING_FILE, ios::in);
    if (!ifstr.is_open()) {
        thongBaoLoi("Khong the mo file quan li: ");
        return;
    }

    // Luu noi dung file ra mang tam thoi
    for (int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
        if (!getline(ifstr, noiDungFile[i])) {
                thongBaoLoi("Co loi khi doc file quan li: ");
                ifstr.close();
                return;
        }
    }
    ifstr.close();

    // Update noi dung cua duong dan moi vao mang tam thoi
    noiDungFile[luaChon - 1] = duongDanMoi;

    // Mo file de viet lai noi dung moi
    ofstream ofstr(MANAGING_FILE, ios::out);
    if (!ofstr.is_open()) {
        thongBaoLoi("Khong the mo file quan li de ghi: ");
        return;
    }

    // Viet noi dung moi, them '\n' vao cuoi moi duong dan de dung dinh dang
    for (int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
        ofstr << noiDungFile[i] << "\n";
    }
    ofstr.close();
}

void saferScanf(const char formatString[], void* addr) {
    /*
    Ep nguoi dung nhap dung dinh dang input de dam bao tinh dung dan du lieu.
    Chi co the nhan du lieu cho mot bien mot luc, khong nhu scanf
    */
    // Chu y tranh su dung format string voi whitespace phia sau, vd: " %d  ". Dieu do se khien cho input khong bao gio duoc chap nhan
    int result;
    char extraChr;
    char chr;

    while (1) {
        result = scanf(formatString, addr);
        if(result == 0 || result == EOF) {
            printf("Dau vao khong hop le\n");
            printf("Dau vao: ");
            while((chr = getchar()) != '\n' && chr != EOF); // Don sach input khong hop le cu trong buffer
        } else {
            if(scanf("%c", &extraChr) == 1 && extraChr != '\n') { // Do mot ly do nao do, input nhu "3ad" voi format %d vx duoc nhan. Dieu kien nay o day de ngan dieu do
                printf("Dau vao khong hop le\n");
                printf("Dau vao: ");
                while((chr = getchar()) != '\n' && chr != EOF); // Don sach input khong hop le cu trong buffer
            } else {
                break;
            }
        }
    }
}

int kiemTraSoLuongFileDoiTuong(string duongDan) {
    ifstream ifstr(duongDan, ios::in);
    if(!ifstr.is_open()) {
        thongBaoLoi("Khong the mo duong dan de kiem tra so luong doi tuong: ");
        return -1;
    }

    int soLuong = 0;
    string line;
    getline(ifstr, line); // Bo qua header
    while(getline(ifstr, line)) {
        soLuong++;
    }

    ifstr.close();

    return soLuong;
}

void khoiTaoLaiFile(int luaChon) {
    if(luaChon < 1 || luaChon > SO_DOI_TUONG_LAM_VIEC) {
        cout << "Lua chon doi tuong khong hop le\n";
        return;
    }

    string duongDan = docFileQuanLi(luaChon);

    ofstream ofstr(duongDan, ios::out);
    if(!ofstr.is_open()) {
        thongBaoLoi("Reset file that bai: ");
        return;
    }

    switch(luaChon) {
        case LUA_CHON_KHACH_HANG:
            ofstr << KHACH_HANG_HEADER;
            break;
        case LUA_CHON_HOA_DON:
            ofstr << HOA_DON_HEADER;
            break;
        case LUA_CHON_KHO:
            ofstr << KHO_HEADER;
            break;
        case LUA_CHON_MENU:
            ofstr << MENU_HEADER;
            break;
        default:
            printf("Lua chon khong hop le\n");
            break;
    }

    ofstr.close();
}
