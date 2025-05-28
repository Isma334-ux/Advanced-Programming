import os
import pandas as pd
import matplotlib.pyplot as plt

# Route to the results
RESULTS_DIR = "results/"

def load_results(algorithm_prefix):
    """
    Carga los CSV de resultados de un algoritmo (ecc o chacha) y
    devuelve un DataFrame con columnas agregadas de tamaño y promedio.
    """
    data = []
    for filename in os.listdir(RESULTS_DIR):
        if filename.startswith(algorithm_prefix) and filename.endswith(".csv"):
            filepath = os.path.join(RESULTS_DIR, filename)
            size = int(filename.split("_")[-1].replace("B.csv", ""))
            df = pd.read_csv(filepath)
            avg_enc = df["Encryption Time (μs)"].mean()
            avg_dec = df["Decryption Time (μs)"].mean()
            avg_ovh = df["Overhead (B)"].mean()
            data.append({
                "Message Size (B)": size,
                "Encryption Time (μs)": avg_enc,
                "Decryption Time (μs)": avg_dec,
                "Overhead (B)": avg_ovh
            })
    return pd.DataFrame(data).sort_values("Message Size (B)")

def plot_comparison(ecc_df, chacha_df, metric, ylabel, title, filename):
    plt.figure(figsize=(8, 5))
    plt.plot(ecc_df["Message Size (B)"], ecc_df[metric], marker='o', label="ECC")
    plt.plot(chacha_df["Message Size (B)"], chacha_df[metric], marker='s', label="ChaCha20")
    plt.xlabel("Message Size (bytes)")
    plt.ylabel(ylabel)
    plt.title(title)
    plt.xscale("log")  # escala logarítmica para tamaños
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(filename)
    plt.close()
    print(f"[✓] Saved: {filename}")

def main():
    ecc_df = load_results("ecc")
    chacha_df = load_results("chacha")

    print("[+] Datos ECC:\n", ecc_df, "\n")
    print("[+] Datos ChaCha20:\n", chacha_df, "\n")

    plot_comparison(ecc_df, chacha_df,
                    metric="Encryption Time (μs)",
                    ylabel="Encryption Time (μs)",
                    title="Encryption Time vs Message Size",
                    filename="results/encryption_time_comparison.png")

    plot_comparison(ecc_df, chacha_df,
                    metric="Decryption Time (μs)",
                    ylabel="Decryption Time (μs)",
                    title="Decryption Time vs Message Size",
                    filename="results/decryption_time_comparison.png")

    plot_comparison(ecc_df, chacha_df,
                    metric="Overhead (B)",
                    ylabel="Overhead (bytes)",
                    title="Overhead vs Message Size",
                    filename="results/overhead_comparison.png")

if __name__ == "__main__":
    main()
