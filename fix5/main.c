#include "menu.h"

#include <stdio.h>
#include <string.h>

#define PLACEHOLDER_QUAN_LY "<placeholder>\n"

#define MAX_KHACH_HANG 100
#define MAX_HOA_DON 100
#define MAX_DONG_DU_LIEU 1000
#define LUA_CHON_KHACH_HANG 1
#define LUA_CHON_HOA_DON 2
#define LUA_CHON_KHO 3
#define LUA_CHON_MENU 4
#define MAX_FILE_PATH_LENGTH 200
#define SO_LUONG_TOI_DA_MOI_MON 10000

#define SO_DOI_TUONG_LAM_VIEC 4 // kho, khach, hoa don, menu
#define MANAGING_FILE "./pathFile.txt"

// CHANGE ???????????????????????????????????????????????????????????????????????????????//

// Khai báo các mảng để lưu menu, danh sách khách hàng và hóa đơn
MonAn menuMacDinh[MAX_MON] = {
    {"Ca phe den", 25.0, {{"Ca phe bot", "kg", 0.05, 12.00}, {"Duong", "kg", 0.01, 13.00}}, 2},
    {"Ca phe sua", 30.0, {{"Ca phe bot", "kg", 0.05, 12.00}, {"Sua dac", "hop", 0.01, 15.00}}, 2},
    {"Tra sua", 35.0, {{"Tra den", "kg", 0.01, 10.00}, {"Sua tuoi", "lit", 0.01, 20.00}}, 2},
    {"Ca phe da xay", 40.0, {{"Ca phe bot", "kg", 0.05, 12.00}, {"Da vien", "kg", 0.1, 5.00}}, 2},
    {"Nuoc cam", 20.0, {{"Cam tuoi", "kg", 0.25, 25.00}}, 1},
    {"Sinh to dua hau", 35.0, {{"Dua hau", "kg", 0.3, 10.00}, {"Sua dac", "hop", 0.02, 15.00}}, 2},
    {"Banh mi op la", 50.0, {{"Bot banh mi", "kg", 0.15, 20.00}, {"Trung ga", "qua", 1, 5.00}}, 2},
    {"Banh mi que", 20.0, {{"Bot banh mi", "kg", 0.1, 20.00}, {"Pate gan", "hop", 0.02, 30.00}}, 2},
    {"Banh bao nhan thit", 25.0, {{"Bot banh bao", "kg", 0.2, 18.00}, {"Thit heo xay", "kg", 0.1, 50.00}}, 2},
    {"Nuoc ep tao", 30.0, {{"Tao tuoi", "kg", 0.3, 15.00}, {"Duong", "kg", 0.01, 13.00}}, 2}
};

int soMonMacDinh = 10;

NguyenLieu khoNguyenLieuMacDinh[MAX_NGUYEN_LIEU] = {
    {"Ca phe bot", "kg", 10.0, 200.0},       // Price per kg
    {"Sua dac", "hop", 20.0, 15.0},         // Price per can
    {"Sua tuoi", "lit", 15.0, 12.0},        // Price per liter
    {"Duong", "kg", 8.0, 10.0},             // Price per kg
    {"Tra den", "kg", 5.0, 150.0},          // Price per kg
    {"Tran chau", "kg", 7.0, 50.0},         // Price per kg
    {"Da vien", "kg", 50.0, 5.0},           // Price per kg
    {"Cam tuoi", "kg", 12.0, 25.0},         // Price per kg
    {"Dua hau", "kg", 20.0, 10.0},          // Price per kg
    {"Bot banh mi", "kg", 25.0, 18.0},      // Price per kg
    {"Thit heo xay", "kg", 10.0, 120.0},    // Price per kg
    {"Bot banh bao", "kg", 15.0, 22.0},     // Price per kg
    {"Trung ga", "qua", 30.0, 3.0},         // Price per egg
    {"Bo", "kg", 5.0, 80.0},                // Price per kg
    {"Pate gan", "hop", 10.0, 20.0},        // Price per can
    {"Tao tuoi", "kg", 18.0, 30.0},         // Price per kg
    {"Tuong ot", "chai", 12.0, 10.0},       // Price per bottle
    {"Dau an", "lit", 10.0, 25.0},          // Price per liter
    {"Hanh tay", "kg", 8.0, 12.0},          // Price per kg
    {"Mayonnaise", "chai", 10.0, 15.0}      // Price per bottle
};


KhachHang danhSachKhachHang[MAX_KHACH_HANG];
HoaDon danhSachHoaDon[MAX_HOA_DON];
int soKhachHang = 0, soHoaDon = 0;

// Cac phan tu chi co mat de dam bao syntax, khong co vai tro
int placeHolderArr[] = {0};
int placeHolderVal = 0;

// Cac ham lam viec voi menu va thanh toan
void hienThiMenu(MonAn menu[], int soMon);
void xoaMonAn(MonAn menu[], int* soMonAn, MonAn* monXoa);
void themMonAnVaoMang(MonAn menu[], int* soMon, MonAn* monThem);
void nhapThongTinMonAn(MonAn* monAn, NguyenLieu kho[], int soNguyenLieuKho);
void nhapTenMonAn(MonAn* monAn, NguyenLieu kho[], int soNguyenLieuKho);
void chuanHoaMonAn(MonAn* monAn, int soLuongMonAn);
void thanhToan(MonAn menu[], int soMon, HoaDon danhSachHoaDon[], int *soHoaDon,
                KhachHang danhSachKhachHang[], int *soKhachHang, NguyenLieu kho[], int soNguyenLieuKho, char duongDanFileKhach[]);
void capNhatMonAnTuFile(MonAn menu[], int* soMonMang, char duongDan[], int* soMonFile);
void capNhatMonAnTuMang(MonAn menu[], int* soMonMang, char duongDan[], int* soMonFile);

// Cac ham lam viec voi hoa don
void xemHoaDon(HoaDon danhSachHoaDon[], int soHoaDon);
void timKiemHoaDon(HoaDon danhSachHoaDon[], int soHoaDon);
void xoaHoaDon(HoaDon danhSach[], int* soLuong, HoaDon* hoaDonXoa);
void nhapThongTinHoaDon(HoaDon* hoaDon, MonAn menu[], int soMon);
void capNhatHoaDonTuMang(HoaDon danhSachHoaDon[], int* soHoaDon, char duongDan[], int* soHoaDonFile);
void capNhatHoaDonTuFile(HoaDon danhSachHoaDon[], int* soHoaDon, char duongDan[], int* soHoaDonFile);

// Cac ham lam viec voi khach hang
void themKhachHang(KhachHang danhSachKhachHang[], int *soKhachHang, KhachHang* khachHangMoi);
void xemDanhSachKhachHang(KhachHang danhSachKhachHang[], int soKhachHang);
void timKiemKhachHang(KhachHang danhSachKhachHang[], int soKhachHang);
void xoaKhachHang(KhachHang danhSachKhach[], int* soLuong, KhachHang* khachXoa);
void nhapThongTinKhach(KhachHang* khachHang, int placeHolderArr[], int placeHolderVal);
void nhapTenSDTKhach(KhachHang* khachHang, int placeholderArr[], int placeholderVal);
void capNhatKhachTuMang(KhachHang danhSach[], int* soKhach, char duongDan[], int* soKhachFile);
void capNhatKhachTuFile(KhachHang danhSach[], int* soKhach, char duongDan[], int* soKhachFile);
void layDiemTichLuy(KhachHang danhSachKhachHang[], int soKhachHang, KhachHang* khach);

// Cac ham lam viec voi kho
void hienThiKho(NguyenLieu kho[], int soLuong);
void themNguyenLieu(NguyenLieu kho[], int* soLuong, NguyenLieu* nguyenLieuMoi);
void xoaNguyenLieu(NguyenLieu kho[], int* soLuong, NguyenLieu* nguyenLieuXoa);
int layNguyenLieu(NguyenLieu kho[], int soNguyenLieuKho, NguyenLieu nguyenLieuSuDung, int soMon);
void nhapThongTinNguyenLieu(NguyenLieu* nguyenLieu, int placeHolderArr[], int* placeHolderVal);
void nhapTenNguyenLieu(NguyenLieu* nguyenLieu, int placeHolderArr[], int* placeHolderVal);
void timKiemNguyenLieu(NguyenLieu kho[], int soNguyenLieu);
void capNhatKhoTuMang(NguyenLieu kho[], int* soLuongKho, char duongDan[], int* soLuongFile);
void capNhatKhoTuFile(NguyenLieu kho[], int* soLuongKho, char duongDan[], int* soLuongFile);

// Cac ham ho tro
void docFileQuanLi(int luatChon, char duongDan[]);
void capNhatFileQuanLi(int luaChon, char duongDanMoi[]);
void saferScanf(char formatString[], void* addr);
void clearBuffer();
void resetFile(int luaChon);

// Cac ham chung
void xemDanhSach(void (*docFile)(char duongDan[], int soPhanTuDoc, void* danhSach), int (*kiemTraSoLuong)(char duongDan[]),
                    void (*hienThi)(void* mang, int soPhanTuMang), char fileQuanLi[], int soLuongHienTai, int doLonVat, void* danhSachHienTai); // Do lon vat la sizeof() cua doi tuong
void reset(int* soPhanTuHienTai, int luaChonDoiTuong);
void xoaPhanTu(void (*xoaMang)(void* mang, int* soLuong, void* vat), void (*xoaFile)(char duongDan[], void* vat),
                void (*nhapThongTin)(void* vatThe, void* mang, int soLuong), int* soPhanTuMang, void* mangHienTai, int* soPhanTuMangDieuKien,
                void* mangDieuKien, int* soPhanTuFile, void* vatXoa, char duongDan[]);
void themPhanTu(void (*nhapThongTin)(void* vat, void* mang, int soLuongMang), void (*themVaoFile)(char duongDan[], void* vatThem),
                void (*themVaoMang)(void* mang, int* soLuongMang, void* vatThem), void* mangHienTai, int* soLuongMangHienTai, void* mangDieuKien, int* soLuongMangDieuKien,
                int* soLuongFile, int gioiHan, void* vatThem, char duongDan[]);
void capNhatDuLieu(void (*capNhatMangTuFile)(void* mang, int* soLuongMang, char duongDan[], int* soLuongFile),
                    void (*capNhatFileTuMang)(void* mang, int* soLuongMang, char duongDan[], int* soLuongFile),
                    void* mangHienTai,int* soLuongMang, int* soLuongFile, char duongDan[]);
void timKiemDuLieu(void (*timKiem)(void* mang, int soLuongMang), void (*docFile)(char duongDan[], int soLuongDoc, void* mangFile),
                    void* mangHienTai, int soLuongMang, int soLuongFile, char duongDan[], int doLonVat);

