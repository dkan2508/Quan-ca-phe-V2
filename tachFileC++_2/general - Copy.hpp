#pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
using namespace std;

// Cac constant de lam viec voi file
#define NGAN_PHAN_TU_CSV ','
#define PLACEHOLDER_QUAN_LY "<placeholder>\n" // Placeholder de xay dung cau truc file quan ly
#define SO_DOI_TUONG_LAM_VIEC 4 // kho, khach, hoa don, menu
#define MANAGING_FILE "./pathFile.txt" // Duong dan den file luu tru duong dan
#define MAX_DONG_DU_LIEU 1000 // Do dai toi da co the doc duoc trong mot lan doc tu mot file doi tuong bat ky
#define MAX_FILE_PATH_LENGTH 200 // Do dai toi da xau duong dan file

// Cac constant quy dinh lua chon, lam viec doi tuong
#define LUA_CHON_KHACH_HANG 1
#define LUA_CHON_HOA_DON 2
#define LUA_CHON_KHO 3
#define LUA_CHON_MENU 4
#define KHONG_GIOI_HAN INT16_MAX

// Cac constant cho doi tuong hoa don
#define SO_LUONG_TOI_DA_MOI_MON 10000 // Su dung de khoi tao so luong mon toi da co the tao dua vao nguyen lieu trong kho. Goi trong ham thanh toan
#define MAX_HOA_DON 100 // So luong toi da mang hoa don
#define HOA_DON_HEADER "tenT,soDienThoai,diemTichLuyKhach," \
                       "ngayNhap,thangNhap,namNhap," \
                       "soMon1,soMon2,soMon3,soMon4,soMon5,soMon6,soMon7,soMon8,soMon9,soMon10," \
                       "soMon11,soMon12,soMon13,soMon14,soMon15,soMon16,soMon17,soMon18,soMon19,soMon20," \
                       "soMon21,soMon22,soMon23,soMon24,soMon25,soMon26,soMon27,soMon28,soMon29,soMon30," \
                       "tenMon1,tenMon2,tenMon3,tenMon4,tenMon5,tenMon6,tenMon7,tenMon8,tenMon9,tenMon10," \
                       "tenMon11,tenMon12,tenMon13,tenMon14,tenMon15,tenMon16,tenMon17,tenMon18,tenMon19,tenMon20," \
                       "tenMon21,tenMon22,tenMon23,tenMon24,tenMon25,tenMon26,tenMon27,tenMon28,tenMon29,tenMon30," \
                       "giaMon1,giaMon2,giaMon3,giaMon4,giaMon5,giaMon6,giaMon7,giaMon8,giaMon9,giaMon10," \
                       "giaMon11,giaMon12,giaMon13,giaMon14,giaMon15,giaMon16,giaMon17,giaMon18,giaMon19,giaMon20," \
                       "giaMon21,giaMon22,giaMon23,giaMon24,giaMon25,giaMon26,giaMon27,giaMon28,giaMon29,giaMon30," \
                       "soMonGoi,tongTien,tienThua,tienNguyenLieu\n"
#define MAX_ARRAY_LENGTH_HOA_DON 3000 // Do dai toi da cua xau doc thong tin tu file hoa don

// Cac constant cho doi tuong khach hang
#define MAX_KHACH_HANG 100 // So luong toi da khach hang trong mang
#define MAX_ARRAY_LENGTH_KHACH_HANG 75 // Do dai toi da cua xau doc thong tin tu file khach hang
#define KHACH_HANG_HEADER "tenT,soDienThoai,diemTichLuy\n"
#define DO_DAI_TEN_KHACH 50 // Do dai toi da cua ten khach hang
#define DO_DAI_SO_DIEN_THOAI 15 // Do dai toi da cua xau so dien thoai

// Cac constant lam viec voi doi tuong kho
#define KHO_HEADER "tenNguyenLieu,donVi,soLuong,gia\n"
#define MAX_DO_DAI_TEN_NGUYEN_LIEU 50 
#define MAX_DO_DAI_CHUOI_DON_VI 15
#define MAX_ARRAY_LENGTH_KHO 70
#define MAX_NGUYEN_LIEU 20 // So luong nguyen lieu toi da ca trong mang kho va trong file

