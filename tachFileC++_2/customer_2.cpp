#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "customer.hpp"
#include "general.hpp"

KhachHang::KhachHang(string name="", string phone="", float points=0.0) {
    tenKhachHang = name;
    soDienThoai = phone;
    diemTichLuy = points;
}

KhachHang::KhachHang(const KhachHang& other) {
    tenKhachHang = other.tenKhachHang;
    soDienThoai = other.soDienThoai;
    diemTichLuy = other.diemTichLuy;
}

string KhachHang::getName() const {
    return tenKhachHang;
}

void KhachHang::setName(string name) {
    tenKhachHang = name;
}

string KhachHang::getPhoneNum() const {
    return soDienThoai;
}

void KhachHang::setPhoneNum(string phone) {
    soDienThoai = phone;
}

float KhachHang::getPoint() const {
    return diemTichLuy;
}

void KhachHang::setPoint(float points) {
    diemTichLuy = points;
}

int KhachHang::khachCoNhuNhau(const KhachHang& other) const {
    return (tenKhachHang == other.tenKhachHang &&
            soDienThoai == other.soDienThoai &&
            diemTichLuy == other.diemTichLuy);
}

int KhachHang::khachCoLaMoi(const KhachHang& other) const {
    return (soDienThoai == other.soDienThoai);
}

void KhachHang::saoChepKhach(const KhachHang& other) {
    tenKhachHang = other.tenKhachHang;
    soDienThoai = other.soDienThoai;
    diemTichLuy = other.diemTichLuy;
}

////////////////////////////////////////////////////////////////

QuanLiKhach::QuanLiKhach() {};

int QuanLiKhach::soLuongMang() const {
    return danhSachMang.size();
}

int QuanLiKhach::soLuongFile() const {
    return kiemTraSoLuongFileDoiTuong(docFileQuanLi(LUA_CHON_KHACH_HANG));
}

int QuanLiKhach::layGioiHanMang() const {
    return gioiHanMang;
}

int QuanLiKhach::layGioiHanFile() const {
    return gioiHanFile;
}

vector<KhachHang> QuanLiKhach::layDanhSachMang() const {
    return danhSachMang;
}

vector<KhachHang> QuanLiKhach::layDanhSachFile() const  {
    string duongDanFile = docFileQuanLi(LUA_CHON_KHACH_HANG);
    int soKhach = kiemTraSoLuongFileDoiTuong(duongDanFile);
    vector<KhachHang> danhSachFile;

    if(soKhach == 0) {
        return danhSachFile;
    }

    ifstream ifstr(duongDanFile, ios::in);
    if(!ifstr.is_open()) {
        thongBaoLoi("Khong mo duoc file de doc doi tuong: ");
        return danhSachFile;
    }

    string line;
    getline(ifstr, line); // Skip header

    for(int i = 0; i < soKhach; i++) {
        if(!getline(ifstr, line)) {
            thongBaoLoi("Khong the doc file doi tuong: ");
            ifstr.close();
            return danhSachFile;
        }
        danhSachFile.push_back(KhachHang());

        line.erase(line.find_last_not_of('\n') + 1);
        line[line.length()] = '\0';

        istringstream lineStream(line);
        string tenKhachHang, soDienThoai, diemTichLuyStr;

        if (getline(lineStream, tenKhachHang, NGAN_PHAN_TU_CSV)) {
            danhSachFile[i].setName(tenKhachHang);
        }

        if (getline(lineStream, soDienThoai, NGAN_PHAN_TU_CSV)) {
            danhSachFile[i].setPhoneNum(soDienThoai);
        }

        if (getline(lineStream, diemTichLuyStr, NGAN_PHAN_TU_CSV)) {
            danhSachFile[i].setPoint(stof(diemTichLuyStr));
        }
    }

    ifstr.close();
    return danhSachFile;
}

