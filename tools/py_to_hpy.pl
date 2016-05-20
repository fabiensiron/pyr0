#!/usr/bin/perl

use strict;
use warnings;

use Getopt::Long qw(GetOptions);

sub parse_args {
    my ($input, $output);
    my $usage = "Usage: $0 --input INPUT --output OUTPUT\n";

    GetOptions(
	"input=s"  => \$input,
	"output=s" => \$output,
    ) or die $usage;

    if ( !defined( $input ) || !defined( $output ) ) {
	print "Some arguments are missing...\n";
	die $usage;
    }
    return ($input, $output);
}

sub generate_hpy {
    my ($code, $var) = @_;
    my $hpy = "";

    $hpy .= "char *$var =\n";

    my @lines = split /\n/, $code;
    foreach my $line (@lines) {
	$hpy .= "\"";
	$hpy .= $line;
	$hpy .= '\n"';
	$hpy .= "\n";
    }

    $hpy .= '"\n"';
    $hpy .= ";\n";
}

sub write_hpy {
    my ($filename, $code) = @_;
    my $fd;

    open($fd, ">", $filename) or die("open: $!");

    print($fd $code);

    close($fd);
}

sub dump_code {
    my ($filename) = @_;
    my $fd;

    open($fd, "<", $filename) or die("open: $!");

    my ($line, $code);

    $code = "";

    while ( defined( $line = <$fd> ) ) {
	$code .= $line;
    }

    close($fd);

    return $code;
}

use File::Basename;

sub build_var_name {
    my ($filename) = @_;

    my $var = fileparse($filename, '.hpy');
    $var =~ tr/-/_/;
    $var .= "_code";

    return $var;
}

my ($input, $output) = parse_args();
my $code = dump_code($input);
my $var = build_var_name($output);
$code = generate_hpy($code, $var);
write_hpy($output, $code);
