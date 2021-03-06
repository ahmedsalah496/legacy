#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>

#include "liblap.h"
#include "debug.h"

// Atmel ; LAP includes
// #include "config.h"


#ifndef max
 #define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

/**
 * Available commands array
 */
					/*
typedef struct {
	void (*fkt)(int, char**);
	char *cmd;
	char *sig;
	char *desc;
} cmd_t;

cmd_t cmds[] = {
  { &cmd_loopback,   "loopback", "loopback [0|1]", "Enable/disable loopback mode" },
  { &cmd_test, "test", "test ...", "Test commands" },
  { &cmd_packet, "packet", "packet <src> <dst> <data>", "Send arbitrary packets" },
  { &cmd_dump,   "dump", "dump", "Packet dump from CAN bus" },
  { &cmd_reset,  "reset", "reset <addr>", "Send reset to <addr>" },
  { &cmd_ping,   "ping", "ping <addr>", "Send ping to <addr>" },
  { &cmd_flash,  "flash", "flash <addr> <file>" ,"flash file to device"},
  { &cmd_lamp,  "lamp", "lamp <addr> <lamp> <value>" ,"set lamp on device to value"},
  { &cmd_borg,  "borg", "borg ..." ,"control bord device"},
  { &cmd_mood,  "mood", "mood ..." ,"control mood device"},
//  { &ftk_lampe, "lampe", "lampe ...",  "Control lampe-device" }
  { NULL, NULL, NULL, NULL }
};
*/

static char *progname;

static char *optstring = "hv::S:s:p:";
struct option longopts[] =
{
  { "help", no_argument, NULL, 'h' },
  { "verbose", optional_argument, NULL, 'v' },
  { "server", required_argument, NULL, 's' },
  { "serial", required_argument, NULL, 'S' },
  { "port", required_argument, NULL, 'p' },
  { NULL, 0, NULL, 0 }
};


void help()
{
//	cmd_t *ncmd;

	printf("\nUsage: %s [OPTIONS] <COMMAND>\n", progname);
	printf("\n\
Options:\n\n\
   -h, --help              display this help and exit\n\
   -v, --verbose           be more verbose and display a CAN packet dump\n\
   -s, --server HOST       use specified server (default: localhost)\n\
   -p, --port PORT         use specified TCP/IP port (default: 2342)\n\
   -S, --serial PORT       use specified serial port\n\n\
Commands:\n\n" );

//	ncmd = cmds;
//	while(ncmd->fkt) {
//		printf( "   %-30s %s\n", ncmd->sig, ncmd->desc );
//		ncmd++;
//	}
//	printf( "\n" );
}

/**
 * Main
 */
int main(int argc, char *argv[])
{
	int tcpport  = 2342;         // TCP Port
	char *server = "localhost"; 
	char *serial = NULL;
	int optc;

	progname = argv[0];

	while ((optc=getopt_long(argc, argv, optstring, longopts, (int *)0))
		!= EOF) {
		switch (optc) {
			case 'v':
				if (optarg)
					debug_level = atoi(optarg);
				else 
					debug_level = 3;
				break;
			case 'S':
				serial = optarg;
				break;
			case 's':
				server = optarg;
				break;
			case 'p':
				tcpport = atoi(optarg);
				break;
			case 'h':
				help();
				exit(0);
			default:
				help();
				exit(1);
		}
	} // while


	if (optind == argc) {
		help();
		exit(1);
	}

	if (serial) {
		debug(1, "Trying to establish CAN communication via serial %s", serial );
//		canu_init(serial);
//		can_init(NULL);		// use serial
		can_connect(server, tcpport);
	} else {
//		cann_conn_t *conn;

		debug(1, "Trying to establish CAN communication via cand (%s:%d)", server, tcpport );
		can_connect(server, tcpport);
//		can_init(conn);		// use specified connection to cand
	}

	char *arg = argv[optind];

//	cmd_t *cmd = cmds;
//	while(cmd->fkt) {
//		if (strcmp(arg, cmd->cmd) == 0) {
//			(*(cmd->fkt))(argc-optind, &(argv[optind]));
//			goto done;
//		}
//		cmd++;
//	}
//
//
	for(;;) {
		can_message_t msg;
		can_get(&msg);

		debug_hexdump(3, "PKT: ", &msg, sizeof(msg));

	}


	debug(0, "Command not understood" );
	help();

done:
	cann_close(0);

	return 0;
}
