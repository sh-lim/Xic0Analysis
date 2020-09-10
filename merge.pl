#!/usr/bin/perl -w

#@datalist = ("LHC17MC1","LHC17MC2","LHC17MC3");
#@datalist = ("LHC16MC1","LHC16MC2","LHC16MC5");
#@datalist = ("LHC18MC2","LHC18MC3");
#@datalist = ("LHC18d","LHC18e","LHC18f","LHC18g","LHC18h");
#@datalist = ("LHC18i","LHC18j","LHC18k","LHC18l","LHC18n");
#@datalist = ("LHC18n","LHC18o","LHC18p","LHC18m");
@datalist = ("LHC16MC5");
#@datalist = ("LHC17MC15","LHC17MC16","LHC17MC17","LHC17MC18","LHC17MC19");
#@datalist = ("LHC18MC15","LHC18MC16","LHC18MC17","LHC18MC18","LHC18MC19");
$taskname = "XiSHLNew2B";

$env_aliphysics = $ENV{"ALICE_PHYSICS"};

foreach $dataset (@datalist){
	
	$dir = "/alice/cern.ch/user/l/lim/myWorkingDir${taskname}${dataset}";

	$cmd = "perl ${env_aliphysics}/PWGUD/DIFFRACTIVE/macros/alien_cp.pl ${dir} root_archive.zip AnalysisResults.root"; 
#	print ${cmd}."\n";
	system $cmd;

	@filelist = `find .${dir} -name 'AnalysisResults.root'`;

#	$cmd = "hadd -f EventAnalysisResults_${taskname}_${dataset}.root";
	$cmd = "hadd -f AnalysisResults_${taskname}_${dataset}.root";

	foreach $filename (@filelist){
		chomp($filename);
		$cmd = $cmd." $filename";
	}

#	print $cmd;
	system $cmd;

	$cmd = "rm -rf .${dir}";
#	print $cmd."\n";
	system $cmd;

}
