<?php

chdir(__DIR__."/../");

$calls = scandir("src/module/_private/api");
$header_file = "#if !defined(PV_DDNS_API_CALLS_h)
	#define PV_DDNS_API_CALLS_h

	#include <module/_private/_ddns.h>
";

$handle_call_file  = (require __DIR__."/auto-gen-header-comment.php")();
$handle_call_file .= "#include <module/_private/_ddns.h>\n";
$handle_call_file .= "#include <module/agf/_api_calls.h>\n\n";
$handle_call_file .= "bool PV_AGF_ddns_handleAPICall(
    ddns__Instance *instance,
    const char *request,
    napc__Writer *response
) {\n";

foreach ($calls as $call) {
	if (substr($call, 0, 1) === ".") continue;
	if (substr($call, -2, 2) === ".h") continue;

	$call_name = substr($call, 0, strlen($call) - 2);

	$prototype = "
    bool PV_ddns_handleAPICall_$call_name(
        ddns__Instance *instance,
        const char *request,
        napc__Writer *response
    );
";

	$handle_call_file .= "
    if (napc_memeql(request, \"$call_name\", napc_strlen(\"$call_name\"))) {
        const char *body = request + napc_strlen(\"$call_name\");\n
        PV_DDNS_DEBUG(\"Handling API Call '$call_name'\");
        return PV_ddns_handleAPICall_$call_name(instance, body, response);
    }
";

	$header_file .= $prototype;
}

$header_file .= "#endif\n";

$handle_call_file .= "\n    PV_DDNS_SECURITY(\"Unknown API call.\");\n\n";
$handle_call_file .= "    return false;\n";
$handle_call_file .= "}\n";

file_put_contents("src/module/agf/_api_calls.h", $header_file);
file_put_contents("src/module/agf/_handle_api_call.c", $handle_call_file);
