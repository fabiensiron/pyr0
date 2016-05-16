#!/usr/bin/perl

use strict;
use warnings;

sub print_header {
    my ($fd) = @_;

    my $header = "/*\n".
	" * This header is automatically generated at build\n".
	" * Please, do not modify this file, modify modules_table_gen.pl instead.\n".
	" */\n\n";

    print($fd $header);
}

sub generate_table {
    my ($filename, $table) = @_;
    my $fd;

    open($fd, ">", $filename) or die("open: $!");

    print_header($fd);

    print($fd "#ifndef _MODULES_H_\n# define _MODULES_H_\n\n");

    print($fd "#include <tinypy/tp.h>\n\n");
    foreach my $elt (@$table) {
	printf($fd "extern void %s_init(TP);\n", lc($elt));
    }

    print($fd "\n\nvoid (*modules_init_vector[])(tp_vm *) = {\n");

    foreach my $elt (@$table) {
	printf($fd "    %s_init,\n", lc($elt));
    }

    print($fd "    NULL,\n");
    print($fd "};\n\n");

    print($fd "#endif /*!_MODULES_H_*/");

    close($fd);
}

sub dump_modules {
    my ($filename) = @_;
    my $fd;

    open($fd, "<", $filename) or die("open: $!");

    my ($line, $line_nr, $entry, @modules);
    $line_nr = 0;

    while ( defined( $line = <$fd> ) ) {
	if ( $line =~ m/^#/ || $line =~ m/^\s*\n/) {
	    $line_nr++;
	    next;
	} elsif ( ($entry) = ($line =~ m/^CONFIG_([\w\d]*)/) ) {
	    push(@modules, $entry);
	    $line_nr++;
	} else {
	    die("Error at line ". $line_nr."\n");
	}
    }

    close($fd);

    return \@modules;
}

my $modules = dump_modules("runtime/runtime-config");
generate_table("runtime/include/tinypy/modules.h", $modules);