// Cac constant lam viec voi doi tuong menu
#define MENU_HEADER "tenMon,gia," \
                    "tenNguyenLieu1,tenNguyenLieu2,tenNguyenLieu3,tenNguyenLieu4,tenNguyenLieu5,tenNguyenLieu6,tenNguyenLieu7,tenNguyenLieu8,tenNguyenLieu9,tenNguyenLieu10," \
                    "tenNguyenLieu11,tenNguyenLieu12,tenNguyenLieu13,tenNguyenLieu14,tenNguyenLieu15,tenNguyenLieu16,tenNguyenLieu17,tenNguyenLieu18,tenNguyenLieu19,tenNguyenLieu20," \
                    "donViNguyenLieu1,donViNguyenLieu2.donViNguyenLieu3,donViNguyenLieu4,donViNguyenLieu5,donViNguyenLieu6,donViNguyenLieu7,donViNguyenLieu8,donViNguyenLieu9,donViNguyenLieu10," \
                    "donViNguyenLieu11,donViNguyenLieu12,donViNguyenLieu13,donViNguyenLieu14,donViNguyenLieu15,donViNguyenLieu16,donViNguyenLieu17,donViNguyenLieu18,donViNguyenLieu19,donViNguyenLieu20," \
                    "soLuongNguyenLieu1,soLuongNguyenLieu2,soLuongNguyenLieu3,soLuongNguyenLieu4,soLuongNguyenLieu5,soLuongNguyenLieu6,soLuongNguyenLieu7,soLuongNguyenLieu8,soLuongNguyenLieu9,soLuongNguyenLieu10," \
                    "soLuongNguyenLieu11,soLuongNguyenLieu12,soLuongNguyenLieu13,soLuongNguyenLieu14,soLuongNguyenLieu15,soLuongNguyenLieu16,soLuongNguyenLieu17,soLuongNguyenLieu18,soLuongNguyenLieu19,soLuongNguyenLieu20," \
                    "giaNguyenLieu1,giaNguyenLieu2,giaNguyenLieu3,giaNguyenLieu4,giaNguyenLieu5,giaNguyenLieu6,giaNguyenLieu7,giaNguyenLieu8,giaNguyenLieu9,giaNguyenLieu10," \
                    "giaNguyenLieu11,giaNguyenLieu12,giaNguyenLieu13,giaNguyenLieu14,giaNguyenLieu15,giaNguyenLieu16,giaNguyenLieu17,giaNguyenLieu18,giaNguyenLieu19,giaNguyenLieu20," \
                    "soNguyenLieu\n" 
#define MAX_MON 30 // So luong mon an toi da trong menu
#define DO_DAI_TEN_MON 50 // Do dai toi da cua ten mon
#define MAX_ARRAY_LENGTH_MENU 3000 // Do dai toi da cua chuoi doc du lieu tu file menu

class Ngay {
    private:
        int ngay;
        int thang;
        int nam;
    public:
        Ngay();
        Ngay(int, int, int);

        int getNgay();
        void setNgay(int);
        int getThang();
        void setThang(int);
        int getNam();
        void setNam(int);

        int coNhuNhauNgay(const Ngay&) const;
        void saoChepNgay(const Ngay&);
};

class DoiTuongLamViec {
    private:
    public:
        virtual int doiTuongCoNhuNhau(const DoiTuongLamViec& other) const = 0; // Thong tin can thiet de coi hai doi tuong la mot (VD voi khach hang thi do la sdt)
        virtual int coLaMotDoiTuong(const DoiTuongLamViec& other) const = 0;
        virtual void nhapThongTinNhanDang() = 0;
        virtual void nhapThongTin() = 0;
        virtual void saoChepThongTin(const DoiTuongLamViec& other) = 0;
};

