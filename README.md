# afree

<!-- ****************************
afree_v2.0             
**************************** -->

afree: a tool for rapid large-scale all-against-all protein sequence comparison.

The afree tool takes two FASTA formatted files containing protein sequences as input and calculates
their all-against-all sequence similarity.

Cite:
Mahmood K, Webb GI, Song J, Whisstock JC, Konagurthu AS. Efficient large-scale protein sequence comparison and gene matching to identify orthologs and co-orthologs. Nucleic Acids Research. 2012;40(6):e44. doi:10.1093/nar/gkr1261.

Installation and availability:

afree executable are available from http://www.vicbioinformatics.com/software.afree.shtml

$ wget https://github.com/khalidm/afree/archive/master.zip
$ unzip master.zip
$ cd afree-master
$ make

EXAMPLE:

	Usage:
		$ afree -g1 <fasta_1> -g2 <fasta_2> -o <output file> -c <SD-score ( 10<c<100 default 10)> -k <k-word size(default+recommended 5)>

	Example:
        The example folder contains the following FASTA files.
		humX.fa - Human Chromosome X
		musX.fa	- Mouse Chromosome X
		tub.fa	- M. Tuberculosis proteome
		lep.fa	- M. Leprae proteome

		To perform an all-against-all proteome wide search run the following

		afree -g1 example/humX.fa -g2 example/musX.fa -o example/hmX -c 15 -k 5

		The output file example/hmx.afree is created.

		#seq1_id	#seq2_id	#SD-score
		960627116	960627116	100.0
		960627117	960627117	100.0
		960627118	960627118	98.6
		960627119	960627119	100.0
		960627120	960627120	100.0
		960627121	960627121	99.7
		960627122	960627122	100.0
		960627122	960627715	70.4
		960627715	960627122	70.4
		960627122	1009027271	64.9
		1009027271	960627122	64.9

	Tested on Mac OSX (Intel) and Linux systems.
