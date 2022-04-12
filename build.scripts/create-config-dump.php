<?php

chdir(__DIR__."/../");

$config = json_decode(
	file_get_contents("config.json"), false
);

$config_dump_file  = (require __DIR__."/auto-gen-header-comment.php")();
$config_dump_file .= "#include <module/config/_private/_config.h>\n";

$config_dump_file .= "\n";

$config_dump_file .= "void PV_ddns_Config_dump(\n";
$config_dump_file .= "    const ddns__Config *config\n";
$config_dump_file .= ") {\n";

$config_dump_file .= "    PV_DDNS_CONFIG_INFO(\" \");\n";

foreach ($config as $section => $keys) {

	$config_dump_file .= "    PV_DDNS_CONFIG_INFO(\"* $section\");\n";

	foreach ($keys as $key => $type) {
		if (!strlen($type)) continue;

		$config_key = "$section.$key";

		$padded_key = str_pad($key, 16, " ", STR_PAD_RIGHT);

		$config_dump_file .= "    PV_DDNS_CONFIG_INFO(\"    $padded_key = ";

		if ($type === "napc_u16") {
			$config_dump_file .= '%" NAPC_U16_PRINTF';
		} else if ($type === "napc_u32") {
			$config_dump_file .= '%" NAPC_U32_PRINTF';
		} else if ($type === "_ip_address") {
			$config_dump_file .= '%s"';
		} else if ($type === "bool") {
			$config_dump_file .= '%s"';
		}

		if ($type !== "bool") {
			$config_dump_file .= ", config->$config_key);\n";
		} else {
			$config_dump_file .= ", config->$config_key ? \"yes\" : \"no\");\n";
		}
	}

	$config_dump_file .= "    PV_DDNS_CONFIG_INFO(\" \");\n";
}

$config_dump_file .= "}\n";

file_put_contents("src/module/config/_private/_dump.c", $config_dump_file);
