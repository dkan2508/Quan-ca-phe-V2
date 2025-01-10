#include "general.h"
#include "kho.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void chuanHoaKho(NguyenLieu* kho, int soNguyenLieu) {
    for (int i = 0; i < soNguyenLieu; i++) {
        // Su dung ky tu khac \0 de mac dinh cac thuoc tinh string cua struct la rat quan trong de strtok lam viec dung
        memset(kho[i].tenNguyenLieu, '0', 2);
        kho[i].tenNguyenLieu[1] = '\0';

        memset(kho[i].donVi, '0', 2);
        kho[i].donVi[1] = '\0';

        kho[i].soLuong = 0;
        kho[i].gia = 0;
    }
}

void saoChepNguyenLieu(NguyenLieu* nguyenLieuNhan, NguyenLieu* nguyenLieuNguon) {
    // nguyenLieuNhan, nguyenLieuNguon la dia chi cua nguyen lieu nhan va cho su sao chep.
    // Thuc hien deep copying thay vi shallow copying su dung memcpy hay "="
    strncpy(nguyenLieuNhan->tenNguyenLieu, nguyenLieuNguon->tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1);  // khachNhan->tenKhachHang tuong duong (*khachNhan).tenKhachHang
    nguyenLieuNhan->tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';
    strncpy(nguyenLieuNhan->donVi, nguyenLieuNguon->donVi, MAX_DO_DAI_CHUOI_DON_VI - 1);
    nguyenLieuNhan->donVi[MAX_DO_DAI_CHUOI_DON_VI - 1] = '\0';
    nguyenLieuNhan->soLuong = nguyenLieuNguon->soLuong;
    nguyenLieuNhan->gia = nguyenLieuNguon->gia;
}

void themNhieuNguyenLieuVaoFile(NguyenLieu danhSachNguyenLieu[], int soNguyenLieu, char duongDan[]) {
    // Su dung ham nay thay cho themNguyenLieuVaoFile khi cap nhat mang du lieu de tranh dong mo file nhieu lan

    FILE* fptr = fopen(duongDan, "a");
    if(!fptr) {
        perror("Khong the them nguyen lieu vao file");
        return;
    }

    for(int i = 0; i < soNguyenLieu; i++) {
        fprintf(fptr, "%s,%s,%.2f,%.2f\n", danhSachNguyenLieu[i].tenNguyenLieu, danhSachNguyenLieu[i].donVi, danhSachNguyenLieu[i].soLuong, danhSachNguyenLieu[i].gia);
    }

    fclose(fptr);
}

int kiemTraSoNguyenLieu(char duongDan[]) {
    FILE *fptr = fopen(duongDan, "r");
    if(!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong nguyen lieu");
        return -1;
    }

    int soNguyenLieu = 0;
    fseek(fptr, sizeof(KHO_HEADER), SEEK_SET); // Bo qua header
    char msg[MAX_ARRAY_LENGTH_KHO];
    while(fgets(msg, MAX_ARRAY_LENGTH_KHO, fptr)) {
        soNguyenLieu++;
    }

    fclose(fptr);

    return soNguyenLieu;
}

int coNhuNhauNguyenLieu(NguyenLieu h1, NguyenLieu h2) {
    // Kiem tra xem hai nguyen lieu co cung thuoc tinh khong.
    // Tra ve 1 neu nhu nhau, 0 neu khac nhau
    if(strcmp(h1.tenNguyenLieu, h2.tenNguyenLieu) == 0 && strcmp(h1.donVi, h2.donVi) == 0 && h1.soLuong == h2.soLuong && h1.gia == h2.gia) {
        return 1;
    } 
    return 0;
}

void docFileKho(char duongDan[], int soNguyenLieu, NguyenLieu kho[]) {
    if(soNguyenLieu == 0) {
        return;
    }

    FILE *fptr = fopen(duongDan, "r");
    if (!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong nguyen lieu");
        return;
    }

    chuanHoaKho(kho, soNguyenLieu);
    char msg[MAX_ARRAY_LENGTH_KHO];
    fseek(fptr, sizeof(KHO_HEADER), SEEK_SET); // Bo qua header

    for (int i = 0; i < soNguyenLieu; i++) {
        if (fgets(msg, MAX_ARRAY_LENGTH_KHO - 1, fptr) == NULL) {
            perror("Xay ra loi khi sao chep tu file nguyen lieu");
            break;
        }

        msg[MAX_ARRAY_LENGTH_KHO - 1] = '\0';
        msg[strcspn(msg, "\n")] = '\0'; // Loai bo newline mac dinh;

        char *tenNguyenLieu = strtok(msg, NGAN_PHAN_TU_CSV);
        if (tenNguyenLieu) {
            strncpy(kho[i].tenNguyenLieu, tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1);
            kho[i].tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';
        }

        char *donVi = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (donVi) {
            strncpy(kho[i].donVi, donVi, MAX_DO_DAI_CHUOI_DON_VI - 1);
            kho[i].donVi[MAX_DO_DAI_CHUOI_DON_VI - 1] = '\0';
        }

        char* soLuong = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (soLuong) {
            kho[i].soLuong = atof(soLuong);
        }

        char* gia = strtok(NULL, NGAN_PHAN_TU_CSV);
        if(gia) {
            kho[i].gia = atof(gia);
        }
    }

    fclose(fptr);
}

