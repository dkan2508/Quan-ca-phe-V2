#include "general.h"
#include "menu.h"
#include "bill.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void chuanHoaHoaDon(HoaDon* hoaDon, int soHoaDon) {
    // Cai dat gia tri mac dinh cho mang tenMonGoi va soLuongMon cho mot vat hoac mot mang hoa don
    // Su dung sau khi tao va dien gia tri thu cong cho mot struct HoaDon (vd, khi thanh toan) de tranh gia tri rac cho cac gia tri cua mang
    for (int i = 0; i < soHoaDon; i++) {
        for(int j = 0; j < MAX_MON; j++) {
            memset(hoaDon[i].tenMonGoi[j], '0', 2); // Su dung ky tu khac \0 de mac dinh cac thuoc tinh string cua struct la rat quan trong de strtok lam viec dung
            hoaDon[i].tenMonGoi[j][1] = '\0';
        }

        memset(hoaDon[i].soLuongMon, 0, sizeof(hoaDon[i].soLuongMon));

        memset(hoaDon[i].giaMonGoi, 0, sizeof(hoaDon[i].giaMonGoi));

        chuanHoaKhachHang(&hoaDon->khachHang, 1);

        hoaDon[i].ngayNhapDon.ngay = 0;
        hoaDon[i].ngayNhapDon.thang = 0;
        hoaDon[i].ngayNhapDon.nam = 0;

        hoaDon[i].soMonGoi = 0;
        hoaDon[i].tienThua = 0;
        hoaDon[i].tongTien = 0;
        hoaDon[i].tienNguyenLieu = 0;
    }
}

void saoChepHoaDon(HoaDon* hoaDonNhan, HoaDon* hoaDonNguon) {
    saoChepKhachHang(&(hoaDonNhan->khachHang), &(hoaDonNguon->khachHang));
    saoChepNgay(&(hoaDonNhan->ngayNhapDon), &(hoaDonNguon->ngayNhapDon));

    for(int i = 0; i < MAX_MON; i++) {
        strncpy(hoaDonNhan->tenMonGoi[i], hoaDonNguon->tenMonGoi[i], DO_DAI_TEN_MON - 1);
        hoaDonNhan->tenMonGoi[i][DO_DAI_TEN_MON - 1] = '\0';
        hoaDonNhan->soLuongMon[i] = hoaDonNguon->soLuongMon[i];
        hoaDonNhan->giaMonGoi[i] = hoaDonNguon->giaMonGoi[i];
    }
    hoaDonNhan->soMonGoi = hoaDonNguon->soMonGoi;
    hoaDonNhan->tongTien = hoaDonNguon->tongTien;
    hoaDonNhan->tienThua = hoaDonNguon->tienThua;
    hoaDonNhan->tienNguyenLieu = hoaDonNguon->tienNguyenLieu;
}

int kiemTraSoHoaDon(char duongDan[]) {
    FILE *fptr = fopen(duongDan, "r");
    if(!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong hoa don");
        return -1;
    }

    int soHoaDon = 0;
    fseek(fptr, sizeof(HOA_DON_HEADER), SEEK_SET); // Bo qua header
    char msg[MAX_ARRAY_LENGTH_HOA_DON];
    while(fgets(msg, MAX_ARRAY_LENGTH_HOA_DON, fptr)) {
        soHoaDon++;
    }

    fclose(fptr);

    return soHoaDon;
}

