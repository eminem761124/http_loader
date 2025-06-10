# http_loader
分离加载—利用http请求下载shellcode
将shellcode放在可以通过http请求访问的位置（oss,云服务器），遇到存储桶的任意文件上传可以结合使用。
将shellcode下载地址用url.py处理并在c代码中进行替换
编译使用gcc即可
gcc.exe yourproject.cpp -o project.exe -lwininet -mwindows
![image](https://github.com/user-attachments/assets/f3e032f3-0365-4fab-a3a9-462e0d8f9ed7)
# 效果
静动态免杀火绒

![image](https://github.com/user-attachments/assets/738aea78-1fbe-4c0a-ba0a-adc51eae29ea)

静动态免杀360，遇到QVM202尝试更换资源即可

![image](https://github.com/user-attachments/assets/6c6ad5e3-9312-41c0-8fdf-26994950722e)

添加三个反沙箱，CPU、内存、出口IP检测

![image](https://github.com/user-attachments/assets/6fa187bb-d474-4ad6-a23a-770fbd7b251d)
![image](https://github.com/user-attachments/assets/9f3c13fc-226a-45ec-a0a1-68eb9fe38d4d)