void xoaNguyenLieuKhoiFile(char duongDan[], NguyenLieu* nguyenLieuXoa) {
    int soNguyenLieuFile = kiemTraSoNguyenLieu(duongDan);
    if(soNguyenLieuFile == 0) {
        printf("Kho trong\n");
        return;
    }

    NguyenLieu* khoFile = (NguyenLieu*) malloc(sizeof(NguyenLieu) * soNguyenLieuFile);
    docFileKho(duongDan, soNguyenLieuFile, khoFile);

    for(int i = 0; i < soNguyenLieuFile; i++) {
        if(strcmp(khoFile[i].tenNguyenLieu, nguyenLieuXoa->tenNguyenLieu) == 0) { //SSN
            for(int j = i; j < soNguyenLieuFile - 1; j++) {
                saoChepNguyenLieu(&khoFile[j], &khoFile[j + 1]);
            }
            soNguyenLieuFile--;
            break;
        }
    }

    FILE* fptr = fopen(duongDan, "w");
    if(!fptr) {
        perror("Khong the mo file kho de xoa nguyen lieu");
        return;
    }
        
    fprintf(fptr, KHO_HEADER);
    for(int i = 0; i < soNguyenLieuFile; i++) {
        fprintf(fptr, "%s,%s,%.2f,%.2f\n", khoFile[i].tenNguyenLieu, khoFile[i].donVi, khoFile[i].soLuong, khoFile[i].gia);
    }

    printf("Xoa nguyen lieu khoi file kho thanh cong\n");
    fclose(fptr);
    free(khoFile);
}

void themNguyenLieuVaoFile(char duongDan[], NguyenLieu* nguyenLieu) {
    int soNguyenLieuFile = kiemTraSoNguyenLieu(duongDan);
    if(soNguyenLieuFile >= MAX_NGUYEN_LIEU) {
        printf("File nguyen lieu day\n");
        return;
    }

    NguyenLieu* khoFile = (NguyenLieu*) malloc(sizeof(NguyenLieu) * soNguyenLieuFile);
    if(!khoFile) {
        printf("Khong the tao mang dong nguyen lieu\n");
        return;
    }
    docFileKho(duongDan, soNguyenLieuFile, khoFile);

    for(int i = 0; i < soNguyenLieuFile; i++) {
        if(strcmp(khoFile[i].tenNguyenLieu, nguyenLieu->tenNguyenLieu) == 0) { //SSN
            printf("Nguyen lieu da co trong file\n");
            free(khoFile);
            return;
        }
    }

    FILE* fptr = fopen(duongDan, "a"); // mode "a": them thong tin vao cuoi file
    if(!fptr) {
        perror("Khong the them nguyen lieu vao file");
        return;
    }

    fprintf(fptr, "%s,%s,%.2f,%.2f\n", nguyenLieu->tenNguyenLieu, nguyenLieu->donVi, nguyenLieu->soLuong, nguyenLieu->gia);
    free(khoFile);
    fclose(fptr);

    printf("Nguyen lieu da duoc them vao file\n");
}

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

void layNguyenLieu(NguyenLieu kho[], int soNguyenLieuKho, NguyenLieu nguyenLieuSuDung, int soMon) {
    for(int i = 0; i < soNguyenLieuKho; i++) {
        if(strcmp(nguyenLieuSuDung.tenNguyenLieu, kho[i].tenNguyenLieu) == 0) { //MARK: LAP_MANG
            if(nguyenLieuSuDung.soLuong * soMon <= kho[i].soLuong) {
                kho[i].soLuong -= nguyenLieuSuDung.soLuong * soMon;
                return;
            }

            printf("Khong the tru di nhieu nguyen lieu nhu vay\n");
            return;
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
    printf("%-3s %-25s %-10s %-10s\n", "STT", "Ten Nguyen Lieu", "Don Vi", "So Luong");
    for (int i = 0; i < soNguyenLieu; i++) {
        if (strstr(kho[i].tenNguyenLieu, tenNguyenLieu)) {
            printf("%-3d %-25s %-10s %-10.2f\n", i + 1, kho[i].tenNguyenLieu, kho[i].soLuong, kho[i].donVi);
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

    printf("Cap nhat thanh cong\n");
}
