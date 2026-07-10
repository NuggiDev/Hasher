<div align="center">

# ⚡ hasher

**A blazing-fast, multi-algorithm file hashing tool — natively built for ARM64**

![Platform](https://img.shields.io/badge/platform-Windows%20ARM64-blue?style=for-the-badge&logo=windows)
![Language](https://img.shields.io/badge/language-C%2B%2B17-orange?style=for-the-badge&logo=cplusplus)
![OpenSSL](https://img.shields.io/badge/OpenSSL-4.0.1-red?style=for-the-badge&logo=openssl)
![BLAKE3](https://img.shields.io/badge/BLAKE3-1.5.0-green?style=for-the-badge)
![xxHash](https://img.shields.io/badge/xxHash-0.8.1-purple?style=for-the-badge)
![License](https://img.shields.io/badge/license-MIT-yellow?style=for-the-badge)

</div>

---

## 🔥 Features

| Algorithm | Type | Speed | Use Case |
|-----------|------|-------|----------|
| **SHA-1** | Cryptographic | Fast | Legacy compatibility |
| **SHA-256** | Cryptographic | Fast | Security & integrity |
| **SHA-512** | Cryptographic | Fast | High-security hashing |
| **BLAKE3** 🚀 | Cryptographic | **Fastest** | Modern, parallelized hashing |
| **xxHash64** ⚡ | Non-cryptographic | **Insanely fast** | Checksums & deduplication |

---

## 📦 Installation

### Prerequisites

- Windows ARM64 (Snapdragon X / X Elite)
- [CMake 3.15+](https://cmake.org/download/)
- [Visual Studio Build Tools 2026](https://visualstudio.microsoft.com/downloads/)
- [OpenSSL ARM64](https://slproweb.com/products/Win32OpenSSL.html)

### Build from Source

Open the **Visual Studio Developer Command Prompt** for ARM64 and run:

```cmd
git clone https://github.com/YOUR_USERNAME/hasher.git
cd hasher
mkdir build && cd build

:: Fix missing ARM64 library paths (Windows Insider bug workaround)
set "LIB=%LIB%;C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\VC\Tools\MSVC\14.52.36418\lib\arm64"
set "LIB=%LIB%;C:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0\ucrt\arm64"
set "LIB=%LIB%;C:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0\um\arm64"

cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_POLICY_VERSION_MINIMUM=3.5 ..
cmake --build .
```

---

## 🚀 Usage

```cmd
hasher <file>
```

### Example Output

```
SHA1   (Makefile) = 595961303f03f0e297fd9ae72f11d4e6e77125cf
SHA256 (Makefile) = 27b7825b2ab7fb0fe02320f411b4e7d3adce0a2515bca0f98d700168a9f50d60
SHA512 (Makefile) = a7d8f23482cfbdf2875456cebca3dd4c4c6b9f722f219dd60b0ad2d3bb566d20...
BLAKE3 (Makefile) = fc75edaceb374e0cd008d307e59e9d89ea0748386652b02963d36e66bc819c4e
xxHash64 (Makefile) = 416dce8db7edd9c6
```

---

## 🧠 How It Works

```
hasher.exe <file>
     │
     ├── 🔐 OpenSSL  ──► SHA-1, SHA-256, SHA-512
     ├── ⚡ BLAKE3   ──► BLAKE3 (NEON SIMD accelerated on ARM64!)
     └── 💨 xxHash  ──► xxHash64
```

> **NEON Acceleration**: On Snapdragon processors, BLAKE3 automatically uses ARM NEON SIMD intrinsics for maximum throughput — no extra configuration needed!

---

## 📁 Project Structure

```
hasher/
├── src/
│   ├── main.cpp
│   ├── hasher.h / hasher.cpp
│   ├── algorithms/
│   │   ├── sha.cpp
│   │   ├── blake3.cpp
│   │   └── xxhash.cpp
│   └── output/
│       ├── formatter.h
│       └── formatter.cpp
└── CMakeLists.txt
```

---

## 📜 License

MIT — do whatever you want with it.

---

<div align="center">

Built with 💀 pain and 🔥 determination on a **Snapdragon X Elite** laptop

</div>