int main() {
    FILE* pathFile;
    char fileQuanLiChung[MAX_FILE_PATH_LENGTH]; // Xau hung du lieu tu docFileQuanLi() cho ba doi tuong: khach hang, hoa don, kho

    pathFile = fopen(MANAGING_FILE, "r");
    if(pathFile) { // Tep ton tai
        fclose(pathFile); // ham docFileQuanLi() se tu mo file nen phai dong file da mo o tren truoc
    } else { // Tep khong ton tai
        printf("Chu y, ban can cai dat duong dan den file quan li khach hang va hoa don!\n");
        pathFile = fopen(MANAGING_FILE, "w");
        if (!pathFile) {
            perror("Khon the tao file luu tru duong dan");
        } else {
            for(int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
                fprintf(pathFile, PLACEHOLDER_QUAN_LY);         // Quan trong, xay dung cau truc cho file quan ly
            }
            fclose(pathFile);
        }
    }

    // Cap nhat kho nguyen lieu tu du lieu trong file kho neu co du lieu trong file kho
    NguyenLieu* khoNguyenLieuSuDung;
    int soLuongNguyenLieuSuDung;
    int canFreeKhoNguyenLieu = 0;

    docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
    int soLuongNguyenLieu = kiemTraSoNguyenLieu(fileQuanLiChung);
    if(soLuongNguyenLieu != -1 && soLuongNguyenLieu != 0) { 
        khoNguyenLieuSuDung = (NguyenLieu*) malloc(sizeof(NguyenLieu) * soLuongNguyenLieu);
        if(khoNguyenLieuSuDung) {
            docFileKho(fileQuanLiChung, soLuongNguyenLieu, khoNguyenLieuSuDung);
            soLuongNguyenLieuSuDung = soLuongNguyenLieu;
            canFreeKhoNguyenLieu = 1;
        } else {
            printf("Khong the khoi tao mang dong cho kho nguyen lieu\n");
            printf("Su dung du lieu kho mac dinh\n");
            khoNguyenLieuSuDung = khoNguyenLieuMacDinh;
            soLuongNguyenLieuSuDung = MAX_NGUYEN_LIEU;
        }
    } else { // Khong the mo file hoac file trong
        printf("Su dung du lieu kho mac dinh\n");
        khoNguyenLieuSuDung = khoNguyenLieuMacDinh;
        soLuongNguyenLieuSuDung = MAX_NGUYEN_LIEU;
    }   

    // Cap nhat du lieu menu tu file
    MonAn* menuSuDung;
    int soMonSuDung;
    int canFreeMenu = 0;

    docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
    int soMonFile = kiemTraSoMonAn(fileQuanLiChung);
    if(soMonFile != -1 && soMonFile != 0) {
        menuSuDung = (MonAn*) malloc(sizeof(MonAn) * soMonFile);
        if(menuSuDung) {
            docFileMenu(fileQuanLiChung, soMonFile, menuSuDung);
            soMonSuDung = soMonFile;
            canFreeMenu = 1;
        } else {
            printf("Khong the khoi tao mang dong cho menu\n");
            printf("Su dung du lieu menu mac dinh\n");
            menuSuDung = menuMacDinh;
            soMonSuDung = soMonMacDinh;
        }
    } else {
        printf("Su dung du lieu menu mac dinh\n");
        menuSuDung = menuMacDinh;
        soMonSuDung = soMonMacDinh;
    }

    int luaChon = -1, luaChonCon = -1, luaChonCon2 = -1; // Gan mot gia tri khong phai la mot trong nx lua chon switch-case ben duoi.
                                                         // Bat buoc de dam bao gia tri khong hop le co the duoc xu li dung cach
    do {
        printf("\n--- MENU QUAN CA PHE ---\n");
        printf("1. Menu\n");
        printf("2. Thanh toan\n");
        printf("3. Hoa don\n");
        printf("4. Khach hang\n");
        printf("5. Kho\n");
        printf("6. Thong ke\n");
        printf("7. Xu li file\n");
        printf("8. Thoat\n");
        printf("Nhap lua chon: ");
        saferScanf("%d", &luaChon);
        
        switch (luaChon) {
            case 1:
                do {
                    printf("\n--- MENU ---\n");
                    printf("1. Xem danh sach mon\n");
                    printf("2. Them mon\n");
                    printf("3. Xoa mon\n");
                    printf("4. Sua mon\n");
                    printf("5. Cap nhat menu\n");
                    printf("6. Xoa du lieu menu\n");
                    printf("7. Quay lai\n");
                    printf("Nhap lua chon: ");
                    saferScanf("%d", &luaChonCon);
                    
                    switch (luaChonCon) {
                        case 1: {
                            docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                            xemDanhSach((void (*)(char*, int, void*))docFileMenu, (int (*)(char*))kiemTraSoMonAn,
                                        (void (*)(void *, int))hienThiMenu, fileQuanLiChung, soMonSuDung, sizeof(MonAn), menuSuDung);   
                            break;
                        }
                        case 2: {
                            docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                            int soMonFile = kiemTraSoMonAn(fileQuanLiChung);
                            MonAn monMoi;
                            themPhanTu((void (*)(void*, void*, int))nhapThongTinMonAn, (void (*)(char[], void*))themMonAnVaoFile, (void (*)(void*, int*, void*))themMonAnVaoMang,
                                        menuSuDung, &soMonSuDung, khoNguyenLieuSuDung, &soLuongNguyenLieuSuDung,
                                        &soMonFile, MAX_MON, &monMoi, fileQuanLiChung);
                            break;
                        }
                        case 3: {
                            docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                            int soMonFile = kiemTraSoMonAn(fileQuanLiChung);
                            MonAn monXoa;
                            xoaPhanTu((void (*)(void*, int*, void*))xoaMonAn, (void (*)(char*, void*))xoaMonAnKhoiFile,
                                        (void (*)(void*, void*, int))nhapTenMonAn, &soMonSuDung, menuSuDung, &placeHolderVal,
                                        placeHolderArr, &soMonFile, &monXoa, fileQuanLiChung);
                            break;
                        }
                        case 4: {
                            int luaChonSua;
                            printf("Sua mon trong menu hien tai (1) hay sua mon trong file menu tu file (2): ");
                            saferScanf("%d", &luaChonSua);

                            if(luaChonSua != 1 && luaChonSua != 2) {
                                printf("Lua chon khong hop le\n");
                                break;
                            }
                
                            char monThayDoi[MAX_DO_DAI_TEN_MON];
                            int timThayMon = 0;
                            int viTriMonCanSua = 0; // Index mon can sua trong menu
                            if(luaChonSua == 1) {
                                if(soMonSuDung == 0) {
                                    printf("Menu hien tai khong co mon an\n");
                                    break;
                                }
                                     
                                hienThiMenu(menuSuDung, soMonSuDung);
                                printf("Nhap ten mon an can thay doi: ");
                                fgets(monThayDoi, MAX_DO_DAI_TEN_MON - 1, stdin);
                                monThayDoi[strcspn(monThayDoi, "\n")] = '\0';

                                for(int i = 0; i < soMonSuDung; i++) {
                                    if(strcmp(monThayDoi, menuSuDung[i].tenMon) == 0) {
                                        timThayMon = 1;
                                        viTriMonCanSua = i;
                                        break;
                                    }
                                }

                                if(timThayMon == 0) {
                                    printf("Menu khong co mon: %s\n", monThayDoi);
                                    printf("Co le ban da danh thua dau cach?\n");
                                    break;
                                }

                                printf("Nhap thong tin moi cho mon can sua\n");
                                nhapThongTinMonAn(&menuSuDung[viTriMonCanSua], khoNguyenLieuSuDung, soLuongNguyenLieuSuDung);
                            } else {
                                docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                                int soMonFile = kiemTraSoMonAn(fileQuanLiChung);
                                if(soMonFile == 0) {
                                    printf("File khong co mon an\n");
                                    break;
                                }
                                MonAn* menuFile = (MonAn*) malloc(sizeof(MonAn) * soMonFile);
                                if(!menuFile) {
                                    perror("Khong the tao mang dong de sua mon trong file");
                                    break;
                                }
                                docFileMenu(fileQuanLiChung, soMonFile, menuFile);
      
                                hienThiMenu(menuFile, soMonFile);
                                printf("Nhap ten mon an can thay doi: ");
                                fgets(monThayDoi, MAX_DO_DAI_TEN_MON - 1, stdin);
                                monThayDoi[strcspn(monThayDoi, "\n")] = '\0';

                                for(int i = 0; i < soMonFile; i++) {
                                    if(strcmp(monThayDoi, menuFile[i].tenMon) == 0) {
                                        timThayMon = 1;
                                        viTriMonCanSua = i;
                                        break;
                                    }
                                }
                                if(timThayMon == 0) {
                                    printf("Menu khong co mon: %s\n", monThayDoi);
                                    printf("Co le ban da danh thua dau cach?\n");
                                    free(menuFile);
                                    break;
                                }

                                printf("Nhap thong tin moi cho mon can sua\n");
                                nhapThongTinMonAn(&menuFile[viTriMonCanSua], khoNguyenLieuSuDung, soLuongNguyenLieuSuDung);

                                resetFile(LUA_CHON_MENU);
                                themNhieuMonAnVaoFile(menuFile, soMonFile, fileQuanLiChung);

                                free(menuFile);
                            }

                            printf("Mon an da duoc sua\n");
                            break;
                        }
                        case 5: {
                            docFileQuanLi(LUA_CHON_MENU, fileQuanLiChung);
                            int soMonFile = kiemTraSoMonAn(fileQuanLiChung);
                            capNhatDuLieu((void (*)(void*, int*, char[], int*))capNhatMonAnTuFile, (void (*)(void*, int*, char[], int*))capNhatMonAnTuMang,
                                            menuSuDung, &soMonSuDung, &soMonFile, fileQuanLiChung);
                            break;
                        }
                        case 6: {
                            reset(&soMonSuDung, LUA_CHON_MENU);
                            break;
                        }
                        case 7:
                            break;
                        default:
                            printf("Lua chon khong hop le. Vui long chon lai.\n");
                            
                    }
                } while (luaChonCon != 7);
                break;
            case 2: {
                docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);
                thanhToan(menuSuDung, soMonSuDung, danhSachHoaDon, &soHoaDon, danhSachKhachHang, &soKhachHang, khoNguyenLieuSuDung, soLuongNguyenLieuSuDung, fileQuanLiChung);
                break;
            }
            case 3:
                do {
                    printf("\n--- HOA DON ---\n");
                    printf("1. Xem danh sach hoa don\n");
                    printf("2. Tim kiem hoa don\n");
                    printf("3. Them hoa don vao file\n");
                    printf("4. Xoa hoa don\n");
                    printf("5. Cap nhat file hoa don\n");
                    printf("6. Xoa du lieu hoa don\n");
                    printf("7. Quay lai\n");
                    printf("Nhap lua chon: ");
                    saferScanf("%d", &luaChonCon);
            
                    switch (luaChonCon) {
                        case 1: {
                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            xemDanhSach((void (*)(char*, int, void*))docFileHoaDon, (int (*)(char*))kiemTraSoHoaDon, (void (*)(void*, int))xemHoaDon,
                                        fileQuanLiChung, soHoaDon, sizeof(HoaDon), danhSachHoaDon);
                            break;
                        }
                        case 2: {
                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            int soFile = kiemTraSoMonAn(fileQuanLiChung);
                            timKiemDuLieu((void (*)(void*, int))timKiemHoaDon, (void (*)(char[], int, void*))docFileHoaDon, danhSachHoaDon,
                                            soHoaDon, soFile, fileQuanLiChung, sizeof(HoaDon));
                            break;
                        }
                        case 3: {
                            HoaDon hoaDonMoi;
                            nhapThongTinHoaDon(&hoaDonMoi, menuSuDung, soMonSuDung);
                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            themHoaDonVaoFile(hoaDonMoi, fileQuanLiChung);
                            break;
                        }
                        case 4: {
                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            int soHoaDonFile = kiemTraSoHoaDon(fileQuanLiChung);
                            HoaDon hoaDon;
                            xoaPhanTu((void (*)(void*, int*, void*))xoaHoaDon, (void (*)(char*, void*))xoaHoaDonKhoiFile,
                                        (void (*)(void*, void*, int))nhapThongTinHoaDon, &soHoaDon, danhSachHoaDon, &soMonSuDung,
                                        menuSuDung, &soHoaDonFile, &hoaDon, fileQuanLiChung);
                            break;
                        }
                        case 5: {
                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            int soHoaDonFile = kiemTraSoHoaDon(fileQuanLiChung);
                            capNhatDuLieu((void (*)(void*, int*, char[], int*))capNhatHoaDonTuFile, (void (*)(void*, int*, char[], int*))capNhatHoaDonTuMang,
                                            danhSachHoaDon, &soHoaDon, &soHoaDonFile, fileQuanLiChung);
                            break;
                        }
                        case 6: {
                            reset(&soHoaDon, LUA_CHON_HOA_DON);
                            break;
                        }
                        case 7:
                            break;
                        default:
                            printf("Lua chon khong hop le. Vui long chon lai.\n");
                    }
                } while (luaChonCon != 7);
                break;
            case 4:
                do {
                    printf("\n--- KHACH HANG ---\n");
                    printf("1. Xem danh sach khach hang\n");
                    printf("2. Tim kiem khach hang\n");
                    printf("3. Them khach hang\n"); // Them thu cong mot khach hang
                    printf("4. Xoa khach hang\n");  // Xoa thu cong mot khach hang
                    printf("5. Cap nhat du lieu khach hang\n");
                    printf("6. Xoa du lieu khach hang\n");
                    printf("7. Quay lai\n");
                    printf("Nhap lua chon: ");
                    saferScanf("%d", &luaChonCon);
            
                    switch (luaChonCon) {
                        case 1: {
                            docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);
                            xemDanhSach((void (*)(char*, int, void*))docFileKhachHang, (int (*)(char*))kiemTraSoKhachHang, (void (*)(void*, int))xemDanhSachKhachHang,
                                        fileQuanLiChung, soKhachHang, sizeof(KhachHang), danhSachKhachHang);
                            break;
                        }
                        case 2: {
                            docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);
                            int soFile = kiemTraSoKhachHang(fileQuanLiChung);
                            timKiemDuLieu((void (*)(void*, int))timKiemKhachHang, (void (*)(char[], int, void*))docFileKhachHang, danhSachKhachHang,
                                            soKhachHang, soFile, fileQuanLiChung, sizeof(KhachHang));
                            break;
                        }
                        case 3: {
                            docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);
                            int soKhachFile = kiemTraSoKhachHang(fileQuanLiChung);
                            KhachHang khachMoi;
                            themPhanTu((void (*)(void*, void*, int))nhapThongTinKhach, (void (*)(char[], void*))themKhachHangVaoFile, (void (*)(void*, int*, void*))themKhachHang,
                                        danhSachKhachHang, &soKhachHang, placeHolderArr, &placeHolderVal,
                                        &soKhachFile, MAX_KHACH_HANG, &khachMoi, fileQuanLiChung);
                            break;
                        }
                        case 4: {
                            docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung);
                            int soKhachHangFile = kiemTraSoKhachHang(fileQuanLiChung);
                            KhachHang khachHang;
                            xoaPhanTu((void (*)(void*, int*, void*))xoaKhachHang, (void (*)(char*, void*))xoaKhachKhoiFile,
                                        (void (*)(void*, void*, int))nhapTenSDTKhach, &soKhachHang, danhSachKhachHang, &placeHolderVal,
                                        &placeHolderArr, &soKhachHangFile, &khachHang, fileQuanLiChung);
                            break;
                        }
                        case 5: {
                            docFileQuanLi(LUA_CHON_KHACH_HANG, fileQuanLiChung); 
                            int soKhachFile = kiemTraSoKhachHang(fileQuanLiChung);
                            capNhatDuLieu((void (*)(void*, int*, char[], int*))capNhatKhachTuFile, (void (*)(void*, int*, char[], int*))capNhatKhachTuMang,
                                            danhSachKhachHang, &soKhachHang, &soKhachFile, fileQuanLiChung);
                            break;
                        }
                        case 6: {
                            reset(&soKhachHang, LUA_CHON_KHACH_HANG);
                            break;
                        }
                        case 7:
                            break;
                        default:
                            printf("Lua chon khong hop le. Vui long chon lai.\n");
                    }
                } while (luaChonCon != 7);
                break;
            case 5:
                do {
                    printf("\n--- MENU QUAN LY KHO NGUYEN LIEU ---\n");
                    printf("1. Xem kho nguyen lieu\n");
                    printf("2. Tim kiem nguyen lieu\n");
                    printf("3. Them nguyen lieu\n");
                    printf("4. Xoa nguyen lieu\n");
                    printf("5. Cap nhat file nguyen lieu\n");
                    printf("6. Xoa du lieu kho\n");
                    printf("7. Quay lai\n");
                    printf("Nhap lua chon: ");

                    saferScanf("%d", &luaChonCon); 
            
                    switch (luaChonCon) {
                        case 1: {
                            docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                            xemDanhSach((void (*)(char*, int, void*))docFileKho, (int (*)(char*))kiemTraSoNguyenLieu, (void (*)(void*, int))hienThiKho,
                                        fileQuanLiChung, soLuongNguyenLieuSuDung, sizeof(NguyenLieu), khoNguyenLieuSuDung);
                            break;
                        }
                        case 2: {
                            docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                            int soFile = kiemTraSoNguyenLieu(fileQuanLiChung);
                            timKiemDuLieu((void (*)(void*, int))timKiemNguyenLieu, (void (*)(char[], int, void*))docFileKho, khoNguyenLieuSuDung,
                                            soLuongNguyenLieuSuDung, soFile, fileQuanLiChung, sizeof(NguyenLieu));
                            break;
                        }
                        case 3: {
                            docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                            int soNguyenLieuFile = kiemTraSoNguyenLieu(fileQuanLiChung);
                            NguyenLieu nguyenLieuMoi;
                            themPhanTu((void (*)(void*, void*, int))nhapThongTinNguyenLieu, (void (*)(char[], void*))themNguyenLieuVaoFile, (void (*)(void*, int*, void*))themNguyenLieu,
                                        khoNguyenLieuSuDung, &soLuongNguyenLieuSuDung, placeHolderArr, &placeHolderVal,
                                        &soNguyenLieuFile, MAX_NGUYEN_LIEU, &nguyenLieuMoi, fileQuanLiChung);
                            break;
                        }    
                        case 4: {
                            docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                            int soNguyenLieuFile = kiemTraSoNguyenLieu(fileQuanLiChung);
                            NguyenLieu nguyenLieuXoa;
                            xoaPhanTu((void (*)(void*, int*, void*))xoaNguyenLieu, (void (*)(char*, void*))xoaNguyenLieuKhoiFile,
                                        (void (*)(void*, void*, int))nhapTenNguyenLieu,
                                        &soLuongNguyenLieuSuDung, khoNguyenLieuSuDung, &placeHolderVal, placeHolderArr, &soNguyenLieuFile, 
                                        &nguyenLieuXoa, fileQuanLiChung);
                            break;
                        }
                        case 5: {
                            docFileQuanLi(LUA_CHON_KHO, fileQuanLiChung);
                            int soNguyenLieuFile = kiemTraSoNguyenLieu(fileQuanLiChung);
                            capNhatDuLieu((void (*)(void*, int*, char[], int*))capNhatKhoTuFile, (void (*)(void*, int*, char[], int*))capNhatKhoTuMang,
                                            khoNguyenLieuSuDung, &soLuongNguyenLieuSuDung, &soNguyenLieuFile, fileQuanLiChung);
                            break;
                        }   
                        case 6: {
                            reset(&soLuongNguyenLieuSuDung, LUA_CHON_KHO);
                            break;
                        }
                        case 7:
                            break;
                        default:
                            printf("Lua chon khong hop le, vui long chon lai\n");
                    }
                } while (luaChonCon != 7);
                break; 
            case 6: // Thong ke du lieu trong file. Profit se duoc tinh su dung ca tien thua
                do {
                    printf("\n--- Thong ke ---\n");
                    printf("1. Thong ke trong nam\n");
                    printf("2. Thong ke trong thang\n");
                    printf("3. Quay lai\n");
                    printf("Nhap lua chon: ");
                    saferScanf("%d", &luaChonCon);

                    switch (luaChonCon){
                        case 1: {
                            int namThongKe;
                            printf("Nhap nam thong ke: ");
                            saferScanf("%d", &namThongKe);

                            if(namThongKe < 0) {
                                printf("Nam khong the am\n");
                                break;
                            }

                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            int soHoaDonFile = kiemTraSoHoaDon(fileQuanLiChung);
                            HoaDon* danhSachHoaDonFile = (HoaDon*) malloc(sizeof(HoaDon) * soHoaDonFile);
                            
                            // Kiem tra xem bo nho co duoc cap phat chua
                            if(!danhSachHoaDonFile) {
                                printf("Khong the khoi tao mang dong de thong ke hoa don theo nam");
                                break;
                            }

                            docFileHoaDon(fileQuanLiChung, soHoaDonFile, danhSachHoaDonFile);

                            float tongTienQ1 = 0, chiPhiQ1 = 0;
                            float tongTienQ2 = 0, chiPhiQ2 = 0;
                            float tongTienQ3 = 0, chiPhiQ3 = 0;
                            float tongTienQ4 = 0, chiPhiQ4 = 0;
                            int soDonQ1 = 0, soDonQ2 = 0, soDonQ3 = 0, soDonQ4 = 0;
                            int tonTaiNam = 0; // Flag danh dau xem input nam co nam trong file khong

                            for(int i = 0; i < soHoaDonFile; i++) {
                                if(danhSachHoaDonFile[i].ngayNhapDon.nam == namThongKe) {
                                    tonTaiNam = 1;
                                    if(danhSachHoaDonFile[i].ngayNhapDon.thang >= 1 && danhSachHoaDonFile[i].ngayNhapDon.thang <= 3) {
                                        tongTienQ1 += danhSachHoaDonFile[i].tongTien - danhSachHoaDonFile[i].tienThua;
                                        chiPhiQ1 += danhSachHoaDonFile[i].tienNguyenLieu;
                                        soDonQ1++;
                                    } else if(danhSachHoaDonFile[i].ngayNhapDon.thang >= 4 && danhSachHoaDonFile[i].ngayNhapDon.thang <= 6) {
                                        tongTienQ2 += danhSachHoaDonFile[i].tongTien - danhSachHoaDonFile[i].tienThua;
                                        chiPhiQ2 += danhSachHoaDonFile[i].tienNguyenLieu;
                                        soDonQ2++;
                                    } else if(danhSachHoaDonFile[i].ngayNhapDon.thang >= 7 && danhSachHoaDonFile[i].ngayNhapDon.thang <= 9) {
                                        tongTienQ3 += danhSachHoaDonFile[i].tongTien - danhSachHoaDonFile[i].tienThua;
                                        chiPhiQ3 += danhSachHoaDonFile[i].tienNguyenLieu;
                                        soDonQ3++;
                                    } else if(danhSachHoaDonFile[i].ngayNhapDon.thang >= 10 && danhSachHoaDonFile[i].ngayNhapDon.thang <= 12) {
                                        tongTienQ4 += danhSachHoaDonFile[i].tongTien - danhSachHoaDonFile[i].tienThua;
                                        chiPhiQ4 += danhSachHoaDonFile[i].tienNguyenLieu;
                                        soDonQ4++;
                                    }
                                }
                            }

                            if(tonTaiNam == 0) {
                                printf("Khong ton tai nam %d trong he thong\n", namThongKe);
                                break;
                            }

                            printf("\n--- Nam %d ---\n", namThongKe);
                            printf("Quy 1 co %d don hang, tong loi nhuan: %.2f\n", soDonQ1, tongTienQ1 - chiPhiQ1);
                            printf("Quy 2 co %d don hang, tong loi nhuan: %.2f\n", soDonQ2, tongTienQ2 - chiPhiQ2);
                            printf("Quy 3 co %d don hang, tong loi nhuan: %.2f\n", soDonQ3, tongTienQ3 - chiPhiQ3);
                            printf("Quy 4 co %d don hang, tong loi nhuan: %.2f\n", soDonQ4, tongTienQ4 - chiPhiQ4);
                            printf("Nam %d co %d don hang, tong thu nhap: %.2f\n", namThongKe, soDonQ1 + soDonQ2 + soDonQ3 + soDonQ4,
                                        tongTienQ1 - chiPhiQ1 + tongTienQ2 - chiPhiQ2 + tongTienQ3 - chiPhiQ3 + tongTienQ4 - chiPhiQ4);

                            free(danhSachHoaDonFile);

                            break;
                        }
                        case 2: {
                            int namThongKe, thangThongKe;
                            printf("Nhap nam thong ke: ");
                            saferScanf("%d", &namThongKe);
                            printf("Nhap thang thong ke: ");
                            saferScanf("%d", &thangThongKe);

                            if(namThongKe < 0 || thangThongKe < 0) {
                                printf("Nam va thang khong the am\n");
                                break;
                            }

                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            int soHoaDonFile = kiemTraSoHoaDon(fileQuanLiChung);
                            HoaDon* danhSachHoaDonFile = (HoaDon*) malloc(sizeof(HoaDon) * soHoaDonFile);
                            
                            // Kiem tra xem bo nho co duoc cap phat chua
                            if(!danhSachHoaDonFile) {
                                printf("Khong the khoi tao mang dong de thong ke hoa don theo thang");
                                break;
                            }

                            docFileHoaDon(fileQuanLiChung, soHoaDonFile, danhSachHoaDonFile);

                            float tongTienThongKe = 0, tienNguyenLieuThongKe = 0;
                            int soHoaDonThongKe = 0;
                            int tonTaiThoiDiem = 0; // Kiem tra xem file co luu hoa don cua thang, nam do khong

                            for(int i = 0; i < soHoaDonFile; i++) {
                                if(danhSachHoaDonFile[i].ngayNhapDon.nam == namThongKe && danhSachHoaDonFile[i].ngayNhapDon.thang == thangThongKe) {
                                    tonTaiThoiDiem = 1;
                                    tongTienThongKe += danhSachHoaDonFile[i].tongTien - danhSachHoaDonFile[i].tienThua;
                                    tienNguyenLieuThongKe += danhSachHoaDonFile[i].tienNguyenLieu;
                                    soHoaDonThongKe++;
                                }
                            }

                            if(tonTaiThoiDiem == 0) {
                                printf("Khong ton tai hoa don thang %d nam %d trong file\n", thangThongKe, namThongKe);
                                break;
                            }
                            printf("\n--- Thong ke thang %d nam %d ---\n", thangThongKe, namThongKe);
                            printf("Tong thu nhap: %.2f\n", tongTienThongKe - tienNguyenLieuThongKe);
                            printf("So hoa don: %d\n", soHoaDonThongKe);

                            free(danhSachHoaDonFile);

                            break;
                        }
                        case 3:
                            break;
                        default:
                            printf("Lua chon khong hop le, vui long chon lai\n");
                    }
                } while(luaChonCon != 3);
                break;
            case 7:
                do {
                    printf("\n--- FILE ---\n");
                    printf("1. File khach hang\n");
                    printf("2. File hoa don\n");
                    printf("3. File kho\n");
                    printf("4. File menu\n");
                    printf("5. Reset file quan li\n");
                    printf("6. Quay lai\n");
                    printf("Nhap lua chon: ");
                    saferScanf("%d", &luaChonCon);

                    if(luaChonCon == 5) {
                        FILE* quanLiFptr = fopen(MANAGING_FILE, "w");
                        if(quanLiFptr) {
                            for(int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
                                fprintf(quanLiFptr, PLACEHOLDER_QUAN_LY);
                            }
                            fclose(quanLiFptr);
                            printf("Reset file thanh cong\n");
                        } else {
                            perror("Khong the reset file quan ly");
                        }
                    } else if(luaChonCon == 1 || luaChonCon == 2 || luaChonCon == 3 || luaChonCon == 4) {
                        do {
                            printf("\n--- Hanh dong ---\n");
                            printf("1. Xoa file\n");
                            printf("2. Tao file\n");
                            printf("3. Di chuyen file\n");
                            printf("4. Xem duong dan hien tai\n");
                            printf("5. Chon file\n");
                            printf("6. Quay lai\n");
                            printf("Nhap lua chon: ");
                            saferScanf("%d", &luaChonCon2);
                    
                            switch (luaChonCon2) {
                                case 1: { // Use "{}" for better scoping
                                    // Xoa file
                                    docFileQuanLi(luaChonCon, fileQuanLiChung);
                                    int ketQuaXoa = remove(fileQuanLiChung);
                                    if(ketQuaXoa != 0) {
                                        perror("Xoa file that bai");
                                        break;
                                    }
                                    printf("File da duoc xoa!\n");

                                    // Cap nhat file quan li
                                    capNhatFileQuanLi(luaChonCon, "");
                                    break;
                                }
                                case 2: {
                                    // Tao file moi
                                    char duongDanMoi[MAX_FILE_PATH_LENGTH];
                                    printf("Nhap duong dan moi: ");
                                    fgets(duongDanMoi, MAX_FILE_PATH_LENGTH - 1, stdin);
                                    duongDanMoi[strcspn(duongDanMoi, "\n")] = '\0';
                                    duongDanMoi[MAX_FILE_PATH_LENGTH - 1] = '\0';

                                    FILE* fptr = fopen(duongDanMoi, "w");
                                    if(!fptr) {
                                        printf("Loi khi tao file!\n");
                                        break;
                                    }
                                    // Khoi tao header
                                    switch (luaChonCon) {
                                        case LUA_CHON_KHACH_HANG:
                                            fprintf(fptr, KHACH_HANG_HEADER);
                                            break;
                                        case LUA_CHON_HOA_DON:
                                            fprintf(fptr, HOA_DON_HEADER);
                                            break;
                                        case LUA_CHON_KHO:
                                            fprintf(fptr, KHO_HEADER);
                                            break;
                                        case LUA_CHON_MENU:
                                            fprintf(fptr, MENU_HEADER);
                                        default:
                                            break;
                                    }

                                    printf("File duoc tao thanh cong!\n");
                                    fclose(fptr);

                                    // Cap nhat file quan li
                                    capNhatFileQuanLi(luaChonCon, duongDanMoi);
                                    break;
                                }
                                case 3: {
                                    char duongDanMoi[MAX_FILE_PATH_LENGTH];
                                    printf("Nhap dia chi moi: ");
                                    fgets(duongDanMoi, MAX_FILE_PATH_LENGTH - 1, stdin);
                                    duongDanMoi[strcspn(duongDanMoi, "\n")] = '\0';
                                    duongDanMoi[MAX_FILE_PATH_LENGTH - 1] = '\0';

                                    docFileQuanLi(luaChonCon, fileQuanLiChung);

                                    if(strncmp(duongDanMoi, fileQuanLiChung, MAX_FILE_PATH_LENGTH) == 0) {
                                        printf("Duong dan moi khong the giong duong dan cu!\n");
                                        break;
                                    }
                                    
                                    // Tao file o dia chi moi
                                    FILE* fptrDich = fopen(duongDanMoi, "w");
                                    if(!fptrDich) {
                                        perror("Loi khi tao file o dia chi moi");
                                        break;
                                    }

                                    // Sao chep du lieu sang file moi
                                    docFileQuanLi(luaChonCon, fileQuanLiChung);
                                    FILE* fptrNguon = fopen(fileQuanLiChung, "r");
                                    if(!fptrNguon) {
                                        perror("Khong the mo file cu de chuyen du lieu");
                                        break;
                                    }
                                    char dongDuLieu[MAX_DONG_DU_LIEU];
                                    while(fgets(dongDuLieu, MAX_DONG_DU_LIEU - 1, fptrNguon)) {
                                        dongDuLieu[MAX_DONG_DU_LIEU - 1] = '\0';
                                        fprintf(fptrDich, "%s", dongDuLieu);
                                    }
                                    fclose(fptrNguon);
                                    fclose(fptrDich);

                                    // Xoa file du lieu cu
                                    if(remove(fileQuanLiChung) != 0) {
                                        perror("File du lieu nguon chua duoc xoa");
                                    }

                                    // Cap nhat duong dan moi cuar file quan li
                                    capNhatFileQuanLi(luaChonCon, duongDanMoi);
                                    printf("File da duoc cap nhat thanh cong\n");
                                    break;
                                }
                                case 4: {
                                    docFileQuanLi(luaChonCon, fileQuanLiChung);
                                    printf("Duong dan hien tai: %s\n", fileQuanLiChung);
                                    break;
                                }
                                case 5: {
                                    // Chuong trinh chi co the lam viec voi du lieu cua mot file cho moi loai doi tuong tai mot thoi diem
                                    // Lay duong dan cua mot file du lieu
                                    printf("CANH BAO: HAY DAM BAO FILE DUOC HUONG TOI LA FILE DU LIEU DUNG LOAI VA DUNG CU PHAP!!!!\n");
                                    char duongDanMoi[MAX_FILE_PATH_LENGTH];
                                    printf("Nhap dia chi moi: ");
                                    fgets(duongDanMoi, MAX_FILE_PATH_LENGTH - 1, stdin);
                                    duongDanMoi[strcspn(duongDanMoi, "\n")] = '\0';
                                    duongDanMoi[MAX_FILE_PATH_LENGTH - 1] = '\0';

                                    // Kiem tra xem dia chi co ton tai khong
                                    FILE* fptr = fopen(duongDanMoi, "r");
                                    if(!fptr) {
                                        perror("Khong the su dung file");
                                        break;
                                    }

                                    // Cap nhat file quan li
                                    capNhatFileQuanLi(luaChonCon, duongDanMoi);
                                    break;
                                }
                                case 6:
                                    break;
                                default:
                                    printf("Lua chon khong hop le. Vui long chon lai.\n");
                            }             
                        } while (luaChonCon2 != 6);
                    } else if(luaChonCon != 6) {
                        printf("Lua chon khong hop le. Vui long chon lai!\n");
                    }
                } while(luaChonCon != 6);
                break;
            case 8:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (luaChon != 8);

    if(canFreeKhoNguyenLieu == 1) {
        free(khoNguyenLieuSuDung);
    }

    if(canFreeMenu == 1) {
        free(menuSuDung);
    }
    
    return 0;
}

