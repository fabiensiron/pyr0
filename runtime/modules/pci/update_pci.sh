#!/bin/sh

set -e
SRC="http://pciids.sourceforge.net/v2.2/pci.ids"
DEST=pci.ids

if which curl >/dev/null 2>&1 ;then
    DL="curl -o $DEST $SRC"
else
    echo >&2 "update_pci: cannot find curl"
    exit 1
fi

if ! $DL ; then
    echo >&2 "update_pci: download failed"
fi

perl update_pci_h.pl

echo "Done."

