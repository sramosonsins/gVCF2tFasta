# gVCF2tFasta Version 1.0.0
Convert gvcf/vcf files to transposed fasta format (tfasta, indexed and compressed).

Jordi Leno-Colorado, Sebastian E. Ramos-Onsins, Ahmed Hafed

#### Usage: 
	gVCF2tFasta -v input.vcf(.gz) -r reference.fa(.gz) -c nsam_x_ploidy [-o outputname] [-n chromosomes.txt] [-i 0/1]

Note: Structural Variants are considered as missing data (N)

#### gVCF2tFasta arguments/options:
        -h              Help and exit
        -v              Input VCF file
        -r              Reference Fasta file
        -c              Number of allele copies per position and individual (ploidy)
        -o              Optional Output compressed tFasta filename, Default same as input vcf file
        -n              Optional File with chromosome(s) to convert and its length, Default use all sequences as in reference fasta file
        -i              Imputation (Only use with VCF files, not gVCF files):
                        0 if missing data in VCF is equal to N in tFasta
                        1 if missing data in VCF is equal to reference fasta in tFasta
                        Default value is 0

gVCF2tFasta accepts both uncompressed and compressed files (gzip). The input VCF file must sorted. 
If the fasta file is compressed, it must be compressed with bgzip. An index file (.fai) is created for the reference fasta file if it does not exist.

The output tfasta file is compressed (bgzip) and indexed.

## Build gVCF2tFasta

#### First Install htslib [Tested with v1.20] 

On linux, you can install htslib using the package manager of your distribution. For example, on Ubuntu, you can install htslib using the following command:
```bash
$ sudo apt-get install libhts-dev
```

On macOS, you can install htslib using Homebrew:
```bash
$ brew install htslib
```

Or you can build htslib from source. To do so, follow these steps:

```bash
$ git clone https://github.com/samtools/htslib.git
$ cd htslib
$ git checkout 1.20
$ autoreconf -i  # Build the configure script and install files it uses
$ ./configure    # Optional but recommended, for choosing extra functionality
$ make
## make install or sudo make install as required
$ make install
```
For more information, see the htslib [GITHUB](https://github.com/samtools/htslib)

### Build gVCF2tFasta
#### Using CMake
```bash
$ git clone https://github.com/sramosonsins/gVCF2tFasta.git 
$ cd gVCF2tFasta
## configure cmake
$ cmake -B ./build -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Release -S ./
# build
$ cmake --build ./build --config Release


## Run gVCF2tFasta

$ ./build/gVCF2tFasta -h

```
