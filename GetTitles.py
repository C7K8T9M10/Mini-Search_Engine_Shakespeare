import os 
  # 指定文件夹路径
folder_path = "D:\CSGO\Mini Search Engine\FullShakespeare"
  
  # 新建txt文件用于存储标题
output_file = open("titles.txt", "w")
  
  # 遍历文件夹中的所有txt文件
for file_name in os.listdir(folder_path):
      if file_name.endswith(".txt"):
          # 写入文件标题到新的txt文件中
          output_file.write(file_name + "\n")
  
  # 关闭文件
output_file.close()
