from PIL import Image  
import math  
  
def png_to_sgl_icon_4bpp(png_path, out_name="my_icon"):  
    img = Image.open(png_path).convert("L")  # 转为灰度图  
    w, h = img.size  

    # img = img.rotate(30)

    pixels = list(img.getdata())  
  
    bytes_per_row = math.ceil(w / 2)  
    data = []  
  
    for row in range(h):  
        for col in range(0, w, 2):  
            hi = pixels[row * w + col] >> 4          # 偶数列，高4位  
            lo = pixels[row * w + col + 1] >> 4 if (col + 1) < w else 0  # 奇数列，低4位  
            data.append((hi << 4) | lo)  
  
    # 输出 C 数组  
    print(f"static const uint8_t {out_name}_pixmap[] = {{")  
    for i, row in enumerate(range(h)):  
        row_bytes = data[row * bytes_per_row:(row + 1) * bytes_per_row]  
        hex_str = ",".join(f"0x{b:02x}" for b in row_bytes)  
        print(f"{hex_str},")  
    print("};")  
    print()  
    print(f"static sgl_icon_pixmap_t {out_name} = {{")  
    print(f"    .bitmap = {out_name}_pixmap,")  
    print(f"    .width  = {w},")  
    print(f"    .height = {h},")  
    print("};")  
  
png_to_sgl_icon_4bpp("fan.png", "icon_fan")