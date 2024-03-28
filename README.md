# VCF2tFasta Version 0.2

### Convert gVCF files to transposed fasta format (tfasta, indexed and compressed).

Jordi Leno-Colorado

#### Usage: 
	./gVCF2tFasta -v input.vcf(.gz) -r reference.fa(.gz) -o outputname -n chromosomes.txt

Note: Structural Variants are considered as missing data (N)

### Flag Options:
    -h        Help and exit
    -v        Input VCF file
    -r        Reference Fasta file
    -o        Output compressed tFasta filename (without extension)
    -n        File with chromosome(s) to convert and its length
    -i        Imputation (Only use with VCF files, not gVCF files):
                0 if missing data in VCF is equal to N in tFasta
                1 if missing data in VCF is equal to reference fasta in tFasta
                Default value is 0

### To compile:
	make -f nbproject/Makefile-Release.mk build/Release/GNU-Linux/main.o
	mkdir -p build/Release/GNU-Linux
	rm -f "build/Release/GNU-Linux/main.o.d"
	g++ -std=c++0x -lz   -c -O2 -MMD -MP -MF "build/Release/GNU-Linux/main.o.d" -o build/Release/GNU-Linux/main.o sources/main.cpp
	/usr/bin/make -f Makefile CONF=Release

### Examples:

Convert a compressed single individual VCF file to a compressed tFasta file

	../bin/gVCF2tFasta -v example.vcf.gz -r ref.fa.gz -o example -n ref.fa.fai

Convert a VCF file with the SNPs of a pool to a compressed tFasta file
	
	../bin/gVCF2tFasta -v pool_p10.vcf -r ref.fa.gz -o pool -n ref.fa.fai


Convert a compressed multiple individual VCF file to a compressed tFasta file

	../bin/gVCF2tFasta -v ./gatk_combined.vcf_10lines.recode.vcf.gz -r ./pdulcis26.contigs_Pd1-8.fa -o ./TEST_almond_10lines -i 0 -n ./pdulcis26.chromosomes.lengths
