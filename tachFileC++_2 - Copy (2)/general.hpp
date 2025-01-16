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
#define MANAGING_FILE "pathFile.txt" // Duong dan den file luu tru duong dan
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
#define HOA_DON_HEADER "tenKhachHang,soDienThoai,diemTichLuyKhach," \
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
#define KHACH_HANG_HEADER "tenKhachHang,soDienThoai,diemTichLuy\n"
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
                    "tenNguyenLieu1,donViNguyenLieu1,soLuongNguyenLieu1,giaNguyenLieu1," \
                    "tenNguyenLieu2,donViNguyenLieu2,soLuongNguyenLieu2,giaNguyenLieu2," \
                    "tenNguyenLieu3,donViNguyenLieu3,soLuongNguyenLieu3,giaNguyenLieu3," \
                    "tenNguyenLieu4,donViNguyenLieu4,soLuongNguyenLieu4,giaNguyenLieu4," \
                    "tenNguyenLieu5,donViNguyenLieu5,soLuongNguyenLieu5,giaNguyenLieu5," \
                    "tenNguyenLieu6,donViNguyenLieu6,soLuongNguyenLieu6,giaNguyenLieu6," \
                    "tenNguyenLieu7,donViNguyenLieu7,soLuongNguyenLieu7,giaNguyenLieu7," \
                    "tenNguyenLieu8,donViNguyenLieu8,soLuongNguyenLieu8,giaNguyenLieu8," \
                    "tenNguyenLieu9,donViNguyenLieu9,soLuongNguyenLieu9,giaNguyenLieu9," \
                    "tenNguyenLieu10,donViNguyenLieu10,soLuongNguyenLieu10,giaNguyenLieu10," \
                    "tenNguyenLieu11,donViNguyenLieu11,soLuongNguyenLieu11,giaNguyenLieu11," \
                    "tenNguyenLieu12,donViNguyenLieu12,soLuongNguyenLieu12,giaNguyenLieu12," \
                    "tenNguyenLieu13,donViNguyenLieu13,soLuongNguyenLieu13,giaNguyenLieu13," \
                    "tenNguyenLieu14,donViNguyenLieu14,soLuongNguyenLieu14,giaNguyenLieu14," \
                    "tenNguyenLieu15,donViNguyenLieu15,soLuongNguyenLieu15,giaNguyenLieu15," \
                    "tenNguyenLieu16,donViNguyenLieu16,soLuongNguyenLieu16,giaNguyenLieu16," \
                    "tenNguyenLieu17,donViNguyenLieu17,soLuongNguyenLieu17,giaNguyenLieu17," \
                    "tenNguyenLieu18,donViNguyenLieu18,soLuongNguyenLieu18,giaNguyenLieu18," \
                    "tenNguyenLieu19,donViNguyenLieu19,soLuongNguyenLieu19,giaNguyenLieu19," \
                    "tenNguyenLieu20,donViNguyenLieu20,soLuongNguyenLieu20,giaNguyenLieu20," \
                    "tenNguyenLieu21,donViNguyenLieu21,soLuongNguyenLieu21,giaNguyenLieu21," \
                    "tenNguyenLieu22,donViNguyenLieu22,soLuongNguyenLieu22,giaNguyenLieu22," \
                    "tenNguyenLieu23,donViNguyenLieu23,soLuongNguyenLieu23,giaNguyenLieu23," \
                    "tenNguyenLieu24,donViNguyenLieu24,soLuongNguyenLieu24,giaNguyenLieu24," \
                    "tenNguyenLieu25,donViNguyenLieu25,soLuongNguyenLieu25,giaNguyenLieu25," \
                    "tenNguyenLieu26,donViNguyenLieu26,soLuongNguyenLieu26,giaNguyenLieu26," \
                    "tenNguyenLieu27,donViNguyenLieu27,soLuongNguyenLieu27,giaNguyenLieu27," \
                    "tenNguyenLieu28,donViNguyenLieu28,soLuongNguyenLieu28,giaNguyenLieu28," \
                    "tenNguyenLieu29,donViNguyenLieu29,soLuongNguyenLieu29,giaNguyenLieu29," \
                    "tenNguyenLieu30,donViNguyenLieu30,soLuongNguyenLieu30,giaNguyenLieu30," \
                    "soNguyenLieu\n"
