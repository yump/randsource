randsource
============

Fast pseudorandom data source. Good for wiping disks. Not cryptographic
grade.

Usage
-----

    randsource >/dev/sdX

Building
--------

    ./autogen && ./configure CFLAGS="-O3 -march=native" && make

Installing
----------

    sudo make install    

Disclaimers
-----------

Not guaranteed to be fit for any particular purpose, etc. etc., not
guaranteed not to put George W. Bush back in the white house or reduce
your cat to a smouldering pile of ash, etc. etc...

Not guaranteed to be faster than your SATA bus, but probably is.
