/*
 */

#include <click/config.h>
#include <click/args.hh>
#include "kernel_ctrl.hh"
#include <click/straccum.hh>
#include <clicknet/ip.h>
#include <stdlib.h>
#include <stdio.h>
CLICK_DECLS

KernelCtrl::KernelCtrl()
{
}

KernelCtrl::~KernelCtrl()
{
}


int
KernelCtrl::configure(Vector<String> &conf, ErrorHandler *errh)
{
  String iface_name;
  Args args = Args(this, errh).bind(conf);
  if (args.read_mp("IFACE", iface_name).execute() < 0)
    return -1;

  _command = "/home/amsmti3/code/hostap-hostap_2_6/wpa_supplicant/"
    "/wpa_cli -i";
  _command += iface_name;
  _command +=  " wl4_resume_queues 18:d6:c7:b8:e7:49";
  click_chatter(_command.mutable_c_str());
  return 0;
}


int
KernelCtrl::initialize(ErrorHandler *)
{
  return 0;
}

int
KernelCtrl::count(Packet *p)
{
  if(p->data()[14] == 'd' || p->data()[14] == 'e')
  {
		FILE *pipein_fp;
		char readbuf[8];
		if (( pipein_fp = popen("cat /proc/net/tcp | grep 6800A8C0 | awk"
						" --non-decimal-data 'BEGIN{x = 0}{n=split($5,array,\":\");y = "
						"sprintf(\"%d\", \"0x\" array[1]); x = x+y;}END{print x}'", "r"))
				== NULL) {
			click_chatter("ERROR IN KERNL CTRL");
			system(_command.mutable_c_str());
			return 0;
		}

		while(fgets(readbuf, 8, pipein_fp)){}
		pclose(pipein_fp);


		if(atoi(readbuf)) {
			system(_command.mutable_c_str());
			return 0;
		} else {
			WritablePacket* p2 = p->uniqueify();
			p2->data()[6] =(char)(0x60);
			p2->data()[7] =(char)(0xe3);
			p2->data()[8] =(char)(0x27);
			p2->data()[9] =(char)(0x12);
			p2->data()[10] =(char)(0x83);
			p2->data()[11] =(char)(0x56);
			p = p2;
			return 1;
		}
  }
  return 0;
}

void
KernelCtrl::push(int, Packet *p)
{
  int out = count(p);
  output(out).push(p);
}

Packet *
KernelCtrl::pull(int)
{
  Packet *p = input(0).pull();
  if (p) count(p);
  return p;
}

CLICK_ENDDECLS
EXPORT_ELEMENT(KernelCtrl)
