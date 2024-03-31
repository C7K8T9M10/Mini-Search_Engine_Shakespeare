from bs4 import BeautifulSoup
import os

source_folder = r'D:\shakespeare'  # 文件夹路径
output_folder = r'D:\WEDV'  # 输出文件夹路径

# 遍历文件夹中的所有文件
for root, dirs, files in os.walk(source_folder):
    for file in files:
        if file == 'full.html':
            file_path = os.path.join(root, file)
            with open(file_path, 'r', encoding='utf-8') as html_file:
                html_content = html_file.read()
                soup = BeautifulSoup(html_content, 'html.parser')
                text_content = soup.get_text()

                # 写入为txt文件
                output_file_path = os.path.join(output_folder, os.path.basename(root) + '.txt')
                with open(output_file_path, 'w', encoding='utf-8') as txt_file:
                    txt_file.write(text_content)

print("HTML文件已转换为TXT文件并重命名完成！")