// -------------------------------------------------- Cac ham xu ly khach hang ----------------------------------------------------- //

void xemDanhSachKhachHang(KhachHang danhSachKhachHang[], int soKhachHang) {
    if(soKhachHang == 0) {
        printf("Chua co khach hang\n");
        return;
    }
    for (int i = 0; i < soKhachHang; i++) {
        printf("%d. %s - %s - %.2f\n", i + 1, danhSachKhachHang[i].tenKhachHang, danhSachKhachHang[i].soDienThoai, danhSachKhachHang[i].diemTichLuy);
    }
}

void timKiemKhachHang(KhachHang danhSachKhachHang[], int soKhachHang) {
    if(soKhachHang == 0) {
        printf("Chua co khach hang\n");
        return;
    }

    int luaChon;
    char keyword[50];

    printf("\nChon phuong thuc tim kiem:\n");
    printf("1. Tim theo ten\n");
    printf("2. Tim theo so dien thoai\n");
    printf("Nhap lua chon: ");
    saferScanf("%d", &luaChon);

    if(luaChon != 1 && luaChon != 2) {
        printf("Lua chon khong hop le\n");
    } else if (luaChon == 1) {
        printf("Nhap ten khach hang: ");
        fgets(keyword, sizeof(keyword) - 1, stdin);
        keyword[strcspn(keyword, "\n")] = '\0'; // Loại bỏ ký tự newline
        keyword[sizeof(keyword) - 1] = '\0';

        printf("\nDanh sach khach hang tim duoc theo ten '%s':\n", keyword);
        for (int i = 0; i < soKhachHang; i++) {
            if (strstr(danhSachKhachHang[i].tenKhachHang, keyword) != NULL) {
                printf("%d. %s - %s - %.2f\n", i + 1, danhSachKhachHang[i].tenKhachHang, danhSachKhachHang[i].soDienThoai, danhSachKhachHang[i].diemTichLuy);
            }
        }
    } else if (luaChon == 2) {
        printf("Nhap so dien thoai khach hang: ");
        fgets(keyword, sizeof(keyword) - 1, stdin);
        keyword[strcspn(keyword, "\n")] = '\0'; // Loại bỏ ký tự newline
        keyword[sizeof(keyword) - 1] = '\0';

        printf("\nDanh sach khach hang tim duoc theo so dien thoai '%s':\n", keyword);
        for (int i = 0; i < soKhachHang; i++) {
            if (strstr(danhSachKhachHang[i].soDienThoai, keyword) != NULL) {
                printf("%d. %s - %s - %.2f\n", i + 1, danhSachKhachHang[i].tenKhachHang, danhSachKhachHang[i].soDienThoai, danhSachKhachHang[i].diemTichLuy);
            }
        }
    }
}

