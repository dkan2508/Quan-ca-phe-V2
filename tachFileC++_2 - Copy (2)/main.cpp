#include<iostream>
#include "general.hpp"
#include "customer.hpp"
#include "kho.hpp"
#include "menu.hpp"
#include "bill.hpp"
#include <sstream>
#include <iomanip>
#include <cstdio>
using namespace std;

vector<MonAn> menuMacDinh = {
    MonAn("Ca phe den", 25.0, {
        NguyenLieu("Ca phe bot", "kg", 0.05, 12.00),
        NguyenLieu("Duong", "kg", 0.01, 13.00)
    }),

    MonAn("Ca phe sua", 30.0, {
        NguyenLieu("Ca phe bot", "kg", 0.05, 12.00),
        NguyenLieu("Sua dac", "hop", 0.01, 15.00)
    }),

    MonAn("Tra sua", 35.0, {
        NguyenLieu("Tra den", "kg", 0.01, 10.00),
        NguyenLieu("Sua tuoi", "lit", 0.01, 20.00)
    }),

    MonAn("Ca phe da xay", 40.0, {
        NguyenLieu("Ca phe bot", "kg", 0.05, 12.00),
        NguyenLieu("Da vien", "kg", 0.1, 5.00)
    }),

    MonAn("Nuoc cam", 20.0, {
        NguyenLieu("Cam tuoi", "kg", 0.25, 25.00)
    }),

    MonAn("Sinh to dua hau", 35.0, {
        NguyenLieu("Dua hau", "kg", 0.3, 10.00),
        NguyenLieu("Sua dac", "hop", 0.02, 15.00)
    }),

    MonAn("Banh mi op la", 50.0, {
        NguyenLieu("Bot banh mi", "kg", 0.15, 20.00),
        NguyenLieu("Trung ga", "qua", 1, 5.00)
    }),

    MonAn("Banh mi que", 20.0, {
        NguyenLieu("Bot banh mi", "kg", 0.1, 20.00),
        NguyenLieu("Pate gan", "hop", 0.02, 30.00)
    }),

    MonAn("Banh bao nhan thit", 25.0, {
        NguyenLieu("Bot banh bao", "kg", 0.2, 18.00),
        NguyenLieu("Thit heo xay", "kg", 0.1, 50.00)
    }),

    MonAn("Nuoc ep tao", 30.0, {
        NguyenLieu("Tao tuoi", "kg", 0.3, 15.00),
        NguyenLieu("Duong", "kg", 0.01, 13.00)
    })
};

vector<NguyenLieu> khoNguyenLieuMacDinh = {
    NguyenLieu("Ca phe bot", "kg", 200.0, 10.0),
    NguyenLieu("Sua dac", "hop", 15.0, 20.0),
    NguyenLieu("Sua tuoi", "lit", 12.0, 15.0),
    NguyenLieu("Duong", "kg", 10.0, 8.0),
    NguyenLieu("Tra den", "kg", 150.0, 5.0),
    NguyenLieu("Tran chau", "kg", 50.0, 7.0),
    NguyenLieu("Da vien", "kg", 5.0, 50.0),
    NguyenLieu("Cam tuoi", "kg", 25.0, 12.0),
    NguyenLieu("Dua hau", "kg", 10.0, 20.0),
    NguyenLieu("Bot banh mi", "kg", 18.0, 25.0),
    NguyenLieu("Thit heo xay", "kg", 120.0, 10.0),
    NguyenLieu("Bot banh bao", "kg", 22.0, 15.0),
    NguyenLieu("Trung ga", "qua", 3.0, 30.0),
    NguyenLieu("Bo", "kg", 80.0, 5.0),
    NguyenLieu("Pate gan", "hop", 20.0, 10.0),
    NguyenLieu("Tao tuoi", "kg", 30.0, 18.0),
    NguyenLieu("Tuong ot", "chai", 10.0, 12.0),
    NguyenLieu("Dau an", "lit", 25.0, 10.0),
    NguyenLieu("Hanh tay", "kg", 12.0, 8.0),
    NguyenLieu("Mayonnaise", "chai", 15.0, 10.0)
};

