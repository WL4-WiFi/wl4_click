/*
 */

#include <click/config.h>
#include <click/args.hh>
#include "wl4_expiry_period.hh"
#include <click/straccum.hh>
#include <clicknet/ip.h>
#include <stdlib.h>
#include <stdio.h>
CLICK_DECLS

WL4ExpiryPeriod::WL4ExpiryPeriod()
{
}

WL4ExpiryPeriod::~WL4ExpiryPeriod()
{
}


int
WL4ExpiryPeriod::configure(Vector<String> &conf, ErrorHandler *errh)
{
	clock_gettime(CLOCK_REALTIME, &expiryTimeValue);
  return Args(conf, this, errh)
		 .read_mp("EP", _ep__)
		 .complete();
}


int
WL4ExpiryPeriod::initialize(ErrorHandler *)
{
  return 0;
}

int
WL4ExpiryPeriod::count(Packet *p)
{
  if(p->data()[14] == 'd' || p->data()[14] == 'e')
  {
		struct timespec curr;
		clock_gettime(CLOCK_REALTIME, &curr);

		uint64_t delta_ms = (curr.tv_sec - expiryTimeValue.tv_sec)
			* 1000000 + (curr.tv_nsec - expiryTimeValue.tv_nsec) / 1000000;
		clock_gettime(CLOCK_REALTIME, &expiryTimeValue);

		if(delta_ms > _ep__) {
			click_chatter("Token Expired");
			return 0;
		} else {
			click_chatter("------------------------Token Not Expired");
			return 1;
		}
  }
  return 0;
}

void
WL4ExpiryPeriod::push(int, Packet *p)
{
  int out = count(p);
  output(out).push(p);
}

Packet *
WL4ExpiryPeriod::pull(int)
{
  Packet *p = input(0).pull();
  if (p) count(p);
  return p;
}

CLICK_ENDDECLS
EXPORT_ELEMENT(WL4ExpiryPeriod)
