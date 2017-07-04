#ifndef CLICK_WL4_HH
#define CLICK_WL4_HH
#include <click/element.hh>
#include <click/timer.hh>
#include <map>
#include <click/sync.hh>
#include <time.h>
CLICK_DECLS


class WL4ExpiryPeriod : public Element {

  inline int count(Packet *);

 public:

  WL4ExpiryPeriod() CLICK_COLD;
  ~WL4ExpiryPeriod() CLICK_COLD;

  const char *class_name() const		{ return "WL4ExpiryPeriod"; }
  const char *port_count() const		{ return PORTS_1_1X2; }

  int initialize(ErrorHandler *) CLICK_COLD;
  virtual int configure(Vector<String> &conf, ErrorHandler *) CLICK_COLD;

  void push(int, Packet *);
  Packet *pull(int);
  String _command;
	int expiryTime;

	struct timespec expiryTimeValue;
	uint64_t _ep__;

};

CLICK_ENDDECLS
#endif
