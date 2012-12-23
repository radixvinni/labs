#!/usr/bin/perl

use Crypt::DES;

my $key = pack("H16", $ARGV[1]);
my $cipher = new Crypt::DES $key;
my $ciphertext = $cipher->encrypt(pack("H16",$ARGV[0]));
print unpack("H16", $ciphertext), "\n";