void themKhachHang(KhachHang danhSachKhachHang[], int *soKhachHang, KhachHang* khachHangMoi) {
    if(*soKhachHang >= MAX_KHACH_HANG) {
        printf("Mang da day\n");
        return;
    }

    for(int i = 0; i < *soKhachHang; i++) {
        if(strcmp(danhSachKhachHang[i].tenKhachHang, khachHangMoi->tenKhachHang) == 0 &&
            strcmp(danhSachKhachHang[i].soDienThoai, khachHangMoi->soDienThoai) == 0) {
                printf("Khach hang da co trong mang\n");
                return;
        }
    }

    saoChepKhachHang(&danhSachKhachHang[*soKhachHang], khachHangMoi);
    (*soKhachHang)++;
    printf("Khach hang da duoc them\n");
}

void xoaKhachHang(KhachHang danhSachKhach[], int* soLuong, KhachHang* khachXoa) {
    if(*soLuong == 0) {
        printf("Chua co khach hang\n");
        return;
    }
    
    for(int i = 0; i < *soLuong; i++) {
        if(strcmp(danhSachKhach[i].tenKhachHang, khachXoa->tenKhachHang) == 0 &&
            strcmp(danhSachKhach[i].soDienThoai, khachXoa->soDienThoai) == 0) {
            // Xoa khach hang bang cach di chuyen cac khach hang con lai
            for(int j = i; j < *soLuong - 1; j++) {
                saoChepKhachHang(&danhSachKhach[j], &danhSachKhach[j + 1]);
            }
            printf("Khach hang da duoc xoa\n");
            (*soLuong)--;
            return;
        }
    }
    printf("Khong tim thay khach hang\n");
}

void nhapThongTinKhach(KhachHang* khachHang, int placeHolderArr[], int placeHolderVal) {
    chuanHoaKhachHang(khachHang, 1);

    printf("Nhap ten khach hang: ");
    fgets(khachHang->tenKhachHang, DO_DAI_TEN_KHACH - 1, stdin);
    printf("Nhap so dien thoai khach hang: ");
    fgets(khachHang->soDienThoai, DO_DAI_SO_DIEN_THOAI - 1, stdin);
    printf("Nhap so diem tich luy khach hang: ");
    saferScanf("%f", &khachHang->diemTichLuy);

    // Khu newline cho cac input
    khachHang->tenKhachHang[strcspn(khachHang->tenKhachHang, "\n")] = '\0';
    khachHang->soDienThoai[strcspn(khachHang->soDienThoai, "\n")] = '\0';

    // Khu null cho cac input
    khachHang->tenKhachHang[DO_DAI_TEN_KHACH - 1] = '\0';
    khachHang->soDienThoai[DO_DAI_SO_DIEN_THOAI - 1] = '\0';
}

void nhapTenSDTKhach(KhachHang* khachHang, int placeholderArr[], int placeholderVal) {
    chuanHoaKhachHang(khachHang, 1);

    printf("Nhap ten khach hang: ");
    fgets(khachHang->tenKhachHang, DO_DAI_TEN_KHACH - 1, stdin);
    printf("Nhap so dien thoai khach hang: ");
    fgets(khachHang->soDienThoai, DO_DAI_SO_DIEN_THOAI - 1, stdin);

    // Khu newline cho cac input
    khachHang->tenKhachHang[strcspn(khachHang->tenKhachHang, "\n")] = '\0';
    khachHang->soDienThoai[strcspn(khachHang->soDienThoai, "\n")] = '\0';

    // Khu null cho cac input
    khachHang->tenKhachHang[DO_DAI_TEN_KHACH - 1] = '\0';
    khachHang->soDienThoai[DO_DAI_SO_DIEN_THOAI - 1] = '\0';
}

void layDiemTichLuy(KhachHang danhSachKhachHang[], int soKhachHang, KhachHang* khach) {
    for(int i = 0; i < soKhachHang; i++) {
        if(strcmp(khach->tenKhachHang, danhSachKhachHang[i].tenKhachHang) == 0 && strcmp(khach->soDienThoai, danhSachKhachHang[i].soDienThoai) == 0) {
            khach->diemTichLuy = danhSachKhachHang[i].diemTichLuy;
            return; 
        } 
    }
}

