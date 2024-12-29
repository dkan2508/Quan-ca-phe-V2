# Quan-ca-phe-V2
-	Kiem tra lai ve logic cua chuong trinh ve van de xu ly file:
Mối liên hệ giữa dữ liệu trong mang va du lieu trong file:

o	Dữ liệu trong mảng là dữ liệu mới hơn so với trong file. Khi cần đọc dữ liệu từ mảng và file, ưu tiên lấy nguyên liệu từ mảng trước. Nếu có trong mảng, lấy thông tin đó và dừng. Nếu không có trong mảng mới tìm tới trong file. Nếu không có trong cả hai thì dùng giá trị mặc định.
 - Chú ý: khi update từ file ra mảng, dữ liệu trong file được ưu tiên hơn. Khi update từ mảng ra file, dữ liệu trong mảng được ưu tiên hơn.
o	Việc thêm một phần tử vào mảng/file phải tuân theo những quy tắc sau:
 - Dữ liệu nơi nhận (ưu tiên thấp hơn) sẽ không bị xóa bỏ, chỉ có thể được update (khi trùng một số dữ liệu) hoặc để nguyên.
 - Viec update chi xay ra voi cac ham cap nhat. Voi cac ham them, obj lap se khong duoc cho vao.
 - Một số dữ liệu ở nơi ưu tiên thấp hơn sẽ được update dữ liệu của nơi ưu tiên cao hơn theo nguyên tắc:
•	Dữ liệu khách hàng được update diemTichLuy nếu trùng  tên và số điện thoại.
•	Món ăn và nguyên liệu được update các trường khác tên nếu trùng tên.
•	Hóa đơn sẽ không có update.
 - Nếu một đối tượng bị trùng dữ liệu toàn bộ với dữ liệu mới, dữ liệu mới sẽ bị bỏ qua.
 - Về giới hạn phần tử:
•	Đương nhiên, dữ liệu từ file vào mảng sẽ không thể vượt quá giới hạn phần tử mảng đó.
•	File lưu món ăn và nguyên liệu bị giới hạn số lượng tương tự với các mảng tương ứng. File lưu hóa đơn và khách hàng thì không.
o	Khi tạo một đối tượng cần chuẩn hóa nó (để tránh giá trị rác), trừ khi sử dụng đối tượng đó cho các hàm đọc file, nhập thông tin. Các hàm thêm, nhập xuất thông tin chú ý chuẩn hóa đối tượng.
o	Điểm cho khách hàng được tính từ tổng số tiền sau khi được giảm giá.
o	Thống kê chỉ thống kê cho dữ liệu từ file.
