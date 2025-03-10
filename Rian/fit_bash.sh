#!/bin/bash

start=$(date +%s)

. /home/oryan/root-6.30.06-install/bin/thisroot.sh



echo "building fitD2PKP"
g++ -o fitD2PKP fitD2PKP.cc     -I$HOME/laura/inc     -L$HOME/laura/build/lib     $(root-config --cflags --libs)     -lLaura++
wait
echo "fitD2PKP built"


# Definir o valor de i
i=$1  # Passar i como argumento na execução do script

inputFile="/home/oryan/laura/Rian/data/HighPurity_signal_m13m23_v5069.root"

echo "Running fitD2PKP, fit $i"
/home/oryan/laura/Rian/fitD2PKP fit $inputFile $i 1 0 
wait

dir_name="Fit_Results_${i}"
# Cria a pasta (se já não existir)
mkdir -p "$dir_name"
echo "Pasta 'Fit_Results_${i}' criada!"


# Executar o script ROOT
root -l -b -q "/home/oryan/laura/Rian/amp_phs_fit_organizer.cpp($i)"
wait

fitfile="/home/oryan/laura/Rian/fitToyMC_${i}_expt0.root"
echo "Saving Plots"
# Executar o script ROOT
root -l -b -q "/home/oryan/laura/Rian/compare_plot.cpp(\"$inputFile\",\"$fitfile\",$i)"
wait

# Move os arquivos para a pasta
mv "fitDpipiK_${i}_expt_0-0.root" "fitToyMC_${i}_expt0.root" "$dir_name" 2>/dev/null

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
echo "                                                     "