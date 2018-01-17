# afree

****************************
afree_v2.0             
****************************

afree: a tool for rapid large-scale protein sequence comparision

GENERAL INFORMATION:
	The afree tool takes two FASTA formatted (.faa) files containing protein sequences as input and calculates
	their an all-against-all protein similarity search.

AVAILIBILITY:
    	afree executable are available (./bin/afree) and can be downloaded from http://vbc.med.monash.edu.au/~kmahmood/afree

REQUIREMENTS:
	* Teseted on Mac OSX (Intel) and Linux systems.

EXAMPLE:

	Usage:
		afree -g1 <fasta file1> -g2 <fasta file2> -o <output file name> -c <SD-score threshold ( 10<c<100 default 10)> -k <k-word size (default+recommended 5)>

	Example: The example folder contains the following FASTA files.
		humx.fa - Human Chromosome X
		musx.fa	- Mouse Chromosome X
		tub.fa	- M. Tuberculosis proteome
		lep.fa	- M. Leprae proteome

		To perform an all-against-all proteome wide search run the following

		~$>./bin/afree -g1 example/humx.fa -g2 example/musx.fa -o example/hmx -c 15 -k 5

		The output file example/hmx.afree is created.

		#accession1	#accession2	#SD-score
		960627116	960627116	100
		960627117	960627117	100
		960627118	960627118	98.6425
		960627119	960627119	100
		960627120	960627120	100
		960627121	960627121	99.7326
		960627122	960627122	100
		960627122	960627715	70.4082
		960627715	960627122	70.4082
		960627122	1009027271	64.966
		1009027271	960627122	64.966	....

CONTACT:
	Khalid.Mahmood@unimelb.edu.au
    
