#include "customer.h"
#include "general.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void chuanHoaKhachHang(KhachHang* khachHang, int soKhachHang) {
    for (int i = 0; i < soKhachHang; i++) {
        // Su dung ky tu khac \0 de mac dinh cac thuoc tinh string cua struct la rat quan trong de strtok lam viec dung
        memset(khachHang[i].tenKhachHang, '0', 2);
        khachHang[i].tenKhachHang[1] = '\0';

        memset(khachHang[i].soDienThoai, '0', 2);
        khachHang[i].soDienThoai[1] = '\0';

        khachHang[i].diemTichLuy = 0;
    }
}

void saoChepKhachHang(KhachHang* khachNhan, KhachHang* khachNguon) {
    // khachNhan, khachNguon la dia chi cua khach nhan va cho su sao chep.
    // Thuc hien deep copying thay vi shallow copying su dung memcpy hay "="
    strncpy(khachNhan->tenKhachHang, khachNguon->tenKhachHang, DO_DAI_TEN_KHACH - 1);  // khachNhan->tenKhachHang tuong duong (*khachNhan).tenKhachHang
    khachNhan->tenKhachHang[DO_DAI_TEN_KHACH - 1] = '\0';
    strncpy(khachNhan->soDienThoai, khachNguon->soDienThoai, DO_DAI_SO_DIEN_THOAI - 1);
    khachNhan->soDienThoai[DO_DAI_SO_DIEN_THOAI - 1] = '\0';
    khachNhan->diemTichLuy = khachNguon->diemTichLuy;
}

int kiemTraSoKhachHang(char duongDan[]) {
    FILE *fptr = fopen(duongDan, "r");
    if(!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong khach hang");
        return -1;
    }

    int soKhachHang = 0;
    fseek(fptr, sizeof(KHACH_HANG_HEADER), SEEK_SET); // Bo qua header
    char msg[MAX_ARRAY_LENGTH_KHACH_HANG];
    while(fgets(msg, MAX_ARRAY_LENGTH_KHACH_HANG, fptr)) {
        soKhachHang++;
    }

    fclose(fptr);

    return soKhachHang;
}

int coNhuNhauKhachHang(KhachHang k1, KhachHang k2) {
    // Kiem tra xem hai khach hang co cung thuoc tinh khong.
    // Tra ve 1 neu nhu nhau, 0 neu khac nhau
    if(strcmp(k1.tenKhachHang, k2.tenKhachHang) == 0 && strcmp(k1.soDienThoai, k2.soDienThoai) == 0 && k1.diemTichLuy == k2.diemTichLuy) {
        return 1;
    } 
    return 0;
}

void docFileKhachHang(char duongDan[], int soKhachHangDoc, KhachHang danhSachKhachHang[]) {
    if(soKhachHangDoc == 0) {
        return;
    }

    FILE *fptr = fopen(duongDan, "r");
    if (!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong khach hang");
        return;
    }

    chuanHoaKhachHang(danhSachKhachHang, soKhachHangDoc);
    char msg[MAX_ARRAY_LENGTH_KHACH_HANG];
    fseek(fptr, sizeof(KHACH_HANG_HEADER), SEEK_SET); // Bo qua header

    for (int i = 0; i < soKhachHangDoc; i++) {
        if (fgets(msg, MAX_ARRAY_LENGTH_KHACH_HANG - 1, fptr) == NULL) {
            perror("Xay ra loi khi sao chep tu file khach hang");
            break;
        }

        msg[MAX_ARRAY_LENGTH_KHACH_HANG - 1] = '\0'; // Dam bao msg duoc null terminate
        msg[strcspn(msg, "\n")] = '\0'; // Loai bo newline mac dinh;

        char *tenKhachHang = strtok(msg, NGAN_PHAN_TU_CSV);
        if (tenKhachHang) {
            strncpy(danhSachKhachHang[i].tenKhachHang, tenKhachHang, DO_DAI_TEN_KHACH - 1);
            danhSachKhachHang[i].tenKhachHang[DO_DAI_TEN_KHACH - 1] = '\0';
        }

        char *soDienThoai = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (soDienThoai) {
            strncpy(danhSachKhachHang[i].soDienThoai, soDienThoai, DO_DAI_SO_DIEN_THOAI - 1);
            danhSachKhachHang[i].soDienThoai[DO_DAI_SO_DIEN_THOAI - 1] = '\0';
        }

        char* diemTichLuy = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (diemTichLuy) {
            danhSachKhachHang[i].diemTichLuy = atof(diemTichLuy);
        }

    }

    fclose(fptr);
}

void xoaKhachKhoiFile(char duongDan[], KhachHang* khachXoa) {
    int soKhachHangFile = kiemTraSoKhachHang(duongDan);
    if(soKhachHangFile == 0) {
        printf("File khong co khach hang\n");
        return;
    }

    // Xoa mot khach hang co spec tuong tu khachXoa khoi file
    KhachHang* danhSachKhachHangFile = (KhachHang*) malloc(sizeof(KhachHang) * soKhachHangFile);
    docFileKhachHang(duongDan, soKhachHangFile, danhSachKhachHangFile);

    int coMat = 0;
    for(int i = 0; i < soKhachHangFile; i++) {
        if(strcmp(danhSachKhachHangFile[i].soDienThoai, khachXoa->soDienThoai) == 0) { //SSK
            for(int j = i; j < soKhachHangFile - 1; j++) {
                danhSachKhachHangFile[j] = danhSachKhachHangFile[j + 1];
            }
            soKhachHangFile--;
            coMat = 1;
            break;
        }
    }
    if(coMat == 0) {
        printf("Khach hang khong co trong file\n");
        free(danhSachKhachHangFile);
        return;
    }

    FILE* fptr = fopen(duongDan, "w");
    if(!fptr) {
        perror("Khong the mo file khach hang de xoa khach hang");
        return;
    }
        
    fprintf(fptr, KHACH_HANG_HEADER);
    for(int i = 0; i < soKhachHangFile; i++) {
        fprintf(fptr, "%s,%s,%.2f\n", danhSachKhachHangFile[i].tenKhachHang, danhSachKhachHangFile[i].soDienThoai, danhSachKhachHangFile[i].diemTichLuy);
    }

    printf("Xoa khach hang khoi file thanh cong\n");
    fclose(fptr);
    free(danhSachKhachHangFile);
}

