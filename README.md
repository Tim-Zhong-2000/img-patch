# img-patcher
lyb操作系统课程，软盘镜像生成器
## 基本用法
### 编译
gcc img-patcher.cpp -o bootimg-patcher.exe
### 参数列表：
1. 输出镜像(string)
2. 输出镜像大小(int)
3. 是否自动写入有效位(0或1)
4. 插入位置
5. 插入文件
其中4,5可以无限重复
### 基本用例
生成标准软盘镜像，把boot.com插入0字节位置，把A.com插入512字节位置，把B.com插入1024字节位置。
`bootimg-patcher.exe ./out.img 1474560 1 0 ./boot.com 512 ./A.com 1024 ./B.com`

**早日搞文件系统，早日脱离坑爹的手写软盘。**
