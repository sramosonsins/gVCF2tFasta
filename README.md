# VCF2tFasta
```
$ gVCF2tFasta
Version 1.0.0
Usage: gVCF2tFasta -v input.vcf(.gz) -r reference.fa(.gz) [-o outputname] [-n chromosomes.txt]
Structural Variants are considered as missing data (N)
Options:
        -h              Help and exit
        -v              Input VCF file
        -r              Reference Fasta file
        -o              Optional Output compressed tFasta filename, Default same as input vcf file
        -n              Optional File with chromosome(s) to convert and its length, Default use all sequences as in reference fasta file
        -i              Imputation (Only use with VCF files, not gVCF files):
                        0 if missing data in VCF is equal to N in tFasta
                        1 if missing data in VCF is equal to reference fasta in tFasta
                        Default value is 0
```