void themKhachHangVaoFile(char duongDan[], KhachHang* khach) {
    int soKhachFile = kiemTraSoKhachHang(duongDan);
    KhachHang* danhSachKhachFile = (KhachHang*) malloc(sizeof(KhachHang) * soKhachFile);
    if(!danhSachKhachFile) {
        printf("Khong the khoi tao mang dong khach hang\n");
        return;
    }

    for(int i = 0; i < soKhachFile; i++) {
        if(strcmp(danhSachKhachFile[i].soDienThoai, khach->soDienThoai) == 0) { //SSK
                printf("Khach hang da co trong file\n");
                free(danhSachKhachFile);
                return;
        }
    }

    FILE* fptr = fopen(duongDan, "a"); // mode "a": them thong tin vao cuoi file
    if(!fptr) {
        perror("Khong the them khach hang vao file");
        return;
    }
    fprintf(fptr, "%s,%s,%.2f\n", khach->tenKhachHang, khach->soDienThoai, khach->diemTichLuy);
    free(danhSachKhachFile);
    fclose(fptr);
    printf("Khach hang da duoc them\n");
}

void themNhieuKhachVaoFile(KhachHang danhSachKhach[], int soKhach, char duongDan[]) {
    FILE* fptr = fopen(duongDan, "a");
    if(!fptr) {
        perror("Khong the them khach vao file");
        return;
    }

    for(int i = 0; i < soKhach; i++) {
        fprintf(fptr, "%s,%s,%.2f\n", danhSachKhach[i].tenKhachHang, danhSachKhach[i].soDienThoai, danhSachKhach[i].diemTichLuy);
    }

    fclose(fptr);
}

void xemDanhSachKhachHang(KhachHang danhSachKhachHang[], int soKhachHang) {
    if(soKhachHang == 0) {
        printf("Chua co khach hang\n");
        return;
    }

    printf("%-5s %-20s %-20s %-15s\n", "STT", "Ten khach hang", "So dien thoai", "Diem tich luy");

    for (int i = 0; i < soKhachHang; i++) {
        printf("%-5d %-20s %-20s %-5.2f\n", i + 1, danhSachKhachHang[i].tenKhachHang, danhSachKhachHang[i].soDienThoai, danhSachKhachHang[i].diemTichLuy);
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
        printf("%-5s %-20s %-20s %-15s\n", "STT", "Ten khach hang", "So dien thoai", "Diem tich luy");
        for (int i = 0; i < soKhachHang; i++) {
            if (strstr(danhSachKhachHang[i].tenKhachHang, keyword) != NULL) {
                printf("%-5d %-20s %-20s %-5.2f\n", i + 1, danhSachKhachHang[i].tenKhachHang, danhSachKhachHang[i].soDienThoai, danhSachKhachHang[i].diemTichLuy);
            }
        }
    } else if (luaChon == 2) {
        printf("Nhap so dien thoai khach hang: ");
        fgets(keyword, sizeof(keyword) - 1, stdin);
        keyword[strcspn(keyword, "\n")] = '\0'; // Loại bỏ ký tự newline
        keyword[sizeof(keyword) - 1] = '\0';

        printf("\nDanh sach khach hang tim duoc theo so dien thoai '%s':\n", keyword);
        printf("%-5s %-20s %-20s %-15s\n", "STT", "Ten khach hang", "So dien thoai", "Diem tich luy");
        for (int i = 0; i < soKhachHang; i++) {
            if (strstr(danhSachKhachHang[i].soDienThoai, keyword) != NULL) {
                printf("%-5d %-20s %-20s %-5.2f\n", i + 1, danhSachKhachHang[i].tenKhachHang, danhSachKhachHang[i].soDienThoai, danhSachKhachHang[i].diemTichLuy);
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
        if(strcmp(danhSachKhachHang[i].soDienThoai, khachHangMoi->soDienThoai) == 0) {
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
        if(strcmp(danhSachKhach[i].soDienThoai, khachXoa->soDienThoai) == 0) {
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
        if(strcmp(khach->soDienThoai, danhSachKhachHang[i].soDienThoai) == 0) {
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
            if (strcmp(danhSach[j].soDienThoai, danhSachKhachHangFile[i].soDienThoai) == 0) {
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
            if (strcmp(danhSachKhachFile[j].soDienThoai, danhSach[i].soDienThoai) == 0) {
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

    resetFile(LUA_CHON_KHACH_HANG);
    themNhieuKhachVaoFile(danhSachMoi, *soKhachFile, duongDan);

    free(danhSachKhachFile);
    free(danhSachMoi);

    printf("Cap nhat thanh cong\n");
}

