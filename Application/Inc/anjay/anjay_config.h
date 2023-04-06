/*
 * Copyright 2023 AVSystem <avsystem@avsystem.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANJAY_CONFIG_H
#define ANJAY_CONFIG_H

/**
 * @file anjay_config.h
 *
 * Anjay library configuration.
 *
 * The preferred way to compile Anjay is to use CMake, in which case this file
 * will be generated automatically by CMake.
 *
 * However, to provide compatibility with various build systems used especially
 * by embedded platforms, it is alternatively supported to compile Anjay by
 * other means, in which case this file will need to be provided manually.
 *
 * <strong>NOTE: To compile this library without using CMake, you need to
 * configure avs_commons and avs_coap first. Please refer to documentation in
 * the <c>avs_commons_config.h</c> and <c>avs_coap_config.h</c> files (provided
 * in the repositories as <c>avs_commons_config.h.in</c> and
 * <c>avs_coap_config.h.in</c>, respectively) for details.</strong>
 *
 * <strong>Anjay requires the following avs_coap options to be enabled:</strong>
 *
 * - @c WITH_AVS_COAP_UDP
 * - @c WITH_AVS_COAP_STREAMING_API
 * - @c WITH_AVS_COAP_BLOCK is highly recommended
 * - @c WITH_AVS_COAP_OBSERVE (if @c ANJAY_WITH_OBSERVE is enabled)
 * - @c WITH_AVS_COAP_OSCORE (if @c ANJAY_WITH_COAP_OSCORE is enabled, available
 *   only as a commercial feature)
 *
 * <strong>Anjay requires the following avs_commons components to be
 * enabled:</strong>
 *
 * - All components required by avs_coap, see <c>avs_coap_config.h</c>
 * - @c avs_algorithm
 * - @c avs_stream
 * - @c avs_url
 * - @c avs_persistence is highly recommended
 * - @c avs_http (if @c ANJAY_WITH_HTTP_DOWNLOAD is enabled)
 * - @c avs_rbtree (if @c ANJAY_WITH_OBSERVE or
 *   @c ANJAY_WITH_MODULE_ACCESS_CONTROL is enabled)
 *
 * In the repository, this file is provided as <c>anjay_config.h.in</c>,
 * intended to be processed by CMake. If editing this file manually, please copy
 * or rename it to <c>anjay_config.h</c> and for each of the
 * <c>\#cmakedefine</c> directives, please either replace it with regular
 * <c>\#define</c> to enable it, or comment it out to disable. You may also need
 * to replace variables wrapped in <c>\@</c> signs with concrete values. Please
 * refer to the comments above each of the specific definition for details.
 *
 * If you are editing a file previously generated by CMake, these
 * <c>\#cmakedefine</c>s will be already replaced by either <c>\#define</c> or
 * commented out <c>\#undef</c> directives.
 */

/**
 * Enable logging in Anjay.
 *
 * If this flag is disabled, no logging is compiled into the binary at all.
 */
#define ANJAY_WITH_LOGS

/**
 * Enable TRACE-level logs in Anjay.
 *
 * Only meaningful if <c>ANJAY_WITH_LOGS</c> is enabled.
 */
/* #undef ANJAY_WITH_TRACE_LOGS */

/**
 * Enable core support for Access Control mechanisms.
 *
 * Requires separate implementation of the Access Control object itself.
 * Either the implementation available as part of
 * <c>ANJAY_WITH_MODULE_ACCESS_CONTROL</c>, or a custom application-provided one
 * may be used.
 */
/* #undef ANJAY_WITH_ACCESS_CONTROL */

/**
 * Enable automatic attribute storage.
 *
 * Requires <c>AVS_COMMONS_WITH_AVS_PERSISTENCE</c> to be enabled in avs_commons
 * configuration.
 */
#define ANJAY_WITH_ATTR_STORAGE

/**
 * Enable support for the <c>anjay_download()</c> API.
 */
#define ANJAY_WITH_DOWNLOADER

/**
 * Enable support for CoAP(S) downloads.
 *
 * Only meaningful if <c>ANJAY_WITH_DOWNLOADER</c> is enabled.
 */
#define ANJAY_WITH_COAP_DOWNLOAD

/**
 * Enable support for HTTP(S) downloads.
 *
 * Only meaningful if <c>ANJAY_WITH_DOWNLOADER</c> is enabled.
 */
