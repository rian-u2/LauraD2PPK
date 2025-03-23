#!/bin/bash

start=$(date +%s)

. /home/oryan/root-6.30.06-install/bin/thisroot.sh

echo "building toyD2PKP"
g++ -o toyD2PKP toyD2PKP.cc     -I$HOME/laura/inc     -L$HOME/laura/build/lib     $(root-config --cflags --libs)     -lLaura++
wait
echo "toyD2PKP built"

# Definir o valor de i
i=$1  # Passar i como argumento na execução do script

echo "Running toyD2PKP, toy $i"
/home/oryan/laura/Rian/toyD2PKP gen 1 
wait

dir_name="Toy_MC_${i}"
# Cria a pasta (se já não existir)
mkdir -p "$dir_name"
echo "Pasta 'Toy_MC_${i}' criada!"

toyfile="/home/oryan/laura/Rian/data.root"
Tree1="DecayTree"
Tree2="DecayTree"
mode="Toy_MC_"
echo "Saving Plots"
# Executar o script ROOT
root -l -b -q "/home/oryan/laura/Rian/compare_plot.cpp(\"$inputFile\",\"$fitfile\",\"$Tree1\",\"$Tree2\",\"$mode\",$i)"
wait

# Move os arquivos para a pasta
mv "/home/oryan/laura/Rian/data.root" "$dir_name" 2>/dev/null

# Mensagem de confirmação
echo "Arquivos movidos para '$dir_name'."

end=$(date +%s)
runtime=$((end-start))

# Convert seconds to minutes
minutes=$((runtime / 60))
seconds=$((runtime % 60))
echo "                                                     "
echo "==================================================="
echo "||    Execution time: $minutes minutes and $seconds seconds   ||"
echo "==================================================="
echo "                                                      "