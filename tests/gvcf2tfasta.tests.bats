load ./base.tests.bats
load '../node_modules/bats-support/load'
load '../node_modules/bats-assert/load'
load '../node_modules/bats-file/load'
# bats test_tags=tag:bin
@test "gvcf2tfasta ok" {
  run gVCF2tFasta -h
  assert_success
  [ "${lines[0]}" = "gVCF2tFasta" ]
  [ "${lines[2]}" = "Usage: gVCF2tFasta -v input.vcf(.gz) -r reference.fa(.gz) [-o outputname] [-n chromosomes.txt]" ]
}


# FASTA TO TFASTA tests with tag fa2tfa
# echo --------------------------------------------------------------------------------------------------
# echo fasta to tfasta: Useful to run mstatspop in sliding windows mode. Also generates a weighting file.
# echo --------------------------------------------------------------------------------------------------

# bats test_tags=tag:vcf2tfa
@test "Convert a VCF" {
  # echo ---------------------------------------------------------
  # echo Example 1. Convert a VCF file to a compressed tFasta file
  # echo ---------------------------------------------------------
  run gVCF2tFasta -v  $TEST_FILES_DIR/example.vcf -r  $TEST_FILES_DIR/ref.fa.gz -o $TEST_OUTPUT/example -n  $TEST_FILES_DIR/ref.fa.fai 
  assert_success
  assert_file_exist $TEST_OUTPUT/example.tfa.gz
}

# bats test_tags=tag:vcf2tfa
@test "Convert a compressed VCF 1" {
  # echo --------------------------------------------------------------------
  # echo Example 2. Convert a compressed VCF file to a compressed tFasta file
  # echo --------------------------------------------------------------------
  run gVCF2tFasta -v  $TEST_FILES_DIR/example.vcf.gz -r  $TEST_FILES_DIR/ref.fa.gz -o $TEST_OUTPUT/example -n  $TEST_FILES_DIR/ref.fa.fai 
  assert_success
  assert_file_exist $TEST_OUTPUT/example.tfa.gz
}

# bats test_tags=tag:vcf2tfa
@test "Convert a multiple VCF with SNPs of 2 pop" {
  # echo -----------------------------------------------------------------------------------------------------------
  # echo Example 3. Convert a multiple VCF file with all SNPs of 2 different populations to a compressed tFasta file
  # echo -----------------------------------------------------------------------------------------------------------
  run gVCF2tFasta -v $TEST_FILES_DIR/multipleVCF_2pop.vcf.gz -r $TEST_FILES_DIR/ref.fa.gz -o $TEST_OUTPUT/example_mult -n $TEST_FILES_DIR/ref.fa.fai
  assert_success
  assert_file_exist $TEST_OUTPUT/example_mult.tfa.gz
}



# bats test_tags=tag:vcf2tfa
@test "Convert a VCF with SNPs pool" {
  # echo ---------------------------------------------------------------------------------
  # echo Example 4. Convert a VCF file with the SNPs of a pool to a compressed tFasta file
  # echo ---------------------------------------------------------------------------------
  run gVCF2tFasta -v $TEST_FILES_DIR/pool_p10.vcf.gz -r $TEST_FILES_DIR/ref.fa.gz -o $TEST_OUTPUT/pool -n $TEST_FILES_DIR/ref.fa.fai
  assert_success
  assert_file_exist $TEST_OUTPUT/pool.tfa.gz
}

# bats test_tags=tag:vcf2tfa
@test "Convert a compressed VCF 2" {
  # echo ---------------------------------------------------------------------------------
  # echo Example 5. Convert a compressed VCF file to a compressed tFasta file
  # echo ---------------------------------------------------------------------------------
  run gVCF2tFasta -v $TEST_FILES_DIR/gatk_combined.vcf_10lines.recode.vcf.gz -r $TEST_FILES_DIR/pdulcis26.contigs_Pd1-8.fa -o $TEST_OUTPUT/TEST_almond_10lines -i 0 -n $TEST_FILES_DIR/pdulcis26.chromosomes.lengths

  assert_success
  assert_file_exist $TEST_OUTPUT/TEST_almond_10lines.tfa.gz
}