template <class T>
class QuanLiDanhSach {
    private:
    protected:
        const int gioiHanMang;
        const int gioiHanFile;
        const int luaChonDoiTuong;
        const string dauDanFile;
        vector<T> danhSachMang;
    public:
        QuanLiDanhSach(int maxMang, int maxFile, int luaChon, string dauDan) : gioiHanMang(maxMang), gioiHanFile(maxFile), luaChonDoiTuong(luaChon), dauDanFile(dauDan) {};

        int soLuongMang() const {
            return danhSachMang.size();
        }

        int soLuongFile() const {
            return kiemTraSoLuongFileDoiTuong(docFileQuanLi(luaChonDoiTuong));
        }

        vector<T> layDanhSachMang() {
            return danhSachMang;
        };

        int layGioiHanMang() const {
            return gioiHanMang;
        };
        
        int layGioiHanFile() const {
            return gioiHanFile;
        };

        void resetMang() {
            danhSachMang.resize(0);
        };

        void resetFile() const {
            khoiTaoLaiFile(luaChonDoiTuong);
        };
        
        void themNhieuDoiTuongVaoFile(vector<T> mangThem) const {
            string duongDan = docFileQuanLi(luaChonDoiTuong);
            ofstream ofstr(duongDan, ios::app);
            if(!ofstr.is_open()) {
                thongBaoLoi("Khong the them doi tuong vao file: ");
                return;
            }

            for(int i = 0; i < mangThem.size(); i++) {
                ofstr << xauDoiTuong(mangThem[i]);
            }

            ofstr.close();
        };  

        vector<T> layDanhSachFile(const string duongDan) const {
            int soLuong = kiemTraSoLuongFileDoiTuong(duongDan);
            vector<T> danhSachFile;

            if(soLuong == 0) {
                return danhSachFile;
            }

            ifstream ifstr(duongDan, ios::in);
            if(!ifstr.is_open()) {
                thongBaoLoi("Khong mo duoc file de doc doi tuong: ");
                return danhSachFile;
            }

            string line;
            getline(ifstr, line); // Skip header

            for(int i = 0; i < soLuong; i++) {
                if(!getline(ifstr, line)) {
                    thongBaoLoi("Khong the doc file doi tuong: ");
                    ifstr.close();
                    return danhSachFile;
                }
                danhSachFile.push_back(taoDoiTuongTuXau(line));
            }

            ifstr.close();
            return danhSachFile;
        };        

        void xoaPhanTu(vector<T>& mangXuLi) {
            int soLuong = mangXuLi.size();
            if(soLuong == 0) {
                cout << "Chua co doi tuong\n";
                return;
            }

            T vatXoa();
            vatXoa.nhapThongTinNhanDang();

            for(int i = 0; i < soLuong; i++) {
                if(vatXoa.coLaMotDoiTuong(mangXuLi[i]) == 1) {
                    mangXuLi.erase(i);
                    cout << "Doi tuong da duoc xoa\n";
                    return;
                }
            }

            cout << "Khong tim thay doi tuong\n";
        };

        void xoaPhanTuMang() {
            xoaPhanTu(danhSachMang);
        }

        void xoaPhanTuFile() {
            string duongDan = docFileQuanLi(luaChonDoiTuong);
            int soLuong = kiemTraSoLuongFileDoiTuong(duongDan);
            if(soLuong == 0) {
                cout << "Chua co doi tuong\n";
                return;
            }
            vector<T> danhSachFile = layDanhSachFile();

            T vatXoa();
            vatXoa.nhapThongTinNhanDang();
            
            int coMat = 0;
            for(int i = 0; i < soLuong; i++) {
                if(vatXoa.coLaMotDoiTuong(danhSachFile[i]) == 1) {
                    danhSachFile.erase(i);
                    coMat = 1;
                    break;
                }
            }
            if(coMat == 0) {
                cout << "Khong tim thay doi tuong\n";
                return;
            }

            ofstream ofstr(duongDan, ios::out);
            ofstr << dauDanFile;
            for(int i = 0; i < soLuong; i++) {
                ofstr << layXauDoiTuong(danhSachFile[i]);
            }
            cout << "Xoa khach khoi file thanh cong\n";
            ofstr.close();
        };

