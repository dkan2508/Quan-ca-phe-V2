#include "general.h"
#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int kiemTraSoMonAn(char duongDan[]) {
    FILE *fptr = fopen(duongDan, "r");
    if(!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong mon an trong menu");
        return -1;
    }

    int soMonAn = 0;
    fseek(fptr, sizeof(MENU_HEADER), SEEK_SET); // Bo qua header
    char msg[MAX_ARRAY_LENGTH_MENU];
    while(fgets(msg, MAX_ARRAY_LENGTH_MENU, fptr)) {
        soMonAn++;
    }

    fclose(fptr);

    return soMonAn;
}

void saoChepMonAn(MonAn* monAnNhan, MonAn* monAnNguon) {
    // monAnNhan, monAnNguon la dia chi cua nguyen lieu nhan va cho su sao chep.
    // Thuc hien deep copying thay vi shallow copying su dung memcpy hay "="
    strncpy(monAnNhan->tenMon, monAnNguon->tenMon, DO_DAI_TEN_MON - 1);  // khachNhan->tenKhachHang tuong duong (*khachNhan).tenKhachHang
    monAnNhan->tenMon[DO_DAI_TEN_MON - 1] = '\0';
    monAnNhan->gia = monAnNguon->gia;
    monAnNhan->soNguyenLieu = monAnNguon->soNguyenLieu;
    for(int i = 0; i < monAnNguon->soNguyenLieu; i++) {
        saoChepNguyenLieu(&(monAnNhan->nguyenLieu[i]), &(monAnNguon->nguyenLieu[i]));
    }
}

void chuanHoaMonAn(MonAn* monAn, int soMonAn) {
    for (int i = 0; i < soMonAn; i++) {
        // Su dung ky tu khac \0 de mac dinh cac thuoc tinh string cua struct la rat quan trong de strtok lam viec dung
        memset(monAn[i].tenMon, '0', 2);
        monAn[i].tenMon[1] = '\0';

        monAn[i].gia = 0;
        monAn[i].soNguyenLieu = 0;

        chuanHoaKho(monAn[i].nguyenLieu, MAX_NGUYEN_LIEU);
    }
}

int coNhuNhauMonAn(MonAn h1, MonAn h2) {
    // Tra ve 1 neu nhu nhau, 0 neu khac nhau
    if(strcmp(h1.tenMon, h2.tenMon) == 0 && h1.gia == h2.gia && h1.soNguyenLieu == h2.soNguyenLieu) {
        for(int i = 0; i < MAX_NGUYEN_LIEU; i++) {
            if(coNhuNhauNguyenLieu(h1.nguyenLieu[i], h2.nguyenLieu[i]) == 0) {
                return 0;
            }
        }
        return 1;
    } 
    return 0;
}

void themNhieuMonAnVaoFile(MonAn danhSachMonAn[], int soMonAn, char duongDan[]) {
    FILE* fptr = fopen(duongDan, "a");
    if(!fptr) {
        perror("Khong the them mon an vao file");
        return;
    }

    for(int i = 0; i < soMonAn; i++) {
        fprintf(fptr, "%s,%.2f,", danhSachMonAn[i].tenMon, danhSachMonAn[i].gia);
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%s,", danhSachMonAn[i].nguyenLieu[j].tenNguyenLieu);
        }
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%s,", danhSachMonAn[i].nguyenLieu[j].donVi);
        }
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%.2f,", danhSachMonAn[i].nguyenLieu[j].soLuong);
        }
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%.2f,", danhSachMonAn[i].nguyenLieu[j].gia);
        }
        fprintf(fptr, "%d\n", danhSachMonAn[i].soNguyenLieu);
    }

    fclose(fptr);
}

void docFileMenu(char duongDan[], int soMonAnDoc, MonAn* danhSachMonAn) {
    if(soMonAnDoc == 0) {
        return;
    }

    FILE *fptr = fopen(duongDan, "r");
    if (!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong mon an trong menu");
        return;
    }

    chuanHoaMonAn(danhSachMonAn, soMonAnDoc);
    char msg[MAX_ARRAY_LENGTH_MENU];
    fseek(fptr, sizeof(MENU_HEADER), SEEK_SET); // Bo qua header

    for (int i = 0; i < soMonAnDoc; i++) {
        // Chu y thu tu cac phan tu duoc gan phai khop voi thu tu cac truong tuong ung trong header
        if (fgets(msg, MAX_ARRAY_LENGTH_MENU - 1, fptr) == NULL) {
            perror("Xay ra loi khi sao chep tu file menu");
            break;
        }

        msg[MAX_ARRAY_LENGTH_MENU - 1] = '\0'; // Dam bao msg duoc null terminate
        msg[strcspn(msg, "\n")] = '\0'; // Loai bo newline mac dinh;

        char* tenMonAn = strtok(msg, NGAN_PHAN_TU_CSV);
        if(tenMonAn) {
            strncpy(danhSachMonAn[i].tenMon, tenMonAn, DO_DAI_TEN_MON - 1);
            danhSachMonAn[i].tenMon[DO_DAI_TEN_MON - 1] = '\0';
        }

        char* giaMon = strtok(NULL, NGAN_PHAN_TU_CSV);
        if(giaMon) {
            danhSachMonAn[i].gia = atof(giaMon);
        }

        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            char *tenNguyenLieu = strtok(NULL, NGAN_PHAN_TU_CSV);
            if (tenNguyenLieu) {
                strncpy(danhSachMonAn[i].nguyenLieu[j].tenNguyenLieu, tenNguyenLieu, MAX_DO_DAI_TEN_NGUYEN_LIEU - 1);
                danhSachMonAn[i].nguyenLieu[j].tenNguyenLieu[MAX_DO_DAI_TEN_NGUYEN_LIEU - 1] = '\0';
            }
        }

        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            char *donVi = strtok(NULL, NGAN_PHAN_TU_CSV);
            if (donVi) {
                strncpy(danhSachMonAn[i].nguyenLieu[j].donVi, donVi, MAX_DO_DAI_CHUOI_DON_VI - 1);
                danhSachMonAn[i].nguyenLieu[j].donVi[MAX_DO_DAI_CHUOI_DON_VI - 1] = '\0';
            }
        }

        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            char* soLuong = strtok(NULL, NGAN_PHAN_TU_CSV);
            if (soLuong) {
                danhSachMonAn[i].nguyenLieu[j].soLuong = atof(soLuong);
            }
        }

        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            char* giaNguyenLieu = strtok(NULL, NGAN_PHAN_TU_CSV);
            if(giaNguyenLieu) {
                danhSachMonAn[i].nguyenLieu[j].gia = atof(giaNguyenLieu);
            }
        }

        char* soNguyenLieu = strtok(NULL, NGAN_PHAN_TU_CSV);
        if(soNguyenLieu) {
            danhSachMonAn[i].soNguyenLieu = atoi(soNguyenLieu);
        }
    }

    fclose(fptr);
}