int coNhuNhauHoaDon(HoaDon h1, HoaDon h2) {
    // Kiem tra xem hai hoa don co cung thuoc tinh khong.
    // Tra ve 1 neu nhu nhau, 0 neu khac nhau
    if(coNhuNhauKhachHang(h1.khachHang, h2.khachHang) && coNhuNhauNgay(h1.ngayNhapDon, h2.ngayNhapDon) && h1.soMonGoi == h2.soMonGoi
                            && h1.tongTien == h2.tongTien && h1.tienThua == h2.tienThua && h1.tienNguyenLieu == h2.tienNguyenLieu) {
        for(int i = 0; i < MAX_MON; i++) {
            if((h1.soLuongMon[i] != h2.soLuongMon[i])
            || (strcmp(h1.tenMonGoi[i], h2.tenMonGoi[i]) != 0)
            || h1.giaMonGoi[i] != h2.giaMonGoi[i]) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

void docFileHoaDon(char duongDan[], int soHoaDon, HoaDon danhSachHoaDon[]) {
    // Do lon cua mang file hoa don can lon hon hoac bang so hoa don doc
    if(soHoaDon == 0) {
        return;
    }

    FILE *fptr = fopen(duongDan, "r");
    if(!fptr) {
        perror("Khong the mo duong dan de kiem tra so luong hoa don");
        return;
    }

    chuanHoaHoaDon(danhSachHoaDon, soHoaDon);
    char msg[MAX_ARRAY_LENGTH_HOA_DON];

    // Bo qua header
    fseek(fptr, sizeof(HOA_DON_HEADER), SEEK_SET);

    for(int i = 0; i < soHoaDon; i++) {
        if (fgets(msg, MAX_ARRAY_LENGTH_HOA_DON - 1, fptr) == NULL) {
            perror("Xay ra loi khi sao chep tu file hoa don");
            break;
        }

        msg[MAX_ARRAY_LENGTH_HOA_DON - 1] = '\0';
        msg[strcspn(msg, "\n")] = '\0'; // Loai bo newline mac dinh

        char *tenKhachHang = strtok(msg, NGAN_PHAN_TU_CSV);
        if (tenKhachHang) {
            strncpy(danhSachHoaDon[i].khachHang.tenKhachHang, tenKhachHang, DO_DAI_TEN_KHACH - 1);
            danhSachHoaDon[i].khachHang.tenKhachHang[DO_DAI_TEN_KHACH - 1] = '\0';
        }

        char *soDienThoai = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (soDienThoai) {
            strncpy(danhSachHoaDon[i].khachHang.soDienThoai, soDienThoai, DO_DAI_SO_DIEN_THOAI - 1);
            danhSachHoaDon[i].khachHang.soDienThoai[DO_DAI_SO_DIEN_THOAI - 1] = '\0';
        }

        char* diemTichLuy = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (diemTichLuy) {
            danhSachHoaDon[i].khachHang.diemTichLuy = atof(diemTichLuy);
        }

        char *ngay = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (ngay) {
            danhSachHoaDon[i].ngayNhapDon.ngay = atoi(ngay);
        }

        char *thang = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (thang) {
            danhSachHoaDon[i].ngayNhapDon.thang = atoi(thang);
        }

        char *nam = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (nam) {
            danhSachHoaDon[i].ngayNhapDon.nam = atoi(nam);
        }

        for(int j = 0; j < MAX_MON; j++) {
            char *soMon = strtok(NULL, NGAN_PHAN_TU_CSV);
            if (soMon) {
                danhSachHoaDon[i].soLuongMon[j] = atoi(soMon);
            }
        }

        for(int j = 0; j < MAX_MON; j++) {
            char *tenMon = strtok(NULL, NGAN_PHAN_TU_CSV);
            if (tenMon) {
                strncpy(danhSachHoaDon[i].tenMonGoi[j], tenMon, DO_DAI_TEN_MON - 1);
                danhSachHoaDon[i].tenMonGoi[j][DO_DAI_TEN_MON - 1] = '\0';
            }
        }

        for(int j = 0; j < MAX_MON; j++) {
            char *giaMon = strtok(NULL, NGAN_PHAN_TU_CSV);
            if (giaMon) {
                danhSachHoaDon[i].giaMonGoi[j] = atof(giaMon);
            }
        }

        char *soMonGoi = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (soMonGoi) {
            danhSachHoaDon[i].soMonGoi = atoi(soMonGoi);
        }

        char *tongTien = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (tongTien) {
            danhSachHoaDon[i].tongTien = atof(tongTien);
        }

        char *tienThua = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (tienThua) {
            danhSachHoaDon[i].tienThua = atof(tienThua);
        }

        char *tienNguyenLieu = strtok(NULL, NGAN_PHAN_TU_CSV);
        if (tienNguyenLieu) {
            danhSachHoaDon[i].tienNguyenLieu = atof(tienNguyenLieu);
        }
    }

    fclose(fptr);
}

void xoaHoaDonKhoiFile(char duongDan[], HoaDon* hoaDonXoa) {
    int soHoaDonFile = kiemTraSoHoaDon(duongDan);
    if(soHoaDonFile == 0) {
        printf("File khong co hoa don\n");
        return;
    }

    HoaDon* danhSachHoaDonFile = (HoaDon*) malloc(sizeof(HoaDon) * soHoaDonFile);
    docFileHoaDon(duongDan, soHoaDonFile, danhSachHoaDonFile);

    for(int i = 0; i < soHoaDonFile; i++) {
        if(coNhuNhauHoaDon(danhSachHoaDonFile[i], *hoaDonXoa) == 1) {
            for(int j = i; j < soHoaDonFile - 1; j++) {
                saoChepHoaDon(&danhSachHoaDonFile[j], &danhSachHoaDonFile[j + 1]);
            }
            soHoaDonFile--;
            break;
        }
    }

    FILE* fptr = fopen(duongDan, "w");
    if(!fptr) {
        perror("Khong the mo file de xoa hoa don");
        return;
    }
        
    fprintf(fptr, HOA_DON_HEADER);
    for(int i = 0; i < soHoaDonFile; i++) {
        fprintf(fptr, "%s,%s,%.2f,%d,%d,%d,", danhSachHoaDonFile[i].khachHang.tenKhachHang, danhSachHoaDonFile[i].khachHang.soDienThoai, danhSachHoaDonFile[i].khachHang.diemTichLuy,
                                     danhSachHoaDonFile[i].ngayNhapDon.ngay, danhSachHoaDonFile[i].ngayNhapDon.thang, danhSachHoaDonFile[i].ngayNhapDon.nam);
        for(int i = 0; i < MAX_MON; i++) {
            fprintf(fptr, "%d,", danhSachHoaDonFile[i].soLuongMon[i]);
        }
        for(int i = 0; i < MAX_MON; i++) {
            fprintf(fptr, "%s,", danhSachHoaDonFile[i].tenMonGoi[i]);
        }
        for(int i = 0; i < MAX_MON; i++) {
            fprintf(fptr, "%.2f,", danhSachHoaDonFile[i].giaMonGoi[i]);
        }
        fprintf(fptr, "%d,%.2f,%.2f,%.2f\n", danhSachHoaDonFile[i].soMonGoi, danhSachHoaDonFile[i].tongTien, danhSachHoaDonFile[i].tienThua, danhSachHoaDonFile[i].tienNguyenLieu);
    }

    printf("Xoa hoa don khoi file thanh cong\n");
    fclose(fptr);
    free(danhSachHoaDonFile);
}

void themHoaDonVaoFile(HoaDon hoaDon, char duongDan[]) { //INT
    // Them mot hoa don vao file
    // Khac voi ham doc tu file, ham nay nhan du lieu co san nen khong can chuan hoa
    int soHoaDonFile = kiemTraSoHoaDon(duongDan);
    HoaDon* danhSachHoaDonFile = (HoaDon*) malloc(sizeof(HoaDon) * soHoaDonFile);
    docFileHoaDon(duongDan, soHoaDonFile, danhSachHoaDonFile);
    if(!danhSachHoaDonFile) {
        perror("Khong the tao mang dong");
        return;
    }

    for(int i = 0; i < soHoaDonFile; i++) {
        if(coNhuNhauHoaDon(hoaDon, danhSachHoaDonFile[i]) == 1) {
            return;
        }
    }
                                
    FILE* fptr = fopen(duongDan, "a"); // mode "a": them thong tin vao cuoi file
    if(!fptr) {
        perror("Khong the them hoa don vao file");
        return;
    }
    fprintf(fptr, "%s,%s,%.2f,%d,%d,%d,", hoaDon.khachHang.tenKhachHang, hoaDon.khachHang.soDienThoai, hoaDon.khachHang.diemTichLuy,
                                     hoaDon.ngayNhapDon.ngay, hoaDon.ngayNhapDon.thang, hoaDon.ngayNhapDon.nam);
    for(int i = 0; i < MAX_MON; i++) {
        fprintf(fptr, "%d,", hoaDon.soLuongMon[i]);
    }
    for(int i = 0; i < MAX_MON; i++) {
        fprintf(fptr, "%s,", hoaDon.tenMonGoi[i]);
    }
    for(int i = 0; i < MAX_MON; i++) {
        fprintf(fptr, "%.2f,", hoaDon.giaMonGoi[i]);
    }
    fprintf(fptr, "%d,%.2f,%.2f,%.2f\n", hoaDon.soMonGoi, hoaDon.tongTien, hoaDon.tienThua, hoaDon.tienNguyenLieu);
    fclose(fptr);
}

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

    int idxMon;
    printf("\nChon mon va so luong mon:\n");
    while (1) {
        hienThiMenu(menu, soMon);

        char tenMonChon[DO_DAI_TEN_MON];
        printf("Nhap ten mon (nhan '0' de dung): ");
        fgets(tenMonChon, DO_DAI_TEN_MON, stdin);
        tenMonChon[strcspn(tenMonChon, "\n")] = '\0';

        if(strcmp(tenMonChon, "0") == 0) {
            break;
        }

        // Kiem tra xem mon co trong menu khong
        int timThay = 0;
        for(int i = 0; i < soMon; i++) {
            if(strcmp(tenMonChon, menu[i].tenMon) == 0) {
                idxMon = i;
                timThay = 1;
                break;
            }
        }
        if(timThay == 0) {
            printf("Khong tim thay mon an\n");
            continue;
        }

        // Kiem tra xem order co the duoc kho hang dap ung khong
        int soMonToiDa = SO_LUONG_TOI_DA_MOI_MON; // So luong mon vua chon toi da co the lam dua vao tinh trang nguyen lieu trong kho
        int chenhLech = 0; // So lan nguyen lieu trong kho voi nguyen lieu yeu cau trong menu
        int chonMonKhac = 0;
        int timThayNguyenLieu = 0;
        for(int i = 0; i < menu[idxMon].soNguyenLieu; i++) {
            timThayNguyenLieu = 0;
            for(int j = 0; j < soNguyenLieuKho; j++) {
                if(strcmp(menu[idxMon].nguyenLieu[i].tenNguyenLieu, kho[j].tenNguyenLieu) == 0) {
                    timThayNguyenLieu = 1;
                    chenhLech = (int) (kho[j].soLuong / menu[idxMon].nguyenLieu[i].soLuong);
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
            printf("Chi co the order %d mon %s. Nhap '0' de order mon khac.\n", soMonToiDa, menu[idxMon].tenMon);
            printf("Nhap so luong cho mon %s: ", menu[idxMon].tenMon);
            saferScanf("%d", &soMonChon);
        } while(soMonChon < 0 || soMonChon > soMonToiDa);
        if(soMonChon == 0) {
            continue;
        }

        // Dam bao lua chon mon nhu nhau se duoc cong don, chu khong phai la tung lua chon rieng le
        int coMat = 0;
        if(hoaDon.soMonGoi == 0) {
            strncpy(hoaDon.tenMonGoi[hoaDon.soMonGoi], menu[idxMon].tenMon, DO_DAI_TEN_MON);
            hoaDon.giaMonGoi[hoaDon.soMonGoi] = menu[idxMon].gia;
            hoaDon.soLuongMon[hoaDon.soMonGoi] = soMonChon;
            hoaDon.soMonGoi++;
        } else {
            for(int i = 0; i < hoaDon.soMonGoi; i++) {
                if(strcmp(hoaDon.tenMonGoi[i], menu[idxMon].tenMon) == 0) {
                    hoaDon.soLuongMon[i] += soMonChon;
                    coMat = 1;
                    break;
                }
            }
            if(coMat == 0) {
                strncpy(hoaDon.tenMonGoi[hoaDon.soMonGoi], menu[idxMon].tenMon, DO_DAI_TEN_MON);
                hoaDon.giaMonGoi[hoaDon.soMonGoi] = menu[idxMon].gia;
                hoaDon.soLuongMon[hoaDon.soMonGoi] = soMonChon;
                hoaDon.soMonGoi++;
            }
        }
        
        hoaDon.tongTien += soMonChon * menu[idxMon].gia;
        for(int i = 0; i < menu[idxMon].soNguyenLieu; i++) {
            layNguyenLieu(kho, soNguyenLieuKho, menu[idxMon].nguyenLieu[i], soMonChon); // Tru di nguyen lieu trong kho
            hoaDon.tienNguyenLieu += menu[idxMon].nguyenLieu[i].gia * soMonChon;
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
    do {
        printf("Nhap so tien khach dua: ");
        saferScanf("%f", &tienKhachDua);
        tienThua = tienKhachDua - hoaDon.tongTien;
    } while (tienThua < 0);
    hoaDon.tienThua = tienThua;
    printf("Tien thua: %.2f\n", tienThua);
    
    int coTrongMang = 0;
    if(*soHoaDon == 0) {
        saoChepHoaDon(&danhSachHoaDon[*soHoaDon], &hoaDon);
        (*soHoaDon)++;
        printf("\nHoa don da duoc luu\n");
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
            if(strcmp(danhSachKhachHang[i].soDienThoai, hoaDon.khachHang.soDienThoai) == 0) {
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

    float tienThanhToan, tienThua;
    do {
        printf("Nhap so tien khach tra: ");
        saferScanf("%f", &tienThanhToan);
        tienThua = tienThanhToan - hoaDon->tongTien;
    } while(tienThua < 0);
    hoaDon->tienThua = tienThua;
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

    printf("Cap nhat thanh cong\n");
}