#define MAX_MON 30 // So luong mon an toi da trong menu
#define DO_DAI_TEN_MON 50 // Do dai toi da cua ten mon
#define MAX_ARRAY_LENGTH_MENU 3000 // Do dai toi da cua chuoi doc du lieu tu file menu

string docFileQuanLi(int luaChon);
void capNhatFileQuanLi(int luaChon, string duongDanMoi); // Thay doi mot duong dan trong file quan ly
int kiemTraSoLuongFileDoiTuong(string duongDan);

// Ham bo tro
void saferScanf(const char formatString[], void* addr); // Warper cho ham scanf, bat buoc nguoi dung nhap cho den khi dung kieu du lieu
void thongBaoLoi(const string thongBao); // Hien thong bao loi

// Xoa toan bo du lieu trong file
void khoiTaoLaiFile(int luaChon);

class Ngay {
    private:
        int ngay;
        int thang;
        int nam;
    public:
        Ngay(int ngay=0, int thang=0, int nam=0);

        int getNgay() const;
        void setNgay(const int);
        int getThang() const;
        void setThang(const int);
        int getNam() const;
        void setNam(const int);

        int coNhuNhauNgay(const Ngay&) const;
        void saoChepNgay(const Ngay&);
        void nhapNgay();
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
        QuanLiDanhSach(int maxMang, int maxFile, int luaChon, string dauDan, vector<T> mang={}) : gioiHanMang(maxMang), gioiHanFile(maxFile), luaChonDoiTuong(luaChon), dauDanFile(dauDan), danhSachMang{} {};

        int soLuongMang() const {
            return danhSachMang.size();
        }

        int soLuongFile() const {
            return kiemTraSoLuongFileDoiTuong(docFileQuanLi(luaChonDoiTuong));
        }

        vector<T> layDanhSachMang() const {
            return danhSachMang;
        };

        vector<T>& layDanhSachMangRef() {
            return danhSachMang;
        }

        void setDanhSachMang(vector<T> v) {
            danhSachMang = v;
        }

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
                ofstr << layXauDoiTuong(mangThem[i]);
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

        int timPhanTu(const vector<T>& danhSach, const T& doiTuong) const {
            // Su dung dieu kien doi tuong ton tai, khong phai dieu kien hoan toan giong nhau
            // Tra ve vi tri doi tuong neu tim thay, khong thi -1
            for(int i = 0; i < danhSach.size(); i++) {
                if(doiTuong.coLaMotDoiTuong(danhSach[i]) == 1) {
                    return i;
                }
            }
            return -1;
        }

        void xoaPhanTuMang() {
            int soLuong = danhSachMang.size();
            if(soLuong == 0) {
                cout << "Chua co doi tuong\n";
                return;
            }

            T vatXoa;
            vatXoa.nhapThongTinNhanDang();

            int status = timPhanTu(danhSachMang, vatXoa);
            if(status != -1) {
                danhSachMang.erase(danhSachMang.begin() + status); // Cu phap xoa phan tu cho vecto
                cout << "Xoa doi tuong thanh cong\n";
            } else {
                cout << "Khong tim thay doi tuong\n";
            }
        }

