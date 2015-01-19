#ifndef _CFGNETOPEER_TRANSAPI_H_
#define _CFGNETOPEER_TRANSAPI_H_

#ifdef __GNUC__
#	define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#	define UNUSED(x) UNUSED_ ## x
#endif

/**
 * Environment variable with settings for verbose level
 */
#define ENVIRONMENT_VERBOSE "NETOPEER_VERBOSE"

#define NETOPEER_MODULE_NAME "Netopeer"
#define NCSERVER_MODULE_NAME "NETCONF-server"

struct np_options {
	uint32_t hello_timeout; //TODO
	uint32_t idle_timeout; //TODO
	uint16_t max_sessions;
	uint8_t server_key_change_flag;		// flag to communicate server key change
	char* rsa_key;
	char* dsa_key;
	pthread_mutex_t client_keys_lock;
	struct np_auth_key {
		char* path;
		char* username;
		struct np_auth_key* next;
		struct np_auth_key* prev;
	} *client_auth_keys; //TODO
	uint8_t password_auth_enabled;
	uint8_t auth_attempts;
	uint16_t auth_timeout;
	uint16_t response_time;
	uint16_t client_removal_time;
	struct np_module {
		char* name; /**< Module name, same as filename (without .xml extension) in MODULES_CFG_DIR */
		struct ncds_ds* ds; /**< pointer to datastore returned by libnetconf */
		ncds_id id; /**< Related datastore ID */
		struct np_module* prev, *next;
	} *modules;
};

/**
 * @brief Load module configuration, add module to library (and enlink to list)
 *
 * @param module Module to enable
 * @param add Enlink module to list of active modules?
 *
 * @return EXIT_SUCCES or EXIT_FAILURE
 */
int module_enable(struct np_module* module, int add);

/**
 * @brief Stop module, remove it from library (and destroy)
 *
 * @param module Module to disable
 * @param destroy Unlink and free module?
 *
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int module_disable(struct np_module* module, int destroy);

#endif /* _CFGNETOPEER_TRANSAPI_H_ */