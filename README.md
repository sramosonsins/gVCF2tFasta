# VCF2tFasta Version 1.0.0
### Convert gVCF files to transposed fasta format (tfasta, indexed and compressed).

Jordi Leno-Colorado

#### Usage: 
	gVCF2tFasta -v input.vcf(.gz) -r reference.fa(.gz) [-o outputname] [-n chromosomes.txt]

Note: Structural Variants are considered as missing data (N)

### Flag Options:
        -h              Help and exit
        -v              Input VCF file
        -r              Reference Fasta file
        -o              Optional Output compressed tFasta filename, Default same as input vcf file
        -n              Optional File with chromosome(s) to convert and its length, Default use all sequences as in reference fasta file
        -i              Imputation (Only use with VCF files, not gVCF files):
                        0 if missing data in VCF is equal to N in tFasta
                        1 if missing data in VCF is equal to reference fasta in tFasta
                        Default value is 0

## Build 

### install htslib first
```bash
$ git clone https://github.com/samtools/htslib.git
$ cd htslib
$ autoreconf -i  # Build the configure script and install files it uses
$ ./configure    # Optional but recommended, for choosing extra functionality
$ make
## make install or sudo make install as required
$ make install
```


### Build gVCF2tFasta

```bash
$ git clone https://github.com/sramosonsins/gVCF2tFasta.git 
$ cd gVCF2tFasta
## configure cmake
$ cmake -B ./build -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Release -S ./
# build
$ cmake --build ./build --config Release
```
