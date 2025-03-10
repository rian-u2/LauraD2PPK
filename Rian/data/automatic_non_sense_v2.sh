#!/bin/bash

start=$(date +%s)


. /home/oryan/root-6.30.06-install/bin/thisroot.sh
# Definir o valor de i
i=$1  # Passar i como argumento na execução do script

# event_to_remove=$2  # Passar o evento a ser removido como argumento

# for ((i=5001; i<=5030; i++)); do
    echo "               "
    echo "=========================================================================================================================================================="
    echo "Current iteration: $i"


    # Definir os nomes dos arquivos
    inputFile="/home/oryan/laura/Rian/data/HighPurity_signal_m13m23_v${i}.root"
    outputFile="/home/oryan/laura/Rian/data/HighPurity_signal_m13m23_v$((i+1)).root"
    trashFile="/home/oryan/laura/Rian/data/HighPurity_signal_m13m23_v$((i-1)).root"

    echo "Running fitD2PKP"
    /home/oryan/laura/Rian/fitD2PKP fit $inputFile 0 1 0 > /dev/null 2>&1

    wait

    echo "capturing event_to_remove from /home/oryan/laura/Rian/problematic_events.txt"
    
    # Captura o primeiro número do arquivo /home/oryan/laura/Rian/problematic_events.txt
    event_to_remove=$(grep -o -E '[0-9]+' /home/oryan/laura/Rian/problematic_events.txt | head -n 1)
    wait
    echo "Processando: $inputFile -> $outputFile (Removendo evento $event_to_remove)"

    # Executar o script ROOT
    root -l -b -q "/home/oryan/laura/Rian/data/RemoveEvent.cpp(\"$inputFile\", \"$outputFile\", $event_to_remove)"

     # Deletar o arquivo antigo (trashFile)
    if [[ -f "$trashFile" ]]; then
        echo "Deletando arquivo antigo: $trashFile"
        rm "$trashFile"
    else
        echo "Arquivo antigo não encontrado: $trashFile"
    fi
    echo "iteration $i done"
    echo "               "
    echo "=========================================================================================================================================================="
    echo "               "
    sleep 1
# done

end=$(date +%s)
runtime=$((end-start))

# Convert seconds to minutes
minutes=$((runtime / 60))
seconds=$((runtime % 60))

echo "Execution time: $minutes minutes and $seconds seconds"
