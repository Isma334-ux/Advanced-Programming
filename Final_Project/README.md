# ECC vs ChaCha20-Poly1305 Simulation for IoT Devices

This project simulates and compares the performance of two cryptographic algorithms with the intention to be applied in IoT devices: **ECC (Elliptic Curve Cryptography)** and **ChaCha20-Poly1305**, using the [Libsodium](https://libsodium.gitbook.io/doc/) library. The simulation measures encryption and decryption times, as well as the overhead for different message sizes.

> 📌 Developed and tested in a Linux environment (Ubuntu).

## 📁 Project Structure
```
ecc_project/
├── bin/ # Compiled binaries
├── env/ # Python virtual environment for plotting
├── include/ # Header files (.h)
├── src/ # Source files (.cpp)
├── results/ # CSV files and performance plots
├── analyze_results.py # Python script for plotting
├── Makefile # Makefile for building the project

```

## ⚙️ Requirements
### Operative System
- Ubuntu 20.04+ (or compatible Linux)
- If you are a windows user, you can use WSL to run ubuntu as a subsystem

### C++ (for simulation)
- [Libsodium](https://libsodium.gitbook.io/doc/installation)
- g++9.0+
- make

### Python (for plotting)
- Python 3.8+
- `matplotlib`
- `pandas`


### Setup
1. Install libsodium
```
sudo apt-get install libsodium-dev
```
2. Create the environment
```
python3 -m venv env
source env/bin/activate
pip install matplotlib pandas
```

## Running simulations
You can run the code using ```make```. This will:
- Compile all source files from the ```src/``` directory.
- Generate object files and the final executable.


After compilation

**To execute the ```ecc encryption``` just write :**
```
./ecc_simulation
```

**To execute the ```ChaCha20-Poly1305``` just write :**
```
./chacha_simulation
```
  
**To clean up compiled files, use:**
```
make clean
```

**To clean up all the ```.csv``` files, use:**
```
make dist-clean
```

## Run the analysis
After activate the enviroment using ```source env/bin/activate``` you need to use
```
python analyze_results.py
```
Then in ```results/``` 3 graphics will be created, showing:

- ⏱ Encryption Time (μs)

- ⏱ Decryption Time (μs)

- 🧱 Overhead (bytes): Difference between ciphertext and plaintext size


## Descriptions of the algorithms

### 🔐 ChaCha20-Poly1305
Libsodium provides authenticated encryption using the ChaCha20-Poly1305 construction, combining the fast ChaCha20 stream cipher (256-bit key) with the Poly1305 MAC for integrity. It offers:

- Secure encryption with a 12-byte nonce and 32-byte key.

- Built-in authentication (128-bit tag) to prevent tampering.

- Additional Data (AAD) support for authenticated metadata.

- Resistance to timing attacks, making it ideal for high-speed encryption (e.g., TLS, VPNs).

### 🔗 ECC (Curve25519 & Ed25519)
Libsodium uses elliptic-curve cryptography (ECC) for key exchange and signatures:

- X25519: For ECDH key exchange, enabling secure shared secrets with 32-byte keys.

- Ed25519: For fast, deterministic digital signatures (64-byte signatures).

- Post-quantum secure: Based on strong elliptic curves (SafeCurves compliant).

- Used in Signal, WireGuard, and SSH for forward secrecy and lightweight operations.
