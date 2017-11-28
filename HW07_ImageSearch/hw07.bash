#!/bin/bash

#PBS -N hw07_Marcum_08
#PBS -l walltime=11:00:00
#PBS -l mem=2GB 
#PBS -l nodes=1:ppn=8
#PBS -S /bin/bash 
#PBS -j oe

cd $PBS_O_WORKDIR

export OMP_NUM_THREADS=$PBS_NP

/usr/bin/time -v ./ImageSearch MiamiMarcumCenter.png WindowPane_mask.png result_Marcum.png true 50 64 
/usr/bin/time -v ./ImageSearch MiamiMarcumCenter.png WindowPane_mask.png result_Marcum.png true 50 64 
/usr/bin/time -v ./ImageSearch MiamiMarcumCenter.png WindowPane_mask.png result_Marcum.png true 50 64 
/usr/bin/time -v ./ImageSearch MiamiMarcumCenter.png WindowPane_mask.png result_Marcum.png true 50 64 
/usr/bin/time -v ./ImageSearch MiamiMarcumCenter.png WindowPane_mask.png result_Marcum.png true 50 64 
