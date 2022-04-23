<?php

chdir(__DIR__."/../");

$config = json_decode(
	file_get_contents("config.json"), false
);

$config_handle_kv_file  = (require __DIR__."/auto-gen-header-comment.php")();
$config_handle_kv_file .= "#include <module/config/_private/_config.h>\n";

$config_handle_kv_file .= "\n";

$config_handle_kv_file .= "bool PV_ddns_Config_handleKeyValue(\n";
$config_handle_kv_file .= "    ddns__Config *config,\n";
$config_handle_kv_file .= "    const char *key,\n";
$config_handle_kv_file .= "    const char *value\n";
$config_handle_kv_file .= ") {\n";

foreach ($config as $section => $keys) {
	foreach ($keys as $key => $type) {
		if (!strlen($type)) continue;

		$config_key = "$section.$key";

		$config_handle_kv_file .= "    if (napc_streqli(key, \"$config_key\")) {\n";

		if ($type === "napc_u16") {
			$config_handle_kv_file .= "        napc_u16 tmp;\n";

			$config_handle_kv_file .= "        if (napc_parser_parseDecimalNumberU16(value, &tmp)) {\n";
			$config_handle_kv_file .= "            config->$config_key = tmp;\n";
		} else if ($type === "napc_u32") {
			$config_handle_kv_file .= "        napc_u32 tmp;\n";

			$config_handle_kv_file .= "        if (napc_parser_parseDecimalNumberU32(value, &tmp)) {\n";
			$config_handle_kv_file .= "            config->$config_key = tmp;\n";
		} else if ($type === "_ip_address") {
			$config_handle_kv_file .= "        if (napc_parser_parseIPv4Address(value, NULL)) {\n";
			$config_handle_kv_file .= "            memcpy(config->$config_key, value, sizeof(config->$config_key));\n";
		} else if ($type === "bool") {
			$config_handle_kv_file .= "        bool tmp;\n";

			$config_handle_kv_file .= "        if (napc_parser_parseBoolean(value, &tmp)) {\n";
			$config_handle_kv_file .= "            config->$config_key = tmp;\n";
		}

		$config_handle_kv_file .= "            return true;\n";
		$config_handle_kv_file .= "        } else {\n";
		$config_handle_kv_file .= "            PV_DDNS_CONFIG_ERROR(\"Failed to parse value for '$config_key' value is '%s'\", value);\n";
		$config_handle_kv_file .= "        }\n";

		$config_handle_kv_file .= "    }\n\n";
	}
}

$config_handle_kv_file .= "    PV_DDNS_CONFIG_ERROR(\"Unknown key '%s'\", key);\n";
$config_handle_kv_file .= "    return false;\n";
$config_handle_kv_file .= "}\n";

file_put_contents("src/module/agf/_config_handle_key_value.c", $config_handle_kv_file);
