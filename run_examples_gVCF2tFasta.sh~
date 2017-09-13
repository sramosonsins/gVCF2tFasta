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
make -f nbproject/Makefile-Release.mk build/Release/GNU-Linux/main.o
mkdir -p build/Release/GNU-Linux
rm -f "build/Release/GNU-Linux/main.o.d"
g++ -std=c++0x -lz   -c -O2 -MMD -MP -MF "build/Release/GNU-Linux/main.o.d" -o build/Release/GNU-Linux/main.o main.cpp
/usr/bin/make -f Makefile CONF=Release

cd ./Examples

# Run examples

echo --------------------------------------------------------------------------------
echo Example 1. Convert the chromosome 1 from a VCF file to a compressed tFasta file
echo --------------------------------------------------------------------------------
echo
echo ../bin/gVCF2tFasta -v example.vcf -r ref.fa -o example -c 1
echo
echo ---------------------------------------------------------------------------------------
echo Example 2. Convert the chromosomes 1 and 3 from a VCF file to a compressed tFasta file
echo ---------------------------------------------------------------------------------------
echo
echo ../bin/gVCF2tFasta -v example.vcf -r ref.fa -o example -c 1,3
echo
echo -------------------------------------------------------------------------------------------
echo Example 3. Convert the chromosome 1 from a compressed VCF file to a compressed tFasta file
echo -------------------------------------------------------------------------------------------
echo
echo ../bin/gVCF2tFasta -v example.vcf.gz -r ref.fa -o example -c 1
echo
echo ---------------------------------------------------------------------------------------------------------------------------------------------
echo Example 4. Convert the chromosome 1 from a multiple VCF file with all SNPs of 2 different populations to a compressed tFasta file
echo ---------------------------------------------------------------------------------------------------------------------------------------------
echo
echo ../bin/gVCF2tFasta -v example_mult.vcf -r ref.fa -o example_mult -c 1
echo
echo --------------------------------------------------------------------------------------------------------
echo Example 5. Convert the chromosome 1 from a VCF file with the SNPs of a pool to a compressed tFasta file
echo --------------------------------------------------------------------------------------------------------
echo
echo ../bin/gVCF2tFasta -v pool_p10.vcf -r ref.fa -o pool -c 1
echo

