#!/bin/bash

start=$(date +%s)

. /home/oryan/root-6.30.06-install/bin/thisroot.sh

echo "building toyDs2PKP"
g++ -o toyDs2PKP toyDs2PKP.cc     -I$HOME/laura/inc     -L$HOME/laura/build/lib     $(root-config --cflags --libs)     -lLaura++
wait
echo "toyDs2PKP built"

# Definir o valor de i
i=$1  # Passar i como argumento na execução do script

echo "Running toyDs2PKP, toy $i"
/home/oryan/laura/Rian/toyDs2PKP gen 1 
wait

#dir_name="GooFit_comp_Toys_${i}"
dir_name="kappa_v${i}"
# Cria a pasta (se já não existir)
mkdir -p "$dir_name"
echo "Pasta $dir_name criada!"

toyfile="/home/oryan/laura/Rian/data.root"
Tree1="DecayTree"
Tree2="DecayTree"
echo "Saving Plots"
# Executar o script ROOT
root -l -b -q "/home/oryan/laura/Rian/compare_plot.cpp(\"$toyfile\",\"$toyfile\",\"$Tree1\",\"$Tree2\",\"$dir_name\",$i)"
wait

# dir_name2="$dir_name/Fit"
# # Cria a pasta (se já não existir)
# mkdir -p "$dir_name2"
# echo "Pasta $dir_name2 criada!"


# echo "Running toyD2PKP, fit $i"
# /home/oryan/laura/Rian/toyD2PKP fit $toyfile $i 1 0 
# wait


# # Executar o script ROOT
# root -l -b -q "/home/oryan/laura/Rian/amp_phs_fit_organizer.cpp($i,\"$dir_name2\")"
# wait


# fitfile="/home/oryan/laura/Rian/fitToyMC_${i}_expt0.root"
# Tree3="DecayTree"
# Tree4="genResults"

# echo "Saving Plots"
# # Executar o script ROOT
# root -l -b -q "/home/oryan/laura/Rian/compare_plot.cpp(\"$toyfile\",\"$fitfile\",\"$Tree3\",\"$Tree4\",\"$dir_name2\",$i)"
# wait

# # Move os arquivos para a pasta
# mv "fitDpipiK_${i}_expt_0-0.root" "fitToyMC_${i}_expt0.root" "$dir_name2" 2>/dev/null


# Move os arquivos para a pasta
mv "/home/oryan/laura/Rian/data.root" "$dir_name" 2>/dev/null

# Mensagem de confirmação
echo "Arquivos movidos para '$dir_name' e '$dir_name2'."




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