import sys
import os
import re

def read_diagonal_fractions(file_path):
    """Lê diagonal_fractions.txt e retorna uma lista de (nome, fraction_goofit)"""
    data = []
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.split()
            if len(parts) >= 2:
                data.append((parts[0], float(parts[1])))
    return data

def read_fit_result(file_path, names):
    """Lê fit_result.txt e extrai os valores de AMP e PHS para cada nome"""
    results = {name: {'Amp_Goofit': None, 'Phs_Goofit': None} for name in names}
    
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.split()
            if len(parts) >= 2:
                key, value = parts[0], parts[1]
                for name in names:
                    if key == f"{name}_AMP":
                        results[name]['Amp_Goofit'] = float(value)
                    elif key == f"{name}_PHS":
                        results[name]['Phs_Goofit'] = float(value)
    
    return results

def read_laura_results(file_path, names):
    """Lê Fit_results_$N_.txt e extrai Fraction, Amp e Phase corretamente."""
    results = {name: {'Fraction_Laura': None, 'Amp_Laura': None, 'Phs_Laura': None} for name in names}

    with open(file_path, 'r') as file:
        lines = file.readlines()

    i = 1
    while i < len(lines):
        line = lines[i].strip()

        # Se encontramos um nome de ressonância, verificamos as 3 próximas linhas
        
        if i + 3 < len(lines):
            amp_line = lines[i + 1].strip()
            phase_line = lines[i + 2].strip()
            fraction_line = lines[i + 3].strip()

            # Pega apenas o primeiro número antes do "±" e ignora "Fixed"
            amp_match = re.search(r"[-+]?\d*\.?\d+", amp_line)
            phase_match = re.search(r"[-+]?\d*\.?\d+", phase_line)
            fraction_match = re.search(r"[-+]?\d*\.?\d+", fraction_line)

            if amp_match:
                 results[line]['Amp_Laura'] = float(amp_match.group())
            if phase_match:
                results[line]['Phs_Laura'] = float(phase_match.group())
            if fraction_match:
                results[line]['Fraction_Laura'] = float(fraction_match.group())

            i += 3  # Pular para a próxima ressonância
        i += 1  # Continuar a leitura

    return results

def main():
    """Função principal do script"""
    if len(sys.argv) != 2:
        print("Uso: python script.py <N>")
        return
    
    N = sys.argv[1]
    base_path = f"/data1000/charmosinhos/Rian/Goofit3/GooFit/build/examples/D2PPK/Fit/Laura_v{N}"
    laura_path = f"/data1000/charmosinhos/Rian/Laura3/laura/Rian/Toy_MC_{N}/Fit/Fit_results_{N}_.txt"
    
    diagonal_file = os.path.join(base_path, "diagonal_fractions.txt")
    fit_result_file = os.path.join(base_path, "fit_result.txt")
    output_file = os.path.join(base_path, "fit_comparison.txt")
    
    if not (os.path.exists(diagonal_file) and os.path.exists(fit_result_file) and os.path.exists(laura_path)):
        print("Erro: Um ou mais arquivos necessários não existem.")
        return
    
    print("Lendo diagonal_fractions.txt...")
    fractions = read_diagonal_fractions(diagonal_file)
    names = [name for name, _ in fractions]

    print("Lendo fit_result.txt...")
    goofit_results = read_fit_result(fit_result_file, names)

    print("Lendo Fit_results_$N_.txt...")
    laura_results = read_laura_results(laura_path, names)

    print("Gerando arquivo de saída...")
    with open(output_file, 'w') as file:
        file.write("Resonance \t Frac_Goofit \t Frac_Laura \t Amp_Goofit \t Amp_Laura \t Phs_Goofit \t Phs_Laura\n")
        for name, fraction in fractions:
            if name == "rho770":
                file.write(f"{name} \t\t {fraction} \t\t {laura_results[name]['Fraction_Laura']} \t\t\t "
                        f"{goofit_results[name]['Amp_Goofit']} \t\t\t {laura_results[name]['Amp_Laura']} \t\t "
                        f"{goofit_results[name]['Phs_Goofit']} \t\t\t {laura_results[name]['Phs_Laura']}\n")
            else:
                file.write(f"{name} \t\t {fraction} \t\t {laura_results[name]['Fraction_Laura']} \t\t\t "
                        f"{goofit_results[name]['Amp_Goofit']} \t\t {laura_results[name]['Amp_Laura']} \t\t "
                        f"{goofit_results[name]['Phs_Goofit']} \t\t {laura_results[name]['Phs_Laura']}\n")

    print(f"Arquivo gerado com sucesso: {output_file}")

if __name__ == "__main__":
    main()