void QuanLiKhach::hienThiMang() const {
    int soKhach = soLuongMang();
    if (soKhach == 0) {
        cout << "Chua co khach hang\n";
        return;
    }

    // Thuc hien cac thay doi nhu setw, left tren mot stream tam thoi
    // do cac thay doi nay, neu su dung tren cout, se anh huong den cout tren toan bo he thong cho den khi nguoi dung thay doi lai
    ostringstream oss;

    oss << left
        << setw(5) << "STT"
        << setw(20) << "Ten khach hang"
        << setw(20) << "So dien thoai"
        << setw(15) << "Diem tich luy\n";

    for (int i = 0; i < soKhach; i++) {
        oss << left
            << setw(5) << (i + 1)
            << setw(20) << danhSachMang[i].getName()
            << setw(20) << danhSachMang[i].getPhoneNum()
            << setw(15) << fixed << setprecision(2) << danhSachMang[i].getPoint()
            << "\n";
    }

    cout << oss.str();
}

void QuanLiKhach::hienThiFile() const {
    string duongDan = docFileQuanLi(LUA_CHON_KHACH_HANG);
    int soKhach = kiemTraSoLuongFileDoiTuong(duongDan);
    if (soKhach == 0) {
        cout << "Chua co khach hang\n";
        return;
    }
    vector<KhachHang> danhSachFile = layDanhSachFile();

    ostringstream oss;

    oss << left
        << setw(5) << "STT"
        << setw(20) << "Ten khach hang"
        << setw(20) << "So dien thoai"
        << setw(15) << "Diem tich luy\n";

    for (int i = 0; i < soKhach; i++) {
        oss << left
            << setw(5) << (i + 1)
            << setw(20) << danhSachFile[i].getName()
            << setw(20) << danhSachFile[i].getPhoneNum()
            << setw(15) << fixed << setprecision(2) << danhSachFile[i].getPoint()
            << "\n";
    }

    cout << oss.str();
}

void QuanLiKhach::resetMang() {
    // Dat size ve 0 va bo het phan tu
    danhSachMang.resize(0);
}

void QuanLiKhach::resetFile() const {
    khoiTaoLaiFile(LUA_CHON_KHACH_HANG);
}

void QuanLiKhach::xoaPhanTuMang() {
    int soLuong = soLuongMang();
    if(soLuong == 0) {
        cout << "Chua co khach hang\n";
        return;
    }

    string sdtKhachXoa = "";
    cout << "Nhap so dien thoai khach xoa: ";
    getline(cin, sdtKhachXoa); // getline() khong tinh them newline nen khong can khu
    
    for(auto it = danhSachMang.begin(); it != danhSachMang.end(); it++) {
        if(it->getPhoneNum() == sdtKhachXoa) {
            danhSachMang.erase(it);
            cout << "Khach hang da duoc xoa\n";
            return;
        }
    }
    cout << "Khong tim thay khach hang\n";
}

void QuanLiKhach::xoaPhanTuFile() const {
    string duongDan = docFileQuanLi(LUA_CHON_KHACH_HANG);
    int soLuong = kiemTraSoLuongFileDoiTuong(duongDan);
    if(soLuong == 0) {
        cout << "Chua co khach hang\n";
        return;
    }
    vector<KhachHang> danhSachFile = layDanhSachFile();

    string sdtKhachXoa = "";
    cout << "Nhap so dien thoai khach xoa: ";
    getline(cin, sdtKhachXoa); // getline() khong tinh them newline nen khong can khu
    
    int coMat = 0;
    for(auto it = danhSachFile.begin(); it != danhSachFile.end(); it++) {
        if(it->getPhoneNum() == sdtKhachXoa) {
            danhSachFile.erase(it);
            coMat = 1;
            break;
        }
    }
    if(coMat == 0) {
        cout << "Khong tim thay khach hang\n";
        return;
    }

    ofstream ofstr(duongDan, ios::out);
    ofstr << KHACH_HANG_HEADER;
    for(int i = 0; i < soLuong; i++) {
        ofstr << danhSachFile[i].getName() << NGAN_PHAN_TU_CSV
         << danhSachFile[i].getPhoneNum() << NGAN_PHAN_TU_CSV
         << fixed << setprecision(2) << danhSachFile[i].getPoint() << "\n";
    }
    cout << "Xoa khach khoi file thanh cong\n";
    ofstr.close();
}

