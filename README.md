# c-crypt-project

一个用 C 实现的简单命令行 XOR 加解密工具，使用 `CMake` 管理构建。包含用于本地构建和使用 `Android NDK` 构建的脚本。

快速本地构建：

```bash
./scripts/build-native.sh
./build-native/c-crypt -k mykey -i plain.bin -o cipher.bin
```

为 Android 构建（需要 Android NDK，设置 `ANDROID_NDK_HOME` 或 `ANDROID_NDK_ROOT`）：

```bash
export ANDROID_NDK_HOME=/path/to/android-ndk
./scripts/build-android.sh
# 输出在 build-android/ 目录
```

使用说明：

```
c-crypt -k key [-e|-d] [-i infile] [-o outfile]

-k key     : xor 密钥（必填）
-e         : 加密（默认行为）
-d         : 解密（对 XOR 来说与加密相同）
-i infile  : 输入文件（默认 stdin）
-o outfile : 输出文件（默认 stdout）
```

说明：
- 本工具实现的是简单的 XOR cipher（异或），属于演示用途，不应在对安全性有严格要求的场景下使用。
