# Change log Version 1.0.0 


#### Usage: 
	gVCF2tFasta -v input.vcf(.gz) -r reference.fa(.gz) [-o outputname] [-n chromosomes.txt]

Note: Structural Variants are considered as missing data (N)

#### gVCF2tFasta arguments/options:
        -h              Help and exit
        -v              Input VCF file
        -r              Reference Fasta file
        -o              Optional Output compressed tFasta filename, Default same as input vcf file
        -n              Optional File with chromosome(s) to convert and its length, Default use all sequences as in reference fasta file
        -i              Imputation (Only use with VCF files, not gVCF files):
                        0 if missing data in VCF is equal to N in tFasta
                        1 if missing data in VCF is equal to reference fasta in tFasta
                        Default value is 0

## Input and Output Files
### Input Files and Flags
- VCF file (input.vcf(.gz)) : accepts both uncompressed and compressed files (gzip , bgzip). The input VCF file must be sorted.
- Reference Fasta file (reference.fa(.gz)) : accepts both uncompressed and compressed files (only bgzip). An index file (.fai) is created for the reference fasta file if it does not exist.
- File with chromosome(s) to convert and its length (chromosomes.txt) : Optional File with chromosome(s) to convert and its length, Default use all sequences as in reference fasta file, if not provided.
- Output compressed tFasta filename (outputname) : Optional Output compressed tFasta filename, Default same as input vcf file, if not provided.
- Imputation (Only use with VCF files, not gVCF files) : 0 if missing data in VCF is equal to N in tFasta, 1 if missing data in VCF is equal to reference fasta in tFasta, Default value is 0.
### Output Files
- Output tfasta file : The output tfasta file is compressed (bgzip).
- Index file : An index file (.tbi) is created for the output tfasta file.