        void xoaPhanTuFile() {
            string duongDan = docFileQuanLi(luaChonDoiTuong);
            int soLuong = kiemTraSoLuongFileDoiTuong(duongDan);
            if(soLuong == 0) {
                cout << "Chua co doi tuong\n";
                return;
            }
            vector<T> danhSachFile = layDanhSachFile(docFileQuanLi(luaChonDoiTuong));

            T vatXoa;
            vatXoa.nhapThongTinNhanDang();
            
            int status = timPhanTu(danhSachFile, vatXoa);
            if(status == -1) {
                cout << "Khong tim thay doi tuong\n";
                return;
            }

            danhSachFile.erase(danhSachFile.begin() + status);

            ofstream ofstr(duongDan, ios::out);
            if(!ofstr.is_open()) {
                thongBaoLoi("Khong the xoa khoi file: ");
                return;
            }

            ofstr << dauDanFile;
            for(int i = 0; i < danhSachFile.size(); i++) {
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

            T doiTuongThem;
            doiTuongThem.nhapThongTin();

            int status = timPhanTu(danhSachMang, doiTuongThem);
            if(status == -1) {
                danhSachMang.push_back(doiTuongThem);
                cout << "Da them vao mang\n";
            } else {
                cout << "Doi tuong da ton tai\n";
            }
        };
        
        void themPhanTuFile() {
            string duongDan = docFileQuanLi(luaChonDoiTuong);
            int soLuong = kiemTraSoLuongFileDoiTuong(duongDan);
            vector<T> danhSachFile = layDanhSachFile(docFileQuanLi(luaChonDoiTuong));

            T doiTuongThem;
            doiTuongThem.nhapThongTin();

            int status = timPhanTu(danhSachFile, doiTuongThem);
            if(status != -1) {
                cout << "Doi tuong da ton tai\n";
                return;
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

        void hienThiMang() const {
            int soLuong = soLuongMang();
            if (soLuong == 0) {
                cout << "Chua co doi tuong\n";
                return;
            }
            hienThi(danhSachMang);    
        }

        void hienThiFile() const {
            string duongDan = docFileQuanLi(luaChonDoiTuong);
            int soLuong = soLuongFile();
            if (soLuong == 0 || soLuong == -1) {
                cout << "Chua co doi tuong\n";
                return;
            }

            vector<T> danhSachFile = layDanhSachFile(duongDan);
            hienThi(danhSachFile);
        }

        void timKiemMang() {
            int soLuong = soLuongMang();
            if (soLuong == 0) {
                cout << "Chua co doi tuong\n";
                return;
            }
            timKiem(danhSachMang);  
        }

        void timKiemFile() {
            string duongDan = docFileQuanLi(luaChonDoiTuong);
            int soLuong = soLuongFile();
            if (soLuong == 0) {
                cout << "Chua co doi tuong\n";
                return;
            }

            vector<T> danhSachFile = layDanhSachFile(duongDan);
            timKiem(danhSachFile);
        }

        void capNhatDanhSach(const vector<T> dsNguon, vector<T>& dsNhan, const int gioiHanNhan) {
            vector<T> danhSachMoi = dsNhan;

            int status = 0;
            for (int i = 0; i < dsNguon.size(); i++) {
                if(danhSachMoi.size() >= gioiHanNhan) {
                    cout << "Danh sach nhan du lieu da day\n";
                    return;
                }
                status = timPhanTu(danhSachMoi, dsNguon[i]);
                if(status == -1) {
                    danhSachMoi.push_back(dsNguon[i]);
                } else {
                    danhSachMoi[status].saoChepThongTin(dsNguon[i]);
                }
            }

            dsNhan = danhSachMoi;
        }

        void capNhatMangTuFile() {
            string duongDan = docFileQuanLi(luaChonDoiTuong);
            int soLuongFile = kiemTraSoLuongFileDoiTuong(duongDan);
            if(soLuongFile == 0) {
                cout << "Khong co du lieu trong file\n";
                return;
            }

            vector<T> dsFile = layDanhSachFile(duongDan);
            capNhatDanhSach(dsFile, danhSachMang, gioiHanMang);
            cout << "Cap nhat thanh cong\n";
        }

        void capNhatFileTuMang() {
            int soLuong = soLuongMang();
            if(soLuong == 0) {
                cout << "Khong co du lieu trong mang\n";
                return;
            }

            vector<T> dsFile;
            capNhatDanhSach(danhSachMang, dsFile, gioiHanFile);

            resetFile();
            themNhieuDoiTuongVaoFile(dsFile);
        }

        virtual string layXauDoiTuong(const T& doiTuong) const = 0; // Tao ra mot string thong tin cua vat tuong ung voi format file csv
        virtual T taoDoiTuongTuXau(string xauThongTin) const = 0;
        virtual void hienThi(const vector<T>& danhSach) const = 0;
        virtual void timKiem(const vector<T>& danhSach) const = 0;
};

// Cac ham chung
// Xem thong tin cua mang hoac file
template <class T>
void xemDanhSach(const T danhSach) {
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

// Xoa du lieu trong mang hoac goi ham resetFile
template <class T>
void timKiemDuLieu(T danhSach) {
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