/* #undef ANJAY_WITH_HTTP_DOWNLOAD */

/**
 * Enable support for the LwM2M Bootstrap Interface.
 */
#define ANJAY_WITH_BOOTSTRAP

/**
 * Enable support for the LwM2M Discover operation.
 *
 * Note that it is required for full compliance with the LwM2M protocol.
 */
#define ANJAY_WITH_DISCOVER

/**
 * Enable support for the LwM2M Information Reporting interface (Observe and
 * Notify operations).
 *
 * Requires <c>WITH_AVS_COAP_OBSERVE</c> to be enabled in avs_coap
 * configuration.
 *
 * Note that it is required for full compliance with the LwM2M protocol.
 */
#define ANJAY_WITH_OBSERVE

/**
 * Enable support for measuring amount of LwM2M traffic
 * (<c>anjay_get_tx_bytes()</c>, <c>anjay_get_rx_bytes()</c>,
 * <c>anjay_get_num_incoming_retransmissions()</c> and
 * <c>anjay_get_num_outgoing_retransmissions()</c> APIs.
 */
/* #undef ANJAY_WITH_NET_STATS */

/**
 * Enable support for communication timestamp
 * (<c>anjay_get_server_last_registration_time()</c>
 * <c>anjay_get_server_next_update_time()</c> and
 * <c>anjay_get_server_last_communication_time()</c>) APIs.
 */
/* #undef ANJAY_WITH_COMMUNICATION_TIMESTAMP_API */

/**
 * Enable support for the <c>anjay_resource_observation_status()</c> API.
 */
#define ANJAY_WITH_OBSERVATION_STATUS

/**
 * Maximum number of servers observing a given Resource listed by
 * <c>anjay_resource_observation_status()</c> function.
 *
 * Only meaningful if <c>ANJAY_WITH_OBSERVATION_STATUS</c> is enabled.
 */
#define ANJAY_MAX_OBSERVATION_SERVERS_REPORTED_NUMBER 0

/**
 * Enable guarding of all accesses to <c>anjay_t</c> with a mutex.
 */
#define ANJAY_WITH_THREAD_SAFETY

/**
 * Enable standard implementation of an event loop.
 *
 * Requires C11 <c>stdatomic.h</c> header to be available, and either a platform
 * that provides a BSD-compatible socket API, or a compatibility layer file (see
 * <c>AVS_COMMONS_POSIX_COMPAT_HEADER</c> in <c>avs_commons_config.h</c>). This
 * is designed to best work with the defalt implementation of avs_net sockets
 * (see <c>AVS_COMMONS_NET_WITH_POSIX_AVS_SOCKET</c>), but alternative socket
 * implementations can also be used.
 *
 * The event loop is most useful when thread safety features
 * (@ref ANJAY_WITH_THREAD_SAFETY and <c>AVS_COMMONS_SCHED_THREAD_SAFE</c>) are
 * enabled as well, but this is not a hard requirement. See the documentation
 * for <c>anjay_event_loop_run()</c> for details.
 */
#define ANJAY_WITH_EVENT_LOOP

/**
 * Enable support for features new to LwM2M protocol version 1.1.
 */
#define ANJAY_WITH_LWM2M11

/**
 * Enable support for OSCORE-based security for LwM2M connections.
 *
 * Requires <c>ANJAY_WITH_LWM2M11</c> to be enabled, and
 * <c>WITH_AVS_COAP_OSCORE</c> to be enabled in avs_coap configuration.
 *
 * IMPORTANT: Only available as part of the OSCORE commercial feature. Ignored
 * in the open source version.
 */
/* #undef ANJAY_WITH_COAP_OSCORE */

/**
 * Enable support for the LwM2M Send operation.
 *
 * Requires <c>ANJAY_WITH_LWM2M11</c> and either <c>ANJAY_WITH_SENML_JSON</c> or
 * <c>ANJAY_WITH_CBOR</c> to be enabled.
 */
#define ANJAY_WITH_SEND

/**
 * Enable support for the SMS binding and the SMS trigger mechanism.
 *
 * Requires <c>WITH_AVS_COAP_UDP</c> to be enabled in avs_coap configuration.
 *
 * IMPORTANT: Only available as part of the SMS commercial feature. Ignored in
 * the open source version.
 */
