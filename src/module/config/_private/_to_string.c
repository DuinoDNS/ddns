/*
 * NOTICE: This file was automatically generated.
 */
#include <module/config/_private/_config.h>

bool PV_ddns_Config_toString(
    const ddns__Config *config,
    bool include_secret,
    char *buf,
    napc_size buf_size
) {
    napc__Writer writer;
    napc_Writer_init(&writer, buf, buf_size);

    if (include_secret) {
        if (!napc_Writer_writeString(&writer, "general.secret,")) return false;
        if (!napc_Writer_writeString(&writer, config->general.secret)) return false;
        if (!napc_Writer_writeChar(&writer, '\n')) return false;
    }

    if (!napc_Writer_writeString(&writer, "general.config_lock,")) return false;
    if (config->general.config_lock) {
        if (!napc_Writer_writeString(&writer, "true")) return false;
    } else {
        if (!napc_Writer_writeString(&writer, "false")) return false;
    }
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "general.tracked_metric,")) return false;
    if (!napc_Writer_writeStringFormat(&writer, "%" NAPC_U16_PRINTF, config->general.tracked_metric)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "debug.ip,")) return false;
    if (!napc_Writer_writeString(&writer, config->debug.ip)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "debug.port,")) return false;
    if (!napc_Writer_writeStringFormat(&writer, "%" NAPC_U16_PRINTF, config->debug.port)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "debug.level,")) return false;
    if (!napc_Writer_writeStringFormat(&writer, "%" NAPC_U16_PRINTF, config->debug.level)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "network.address,")) return false;
    if (!napc_Writer_writeString(&writer, config->network.address)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "network.netmask,")) return false;
    if (!napc_Writer_writeString(&writer, config->network.netmask)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "network.gateway,")) return false;
    if (!napc_Writer_writeString(&writer, config->network.gateway)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "network.out_port,")) return false;
    if (!napc_Writer_writeStringFormat(&writer, "%" NAPC_U16_PRINTF, config->network.out_port)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "upstream.enabled,")) return false;
    if (config->upstream.enabled) {
        if (!napc_Writer_writeString(&writer, "true")) return false;
    } else {
        if (!napc_Writer_writeString(&writer, "false")) return false;
    }
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "upstream.address,")) return false;
    if (!napc_Writer_writeString(&writer, config->upstream.address)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "upstream.port,")) return false;
    if (!napc_Writer_writeStringFormat(&writer, "%" NAPC_U16_PRINTF, config->upstream.port)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "upstream.ping_port,")) return false;
    if (!napc_Writer_writeStringFormat(&writer, "%" NAPC_U16_PRINTF, config->upstream.ping_port)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "upstream.ping_interval,")) return false;
    if (!napc_Writer_writeStringFormat(&writer, "%" NAPC_U16_PRINTF, config->upstream.ping_interval)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "upstream.timeout,")) return false;
    if (!napc_Writer_writeStringFormat(&writer, "%" NAPC_U16_PRINTF, config->upstream.timeout)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "discovery.enabled,")) return false;
    if (config->discovery.enabled) {
        if (!napc_Writer_writeString(&writer, "true")) return false;
    } else {
        if (!napc_Writer_writeString(&writer, "false")) return false;
    }
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "api.enabled,")) return false;
    if (config->api.enabled) {
        if (!napc_Writer_writeString(&writer, "true")) return false;
    } else {
        if (!napc_Writer_writeString(&writer, "false")) return false;
    }
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "api.listen_port,")) return false;
    if (!napc_Writer_writeStringFormat(&writer, "%" NAPC_U16_PRINTF, config->api.listen_port)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "dns.listen_port,")) return false;
    if (!napc_Writer_writeStringFormat(&writer, "%" NAPC_U16_PRINTF, config->dns.listen_port)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeString(&writer, "dns.local_ttl,")) return false;
    if (!napc_Writer_writeStringFormat(&writer, "%" NAPC_U32_PRINTF, config->dns.local_ttl)) return false;
    if (!napc_Writer_writeChar(&writer, '\n')) return false;

    if (!napc_Writer_writeChar(&writer, 0)) return false;

    return true;
}
