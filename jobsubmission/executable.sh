#!/bin/sh

#####export GUN_PHI=${3}
#####export GUN_THETA=${4}

export GUN_PARTICLE=${3}
export GUN_MOMENTUM=${4}
export NUMBER_OF_EVENTS=1000

export FILENAME=${GUN_PARTICLE}_${NUMBER_OF_EVENTS}events_p${GUN_MOMENTUM}GeV_${1}_${2}
export DDSIM_FILE=sim_${FILENAME}.edm4hep.root
export OUTPUT_FILE=output_${FILENAME}.root


echo "source /gpfs/mnt/gpfs02/eic/palspeic/EpicHcalAnalysis/ebyh/runSimBatch.sh ${1} ${2}" | /eic/u/palspeic/eic-shell

#EOF
