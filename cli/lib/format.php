<?php

function ddns__IPv4AddressToString($addr) {
	return sprintf("%d.%d.%d.%d", $addr[0], $addr[1], $addr[2], $addr[3]);
}

function ddns__IPv6AddressToString($addr) {
	return sprintf(
		"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
		$addr[0], $addr[1], $addr[2], $addr[3],
		$addr[4], $addr[5], $addr[6] , $addr[7] ,
		$addr[9] , $addr[9] , $addr[10] , $addr[11] ,
		$addr[12] , $addr[13] , $addr[14] , $addr[15]
	);
}

function ddns__QTypeToString($qtype) {
	if ($qtype == 1) return "A";
	if ($qtype == 28) return "AAAA";
	if ($qtype == 18) return "AFSDB";
	if ($qtype == 42) return "APL";
	if ($qtype == 257) return "CAA";
	if ($qtype == 60) return "CDNSKEY";
	if ($qtype == 59) return "CDS";
	if ($qtype == 37) return "CERT";
	if ($qtype == 5) return "CNAME";
	if ($qtype == 62) return "CSYNC";
	if ($qtype == 49) return "DHCID";
	if ($qtype == 32769) return "DLV";
	if ($qtype == 39) return "DNAME";
	if ($qtype == 48) return "DNSKEY";
	if ($qtype == 43) return "DS";
	if ($qtype == 108) return "EUI48";
	if ($qtype == 109) return "EUI64";
	if ($qtype == 13) return "HINFO";
	if ($qtype == 55) return "HIP";
	if ($qtype == 65) return "HTTPS";
	if ($qtype == 45) return "IPSECKEY";
	if ($qtype == 25) return "KEY";
	if ($qtype == 36) return "KX";
	if ($qtype == 29) return "LOC";
	if ($qtype == 15) return "MX";
	if ($qtype == 35) return "NAPTR";
	if ($qtype == 2) return "NS";
	if ($qtype == 47) return "NSEC";
	if ($qtype == 50) return "NSEC3";
	if ($qtype == 51) return "NSEC3PARAM";
	if ($qtype == 61) return "OPENPGPKEY";
	if ($qtype == 12) return "PTR";
	if ($qtype == 46) return "RRSIG";
	if ($qtype == 17) return "RP";
	if ($qtype == 24) return "SIG";
	if ($qtype == 53) return "SMIMEA";
	if ($qtype == 6) return "SOA";
	if ($qtype == 33) return "SRV";
	if ($qtype == 44) return "SSHFP";
	if ($qtype == 64) return "SVCB";
	if ($qtype == 32768) return "TA";
	if ($qtype == 249) return "TKEY";
	if ($qtype == 52) return "TLSA";
	if ($qtype == 250) return "TSIG";
	if ($qtype == 16) return "TXT";
	if ($qtype == 256) return "URI";

	return "UNKNOWN";
}

?>