/* #undef ANJAY_WITH_SMS */

/**
 * Enable support for sending and receiving multipart SMS messages.
 *
 * Requires <c>ANJAY_WITH_SMS</c> to be enabled.
 *
 * IMPORTANT: Only available as part of the SMS commercial feature. Ignored in
 * the open source version.
 */
/* #undef ANJAY_WITH_SMS_MULTIPART */

/**
 * Enable support for Non-IP Data Delivery.
 *
 * Requires <c>ANJAY_WITH_LWM2M11</c> to be enabled, and
 * <c>WITH_AVS_COAP_UDP</c> to be enabled in avs_coap configuration.
 *
 * IMPORTANT: Only available as a commercial feature. Ignored in the open
 * source version.
 */
/* #undef ANJAY_WITH_NIDD */

/**
 * Enable support for core state persistence
 * (<c>anjay_new_from_core_persistence()</c> and
 * <c>anjay_delete_with_core_persistence()</c> APIs).
 *
 * Requires <c>ANJAY_WITH_OBSERVE</c> to be enabled, and
 * <c>AVS_COMMONS_WITH_AVS_PERSISTENCE</c> to be enabled in avs_commons
 * configuration.
 *
 * IMPORTANT: Only available as a commercial feature. Ignored in the open
 * source version.
 */
/* #undef ANJAY_WITH_CORE_PERSISTENCE */

/**
 * Enable support for CoAP Content-Format numerical values 1541-1544 that have
 * been used before final LwM2M TS 1.0.
 */
/* #undef ANJAY_WITH_LEGACY_CONTENT_FORMAT_SUPPORT */

/**
 * Enable support for JSON format as specified in LwM2M TS 1.0.
 *
 * NOTE: Anjay is only capable of generating this format, there is no parsing
 * support regardless of the state of this option.
 */
/* #undef ANJAY_WITH_LWM2M_JSON */

/**
 * Disable support for TLV format as specified in LwM2M TS 1.0.
 *
 * NOTE: LwM2M Client using LwM2M 1.0 MUST support this format. It may be
 * disabled if LwM2M 1.1 is used and SenML JSON or SenML CBOR is enabled.
 */
/* #undef ANJAY_WITHOUT_TLV */

/**
 * Disable support for Plain Text format as specified in LwM2M TS 1.0 and 1.1.
 *
 * NOTE: LwM2M Client SHOULD support this format. It may be disabled to reduce
 * library size if LwM2M Server is configured to not use it in requests.
 */
/* #undef ANJAY_WITHOUT_PLAINTEXT */

/**
 * Disable use of the Deregister message.
 */
/* #undef ANJAY_WITHOUT_DEREGISTER */

/**
 * Disable support for "IP stickiness", i.e. preference of the same IP address
 * when reconnecting to a server using a domain name.
 */
#define ANJAY_WITHOUT_IP_STICKINESS

/**
 * Enable support for SenML JSON format, as specified in LwM2M TS 1.1.
 *
 * NOTE: As opposed to <c>ANJAY_WITH_LWM2M_JSON</c>, both generating and parsing
 * is supported.
 *
 * Requires <c>ANJAY_WITH_LWM2M11</c> to be enabled.
 */
#define ANJAY_WITH_SENML_JSON

/**
 * Enable support for CBOR and SenML CBOR formats, as specified in LwM2M TS 1.1.
 *
 * Requires <c>ANJAY_WITH_LWM2M11</c> to be enabled.
 */
#define ANJAY_WITH_CBOR

/**
 * Enable support for Enrollment over Secure Transport.
 *
 * Requires <c>ANJAY_WITH_BOOTSTRAP</c> to be enabled.
 *
 * IMPORTANT: Only available as part of the EST commercial feature. Ignored in
 * the open source version.
 */
/* #undef ANJAY_WITH_EST */

/**
 * Enable support for hardware security engine in the EST subsystem.
 *
 * Requires <c>ANJAY_WITH_EST</c> to be enabled in Anjay configuration and
 * <c>AVS_COMMONS_WITH_AVS_CRYPTO_PKI_ENGINE</c> to be enabled in avs_commons
 * configuration.
 *
 * IMPORTANT: Only available in commercial versions that include both the EST
 * and HSM features. Ignored in versions distributed without these features.
 */
/* #undef ANJAY_WITH_EST_ENGINE_SUPPORT */