void capNhatKhachTuFile(KhachHang danhSach[], int* soKhach, char duongDan[], int* soKhachFile) {
    if(*soKhachFile == 0) {
        printf("Khong co du lieu trong file\n");
        return;
    }

    KhachHang* danhSachKhachHangFile = (KhachHang*) malloc(sizeof(KhachHang) * (*soKhachFile));
    if(!danhSachKhachHangFile) {
        printf("Khong the tao mang dong cho khach hang\n");
        return;
    }
    docFileKhachHang(duongDan, *soKhachFile, danhSachKhachHangFile);

    int coMat = 0;
    for (int i = 0; i < *soKhachFile; i++) {
        coMat = 0;
        if (*soKhach >= MAX_KHACH_HANG) {
            printf("Mang da day\n");
            break;
        }

        for (int j = 0; j < *soKhach; j++) {
            if (strcmp(danhSach[j].tenKhachHang, danhSachKhachHangFile[i].tenKhachHang) == 0 &&
                strcmp(danhSach[j].soDienThoai, danhSachKhachHangFile[i].soDienThoai) == 0) {
                saoChepKhachHang(&danhSach[j], &danhSachKhachHangFile[i]);
                coMat = 1;
                break;
            }
        }

        if (coMat == 0) {
            saoChepKhachHang(&danhSach[*soKhach], &danhSachKhachHangFile[i]);
            (*soKhach)++;
        }
    }

    free(danhSachKhachHangFile);
    printf("Cap nhat thanh cong\n");
}

void capNhatKhachTuMang(KhachHang danhSach[], int* soKhach, char duongDan[], int* soKhachFile) { // CHANGE
    // soKhach la so khach trong mang
    if (*soKhach == 0) {
        printf("Khong co du lieu trong mang\n");
        return;
    }

    KhachHang* danhSachKhachFile = (KhachHang*) malloc(sizeof(KhachHang) * (*soKhachFile));
    if (!danhSachKhachFile) {
        printf("Khong the khoi tao mang dong cho danh sach khach hang\n");
        return;
    }
    docFileKhachHang(duongDan, *soKhachFile, danhSachKhachFile);

    KhachHang* danhSachMoi = (KhachHang*) malloc(sizeof(KhachHang) * (*soKhachFile + (*soKhach)));
    if (!danhSachMoi) {
        printf("Khong the tao mang dong cho danh sach moi\n");
        free(danhSachKhachFile);
        return;
    }

    for (int i = 0; i < *soKhachFile; i++) {
        saoChepKhachHang(&danhSachMoi[i], &danhSachKhachFile[i]);
    }

    int coMat = 0;
    for (int i = 0; i < *soKhach; i++) {
        coMat = 0;
        for (int j = 0; j < *soKhachFile; j++) {
            if (strcmp(danhSachKhachFile[j].tenKhachHang, danhSach[i].tenKhachHang) == 0 &&
                strcmp(danhSachKhachFile[j].soDienThoai, danhSach[i].soDienThoai) == 0) {
                saoChepKhachHang(&danhSachMoi[j], &danhSach[i]);
                coMat = 1;
                break;
            }
        }

        if (coMat == 0) {
            saoChepKhachHang(&danhSachMoi[*soKhachFile], &danhSach[i]);
            (*soKhachFile)++;
        }
    }

    // Reset the file and write the updated list of customers
    resetFile(LUA_CHON_KHACH_HANG);
    themNhieuKhachVaoFile(danhSachMoi, *soKhachFile, duongDan);

    // Free the allocated memory
    free(danhSachKhachFile);
    free(danhSachMoi);
}

// -------------------------------------------------- Cac ham xu ly menu -----------------------------------------------------------//

void hienThiMenu(MonAn menu[], int soMon) {
    printf("\nDanh sach mon an:\n");
    for (int i = 0; i < soMon; i++) {
        printf("%d. %s - Gia: %.2f\n", i + 1, menu[i].tenMon, menu[i].gia);
    }
}

void nhapThongTinMonAn(MonAn* monAn, NguyenLieu kho[], int soNguyenLieuKho) {
    // Su dung de khai bao thong tin cho mot mon an moi
    // Su dung trong themMon va suaMon
    chuanHoaMonAn(monAn, 1);
    printf("\nNhap ten mon: ");
    fgets(monAn->tenMon, sizeof(monAn->tenMon) - 1, stdin);
    monAn->tenMon[strcspn(monAn->tenMon, "\n")] = '\0'; // Loại bỏ ký tự newline
    monAn->tenMon[sizeof(monAn->tenMon) - 1] = '\0';
    printf("Nhap gia mon: ");
    saferScanf("%f", &monAn->gia);

    do {
        printf("Luu y: so nguyen lieu mot mon phai duong va khong the qua %d\n", soNguyenLieuKho);
        printf("Nhap so nguyen lieu mon: ");
        saferScanf("%d", &monAn->soNguyenLieu);
    } while(monAn->soNguyenLieu <= 0 || monAn->soNguyenLieu > soNguyenLieuKho);

    int i = 0;
    while(i < monAn->soNguyenLieu) {        //MARK: THEM_MON
        hienThiKho(kho, soNguyenLieuKho);
        printf("Nhap ten nguyen lieu: ");
        fgets(monAn->nguyenLieu[i].tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1, stdin);
        monAn->nguyenLieu[i].tenNguyenLieu[strcspn(monAn->nguyenLieu[i].tenNguyenLieu, "\n")] = '\0';   //MARK: STR_PRO
        monAn->nguyenLieu[i].tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';

        int timThayTen = 0;
        for(int j = 0; j < soNguyenLieuKho; j++) {
            if(strcmp(monAn->nguyenLieu[i].tenNguyenLieu, kho[j].tenNguyenLieu) == 0) {
                do {
                    printf("So luong phai duong va khong qua %.2f %s\n", kho[j].soLuong, kho[j].donVi);
                    printf("Nhap so luong cho nguyen lieu nay: ");
                    saferScanf("%f", &monAn->nguyenLieu[i].soLuong);
                } while(monAn->nguyenLieu[i].soLuong <= 0 && monAn->nguyenLieu[i].soLuong > kho[j].soLuong);

                monAn->nguyenLieu[i].gia = kho[j].gia;
                strncpy(monAn->nguyenLieu[i].donVi, kho[j].donVi, MAX_DO_DAI_CHUOI_DON_VI - 1);
                monAn->nguyenLieu[i].donVi[MAX_DO_DAI_CHUOI_DON_VI - 1] = '\0';         //MARK: STR_PRO

                i++;
                timThayTen = 1;
                break;
            }
        }
        if(timThayTen == 0) {
            printf("Khong ton tai nguyen lieu\n");
        }
    }
}

void nhapTenMonAn(MonAn* monAn, NguyenLieu kho[], int soNguyenLieuKho) {
    chuanHoaMonAn(monAn, 1);
    printf("\nNhap ten mon: ");
    fgets(monAn->tenMon, sizeof(monAn->tenMon) - 1, stdin);
    monAn->tenMon[strcspn(monAn->tenMon, "\n")] = '\0'; // Loại bỏ ký tự newline
    monAn->tenMon[sizeof(monAn->tenMon) - 1] = '\0';
}

void xoaMonAn(MonAn menu[], int* soMonAn, MonAn* monXoa) {
    if(*soMonAn == 0) {
        return;
    }

    for(int i = 0; i < *soMonAn; i++) {
        if(strcmp(menu[i].tenMon, monXoa->tenMon) == 0) {       //MARK: LAP_MANG
            for(int j = i; j < (*soMonAn) - 1; j++) {
                saoChepMonAn(&menu[j], &menu[j + 1]);
            }
            printf("Mon an da duoc xoa\n");
            (*soMonAn)--;
            return;
        }
    }
    printf("Khong tim thay mon an\n");
}

void themMonAnVaoMang(MonAn menu[], int* soMon, MonAn* monThem) {
    if(*soMon >= MAX_MON) {
        printf("Mang da day\n");
        return;
    }

    for(int i = 0; i < *soMon; i++) {
        if(strcmp(menu[i].tenMon, monThem->tenMon) == 0) {
            printf("Mon an da co trong mang\n");
            return;
        }
    }

    saoChepMonAn(&menu[*soMon], monThem);
    (*soMon)++;
    printf("Mon an da duoc them\n");
}

void capNhatMonAnTuFile(MonAn menu[], int* soMonMang, char duongDan[], int* soMonFile) {
    if(*soMonFile == 0) {
        printf("Khong co du lieu trong file\n");
        return;
    }

    MonAn* menuFile = (MonAn*) malloc(sizeof(MonAn) * (*soMonFile));
    if(!menuFile) {
        printf("Khong the tao mang dong cho menu\n");
        return;
    }
    docFileMenu(duongDan, *soMonFile, menuFile);

    int coMat = 0;
    for (int i = 0; i < *soMonFile; i++) {
        coMat = 0;
        if (*soMonMang >= MAX_MON) {
            printf("Mang da day\n");
            break;
        }

        for (int j = 0; j < *soMonMang; j++) {
            if (strcmp(menuFile[i].tenMon, menu[j].tenMon) == 0) {
                saoChepMonAn(&menu[j], &menuFile[i]); 
                coMat = 1;
                break;
            }
        }

        if (coMat == 0) {
            saoChepMonAn(&menu[*soMonMang], &menuFile[i]);
            (*soMonMang)++;
        }
    }

    free(menuFile);
    printf("Cap nhat thanh cong\n");
}

void capNhatMonAnTuMang(MonAn menu[], int* soMonMang, char duongDan[], int* soMonFile) { // CHANGE
    if (*soMonMang == 0) {
        printf("Khong co du lieu trong mang\n");
        return;
    }

    MonAn* menuFile = (MonAn*)malloc(sizeof(MonAn) * (*soMonFile));
    if (!menuFile) {
        printf("Khong the tao mang dong cho menu\n");
        return;
    }
    docFileMenu(duongDan, *soMonFile, menuFile);

    MonAn menuMoi[MAX_MON];
    int soLuongMoi = 0;

    for (int i = 0; i < *soMonFile && soLuongMoi < MAX_MON; i++) {
        saoChepMonAn(&menuMoi[soLuongMoi++], &menuFile[i]);
    }
    free(menuFile);

    for (int i = 0; i < *soMonMang; i++) {
        int found = 0;
        if(soLuongMoi >= MAX_MON) {
            printf("File day\n");
            break;
        }

        for (int j = 0; j < soLuongMoi; j++) {
            if (strcmp(menuMoi[j].tenMon, menu[i].tenMon) == 0) {
                saoChepMonAn(&menuMoi[j], &menu[i]);
                found = 1;
                break;
            }
        }

        if (found == 0) {
            saoChepMonAn(&menuMoi[soLuongMoi++], &menu[i]);
        }
    }
    resetFile(LUA_CHON_MENU);
    themNhieuMonAnVaoFile(menuMoi, soLuongMoi, duongDan);
}

// -------------------------------------------------- Cac ham xu ly hoa don --------------------------------------------------------- //

void xemHoaDon(HoaDon danhSachHoaDon[], int soHoaDon) {
    // Viec hien thi cac mon goi tu hoa don doc tu trong file la mot van de do menu co the thay doi
    printf("\nDanh sach hoa don:\n");
    for (int i = 0; i < soHoaDon; i++) {
        printf("\n");
        printf("Hoa don %d:\n", i + 1);
        printf("Ten khach hang: %s\n", danhSachHoaDon[i].khachHang.tenKhachHang);
        printf("Diem tich luy khach hang: %.2f\n", danhSachHoaDon[i].khachHang.diemTichLuy);
        printf("So dien thoai: %s\n", danhSachHoaDon[i].khachHang.soDienThoai);
        printf("Ngay nhap: %d/%d/%d\n", danhSachHoaDon[i].ngayNhapDon.ngay, danhSachHoaDon[i].ngayNhapDon.thang, danhSachHoaDon[i].ngayNhapDon.nam);
        printf("Danh sach mon an:\n");
        for (int j = 0; j < danhSachHoaDon[i].soMonGoi; j++) {
            printf("%d. %s - %d x %.2f = %.2f\n", j + 1, danhSachHoaDon[i].tenMonGoi[j], danhSachHoaDon[i].soLuongMon[j], danhSachHoaDon[i].giaMonGoi[j], danhSachHoaDon[i].soLuongMon[j] * danhSachHoaDon[i].giaMonGoi[j]);
        }
        printf("Tong tien: %.2f\n", danhSachHoaDon[i].tongTien);
        printf("Tien thua: %.2f\n", danhSachHoaDon[i].tienThua);
    }
}

