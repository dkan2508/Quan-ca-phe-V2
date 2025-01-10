#pragma once

// Cac constant de lam viec voi file
#define NGAN_PHAN_TU_CSV ","
#define PLACEHOLDER_QUAN_LY "<placeholder>\n" // Placeholder de xay dung cau truc file quan ly
#define SO_DOI_TUONG_LAM_VIEC 4 // kho, khach, hoa don, menu
#define MANAGING_FILE "./pathFile.txt" // Duong dan den file luu tru duong dan
#define MAX_DONG_DU_LIEU 1000 // Do dai toi da co the doc duoc trong mot lan doc tu mot file doi tuong bat ky
#define MAX_FILE_PATH_LENGTH 200 // Do dai toi da xau duong dan file

// Cac constant quy dinh lua chon doi tuong
#define LUA_CHON_KHACH_HANG 1
#define LUA_CHON_HOA_DON 2
#define LUA_CHON_KHO 3
#define LUA_CHON_MENU 4

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

typedef struct {
    int ngay;
    int thang;
    int nam;
} Ngay; // Dinh nghia doi tuong ngay
int coNhuNhauNgay(Ngay n1, Ngay n2); // Kiem tra xem hai doi tuong ngay co la mot
void saoChepNgay(Ngay* ngayNhan, Ngay* ngayNguon); // Deep-copy hai doi tuong ngay

// Cac ham ho tro xu ly file quan ly duong dan
void docFileQuanLi(int luaChon, char duongDan[]); // Doc mot duong dan tu file quan ly
void capNhatFileQuanLi(int luaChon, char duongDanMoi[]); // Thay doi mot duong dan trong file quan ly

// Ham bo tro
void saferScanf(char formatString[], void* addr); // Warper cho ham scanf, bat buoc nguoi dung nhap cho den khi dung kieu du lieu

// Cac ham chung
// Xem thong tin cua mang hoac file
void xemDanhSach(void (*docFile)(char duongDan[], int soPhanTuDoc, void* danhSach), int (*kiemTraSoLuong)(char duongDan[]),
                    void (*hienThi)(void* mang, int soPhanTuMang), char fileQuanLi[], int soLuongHienTai, int doLonVat, void* danhSachHienTai);
// Xoa mot phan tu trong mang hoac file
void xoaPhanTu(void (*xoaMang)(void* mang, int* soLuong, void* vat), void (*xoaFile)(char duongDan[], void* vat),
                void (*nhapThongTin)(void* vatThe, void* mang, int soLuong), int* soPhanTuMang, void* mangHienTai, int* soPhanTuMangDieuKien,
                void* mangDieuKien, int* soPhanTuFile, void* vatXoa, char duongDan[]);
// Them mot phan tu vao mang hoac file
void themPhanTu(void (*nhapThongTin)(void* vat, void* mang, int soLuongMang), void (*themVaoFile)(char duongDan[], void* vatThem),
                void (*themVaoMang)(void* mang, int* soLuongMang, void* vatThem), void* mangHienTai, int* soLuongMangHienTai, void* mangDieuKien, int* soLuongMangDieuKien,
                int* soLuongFile, int gioiHan, void* vatThem, char duongDan[]);
// Cap nhat du lieu tu mang vao file hoac nguoc lai
void capNhatDuLieu(void (*capNhatMangTuFile)(void* mang, int* soLuongMang, char duongDan[], int* soLuongFile),
                    void (*capNhatFileTuMang)(void* mang, int* soLuongMang, char duongDan[], int* soLuongFile),
                    void* mangHienTai,int* soLuongMang, int* soLuongFile, char duongDan[]);
// Tim kiem du lieu trong mang hoac file
void timKiemDuLieu(void (*timKiem)(void* mang, int soLuongMang), void (*docFile)(char duongDan[], int soLuongDoc, void* mangFile),
                    void* mangHienTai, int soLuongMang, int soLuongFile, char duongDan[], int doLonVat);

// Xoa toan bo du lieu trong file
void resetFile(int luaChon);
// Xoa du lieu trong mang hoac goi ham resetFile
void reset(int* soPhanTuHienTai, int luaChonDoiTuong);