void themMonAnVaoFile(char duongDan[], MonAn* monAn) {
    int soMonFile = kiemTraSoMonAn(duongDan);
    if(soMonFile >= MAX_MON) {
        printf("File da day\n");
        return;
    }

    MonAn* menuFile = (MonAn*) malloc(sizeof(MonAn) * soMonFile);
    if(!menuFile) {
        printf("Khong the khoi tao mang dong mon an\n");
        return;
    }

    docFileMenu(duongDan, soMonFile, menuFile);
    for(int i = 0; i < soMonFile; i++) {
        if(strcmp(monAn->tenMon, menuFile[i].tenMon) == 0) { //SSM
            printf("Mon an da co trong file\n");
            free(menuFile);
            return;
        }
    }
    free(menuFile);

    FILE* fptr = fopen(duongDan, "a"); // mode "a": them thong tin vao cuoi file
    if(!fptr) {
        perror("Khong the them nguyen lieu vao file");
        return;
    }
    fprintf(fptr, "%s,%.2f,", monAn->tenMon, monAn->gia);
    for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
        fprintf(fptr, "%s,", monAn->nguyenLieu[j].tenNguyenLieu);
    }
    for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
        fprintf(fptr, "%s,", monAn->nguyenLieu[j].donVi);
    }
    for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
        fprintf(fptr, "%.2f,", monAn->nguyenLieu[j].soLuong);
    }
    for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
        fprintf(fptr, "%.2f,", monAn->nguyenLieu[j].gia);
    }
    fprintf(fptr, "%d\n", monAn->soNguyenLieu);
    fclose(fptr);

    printf("Mon an da duoc them\n");
}

void xoaMonAnKhoiFile(char duongDan[], MonAn* monXoa) {
    int soMonFile = kiemTraSoMonAn(duongDan);
    if(soMonFile == 0) {
        printf("File menu trong\n");
        return;
    }

    MonAn* menuFile = (MonAn*) malloc(sizeof(MonAn) * soMonFile);
    docFileMenu(duongDan, soMonFile, menuFile);

    int coTrongFile = 0;
    for(int i = 0; i < soMonFile; i++) {
        if(strcmp(menuFile[i].tenMon, monXoa->tenMon) == 0) { //SSM
            for(int j = i; j < soMonFile - 1; j++) {
                menuFile[j] = menuFile[j + 1];
            }
            soMonFile--;
            coTrongFile = 1;
            break;
        }
    }
    if(coTrongFile == 0) {
        printf("Khong ton tai mon an voi ten '%s' trong file\n", monXoa->tenMon);
    }

    FILE* fptr = fopen(duongDan, "w");
    if(!fptr) {
        perror("Khong the mo file kho de xoa mon an");
        return;
    }

    fprintf(fptr, MENU_HEADER);    
    for(int i = 0; i < soMonFile; i++) {
        fprintf(fptr, "%s,%.2f,", menuFile[i].tenMon, menuFile[i].gia);
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%s,", menuFile[i].nguyenLieu[j].tenNguyenLieu);
        }
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%s,", menuFile[i].nguyenLieu[j].donVi);
        }
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%.2f,", menuFile[i].nguyenLieu[j].soLuong);
        }
        for(int j = 0; j < MAX_NGUYEN_LIEU; j++) {
            fprintf(fptr, "%.2f,", menuFile[i].nguyenLieu[j].gia);
        }
        fprintf(fptr, "%d\n", menuFile[i].soNguyenLieu);
    }

    printf("Mon an da duoc xoa\n");
    fclose(fptr);
    free(menuFile);
}

void hienThiMenu(MonAn menu[], int soMon) {
    printf("\nDanh sach mon an:\n");

    printf("%-5s %-20s %-5s\n", "STT", "Ten mon", "Gia");

    for (int i = 0; i < soMon; i++) {
        printf("%-5d %-20s %-7.2f\n", i + 1, menu[i].tenMon, menu[i].gia);
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

void xoaMonAnTrongMang(MonAn menu[], int* soMonAn, MonAn* monXoa) {
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
    printf("Cap nhat thanh cong\n");
}
