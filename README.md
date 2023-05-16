Trần Thanh Thảo - 22021157 
I. Giới thiệu về Sweet Home:
1. Game lấy ý tưởng từ game Candy Crush Saga
2. Code bằng ngôn ngữ C ++ và SDL2.0

II. Hướng dẫn cách chơi game :

+ Mỗi màn đã cho trước số điểm cần đạt và số lượt di chuyển.
+ Nếu đạt được số điểm cho trước trong số lượt quy định thì THẮNG , ngược lại thì THUA.

+ Đổi chỗ 2 nhân vật cạnh nhau để tạo tối thiểu 3 nhân vật liền kề theo hàng hoặc cột giống nhau.
+ Mỗi ô đã ăn được tính 100 điểm. 
+ Khi ăn được chuỗi >= 5 thì tất cả các nhân vật đó trên bàn đều được ăn.
Lưu ý : nếu không hiểu thì khi vào game có thể ấn nút setting ở góc bên dưới phía bên trái màn hình.
+ Chọn mục how to play có hướng dẫn cách chơi chi tiết.
+ muốn thoát ra thì chỉ cần ấn dấu X là được.

III.Hướng dẫn cách tải và chơi game :
1.  Cài git
2. Clone repo về máy
3. Chạy file main.exe

IV: Cấu trúc Sweet Home:

+ Folder audio: lưu trữ các file âm thanh cần thiết cho game.
+ Folder font: lưu trữ file font chữ cho game.
+ Folder image: lưu trữ các hình ảnh cần thiết cho game.
+ Folder include: lưu trữ các thư viện của SDL2.0
+ File game.cpp: dùng để khởi tạo game, các chức năng cho menu, chức năng cho select level , hàm kết quả trả về khi người chơi chơi game xong
+ File Tile.cpp: dùng để khởi tạo trạng thái cho các nhân vật ( có 8 trạng thái: empty, selected, 6 trạng thái của 6 candy và 6 nhân vật candy) và hàm swap ( swap trạng thái của các candy).
+ File utils.cpp: dùng để khởi tạo cửa sổ game và hàm báo lỗi
+ File SDL_image_functions: dùng để load ảnh ra screen
+ File main.cpp:
+ File GameBoard.cpp: check các bước đi của người chơi ( xử lý game trong quá trình người chơi di chuyển trong game)

