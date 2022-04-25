<?php

chdir(__DIR__."/../");

$config = json_decode(
	file_get_contents("config.json"), false
);

$config_to_string_file  = (require __DIR__."/auto-gen-header-comment.php")();
$config_to_string_file .= "#include <module/config/_private/_config.h>\n";

$config_to_string_file .= "\n";

$config_to_string_file .= "bool PV_AGF_ddns_Config_write(\n";
$config_to_string_file .= "    const ddns__Config *config,\n";
$config_to_string_file .= "    const char *desired_section,\n";
$config_to_string_file .= "    napc__Writer *writer\n";
$config_to_string_file .= ") {\n";

$config_to_string_file .= "    if (napc_streqli(desired_section, \"secret\")) {\n";
$config_to_string_file .= "        if (!napc_Writer_writeString(writer, \"general.secret,\")) return false;\n";
$config_to_string_file .= "        if (!napc_Writer_writeString(writer, config->general.secret)) return false;\n";
$config_to_string_file .= "        if (!napc_Writer_writeChar(writer, '\\n')) return false;\n";
$config_to_string_file .= "        return true;\n";	
$config_to_string_file .= "    }\n\n";

foreach ($config as $section => $keys) {
	$config_to_string_file .= "    /* $section */\n";
	$if_expr = "napc_streqli(desired_section, \"$section\")";

	$config_to_string_file .= "    if ($if_expr) {\n";

	foreach ($keys as $key => $type) {
		if (!strlen($type)) continue;

		$config_key = "$section.$key";

		$config_to_string_file .= "        if (!napc_Writer_writeString(writer, \"$config_key,\")) return false;\n";

		if ($type === "napc_u16") {
			$config_to_string_file .= "        if (!napc_Writer_writeStringFormat(writer, \"%\" NAPC_U16_PRINTF, config->$config_key)) return false;\n";
		} else if ($type === "napc_u32") {
			$config_to_string_file .= "        if (!napc_Writer_writeStringFormat(writer, \"%\" NAPC_U32_PRINTF, config->$config_key)) return false;\n";
		} else if ($type === "_ip_address") {
			$config_to_string_file .= "        if (!napc_Writer_writeString(writer, config->$config_key)) return false;\n";
		} else if ($type === "bool") {
			$config_to_string_file .= "        if (config->$config_key) {\n";
			$config_to_string_file .= "            if (!napc_Writer_writeString(writer, \"true\")) return false;\n";
			$config_to_string_file .= "        } else {\n";
			$config_to_string_file .= "            if (!napc_Writer_writeString(writer, \"false\")) return false;\n";
			$config_to_string_file .= "        }\n";
		}

		$config_to_string_file .= "        if (!napc_Writer_writeChar(writer, '\\n')) return false;\n";

		$config_to_string_file .= "\n";
	}

	$config_to_string_file .= "        return true;\n";
	$config_to_string_file .= "    }\n";
}

$config_to_string_file .= "    return false;\n";
$config_to_string_file .= "}\n";

file_put_contents("src/module/agf/_config_to_string.c", $config_to_string_file);