void QuanLiKhach::themPhanTuMang() {
    int soLuong = soLuongMang();
    if(soLuong >= QuanLiKhach::gioiHanMang) {
        cout << "Mang da day\n";
        return;
    }

    string sdt = "";
    cout << "Nhap so dien thoai khach moi: ";
    getline(cin, sdt);

    for(int i = 0; i < soLuong; i++) {
        if(danhSachMang[i].getPhoneNum() == sdt) {
            cout << "Khach hang da co trong mang\n";
            return;
        }
    }

    string ten;
    cout << "Nhap ten khach: ";
    getline(cin, ten);

    float diemTichLuy;
    cout << "Nhap so diem tich luy: ";
    saferScanf("%f", &diemTichLuy);

    danhSachMang.push_back(KhachHang(ten, sdt, diemTichLuy));
    cout << "Khach hang da duoc them\n";
}

void QuanLiKhach::themPhanTuFile() const {
    string duongDan = docFileQuanLi(LUA_CHON_KHACH_HANG);
    int soLuong = kiemTraSoLuongFileDoiTuong(duongDan);
    vector<KhachHang> danhSachFile = layDanhSachFile();

    string sdt = "";
    cout << "Nhap so dien thoai khach: ";
    getline(cin, sdt); 

    for(int i = 0; i < soLuong; i++) {
        if(danhSachFile[i].getPhoneNum() == sdt) {
            cout << "Khach hang da ton tai trong file\n";
            return;
        }
    }

    ofstream ofstr(duongDan, ios::app);
    if(!ofstr.is_open()) {
        thongBaoLoi("Khong the them khach hang vao file: ");
        return;
    }
    
    string ten;
    cout << "Nhap ten khach: ";
    getline(cin, ten);

    float diemTichLuy;
    cout << "Nhap so diem tich luy: ";
    saferScanf("%f", &diemTichLuy);

    ofstr << ten << NGAN_PHAN_TU_CSV
         << sdt << NGAN_PHAN_TU_CSV
         << fixed << setprecision(2) << diemTichLuy << "\n";
    
    cout << "Khach hang da duoc them\n";

    ofstr.close();
}

void QuanLiKhach::themNhieuDoiTuongVaoFile(vector<KhachHang> mangThem) const {
    string duongDan = docFileQuanLi(LUA_CHON_KHACH_HANG);
    ofstream ofstr(duongDan, ios::app);
    if(!ofstr.is_open()) {
        thongBaoLoi("Khong the them khach vao file: ");
        return;
    }

    for(int i = 0; i < mangThem.size(); i++) {
        ofstr << mangThem[i].getName() << NGAN_PHAN_TU_CSV
         << mangThem[i].getPhoneNum() << NGAN_PHAN_TU_CSV
         << fixed << setprecision(2) << mangThem[i].getPoint() << "\n";
    }

    ofstr.close();
}

