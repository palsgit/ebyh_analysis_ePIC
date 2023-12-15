# ebyh_analysis_ePIC

## ebyhresponse

### Run Batch Farm

use `./run.sh` on SDCC shell

It will run multiple jobs with particle gun type and momentum specified - `particle_p_all.txt`, the execution script is defined in `runSimBatch.sh`.

The analysis macro for filling hitograms with energy deposition is defined in `readHCalSimReader.C`. This macro is executed on Simulation output files.


### Run local analysis

After the jobs have finished one needs to merge the files.

```bash
cd /parent/to/desired/outputdirectory/withparticleandmomentum
merge_new.sh e-_1GeV_hcal_only
```
optionally change the names in alphabetic order (aoutput_e-_1GeV_hcal_only.root, boutput_e-_2GeV_hcal_only.root, etc.)

Then copy `*hcal_only.root`s to the working dir. One can further analyze it and plot energy deposition distribution, sampling fraction, etc. histograms using `ebyh_ana.C ("particle species (e.g. e-)", "path\to\working\dir")`

repeat the same procedure for pi-.

run `ebyh_ratio.C` to get e/h ratio plot.