void timKiemHoaDon(HoaDon danhSachHoaDon[], int soHoaDon) {
    int luaChon;
    float giaTien;
    char keyword[50];
    int monTimKiem;

    printf("\nChon phuong thuc tim kiem hoa don:\n");
    printf("1. Tim theo gia tien\n");
    printf("2. Tim theo ten/sdt khach hang\n");
    printf("3. Tim theo mon an\n");
    printf("Nhap lua chon: ");
    saferScanf("%d", &luaChon);

    if (luaChon == 1) {
        printf("Nhap gia tien hoa don: ");
        saferScanf("%f", &giaTien);
        
        printf("\nDanh sach hoa don tim duoc theo gia tien %.2f:\n", giaTien);
        for (int i = 0; i < soHoaDon; i++) {
            if (danhSachHoaDon[i].tongTien == giaTien) {
                printf("Hoa don %d: Ten khach hang: %s - So dien thoai: %s - Ngay nhap: %d/%d/%d - Tong tien: %.2f\n", 
                        i + 1, danhSachHoaDon[i].khachHang.tenKhachHang, danhSachHoaDon[i].khachHang.soDienThoai, danhSachHoaDon[i].ngayNhapDon.ngay,
                        danhSachHoaDon[i].ngayNhapDon.thang, danhSachHoaDon[i].ngayNhapDon.nam, danhSachHoaDon[i].tongTien);
            }
        }
    } else if (luaChon == 2) {
        printf("Nhap ten hoac so dien thoai khach hang: ");
        fgets(keyword, sizeof(keyword) - 1, stdin);
        keyword[strcspn(keyword, "\n")] = '\0'; // Loại bỏ ký tự newline    //MARK: STR_PRO
        keyword[sizeof(keyword) - 1] = '\0';
        
        printf("\nDanh sach hoa don tim duoc theo ten/sdt khach hang '%s':\n", keyword);
        for (int i = 0; i < soHoaDon; i++) {
            if (strstr(danhSachHoaDon[i].khachHang.tenKhachHang, keyword) != NULL || 
                strstr(danhSachHoaDon[i].khachHang.soDienThoai, keyword) != NULL) {
                printf("Hoa don %d: Ten khach hang: %s - So dien thoai: %s - Ngay nhap: %d/%d/%d - Tong tien: %.2f\n", 
                        i + 1, danhSachHoaDon[i].khachHang.tenKhachHang, danhSachHoaDon[i].khachHang.soDienThoai, danhSachHoaDon[i].ngayNhapDon.ngay,
                        danhSachHoaDon[i].ngayNhapDon.thang, danhSachHoaDon[i].ngayNhapDon.nam, danhSachHoaDon[i].tongTien);
            }
        }
    } else if (luaChon == 3) {
        printf("Nhap mon an can tim: ");
        fgets(keyword, sizeof(keyword), stdin);
        keyword[strcspn(keyword, "\n")] = '\0'; // Loại bỏ ký tự newline    //MARK: STR_PRO
        keyword[sizeof(keyword) - 1] = '\0';

        printf("\nDanh sach hoa don chua mon an '%s':\n", keyword);
        for (int i = 0; i < soHoaDon; i++) {
            for (int j = 0; j < danhSachHoaDon[i].soMonGoi; j++) {
                if (strstr(danhSachHoaDon[i].tenMonGoi[j], keyword) != NULL) {
                    printf("Hoa don %d: Ten khach hang: %s - So dien thoai: %s - Ngay nhap: %d/%d/%d - Tong tien: %.2f\n", 
                        i + 1, danhSachHoaDon[i].khachHang.tenKhachHang, danhSachHoaDon[i].khachHang.soDienThoai, danhSachHoaDon[i].ngayNhapDon.ngay,
                        danhSachHoaDon[i].ngayNhapDon.thang, danhSachHoaDon[i].ngayNhapDon.nam, danhSachHoaDon[i].tongTien);
                    break;  // Nếu tìm thấy món ăn trong hóa đơn, dừng kiểm tra cho hóa đơn đó
                }
            }
        }
    } else {
        printf("Lua chon khong hop le.\n");
    }
}

void thanhToan(MonAn menu[], int soMon, HoaDon danhSachHoaDon[], int *soHoaDon, KhachHang danhSachKhachHang[], int *soKhachHang,
                NguyenLieu kho[], int soNguyenLieuKho, char duongDanFileKhach[]) {
    if(soNguyenLieuKho == 0) {
        printf("Kho trong, khong the order\n");
        return;
    }

    HoaDon hoaDon; 
    chuanHoaHoaDon(&hoaDon, 1);
    printf("\nNhap thong tin khach hang:\n");
    printf("Nhap ten khach hang: ");
    fgets(hoaDon.khachHang.tenKhachHang, sizeof(hoaDon.khachHang.tenKhachHang) - 1, stdin); //MARK: STR_PRO
    hoaDon.khachHang.tenKhachHang[strcspn(hoaDon.khachHang.tenKhachHang, "\n")] = '\0'; // Loại bỏ ký tự newline
    hoaDon.khachHang.tenKhachHang[sizeof(hoaDon.khachHang.tenKhachHang) - 1] = '\0';

    printf("Nhap so dien thoai khach hang: ");
    fgets(hoaDon.khachHang.soDienThoai, sizeof(hoaDon.khachHang.soDienThoai) - 1, stdin);   //MARK: STR_PRO
    hoaDon.khachHang.soDienThoai[strcspn(hoaDon.khachHang.soDienThoai, "\n")] = '\0'; // Loại bỏ ký tự newline
    hoaDon.khachHang.soDienThoai[sizeof(hoaDon.khachHang.soDienThoai) - 1] = '\0';

    // Lay so diem tich luy dua vao ho ten va sdt cua khach hang.
    // Du lieu se duoc tim trong mang khach hang hien tai (thong tin o day se moi hon).
    // Khi mang khach hang hien tai khong co du lieu ve khach hang can tim, tim du lieu trong file khach hang duoc chi dinh.
    // Neu ca mang khach hang va file deu khong co, mac dinh diem tich luy ve 0 (co tu buoc chuan hoa)
    int ketQua;
    if(*soKhachHang == 0) { // Khong co khach hang trong mang
        docFileQuanLi(LUA_CHON_KHACH_HANG, duongDanFileKhach);
        int soKhachFile = kiemTraSoKhachHang(duongDanFileKhach);
        KhachHang* danhSachKhachFile = (KhachHang*) malloc(sizeof(KhachHang) * soKhachFile);
        docFileKhachHang(duongDanFileKhach, soKhachFile, danhSachKhachFile);
        layDiemTichLuy(danhSachKhachFile, soKhachFile, &hoaDon.khachHang);
        free(danhSachKhachFile);
    } else { // Co khach hang trong mang
        layDiemTichLuy(danhSachKhachHang, *soKhachHang, &hoaDon.khachHang);
    }

    printf("Nhap ngay: ");
    saferScanf("%d", &hoaDon.ngayNhapDon.ngay);
    printf("Nhap thang: ");
    saferScanf("%d", &hoaDon.ngayNhapDon.thang);
    printf("Nhap nam: ");
    saferScanf("%d", &hoaDon.ngayNhapDon.nam);

    int chonMon;
    printf("\nChon mon va so luong mon:\n");
    while (1) {
        hienThiMenu(menu, soMon);
        printf("Nhap so mon (0 de ket thuc): ");
        saferScanf("%d", &chonMon);

        if (chonMon == 0) break;
        
        if (chonMon < 1 || chonMon > soMon) {
            printf("Mon khong hop le. Vui long chon lai.\n");
            continue;
        }

        // Kiem tra xem order co the duoc kho hang dap ung khong
        int soMonToiDa = SO_LUONG_TOI_DA_MOI_MON; // So luong mon vua chon toi da co the lam dua vao tinh trang nguyen lieu trong kho
        int chenhLech = 0; // So lan nguyen lieu trong kho voi nguyen lieu yeu cau trong menu
        int chonMonKhac = 0;
        int timThayNguyenLieu = 0;
        for(int i = 0; i < menu[chonMon - 1].soNguyenLieu; i++) {
            timThayNguyenLieu = 0;
            for(int j = 0; j < soNguyenLieuKho; j++) {
                if(strcmp(menu[chonMon - 1].nguyenLieu[i].tenNguyenLieu, kho[j].tenNguyenLieu) == 0) {
                    timThayNguyenLieu = 1;
                    chenhLech = (int) (kho[j].soLuong / menu[chonMon - 1].nguyenLieu[i].soLuong);
                    if(chenhLech == 0) {
                        chonMonKhac = 1;
                        break;
                    } else if(soMonToiDa > chenhLech) {
                        soMonToiDa = chenhLech;
                        break;
                    }
                }
            }
            if(chonMonKhac == 1 || timThayNguyenLieu == 0) {
                break;
            }
        }
        if(chonMonKhac == 1 || timThayNguyenLieu == 0) {
            printf("So nguyen lieu trong kho hien tai khong the lam mon nay. Vui long chon mon khac.\n");
            continue;
        }

        int soMonChon = 0;
        do {
            printf("Chi co the order %d mon %s. Nhap '0' de order mon khac.\n", soMonToiDa, menu[chonMon - 1].tenMon);
            printf("Nhap so luong cho mon %s: ", menu[chonMon - 1].tenMon);
            saferScanf("%d", &soMonChon);
        } while(soMonChon < 0 || soMonChon > soMonToiDa);
        if(soMonChon == 0) {
            continue;
        }

        // Dam bao lua chon mon nhu nhau se duoc cong don, chu khong phai la tung lua chon rieng le
        int coMat = 0;
        if(hoaDon.soMonGoi == 0) {
            strncpy(hoaDon.tenMonGoi[hoaDon.soMonGoi], menu[chonMon - 1].tenMon, DO_DAI_TEN_MON);
            hoaDon.giaMonGoi[hoaDon.soMonGoi] = menu[chonMon - 1].gia;
            hoaDon.soLuongMon[hoaDon.soMonGoi] = soMonChon;
            hoaDon.soMonGoi++;
        } else {
            for(int i = 0; i < hoaDon.soMonGoi; i++) {
                if(strcmp(hoaDon.tenMonGoi[i], menu[chonMon - 1].tenMon) == 0) {
                    hoaDon.soLuongMon[i] += soMonChon;
                    coMat = 1;
                    break;
                }
            }
            if(coMat == 0) {
                strncpy(hoaDon.tenMonGoi[hoaDon.soMonGoi], menu[chonMon - 1].tenMon, DO_DAI_TEN_MON);
                hoaDon.giaMonGoi[hoaDon.soMonGoi] = menu[chonMon - 1].gia;
                hoaDon.soLuongMon[hoaDon.soMonGoi] = soMonChon;
                hoaDon.soMonGoi++;
            }
        }
        
        hoaDon.tongTien += soMonChon * menu[chonMon - 1].gia;
        for(int i = 0; i < menu[chonMon - 1].soNguyenLieu; i++) {
            layNguyenLieu(kho, soNguyenLieuKho, menu[chonMon - 1].nguyenLieu[i], soMonChon); // Tru di nguyen lieu trong kho
            hoaDon.tienNguyenLieu += menu[chonMon - 1].nguyenLieu[i].gia * soMonChon;
        }
    }
    printf("\nTong tien thanh toan: %.2f\n", hoaDon.tongTien);

    // Lua chon su dung diem de giam gia
    int coSuDungDiem = 0;
    float diemTichLuySuDung = 0, gioiHanDiem = 0;
    if(hoaDon.tongTien > hoaDon.khachHang.diemTichLuy) {
        gioiHanDiem = hoaDon.khachHang.diemTichLuy;
    } else {
        gioiHanDiem = hoaDon.tongTien;
    }

    printf("Su dung diem tich luy de duoc giam gia? (1 - co) ");
    saferScanf("%d", &coSuDungDiem);
    if(coSuDungDiem == 1) {
        do {
            printf("Nhap so diem ban muon su dung.\n");
            printf("So diem khong duoc am va khong qua %.2f: ", gioiHanDiem);
            saferScanf("%f", &diemTichLuySuDung);
        } while(diemTichLuySuDung < 0 || diemTichLuySuDung > gioiHanDiem);

        hoaDon.khachHang.diemTichLuy -= diemTichLuySuDung;
        hoaDon.tongTien -= diemTichLuySuDung; 

        printf("So diem tich luy con lai: %.2f\n", hoaDon.khachHang.diemTichLuy);
        printf("So tien can thanh toan da duoc giam con: %.2f\n", hoaDon.tongTien);
    }

    // Tich luy diem cho khach hang
    hoaDon.khachHang.diemTichLuy += hoaDon.tongTien / 10;
    printf("So diem tich luy cua khach hang: %.2f\n", hoaDon.khachHang.diemTichLuy);

    float tienKhachDua, tienThua;
    printf("Nhap so tien khach dua: ");
    saferScanf("%f", &tienKhachDua);
    tienThua = tienKhachDua - hoaDon.tongTien;
    hoaDon.tienThua = tienThua;
    printf("Tien thua: %.2f\n", tienThua);
    
    int coTrongMang = 0;
    if(*soHoaDon == 0) {
        saoChepHoaDon(&danhSachHoaDon[*soHoaDon], &hoaDon);
        (*soHoaDon)++;
    } else {
        for(int i = 0; i < *soHoaDon; i++) {
            if(coNhuNhauHoaDon(danhSachHoaDon[i], hoaDon) == 1) {
                printf("Hoa don da co trong file");
                coTrongMang = 1;
                break;
            }
        }
        if(coTrongMang == 0) {
            saoChepHoaDon(&danhSachHoaDon[*soHoaDon], &hoaDon);
            (*soHoaDon)++;
            printf("\nHoa don da duoc luu\n");
        }
    }

    coTrongMang = 0;
    if(*soKhachHang == 0) {
        saoChepKhachHang(&danhSachKhachHang[*soKhachHang], &hoaDon.khachHang);
        (*soKhachHang)++;
    } else {
        for(int i = 0; i < *soKhachHang; i++) {
            if(strcmp(danhSachKhachHang[i].tenKhachHang, hoaDon.khachHang.tenKhachHang) == 0 
            && strcmp(danhSachKhachHang[i].soDienThoai, hoaDon.khachHang.soDienThoai) == 0) {
                danhSachKhachHang[i].diemTichLuy = hoaDon.khachHang.diemTichLuy;
                coTrongMang = 1;
                break;
            }
        }
        if(coTrongMang == 0) {
            saoChepKhachHang(&danhSachKhachHang[*soKhachHang], &hoaDon.khachHang);
            (*soKhachHang)++;
        }
    }
}

