#gVCF2tFasta v0.2 (20170908) Jordi Leno-Colorado

# Usage: ./gVCF2tFasta -v input.vcf -r reference.fa -o outputname -c chromosome(s)
#
# Flags:
#      -v [Input VCF file]
#      -r [Reference Fasta file (it must be indexed with samtools faidx)]
#      -o [Output compressed tFasta filename (without extension), it will be added the chromosome(s) of -c option in the final filename]
#      -c [Chromosome(s) to convert (if there are more than one chromosome, they have to be separated by comma)]
#   OPTIONAL PARAMETERS:
#      -h [help and exit]

# To compile:
#make -f nbproject/Makefile-Release.mk build/Release/GNU-Linux/main.o
#mkdir -p build/Release/GNU-Linux
#rm -f "build/Release/GNU-Linux/main.o.d"
#g++ -std=c++0x -lz   -c -O2 -MMD -MP -MF "build/Release/GNU-Linux/main.o.d" -o build/Release/GNU-Linux/main.o sources/main.cpp
#/usr/bin/make -f Makefile CONF=Release

cd ./Examples

# Run examples

echo ---------------------------------------------------------
echo Example 1. Convert a VCF file to a compressed tFasta file
echo ---------------------------------------------------------
echo
echo ../bin/gVCF2tFasta -v example.vcf -r ref.fa.gz -o example -n ref.fa.fai
../bin/gVCF2tFasta -v example.vcf -r ref.fa.gz -o example -n ref.fa.fai
echo
echo --------------------------------------------------------------------
echo Example 2. Convert a compressed VCF file to a compressed tFasta file
echo --------------------------------------------------------------------
echo
echo ../bin/gVCF2tFasta -v example.vcf.gz -r ref.fa.gz -o example -n ref.fa.fai
../bin/gVCF2tFasta -v example.vcf.gz -r ref.fa.gz -o example -n ref.fa.fai
echo
echo -----------------------------------------------------------------------------------------------------------
echo Example 3. Convert a multiple VCF file with all SNPs of 2 different populations to a compressed tFasta file
echo -----------------------------------------------------------------------------------------------------------
echo
echo ../bin/gVCF2tFasta -v multipleVCF_2pop.vcf -r ref.fa.gz -o example_mult -n ref.fa.fai
../bin/gVCF2tFasta -v multipleVCF_2pop.vcf -r ref.fa.gz -o example_mult -n ref.fa.fai
echo
echo ---------------------------------------------------------------------------------
echo Example 4. Convert a VCF file with the SNPs of a pool to a compressed tFasta file
echo ---------------------------------------------------------------------------------
echo
echo ../bin/gVCF2tFasta -v pool_p10.vcf -r ref.fa.gz -o pool -n ref.fa.fai
../bin/gVCF2tFasta -v pool_p10.vcf -r ref.fa.gz -o pool -n ref.fa.fai
echo

