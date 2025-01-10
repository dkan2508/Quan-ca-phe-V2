#include "menu.h"
#include "customer.h"
#include "kho.h"
#include "bill.h"
#include "menu.h"
#include "general.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Lenh compile va chay chuong trinh
cd "<DUONG DAN DEN FOLDER CHUA CAC FILE MA NGUON>" ; if ($?) { gcc main.c general.c bill.c customer.c kho.c menu.c -o main } ; if ($?) { .\main }
*/

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

int main() {
    int soMonMacDinh = 10;
    KhachHang danhSachKhachHang[MAX_KHACH_HANG];
    HoaDon danhSachHoaDon[MAX_HOA_DON];
    int soKhachHang = 0, soHoaDon = 0;

    // Cac phan tu chi co mat de dam bao syntax, khong co vai tro
    int placeHolderArr[] = {0};
    int placeHolderVal = 0;

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
                            xoaPhanTu((void (*)(void*, int*, void*))xoaMonAnTrongMang, (void (*)(char*, void*))xoaMonAnKhoiFile,
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
                
                            char monThayDoi[DO_DAI_TEN_MON];
                            int timThayMon = 0;
                            int viTriMonCanSua = 0; // Index mon can sua trong menu
                            if(luaChonSua == 1) {
                                if(soMonSuDung == 0) {
                                    printf("Menu hien tai khong co mon an\n");
                                    break;
                                }
                                     
                                hienThiMenu(menuSuDung, soMonSuDung);
                                printf("Nhap ten mon an can thay doi: ");
                                fgets(monThayDoi, DO_DAI_TEN_MON - 1, stdin);
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
                                fgets(monThayDoi, DO_DAI_TEN_MON - 1, stdin);
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
                            int soFile = kiemTraSoHoaDon(fileQuanLiChung);
                            timKiemDuLieu((void (*)(void*, int))timKiemHoaDon, (void (*)(char[], int, void*))docFileHoaDon, danhSachHoaDon,
                                            soHoaDon, soFile, fileQuanLiChung, sizeof(HoaDon));
                            break;
                        }
                        case 3: {
                            HoaDon hoaDonMoi;
                            nhapThongTinHoaDon(&hoaDonMoi, menuSuDung, soMonSuDung);
                            docFileQuanLi(LUA_CHON_HOA_DON, fileQuanLiChung);
                            themHoaDonVaoFile(hoaDonMoi, fileQuanLiChung);
                            printf("Hoa don duoc them thanh cong\n");
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