QuanLiMenu quanLiMenu(MAX_MON, MAX_MON, LUA_CHON_MENU, MENU_HEADER);
QuanLiKhachHang quanLiKhach(MAX_KHACH_HANG, KHONG_GIOI_HAN, LUA_CHON_KHACH_HANG, KHACH_HANG_HEADER);
QuanLiNguyenLieu quanLiNguyenLieu(MAX_NGUYEN_LIEU, MAX_NGUYEN_LIEU, LUA_CHON_KHO, KHO_HEADER);
QuanLiHoaDon quanLiHoaDon(MAX_MON, KHONG_GIOI_HAN, LUA_CHON_HOA_DON, HOA_DON_HEADER);

int main() {
    ifstream ifstr(MANAGING_FILE, ios::in);
    if(ifstr.is_open()) { // Tep ton tai
        ifstr.close(); // ham docFileQuanLi() se tu mo file nen phai dong file da mo o tren truoc
    } else { // Tep khong ton tai
        cout << "Chu y, ban can cai dat duong dan den file quan li khach hang va hoa don!\n";
        ofstream ofstr(MANAGING_FILE, ios::out);
        if (!ofstr.is_open()) {
            cout << "Khon the tao file luu tru duong dan";
        } else {
            for(int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
                ofstr << PLACEHOLDER_QUAN_LY;
            }
            ofstr.close();
        }
    }

    // Khoi tao mang quan li menu va kho
    // Menu:
    quanLiMenu.setDanhSachMang(menuMacDinh);
    int soMonFileMenu = quanLiMenu.soLuongFile();
    if(soMonFileMenu != -1 && soMonFileMenu != 0) {
        quanLiNguyenLieu.setDanhSachMang(quanLiNguyenLieu.layDanhSachFile(docFileQuanLi(LUA_CHON_MENU)));
    }

    // Kho:
    quanLiNguyenLieu.setDanhSachMang(khoNguyenLieuMacDinh);
    int soMonFileKho = quanLiNguyenLieu.soLuongFile();
    if(soMonFileKho != -1 && soMonFileKho != 0) {
        quanLiNguyenLieu.setDanhSachMang(quanLiNguyenLieu.layDanhSachFile(docFileQuanLi(LUA_CHON_KHO)));
    }

    int luaChon = -1, luaChonCon = -1, luaChonCon2 = -1;
    do {
        cout << "\n--- MENU QUAN CA PHE ---\n";
        cout << "1. Menu\n";
        cout << "2. Thanh toan\n";
        cout << "3. Hoa don\n";
        cout << "4. Khach hang\n";
        cout << "5. Kho\n";
        cout << "6. Thong ke\n";
        cout << "7. Xu li file\n";
        cout << "8. Thoat\n";
        cout << "Nhap lua chon: ";
        saferScanf("%d", &luaChon);

        switch (luaChon) {
            case 1:
                do {
                    cout << "\n--- MENU ---\n";
                    cout << "1. Hien thi menu\n";
                    cout << "2. Them mon\n";
                    cout << "3. Xoa mon\n";
                    cout << "4. Cap nhat menu\n";
                    cout << "5. Xoa du lieu menu\n";
                    cout << "6. Quay lai\n";
                    cout << "Nhap lua chon: ";
                    saferScanf("%d", &luaChonCon);
                    
                    switch (luaChonCon) {
                        case 1: {
                            xemDanhSach(quanLiMenu);
                            break;
                        }
                        case 2: {
                            themPhanTu(quanLiMenu);
                            break;
                        }
                        case 3: {
                            xoaPhanTu(quanLiMenu);
                            break;
                        }
                        case 4: {
                            capNhatDuLieu(quanLiMenu);
                            break;
                        }
                        case 5: {
                            reset(quanLiMenu);
                            break;
                        }
                        case 6: {
                            break;
                        }
                        default: {
                            cout << "Lua chon khong hop le\n";
                            break;
                        }
                    }
                } while (luaChonCon != 6);
                break;
            case 2:
                thanhToan(quanLiMenu, quanLiNguyenLieu, quanLiKhach, quanLiHoaDon);
                break;
            case 3:
                do {
                    cout << "\n--- HOA DON ---\n";
                    cout << "1. Xem danh sach hoa don\n";
                    cout << "2. Tim kiem hoa don\n";
                    cout << "3. Them hoa don vao file\n";
                    cout << "4. Xoa hoa don\n";
                    cout << "5. Cap nhat file hoa don\n";
                    cout << "6. Xoa du lieu hoa don\n";
                    cout << "7. Quay lai\n";
                    cout << "Nhap lua chon: ";
                    saferScanf("%d", &luaChonCon);

                    switch (luaChonCon) {
                        case 1:
                            xemDanhSach(quanLiHoaDon);
                            break;
                        case 2:
                            timKiemDuLieu(quanLiHoaDon);
                            break;
                        case 3:
                            themPhanTu(quanLiHoaDon);
                            break;
                        case 4:
                            xoaPhanTu(quanLiHoaDon);
                            break;
                        case 5:
                            capNhatDuLieu(quanLiHoaDon);
                            break;
                        case 6:
                            reset(quanLiHoaDon);
                            break;
                        case 7:
                            break;
                        default:
                            cout << "Lua chon khong hop le. Vui long chon lai.\n";
                    }
                } while (luaChonCon != 7);
                break;
            case 4:
                do {
                    cout << "\n--- KHACH HANG ---\n";
                    cout << "1. Xem danh sach khach hang\n";
                    cout << "2. Tim kiem khach hang\n";
                    cout << "3. Them khach hang\n"; // Them thu cong mot khach hang
                    cout << "4. Xoa khach hang\n";  // Xoa thu cong mot khach hang
                    cout << "5. Cap nhat du lieu khach hang\n";
                    cout << "6. Xoa du lieu khach hang\n";
                    cout << "7. Quay lai\n";
                    cout << "Nhap lua chon: ";
                    saferScanf("%d", &luaChonCon);
            
                    switch (luaChonCon) {
                        case 1: {
                            xemDanhSach(quanLiKhach);
                            break;
                        }
                        case 2: {
                            timKiemDuLieu(quanLiKhach);
                            break;
                        }
                        case 3: {
                            themPhanTu(quanLiKhach);
                            break;
                        }
                        case 4: {
                            xoaPhanTu(quanLiKhach);
                            break;
                        }
                        case 5: {
                            capNhatDuLieu(quanLiKhach);
                            break;
                        }
                        case 6: {
                            reset(quanLiKhach);
                            break;
                        }
                        case 7:
                            break;
                        default:
                            cout << "Lua chon khong hop le. Vui long chon lai.\n";
                    }
                } while (luaChonCon != 7);
                break;
            case 5:
                do {
                    cout << "\n--- MENU QUAN LY KHO NGUYEN LIEU ---\n";
                    cout << "1. Xem kho nguyen lieu\n";
                    cout << "2. Tim kiem nguyen lieu\n";
                    cout << "3. Them nguyen lieu\n";
                    cout << "4. Xoa nguyen lieu\n";
                    cout << "5. Cap nhat file nguyen lieu\n";
                    cout << "6. Xoa du lieu kho\n";
                    cout << "7. Quay lai\n";
                    cout << "Nhap lua chon: ";
                    saferScanf("%d", &luaChonCon);

                    switch (luaChonCon) {
                        case 1: {
                            xemDanhSach(quanLiNguyenLieu);
                            break;
                        }
                        case 2: {
                            timKiemDuLieu(quanLiNguyenLieu);
                            break;
                        }
                        case 3: {
                            themPhanTu(quanLiNguyenLieu);
                            break;
                        }
                        case 4: {
                            xoaPhanTu(quanLiNguyenLieu);
                            break;
                        }
                        case 5: {
                            capNhatDuLieu(quanLiNguyenLieu);
                            break;
                        }
                        case 6: {
                            reset(quanLiNguyenLieu);
                            break;
                        }
                        case 7:
                            break;
                        default:
                            cout << "Lua chon khong hop le, vui long chon lai\n";
                    }
                } while (luaChonCon != 7);
                break;
            case 6:
                do {
                    cout << "\n--- Thong ke ---\n";
                    cout << "1. Thong ke trong nam\n";
                    cout << "2. Thong ke trong thang\n";
                    cout << "3. Quay lai\n";
                    cout << "Nhap lua chon: ";
                    saferScanf("%d", &luaChonCon);

                    switch (luaChonCon) {
                        case 1: {
                            int namThongKe;
                            cout << "Nhap nam thong ke: ";
                            saferScanf("%d", &namThongKe);

                            if(namThongKe < 0) {
                                cout << "Nam khong the am\n";
                                break;
                            }

                            string duongDan = docFileQuanLi(LUA_CHON_HOA_DON);
                            vector<HoaDon> data = quanLiHoaDon.layDanhSachFile(duongDan);

                            float tongTienQ1 = 0, chiPhiQ1 = 0;
                            float tongTienQ2 = 0, chiPhiQ2 = 0;
                            float tongTienQ3 = 0, chiPhiQ3 = 0;
                            float tongTienQ4 = 0, chiPhiQ4 = 0;
                            int soDonQ1 = 0, soDonQ2 = 0, soDonQ3 = 0, soDonQ4 = 0;
                            int tonTaiNam = 0; // Flag danh dau xem input nam co nam trong file khong

                            for(int i = 0; i < data.size(); i++) {
                                if(data[i].getNgay().getNam() == namThongKe) {
                                    tonTaiNam = 1;
                                    if(data[i].getNgay().getThang() >= 1 && data[i].getNgay().getThang() <= 3) {
                                        tongTienQ1 += data[i].getTongTien() - data[i].getTienThua();
                                        chiPhiQ1 += data[i].getTienNguyenLieu();
                                        soDonQ1++;
                                    } else if(data[i].getNgay().getThang() >= 4 && data[i].getNgay().getThang() <= 6) {
                                        tongTienQ2 += data[i].getTongTien() - data[i].getTienThua();
                                        chiPhiQ2 += data[i].getTienNguyenLieu();
                                        soDonQ2++;
                                    } else if(data[i].getNgay().getThang() >= 7 && data[i].getNgay().getThang() <= 9) {
                                        tongTienQ3 += data[i].getTongTien() - data[i].getTienThua();
                                        chiPhiQ3 += data[i].getTienNguyenLieu();
                                        soDonQ3++;
                                    } else if(data[i].getNgay().getThang() >= 10 && data[i].getNgay().getThang() <= 12) {
                                        tongTienQ4 += data[i].getTongTien() - data[i].getTienThua();
                                        chiPhiQ4 += data[i].getTienNguyenLieu();
                                        soDonQ4++;
                                    }
                                }
                            }

                            if(tonTaiNam == 0) {
                                cout << "Khong ton tai nam %d trong he thong\n", namThongKe;
                                break;
                            }

                            ostringstream oss;
                            oss << "\n--- Nam " << namThongKe << " ---\n";
                            oss << "Quy 1 co " << soDonQ1 << " don hang, tong loi nhuan: " << fixed << setprecision(2) << (tongTienQ1 - chiPhiQ1) << "\n";
                            oss << "Quy 2 co " << soDonQ2 << " don hang, tong loi nhuan: " << (tongTienQ2 - chiPhiQ2) << "\n";
                            oss << "Quy 3 co " << soDonQ3 << " don hang, tong loi nhuan: " << (tongTienQ3 - chiPhiQ3) << "\n";
                            oss << "Quy 4 co " << soDonQ4 << " don hang, tong loi nhuan: " << (tongTienQ4 - chiPhiQ4) << "\n";
                            oss << "Nam " << namThongKe << " co " << (soDonQ1 + soDonQ2 + soDonQ3 + soDonQ4) << " don hang, tong thu nhap: "
                                << (tongTienQ1 - chiPhiQ1 + tongTienQ2 - chiPhiQ2 + tongTienQ3 - chiPhiQ3 + tongTienQ4 - chiPhiQ4) << "\n";

                            cout << oss.str();

                            break;
                        }
                        case 2: {
                            int namThongKe, thangThongKe;
                            cout << "Nhap nam thong ke: ";
                            saferScanf("%d", &namThongKe);
                            cout << "Nhap thang thong ke: ";
                            saferScanf("%d", &thangThongKe);

                            if(namThongKe < 0 || thangThongKe < 0) {
                                cout << "Nam va thang khong the am\n";
                                break;
                            }

                            ostringstream oss;
                            string duongDan = docFileQuanLi(LUA_CHON_HOA_DON);
                            vector<HoaDon> data = quanLiHoaDon.layDanhSachFile(duongDan);
                            int soHoaDonFile = data.size();

                            float tongTienThongKe = 0, tienNguyenLieuThongKe = 0;
                            int soHoaDonThongKe = 0;
                            int tonTaiThoiDiem = 0; // Kiem tra xem file co luu hoa don cua thang, nam do khong

                            for(int i = 0; i < soHoaDonFile; i++) {
                                if(data[i].getNgay().getNam() == namThongKe && data[i].getNgay().getThang() == thangThongKe) {
                                    tonTaiThoiDiem = 1;
                                    tongTienThongKe += data[i].getTongTien() - data[i].getTienThua();
                                    tienNguyenLieuThongKe += data[i].getTienNguyenLieu();
                                    soHoaDonThongKe++;
                                }
                            }

                            if(tonTaiThoiDiem == 0) {
                                cout << "Khong ton tai hoa don thang " << thangThongKe << " nam " << namThongKe << " trong file\n";
                                break;
                            }
                            oss << "\n--- Thong ke thang " << thangThongKe << " nam " << namThongKe << " ---\n";
                            oss << "Tong thu nhap: " << fixed << setprecision(2) << (tongTienThongKe - tienNguyenLieuThongKe) << "\n";
                            oss << "So hoa don: " << soHoaDonThongKe << "\n";
                            break;
                        }
                        case 3:
                            break;
                        default:
                            cout << "Lua chon khong hop le, vui long chon lai\n";
                    }
                } while (luaChonCon != 3);
                break;
            case 7:
                do {
                    cout << "\n--- FILE ---\n";
                    cout << "1. File khach hang\n";
                    cout <<"2. File hoa don\n";
                    cout <<"3. File kho\n";
                    cout <<"4. File menu\n";
                    cout <<"5. Reset file quan li\n";
                    cout <<"6. Quay lai\n";
                    cout << "Nhap lua chon: ";
                    saferScanf("%d", &luaChonCon);

                    if(luaChonCon == 5) {
                        ofstream ofstr(MANAGING_FILE, ios::out);
                        if(ofstr.is_open()) {
                            for(int i = 0; i < SO_DOI_TUONG_LAM_VIEC; i++) {
                                ofstr << PLACEHOLDER_QUAN_LY;
                            }
                            ofstr.close();
                            cout << "Reset file thanh cong\n";
                        } else {
                            thongBaoLoi("Khong the reset file quan ly: ");
                        }
                    } else if(luaChonCon == 1 || luaChonCon == 2 || luaChonCon == 3 || luaChonCon == 4) {
                        do {
                            cout << "\n--- Hanh dong ---\n";
                            cout << "1. Xoa file\n";
                            cout << "2. Tao file\n";
                            cout << "3. Di chuyen file\n";
                            cout << "4. Xem duong dan hien tai\n";
                            cout << "5. Chon file\n";
                            cout << "6. Quay lai\n";
                            cout << "Nhap lua chon: ";
                            saferScanf("%d", &luaChonCon2);
                    
                            switch (luaChonCon2) {
                                case 1: { // Use "{}" for better scoping
                                    // Xoa file
                                    string duongDan = docFileQuanLi(luaChonCon);
                                    int ketQuaXoa = remove(duongDan.c_str());
                                    if(ketQuaXoa != 0) {
                                        perror("Xoa file that bai");
                                        break;
                                    }
                                    printf("File da duoc xoa!\n");

                                    capNhatFileQuanLi(luaChonCon, "");
                                    break;
                                }
                                case 2: {
                                    // Tao file moi
                                    string duongDan;
                                    printf("Nhap duong dan moi: ");
                                    getline(cin, duongDan);

                                    ofstream ofstr(duongDan, ios::out);
                                    if(!ofstr.is_open()) {
                                        thongBaoLoi("Tao file moi that bai: ");
                                        break;
                                    }

                                    // Khoi tao header
                                    switch (luaChonCon) {
                                        case LUA_CHON_KHACH_HANG:
                                            ofstr << KHACH_HANG_HEADER;
                                            break;
                                        case LUA_CHON_HOA_DON:
                                            ofstr << HOA_DON_HEADER;
                                            break;
                                        case LUA_CHON_KHO:
                                            ofstr << KHO_HEADER;
                                            break;
                                        case LUA_CHON_MENU:
                                            ofstr << MENU_HEADER;
                                        default:
                                            break;
                                    }

                                    cout << "File duoc tao thanh cong!\n";
                                    ofstr.close();

                                    // Cap nhat file quan li
                                    capNhatFileQuanLi(luaChonCon, duongDan);
                                    break;
                                }
                                case 3: {
                                    string duongDan;
                                    printf("Nhap dia chi moi: ");
                                    getline(cin, duongDan);

                                    string duongDanCu = docFileQuanLi(luaChonCon);

                                    if(duongDan == duongDanCu) {
                                        cout << "Duong dan moi khong the giong duong dan cu!\n";
                                        break;
                                    }
                                    
                                    // Tao file o dia chi moi
                                    ofstream ofstr(duongDan, ios::out);
                                    if(!ofstr.is_open()) {
                                        thongBaoLoi("Khong the tao file moi: ");
                                    }

                                    // Sao chep du lieu sang file moi
                                    ifstream ifstr(duongDanCu, ios::in);
                                    if(!ifstr.is_open()) {
                                        thongBaoLoi("Khong the tao file moi: ");
                                    }

                                    string line;
                                    while(getline(ifstr, line)) {
                                        ofstr << line << "\n";
                                    }

                                    ofstr.close();
                                    ifstr.close();

                                    // Xoa file du lieu cu
                                    if(remove(duongDanCu.c_str()) != 0) {
                                        thongBaoLoi("File du lieu nguon chua duoc xoa: ");
                                    }

                                    // Cap nhat duong dan moi cua file quan li
                                    capNhatFileQuanLi(luaChonCon, duongDan);
                                    cout << "File da duoc cap nhat thanh cong\n";
                                    break;
                                }
                                case 4: {
                                    cout << "Duong dan hien tai: " << docFileQuanLi(luaChonCon) << "\n";
                                    break;
                                }
                                case 5: {
                                    // Chuong trinh chi co the lam viec voi du lieu cua mot file cho moi loai doi tuong tai mot thoi diem
                                    // Lay duong dan cua mot file du lieu
                                    printf("CANH BAO: HAY DAM BAO FILE DUOC HUONG TOI LA FILE DU LIEU DUNG LOAI VA DUNG CU PHAP!!!!\n");
                                    string duongDanMoi;
                                    cout << "Nhap dia chi moi: ";
                                    getline(cin, duongDanMoi);

                                    // Kiem tra xem dia chi co ton tai khong
                                    ifstream ifstr(duongDanMoi);
                                    if(!ifstr.is_open()) {
                                        cout << "Khong mo duoc file\n";
                                        break;
                                    }

                                    // Cap nhat file quan li
                                    capNhatFileQuanLi(luaChonCon, duongDanMoi);
                                    break;
                                }
                                case 6:
                                    break;
                                default:
                                    cout << "Lua chon khong hop le. Vui long chon lai.\n";
                            }             
                        } while (luaChonCon2 != 6);
                    } else if(luaChonCon != 6) {
                        cout << "Lua chon khong hop le. Vui long chon lai!\n";
                    }
                } while (luaChonCon != 6);
                break;
            case 8:
                cout << "Ket thuc chuong trinh\n";
                break;
            default:
                cout << "Lua chon khong hop le, vui long chon lai\n";
        } 
    } while(luaChon != 8);
}
