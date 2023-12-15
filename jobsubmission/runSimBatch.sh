#!/bin/sh
workdir=/gpfs/mnt/gpfs02/eic/palspeic/simdir/ebyh_response/Steel/${GUN_PARTICLE}_${GUN_MOMENTUM}GeV_hcal_only
mkdir -p $workdir
cd $workdir

#####export GUN_THETA_MIN=$(echo "$GUN_THETA - 0.0001" | bc)
#####export GUN_THETA_MAX=$(echo "$GUN_THETA + 0.0001" | bc)
#####export GUN_PHI_MIN=$(echo "$GUN_PHI - 0.0001" | bc)
#####export GUN_PHI_MAX=$(echo "$GUN_PHI + 0.0001" | bc)
export GUN_MOMENTUM_MIN=$(echo "$GUN_MOMENTUM - 0.00001" | bc)
export GUN_MOMENTUM_MAX=$(echo "$GUN_MOMENTUM + 0.00001" | bc)


if [ -f "$DDSIM_FILE" ]; then
    echo "$DDSIM_FILE exists."
else
    source /gpfs/mnt/gpfs02/eic/palspeic/eicsoft/epic/install/setup.sh
    ddsim --compactFile $DETECTOR_PATH/epic_hcal_only.xml --numberOfEvents ${NUMBER_OF_EVENTS} --random.seed $(date +%N) --enableGun --gun.particle $GUN_PARTICLE --gun.thetaMin 90*degree --gun.thetaMax 180*degree --gun.distribution uniform --gun.momentumMin ${GUN_MOMENTUM_MIN}*GeV --gun.momentumMax ${GUN_MOMENTUM_MAX}*GeV --outputFile ${DDSIM_FILE}
fi

#####if [ -f "$EICRECON_FILE" ]; then
 #####   echo "$EICRECON_FILE exists."
#####else
#####   source /gpfs/mnt/gpfs02/eic/alpro/EICrecon/bin/eicrecon-this.sh
 #####   eicrecon $DDSIM_FILE -Ppodio:output_file=${EICRECON_FILE} -Pjana:nevents=${NUMBER_OF_EVENTS} -Ppodio:output_include_collections="MCParticles,HcalEndcapNRawHits,HcalEndcapNRecHits,HcalEndcapNMergedHits,HcalEndcapNClusters,HcalEndcapNTruthClusters,EcalEndcapNRawHits,EcalEndcapNRecHits,EcalEndcapNClusters,EcalEndcapNClusterAssociations,EcalEndcapNTruthClusters,EcalEndcapNTruthClusterAssociations"
    rm -r calibrations
    rm -r fieldmaps
####fi

root -l '/gpfs/mnt/gpfs02/eic/palspeic/EpicHcalAnalysis/ebyh/readHCalSimReader.C("'${DDSIM_FILE}'" , "'${OUTPUT_FILE}'")'
rm -r $DDSIM_FILE