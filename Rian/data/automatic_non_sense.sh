#!/bin/bash
. /home/oryan/root-6.30.06-install/bin/thisroot.sh
# Definir o valor de i
i=$1  # Passar i como argumento na execução do script

event_to_remove=$2  # Passar o evento a ser removido como argumento

# Definir os nomes dos arquivos
inputFile="/home/oryan/laura/Rian/data/HighPurity_signal_m13m23_v${i}.root"
outputFile="/home/oryan/laura/Rian/data/HighPurity_signal_m13m23_v$((i+1)).root"

echo "Processando: $inputFile -> $outputFile (Removendo evento $event_to_remove)"

# Executar o script ROOT
root -l -b -q "/home/oryan/laura/Rian/data/RemoveEvent.cpp(\"$inputFile\", \"$outputFile\", $event_to_remove)"
