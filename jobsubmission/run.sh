#!/bin/bash

# Define the input file
input_file="particle_p_all.txt"
#input_file="tileMapTest.txt"
# Define the base job configuration file
base_config="submitSim.job"

echo "reading from $input_file"

# Check if the input file exists
if [ ! -e "$input_file" ]; then
  echo "Input file '$input_file' does not exist."
  exit 1
fi
mkdir -p /gpfs/mnt/gpfs02/eic/palspeic/simdir/ebyh_response/Steel/log
###rm '/gpfs/mnt/gpfs02/eic/palspeic/simdir/ebyh_response/"$1"/log/*'

# Loop through each line in the input file
while read -r line; do
  # Split the line into two variables, assuming they are separated by a space
  PARTICLE=$(echo "$line" | cut -d' ' -f1)
  MOMENTUM=$(echo "$line" | cut -d' ' -f2)

  echo "PARTICLE: $PARTICLE"
  echo "MOMENTUM: $MOMENTUM"
  

  # Define an array of argument sets
  arg_set=("${PARTICLE} ${MOMENTUM}")
  # Create a new job configuration file by appending arguments to the base file
  config_file="config_$(echo $arg_set | tr ' ' '_').job"
  cp "$base_config" "$config_file"

  line=" arguments =  \$(Cluster) \$(Process) ${arg_set} \n"
  sed -i "25 a ${line}" $config_file
  # Submit the job
  echo "Submitting job with arguments: $arg_set"
  condor_submit "$config_file"
  # remove the temporary config file
  rm "$config_file"

done <"$input_file"
