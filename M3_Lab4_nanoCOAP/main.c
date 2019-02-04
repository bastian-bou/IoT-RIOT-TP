/*
 * Copyright (C) 2016 Kaspar Schleiser <kaspar@schleiser.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       CoAP example server application (using nanocoap)
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @}
 */

#include <stdio.h>

#include "net/nanocoap_sock.h"
#include "xtimer.h"
#include "lps331ap.h"
#include "lps331ap_params.h"

#define COAP_INBUF_SIZE (256U)

#define MAIN_QUEUE_SIZE     (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

static char stack[THREAD_STACKSIZE_MAIN];

uint32_t temperature, pression;

lps331ap_t dev;

/* import "ifconfig" shell command, used for printing addresses */
extern int _gnrc_netif_config(int argc, char **argv);

void *thread_sensors_handler(void *arg){
	(void) arg;
	while(1) {
		pression = lps331ap_read_pres(&dev);
		temperature = lps331ap_read_temp(&dev);
		
		xtimer_usleep(1000 * US_PER_MS);
	}
	return NULL;
}

int main(void)
{
    puts("RIOT nanocoap example application");
    
    if (lps331ap_init(&dev, &lps331ap_params[0]) == -1) {
		puts("ERROR init lps331ap");
		return -1;
	}
	
	thread_create(stack, sizeof(stack), THREAD_PRIORITY_MAIN -1, THREAD_CREATE_STACKTEST, thread_sensors_handler, NULL, "Temperature + pressure thread");

    /* nanocoap_server uses gnrc sock which uses gnrc which needs a msg queue */
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);

    puts("Waiting for address autoconfiguration...");
    xtimer_sleep(3);

    /* print network addresses */
    puts("Configured network interfaces:");
    _gnrc_netif_config(0, NULL);

    /* initialize nanocoap server instance */
    uint8_t buf[COAP_INBUF_SIZE];
    sock_udp_ep_t local = { .port=COAP_PORT, .family=AF_INET6 };
    nanocoap_server(&local, buf, sizeof(buf));

    /* should be never reached */
    return 0;
}
