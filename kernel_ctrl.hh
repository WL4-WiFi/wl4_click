#ifndef CLICK_KERNELCTRL_HH
#define CLICK_KERNELCTRL_HH
#include <click/element.hh>
#include <click/timer.hh>
#include <map>
#include <click/sync.hh>
CLICK_DECLS


class KernelCtrl : public Element {

  inline int count(Packet *);

 public:

  KernelCtrl() CLICK_COLD;
  ~KernelCtrl() CLICK_COLD;

  const char *class_name() const		{ return "KernelCtrl"; }
  const char *port_count() const		{ return PORTS_1_1X2; }

  int initialize(ErrorHandler *) CLICK_COLD;
  virtual int configure(Vector<String> &conf, ErrorHandler *) CLICK_COLD;

  void push(int, Packet *);
  Packet *pull(int);
  String _command;

};

CLICK_ENDDECLS
#endif
