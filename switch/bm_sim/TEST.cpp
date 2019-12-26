#include "switch.cpp"

#include "crc_map.h"
#include "crc_tables.h"
#include "extract.h"
//#include "lpm_trie.h"
#include "md5.h"
#include "utils.h"
#include "version.h"
#include "xxhash.h"
#include "action_profile.cpp"
#include "actions.cpp"
#include "ageing.cpp"
#include "_assert.cpp"
#include "bytecontainer.cpp"
#include "calculations.cpp"
#include "checksums.cpp"
#include "conditionals.cpp"
#include "context.cpp"
#include "control_action.cpp"
#include "counters.cpp"
#include "crc_map.cpp"
#include "debugger.cpp"
#include "deparser.cpp"
#include "dev_mgr_bmi.cpp"
#include "dev_mgr.cpp"
#include "dev_mgr_packet_in.cpp"
#include "enums.cpp"
#include "event_logger.cpp"
#include "expressions.cpp"
#include "extern.cpp"
#include "fields.cpp"
#include "headers.cpp"
#include "header_unions.cpp"
#include "learning.cpp"
#include "logger.cpp"
#include "lookup_structures.cpp"
#include "match_tables.cpp"
#include "match_units.cpp"
#include "meters.cpp"
#include "options_parse.cpp"
//#include "P4Objects.cpp"
#include "packet.cpp"
#include "parser.cpp"
#include "parser_error.cpp"
#include "pcap_file.cpp"
#include "periodic_task.cpp"
#include "phv.cpp"
#include "phv_source.cpp"
#include "pipeline.cpp"
#include "port_monitor.cpp"
#include "simple_pre.cpp"
#include "simple_pre_lag.cpp"
#include "source_info.cpp"
#include "stacks.cpp"
#include "stateful.cpp"
#include "tables.cpp"
#include "target_parser.cpp"
#include "transport.cpp"
#include "transport_nn.cpp"
#include "simple_switch.h"
#include <bm/SimpleSwitch.h>
#include <bm/runtime/bm_runtime.h>
#include <bm/bm_sim/options_parse.h>
#include <bm/bm_sim/target_parser.h> 
//
//#include "bf_lpm_trie.h"
//#include "bf_lpm_trie.c"
class yt : public bm::Switch {
	public :
		yt (void): bm::Switch(true) {

		}
		int receive_(port_t port_num, const char *buffer, int len) {
			return 0; 
		}
		void start_and_return_() {
			 
		}
};
int main(int argc, char **argv ) {
	bm::TargetParserBasicWithDynModules simple_switch_parser;
	simple_switch_parser.add_flag_option("enable-swap","enable JSON swapping at runtime");
	simple_switch_parser.add_uint_option("drop-port", "choose drop port number (default is 511");
	bm::OptionsParser parser;
	parser.parse(argc, argv , &simple_switch_parser);
	bool enable_swap_flag = false;
	if  (simple_switch_parser.get_flag_option("enable-swap", &enable_swap_flag) != bm::TargetParserBasic::ReturnCode:SUCCESS) {
		std::exit(1) ;
	}
	simple_switch = new SimpleSwitch(enable_swap_flag,drop_port); 
	int status = simple_switch->init_from_options_parser(parser);
	if (status != 0) std::exit(status); 
	int thrift_port = simple_switch-> get_runtime_port(); 
	bm_runtime::start_server(simple_switch, thrift_port);
	using ::sswitch_runtime::SimpleSwitchIf;
	using ::sswitch_runtime::SimpleSwitchProcessor; 
	bm_runtime::add_service<SimpleSwitchIf, SimpleSwitchProcessor>( "simple_switch", sswitch_runtime::get_handler(simple_switch));
	simpe
	if (status != 0 ) return status ;
	bm::packet_handler( port, buffer, len , static_cast<void * > (&aswitch)  ) ;
}
