# ECC vs ChaCha20 Simulation for IoT Devices

This project simulates and compares the performance of two cryptographic algorithms in the context of IoT devices: **ECC (Elliptic Curve Cryptography)** and **ChaCha20-Poly1305**, using the [Libsodium](https://libsodium.gitbook.io/doc/) library. The simulation measures encryption and decryption times, as well as the overhead for different message sizes.

> 📌 Developed and tested in a Linux environment (Ubuntu).

## 📁 Project Structure

ecc_project/
├── bin/ # Compiled binaries
├── env/ # Python virtual environment for plotting
├── include/ # Header files (.h)
├── src/ # Source files (.cpp)
├── results/ # CSV files and performance plots
├── analyze_results.py # Python script for plotting
├── Makefile # Makefile for building the project

markdown
Copy
Edit

## ⚙️ Requirements

### C++ (for simulation)
- [Libsodium](https://libsodium.gitbook.io/doc/installation)
- g++
- make

### Python (for plotting)
- Python 3.8+
- `matplotlib`
- `pandas`

To set up the Python environment:

```bash
cd ecc_project
python3 -m venv env
source env/bin/activate
pip install -r requirements.txt
Contents of requirements.txt:

nginx
Copy
Edit
matplotlib
pandas
🔨 Building the Project
Compile using make:

bash
Copy
Edit
make
This generates two binaries in bin/:

ecc.app — ECC simulation

chacha.app — ChaCha20 simulation

🚀 Running the Simulations
Each simulation runs across multiple message sizes and performs 1000 iterations per size. Results are stored in CSV format.

bash
Copy
Edit
./bin/ecc.app       # Run ECC simulation
./bin/chacha.app    # Run ChaCha20 simulation
CSV outputs are saved in the results/ folder.

📊 Visualizing Results
To generate performance plots:

bash
Copy
Edit
source env/bin/activate
python analyze_results.py
This creates the following plots in results/:

encryption_time_comparison.png

decryption_time_comparison.png

overhead_comparison.png

📈 Metrics Collected
For each message size:

⏱ Encryption Time (μs)

⏱ Decryption Time (μs)

🧱 Overhead (bytes): Difference between ciphertext and plaintext size

🔐 Cryptographic Details
ChaCha20-Poly1305: A fast, modern, and secure AEAD symmetric cipher, suitable for constrained devices and software-only environments.

ECC (via crypto_box): Asymmetric encryption using public/private key pairs.

All cryptographic operations use Libsodium for high security and performance.

📚 Credits
Developed for a performance simulation project comparing cryptographic algorithms in resource-constrained environments.

Cryptographic library: Libsodium

yaml
Copy
Edit

---
