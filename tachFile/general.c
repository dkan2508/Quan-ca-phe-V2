#include "general.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int coNhuNhauNgay(Ngay n1, Ngay n2) {
    if(n1.ngay == n2.ngay && n1.thang == n2.thang && n1.nam == n2.nam) {
        return 1;
    }
    return 0;
}

void saoChepNgay(Ngay* ngayNhan, Ngay* ngayNguon) {
    ngayNhan->ngay = ngayNguon->ngay;
    ngayNhan->thang = ngayNguon->thang;
    ngayNhan->nam = ngayNguon->nam;
}

void docFileQuanLi(int luaChon, char duongDan[]) {
    // 1: file khach hang
    // 2: file hoa don
    // 3: file kho
    // 4: file menu
    if(luaChon < 1 || luaChon > 4) {
        printf("Lua chon mo file quan li khong hop le!\n");
        return;
    }
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
        printf("File da duoc reset\n");
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
        docFile(duongDan, soLuongFile, mangFile);

        timKiem(mangFile, soLuongFile);

        free(mangFile);
    }
}
