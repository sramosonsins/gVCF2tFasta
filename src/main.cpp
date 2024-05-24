
#include <getopt.h>
#include <htslib/vcf.h>
#include <htslib/hts.h>
#include <htslib/kseq.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "CFai.h"
#include "CVCF.h"
#include "log.h"
#include "CTFasta.h"
#include "CFasta.h"

inline int end_error(int err)
{
  log_error("Program finished with errors");
  exit( err);
}

void help(char *name)
{
  // std::cerr << "VCF2tFasta\n"
  //         << "Version 0.2\n"
  //         << "Usage: ./gVCF2tFasta -v input.vcf(.gz) -r reference.fa(.gz) -o outputname -n chromosomes.txt\n"
  //         << "Structural Variants are considered as missing data (N)\n"
  //         << "Options:\n"
  //         << "\t-h\t\tHelp and exit\n"
  //         << "\t-v\t\tInput VCF file\n"
  //         << "\t-r\t\tReference Fasta file\n"
  //         << "\t-o\t\tOutput compressed tFasta filename (without extension)\n"
  //         << "\t-n\t\tFile with chromosome(s) to convert and its length\n"
  //         << "\t-i\t\tImputation (Only use with VCF files, not gVCF files):\n"
  //         << "\t\t\t\t0 if missing data in VCF is equal to N in tFasta\n"
  //         << "\t\t\t\t1 if missing data in VCF is equal to reference fasta in tFasta\n"
  //         << "\t\t\t\tDefault value is 0\n"
  //         << std::endl;
  printf("VCF2tFasta\n"
         "Version 0.2\n"
         "Usage: ./gVCF2tFasta -v input.vcf(.gz) -r reference.fa(.gz) -o outputname -n chromosomes.txt\n"
         "Structural Variants are considered as missing data (N)\n"
         "Options:\n"
         "\t-h\t\tHelp and exit\n"
         "\t-v\t\tInput VCF file\n"
         "\t-r\t\tReference Fasta file\n"
         "\t-o\t\tOutput compressed tFasta filename (without extension)\n"
         "\t-n\t\tFile with chromosome(s) to convert and its length\n"
         "\t-i\t\tImputation (Only use with VCF files, not gVCF files):\n"
         "\t\t\t\t0 if missing data in VCF is equal to N in tFasta\n"
         "\t\t\t\t1 if missing data in VCF is equal to reference fasta in tFasta\n"
         "\t\t\t\tDefault value is 0\n"
         "\n");
}

#include <htslib/faidx.h>
// Function to read and print sequence names and lengths from a .fai file
void read_fai_file(const char *fai_filename)
{
  // Load the .fai index
  faidx_t *fai = fai_load(fai_filename);
  if (!fai)
  {
    fprintf(stderr, "Failed to load .fai index for: %s\n", fai_filename);
    return;
  }

  // Get the number of sequences
  int nseq = faidx_nseq(fai);
  if (nseq < 0)
  {
    fprintf(stderr, "Failed to get the number of sequences from: %s\n", fai_filename);
    fai_destroy(fai);
    return;
  }

  printf("Number of sequences: %d\n", nseq);

  // Iterate through sequence names and print their lengths
  for (int i = 0; i < nseq; i++)
  {
    const char *seq_name = faidx_iseq(fai, i);
    int seq_len = faidx_seq_len(fai, seq_name);
    if (seq_len < 0)
    {
      fprintf(stderr, "Failed to get the length of sequence: %s\n", seq_name);
      continue;
    }

    printf("Sequence name: %s, Length: %d\n", seq_name, seq_len);
  }

  // Cleanup
  fai_destroy(fai);
}

bool set_tfasta_header(CTFasta& tfasta, CVCF& vcf) {
    // Get the VCF header
 // determine number of alleles
  // get one line 
    std::string line = "";
    if(vcf.getLine(line) < 0){
      log_error("Error reading the VCF file");
      return 0;
    }
    std::vector<std::string> vcfline = CStringTools::split(line, '\t');
    int count_alleles = 0;
    for (int n = 0; n < vcfline[9].size(); n++)
    {
      if ((vcfline[9][n] == '/') || (vcfline[9][n] == '|'))
      {
        count_alleles++;
      }
    }
    count_alleles++;
    tfasta.count_alleles = count_alleles;
    return 1;
  }