/**
 * Enable support for the Confirmable Notification attribute, as specified in
 * LwM2M TS 1.2.
 *
 * Before TS 1.2, this has been supported in Anjay as a custom extension, and
 * thus it is available independently from TS 1.2 support itself, including in
 * the open source version.
 *
 * Requires <c>ANJAY_WITH_OBSERVE</c> to be enabled.
 */
/* #undef ANJAY_WITH_CON_ATTR */

/**
 * Enable support for handling security credentials in the data model using
 * structured <c>avs_crypto</c> types.
 *
 * If the <c>security</c> module is also enabled (see @ref
 * ANJAY_WITH_MODULE_SECURITY), it also enables support for passing these
 * credentials through such structured types when adding Security object
 * instances via the @ref anjay_security_instance_t structure.
 */
#define ANJAY_WITH_SECURITY_STRUCTURED

/**
 * Maximum size in bytes supported for the "Public Key or Identity" resource in
 * the LwM2M Security object.
 *
 * If editing this file manually, <c>256</c> shall be
 * replaced with a positive integer literal.
 *
 * The default value defined in CMake build scripts is 2048.
 * Minimal suggested setting for low-resource builds is 256.
 */
#define ANJAY_MAX_PK_OR_IDENTITY_SIZE 256

/**
 * Maximum size in bytes supported for the "Secret Key" resource in the LwM2M
 * Security Object.
 *
 * If editing this file manually, <c>128</c> shall be replaced
 * with a positive integer literal.
 *
 * The default value defined in CMake build scripts is 256.
 * Minimal suggested setting for low-resource builds is 128.
 */
#define ANJAY_MAX_SECRET_KEY_SIZE 128

/**
 * Maximum length supported for stringified floating-point values.
 *
 * Used when parsing plaintext and SenML JSON content formats - when parsing a
 * floating-point value, any string of length equal or greater than this setting
 * will automatically be considered invalid, even if it could in theory be
 * parsed as a valid number.
 *
 * If editing this file manually, <c>64</c> shall be
 * replaced with a positive integer literal.
 *
 * The default value defined in CMake build scripts is 512.
 * Minimal suggested setting for low-resource builds is 64.
 */
#define ANJAY_MAX_DOUBLE_STRING_SIZE 64

/**
 * Maximum length supported for a single Uri-Path or Location-Path segment.
 *
 * When handling incoming CoAP messages, any Uri-Path or Location-Path option of
 * length equal or greater than this setting will be considered invalid.
 *
 * If editing this file manually, <c>64</c> shall be
 * replaced with a positive integer literal.
 *
 * The default value defined in CMake build scripts is 256.
 * Minimal suggested setting for low-resource builds is 64.
 */
#define ANJAY_MAX_URI_SEGMENT_SIZE 64

/**
 * Maximum length supported for a single Uri-Query segment.
 *
 * When handling incoming CoAP messages, any Uri-Query option of length equal or
 * greater than this setting will be considered invalid.
 *
 * If editing this file manually, <c>64</c> shall be
 * replaced with a positive integer literal.
 *
 * The default value defined in CMake build scripts is 256.
 * Minimal suggested setting for low-resource builds is 64.
 */
#define ANJAY_MAX_URI_QUERY_SEGMENT_SIZE 64

/**
 * Size of buffer allocated for storing DTLS session state when connection is
 * not in use (e.g. during queue mode operation).
 *
 * If editing this file manually, <c>1024</c> shall be
 * replaced with a positive integer literal. The default value defined in CMake
 * build scripts is 1024.
 */
#define ANJAY_DTLS_SESSION_BUFFER_SIZE 1024

/**
 * Value of Content-Format used in Send messages. Only a few specific values are
 * supported:
 *
 * - @c AVS_COAP_FORMAT_NONE means no default value is used and Anjay will
 *   decide the format based on the what is available.
 * - @c AVS_COAP_FORMAT_OMA_LWM2M_CBOR Anjay will generate a Send message in
 *   LwM2M CBOR format.
 * - @c AVS_COAP_FORMAT_SENML_CBOR Anjay will generate a Send message in SenML
 *   CBOR format.
 * - @c AVS_COAP_FORMAT_SENML_JSON Anjay will generate a Send message in SenML
 *   JSON format.
 *
 * Note that to use a specific format it must be available during compilation.
 *
 * The default value defined in CMake build scripts is
 * <c>AVS_COAP_FORMAT_NONE</c>.
 */