void xoaHoaDon(HoaDon danhSach[], int* soLuong, HoaDon* hoaDonXoa) {
    if(*soLuong == 0) {
        printf("Danh sach khong co hoa don\n");
        return;
    }

    for(int i = 0; i < *soLuong; i++) {
        if(coNhuNhauHoaDon(danhSach[i], *hoaDonXoa) == 1) {
            // Xoa khach hang bang cach di chuyen cac hoa don con lai
            for(int j = i; j < (*soLuong) - 1; j++) {
                danhSach[j] = danhSach[j + 1];
            }
            printf("Hoa don da duoc xoa\n");
            (*soLuong)--;
            return;
        }
    }
    printf("Khong tim thay hoa don\n");
}

void nhapThongTinHoaDon(HoaDon* hoaDon, MonAn menu[], int soMonMenu) { //CHANGE
    chuanHoaHoaDon(hoaDon, 1);

    printf("Nhap ten khach hang: ");
    fgets(hoaDon->khachHang.tenKhachHang, DO_DAI_TEN_KHACH - 1, stdin);
    hoaDon->khachHang.tenKhachHang[strcspn(hoaDon->khachHang.tenKhachHang, "\n")] = '\0';

    printf("Nhap so dien thoai khach hang: ");
    fgets(hoaDon->khachHang.soDienThoai, DO_DAI_SO_DIEN_THOAI - 1, stdin);
    hoaDon->khachHang.soDienThoai[strcspn(hoaDon->khachHang.soDienThoai, "\n")] = '\0';

    printf("Nhap diem tich luy khach hang: ");
    saferScanf("%f", &(hoaDon->khachHang.diemTichLuy));

    printf("Nhap ngay: ");
    saferScanf("%d", &hoaDon->ngayNhapDon.ngay);
    printf("Nhap thang: ");
    saferScanf("%d", &hoaDon->ngayNhapDon.thang);
    printf("Nhap nam: ");
    saferScanf("%d", &hoaDon->ngayNhapDon.nam);

    int soMonGoiMoi = 0;
    do {
        printf("Nhap so mon (toi da %d): ", MAX_MON);
        saferScanf("%d", &soMonGoiMoi);
    } while (soMonGoiMoi < 0 || soMonGoiMoi > MAX_MON);

    for (int i = 0; i < soMonGoiMoi; i++) {
        hienThiMenu(menu, soMonMenu);

        printf("Nhap ten mon an: ");
        char tenMonMoi[DO_DAI_TEN_MON];
        fgets(tenMonMoi, DO_DAI_TEN_MON, stdin);
        tenMonMoi[strcspn(tenMonMoi, "\n")] = '\0';

        int timThayMon = 0;
        for (int j = 0; j < soMonMenu; j++) {
            if (strcmp(tenMonMoi, menu[j].tenMon) == 0) {
                int soLuongMoi;
                do {
                    printf("Nhap so luong mon: ");
                    saferScanf("%d", &soLuongMoi);
                } while (soLuongMoi < 0);

                int daTonTai = 0;
                for (int k = 0; k < hoaDon->soMonGoi; k++) {
                    if (strcmp(hoaDon->tenMonGoi[k], tenMonMoi) == 0) {
                        hoaDon->soLuongMon[k] += soLuongMoi;
                        hoaDon->tongTien += menu[j].gia * soLuongMoi;

                        for (int m = 0; m < menu[j].soNguyenLieu; m++) {
                            hoaDon->tienNguyenLieu += menu[j].nguyenLieu[m].gia * soLuongMoi;
                        }
                        daTonTai = 1;
                        break;
                    }
                }

                if (daTonTai == 0) {
                    strncpy(hoaDon->tenMonGoi[hoaDon->soMonGoi], tenMonMoi, DO_DAI_TEN_MON);
                    hoaDon->soLuongMon[hoaDon->soMonGoi] = soLuongMoi;
                    hoaDon->giaMonGoi[hoaDon->soMonGoi] = menu[j].gia;

                    for (int m = 0; m < menu[j].soNguyenLieu; m++) {
                        hoaDon->tienNguyenLieu += menu[j].nguyenLieu[m].gia * soLuongMoi;
                    }

                    hoaDon->tongTien += menu[j].gia * soLuongMoi;
                    hoaDon->soMonGoi++;
                }

                timThayMon = 1;
                break;
            }
        }

        if (timThayMon == 0) {
            printf("Khong tim thay mon an trong menu.\n");
        }
    }

    float tienThanhToan;
    printf("Nhap so tien khach tra: ");
    saferScanf("%f", &tienThanhToan);
    hoaDon->tienThua = tienThanhToan - hoaDon->tongTien;
}

void capNhatHoaDonTuFile(HoaDon danhSachHoaDon[], int* soHoaDon, char duongDan[], int* soHoaDonFile) {
    if(*soHoaDonFile == 0) {
        printf("Khong co du lieu trong file\n");
        return;
    }

    HoaDon* danhSachHoaDonFile = (HoaDon*) malloc(sizeof(HoaDon) * (*soHoaDonFile));
    if(!danhSachHoaDonFile) {
        printf("Khong the tao mang dong cho hoa don\n");
        return;
    }
    docFileHoaDon(duongDan, *soHoaDonFile, danhSachHoaDonFile);

    int coMat = 0;
    for (int i = 0; i < *soHoaDonFile; i++) {
        coMat = 0;
        if (*soHoaDon >= MAX_HOA_DON) {
            printf("Mang da day\n");
            break;
        }

        for (int j = 0; j < *soHoaDon; j++) {
            if (coNhuNhauHoaDon(danhSachHoaDonFile[i], danhSachHoaDon[j])) {
                saoChepHoaDon(&danhSachHoaDon[j], &danhSachHoaDonFile[i]); 
                coMat = 1;
                break;
            }
        }

        if (coMat == 0) {
            saoChepHoaDon(&danhSachHoaDon[*soHoaDon], &danhSachHoaDonFile[i]);
            (*soHoaDon)++;
        }
    }

    free(danhSachHoaDonFile);
    printf("Cap nhat thanh cong\n");
}

void capNhatHoaDonTuMang(HoaDon danhSachHoaDon[], int* soHoaDon, char duongDan[], int* soHoaDonFile) {
    if(*soHoaDon == 0) {
        printf("Khong co du lieu trong mang\n");
        return;
    }

    for(int i = 0; i < *soHoaDon; i++) {
        themHoaDonVaoFile(danhSachHoaDon[i], duongDan);
    }
}

// -------------------------------------------------- Cac ham quan ly kho nguyen lieu ---------------------------------------------- //

void hienThiKho(NguyenLieu kho[], int soLuong) {
    if(soLuong == 0) {
        printf("Chua co nguyen lieu\n");
        return;
    }
    printf("DANH SACH NGUYEN LIEU TRONG KHO:\n");
    printf("%-3s %-25s %-10s %-10s\n", "STT", "Ten Nguyen Lieu", "Don Vi", "So Luong");
    for (int i = 0; i < soLuong; i++) {
        printf("%-3d %-25s %-10s %-10.2f\n", i + 1, kho[i].tenNguyenLieu, kho[i].donVi, kho[i].soLuong);
    }
}

void themNguyenLieu(NguyenLieu kho[], int* soLuong, NguyenLieu* nguyenLieuMoi) {
    if (*soLuong >= MAX_NGUYEN_LIEU) {
        printf("Kho da day, khong the them nguyen lieu moi!\n");
        return;
    }

    // Kiem tra xem loai nguyen lieu do da co trong mang hay chua. Chi can quan tam den ten
    for(int i = 0; i < *soLuong; i++) {
        if(strcmp(kho[i].tenNguyenLieu, nguyenLieuMoi->tenNguyenLieu) == 0) {
            printf("Nguyen lieu nay da co trong kho\n");                //MARK: LAP_MANG
            return;
        }
    }

    saoChepNguyenLieu(&kho[*soLuong], nguyenLieuMoi);
    (*soLuong)++;
    printf("Da them nguyen lieu vao mang\n");
}

void xoaNguyenLieu(NguyenLieu kho[], int* soLuong, NguyenLieu* nguyenLieuXoa) {
    if(*soLuong == 0) {
        return;
    }
    // Xoa phan tu tuong tu KhachXoa dau tien
    for(int i = 0; i < *soLuong; i++) {
        if(strcmp(kho[i].tenNguyenLieu, nguyenLieuXoa->tenNguyenLieu) == 0) {       //MARK: LAP_MANG
            for(int j = i; j < *soLuong - 1; j++) {
               saoChepNguyenLieu(&kho[j], &kho[j + 1]);
            }
            printf("Nguyen lieu da duoc xoa\n");
            (*soLuong)--;
            return;
        }
    }
    printf("Khong tim thay nguyen lieu\n");
}

int layNguyenLieu(NguyenLieu kho[], int soNguyenLieuKho, NguyenLieu nguyenLieuSuDung, int soMon) {
    for(int i = 0; i < soNguyenLieuKho; i++) {
        if(strcmp(nguyenLieuSuDung.tenNguyenLieu, kho[i].tenNguyenLieu) == 0) { //MARK: LAP_MANG
            if(nguyenLieuSuDung.soLuong * soMon <= kho[i].soLuong) {
                kho[i].soLuong -= nguyenLieuSuDung.soLuong * soMon;
                return 1;
            }

            printf("Khong the tru di nhieu nguyen lieu nhu vay\n");
            return -1;
        }
    }
}

void nhapThongTinNguyenLieu(NguyenLieu* nguyenLieu, int placeHolderArr[], int* placeHolderVal) {
    chuanHoaKho(nguyenLieu, 1);
    printf("Nhap ten nguyen lieu: ");
    fgets(nguyenLieu->tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1, stdin);
    nguyenLieu->tenNguyenLieu[strcspn(nguyenLieu->tenNguyenLieu, "\n")] = '\0';
    nguyenLieu->tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';

    printf("Nhap don vi do cua nguyen lieu: ");
    fgets(nguyenLieu->donVi, MAX_DO_DAI_CHUOI_DON_VI - 1, stdin);
    nguyenLieu->donVi[strcspn(nguyenLieu->donVi, "\n")] = '\0';
    nguyenLieu->donVi[MAX_DO_DAI_CHUOI_DON_VI - 1] = '\0';

    printf("Nhap so luong nguyen lieu: ");
    saferScanf("%f", &(nguyenLieu->soLuong));
}

void nhapTenNguyenLieu(NguyenLieu* nguyenLieu, int placeHolderArr[], int* placeHolderVal) {
    chuanHoaKho(nguyenLieu, 1);
    printf("Nhap ten nguyen lieu: ");
    fgets(nguyenLieu->tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1, stdin);
    nguyenLieu->tenNguyenLieu[strcspn(nguyenLieu->tenNguyenLieu, "\n")] = '\0';
    nguyenLieu->tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';
}

void timKiemNguyenLieu(NguyenLieu kho[], int soNguyenLieu) {
    if(soNguyenLieu == 0) {
        printf("Chua co nguyen lieu\n");
        return;
    }

    char tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU];
    printf("Nhap ten nguyen lieu: ");
    fgets(tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1, stdin);
    tenNguyenLieu[strcspn(tenNguyenLieu, "\n")] = '\0';     //MARK: STR_PRO
    tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';

    printf("\nDanh sach nguyen lieu tim duoc theo ten '%s':\n", tenNguyenLieu);
    for (int i = 0; i < soNguyenLieu; i++) {
        if (strstr(kho[i].tenNguyenLieu, tenNguyenLieu)) {
            printf("%d. %s - %.2f %s\n", i + 1, kho[i].tenNguyenLieu, kho[i].soLuong, kho[i].donVi);
        }
    }
}

void capNhatKhoTuFile(NguyenLieu kho[], int* soLuongKho, char duongDan[], int* soLuongFile) {
    if (*soLuongFile == 0) {
        printf("Khong co du lieu trong file\n");
        return;
    }

    NguyenLieu* khoFile = (NguyenLieu*)malloc(sizeof(NguyenLieu) * (*soLuongFile));
    if (!khoFile) {
        printf("Khong the tao mang dong cho du lieu tu file (memory allocation failed)\n");
        return;
    }

    docFileKho(duongDan, *soLuongFile, khoFile);

    for (int i = 0; i < *soLuongFile; i++) {
        int coMat = 0;

        if (*soLuongKho >= MAX_NGUYEN_LIEU) {
            printf("Mang da day\n");
            break; 
        }

        for (int j = 0; j < *soLuongKho; j++) {
            if (strcmp(khoFile[i].tenNguyenLieu, kho[j].tenNguyenLieu) == 0) {
                printf("Cap nhat nguyen lieu: %s\n", kho[j].tenNguyenLieu);
                saoChepNguyenLieu(&kho[j], &khoFile[i]); 
                coMat = 1;
                break;
            }
        }

        if (coMat == 0) {
            saoChepNguyenLieu(&kho[*soLuongKho], &khoFile[i]);
            (*soLuongKho)++;
        }
    }

    free(khoFile);

    printf("Cap nhat thanh cong\n");
}

