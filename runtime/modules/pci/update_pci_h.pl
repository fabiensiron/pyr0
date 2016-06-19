#!/usr/bin/perl

use strict;
use warnings;

sub backslash {
    my ($str) = @_;

    $str =~ s/\\/\\\\/g;
    $str =~ s/\"/\\"/g;

    return $str;
}

sub trigraph_warn {
    my ($str) = @_;

    $str =~ s/\?\?\)/\)/g;

    return $str;
}

sub generate_header {
    my ($filename, $table) = @_;
    my $fd;

    open($fd, ">", $filename) or die("open: $!");

    my $struct = "struct pci_ids_table {\n".
	"\tunsigned short ven_id;\n".
	"\tconst char *ven_s;\n".
	"\tunsigned short dev_id;\n".
	"\tconst char *dev_s;\n".
	"} pci_ids_table[] = {\n";

    printf($fd $struct);

    foreach my $elt (0..@$table-1) {
	printf($fd "\t{0x%s, \"%s\", 0x%s, \"%s\"},\n", $table->[$elt][0],
	       trigraph_warn(backslash($table->[$elt][1])),
	       $table->[$elt][2],
	       trigraph_warn(backslash($table->[$elt][3])));
    }

    printf($fd "};\n");

    close($fd);
}

sub dump_table {

    my ($filename) = @_;
    my $fd;

    open($fd, "<", $filename) or die("open: $!");

    my ($line, $vendor_id, $vendor_s, $last_vendor_id, $last_vendor_s);
    my ($device_id, $device_s);
    my @ids;
    my $v = 0;

    while ( defined( $line = <$fd> ) ) {
	if ( $line =~ m/^#/ || $line =~ m/^\s*\n/) {
	    next;
	} elsif ( ($vendor_id, $vendor_s) = ($line =~ m/^([\d\w]*)  (.*)/) ) {
	    if ( $v == 1 || $vendor_id eq "ffff" ) {
		$device_id = "0000";
		$device_s = "";
		push(@ids, [$last_vendor_id, $last_vendor_s, $device_id, $device_s]);
	    }

	    $last_vendor_id = $vendor_id;
	    $last_vendor_s = $vendor_s;

	    if ( $vendor_id eq "ffff" ) {
		last;
	    }

	    $v = 1;

	} elsif ( ($device_id, $device_s) = ($line =~ m/^\t([d\w]*)  (.*)/) ) {
#	    printf("%s %s %s %s \n", $last_vendor_id, $last_vendor_s, $device_id, $device_s);
	    push(@ids, [$last_vendor_id, $last_vendor_s, $device_id, $device_s]);

	    $v = 0;
	}
    }

    push(@ids, ["1234", "Bochs", "1111", "VGA BIOS Extensions Graphics Adapter"]);

    close($fd);

    return \@ids;
}

my $ids = dump_table("pci.ids");
generate_header("pci_list.h", $ids);
