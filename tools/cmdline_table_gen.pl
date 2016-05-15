#!/usr/bin/perl

use strict;
use warnings;

sub print_header {
    my ($fd) = @_;

    my $header = "/*\n".
	" * This header is automatically generated at build\n".
	" * Please, do not modify this file, modify cmdline_table_gen.pl instead\n".
	" */\n\n";
    print($fd $header);
}

sub generate_enum_table {
    my ($filename, $table) = @_;
    my ($fd, $i);

    open($fd, ">", $filename) or die("open: $!");

    print_header($fd);

    print($fd "#ifndef _CMDLINE_LIST_H_\n# define _CMDLINE_LIST_H_\n\n");

    # enumeration
    $i = 0;
    print($fd "enum {\n");
    foreach my $key (keys %{ $table }) {
	if ($i < 2) {
	    print($fd "\tARG_$key \t= $i,\n");
	} else {
	    print($fd "\tARG_$key,\n");
	}
	$i++;
    }
    print($fd "\tARG_NULL,\n");

    print($fd "};\n\n");

    print($fd "#endif /*!_CMDLINE_LIST_H_*/");

    close($fd);
}

sub generate_struct_table {
    my ($filename, $table) = @_;
    my $fd;

    open($fd, ">", $filename) or die("open: $!");

    print_header($fd);

    # enumeration
    print($fd "static struct cmdline_mod_param mod_param[] = {\n");
    foreach my $key (keys %{ $table }) {
	print($fd "\t[ARG_$key] = {\n");
	printf($fd "\t\t.var = \"%s\",\n", lc($key));
	print($fd "\t\t.type = ");

	if( $table->{ $key } eq "B") {
	    print($fd "CMD_BOOL,\n");
	} elsif( $table->{ $key } eq "I") {
	    print($fd "CMD_INT,\n");
	} elsif( $table->{ $key } eq "S") {
	    print($fd "CMD_STRING,\n");
	}

	print($fd "\t\t.present = 0,\n");
	print($fd "\t},\n");
    }

    print($fd "\t[ARG_NULL] = {\n");
    print($fd "\t\t.var = \"\",\n");
    print($fd "\t\t.type = CMD_NULL,\n");
    print($fd "\t\t.present = 0,\n");
    print($fd "\t}\n");


    print($fd "};\n\n");

    close($fd);
}

sub dump_arg_type {
    my ($line) = @_;
    my $arg;

    if ( ($arg) = ($line =~ m/^[\w\d]*\s*:=\s*([ISB])/) ) {
	return $arg;
    } else {
	die("Error arg.\n");
    }
}

sub dump_args {
    my ($filename) = @_;
    my $fd;

    open($fd, "<", $filename) or die("open: $!");

    my ($line, $line_nr, $entry, %args);
    $line_nr = 0;

    while ( defined( $line = <$fd> ) ) {
	if ( $line =~ m/^#/ || $line =~ m/^\s*\n/) {
	    $line_nr++;
	    next;
	} elsif ( ($entry) = ($line =~ m/^ARG_([\w\d]*)/) ) {
	    $args{ $entry } = dump_arg_type($line);
	    $line_nr++;
	} else {
	    die("Error at line ". $line_nr."\n");
	}
    }

    close($fd);

    return \%args;
}

my $args = dump_args("core/kernel/cmdline-config");
generate_enum_table("core/include/atomos/cmdline_list.h", $args);
generate_struct_table("core/kernel/cmdline_struct.h", $args);