void capNhatKhoTuMang(NguyenLieu kho[], int* soLuongKho, char duongDan[], int* soLuongFile) {   // CHANGE
    if (*soLuongKho == 0) {
        printf("Khong co du lieu trong mang\n");
        return;
    }

    NguyenLieu* khoFile = (NguyenLieu*)malloc(sizeof(NguyenLieu) * (*soLuongFile));
    if (!khoFile) {
        printf("Khong the tao mang dong cho kho\n");
        return;
    }
    docFileKho(duongDan, *soLuongFile, khoFile);

    NguyenLieu khoMoi[MAX_NGUYEN_LIEU];
    int soLuongMoi = 0;

    for (int i = 0; i < *soLuongFile && soLuongMoi < MAX_NGUYEN_LIEU; i++) {
        saoChepNguyenLieu(&khoMoi[soLuongMoi++], &khoFile[i]);
    }

    for (int i = 0; i < *soLuongKho; i++) {
        int found = 0;
        if(soLuongMoi >= MAX_NGUYEN_LIEU) {
            printf("File day\n");
            break;
        }

        for (int j = 0; j < soLuongMoi; j++) {
            if (strcmp(khoMoi[j].tenNguyenLieu, kho[i].tenNguyenLieu) == 0) {
                saoChepNguyenLieu(&khoMoi[j], &kho[i]);
                found = 1;
                break;
            }
        }

        if (found == 0) {
            saoChepNguyenLieu(&khoMoi[soLuongMoi++], &kho[i]);
        }
    }

    resetFile(LUA_CHON_KHO);
    themNhieuNguyenLieuVaoFile(khoMoi, soLuongMoi, duongDan);
    free(khoFile);
}

// --------------------------------------------------- Cac ham bo tro -------------------------------------------------------------- //

void docFileQuanLi(int luaChon, char duongDan[]) {
    // 1: file khach hang
    // 2: file hoa don
    // 3: file kho
    // 4: file menu
    if(luaChon < 1 || luaChon > 4) {
        printf("Lua chon mo file quan li khong hop le!\n");
        return;
    }   \
    FILE* fptr = fopen(MANAGING_FILE, "r");

    if (!fptr) {
        perror("Khong the mo file quan li file");
        return;
    }
    for(int i = 1; i <= luaChon; i++) {
        if(!fgets(duongDan, MAX_FILE_PATH_LENGTH, fptr)) { //DK !feof(fptr) ??
            perror("Xay ra loi khi doc file quan li");
            fclose(fptr);
            return;
        }
    }
    duongDan[strcspn(duongDan, "\n")] = '\0';
    fclose(fptr);
}

void capNhatFileQuanLi(int luaChon, char duongDanMoi[]) {
    // 1: file khach hang
    // 2: file hoa don
    // 3: file kho
    // 4: file menu

    if (luaChon < 1 || luaChon > SO_DOI_TUONG_LAM_VIEC) {
        printf("Lua chon khong hop le!\n");
        return;
    }
    // Loai bo ky tu newline cua dau vao (neu co). Neu dau vao khong co newline, doan code nay khong gay anh huong gi
    if(strlen(duongDanMoi) != 0) {
        duongDanMoi[strcspn(duongDanMoi, "\n")] = '\0';     
    }

    // Mo file de doc
    char noiDungFile[SO_DOI_TUONG_LAM_VIEC][MAX_FILE_PATH_LENGTH] = {""}; // Store up to 3 lines
    FILE* fptr1 = fopen(MANAGING_FILE, "r");
    if (!fptr1) {
        perror("Khong the mo file quan li!");
        return;
    }

    // Luu noi dung file ra mang tam thoi
    for (int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
        if (!fgets(noiDungFile[i], MAX_FILE_PATH_LENGTH, fptr1)) {//DK !feof(fptr) ??
                perror("Co loi khi doc file quan li");
                fclose(fptr1);
                return;
        } else {
            // Xoa bo ky tu newline cua tat ca duong dan cu
            noiDungFile[i][strcspn(noiDungFile[i], "\n")] = '\0';   //MARK: STR_PRO
        }
    }
    fclose(fptr1);

    // Update noi dung cua duong dan moi vao mang tam thoi
    // Su dung MAX_FILE_PATH_LENGTH - 1 de dam bao cho cho ky tu '\0'
    strncpy(noiDungFile[luaChon - 1], duongDanMoi, MAX_FILE_PATH_LENGTH - 1); // Dieu nay chi thuong co anh huong khi duong dan moi dai hon MAX_FILE_PATH_LENGTH
    noiDungFile[luaChon - 1][MAX_FILE_PATH_LENGTH - 1] = '\0';      //MARK: STR_PRO

    // Mo file de viet lai noi dung moi
    FILE* fptr2 = fopen(MANAGING_FILE, "w");
    if (!fptr2) {
        perror("Khong the mo file quan li de ghi");
        return;
    }

    // Viet noi dung moi, them '\n' vao cuoi moi duong dan de dung dinh dang
    for (int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
        fprintf(fptr2, "%s\n", noiDungFile[i]);
    }
    fclose(fptr2);
}

void clearBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF) {}; // Doc buffer den khi gap ky tu xuong dong (enter) hoac den het buffer (neu buffer khong co xuong dong)
}

void saferScanf(char formatString[], void* addr) {
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

void resetFile(int luaChon) {
    if(luaChon < 1 || luaChon > SO_DOI_TUONG_LAM_VIEC) {
        printf("Lua chon doi tuong khong hop le\n");
        return;
    }

    char duongDan[MAX_FILE_PATH_LENGTH];
    docFileQuanLi(luaChon, duongDan);

    FILE* fptr = fopen(duongDan, "w");
    if(!fptr) {
        perror("Reset file that bai");
        return;
    }

    switch(luaChon) {
        case LUA_CHON_KHACH_HANG:
            fprintf(fptr, KHACH_HANG_HEADER);
            break;
        case LUA_CHON_HOA_DON:
            fprintf(fptr, HOA_DON_HEADER);
            break;
        case LUA_CHON_KHO:
            fprintf(fptr, KHO_HEADER);
            break;
        case LUA_CHON_MENU:
            fprintf(fptr, MENU_HEADER);
            break;
        default:
            printf("Lua chon khong hop le\n");
            break;
    }

    fclose(fptr);
}

// --------------------------------------------------- Cac ham chung ----------------------------------------------------------------- //
void xemDanhSach(void (*docFile)(char duongDan[], int soPhanTuDoc, void* danhSach), int (*kiemTraSoLuong)(char duongDan[]),
                    void (*hienThi)(void* mang, int soPhanTuMang), char fileQuanLi[], int soLuongHienTai, int doLonVat, void* danhSachHienTai) {
    int luaChonXem;
    printf("Xem mang hien tai (1) hay xem tu file (2): ");
    saferScanf("%d", &luaChonXem);

    if(luaChonXem != 1 && luaChonXem != 2) {
        printf("Lua chon khong hop le.\n");
        return;
    }

    if(luaChonXem == 1) {
        if(soLuongHienTai == 0) {
            printf("Khong ton tai du lieu trong mang\n");
            return;
        }
        hienThi(danhSachHienTai, soLuongHienTai);
    } else {
        int soLuongFile = kiemTraSoLuong(fileQuanLi);
        if (soLuongFile == 0) {
            printf("Chua co du lieu trong file\n");
            return;
        }

        void* danhSachFile = malloc(doLonVat * soLuongFile); 
        if (!danhSachFile) {
            printf("Khong the khoi tao mang dong\n");
            return;
        }

        docFile(fileQuanLi, soLuongFile, danhSachFile);
        hienThi(danhSachFile, soLuongFile);
        free(danhSachFile);
    }
}

void reset(int* soPhanTuHienTai, int luaChonDoiTuong) {
    int canhCao;
    printf("CANH BAO: VIEC NAY SE XOA TOAN BO DU LIEU CUA BAN VA KHONG THE BI DAO NGUOC. TIEP TUC? (1) ");
    saferScanf("%d", &canhCao);
    if(canhCao != 1) {
        return;
    }

    int luaChonXoa;
    printf("Xoa du lieu mang hien tai (1) hay xoa du lieu file (2) ");
    saferScanf("%d", &luaChonXoa);
                            
    if(luaChonXoa != 1 && luaChonXoa != 2) {
        printf("Lua chon khong hop le\n");
        return;
    } else if(luaChonXoa == 1) {
        *soPhanTuHienTai = 0;
        printf("Mang da duoc reset\n");
    } else {
        resetFile(luaChonDoiTuong);
    }
}

void xoaPhanTu(void (*xoaMang)(void* mang, int* soLuong, void* vat), void (*xoaFile)(char duongDan[], void* vat),
                void (*nhapThongTin)(void* vatThe, void* mang, int soLuong), int* soPhanTuMang, void* mangHienTai, int* soPhanTuMangDieuKien,
                void* mangDieuKien, int* soPhanTuFile, void* vatXoa, char duongDan[]) {
    int luaChonXoaBo;
    printf("Xoa trong mang hien tai (1) hay xoa trong file (2): ");
    saferScanf("%d", &luaChonXoaBo);
    if(luaChonXoaBo != 1 && luaChonXoaBo != 2) {
        printf("Lua chon khong hop le\n");
        return;
    } else if(luaChonXoaBo == 1) {
        if(*soPhanTuMang == 0) {
            printf("Mang khong co phan tu\n");
            return;
        }
        nhapThongTin(vatXoa, mangDieuKien, *soPhanTuMangDieuKien);
        xoaMang(mangHienTai, soPhanTuMang, vatXoa);
    } else {
        if(*soPhanTuFile == 0) {
            printf("File khong co phan tu\n");
            return;
        }
        nhapThongTin(vatXoa, mangDieuKien, *soPhanTuMangDieuKien);
        xoaFile(duongDan, vatXoa);
    }
}

void themPhanTu(void (*nhapThongTin)(void* vat, void* mang, int soLuongMang), void (*themVaoFile)(char duongDan[], void* vatThem),
                void (*themVaoMang)(void* mang, int* soLuongMang, void* vatThem), void* mangHienTai, int* soLuongMangHienTai, void* mangDieuKien, int* soLuongMangDieuKien,
                int* soLuongFile, int gioiHan, void* vatThem, char duongDan[]) {
    int luaChonThem;
    printf("Them vao mang hien tai (1) hay them vao file (2): ");
    saferScanf("%d", &luaChonThem);
    if(luaChonThem != 1 && luaChonThem != 2) {
        printf("Lua chon khong hop le\n");
        return;
    } else if(luaChonThem == 1) {
        if(*soLuongMangHienTai >= gioiHan) {
            printf("Mang da day\n");
            return;
        }
        nhapThongTin(vatThem, mangDieuKien, *soLuongMangDieuKien);
        themVaoMang(mangHienTai, soLuongMangHienTai, vatThem);
    } else {
        if(*soLuongFile >= gioiHan) {
            printf("File da day\n");
            return;
        }
        nhapThongTin(vatThem, mangDieuKien, *soLuongMangDieuKien);
        themVaoFile(duongDan, vatThem);
    }
}

void capNhatDuLieu(void (*capNhatMangTuFile)(void* mang, int* soLuongMang, char duongDan[], int* soLuongFile),
                    void (*capNhatFileTuMang)(void* mang, int* soLuongMang, char duongDan[], int* soLuongFile),
                    void* mangHienTai,int* soLuongMang, int* soLuongFile, char duongDan[]) {
    int luaChonCapNhat;
    printf("Cap nhat thong tin tu file vao mang (1) hay tu mang vao file (2) ");
    saferScanf("%d", &luaChonCapNhat);
    if(luaChonCapNhat != 1 && luaChonCapNhat != 2) {
        printf("Lua chon khong hop le\n");
        return;
    }

    if(luaChonCapNhat == 1 && *soLuongFile == 0) {
        printf("File khong co mon an\n");
        return;
    } else if(luaChonCapNhat == 2 && *soLuongMang == 0) {
        printf("Mang khong co mon an\n");
        return;
    }

    if(luaChonCapNhat == 1) {
        capNhatMangTuFile(mangHienTai, soLuongMang, duongDan, soLuongFile);
    } else {
        capNhatFileTuMang(mangHienTai, soLuongMang, duongDan, soLuongFile);
    }
}

void timKiemDuLieu(void (*timKiem)(void* mang, int soLuongMang), void (*docFile)(char duongDan[], int soLuongDoc, void* mangFile),
                    void* mangHienTai, int soLuongMang, int soLuongFile, char duongDan[], int doLonVat) {
    int luaChonTimKiem;
    printf("Tim kiem trong mang (1) hay trong file (2): ");
    saferScanf("%d", &luaChonTimKiem);
    if (luaChonTimKiem != 1 && luaChonTimKiem != 2) {
        printf("Lua chon khong hop le\n");
        return;
    } else if (luaChonTimKiem == 1) {
        if(soLuongMang == 0) {
            printf("Chua co du lieu trong mang\n");
        }
        timKiem(mangHienTai, soLuongMang);
    } else {
        if (soLuongFile == 0) {
            printf("Chua co du lieu trong file\n");
            return;
        }
        void* mangFile = malloc(doLonVat * soLuongFile);
        if (!mangFile) {
            printf("Khong the khoi tao mang dong de tim kiem\n");
            return;
        }
        docFile(duongDan, soLuongFile, mangHienTai);

        timKiem(mangFile, soLuongFile);

        free(mangFile);
    }
}
