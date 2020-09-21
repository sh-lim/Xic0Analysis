#!/usr/bin/perl -w

use File::Copy qw(move);

#@datalist = ("LHC17MC19");
#@datalist = ("LHC17MC10","LHC17MC11","LHC17MC12","LHC17MC13","LHC17MC14");
#@datalist = ("LHC18MC10","LHC18MC11","LHC18MC12","LHC18MC13","LHC18MC14");
#@datalist = ("LHC17MC1","LHC17MC2","LHC17MC3");
#@datalist = ("LHC18MC1","LHC18MC2","LHC18MC3");
#@datalist = ("LHC16MCl","LHC16MC1","LHC16MC2","LHC16MC5");
#@datalist = ("LHC16MCk","LHC16MCl");
#@datalist = ("LHC18d","LHC18e","LHC18f","LHC18g","LHC18h");
#@datalist = ("LHC18i","LHC18j","LHC18k","LHC18l");
#@datalist = ("LHC18n","LHC18o","LHC18p","LHC18m");
@datalist = ("LHC18k","LHC18l");
#$taskname = "XiSHLEventA";
$taskname = "XiSHLNew2B";
$mode = "full"; #full, terminate, merge

foreach $dataset (@datalist){

	print "Dataset: ".$dataset."\n";

	$cmd = "aliroot -q 'runAnalysis.C(\"$taskname\",\"$dataset\",\"$mode\")'"; 
#	print $cmd."\n";
	system $cmd;

	if ( $mode eq "merge" ){
		move "AnalysisResults.root", "AnalysisResults_$dataset.root";
		move "event_stat.root", "event_stat_$dataset.root";
		move "EventStat_temp.root", "EventStat_temp_$dataset.root";

#		$cmd = "mv AnalysisResults.root AnalysisResults_$dataset.root";
#		print $cmd."\n";
#		system $cmd;

#		$cmd = "mv event_stat.root event_stat_$dataset.root";
#		print $cmd."\n";
#		system $cmd;

#		$cmd = "mv EventStat_temp.root EventStat_temp_$dataset.root";
#		print $cmd."\n";
#		system $cmd;
	}

	system "rm -rf ${taskname}${dataset}*";
	system "rm -rf *.d *.so *.xml";

}