int main(int argc, char *argv[])
{

   // set program name as gVCF2tFasta
  const char *program_name = "gVCF2tFasta";
  log_start(program_name,argc,argv);


  // char *vcfname = NULL;

  // Input parameters
  std::string vcfname;

  std::string chromname;
  std::string tfastaname;
  std::string refname;

  bool imputation = false; // 0: missing data in VCF is equal to N in tFasta, 1: missing data in VCF is equal to reference fasta in tFasta
  // default imputation == "0" missing data in VCF is equal to N in tFasta

  char tmp;
  while ((tmp = getopt(argc, argv, "hv:r:o:n:i:")) != -1)
  {
    switch (tmp)
    {
    case 'h':
      help(argv[0]);
      return 0;
    case 'v':
      vcfname = std::string(optarg);
      break;
    case 'r':
      refname = std::string(optarg);
      break;
    case 'o':
      tfastaname = std::string(optarg);
      break;
    case 'n':
      chromname = std::string(optarg);
      break;
    case 'i':
      imputation = std::stoi(optarg);
      break;
    default:
      help(argv[0]);
      return 1;
    }
  }

  if (vcfname == "")
  {
    log_error("VCF file is required");
    help(argv[0]);
    return 1;
  }

  log_info("VCF file: %s", vcfname.c_str());

  // if (chromname == "")
  // {
  //   log_error("File with chromosomes and lengths not defined");
  //   return 1;
  // }

  // log_info("File with chromosomes and length: %s", chromname.c_str());

  char c;

  // read_fai_file(chromname.c_str());

 

  CVCF vcf(vcfname);

  CFasta fasta(refname);

  std::string tfastaext = tfastaname ;
  // if tfastaname end with .tfa.bgz or .tfa.gz  do not add the extension

  if (tfastaext == "")
  {
    // get basename without path name from vcfname
    std::string base = vcfname;
    size_t lastindex = base.find_last_of("/");
    if (lastindex != std::string::npos)
    {
      base = base.substr(lastindex + 1);
    }
    // get basename without extension
    lastindex = base.find_last_of(".");
    if (lastindex != std::string::npos)
    {
      base = base.substr(0, lastindex);
    }
    // if base end with .vcf or .gvcf just replace the extension
    if (base.size() >= 4 && base.substr(base.size() - 4) == ".vcf")
    {
      base = base.substr(0, base.size() - 4);
    }
    else if (base.size() >= 5 && base.substr(base.size() - 5) == ".gvcf")
    {
      base = base.substr(0, base.size() - 5);
    }

    tfastaext = base + ".tfa.gz";
  }
  else
  {
    if ((tfastaext.size() >= 8 && tfastaext.substr(tfastaext.size() - 8) == ".tfa.bgz") || (tfastaext.size() >= 7 && tfastaext.substr(tfastaext.size() - 7) == ".tfa.gz"))
    {
    }
    else
    {
      // if tfastaname  end with .tfa just add .gz extension
      if (tfastaext.size() >= 4 && tfastaext.substr(tfastaext.size() - 4) == ".tfa")
      {
        tfastaext = tfastaext + ".gz";
      }
      else
      {
        tfastaext = tfastaext + ".tfa.gz";
      }
    }
  }

  // print tfastaext.substr(tfastaext.size() - 7)
  // log_debug("tfastaext: %s",tfastaext.substr(tfastaext.size() - 7).c_str()  );

  
  log_info("Output file: %s", tfastaext.c_str());

 
  CTFasta tfasta(tfastaext);

  std::string linefai = "";
  std::string chromfai = "";
  std::string lengthfai = "";

  std::vector<std::string> chromosomegroup = {};
  std::vector<int> chromosomelength = {};

  if (chromname == "")
  {
    log_warn("File with chromosomes and lengths not defined, Will fallback to the fasta file to get the chromosome names and lengths");
  }
  else
  {
    log_info("File with chromosomes and length: %s", chromname.c_str());
    CFai fai(chromname);
    if (fai.openReadFile())
    {
      linefai = "";
      while (!fai.endFile())
      {
        c = fai.getFileChar();
        // std::cout << c;
        if (c == '\n')
        {
          if (linefai == "")
          {
            continue;
          }
          // Dividimos la linea por columnas y obtenemos el cromosoma:
          std::vector<std::string> failine = CStringTools::split(linefai, '\t');
          chromfai = failine[0];
          chromosomegroup.push_back(chromfai);
          lengthfai = failine[1];
          chromosomelength.push_back( CStringTools::stringToInt(lengthfai));

          linefai = "";
        }
        else
        {
          linefai += c;
        }
      }
      fai.closeFile();
    }
    else
    {
      log_warn("Error Processing fai file %s", chromname.c_str());
      log_warn("Will fallback to the fasta file to get the chromosome names and lengths");
      chromname = "";
    }
  }

  if(!fasta.openReadFile() ) {
    log_error("Error Processing fasta file %s" , refname.c_str() );
    return end_error(1);
  }
  if(chromname == ""){
    log_info("Getting chromosome names and lengths from the fasta file");
    chromosomegroup = fasta.chromosomegroup;
    chromosomelength = fasta.chromosomelength;
  }

  // flush
  std::cout << std::flush;

  std::string chromosome = "";
  int sizeChrom = 0;

  // Follow same logic as in gVCF2tFasta

  if (!vcf.openFile())
  {
    return 1;
  }
  int is_sorted = vcf.is_vcf_sorted();
  if(is_sorted == -1 ){
    log_error("Cannot determine if the VCF file is sorted");
    end_error(1);
  }
  else if(is_sorted == 0){
    log_error("The VCF file is not sorted");

    log_error("Please sort the VCF file, You can run the following command to sort the VCF file: \n");
    
    // bcftools sort -O v -o sorted_example.vcf example.vcf
    log_info("bcftools sort -O v -o sorted_%s %s", vcfname.c_str(), vcfname.c_str());

    end_error(1);
  }
  else{
    log_info("The VCF file is sorted");
  }
  vcf.closeFile();
 
  tfasta.openWriteFile();

  
  vcf.openFile();

  set_tfasta_header(tfasta,vcf);
  vcf.closeFile();

  std::string samplenames_alleles;
  for (int s = 0; s < vcf.GetNumberSamples(); s++)
  {
    for (int m = 0; m < tfasta.count_alleles; m++)
    {
      if (samplenames_alleles == "")
      {
        samplenames_alleles = ">" + vcf.samplenames_[s] + "_" + CStringTools::intToString(m);
      }
      else
      {
        samplenames_alleles = samplenames_alleles + "\t" + ">" + vcf.samplenames_[s] + "_" + CStringTools::intToString(m);
      }
    }
  }

  std::string header =
      "#gVCF2tfasta -v " + vcfname + " -r " + refname + " -o " + tfastaext + " -n " + chromname + "\n" +
      "#NAMES: " + samplenames_alleles + "\n" +
      "#CHROMOSOME\tPOSITION\tGENOTYPES\n";
  tfasta.writeFile(header);

  
  // bcf_hdr_t *hdr = bcf_hdr_read(fp); // Read the VCF header
  // if (!hdr)
  // {
  //   fprintf(stderr, "Failed to read the header from %s", vcfname.c_str());
  //   hts_close(fp);
  //   return 1;
  // }
  // int num_samples = bcf_hdr_nsamples(hdr);
  // // log the number of samples
  // log_info("Number of samples: %d", num_samples);
  // for (int i = 0; i < num_samples; i++)
  // {
  //   // print samile at i hdr->samples[i]
  //   log_info("Sample %d: %s", i, hdr->samples[i]);
  // }

  // // Get the sequence dictionary
  // int nseq = 0;
  // const char **seq_names = bcf_hdr_seqnames(hdr, &nseq);
  // if (!seq_names)
  // {
  //   fprintf(stderr, "Failed to retrieve sequence names from header.\n");
  //   bcf_hdr_destroy(hdr);
  //   bcf_close(fp);
  //   return 1;
  // }

  // // Iterate through header lines to find contig lines
  // for (int i = 0; i < hdr->nhrec; i++)
  // {
  //   bcf_hrec_t *hrec = hdr->hrec[i];
  //   if (hrec->type == BCF_HL_CTG && strcmp(hrec->key, "contig") == 0)
  //   {
  //     const char *seq_name = NULL;
  //     const char *seq_length = NULL;
  //     for (int j = 0; j < hrec->nkeys; j++)
  //     {
  //       if (strcmp(hrec->keys[j], "ID") == 0)
  //       {
  //         seq_name = hrec->vals[j];
  //       }
  //       else if (strcmp(hrec->keys[j], "length") == 0)
  //       {
  //         seq_length = hrec->vals[j];
  //       }
  //     }
  //     if (seq_name && seq_length)
  //     {
  //       printf("Sequence name: %s, Length: %s\n", seq_name, seq_length);
  //     }
  //   }
  // }

  // // log the number of sequences
  // log_info("Number of sequences: %d", nseq);
  // // log the sequence names
  // for (int i = 0; i < nseq; i++)
  // {
  //   log_info("Sequence %d: %s", i, seq_names[i]);
  // }

  // // close the file
  // bcf_hdr_destroy(hdr);
  // hts_close(fp);

  // read file line by line
  kstring_t str = {0, 0, NULL};
  int len;
  std::string line = "";
  // For each chromosome
  bool start_vcf = true;
  int current_position;
  // std::string current_chromosome;
  

  //
  // std::string lineVCF = "";
  // std::string chromVCF = "";
  int pos;
  int pos_f = 0;
  std::string nts;

  int block;
  int snppos;
  int indelpos;
  std::string linetfasta = "";
  std::string subseq = "";


  
  log_info("Processing the VCF file %s", vcfname.c_str());
  // process each chromosome in the same order as provided in the fasta file and the fai file
  // 
  for (std::vector<int>::size_type i = 0; i < chromosomegroup.size(); i++)
  {
    log_debug("Chromosome: %s, Length: %d", chromosomegroup[i].c_str(), chromosomelength[i]);
    chromosome = chromosomegroup[i];
    sizeChrom = chromosomelength[i];

    if (!vcf.openFile())
    {
      return 1;
    }
    int len = 0;
    line = "";
    // current_chromosome = "";
    bool processing_chromosome = false;
    current_position = 0;

    // since the VCF file is sorted, we can read it line by line

    // stop when we reach the end of the chromosome or the end of the file
    while (true)
    {
      // read a new line
      len = vcf.getLine(line);

      

      // if we reach the end of the file, stop
      if (len < 0)
      {
        break;
      }
      // if empty line, skip
      if (line.empty())
      {
        continue;
      }
      // if line starts with #, skip
      if (line[0] == '#')
      {
        continue;
      }
      // otherwise, split the line and process it
      std::vector<std::string> vcfline = CStringTools::split(line, '\t');
      // if the chromosome of the line is different from the current chromosome, stop processing
      if (processing_chromosome && vcfline[0] != chromosome)
      {
        break;
      }
      if (vcfline[0] == chromosome)
      {
        processing_chromosome = true;
      }
      if (!processing_chromosome)
      {
        continue;
      }
      // check if vcfline is a valid vcf record
      if (vcfline.size() < 5)
      {
        log_error("Invalid VCF record: %s", line.c_str());
        continue;
      }

      std::string lineVCF = vcf.SetDataline(vcfline);
      std::vector<std::string> dline = CStringTools::split(lineVCF, '\t');
      // chromVCF = dline[0];
      pos = CStringTools::stringToInt(dline[1]);
     
      nts = dline[2];
      if (pos > (current_position + 1))
      {
        // counter to get subseq
        int counter = 0;
        if (imputation)
        {
          subseq = fasta.obtainSubSeq(chromosome, (current_position + 1), pos);
        }
        // Si la posicion de la dataline es mayor a la posición siguiente de la anterior dataline, escribimos las posiciones intermedias con Ns (missing data):
        for (int n = (current_position + 1); n < pos; n++)
        {
          char c = 'N';
          if (imputation)
          {
            c = subseq[counter];
            counter++;
          }
          std::string nucleotides = "";

          linetfasta = chromosome + "\t" + CStringTools::intToString(n) + "\t";

          for (int s = 0; s < vcf.GetNumberSamples(); s++)
          {
            for (int i = s * tfasta.count_alleles; i < (s * tfasta.count_alleles) + tfasta.count_alleles; i++)
            {
              nucleotides = nucleotides + c;
            }
          }

          linetfasta = linetfasta + nucleotides + "\n";
          tfasta.writeFile(linetfasta);
        }
      } // end if pos > current_position + 1

      // We determine if the dataline corresponds to a SNP, a homozygous block or an indel (checked by the SetDataline function)
      snppos = lineVCF.find("SNP");
      block = lineVCF.find("ROH");
      indelpos = lineVCF.find("INDEL");

      if (pos != current_position)
      {
        if (snppos != std::string::npos)
        {
          // Si la linea del VCF corresponde a un SNP:

          linetfasta = chromosome + "\t" + CStringTools::intToString(pos) + "\t" + nts + "\n";
          tfasta.writeFile(linetfasta);

          current_position = pos;
        }
        else if (block != std::string::npos)
        {
          // Si la linea del VCF corresponde a un Bloque Homocigoto:
          pos_f = CStringTools::stringToInt(dline[4]);

          // // Obtenemos la secuencia correspondiente al bloque a partir del Fasta de referencia:
          // if (fasta.openReadFile())
          // {
          subseq = fasta.obtainSubSeq(chromosome, pos, pos_f);
          //   fasta.closeFile();
          // }

          int counter = 0;
          // Imprimimos la secuencia en formato tFasta:
          for (int n = pos; n <= pos_f; n++)
          {
            std::string nucleotides = "";

            linetfasta = chromosome + "\t" + CStringTools::intToString(n) + "\t";

            for (int s = 0; s < vcf.GetNumberSamples(); s++)
            {
              for (int i = s * tfasta.count_alleles; i < (s * tfasta.count_alleles) + tfasta.count_alleles; i++)
              {
                if (nts[i] == 'R')
                {
                  nucleotides = nucleotides + subseq[counter];
                }
                else if (nts[i] == 'M')
                {
                  nucleotides = nucleotides + "N";
                }
              }
            }

            linetfasta = linetfasta + nucleotides + "\n";
            tfasta.writeFile(linetfasta);
            counter++;
          }

          current_position = pos_f;
        }
        else if (indelpos != std::string::npos)
        {
          // Si la linea del VCF corresponde a un INDEL, ponemos Ns como si fuera missing data:

          linetfasta = chromosome + "\t" + CStringTools::intToString(pos) + "\t" + nts + "\n";
          tfasta.writeFile(linetfasta);

          current_position = pos;
        } // end if indelpos
      } // end if pos != current_position
    } // end while true

    // finished all the lines for the chromosome in the vcf file, now we need to pad the rest of the chromosome if needed
    int counter = 0;
    if (imputation)
    {
      subseq = fasta.obtainSubSeq(chromosome, (current_position + 1), sizeChrom);
    }

    // fasta.closeFile();
    //}

    // Si ya previamente había otro cromosoma con el que se ha trabajado, se escriben Ns hasta la ultima posicion del anterior cromosoma
    for (int n = (current_position + 1); n <= sizeChrom; n++)
    {
      char c = 'N';
      if (imputation)
      {
        c = subseq[counter];
        counter++;
      }
      std::string nucleotides = "";

      linetfasta = chromosome + "\t" + CStringTools::intToString(n) + "\t";

      for (int s = 0; s < vcf.GetNumberSamples(); s++)
      {
        for (int i = s * tfasta.count_alleles; i < (s * tfasta.count_alleles) + tfasta.count_alleles; i++)
        {
          // nucleotides = nucleotides + subseq[counter];
          nucleotides = nucleotides + c;
        }
      }
      linetfasta = linetfasta + nucleotides + "\n";
      tfasta.writeFile(linetfasta);
      
    }
    // finished all the lines for the chromosome in the vcf file, now we need to pad the rest of the chromosome if needed

    // when stoped we will have the last position of the chromosome in the vcf file
    // for the rest of the chromosome we will pad according to the imputation value 

      // close the VCF file to open it again for the next chromosome 
      // TODO :: check if we can reset the file pointer to the beginning of the file instead of closing and opening the file
      vcf.closeFile();
    } // end for each chromosome
    
    
  // close the files
  fasta.closeFile();
  log_info("Finished processing the VCF file");
  log_info("Saving Output file and createing an index: %s", tfastaext.c_str());
  tfasta.closeFile();


  return 0;


  
}