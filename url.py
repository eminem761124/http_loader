import sys
def main(url):
    # 按字符拆分
    parts = [f'"{c}"' for c in url]

    # 拼接成 C 数组格式
    output = "const char* parts[] = {\n    "
    output += ", ".join(parts)
    output += "\n};"

    # 保存到 result.txt
    with open("result.txt", "w", encoding="utf-8") as f:
        f.write(output)

    print("处理完成，已保存到 result.txt")

if __name__ == '__main__':
    argv = sys.argv
    if len(argv) < 2:
        print("用法: python url.py <url>")
        print("将输入的 URL 按字符拆分并保存为 C 数组格式到 result.txt")
        exit(1)
    elif argv[1] == "-h" or argv[1] == "--help":
        print("用法: python url.py <url>")
        print("将输入的 URL 按字符拆分并保存为 C 数组格式到 result.txt")
        exit(0)
    else:
        main(argv[1])