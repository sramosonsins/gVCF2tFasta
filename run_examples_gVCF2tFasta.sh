#VCF2tFasta
#Version 0.2
#Usage: ./gVCF2tFasta -v input.vcf(.gz) -r reference.fa(.gz) -o v2_outputname -n chromosomes.txt
#Structural Variants are considered as missing data (N)
#Options:
#    -h        Help and exit
#    -v        Input VCF file
#    -r        Reference Fasta file
#    -c        Number of allele copies per position per individual (ploidy)
#    -o        Output compressed tFasta filename (without extension)
#    -n        File with chromosome(s) to convert and its length
#    -i        Imputation (Only use with VCF files, not gVCF files):
#                0 if missing data in VCF is equal to N in tFasta
#                1 if missing data in VCF is equal to reference fasta in tFasta
#                Default value is 0

# To compile:
#make -f nbproject/Makefile-Release.mk build/Release/GNU-Linux/main.o
#mkdir -p build/Release/GNU-Linux
#rm -f "build/Release/GNU-Linux/main.o.d"
#g++ -std=c++0x -lz   -c -O2 -MMD -MP -MF "build/Release/GNU-Linux/main.o.d" -o build/Release/GNU-Linux/main.o sources/main.cpp
#/usr/bin/make -f Makefile CONF=Release

# cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -S./ -B./build -G "Unix Makefiles"
# cmake --build ./build --config Release --target gVCF2tFasta -j 14 --
cd ./Examples

# Run examples

echo ---------------------------------------------------------
echo Example 1. Convert a VCF file to a compressed tFasta file
echo ---------------------------------------------------------
echo
echo ../build/gVCF2tFasta -v example.vcf -r ref.fa.gz -c 2 -o v2_example -n ref.fa.fai
../build/gVCF2tFasta -v example.vcf -r ref.fa.gz -c 2 -o v2_example -n ref.fa.fai
echo
echo --------------------------------------------------------------------
echo Example 2. Convert a compressed VCF file to a compressed tFasta file
echo --------------------------------------------------------------------
echo
echo ../build/gVCF2tFasta -v example.vcf.gz -r ref.fa.gz -o v2_example -n ref.fa.fai
../build/gVCF2tFasta -v example.vcf.gz -r ref.fa.gz -o v2_example -n ref.fa.fai
echo
echo -----------------------------------------------------------------------------------------------------------
echo Example 3. Convert a multiple VCF file with all SNPs of 2 different populations to a compressed tFasta file
echo -----------------------------------------------------------------------------------------------------------
echo
echo ../build/gVCF2tFasta -v multipleVCF_2pop.vcf -r ref.fa.gz -c 2 -o v2_example_mult -n ref.fa.fai
../build/gVCF2tFasta -v multipleVCF_2pop.vcf.gz -r ref.fa.gz -c 2 -o v2_example_mult -n ref.fa.fai
echo
echo ---------------------------------------------------------------------------------
echo Example 4. Convert a VCF file with the SNPs of a pool to a compressed tFasta file
echo ---------------------------------------------------------------------------------
echo
echo ../build/gVCF2tFasta -v pool_p10.vcf -r ref.fa.gz -c 10 -o v2_pool -n ref.fa.fai
../build/gVCF2tFasta -v pool_p10.vcf.gz -r ref.fa.gz -c 10 -o v2_pool -n ref.fa.fai
echo
echo ---------------------------------------------------------------------------------
echo Example 5. Convert a compressed VCF file to a compressed tFasta file
echo ---------------------------------------------------------------------------------
echo
echo ../build/gVCF2tFasta -v ./gatk_combined.vcf_10lines.recode.vcf.gz -r ./pdulcis26.contigsPd1-8.fa -c 2 -o ./v2_TEST_almond_10lines -i 0 -n ./pdulcis26.chromosomes.lengths
../build/gVCF2tFasta -v ./gatk_combined.vcf_10lines.recode.vcf.gz -r ./pdulcis26.contigs_Pd1-8.fa -c 2 -o ./v2_TEST_almond_10lines -i 0 -n ./pdulcis26.chromosomes.lengths
echo
echo --------------------------------------------------------------------------------------------
echo Example 6. Convert a compressed gVCF file to a compressed tFasta file for tetraploid samples
echo ---------------------------------------------------------------------------------------------
echo
echo ../build/gVCF2tFasta -v ./Ewi_prueba_merge.vcf.gz -r ./prueba_Eche_ref.fa -c 4
../build/gVCF2tFasta -v ./Ewi_prueba_merge.vcf.gz -r ./prueba_Eche_ref.fa -c 4
echo