void QuanLiKhach::timKiemMang() const {
    int soLuong = soLuongMang();
    if (soLuong == 0) {
        cout << "Chua co khach hang\n";
        return;
    }

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

        ostringstream oss;
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

        ostringstream oss;
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

void QuanLiKhach::timKiemFile() const {
    string duongDan = docFileQuanLi(LUA_CHON_KHACH_HANG);
    int soLuong = kiemTraSoLuongFileDoiTuong(duongDan);
    if (soLuong == 0) {
        cout << "Chua co khach hang\n";
        return;
    }
    vector<KhachHang> mangFile = layDanhSachFile();

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

        ostringstream oss;
        oss << "\nDanh sach khach hang tim duoc theo ten '" << keyword << "':\n";
        oss << left << setw(5) << "STT" << setw(20) << "Ten khach hang"
            << setw(20) << "So dien thoai" << setw(15) << "Diem tich luy" << "\n";

        int stt = 1;
        for (int i = 0; i < soLuong; i++) {
            if (mangFile[i].getName().find(keyword) != string::npos) {
                oss << left << setw(5) << stt++
                    << setw(20) << mangFile[i].getName()
                    << setw(20) << mangFile[i].getPhoneNum()
                    << fixed << setprecision(2) << setw(15) << mangFile[i].getPoint() << "\n";
            }
        }
        cout << oss.str();
    } else if (luaChon == 2) {
        cout << "Nhap so dien thoai khach hang: ";
        getline(cin, keyword);

        ostringstream oss;
        oss << "\nDanh sach khach hang tim duoc theo so dien thoai '" << keyword << "':\n";
        oss << left << setw(5) << "STT" << setw(20) << "Ten khach hang"
            << setw(20) << "So dien thoai" << setw(15) << "Diem tich luy" << "\n";

        int stt = 1;
        for (int i = 0; i < soLuong; i++) {
            if (mangFile[i].getPhoneNum().find(keyword) != string::npos) {
                oss << left << setw(5) << stt++
                    << setw(20) << mangFile[i].getName()
                    << setw(20) << mangFile[i].getPhoneNum()
                    << fixed << setprecision(2) << setw(15) << mangFile[i].getPoint() << "\n";
            }
        }
        cout << oss.str();
    }
}

void QuanLiKhach::capNhatMangTuFile() {
    string duongDan = docFileQuanLi(LUA_CHON_KHACH_HANG);
    int soLuong = kiemTraSoLuongFileDoiTuong(duongDan);
    if(soLuong == 0) {
        cout << "Khong co du lieu trong file\n";
        return;
    }

    vector<KhachHang> mangFile = layDanhSachFile();
    int soKhachMang = soLuongMang();
    int coMat = 0;
    for(int i = 0; i < soLuong; i++) {
        coMat = 0;
        if(soLuong >= QuanLiKhach::gioiHanMang) {
            cout << "Mang da day\n";
            break;
        }

        for(int j = 0; j < soKhachMang; j++) {
            if (mangFile[i].getPhoneNum() == danhSachMang[j].getPhoneNum()) {
                danhSachMang[j].saoChepKhach(mangFile[i]);
                coMat = 1;
                break;
            }
        }

        if (!coMat) {
            danhSachMang.push_back(mangFile[i]);
        }
    }

    cout << "Cap nhat thanh cong\n";
}

void QuanLiKhach::capNhatFileTuMang() const {
    int soMang = soLuongMang();
    if (soMang == 0) {
        cout << "Khong co du lieu trong mang\n";
        return;
    }

    string duongDan = docFileQuanLi(LUA_CHON_KHACH_HANG);
    int soLuongFile = kiemTraSoLuongFileDoiTuong(duongDan);

    vector<KhachHang> danhSachKhachFile = layDanhSachFile();
    vector<KhachHang> danhSachMoi;

    for (int i = 0; i < soLuongFile; i++) {
        danhSachMoi.push_back(danhSachKhachFile[i]);
    }

    int coMat = 0;
    for (int i = 0; i < soMang; i++) {
        coMat = 0;
        for (int j = 0; j < soLuongFile; j++) {
            if (danhSachMang[i].getPhoneNum() == danhSachKhachFile[j].getPhoneNum()) {
                danhSachMoi[j].saoChepKhach(danhSachMang[i]);
                coMat = 1;
                break;
            }
        }

        if (!coMat) {
            danhSachMoi.push_back(danhSachMang[i]);
        }
    }

    resetFile();
    themNhieuDoiTuongVaoFile(danhSachMoi);

    cout << "Cap nhat thanh cong\n";
}