#define ANJAY_DEFAULT_SEND_FORMAT AVS_COAP_FORMAT_NONE

/**
 * Optional Anjay modules.
 */
/**@{*/
/**
 * Enable access_control module (implementation of the Access Control object).
 *
 * Requires <c>ANJAY_WITH_ACCESS_CONTROL</c> to be enabled.
 */
/* #undef ANJAY_WITH_MODULE_ACCESS_CONTROL */

/**
 * Enable security module (implementation of the LwM2M Security object).
 */
#define ANJAY_WITH_MODULE_SECURITY

/**
 * Enable support for hardware security engine in the security module.
 *
 * This feature allows security credentials provisioned into the LwM2M Security
 * object to be automatically moved into a hardware security module.
 *
 * Requires <c>ANJAY_WITH_MODULE_SECURITY</c> to be enabled in Anjay
 * configuration, and at least one of
 * <c>AVS_COMMONS_WITH_AVS_CRYPTO_PKI_ENGINE</c> or
 * <c>AVS_COMMONS_WITH_AVS_CRYPTO_PSK_ENGINE</c> to be enabled in avs_commons
 * configuration.
 *
 * IMPORTANT: Only available as part of the HSM support commercial feature.
 * Ignored in versions distributed without this feature.
 */
/* #undef ANJAY_WITH_MODULE_SECURITY_ENGINE_SUPPORT */

/**
 * Enable server module (implementation of the LwM2M Server object).
 */
#define ANJAY_WITH_MODULE_SERVER

/**
 * Enable fw_update module (implementation of the Firmware Update object).
 */
#define ANJAY_WITH_MODULE_FW_UPDATE

/**
 * Disable support for PUSH mode Firmware Update.
 *
 * Only meaningful if <c>ANJAY_WITH_MODULE_FW_UPDATE</c> is enabled. Requires
 * <c>ANJAY_WITH_DOWNLOADER</c> to be enabled.
 */
/* #undef ANJAY_WITHOUT_MODULE_FW_UPDATE_PUSH_MODE */

/**
 * Enables ipso_objects module (generic implementation of the following kinds of
 * the basic sensor and three axis sensor IPSO objects).
 */
#define ANJAY_WITH_MODULE_IPSO_OBJECTS

/**
 * Enable at_sms module (implementation of an SMS driver for AT modem devices).
 *
 * Requires <c>ANJAY_WITH_SMS</c> to be enabled and the operating system to
 * support the POSIX <c>poll()</c> function.
 *
 * IMPORTANT: Only available as part of the SMS commercial feature. Ignored in
 * the open source version.
 */
/* #undef ANJAY_WITH_MODULE_AT_SMS */

/**
 * Enable bg96_nidd module (implementation of NB-IoT-based NIDD driver for
 * Quectel BG96).
 *
 * Requires <c>ANJAY_WITH_NIDD</c> to be enabled.
 *
 * IMPORTANT: Only available as part of the NIDD commercial feature. Ignored
 * in the open source version.
 */
/* #undef ANJAY_WITH_MODULE_BG96_NIDD */

/**
 * Enable bootstrapper module (loader for bootstrap information formatted as per
 * the "Storage of LwM2M Bootstrap Information on the Smartcard" appendix to the
 * LwM2M TS).
 *
 * Requires <c>ANJAY_WITH_BOOTSTRAP</c> to be enabled and
 * <c>AVS_COMMONS_WITH_AVS_PERSISTENCE</c> to be enabled in avs_commons
 * configuration.
 *
 * IMPORTANT: Only available with the boostrapper feature. Ignored in the open
 * source version.
 */
/* #undef ANJAY_WITH_MODULE_BOOTSTRAPPER */

/**
 * Enable factory provisioning module. Data provided during provisioning uses
 * SenML CBOR format.
 */
/* #undef ANJAY_WITH_MODULE_FACTORY_PROVISIONING */

/**
 * Enable oscore module (implementation of the OSCORE object).
 *
 * IMPORTANT: Only available as part of the OSCORE commercial feature. Ignored
 * in the open source version.
 */
/* #undef ANJAY_WITH_MODULE_OSCORE */
/**@}*/

#endif // ANJAY_CONFIG_H
