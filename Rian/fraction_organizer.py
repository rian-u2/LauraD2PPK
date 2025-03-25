import numpy as np
import sys

# Ler fractions.txt e extrair a diagonal
def read_diagonal(filename):
    data = np.loadtxt(filename)
    return np.diag(data)

# Ler fit_result.txt e extrair os nomes truncados
def read_truncated_names(filename):
    truncated_names = []
    with open(filename, 'r') as file:
        lines = file.readlines()
        for i in range(1, len(lines), 2):  # Pega a cada 2 linhas
            first_column = lines[i].split()[0]  # Pega a primeira coluna
            truncated_name = first_column.split('_')[0]  # Trunca no primeiro '_'
            truncated_names.append(truncated_name)
    return truncated_names

# Escrever arquivo de saída
def write_output(filename, names, diagonal_values):
    with open(filename, 'w') as file:
        for name, value in zip(names, diagonal_values):
            file.write(f"{name} {value}\n")

# Verifica argumentos da linha de comando
if len(sys.argv) != 2:
    print("Uso: python script.py <arquivo_de_saida>")
    sys.exit(1)

out_filename = sys.argv[1]

diagonal_elements = read_diagonal("/data1000/charmosinhos/Rian/Goofit3/GooFit/build/examples/D2PPK/Fit/"+out_filename+"/fractions.txt")
names = read_truncated_names("/data1000/charmosinhos/Rian/Goofit3/GooFit/build/examples/D2PPK/Fit/"+out_filename+"/fit_result.txt")
write_output("/data1000/charmosinhos/Rian/Goofit3/GooFit/build/examples/D2PPK/Fit/"+out_filename+"/diagonal_fractions.txt", names, 100*diagonal_elements)

print(f"Arquivo diagonal_fractions.txt para {out_filename} criado com sucesso!")