        void themPhanTuMang() {
            int soLuong = soLuongMang();
            if(soLuong >= gioiHanMang) {
                cout << "Mang da day\n";
                return;
            }

            T doiTuongThem();
            doiTuongThem.nhapThongTin();

            for(int i = 0; i < soLuong; i++) {
                if(doiTuongThem.coLaMotDoiTuong(danhSachMang[i]) == 1) {
                    cout << "Doi tuong da co trong mang\n";
                    return;
                }
            }

            danhSachMang.push_back(doiTuongThem());
            cout << "Da them vao mang\n";
        };
        
        void themPhanTuFile() {
            string duongDan = docFileQuanLi(luaChonDoiTuong);
            int soLuong = kiemTraSoLuongFileDoiTuong(duongDan);
            vector<T> danhSachFile = layDanhSachFile();

            T doiTuongThem();
            doiTuongThem.nhapThongTin();

            for(int i = 0; i < soLuong; i++) {
                if(doiTuongThem.coLaMotDoiTuong(danhSachFile[i]) == 1) {
                    cout << "Doi tuong da co trong file\n";
                    return;
                }
            }

            ofstream ofstr(duongDan, ios::app);
            if(!ofstr.is_open()) {
                thongBaoLoi("Khong the them doi tuong vao file: ");
                return;
            }

            ofstr << layXauDoiTuong(doiTuongThem);
            
            cout << "Doi tuong da duoc them\n";

            ofstr.close();
        };

        virtual string layXauDoiTuong(const T& doiTuong) const = 0; // Tao ra mot string thong tin cua vat tuong ung voi format file csv
        virtual T taoDoiTuongTuXau(const string xauThongTin) const = 0;
        virtual void hienThiMang() const = 0;
        virtual void hienThiFile() const = 0;
        virtual void capNhatMangTuFile() = 0;
        virtual void capNhatFileTuMang() const = 0;
        virtual void timKiemMang() const = 0;
        virtual void timKiemFile() const = 0;
};

// Cac ham ho tro xu ly file quan ly duong dan
string docFileQuanLi(int luaChon); // Doc mot duong dan tu file quan ly
void capNhatFileQuanLi(int luaChon, string duongDanMoi); // Thay doi mot duong dan trong file quan ly
int kiemTraSoLuongFileDoiTuong(string duongDan);

// Ham bo tro
void saferScanf(const char formatString[], void* addr); // Warper cho ham scanf, bat buoc nguoi dung nhap cho den khi dung kieu du lieu
void thongBaoLoi(const string thongBao); // Hien thong bao loi

// Cac ham chung
// Xem thong tin cua mang hoac file
template <class T>
void xemDanhSach(const T& danhSach) {
    int luaChonXem;
    cout << "Xem mang hien tai (1) hay xem tu file (2): ";
    saferScanf("%d", &luaChonXem);

    if(luaChonXem != 1 && luaChonXem != 2) {
        cout << "Lua chon khong hop le.\n";
        return;
    }

    if(luaChonXem == 1) {
        if(danhSach.soLuongMang() == 0) {
            cout << "Khong ton tai du lieu trong mang\n";
            return;
        }
        danhSach.hienThiMang();
    } else {
        if(danhSach.soLuongFile() == 0) {
            cout << "Khong ton tai du lieu trong file\n";
            return;
        }
        danhSach.hienThiFile();
    }
}

// Xoa mot phan tu trong mang hoac file
template <class T>
void reset(T& danhSach) {
    int canhCao;
    cout << "CANH BAO: VIEC NAY SE XOA TOAN BO DU LIEU CUA BAN VA KHONG THE BI DAO NGUOC. TIEP TUC? (1) ";
    saferScanf("%d", &canhCao);
    if(canhCao != 1) {
        return;
    }

    int luaChonXoa;
    cout << "Xoa du lieu mang hien tai (1) hay xoa du lieu file (2) ";
    saferScanf("%d", &luaChonXoa);
                            
    if(luaChonXoa != 1 && luaChonXoa != 2) {
        cout << "Lua chon khong hop le\n";
        return;
    } else if(luaChonXoa == 1) {
        danhSach.resetMang();
        cout << "Mang da duoc reset!\n";
    } else {
        danhSach.resetFile();
        cout << "File da duoc reset\n";
    }
}

// Them mot phan tu vao mang hoac file
template <class T>
void xoaPhanTu(T& danhSach) {
    int luaChonXoaBo;
    cout << "Xoa trong mang hien tai (1) hay xoa trong file (2): ";
    saferScanf("%d", &luaChonXoaBo);

    if(luaChonXoaBo != 1 && luaChonXoaBo != 2) {
        cout << "Lua chon khong hop le\n";
        return;
    } else if(luaChonXoaBo == 1) {
        if(danhSach.soLuongMang() == 0) {
            cout << "Mang khong co phan tu\n";
            return;
        }
        danhSach.xoaPhanTuMang();
    } else {
        if(danhSach.soLuongFile() == 0) {
            cout << "File khong co phan tu\n";
            return;
        }
        danhSach.xoaPhanTuFile();
    }
}

// Cap nhat du lieu tu mang vao file hoac nguoc lai
template <class T>
void themPhanTu(T& danhSach) {
    int luaChonThem;
    cout << "Them vao mang hien tai (1) hay them vao file (2): ";
    saferScanf("%d", &luaChonThem);
    if(luaChonThem != 1 && luaChonThem != 2) {
        cout << "Lua chon khong hop le\n";
        return;
    } else if(luaChonThem == 1) {
        if(danhSach.soLuongMang() >= danhSach.layGioiHanMang()) {
            cout << "Mang da day\n";
            return;
        }
        danhSach.themPhanTuMang();
    } else {
        if(danhSach.soLuongFile() >= danhSach.layGioiHanFile()) {
            cout << "File da day\n";
            return;
        }
        danhSach.themPhanTuFile();
    }
}

// Tim kiem du lieu trong mang hoac file
template <class T>
void capNhatDuLieu(T& danhSach) {
    int luaChonCapNhat;
    cout << "Cap nhat thong tin tu file vao mang (1) hay tu mang vao file (2) ";
    saferScanf("%d", &luaChonCapNhat);
    if(luaChonCapNhat != 1 && luaChonCapNhat != 2) {
        cout << "Lua chon khong hop le\n";
        return;
    }

    if(luaChonCapNhat == 1 && danhSach.soLuongFile() == 0) {
        cout << "File khong co mon an\n";
        return;
    } else if(luaChonCapNhat == 2 && danhSach.soLuongMang() == 0) {
        cout << "Mang khong co doi tuong\n";
        return;
    }

    if(luaChonCapNhat == 1) {
        danhSach.capNhatMangTuFile();
    } else {
        danhSach.capNhatFileTuMang();
    }
}

// Xoa toan bo du lieu trong file
void khoiTaoLaiFile(int luaChon);
// Xoa du lieu trong mang hoac goi ham resetFile
template <class T>
void timKiemDuLieu(const T& danhSach) {
    int luaChonTimKiem;
    cout << "Tim kiem trong mang (1) hay trong file (2): ";
    saferScanf("%d", &luaChonTimKiem);
    if (luaChonTimKiem != 1 && luaChonTimKiem != 2) {
        cout << "Lua chon khong hop le\n";
        return;
    } else if (luaChonTimKiem == 1) {
        if(danhSach.soLuongMang() == 0) {
            cout << "Chua co du lieu trong mang\n";
        }
        danhSach.timKiemMang();
    } else {
        if (danhSach.soLuongFile() == 0) {
            cout << "Chua co du lieu trong file\n";
            return;
        }
        danhSach.timKiemFile();
    }
}
